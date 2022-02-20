CC=/home/james/opt/cross/bin/i686-elf-gcc
LD=/home/james/opt/cross/bin/i686-elf-ld

FILES = ./build/kernel.asm.o ./build/kernel_main.o

all: ./bin/boot.bin ./bin/kernel.bin
	rm -rf ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin

	# Pad out to 100 sectors.  Allows for a 51kb kernel (room for expansion)
	# So we dont have to keep calculating kernel size as its being built.
	# 100 Sectors will be loaded into memory from the bootloader.

	dd if=/dev/zero bs=512 count=100 >> ./bin/os.bin  

./bin/kernel.bin: $(FILES)
	$(LD) -g -relocatable $(FILES) -o ./build/kernelfull.o
	$(CC) -T ./src/linker.ld -o ./bin/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o
	
./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf -g ./src/kernel.asm -o ./build/kernel.asm.o

./build/kernel_main.o : ./src/kernel_main.c
	$(CC) -c ./src/kernel_main.c -o ./build/kernel_main.o

clean:
	rm -rf ./bin/*.bin
	rm -rf ./build/kernelfull.o $(FILES)