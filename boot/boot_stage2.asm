start_pm:
    [bits 16]

    ;Set up A20 mode so we don't end up looping
    mov ax, 0x2401
    int 0x15
    in al, 0x92
    or al, 2
    out 0x92, al

    cli ;Disable interrupts
    lgdt [GDT32_descriptor] ;Load the 32-bit GDT
    ;set 32 bit mode here
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp GDT32_CODE_SEG:start32

start32:
    [bits 32]
    cli
    cld
    ;Set the segmentation registers
    mov ax, GDT32_DATA_SEG
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x30A000
    mov edi, 0x310000 ;Start of the page table
    mov cr3, edi
    ;Setting up dynamic page tables
    xor eax, eax
    mov ecx, 0x1000*2
    rep stosd
    mov edi, cr3
    mov DWORD [edi], 0x311003
    add edi, 0x1000
    mov DWORD [edi], 0X312003
    add edi, 0X1000
    mov ebx, 0x313003
    mov ecx, 512
    PDT:
        mov DWORD [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop PDT
    mov ebx, 0x00000003
    mov ecx, 512*512
    PT:
        mov DWORD [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop PT
    ;Enabling PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax
    ;Switch to 32 bit compatibility mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr
    ;Enable paging and switch into full 64 bit mode
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    ;Load the 64 bit gdt
    lgdt[GDT64_descriptor]
    jmp GDT64_CODE_SEG:start64

start64:
    [bits 64]
    cli ;Disable interrupts
    ;set the segmentation registers
    mov ax, GDT64_DATA_SEG
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ;Run the kernel
    call KERNEL_OFFSET
    hlt

GDT32_start:
    dd 0x0
    dd 0x0
GDT32_code:
    ;code segment
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
GDT32_data:
    ;data segment
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
GDT32_end:

GDT32_descriptor:
    dw GDT32_end - GDT32_start - 1
    dd GDT32_start

GDT32_CODE_SEG equ GDT32_code - GDT32_start
GDT32_DATA_SEG equ GDT32_data - GDT32_start

GDT64_descriptor:
    dw(GDT64_end - GDT64_start) - 1
    dd GDT64_start
GDT64_start:
    dd 0x0
    dd 0x0
GDT64_code:
    ;code segment
    dw 0
    dw 0
    db 0
    db 10011010b
    db 10101111b
    db 0
GDT64_data:
    ;data segment
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 00000000b
    db 0x0
GDT64_end:

GDT64_CODE_SEG equ GDT64_code - GDT64_start
GDT64_DATA_SEG equ GDT64_data - GDT64_start
