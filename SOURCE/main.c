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
#include <avr/io.h>
#include <stdbool.h>
#include "../Libraries/Headers/delay.h"
#include "../Libraries/Headers/lcd.h"
//#include "../HEADERS/DEV_COMMAND.h"
//#include "../HEADERS/LCD_EXPLOITING.h"
#include "../HEADERS/pwm.h"
//#include "../HEADERS/LEDcontrol.h"
//#include "../HEADERS/UART_COMMUNICATION.h"
//#include "../HEADERS/SettingsMenu.h"

/* DEFINITHIONS */
#define BTN_plus (!(PINC & 0x1))
#define BTN_minus (!(PINC & 0x2))
#define BTN_left (!(PINC & 0x4))
#define  BTN_right (!(PINC & 0x8))

/* DECLARATIONS FUNCTIONS */
uint16_t adc_read(uint8_t ch);
float voltRead(uint8_t ch);
uint16_t setPwmValue(float volt, uint8_t multiplier);
void AddOrRemovePercent(uint8_t current, bool add);
void Initialize();
void MainLoop();
void ReadInputValue();
void ScreenRefresh();
void Timer1();
bool WaitPageChange();
bool WaitChangeValue();

uint16_t first = 0;
uint16_t firstPercent = 0;
uint16_t second = 0;
uint16_t secondPercent = 0;
uint8_t currentChecked = 1;
float voltage = 0;
int timer1=0;
int timer1Overflow=1000;
int waitPageChange = 0;
int waitPageChangeOverflow = 1000;
int waitChangeValue = 0;
int waithangeValueOverflow = 300;


/* MAIN PROGRAM */
int main() {
	Initialize();
	MainLoop();

	return (0);
}

/* FUNCTIONS */

void Timer1(){
	timer1++;
	if(timer1 >= timer1Overflow){
		timer1=0;
		ScreenRefresh();
	}
}

bool WaitPageChange(){
	waitPageChange++;
	if(waitPageChange >= waitPageChangeOverflow){
		waitPageChange=0;
		return true;
	}
	return false;
}

bool WaitChangeValue(){
	waitChangeValue++;
	if(waitChangeValue >= waithangeValueOverflow){
		waitChangeValue=0;
		return true;
	}
	return false;
}

void ScreenRefresh(){
	LCD_Clear();
	LCD_XYPrintf(1, 0, "%d/%d", first, firstPercent);
	LCD_XYPrintf(1, 1, "%d/%d", second, secondPercent);
	if (currentChecked == 1) {
		LCD_XYPrintf(0, 0, ">");
		LCD_XYPrintf(0, 1, " ");
	}
	if (currentChecked == 2) {
		LCD_XYPrintf(0, 0, " ");
		LCD_XYPrintf(0, 1, ">");
	}
}

void MainLoop() {
	PWM_SetDutyCycle(1, first);
	PWM_SetDutyCycle(2, second);

	while (true) {
		Timer1();
		ReadInputValue();
		if (BTN_left) {
			if (currentChecked > 1)
				if(WaitPageChange()) currentChecked--;
		}
		if (BTN_right) {
			if (currentChecked < 2)
				if(WaitPageChange()) currentChecked++;
		}
		if (BTN_plus) {
			AddOrRemovePercent(currentChecked, true);
		}
		if (BTN_minus) {
			AddOrRemovePercent(currentChecked, false);
		}
	}
}

void ReadInputValue(){
	if (voltage != voltRead(4)) {
				voltage = voltRead(4);
				second = setPwmValue(voltage, secondPercent);
				first = setPwmValue(voltage, firstPercent);
				PWM_SetDutyCycle(1, first);
				PWM_SetDutyCycle(2, second);
			}
}

void Initialize() {
	LCD_SetUp(PD_0, PD_1, PD_2, P_NC, P_NC, P_NC, P_NC, PD_3, PD_4, PD_5, PD_6);
	LCD_Init(2, 8);
	PWM_Init();
	PWM_Start();
	DDRC = 0x00;
	PORTC = 0xff;

	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void AddOrRemovePercent(uint8_t current, bool add) {

	if (add) {
		switch (current) {
		case 1:
			if(WaitChangeValue()){
			if (firstPercent < 100)
				firstPercent++;
			first = setPwmValue(voltage, firstPercent);
			PWM_SetDutyCycle(1, first);
		}
			break;
		case 2:
			if(WaitChangeValue()){
			if (secondPercent < 100)
				secondPercent++;
			second = setPwmValue(voltage, secondPercent);
			PWM_SetDutyCycle(1, second);
			}
			break;
		}
	} else {
		switch (current) {
		case 1:
			if(WaitChangeValue()){
			if (firstPercent > 0)
				firstPercent--;
			first = setPwmValue(voltage, firstPercent);
			PWM_SetDutyCycle(1, first);
			}
			break;
		case 2:
			if(WaitChangeValue()){
			if (secondPercent > 0)
				secondPercent--;
			second = setPwmValue(voltage, secondPercent);
			PWM_SetDutyCycle(1, second);
			}
			break;
		}
	}

}

uint16_t adc_read(uint8_t ch) {
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8) | ch; // clears the bottom 3 bits before ORing
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
		;
	return (ADC);
}

float voltRead(uint8_t ch) {
	uint16_t adc = adc_read(ch);
	return adc / 222.391;
}

uint16_t setPwmValue(float volt, uint8_t multiplier) {
	uint16_t val = ((volt * 100) / 4.6) * (multiplier / 100.0);
	return val;
}
