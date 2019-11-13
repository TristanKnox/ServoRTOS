#ifndef __Global_Defines_H
#define __Global_Defines_H

#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "cmsis_os.h"

#define PCS (80)
#define PWM_count (20000) 
#define PWM_mode MODE_1

#define NUMBER_OF_SERVOS (2)

#define MAX_INPUT (3)
#define MESSAGE_SIZE (3)

// These values should be adjusted to calibrate each individual servo
// Once the min and max are set by using calibrat_servo the other duty cycles for positions in between are calculated as needed
#define SERVO_1_MIN_DUTY_CALIBRATION 3.1 //2.7  //Calibrated for box #13-2015 Right Servo
#define SERVO_1_MAX_DUTY_CALIBRATION 8.5 //9.2  //Calibrated for box #13-2015 Right Servo
#define SERVO_2_MIN_DUTY_CALIBRATION 3.0  //Calibrated for box #13-2015 Left Servo
#define SERVO_2_MAX_DUTY_CALIBRATION 9.5  //Calibrated for box #13-2015 Left Servo

extern QueueHandle_t servo_msg_queue[NUMBER_OF_SERVOS];


#endif





