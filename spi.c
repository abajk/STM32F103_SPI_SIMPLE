#include "stm32f10x.h"
#include "spi.h"

void SPI_Initialize(void){	
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN |
										RCC_APB2ENR_AFIOEN |
										RCC_APB2ENR_IOPAEN;
		
	GPIOA -> CRL |= GPIO_CRL_MODE4 |
									GPIO_CRL_MODE5 |
									GPIO_CRL_MODE7;
	
	GPIOA -> CRL &= ~(GPIO_CRL_CNF4_0 |
										GPIO_CRL_CNF5_0 |
										GPIO_CRL_CNF7_0);
	
	GPIOA -> CRL |= GPIO_CRL_CNF5_1 |
									GPIO_CRL_CNF7_1;
	
	SPI1 -> CR1 |= SPI_CR1_BR_0 |
								 SPI_CR1_SSI |
								 SPI_CR1_SSM |
								 SPI_CR1_MSTR;	
	
	SPI_EN_bb = 1ul;
}

int SPI1_Transmit(uint8_t *buf, uint16_t buf_len){
		uint16_t i = buf_len - 1;
		SPI1_CS_bb = 0ul;
		do{
			while(!SPI_TXE_bb);
			SPI1 -> DR = *buf++;
		} while(i--);
		while(SPI_BSY_bb);
		SPI1_CS_bb = 1ul;
		return 0;
}	

int SPI1_Receive(uint8_t *buf, uint16_t buf_len){
		uint16_t i = buf_len - 1;
		SPI1_CS_bb = 0ul;
		while (i--){
			while(!SPI_RXNE_bb);
			*buf++ = SPI1 -> DR;
		}
		while(SPI_BSY_bb);
		SPI1_CS_bb = 1ul;
		return 0;
}	