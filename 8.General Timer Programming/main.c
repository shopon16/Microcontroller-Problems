#include "stm32f446xx.h"
int count=0;

void TIM7_IRQHandler(void){
	count++;
	TIM7->SR &=~(1<<0);   //setting Update interrupt flag(bit possition 0) 0.           **0: No update occurred
	TIM7->CNT = 0;          // if not given, counts 2 at a time                  
}



int main(){
	SystemCoreClockUpdate();
	RCC->APB1ENR |= (1<<5);    //clock enable for timer7_APB1 peripheral(TIM7)
	TIM7->PSC = 800;   //Prescaller value
	TIM7->ARR = 10000;     //ARR value
	TIM7->CR1 |= (1<<2);     //Counter overflow generates update interrupt
	TIM7->DIER |= (1<<0);      //Update interrupt enabled
	TIM7->EGR |= (1<<0);         //Re-initializes the timer counter and generates an update of the registers.(UG bit) 
	
	
	NVIC_EnableIRQ(TIM7_IRQn);
	
	TIM7->CR1 |= (1<<0);   //Counter starts counting   
	while(1){
	
	
	
	}

	 

}
