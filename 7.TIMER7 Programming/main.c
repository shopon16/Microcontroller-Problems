#include "stm32f446xx.h"
int count =0;
void TIM7_IRQHandler(void){
	count++;
	TIM7->SR &= ~(1<<0);   //update interrupt flag disable
	TIM7->CR1 |= (1<<0);  //counter enable   CEN bit
	//TIM7->CNT =0;  



} 

int main(){
	SystemCoreClockUpdate();     
	RCC->APB1ENR |= (1<<5);           //Clock enable for timer7 APB1 peripheral (TIM7)    16MHz Clock Frequency
	TIM7->PSC = 6400;           // Prescaler value    slows down the clock
	TIM7->ARR = 50000;               // Auto Reload Value   Counter will count 10000 pulse then reset
	//TIM7->CR1 |= (1<<0);           //counter enable
	TIM7->DIER |= (1<<0);           //interrupt enable
	//TIM7->SR &= ~(1<<0);           //update interrupt flag disable
	TIM7->EGR |= (1<<0);        //Re-initializes the timer counter and generates an update of the registers.

	
//	TIM7->CR1 |= (1<<0);           //counter enable-----counting
	NVIC_EnableIRQ(TIM7_IRQn);     // interrupt calling
	
	while(1){
	
	
	}
	
}
