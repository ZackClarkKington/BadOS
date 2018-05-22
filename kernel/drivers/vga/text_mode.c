#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "text_mode.h"

static const size_t WIDTH = 80;
static const size_t HEIGHT = 25;
static size_t row = 0;
static uint8_t text_color;
char screen_buff[25][80];

void print_char(char a, size_t x, size_t y, bool shouldUpdate){
    if(x <= WIDTH && y <= HEIGHT){
        screen_buff[y][x] = a;
    }
    
    if(shouldUpdate) update_display();
}

void update_display(){
    uint16_t* VIDEO_MEM = (uint16_t*) 0xb8000;
    for(size_t y = 0; y < HEIGHT; y++){
        char *line = screen_buff[y];
        for(size_t x = 0; x < WIDTH; x++){
            size_t index = get_index(x,y);
            char a = line[x];
            VIDEO_MEM[index] = ((uint16_t) a | (uint16_t) text_color << 8);
        }
    }
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
            print_char(' ', x,y, 0);
        }
    }
}

void print_str(char* str, size_t start_x, size_t y){
    for(size_t i = 0; i < WIDTH && str[i] != '\0'; i++){
        print_char(str[i], start_x + i, y, 0);
    }
    update_display();
}

void print_ln(char* str){
    
    if(row >= HEIGHT){
        clear_display();
    }

    size_t start_x = 0;
    size_t y = row;
    print_str(str, start_x,y);
    row++;
}

void init_display(){
    set_text_color(WHITE, BLACK);
    clear_display();
}
