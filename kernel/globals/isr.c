#include "isr.h"
#include "idt.h"
#include "../drivers/vga/text_mode.h"
#include "io.h"
#include "assert.h"
#include "itoa.h"

isr all_isr[] = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9,
    isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19,
    isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29,
    isr30, isr31, isr32, isr33, isr34    
};

isr all_irq[] = {
    irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9,
    irq10, irq11, irq12, irq13, irq15
};

void init_isr_gates(){
    for(int i = 0; i < 35; i++){
        set_idt_gate(i, (uintptr_t)all_isr[i], KERNEL_SEGMENT_SELECTOR, 0x8e);
        assert((idt[i].offset_1 == (uintptr_t)all_isr[i] & 0xffff), "IDT Offset 1 not correctly set");
        assert((idt[i].segment_selector == KERNEL_SEGMENT_SELECTOR), "IDT segment selector not set to KERNEL_SEGMENT_SELECTOR");
        assert((idt[i].zero == 0), "IDT zero value not equal to 0");
        assert((idt[i].flags == 0x8e), "IDT flags not correctly set");
    }
    
    //Remap PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    for(int i = 35; i < 52; i++){
        set_idt_gate(i, (uintptr_t)all_irq[i - 35], KERNEL_SEGMENT_SELECTOR, 0x8e);
    }

    load_idtr();
}

void isr_handler(registers_store r){
    char * interrupt_messages[] = {
        "DivByZeroException",
        "DebugException",
        "NMIException", //Non-maskable Interrupt,
        "Breakpoint",
        "Overflow Detected",
        "OutOfBoundsException",
        "InvalidOpcodeException",
        "No Coprocessor",
        "DoubleFaultException",
        "Co-processor segment over-run detected",
        "BadTSSException",
        "SegmentNotPresentException",
        "StackFaultException",
        "GPFaultException", //General protection fault
        "Page Fault",
        "Unknown Interrupt",
        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"
    };
    
    print_ln("Received Interrupt");
    print_ln(interrupt_messages[r.interrupt_num]);
}

void irq_handler(registers_store r){
    if(r.interrupt_num >= 40) outb(0xA0, 0x20);
    outb(0x20, 0x20);

    if(all_isr[r.interrupt_num] != 0){
        isr handler = all_isr[r.interrupt_num];
        handler(r);
    }
}
