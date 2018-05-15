#!/bin/sh
rm -rf bin
mkdir bin
echo 'Compiling kernel...'
cd kernel/drivers/vga
rm -rf bin
mkdir bin
gcc -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c text_mode.c -o ./bin/text_mode.o
cd ../../
rm -rf bin
mkdir bin
gcc -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c kernel.c -o ./bin/kernel.o
ld -r ./drivers/vga/bin/text_mode.o ./bin/kernel.o -o ../bin/kernel.o
echo 'Assembling kernel entry'
nasm kernel_entry.asm -f elf64 -o ../bin/kernel_entry.o
cd ../bin
echo 'Linking kernel and kernel entry'
ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary
cd ../boot
echo 'Assembling boot sector'
nasm -f bin boot_sector.asm -o ../bin/boot_sector.bin
cd ../bin
echo 'Constructing OS image'
cat boot_sector.bin kernel.bin > os-image.bin
cd ..
