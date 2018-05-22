#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "text_mode.h"

static display screen;

void print_char(char a, size_t x, size_t y, bool shouldUpdate){
    if(x <= screen.width && y <= screen.height){
        screen.screen_buff[y][x] = a;
    }
    
    if(shouldUpdate) update_display();
}

void update_display(){
    uint16_t* VIDEO_MEM = (uint16_t*) 0xb8000;
    for(size_t y = 0; y < screen.height; y++){
        char *line = screen.screen_buff[y];
        for(size_t x = 0; x < screen.width; x++){
            size_t index = get_index(x,y);
            char a = line[x];
            VIDEO_MEM[index] = ((uint16_t) a | (uint16_t) screen.text_color << 8);
        }
    }
}

void set_text_color(color fg, color bg){
    screen.text_color = fg | bg << 4;
}

size_t get_index(size_t x, size_t y){
    return y * screen.width + x;
}

void clear_display(){
    screen.c.y = 0;
    screen.c.x = 0;

    for(size_t y = 0; y < screen.height; y++){
        for(size_t x = 0; x < screen.width; x++){
            print_char(' ', x,y, 0);
        }
    }
}

void print_str(char* str, size_t start_x, size_t y){
    for(size_t i = 0; i < screen.width && str[i] != '\0'; i++){
        print_char(str[i], start_x + i, y, 0);
    }
    update_display();
}

void print_ln(char* str){
    
    if(screen.c.y >= screen.height){
        clear_display();
    }

    size_t start_x = 0;
    size_t y = screen.c.y;
    print_str(str, start_x,y);
    screen.c.y++;
}

void init_display(){
    screen.c.x = 0;
    screen.c.y = 0;
    screen.width = 80;
    screen.height = 25;
    set_text_color(WHITE, BLACK);
    clear_display();
}
