// Tristan Knox
#ifndef __PinSetup_H
#define __PinSetup_H

#include "stm32l476xx.h"

#define SLEW_COMP (50)

typedef enum{
	INPUT,	//Input mode
	OUTPUT,	//Gerneral purpose output mode
	ALT,		//Alternate function mode
	ANALOG	//Analog mode
}mode_t;

typedef enum{
	A,B,C,D,E,F,G,H //Represent the GPIOx groups where x = A..H
}GPIO_group_t;

typedef enum{
	CLEAR_MASK,
	SET_MASK,
	EXTRACT_MASK
}mask_t;

// Alt functions
typedef enum{
	AF0,	AF1,	AF2,	AF3,	AF4,	AF5,	AF6,	AF7,	AF8,	AF9,	AF10,	AF11,	AF12,	AF13,	AF14,	AF15
}AF_t;

// Pin data
typedef struct{
	GPIO_group_t group;
	int pin_number;
	mode_t mode;
	AF_t alt_function;
}pin_t;




//function declarations
void init_pinX(pin_t pin);
int read_pinX(pin_t pin);
void monitor_pinX(pin_t pin);
void output_pinX_ON(pin_t pin);
void output_pinX_OFF(pin_t pin);


//helper functions
void enable_clock(GPIO_group_t group);
GPIO_TypeDef * get_GPIOx(GPIO_group_t group);

void set_ALT_function(pin_t pin);
int get_AF_base_mask(pin_t pin);
//int build_mask(int pin_number, mask_t type, int bit_clusterint, int culster_size);
int bit_mask(int pin_number, mask_t type);
int mode_mask(pin_t pin, mask_t type);

//int get_bit_cluster(mode_t mode);
int mode_bit_config(mode_t mode);
void time_delay(int duration);

#endif 

