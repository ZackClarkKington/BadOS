#include "drivers/vga/text_mode.h"
#include "drivers/keyboard/ps2.h"
#include "globals/assert.h"
#include "globals/itoa.h"
#include "globals/strutils.h"

void _start() {
    init_display();
    print_ln("Executing Kernel");

    /*
    	Test the testing library
    */

    assert((true == true), "true == true");
    assert((true == false), "Expected fail, true != false");

    char* one = "2";
    itoa(1, one, 10);
    assert(str_equal(one, "1"), "itoa(1) != \"1\"");

    init_keyboard();
    char to_print = get_char();
    print_char(to_print, 0,1, 1);
}
