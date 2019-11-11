#ifndef __Global_Defines_H
#define __Global_Defines_H

#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"

#define PCS (80)
#define PWM_count (20000) 
#define PWM_mode MODE_1

#define NUMBER_OF_SERVOS (2)

// These values should be adjusted to calibrate each individual servo
// Once the min and max are set by using calibrat_servo the other duty cycles for positions in between are calculated as needed
#define SERVO_1_MIN_DUTY_CALIBRATION 3.1 //2.7  //Calibrated for box #13-2015 Right Servo
#define SERVO_1_MAX_DUTY_CALIBRATION 8.9 //9.2  //Calibrated for box #13-2015 Right Servo
#define SERVO_2_MIN_DUTY_CALIBRATION 2.7  //Calibrated for box #13-2015 Left Servo
#define SERVO_2_MAX_DUTY_CALIBRATION 9.8  //Calibrated for box #13-2015 Left Servo


#endif

