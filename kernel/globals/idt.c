#include "idt.h"

void set_idt_gate(uint8_t index, uintptr_t base, uint16_t selector, uint8_t flags){
	idt[index].offset_1 = base & 0xffff;
	idt[index].segment_selector = selector;
	idt[index].zero = 0;
	idt[index].flags = flags;
	idt[index].offset_2 = (base >> 16) & 0xffff;
	idt[index].offset_3 = base >> 32;
}

void load_idtr(){
	idt_register.base = (uintptr_t) &idt;
	idt_register.limit = 256 * sizeof(IDTDescr) - 1;
	asm volatile ("lidt (%0)" : : "r" (&idt_register));
}