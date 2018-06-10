#!/bin/sh
rm -rf bin
mkdir bin
echo 'Compiling kernel...'
cd kernel/drivers/vga
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c text_mode.c -o ./bin/text_mode.o
cd ../../globals
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c Queue.c -o ./bin/Queue.o
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c io.c -o ./bin/io.o
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c idt.c -o ./bin/idt.o
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c isr.c -o ./bin/isr.o
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c assert.c -o ./bin/assert.o
nasm interrupt.asm -f elf64 -Fdwarf -o ./bin/interrupt.o
ld -r ./bin/idt.o ./bin/isr.o ./bin/interrupt.o -o ./bin/interrupts.o
cd ../drivers/keyboard
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c ps2.c -o ./bin/ps2.o
cd ../../
rm -rf bin
mkdir bin
$CROSS_COMPILER -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie -c kernel.c -o ./bin/kernel.o
ld -r ./globals/bin/assert.o ./globals/bin/interrupts.o ./globals/bin/io.o ./drivers/keyboard/bin/ps2.o ./drivers/vga/bin/text_mode.o ./bin/kernel.o -o ../bin/kernel.o
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