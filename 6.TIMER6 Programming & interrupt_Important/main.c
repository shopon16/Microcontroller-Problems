#include "stm32f446xx.h"
#include "BitDefination.h"
int count =0;

void TIM6_DAC_IRQHandler(void){                                                             
			TIM6->SR &=~(1<<0);                                    // clear the update interrupt flag bit (Update Interrupt Flag disable)
			GPIOA->ODR ^= (1<<5);                                  // set and reset GPIO PA5 pin which is connected to the in-built LED2
			count++;

}

int main(){
	SystemCoreClockUpdate();
	RCC->AHB1ENR |= GPIO_PORTA_ENABLE_BIT;                     // Clock enable for PA5_AHB1_Peripheral
	RCC->APB1ENR |=TIMER6_CLOCK_ENABLE;                        // clock enable for timer6_APB1 peripheral
	GPIOA->MODER |= PA5_GENERAL_PURPOSE_OUTPUT;               // select PA5 as General purpose output
	TIM6->PSC = 6400;                                         // Prescaller value slows down the clock
	TIM6->ARR = 50000;                                        // Auto Reload Value.  Counter will count 10000 pulse then reset
	TIM6->DIER |= UIE_BIT_ENABLE;                             // Update interrupt enabled
	TIM6->EGR |= UG_BIT_ENABLE;                              // Re-initializes the timer counter and generates an update of the registers. 
	
	
	NVIC_EnableIRQ(TIM6_DAC_IRQn);                            //Interrupt request
	
	TIM6->CR1 |= CEN_BIT;                                   // Counter starts counting   
	while(1){
	
	}
 

}
