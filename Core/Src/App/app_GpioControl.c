/*
 * app_GpioControl.c
 *
 *  Created on: Feb 26, 2025
 *      Author: aa
 */

#include "App/app_GpioControl.h"

void ledOff() {
	HAL_GPIO_TogglePin(LED_SET_GPIO_Port, LED_SET_Pin);
	HAL_GPIO_TogglePin(LED_COMM_GPIO_Port, LED_COMM_Pin);
	HAL_GPIO_TogglePin(LED_ALARM_GPIO_Port, LED_ALARM_Pin);
	HAL_GPIO_TogglePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin);
}

void SWDIO_To_GPIO(uint8_t Flag) {
	if ( Flag ) {
		HAL_GPIO_WritePin(LED_SET_GPIO_Port, LED_SET_Pin, 1);
		return; // GPIO로 변경 안하고 다운로드로 사용
	}

	if ( (RCC->APB2ENR & RCC_APB2ENR_IOPAEN) == 0 ) {
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// PA13 (SWDIO) 핀을 GPIO로 변경
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

uint8_t SwitchModeSelector() {
	// 0 MODE, 1 UP, 2 DOWN, 3 SET, 4 RESET
	while ( SwitchFAC[1].Flag && SwitchFAC[2].Flag ) {
		if ( SwitchFAC[1].Counter > 3000 && SwitchFAC[2].Counter > 3000 ) {
			// SWDIO 활성화 아니면 GPIO 활성화
			return 1;
		}
	}
	return 0;
}