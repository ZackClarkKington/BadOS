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
    ;TODO: Restore state, write individual interrupt sections for pushing error codes