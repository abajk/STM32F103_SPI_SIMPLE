#include "stm32f10x.h"
#include "spi.h"

extern void SPI_Initialize(void){	
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

extern void SPI_Initialize_DMA(void){	
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
	
	SPI1 -> CR2 |= SPI_CR2_TXDMAEN;
	
	// set up DMA1 channel 3 for data transfer
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	// disable channel completely
	DMA1_Channel3->CCR = 0;
	// SPI address
	DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
	// other params
	DMA1_Channel3->CCR = 	DMA_CCR3_DIR |  	// memory->SPI
												DMA_CCR3_MINC | 	// memory increment
												DMA_CCR3_PL_1 |		// priority high
												DMA_CCR3_TCIE;		// transfer complete irq
	
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	NVIC_SetPriority(DMA1_Channel3_IRQn,14);
	
	SPI_EN_bb = 1ul;
}

extern int SPI1_Transmit(uint8_t *buf, uint16_t buf_len){
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

extern int SPI1_Transmit_DMA(uint8_t *buf, uint16_t buf_len){		
		DMA1_Channel3->CMAR = (uint32_t)buf;
		DMA1_Channel3->CNDTR = buf_len;
	
		SPI1_CS_bb = 0ul;
		DMA1_Channel3->CCR |= DMA_CCR3_EN;	
		return 0;
}	

extern int SPI1_Receive(uint8_t *buf, uint16_t buf_len){
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