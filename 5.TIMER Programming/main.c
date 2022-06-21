



#include "stm32f446xx.h"

int main(){
	RCC->APB1ENR |= (1<<4);
	TIM6->PSC |= 0x2710;    //preslaer value 10 000 	
	TIM6->ARR |= 0x1194;     //auto reload value 4500  
	TIM6->CR1 |= (1<<0);       // enable the counter   CEN bit Enable	
	TIM6->EGR |= 0x0;      // update generation

	



}
