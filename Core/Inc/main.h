/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ALARM_Pin GPIO_PIN_13
#define LED_ALARM_GPIO_Port GPIOC
#define LED_SET_Pin GPIO_PIN_14
#define LED_SET_GPIO_Port GPIOC
#define LED_COMM_Pin GPIO_PIN_15
#define LED_COMM_GPIO_Port GPIOC
#define SEG_DP_Pin GPIO_PIN_0
#define SEG_DP_GPIO_Port GPIOA
#define SEG_G_Pin GPIO_PIN_1
#define SEG_G_GPIO_Port GPIOA
#define SEG_F_Pin GPIO_PIN_2
#define SEG_F_GPIO_Port GPIOA
#define SEG_E_Pin GPIO_PIN_3
#define SEG_E_GPIO_Port GPIOA
#define SEG_D_Pin GPIO_PIN_4
#define SEG_D_GPIO_Port GPIOA
#define SEG_C_Pin GPIO_PIN_5
#define SEG_C_GPIO_Port GPIOA
#define SEG_B_Pin GPIO_PIN_6
#define SEG_B_GPIO_Port GPIOA
#define SEG_A_Pin GPIO_PIN_7
#define SEG_A_GPIO_Port GPIOA
#define SEG_TR_3_Pin GPIO_PIN_0
#define SEG_TR_3_GPIO_Port GPIOB
#define SEG_TR_2_Pin GPIO_PIN_1
#define SEG_TR_2_GPIO_Port GPIOB
#define SEG_TR_1_Pin GPIO_PIN_2
#define SEG_TR_1_GPIO_Port GPIOB
#define SW_MODE_Pin GPIO_PIN_12
#define SW_MODE_GPIO_Port GPIOB
#define SW_MODE_EXTI_IRQn EXTI15_10_IRQn
#define SW_UP_Pin GPIO_PIN_13
#define SW_UP_GPIO_Port GPIOB
#define SW_UP_EXTI_IRQn EXTI15_10_IRQn
#define SW_DOWN_Pin GPIO_PIN_14
#define SW_DOWN_GPIO_Port GPIOB
#define SW_DOWN_EXTI_IRQn EXTI15_10_IRQn
#define SW_SET_Pin GPIO_PIN_15
#define SW_SET_GPIO_Port GPIOB
#define SW_SET_EXTI_IRQn EXTI15_10_IRQn
#define SW_RESET_Pin GPIO_PIN_8
#define SW_RESET_GPIO_Port GPIOA
#define SW_RESET_EXTI_IRQn EXTI9_5_IRQn
#define LINE_ALARM_Pin GPIO_PIN_11
#define LINE_ALARM_GPIO_Port GPIOA
#define LINE_OPEN_Pin GPIO_PIN_12
#define LINE_OPEN_GPIO_Port GPIOA
#define LINE_B_Pin GPIO_PIN_6
#define LINE_B_GPIO_Port GPIOB
#define LINE_A_Pin GPIO_PIN_7
#define LINE_A_GPIO_Port GPIOB
#define LED_PW_Pin GPIO_PIN_8
#define LED_PW_GPIO_Port GPIOB
#define LED_ERROR_Pin GPIO_PIN_9
#define LED_ERROR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
