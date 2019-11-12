#ifndef __VALIDATION_H
#define __VALIDATION_H
typedef struct{
	int min;
	int max;
}range_t;


int is_number(char* limit);
int validate_Yes_No(char* input);
int validate_input(char* input);
int validate_within_range(int value, range_t range);

#endif
