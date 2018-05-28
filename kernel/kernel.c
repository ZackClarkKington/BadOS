#include "drivers/vga/text_mode.h"
#include "drivers/keyboard/ps2.h"
#include "globals/isr.h"
#include "globals/io.h"

void _start() {
	init_isr_gates();
    init_display();
    print_ln("Executing Kernel");
    init_keyboard();
    char to_print = get_char();
    print_char(to_print, 0,1, 1);
}
