#include "isr.h"
#include "idt.h"
#include "../drivers/vga/textmode.h"

void init_isr_gates(){
    
    isr all_isr[] = {
        isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9,
        isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19,
        isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29,
        isr30, isr31, isr32, isr33, isr34    
    }
    
    for(int i = 0; i < 35; i++){
        set_idt_gate(i, (uintptr_t)all_isr[i], KERNEL_SEGMENT_SELECTOR, 0x8e);
    }
}

void isr_handler(){
    print_ln("Interrupt received");
    //TODO: Define exception messages and print appropriate message to term
}