#include "drivers/vga/text_mode.h"

void _start() {
    init_display();
    print_ln("Executing Kernel");
}
