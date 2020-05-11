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


/* MAIN PROGRAM */
int main() {
	LCD_SetUp(PA_0, PA_1, PA_2, P_NC, P_NC, P_NC, P_NC, PA_3, PA_4, PA_5, PA_6);
	LCD_Init(1, 16);
	PWM_Init();
	PWM_Start();
	DDRB = 0x00;
	PORTB = 0xff;
int first=0;
int second = 100;

PWM_SetDutyCycle(1, first);
PWM_SetDutyCycle(2, second);
	while(true){

		if(BTN_plus){
				if(first < 100)first++;
				PWM_SetDutyCycle(1, first);
				DELAY_ms(300);
				LCD_Clear();
			}
		if(BTN_minus){
				if(first > 0)first--;
				PWM_SetDutyCycle(1, first);
				DELAY_ms(300);
				LCD_Clear();
			}

		LCD_XYPrintf(0, 0, "%d", first);
		LCD_XYPrintf(4, 0, "%d", second);
	}
	return (0);
}

/* FUNCTIONS */
//void Initialization(struct SettingsMenu_values *settinsgMenu_values, int *page,
//		struct LCDEXPLOITING_AllPages *lcdPageLabbles) {
//
//	UART_Init(9600);  // Initialize UARt at 9600 baud rate
//	/*Connect RS->PB0, RW->PB1, EN->PB2 and data bus to PORTB.4 to PORTB.7*/
//	LCD_SetUp(PA_0, PA_1, PA_2, P_NC, P_NC, P_NC, P_NC, PA_3, PA_4, PA_5, PA_6);
//	LCD_Init(2, 16);
//
//	DDRB = 0x00;
//	PORTB = 0xff;
//
//	PWM_Init();
//	PWM_Start();
//
//	LedControl_OFF(0);
//
//	//reading data from eeprom
//	bool firstStart;
//	unsigned char eepromAddressFirstStart = 0x01;
//	firstStart = EEPROM_ReadByte(eepromAddressFirstStart);
//
//	if (!firstStart) {
//		settinsgMenu_values->eepromAddressBrightness = 0x02;
//		settinsgMenu_values->pwmBrightness = 50;
//		settinsgMenu_values->pwmBrightness = EEPROM_ReadByte(
//				settinsgMenu_values->eepromAddressBrightness);
//		PWM_SetDutyCycle(1, 100);
//
//		settinsgMenu_values->eepromAddressLedStatus = 0x03;
//		settinsgMenu_values->ledStatus = true;
//		settinsgMenu_values->ledStatus = EEPROM_ReadByte(
//				settinsgMenu_values->eepromAddressLedStatus);
//
//		settinsgMenu_values->eepromAddressTimeDelay = 0x04;
//		settinsgMenu_values->timeDelay = 100;
//		settinsgMenu_values->timeDelay = EEPROM_ReadByte(
//				settinsgMenu_values->eepromAddressTimeDelay);
//
//		settinsgMenu_values->eepromAddressDebugMode = 0x05;
//		settinsgMenu_values->debugMode = false;
//		settinsgMenu_values->debugMode = EEPROM_ReadByte(
//				settinsgMenu_values->eepromAddressDebugMode);
//
//		settinsgMenu_values->eepromAddressShowChangingPage = 0x06;
//		settinsgMenu_values->showChangingPage = false;
//		settinsgMenu_values->showChangingPage = EEPROM_ReadByte(
//				settinsgMenu_values->eepromAddressShowChangingPage);
//	} else {
//		LCD_Clear();
//		LCD_XYPrintf(0, 0, "* First start  *");
//		LCD_XYPrintf(0, 1, "memory config...");
//		settinsgMenu_values->showChangingPage = false;
//		settinsgMenu_values->pwmBrightness = 50;
//		settinsgMenu_values->ledStatus = true;
//		settinsgMenu_values->timeDelay = 100;
//		settinsgMenu_values->debugMode = false;
//		firstStart = false;
//		EEPROM_WriteByte(eepromAddressFirstStart, firstStart);
//		EEPROM_WriteByte(settinsgMenu_values->eepromAddressBrightness,
//				settinsgMenu_values->pwmBrightness);
//		DELAY_ms(200);
//		EEPROM_WriteByte(settinsgMenu_values->eepromAddressLedStatus,
//				settinsgMenu_values->ledStatus);
//		DELAY_ms(200);
//		EEPROM_WriteByte(settinsgMenu_values->eepromAddressTimeDelay,
//				settinsgMenu_values->timeDelay);
//		DELAY_ms(200);
//		EEPROM_WriteByte(settinsgMenu_values->eepromAddressDebugMode,
//				settinsgMenu_values->debugMode);
//		DELAY_ms(200);
//		EEPROM_WriteByte(settinsgMenu_values->eepromAddressShowChangingPage,
//				settinsgMenu_values->showChangingPage);
//		DELAY_ms(200);
//		DELAY_ms(200);
//	}
//
//	//starting program
//	LCD_InitializeSymbols();
//	LCD_CmdWrite(0x0C); //turn cursor off
//	if (settinsgMenu_values->ledStatus)
//		LedControl_ON(1000);
//	else
//		DELAY_ms(1000);
//	LCD_Clear();
//	LCD_XYPrintf(3, 0, "USB Media");
//	LCD_XYPrintf(3, 1, "Controller");
//	for (int clk = 0; clk < settinsgMenu_values->pwmBrightness; clk++) {
//		LCDEXPLOITING_SetLctBrightness(clk);
//		DELAY_ms(20);
//	}
//	DELAY_ms(200);
//	LCD_Clear();
//
//	*page = 1;
//
//	if (settinsgMenu_values->ledStatus)
//		LedControl_OFF(100);
//	else
//		DELAY_ms(100);
//	if (settinsgMenu_values->ledStatus)
//		LedControl_ON(100);
//	else
//		DELAY_ms(100);
//	screen_show_initialize(settinsgMenu_values->ledStatus, lcdPageLabbles,
//			settinsgMenu_values);
//	LCDEXPLOITING_showPage(*page, lcdPageLabbles);
//	PORTB |= (1 << 0);
//
//	LCDEXPLOITING_SetLctBrightness(settinsgMenu_values->pwmBrightness);
//}
//
//void MainLoop(struct SettingsMenu_values *settinsgMenu_values, int *page,
//		struct LCDEXPLOITING_AllPages *lcdPageLabbles) {
//
//	int time = 200;
//	int clkPressedButton = 0;
//
//	int refreshClock= 0;
//	while (1) {
//		if (BTN_LEFT || BTN_RIGHT) {
//			if (BTN_RIGHT && ((*page) < 4)) {
//				if (settinsgMenu_values->ledStatus)
//					LedControl_ON(100);
//				else
//					DELAY_ms(100);
//				(*page)++;
//				ShowPage(500, *page, settinsgMenu_values->showChangingPage);
//				LCDEXPLOITING_showPage(*page, lcdPageLabbles);
//				if (settinsgMenu_values->ledStatus)
//					LedControl_OFF(100);
//				else
//					DELAY_ms(100);
//				DELAY_ms(settinsgMenu_values->timeDelay * 4);
//			} else if (BTN_LEFT && ((*page) > 1)) {
//				if (settinsgMenu_values->ledStatus)
//					LedControl_ON(100);
//				else
//					DELAY_ms(100);
//				(*page)--;
//				ShowPage(500, *page, settinsgMenu_values->showChangingPage);
//				LCDEXPLOITING_showPage(*page, lcdPageLabbles);
//				if (settinsgMenu_values->ledStatus)
//					LedControl_OFF(100);
//				else
//					DELAY_ms(100);
//				DELAY_ms(settinsgMenu_values->timeDelay * 4);
//			}
//		}
//		if (BTN_RL) {
//			SettingsMenu_ShowMenu(settinsgMenu_values);
//			*page = 1;
//			LCDEXPLOITING_showPage(*page, lcdPageLabbles);
//		}
//
//		if (BTN_1 || BTN_2 || BTN_3 || BTN_4) {
//			if (BTN_1) {
//				DEVCOMMAND_ExecuteCommand(1, *page,
//						settinsgMenu_values->ledStatus, time);
//			} else if (BTN_2) {
//				DEVCOMMAND_ExecuteCommand(2, *page,
//						settinsgMenu_values->ledStatus, time);
//			} else if (BTN_3) {
//				DEVCOMMAND_ExecuteCommand(3, *page,
//						settinsgMenu_values->ledStatus, time);
//			} else if (BTN_4) {
//				DEVCOMMAND_ExecuteCommand(4, *page,
//						settinsgMenu_values->ledStatus, time);
//			}
//			clkPressedButton++;
//			if (clkPressedButton == 3)
//				time = 150;
//			else if (clkPressedButton == 5)
//				time = 100;
//			else if (clkPressedButton == 8)
//				time = 0;
//		} else {
//			clkPressedButton = 0;
//			time = 200;
//		}
//		LCD_RefreshScreen(&refreshClock, 500);
//	}
//}
//
//void ShowPage(int time, int page, bool willShow) {
//	if (willShow) {
//		LCD_Clear();
//		LCD_XYPrintf(7, 0, "%d", page);
//		DELAY_ms(time);
//	}
//}
