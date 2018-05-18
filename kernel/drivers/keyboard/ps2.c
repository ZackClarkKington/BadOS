#include "ps2.h"
#include "../../globals/Queue.h"
#include "../../globals/io.h"

Keyboard k;

void init_keyboard(){
    k.kbd_code_set = 1;
    k.caps_lock = false;
    k.scroll_lock = false;
}

char get_char(){
    char *scan_set_1 = "\0\27\01234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;\'`\0\\zxcvbnm,./";
    char scan_code = get_scan_code() - 1;
    char ret = scan_set_1[scan_code];

    return ret;
}

char get_scan_code(){
    while (!(inb(0x64) & 1));
    return inb(0x60);
}