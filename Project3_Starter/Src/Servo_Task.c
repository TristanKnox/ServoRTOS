#include "Servo_Task.h"


servo_task_t servo_params[2];


void servo_task(void *parameters){
	int counter = 0;
	servo_task_t *params = (servo_task_t*) parameters;
	while(1){
		USART_Printf("%s is running this is the counter %d\r\n",params->name,counter);
		counter++;
	}
	while(1){
		USART_Printf("%s is running this is the counter %d\r\n",params->name,counter);
		counter++;
		if(params->recipe.is_active){
			Green_LED_On();
			command_t command = get_next_command(&params->recipe);
			execute_CMD(&params->servo, &command);
		}
		vTaskDelay(100);
	}
}

void init_servo_task(int id, char* task_name, channel_t channal, recipe_t recipe){
	servo_task_t *p = &servo_params[id];
	servo_t servo;
	init_servo(&servo,channal,PWM_count);
	p->id = id;
	strncpy(p->name,task_name,configMAX_TASK_NAME_LEN);
	p->servo = servo;
	p->recipe = recipe;
	xTaskCreate(servo_task, task_name, 256, (void*)p,2, p->handle);
}
