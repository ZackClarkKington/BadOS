#include "strutils.h"

char* str_reverse(char* str, size_t len){
	for(int start = 0, end = len - 1; start < end; start++){
		swap(&str[start], &str[end]);
		end--;
	}
}

bool str_equal(char* a, char *b){
	int a_len = 0;
	int b_len = 0;

	for(int i = 0; a[i] != '\0'; i++){
		a_len = (i > a_len)? i : a_len;
	}

	for(int i = 0; b[i] != '\0'; i++){
		b_len = (i > b_len)? i : b_len;
	}

	if(a_len != b_len) return false;

	for(int i = 0; i < a_len; i++){
		if(a[i] != b[i]) return false;
	}

	return true;
}

static void swap(char* a, char* b){
	char swap_val = *a;
	*a = *b;
	*b = swap_val;
}

size_t strlen(char* str){
    size_t count = 0;

    while(str[count] != '\0'){
        count++;
    }

    return count;
}

void str_concat(char* a, char* b, char* buff){
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    for(int i = 0; i < len_a - 1; i++){
        buff[i] = a[i];
    }

    for(int i = len_a - 1; i < len_a + len_b - 1; i++){
        buff[i] = b[i];
    }

    buff[len_a + len_b] = '\0';
}
