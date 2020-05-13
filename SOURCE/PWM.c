/* CONNECT HEADER */
#include "../HEADERS/PWM.h"

/* BODY OF FUNCTIONS */
void PWM_Init() {
	DDRB |= (PWM_A | PWM_B);
}

void PWM_SetDutyCycle(uint8_t channel, uint8_t dutysCycle) {
	dutysCycle *= 2.55;

	switch (channel) {
	case 1:
		OCR1A = dutysCycle;    //Set the Duty Cycle between 0-100
		break;

	case 2:
		OCR1B = dutysCycle;    //Set the Duty Cycle between 0-100
		break;
	}
}

void PWM_Start() {
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << CS10) | (1 << CS11);
	OCR1A = 0;
	OCR1B = 0;
}


