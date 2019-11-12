#include "UI_Task.h"

int current_index = 0;

ui_task_t ui_params;

//Queues
QueueHandle_t servo1_queue;
QueueHandle_t servo2_queue;

void init_ui_task(int id, char* task_name, char* input_buffer, int max_input_size)
{
	ui_task_t *p = &ui_params;
	p->id = id;
	p->input = input_buffer;
	p->max_input_size = max_input_size;
	strncpy(p->name,task_name,configMAX_TASK_NAME_LEN);
	xTaskCreate(ui_task, task_name, 256, (void*)p,2, p->handle);
}


void ui_task(void *parameters){
	ui_task_t *p = (ui_task_t*) parameters;
	while(1){
		if(get_user_input(p->input, MAX_INPUT)){
			display_string(p->input);
			if(validate_input(p->input))
			{
				process_user_input(p->input);
			}
			else
			{
				display_string("Invalid Input");
			}
		}
	}
}

int get_user_input(char* input, int max_input_size){
	uint8_t ui_buffer[BUFFER_SIZE];
	char rxByte;
	int current_char;
	if(current_index == max_input_size){
			over_flow_error(max_input_size);
			current_index = 0;
			
		}
		if(USART2->ISR & USART_ISR_RXNE){
			rxByte = (uint8_t)(USART2->RDR & 0xFF);
			current_char = sprintf((char *) ui_buffer, "%c",rxByte);
			USART_Write(USART2,ui_buffer,current_char);	
			input[current_index] = rxByte;
			if(rxByte == 0x08){ // Backspace
				if(current_index > 0)
				{
					current_index--;
				}
				return 0;
			}
			current_index++;
		}
		if(rxByte == 0x0D){
			input[current_index - 1] = '\0';
			current_index = 0;
			return 1;
		}
	return 0;
}

void process_user_input(char* input)
{
	char message[MESSAGE_SIZE] = {0};
	switch(input[0])
	{
		case 'P':
		case 'p':
			snprintf(message,MESSAGE_SIZE, "p");
			//xQueueSend(servo1_queue,message,0);
			xQueueSend(servo_msg_queue[0],message,0);
			break;
		case 'C':
		case 'c':
			snprintf(message,MESSAGE_SIZE, "c");
			//xQueueSend(servo1_queue,message,0);
			xQueueSend(servo_msg_queue[0],message,0);
			break;
		case 'R':
		case 'r':
			snprintf(message,MESSAGE_SIZE, "r");
			//xQueueSend(servo1_queue,message,0);
			xQueueSend(servo_msg_queue[0],message,0);
			break;
		case 'L':
		case 'l':
			snprintf(message,MESSAGE_SIZE, "l");
			//xQueueSend(servo1_queue,message,0);
			xQueueSend(servo_msg_queue[0],message,0);
			break;
		case 'N':
		case 'n':
			break;
		case 'B':
		case 'b':
			snprintf(message,MESSAGE_SIZE, "p");
			//xQueueSend(servo1_queue,message,0);
			xQueueSend(servo_msg_queue[0],message,0);
			break;
		default:
			break;
	}
	
	switch(input[1])
	{
		case 'P':
		case 'p':
			snprintf(message,MESSAGE_SIZE, "p");
			//xQueueSend(servo2_queue,message,0);
			xQueueSend(servo_msg_queue[1],message,0);
			break;
		case 'C':
		case 'c':
			snprintf(message,MESSAGE_SIZE, "c");
			//xQueueSend(servo2_queue,message,0);
			xQueueSend(servo_msg_queue[1],message,0);
			break;
		case 'R':
		case 'r':
			snprintf(message,MESSAGE_SIZE, "r");
			//xQueueSend(servo2_queue,message,0);
			xQueueSend(servo_msg_queue[1],message,0);
			break;
		case 'L':
		case 'l':
			snprintf(message,MESSAGE_SIZE, "l");
			//xQueueSend(servo2_queue,message,0);
			xQueueSend(servo_msg_queue[1],message,0);
			break;
		case 'N':
		case 'n':
			break;
		case 'B':
		case 'b':
			snprintf(message,MESSAGE_SIZE, "b");
			//xQueueSend(servo2_queue,message,0);
			xQueueSend(servo_msg_queue[1],message,0);
			break;
		default:
			break;
	}
}


// Display over flow error mesage 
// used when user tries to input more chars than input string can hold
void over_flow_error(int limit){
	uint8_t overflow_buffer[OVERFLOW_BUFFER_SIZE];
	int msg = sprintf((char *) overflow_buffer, "\r\nExceeded char limit!\r\n");
	USART_Write(USART2,overflow_buffer,msg);
	msg = sprintf((char *) overflow_buffer, "Input may not exceed %d characters.\r\nPlease try again.\r\n",limit);
	USART_Write(USART2,overflow_buffer,msg);
}

