#ifndef ASSERT_H
#define ASSERT_H
#include <stdbool.h>

void assert(bool, char*);
void assert_equal_int(int, int);
void assert_equal_str(char*, char*);
#endif //ASSERT_H
