


#include "stm32f446xx.h"
#include "LEDONOFF.h"

int main(){
	
//RCC->AHB1ENR |= CLOCK_ENABLE_AHB1_GPIOA;
	RCC->AHB1ENR |= (1<<0);                      // Enable GPIO PortA
//GPIOA->MODER |= GPIOA_MODER_OUTPUT_PIN5;
	GPIOA->MODER |= (1<<10);                     // select PA5 as General purpose output
	while(1){
//		GPIOA->BSRR |= 0x00000020;
		GPIOA->BSRR |= (1<<5);                     // set PA5
		for(int i=0; i<1200000; i++){
		
		};
//		GPIOA->BSRR |= 0x00200000;
		GPIOA->BSRR |=(1<<21);                     //reset PA5
		for(int i=0; i<1200000; i++){
		
		};
	}
}
