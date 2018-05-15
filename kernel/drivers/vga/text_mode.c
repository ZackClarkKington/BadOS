#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "text_mode.h"

static const size_t WIDTH = 80;
static const size_t HEIGHT = 25;
static size_t row = 0;
static uint8_t text_color;

void print_char(char a, size_t index){
    uint16_t* VIDEO_MEM = (uint16_t*) 0xb8000;
    VIDEO_MEM[index] = ((uint16_t) a | (uint16_t) text_color << 8);
}

void set_text_color(color fg, color bg){
    text_color = fg | bg << 4;
}

size_t get_index(size_t x, size_t y){
    return y * WIDTH + x;
}

void clear_display(){
    row = 0;

    for(size_t y = 0; y < HEIGHT; y++){
        for(size_t x = 0; x < WIDTH; x++){
            print_char(' ', get_index(x,y));
        }
    }
}

void print_str(char* str, size_t index){
    for(size_t i = 0; i < WIDTH && str[i] != '\0'; i++){
        print_char(str[i], index + i);
    }
}

void print_ln(char* str){
    
    if(row >= HEIGHT){
        clear_display();
    }

    size_t start_index = get_index(0, row);
    print_str(str, start_index);
    row++;
}

void init_display(){
    set_text_color(WHITE, BLACK);
    clear_display();
}
