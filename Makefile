CC=i686-elf-gcc
LD=i686-elf-ld

INCLUDES = -Iinc

FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels
FLAGS += -falign-loops -fstrength-reduce -fomit-frame-pointer -fno-builtin
FLAGS += -finline-functions -Wno-unused-label -Wno-cpp  -std=gnu99
FLAGS += -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

FILES = ./build/kernel.asm.o ./build/kernel.o ./build/stdio.o ./build/strings.o \
		./build/memory/memory.o ./build/memory/heap.o ./build/memory/kheap.o ./build/idt/idt.asm.o ./build/idt/idt.o ./build/idt/interrupts.o ./build/idt/pic.o \
		./build/io/io.asm.o ./build/io/io.o 

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
	nasm -f elf -g ./src/kernel/kernel.asm -o ./build/kernel.asm.o

./build/kernel.o : src/kernel/kernel.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/kernel/kernel.c -o ./build/kernel.o

./build/stdio.o : src/stdio/stdio.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/stdio/stdio.c -o ./build/stdio.o

./build/strings.o: src/strings/strings.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/strings/strings.c -o ./build/strings.o

./build/memory/memory.o: ./src/memory/memory.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/memory.c -o ./build/memory/memory.o

./build/memory/heap.o: ./src/memory/heap.c
./build/memory/kheap.o: ./src/memory/kheap.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/heap.c -o ./build/memory/heap.o
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/memory/kheap.c -o ./build/memory/kheap.o

./build/idt/idt.asm.o: ./src/idt/idt.asm
	nasm -f elf -g ./src/idt/idt.asm -o ./build/idt/idt.asm.o

./build/idt/idt.o: ./src/idt/idt.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/idt/idt.c -o ./build/idt/idt.o

./build/idt/interrupts.o: ./src/idt/interrupts/interrupts.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/idt/interrupts/interrupts.c -o ./build/idt/interrupts.o

./build/idt/pic.o: ./src/idt/PIC/pic.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/idt/PIC/pic.c -o ./build/idt/pic.o

./build/io/io.asm.o: ./src/io/io.asm
	nasm -f elf -g ./src/io/io.asm -o ./build/io/io.asm.o

./build/io/io.o: ./src/io/io.c
	$(CC) $(INCLUDES) $(FLAGS) -c ./src/io/io.c -o ./build/io/io.o

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
