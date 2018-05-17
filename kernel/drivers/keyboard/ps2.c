#include "ps2.h"
#include "../../globals/Queue.h"
#include "../../globals/io.h"

char scan_set_1[81] = {
    ' ','1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','Q','W','E','R','T','Y','U','I','O','P','[',']',' ',' ','A','S','D','F','G','H','J','K','L',';','\'','`',' ','\\','Z','X','C','V','B','N','M',',','.','/',' ','*',' ',' ',' '
};

Keyboard k;

void init_keyboard(){
    k.kbd_code_set = 1;
    k.caps_lock = false;
    k.scroll_lock = false;
}

char get_char(){
    char scan_code = get_scan_code() + 1;
    char ret;
    if(scan_code < 0x3A){
        ret = scan_set_1[scan_code];
    } else {
        ret = ' ';
    }
    return ret;
}

char get_scan_code(){
    char ret = 0;
    while(1){
        if(inb(0x60) != ret){
            ret = inb(0x60);
            if(ret > 0) return ret;
        }
    }
}
