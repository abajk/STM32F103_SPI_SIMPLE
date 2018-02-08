#include "stm32f10x.h"
#include "main.h"
#include "delay.h"
#include "spi.h"

void LED_Initialize(void);

int main(void){

	SystemInit();

  SystemCoreClockUpdate();	
	SysTick_Config(SystemCoreClock / 1000);                  // SysTick 1 msec interrupts
	
	LED_Initialize();
	SPI_Initialize();	
	
	uint8_t buf[20]="Aleksander Bajkowski";
	uint16_t buf_len = 20;
	
	for(;;){
		
		LED_bb ^= 1ul;
		SPI1_Transmit(buf,buf_len);
//		SPI1_Receive(buf,buf_len);
		Delay(100);
	}	
}

void LED_Initialize(void){
	RCC -> APB2ENR 		|= RCC_APB2ENR_IOPCEN;			//Enable clock for port A
	GPIOC -> CRH 			|= GPIO_CRH_MODE13;					//PA4 -> Output	
	GPIOC -> CRH			&= ~GPIO_CRH_CNF13;
}
