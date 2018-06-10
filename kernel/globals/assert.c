#include "assert.h"
#include "../drivers/vga/text_mode.h"

void assert(bool condition, char* message){
	if(!condition){
		print_ln("ASSERT CONDITION NOT MET: ");
		print_ln(message);
	}
}