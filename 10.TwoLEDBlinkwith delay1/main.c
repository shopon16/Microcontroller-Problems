#include "stm32f446xx.h"
#include "Bits.h"
int count = -1;

void GPIOSetup(void){
	RCC->AHB1ENR |= GPIO_PORTA_ENABLE_BIT;                     // Clock enable for PA5_AHB1_Peripheral
	GPIOA->MODER |= PA5_GENERAL_PURPOSE_OUTPUT;               // select PA5 as General purpose output
	GPIOA->MODER |= PA6_GENERAL_PURPOSE_OUTPUT; 
}
void TimerSetup(void){
	SystemCoreClockUpdate();
	RCC->APB1ENR |= TIMER6_CLOCK_ENABLE;                        // clock enable for timer6_APB1 peripheral
	TIM6->PSC = 1600;                                         // Prescaller value slows down the clock
	TIM6->ARR = 10000;                                        // Auto Reload Value.  Counter will count 10000 pulse then reset
	TIM6->DIER |= UIE_BIT_ENABLE;                             // Update interrupt enabled
	TIM6->EGR |= UG_BIT_ENABLE;                              // Re-initializes the timer counter and generates an update of the registers. 
	NVIC_EnableIRQ(TIM6_DAC_IRQn);                            // Interrupt request
	
}


void TIM6_DAC_IRQHandler(void){                                                             
	TIM6->SR &=~(1<<0);                                    // clear the update interrupt flag bit (Update Interrupt Flag disable)          UIF: Update interrupt flag.  This bit is set by hardware when the registers are updated
	//GPIOA->ODR |= (1<<5);                                  // set GPIO PA5 pin which is connected to the in-built LED2
	count++;
}

void delay(uint16_t sec){                                        // second delay function
	TIM6->CR1 |= CEN_BIT_ENABLE;                                   // Counter starts counting  i have to turn the counter ON here otherwise timer wont give me precise count
	while(1){
			if(count>=sec){                                        
				TIM6->CR1 &= ~(1<<0);                                    // TIMER OFF
				//GPIOA->ODR &= ~(1<<5);                                   //LED OFF
				count = 0;
				break;
			}
	}
}

int main(){
	GPIOSetup();                                              // GPIO PA5 Setup
	TimerSetup();                                             // Timer6 Setup for 1 sec


	
	while(1){
		GPIOA->ODR |= (1<<5); 
		GPIOA->ODR &= ~(1<<6);
		delay(2);
		GPIOA->ODR &= ~(1<<5);
		GPIOA->ODR |= (1<<6);
		delay(2);
		
	}
}
