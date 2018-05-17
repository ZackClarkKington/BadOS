#ifndef PS2_H
#define PS2_H
#include <stdint.h>
#include <stdbool.h>

typedef struct{
    int kbd_code_set;
    bool caps_lock;
    bool scroll_lock;
}Keyboard;
void init_keyboard();
char get_char();
char get_scan_code();
#endif //PS2_H
