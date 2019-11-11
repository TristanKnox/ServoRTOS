#ifndef __Servo_Task_H
#define __Servo_Task_H

#include "ServoControl.h"
#include "Global_Defines.h"
#include "string.h"
#include "RecipeHandler.h"

typedef struct{
	int id;
	char name[configMAX_TASK_NAME_LEN];
	servo_t servo;
	recipe_t recipe;
	TaskHandle_t handle;	
}servo_task_t;

void servo_task(void *parameters);
void init_servo_task(int id, char* task_name, channel_t channel, recipe_t recipe);



#endif
