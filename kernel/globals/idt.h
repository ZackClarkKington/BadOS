#ifndef IDT_H
#define IDT_H
#include <stdint.h>

typedef struct {
    uint16_t offset_1;
    uint16_t segment_selector;
    uint8_t ist; //Interrupt stack table offset
    uint8_t flags; //Type and attributes
    uint16_t offset_2;
    uint16_t offset_3;
    uint32_t zero; //Reserved, always zero
}IDTDescr;

typedef struct {
    uint16_t limit; //Max addressable byte in the table
    uint64_t base; //Base address of IDT
}IDT_r;

IDTDescr idt[256];
IDT_r idt_register;

void set_idt_gate(uint8_t index, uintptr_t base, uint16_t selector, uint8_t flags);
void load_idtr();
#endif //IDT_H
