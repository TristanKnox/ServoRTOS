#ifndef __UI_Task_H
#define __UI_Task_H

#include "UART.h"
#include "Global_Defines.h"
#include "UI_Ginerics.h"
#include <string.h>
#include <stdio.h>

typedef struct{
	int id;
	char name[configMAX_TASK_NAME_LEN];
	char * input;
	int max_input_size;
	TaskHandle_t handle;	
}ui_task_t;

extern QueueHandle_t servo1_queue;
extern QueueHandle_t servo2_queue;

void ui_task(void *parameters);
int get_user_input(char* input, int max_input_size);
void process_user_input(char* input);
void over_flow_error(int limit);
void init_ui_task(int id, char* task_name, char* input_buffer, int max_input_size);


#endif
