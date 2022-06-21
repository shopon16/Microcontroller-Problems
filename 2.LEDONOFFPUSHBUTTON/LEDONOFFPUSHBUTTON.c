#include "stm32f446xx.h"
#include "Main.h"


int main(){
	RCC->AHB1ENR |= CLOCK_ENABLE_AHB1_GPIOA;                   //start clock for GPIOA AHB1
	RCC->AHB1ENR |= CLOCK_ENABLE_AHB1_GPIOC;                   // start clock for GPIOC AHB1
	
	GPIOA->MODER |= GPIOA_PA5_MODER_OUTPUT;                     //set PA5 as OUTPUT mode
	GPIOC->MODER &= ~(GPIOC_PC13_MODER_INPUT);                  //set the PC13 as INPUT mode

	while(1){
		if (GPIOC->IDR & THIRTEENTH_BIT){                        //if pushbutton is not pressed statement is true    **if not pressed IDR logic state is 1 for PC13
			GPIOA->BSRR |= GPIOA_PA5_RESET;                          // internal LED is OFF
		}
		else {                                                   // if pressed LED is ON
			GPIOA->BSRR |= GPIOA_PA5_SET;                        
		}

	}
}
