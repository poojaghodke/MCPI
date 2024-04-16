/*
 * uart.h
 *
 *  Created on: Apr 4, 2024
 *      Author:
 */

#ifndef UART_H_
#define UART_H_

#define baud_9600 9600
#define baud_38400 38400
#define baud_115200 115200

#define BAUD_BRR_9600  0X683
#define BAUD_BRR_38400  0X1A1
#define BAUD_BRR_115200  OX8B

void UartInit(uint32_t baud);
void UartPutch(uint8_t ch);
uint8_t UartGetch (void);
void UartPuts(char str[]);
void UartGets(char str[]);

#endif /* UART_H_ */
