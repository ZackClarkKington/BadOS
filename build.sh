#!/bin/sh
rm -rf bin
mkdir bin
echo 'Compiling kernel...'
cd kernel/globals
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c Queue.c -o ./bin/Queue.o
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c io.c -o ./bin/io.o
cd ../drivers/vga
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c text_mode.c -o ./bin/text_mode.o
cd ../keyboard
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c ps2.c -o ./bin/ps2-unlinked.o
ld -r ../../globals/bin/io.o ./bin/ps2-unlinked.o -o ./bin/ps2.o
cd ../../
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c kernel.c -o ./bin/kernel.o
ld -r ./drivers/keyboard/bin/ps2.o ./drivers/vga/bin/text_mode.o ./bin/kernel.o -o ../bin/kernel.o
echo 'Assembling kernel entry'
nasm kernel_entry.asm -f elf64 -Fdwarf -o ../bin/kernel_entry.o
cd ../bin
echo 'Linking kernel and kernel entry'
ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary
cd ../boot
echo 'Assembling boot sector'
nasm -f bin boot_sector.asm -o ../bin/boot_sector.bin
cd ../bin
echo 'Constructing OS image'
cat boot_sector.bin kernel.bin > os-image.bin
dd if=/dev/zero of=./os-image.img bs=1024 count=1440
dd if=./os-image.bin of=./os-image.img bs=512 conv=notrunc seek=0
cd ..