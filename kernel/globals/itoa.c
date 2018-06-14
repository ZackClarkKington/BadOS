#include "itoa.h"
#include <stdbool.h>
#include "strutils.h"

char* itoa(int i, char* a, int base){
	bool negative = false;
	int digitCount = 0;

	if(i == 0){
		a[0] = '0';
		a[1] = '\0';
		return a;
	}

	if(i < 0 && base == 10){
		negative = true;
		i = i * -1;
	}

	while(i != 0){
		int remainder = i % base;
		a[digitCount++] = (remainder > 9)? (remainder - 10) + 'a': remainder + '0';
		i = i / base;
	}

	if(negative) a[digitCount++] = '-';

	str_reverse(a, digitCount);

	return a; 
}