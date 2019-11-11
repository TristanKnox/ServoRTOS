#include "Servo_Task.h"


servo_task_t servo_params[2];

void led_on(int id);
void led_off(int id);


void servo_task(void *parameters){
	int counter = 0;
	servo_task_t *params = (servo_task_t*) parameters;
	
	while(1){
		//USART_Printf("%s is running this is the counter %d\r\n",params->name,counter);
		counter++;
		if(params->recipe.is_active){
			//USART_Printf("Holyshit its doing stuff %d",counter);
			led_on(params->id);
			command_t command = get_next_command(&params->recipe);
			execute_CMD(&params->servo, &command);
		}
		else
			led_off(params->id);
		vTaskDelay(1000);
	}
}

void init_servo_task(int id, char* task_name, channel_t channal, recipe_t recipe){
	servo_task_t *p = &servo_params[id];
	servo_t servo;
	init_servo(&servo,channal,PWM_count);
	if(id == 1)
		calibrate_servo(&servo,SERVO_1_MAX_DUTY_CALIBRATION,SERVO_1_MIN_DUTY_CALIBRATION);
	if(id == 2)
		calibrate_servo(&servo,SERVO_2_MAX_DUTY_CALIBRATION,SERVO_2_MIN_DUTY_CALIBRATION);
	set_servo_position(&servo,0);
	p->id = id;
	strncpy(p->name,task_name,configMAX_TASK_NAME_LEN);
	p->servo = servo;
	p->recipe = recipe;
	xTaskCreate(servo_task, task_name, 256, (void*)p,2, &p->handle);
}

void led_on(int id){
	if(id == 1)
		Green_LED_On();
	if(id == 2)
		Red_LED_On();
}

void led_off(int id){
	if(id == 1)
		Green_LED_Off();
	if(id == 2)
		Red_LED_Off();
}
