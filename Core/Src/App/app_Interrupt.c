/*
 * app_Interrupt.c
 *
 *  Created on: Feb 17, 2025
 *      Author: aa
 */
#include "App/app_interrupt.h"

uint16_t UartDelayCount = 0;

uint8_t SegDelayCount = 0;
uint8_t SegScanPos = 0;
uint16_t SegScanCount = 0;

uint8_t SegTrPos = 1;
uint16_t SegTrDelay = 0;


FlagAndCounter SwitchFAC[5];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_12) {
        // SW_MODE (A) SW_1
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {

        } else {

        }
    }
    else if (GPIO_Pin == GPIO_PIN_13) {
        // SW_UP (B) SW_2
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {

        } else {
			HAL_GPIO_WritePin(LINE_ALARM_GPIO_Port, LINE_ALARM_Pin, 1);
			HAL_GPIO_WritePin(LED_ALARM_GPIO_Port, LED_ALARM_Pin, 1);
        }
    }
    else if (GPIO_Pin == GPIO_PIN_14) {
        // SW_DOWN (C) SW_3
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) {

        } else {

        }
    }
    else if (GPIO_Pin == GPIO_PIN_15) {
        // SW_SET (D) SW_4
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET) {

        } else {

        }
    }
    else if (GPIO_Pin == GPIO_PIN_8) {
        // SW_RESET (E) SW_5
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {

        } else {

        }
    }
}


void SwitchFlagCount(){
	if ( SwitchFAC[0].Flag ) SwitchFAC[0].Counter++; // SW_MODE
	if ( SwitchFAC[1].Flag ) SwitchFAC[1].Counter++; // SW_UP
	if ( SwitchFAC[2].Flag ) SwitchFAC[2].Counter++; // SW_DOWN
	if ( SwitchFAC[3].Flag ) SwitchFAC[3].Counter++; // SW_SET
	if ( SwitchFAC[4].Flag ) SwitchFAC[4].Counter++; // SW_RESET
}

void HAL_IncTick(void)
{
    uwTick += uwTickFreq;

    if ( UC.TxReady && UC.TxTimer ) UC.TxTimer--;

    // 스위치 누른 시간 확인.
    SwitchFlagCount();

    if ( UC.TxSendFlag ) UC.ReceivedCounter++;

    if ( UartDelayCount ) UartDelayCount--;

    if ( !SegTrDelay ) {
        SegTrPos++;
        if ( SegTrPos > 3 ) SegTrPos = 1;
        SegTrDelay = 6;
    } else {
        SegTrDelay--;
    }

    return;
}
