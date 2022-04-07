CC=i686-elf-gcc
LD=i686-elf-ld

INCLUDES = -Iinc

FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels
FLAGS += -falign-loops -fstrength-reduce -fomit-frame-pointer -fno-builtin
FLAGS += -finline-functions -Wno-unused-label -Wno-cpp  -std=gnu99 -m32
FLAGS += -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

FILES = ./build/kernel.asm.o ./build/kernel.o ./build/stdio.o ./build/strings.o \
		./build/memory/memory.o ./build/memory/heap.o ./build/memory/kheap.o ./build/idt/idt.asm.o ./build/idt/idt.o \
		./build/idt/interrupts.o ./build/idt/pic.o ./build/io/io.asm.o ./build/io/io.o ./build/memory/paging.o \
		./build/memory/paging.asm.o ./build/disk/disk.o ./build/disk/disk_stream.o ./build/fs/path_parser.o

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin

	./build_size_check.sh ./bin/os.bin

	# Pad out to 100 sectors.  Allows for a 51kb kernel (room for expansion)
	# So we dont have to keep calculating kernel size as its being built.
	# 100 Sectors will be loaded into memory from the bootloader.

	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin  

./bin/kernel.bin: $(FILES)
	$(LD) -g -relocatable $(FILES) -o ./build/kernelfull.o
	$(CC) $(FLAGS) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o
	
./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: src/kernel/kernel.asm
./build/kernel.o : src/kernel/kernel.c
	nasm -f elf -g ./src/kernel/kernel.asm -o ./build/kernel.asm.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/kernel/kernel.c -o ./build/kernel.o

./build/stdio.o : src/stdio/stdio.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/stdio/stdio.c -o ./build/stdio.o

./build/strings.o: src/strings/strings.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/strings/strings.c -o ./build/strings.o

./build/memory/memory.o: ./src/memory/memory.c
./build/memory/heap.o: ./src/memory/heap/heap.c
./build/memory/kheap.o: ./src/memory/heap/kheap.c
./build/memory/paging.o: ./src/memory/paging/paging.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/memory.c -o ./build/memory/memory.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/heap/heap.c -o ./build/memory/heap.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/heap/kheap.c -o ./build/memory/kheap.o

	nasm -f elf -g ./src/memory/paging/paging.asm -o ./build/memory/paging.asm.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/paging/paging.c -o ./build/memory/paging.o

./build/idt/idt.asm.o: ./src/idt/idt.asm
./build/idt/idt.o: ./src/idt/idt.c
./build/idt/pic.o: ./src/idt/PIC/pic.c
./build/idt/interrupts.o: ./src/idt/interrupts/interrupts.c
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/idt/idt.c -o ./build/idt/idt.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/idt/PIC/pic.c -o ./build/idt/pic.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/idt/interrupts/interrupts.c -o ./build/idt/interrupts.o

./build/io/io.asm.o: ./src/io/io.asm
./build/io/io.o: ./src/io/io.c
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/io/io.c -o ./build/io/io.o

./build/disk/disk.o: ./src/disk/disk.c
./build/disk/disk_stream.o: ./src/disk/disk_stream.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/disk/disk.c -o ./build/disk/disk.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/disk/disk_stream.c -o ./build/disk/disk_stream.o


./build/fs/path_parser.o: ./src/fs/path_parser.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/fs/path_parser.c -o ./build/fs/path_parser.o

./bin/os.bin:
	make all

run: all
	qemu-system-i386 -hda ./bin/os.bin

debug: ./bin/os.bin
	gdb-multiarch -ex "target remote | qemu-system-i386 -hda ./bin/os.bin -S -gdb stdio" \
		-ex "add-symbol-file ./build/kernelfull.o 0x100000"
clean:
	rm -rf ./bin/*.bin
	rm -rf ./build/kernelfull.o $(FILES)
