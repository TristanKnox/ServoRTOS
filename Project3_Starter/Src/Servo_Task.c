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
			//USART_Printf("Task %s: command recieved: %s\r\n",params->name,message);
			process_message(message, params);
		}
		if(params->recipe.is_active){
			led_on(params->id);
			command_t command = get_next_command(&params->recipe);
			if(command.opcode == WAIT){
				//execute_CMD(&params->servo, &command);
				vTaskDelay(command.value*60);
			}
			else
				execute_CMD(&params->servo, &command);
		}
		else
			led_off(params->id);
		vTaskDelay(1000);
	}
}

void process_message(char* message, servo_task_t* const params)
{
	switch(message[0])
	{
		case 'P':
		case 'p':
			params->recipe.is_active = 0;
			break;
		case 'C':
		case 'c':
			params->recipe.is_active = 1;
			break;
		case 'R':
		case 'r':
			if(params->recipe.is_active == 0)
			{
				if(params->servo.pos < POS5)
				{
					set_servo_position(&params->servo, params->servo.pos+1);
				}
			}
			break;
		case 'L':
		case 'l':
			if(params->recipe.is_active == 0)
			{
				if(params->servo.pos > POS0)
				{
					set_servo_position(&params->servo, params->servo.pos-1);
				}
			}
			break;
		case 'N':
		case 'n':
			break;
		case 'B':
		case 'b':
			params->recipe.current_index = 0;
			params->recipe.is_active = 1;
			break;
		default:
			break;
	}
}

void init_servo_task(int id, char* task_name, channel_t channal, recipe_t recipe){
	servo_task_t *p = &servo_params[id];
	servo_msg_queue[id] = xQueueCreate(10,MESSAGE_SIZE);
	servo_t servo;
	init_servo(&servo,channal,PWM_count);
	if(id == 0)
		calibrate_servo(&servo,SERVO_1_MAX_DUTY_CALIBRATION,SERVO_1_MIN_DUTY_CALIBRATION);
	else if(id == 1)
		calibrate_servo(&servo,SERVO_2_MAX_DUTY_CALIBRATION,SERVO_2_MIN_DUTY_CALIBRATION);
	else 
		calibrate_servo(&servo,DEFAULT_MAX_DUTY,DEFAULT_MIN_DUTY);
	set_servo_position(&servo,0);
	p->id = id;
	strncpy(p->name,task_name,configMAX_TASK_NAME_LEN);
	p->servo = servo;
	p->recipe = recipe;
	xTaskCreate(servo_task, task_name, 256, (void*)p,2, &p->handle);
}

void led_on(int id){
	if(id == 0)
		Green_LED_On();
//	if(id == 1)
//		Red_LED_On();
}

void led_off(int id){
	if(id == 0)
		Green_LED_Off();
//pp
	
}
