#ifndef __LED_H

#define __LED_H

#include "stm32f1xx_hal.h"

/*********** LED Pin Set **************/
#define LED_PORT        GPIOC
#define LED_PIN         GPIO_PIN_13


void LED_Sta( uint8_t sta );
void LED_Toggle( void );


#endif
