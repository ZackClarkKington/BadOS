#include "assert.h"
#include "../drivers/vga/text_mode.h"
#include "itoa.h"
#include "strutils.h"

void assert(bool condition, char* message){
	if(!condition){
		print_ln("ASSERT CONDITION NOT MET: ");
		print_ln(message);
	}
}

void assert_equal_int(int a, int b){
    char* expected;
    char* actual;

    if(a != b){
        itoa(a, expected, 10);
        itoa(b, actual, 10);
        print_ln("ASSERT CONDITION NOT MET: ");
        char *buffa;
        str_concat("expected: ", expected, buffa);
        print_ln(buffa);
        char *buffb;
        str_concat("got: ", actual, buffb);
        print_ln(buffb);
    }
}

void assert_equal_str(char* a, char* b){
   if(!str_equal(a,b)){
       print_ln("ASSERT CONDITION NOT MET: ");
       char *buffa;
       str_concat("expected: ", a, buffa);
       print_ln(buffa);
       char *buffb;
       str_concat("got: ", b, buffb);
       print_ln(buffb);
   }
}
