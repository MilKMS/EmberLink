/*
 * app_SegmentDisplay.h
 *
 *  Created on: Feb 17, 2025
 *      Author: aa
 */

#ifndef INC_APP_APP_SEGMENTDISPLAY_H_
#define INC_APP_APP_SEGMENTDISPLAY_H_
#include "main.h"
#include "App/app_Interrupt.h"
extern uint8_t SCAN_Mode_Seg[10][3];

extern void scanModeSegDisplay(void);
extern void FND_Display(uint8_t DisplayNum);

#endif /* INC_APP_APP_SEGMENTDISPLAY_H_ */
