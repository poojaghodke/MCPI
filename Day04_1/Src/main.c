/*
 * main.c
 *
 *  Created on: Mar 28, 2024
 *      Author: sunbeam
 */

#include<stdint.h>
#include<stdio.h>
#include"stm32f4xx.h"
#include"system_stm32f4xx.h"

#include"lcd.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	SystemInit();
	LcdInit();
	LcdPuts(LCD_LINE1, "Rise and Shine");
	LcdPuts(LCD_LINE2, "GOOD MORNING!!!");

    while(1)
    {
	for(int i=0;i<16;i++)
	{
		LcdWrite(LCD_CMD,LCD_leftshift);
		DelayMs(100);
	}
    }
	return 0;
}
