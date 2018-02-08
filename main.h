#ifndef MAIN_H
#define MAIN_H

#include "bitband.h"	

#define LED_bb *((volatile unsigned char *)BITBAND_PERIPH(&GPIOC->ODR, 13))

#endif