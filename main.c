#include "stm32f10x.h"
#include "main.h"
#include "delay.h"
#include "spi.h"

static void LED_Initialize(void);

int main(void){

	SystemInit();

  SystemCoreClockUpdate();	
	SysTick_Config(SystemCoreClock / 1000);                  // SysTick 1 msec interrupts
	
	LED_Initialize();
	SPI_Initialize_DMA();	
	
	uint8_t buf[]="Aleksander Bajkowski";
	
	for(;;){
		
		LED_bb ^= 1ul;
		SPI1_Transmit_DMA(buf,sizeof(buf));
//		SPI1_Receive(buf,buf_len);
		Delay(100);
	}	
}

static void LED_Initialize(void){
	RCC -> APB2ENR 		|= RCC_APB2ENR_IOPCEN;			//Enable clock for port A
	GPIOC -> CRH 			|= GPIO_CRH_MODE13;					//PA4 -> Output	
	GPIOC -> CRH			&= ~GPIO_CRH_CNF13;
}
