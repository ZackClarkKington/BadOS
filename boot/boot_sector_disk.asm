[bits 16]
load_from_disk:
    pusha
    push dx

    mov ah, 0x02 ;0x02 = 'read'
    mov al, dh ;number of sectors to read
    mov cl, 0x02 ;first available sector = 0x02
    mov ch, 0x00
    mov dh, 0x00
    int 0x13
    jc disk_error
    pop dx
    cmp al, dh ;Check if correct # of sectors read
    jne sectors_error
    popa
    ret

disk_error:
    jmp disk_loop

sectors_error:
    jmp disk_loop
disk_loop:
    jmp $
