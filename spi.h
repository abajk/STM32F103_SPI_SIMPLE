#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "bitband.h"

#define SPI1_CS_bb *((volatile unsigned char *)BITBAND_PERIPH(&GPIOA->ODR, 4))
#define SPI_RXNE_bb *((volatile unsigned char *)BITBAND_PERIPH(&SPI1 -> SR, 0))	
#define SPI_TXE_bb *((volatile unsigned char *)BITBAND_PERIPH(&SPI1 -> SR, 1))
#define SPI_BSY_bb *((volatile unsigned char *)BITBAND_PERIPH(&SPI1 -> SR, 7))
#define SPI_EN_bb *((volatile unsigned char *)BITBAND_PERIPH(&SPI1 -> CR1, 6))	

extern void SPI_Initialize(void);
extern void SPI_Initialize_DMA(void);
extern int SPI1_Transmit(uint8_t *buf, uint16_t buf_len);
extern int SPI1_Transmit_DMA(uint8_t *buf, uint16_t buf_len);
extern int SPI1_Receive(uint8_t *buf, uint16_t buf_len);

#endif