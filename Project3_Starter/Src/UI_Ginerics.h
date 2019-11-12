#ifndef __UI_Ginerics_H
#define __UI_Ginerics_H

#include "UART.h"
#include "UI_Task.h"
#include "Validation.h"
#include <string.h>


void display_header(int span,char* string);
void display_string(char* string);
char* center_align(char* string, int span, char* buffer);
void wait_for_enter(void);
void  display_charater_sequence(int span, char charater);

#endif



