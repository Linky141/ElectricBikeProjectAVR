#ifndef _PWM_H_
#define _PWM_H_

/* IMPLEMENTATIONS */
#include <avr/io.h>
#include "../Libraries/Headers/stdutils.h"

/* DEFINITHIONS */
#define PWM_A (1<<PD5)
#define PWM_B (1<<PD4)

/* FUNCTIONS */
void PWM_Init();
void PWM_SetDutyCycle(uint8_t channel,uint8_t dutyCycle);
void PWM_Start();


#endif
