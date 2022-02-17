all:
	nasm -f bin boot.asm -o boot.bin
	nasm -f bin disk_read.asm -o disk_read.bin

#	Testing disk read
#	dd if=message.txt >> disk_read.bin
#	dd if=/dev/zero bs=512 count=1>> disk_read.bin


clean:
	rm boot.bin