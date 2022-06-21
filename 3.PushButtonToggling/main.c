#include "stm32f446xx.h"
#include <stdbool.h>

int main(){
	bool LEDON = true;
	bool LEDOFF = false;

	RCC->AHB1ENR |= (1<<0);                                 //start clock for GPIOA AHB1
	RCC->AHB1ENR |= (1<<2);                                 // start clock for GPIOC AHB1
	GPIOA->MODER |= (1<<10);                                //GPIOA->MODER |= GPIOA_MODER_OUTPUT_PIN5;
	GPIOC->MODER &= ~((1<<26) | (1<<27));                   //set the PC13 as input mode

	while(1){
		if(LEDON && (GPIOC->IDR & (1<<13))){
			GPIOA->BSRR |= (1<<5);              
			LEDON = false;
			
		}
		else if(LEDOFF && (GPIOC->IDR & (1<<13))){
			GPIOA->BSRR |= 0x00200000;
			LEDON = false;
			
		}
		
		
		
		
		
		
		
		
		
//		if (GPIOC->IDR & (1<<13)){
//			GPIOA->BSRR |= (1<<5);
//		}
//		else if (!(GPIOC->IDR & (1<<13))){
//			GPIOA->BSRR |= 0x00200000;
//		}

	}
}
