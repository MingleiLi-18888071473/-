#ifndef __KEY_H

#define __KEY_H

#include "stm32f1xx_hal.h"


/*********** KEY Pin Set **************/
#define KEY_PORT        GPIOA
#define KEY_PIN         GPIO_PIN_11



uint8_t Key_StaRead( void );

#endif
