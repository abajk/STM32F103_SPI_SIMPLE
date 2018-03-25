#include "stm32f10x.h"

#define BITBAND_PERIPH(address, bit) ((void*)(PERIPH_BB_BASE + (((uint32_t)address) - PERIPH_BASE) * 32 + (bit) * 4))