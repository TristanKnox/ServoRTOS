#include "Servo_Task.h"


servo_task_t servo_params[NUMBER_OF_SERVOS];
QueueHandle_t servo_msg_queue[NUMBER_OF_SERVOS];

void led_on(int id);
void led_off(int id);


void servo_task(void *parameters){
	int counter = 0;
	servo_task_t *params = (servo_task_t*) parameters;
	int id = params->id;
	char message[MESSAGE_SIZE] = {0};
	while(1){
		if(xQueueReceive(servo_msg_queue[id],message,0)){
			USART_Printf("Task %s: command recieved: %s\r\n",params->name,message);
		}
		if(params->recipe.is_active){
			led_on(params->id);
			command_t command = get_next_command(&params->recipe);
			if(command.opcode == WAIT)
				vTaskDelay(command.value);
			else
				execute_CMD(&params->servo, &command);
		}
		else
			led_off(params->id);
		vTaskDelay(1000);
	}
}

void init_servo_task(int id, char* task_name, channel_t channal, recipe_t recipe){
	servo_task_t *p = &servo_params[id];
	servo_msg_queue[id] = xQueueCreate(10,MESSAGE_SIZE);
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
