[extern isr_handler]

isr_common:
    push rax
    push rbx
    push rcx
    push rbp
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler ;Now we have pushed the registers, hand over to interrupt handler
    pop rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov fs, ax
    mov gs, ax
    pop rax
    pop rbx
    pop rcx
    pop rbp
    pop rsi
    pop rdi
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
    add rsp, 16
    sti
    iret


global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
global isr32
global isr33
global isr34

isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common

isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common

isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common

isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common

isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common

isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common

isr8:
    cli
    push byte 0
    push byte 8
    jmp isr_common

isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common

isr10:
    cli
    push byte 0
    push byte 10
    jmp isr_common

isr11:
    cli
    push byte 0
    push byte 11
    jmp isr_common

isr12:
    cli
    push byte 0
    push byte 12
    jmp isr_common

isr11:
    cli
    push byte 0
    push byte 13
    jmp isr_common

isr12:
    cli
    push byte 0
    push byte 13
    jmp isr_common

isr13:
    cli
    push byte 0
    push byte 13
    jmp isr_common

isr14:
    cli
    push byte 0
    push byte 14
    jmp isr_common

isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common

isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common

isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common

isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common

isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common

isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common

isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common

isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common

isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common

isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common

isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common

isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common

isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common

isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common

isr 29:
    cli
    push byte 0
    push byte 29
    jmp isr_common

isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common

isr31:
    cli
    push byte 0
    push byte 30
    jmp isr_common

isr32:
    cli
    push byte 0
    push byte 32
    jmp isr_common

isr33:
    cli
    push byte 0
    push byte 33
    jmp isr_common

isr34:
    cli
    push byte 0
    push byte 34
    jmp isr_common

