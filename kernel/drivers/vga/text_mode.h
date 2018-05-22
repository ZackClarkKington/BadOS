#ifndef TEXT_MODE_H
#define TEXT_MODE_H
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    BLACK = 0,
    WHITE = 15
}color;

void update_display(void);
void print_char(char, size_t, size_t, bool);
void set_text_color(color, color);
void clear_display(void);
size_t get_index(size_t, size_t);
void init_display(void);
void print_str(char*, size_t, size_t);
void print_ln(char*);
#endif // TEXT_MODE_H_
