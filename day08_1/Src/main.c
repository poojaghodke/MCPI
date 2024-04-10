/*
 * main.c
 *
 *  Created on: Apr 2, 2024
 *      Author: sunbeam
 */
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "eeprom.h"
#include <string.h>
#include "uart.h"
#include"i2c.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	char str[32]="";
	char str1[32]="";
	SystemInit();
	EEPROM_Init();
	UartInit(BAUD_9600);
	   int choice;
	   while(1)
	   {
	  UartPuts("Enter choice :1.write string 2.read string \r\n");
	   UartGets(str);
	   sscanf(str, "%d", &choice);
	   switch(choice)
	   {
	   	   case 1:
	   	   {
	   		   UartPuts("Enter a String: \r\n");
	   		   UartGets(str1);
	   		   EEPROM_Write(0x0020,(uint8_t*)str1,32);
	   		   break;
	   	   }
	   	   case 2:
	   	   {
	   		   EEPROM_Read(0x0020, (uint8_t*)str1, 32);
	   		   UartPuts(str1);
	   		   break;
	   	   }
	   }
	   }
	return 0;
}

