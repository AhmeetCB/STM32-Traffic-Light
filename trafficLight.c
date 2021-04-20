#include "stm32f10x.h"
volatile int sayac;
void SysTick_Handler(void)
	{
		sayac++;  
	}
int main()
{
	RCC -> APB2ENR |= (1<<2); //A Enable
	GPIOA-> CRL &=~((1<<10)|(1<<11));  //A2 Output Mode
	GPIOA -> CRL |=((1<<9)|(1<<8));	
	GPIOA-> CRL &=~((1<<14)|(1<<15));  //A3 Output Mode
	GPIOA -> CRL |=((1<<13)|(1<<12));	
	GPIOA-> CRL &=~((1<<18)|(1<<19));  //A4 Output Mode
	GPIOA -> CRL |=((1<<17)|(1<<16));	
	SysTick->LOAD=(72000000/8000); //Set systick to 1sec
	
	while(1){
		sayac=0;
		SysTick->CTRL=3;   //systick interrupt enable
		
		if(sayac<3000)  
		{ GPIOA->ODR|=(1<<2);}
		while(sayac<=3000);
		
		
		if(sayac<4000) 
		{ GPIOA->ODR|=(1<<3);}
		while(sayac<4000);
		
		
		if(sayac<=7000) 
		{GPIOA->ODR&=~((1<<2)|(1<<3)); 
		 GPIOA->ODR|=(1<<4);
		}
		while(sayac<=7000); 
		
		
		if(sayac<8000) 
		{GPIOA->ODR&=~(1<<4);
		 GPIOA->ODR|=(1<<3);
		}
		while(sayac<=8000);
		
		GPIOA->ODR&=~(1<<3); 
		SysTick->CTRL=0;
	}
}