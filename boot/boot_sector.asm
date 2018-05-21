[bits 16]
[org 0x7c00]
KERNEL_OFFSET equ 0x1000
mov [BOOT_DRIVE], dl
jmp word 0x0000:start

load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 35 ;Read 35 sectors to give us a generous space for the kernel
    mov dl, [BOOT_DRIVE]
    call load_from_disk
    ret
start:
    mov ax, 0x1F00
    mov ss, ax
    mov sp, 0x7C00
    ;Inform BIOS we wish to operate in 64bit mode
    mov ax, 0xEC00
    mov bx, 03h
    int 15h
    ;Load kernel into memory
    call load_kernel
    ;Call second stage
    call start_pm
    jmp $

%include "boot_stage2.asm"
%include "boot_sector_disk.asm"

BOOT_DRIVE db 0
;The actual bootsector
times 510-($-$$) db 0
dw 0xaa55
