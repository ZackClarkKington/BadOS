#ifndef STRUTILS_H
#define STRUTILS_H
#include <stddef.h>
#include <stdbool.h>

char* str_reverse(char*, size_t);
bool str_equal(char*, char*);
static void swap(char*, char*);
size_t strlen(char*);
void str_concat(char*, char*, char*);
#endif //STRUTILS_h
