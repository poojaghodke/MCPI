/*
 * spi.c
 *
 *  Created on: Apr 3, 2024
 *      Author:
 */

#include "spi.h"
#include "stm32f4xx.h"
#include "stm32f407xx.h"

void SPI_Init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	GPIOE->OSPEEDR &= ~BV(SPI_CS_PIN*2+1);
	GPIOE->OSPEEDR |= BV(SPI_CS_PIN*2);
	GPIOE->PUPDR &= ~(BV(SPI_CS_PIN*2+1) | BV(SPI_CS_PIN*2));
	GPIOE->OTYPER &= ~BV(SPI_CS_PIN);
	GPIOE->MODER &= ~BV(SPI_CS_PIN*2+1);
	GPIOE->MODER |= BV(SPI_CS_PIN*2);
	SPI_CS_Disable();

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->OSPEEDR &= ~(BV(SPI_MOSI_PIN*2+1)|BV(SPI_MISO_PIN*2+1)|BV(SPI_SCLK_PIN*2+1)); // GPIO speed=Medium(0b01)
	GPIOA->OSPEEDR |= (BV(SPI_MOSI_PIN*2)|BV(SPI_MISO_PIN*2)|BV(SPI_SCLK_PIN*2));
	GPIOA->PUPDR &= ~(BV(SPI_MOSI_PIN*2)|BV(SPI_MISO_PIN*2)|BV(SPI_SCLK_PIN*2)); // GPIO Pull-Down (0b10)
	GPIOA->PUPDR |= (BV(SPI_MOSI_PIN*2+1)|BV(SPI_MISO_PIN*2+1)|BV(SPI_SCLK_PIN*2+1));
	GPIOA->OTYPER &= ~(BV(SPI_MOSI_PIN)|BV(SPI_MISO_PIN)|BV(SPI_SCLK_PIN));	// GPIO push-pull
	GPIOA->MODER &= ~(BV(SPI_MOSI_PIN*2)|BV(SPI_MISO_PIN*2)|BV(SPI_SCLK_PIN*2)); // GPIO mode=AltFn(0b10)
	GPIOA->MODER |= (BV(SPI_MOSI_PIN*2+1)|BV(SPI_MISO_PIN*2+1)|BV(SPI_SCLK_PIN*2+1));
	GPIOA->AFR[0] = (SPI_ALT_FN << GPIO_AFRL_AFSEL5_Pos) | (SPI_ALT_FN << GPIO_AFRL_AFSEL6_Pos) | (SPI_ALT_FN << GPIO_AFRL_AFSEL7_Pos);

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | (0x02 << SPI_CR1_BR_Pos);
	SPI1->CR2 = 0x0000;
	SPI1->CR1 |= SPI_CR1_SPE;
}

uint16_t SPI_Transmit(uint8_t dataW) {
	while(!(SPI1->SR & SPI_SR_TXE))
		;
	uint32_t frame = dataW;
	SPI1->DR = frame;
	while(!(SPI1->SR & SPI_SR_RXNE))
		;
	frame = SPI1->DR;
	return frame;
}

uint16_t SPI_Receive(void) {
	uint32_t val = SPI_Transmit(0x00);
	return val;
}

void SPI_CS_Enable(void) {
	GPIOE->BSRR = BV(SPI_CS_CLR_BIT);
}

void SPI_CS_Disable(void) {
	GPIOE->BSRR = BV(SPI_CS_SET_BIT);
}

