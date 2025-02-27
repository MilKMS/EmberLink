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

FlagAndCounter SwitchFAC[5];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if ( huart == USART1 ) {
         UC.DataReceived = 1;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_12) {
        // SW_MODE
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) {
            SwitchFAC[0].Flag = 1;
            SwitchFAC[0].Counter = 0;  // 🔹 버튼을 눌렀을 때 카운트 초기화
        } else {
            SwitchFAC[0].Flag = 0;
        }
    }
    else if (GPIO_Pin == GPIO_PIN_13) {
        // SW_UP
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
            SwitchFAC[1].Flag = 1;
            SwitchFAC[1].Counter = 0;
        } else {
            SwitchFAC[1].Flag = 0;
        }
    }
    else if (GPIO_Pin == GPIO_PIN_14) {
        // SW_DOWN
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) {
            SwitchFAC[2].Flag = 1;
            SwitchFAC[2].Counter = 0;
        } else {
            SwitchFAC[2].Flag = 0;
        }
    }
    else if (GPIO_Pin == GPIO_PIN_15) {
        // SW_SET
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET) {
            SwitchFAC[3].Flag = 1;
            SwitchFAC[3].Counter = 0;
        } else {
            SwitchFAC[3].Flag = 0;
        }
    }
    else if (GPIO_Pin == GPIO_PIN_8) {
        // SW_RESET
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
            SwitchFAC[4].Flag = 1;
            SwitchFAC[4].Counter = 0;
        } else {
            SwitchFAC[4].Flag = 0;
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

  // 스위치 누른 시간 확인.
  SwitchFlagCount();

  if ( UC.TxSendFlag ) UC.ReceivedCounter++;

  if( UartDelayCount ) UartDelayCount--;

  if( SegDelayCount ) SegDelayCount--;

  if( SegScanCount > 100 ){
	  SegScanCount = 0;

	  SegScanPos++;
	  if( SegScanPos > 9 ) SegScanPos = 0;
  }

  SegScanCount++;

  return;
}
