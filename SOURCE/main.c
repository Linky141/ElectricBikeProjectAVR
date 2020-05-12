/*
 * main.c
 *
 *  Created on: 17 gru 2019
 *      Author: Tomasz Bielas
 *
 *
 *
 */

/* IMPLEMENTATIONS */
#include <avr\io.h>
#include <stdbool.h>
#include "../Libraries/Headers/uart.h"
#include "../Libraries/Headers/delay.h"
#include "../Libraries/Headers/lcd.h"
//#include "../HEADERS/DEV_COMMAND.h"
//#include "../HEADERS/LCD_EXPLOITING.h"
#include "../HEADERS/pwm.h"
#include "../Libraries/Headers/eeprom.h"
//#include "../HEADERS/LEDcontrol.h"
//#include "../HEADERS/UART_COMMUNICATION.h"
//#include "../HEADERS/SettingsMenu.h"

/* DEFINITHIONS */
#define INPUTVAL (!(PINB & 0x1))
#define OUT1 (!(PINB & 0x2))
#define OUT2 (!(PINB & 0x3))
#define BTN_plus (!(PINB & 0x4))
#define BTN_minus (!(PINB & 0x8))

/* DECLARATIONS FUNCTIONS */
uint16_t adc_read(uint8_t ch);
float voltRead(uint8_t ch);
uint16_t setPwmValue(float volt, uint8_t multiplier);
/* MAIN PROGRAM */
int main() {
	LCD_SetUp(PC_0, PC_1, PC_2, P_NC, P_NC, P_NC, P_NC, PC_3, PC_4, PC_5, PC_6);
	LCD_Init(1, 16);
	PWM_Init();
	PWM_Start();
	DDRB = 0x00;
	PORTB = 0xff;

	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);


	uint16_t first=0;
	uint16_t firstPercent=0;
uint16_t second = 0;
float voltage=0;

PWM_SetDutyCycle(1, first);
PWM_SetDutyCycle(2, second);
	while(true){
		if(voltage != voltRead(0))
		{
			voltage = voltRead(0);
			second = setPwmValue(voltage, 100);
			first = setPwmValue(voltage, firstPercent);
			PWM_SetDutyCycle(1, first);
			PWM_SetDutyCycle(2, second);
		}
		if(BTN_plus){
				if(firstPercent < 100)firstPercent++;
				first = setPwmValue(voltage, firstPercent);
				PWM_SetDutyCycle(1, first);
				DELAY_ms(300);
				LCD_Clear();
			}
		if(BTN_minus){
				if(firstPercent > 0)firstPercent--;
				first = setPwmValue(voltage, firstPercent);
				PWM_SetDutyCycle(1, first);
				DELAY_ms(300);
				LCD_Clear();
			}

		LCD_XYPrintf(0, 0, "%d/%d", first, firstPercent);
		LCD_XYPrintf(6, 0, "%d", second);
//		LCD_XYPrintf(0, 0, "%fV", voltage);
	}
	return (0);
}

/* FUNCTIONS */
uint16_t adc_read(uint8_t ch)
{
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing

  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC);

  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));

  return (ADC);
}

float voltRead(uint8_t ch){
	uint16_t adc = adc_read(ch);
	return adc/222.391;
}
uint16_t setPwmValue(float volt, uint8_t multiplier){
	uint16_t val = ((volt*100)/4.6)*(multiplier/100.0);
	return val;
}
