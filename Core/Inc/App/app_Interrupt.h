/*
 * app_Interrupt.h
 *
 *  Created on: Feb 17, 2025
 *      Author: aa
 */

#ifndef INC_APP_APP_INTERRUPT_H_
#define INC_APP_APP_INTERRUPT_H_
#include "main.h"
#include "App/Global.h"
#include "App/app_GlobalVar.h"
#include "App/app_core.h"

typedef struct {
	uint8_t  Flag;
	uint16_t Counter;
}FlagAndCounter;

extern FlagAndCounter SwitchFAC[5];

extern uint16_t UartDelayCount;
extern uint16_t UartDelayCount2;

extern uint8_t SegDelayCount;
extern uint8_t SegScanPos;

#endif /* INC_APP_APP_INTERRUPT_H_ */
