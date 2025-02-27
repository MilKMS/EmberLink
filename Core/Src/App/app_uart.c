/*
 * app_uart.c
 *
 *  Created on: Feb 17, 2025
 *      Author: aa
 */
#include "App/app_uart.h"

uint8_t rx_data;
uint8_t rx_byte;

UART_RingBuffer uart_rx_buffer = { .head = 0, .tail = 0 };  // 링 버퍼 초기화

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {  // UART1 수신 인터럽트
        uint16_t next_head = (uart_rx_buffer.head + 1) % UART_BUFFER_SIZE;  // 다음 위치 계산

        if (next_head != uart_rx_buffer.tail) {  // 버퍼가 가득 차지 않았을 경우
            uart_rx_buffer.buffer[uart_rx_buffer.head] = rx_byte;  // 데이터 저장
            uart_rx_buffer.head = next_head;  // 헤드 포인터 업데이트
        }

        // 다시 인터럽트 수신 활성화 (계속 수신하도록 설정)
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}


void UART_Init(){
	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = 115200;
	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  huart1.Init.StopBits = UART_STOPBITS_1;
	  huart1.Init.Parity = UART_PARITY_NONE;
	  huart1.Init.Mode = UART_MODE_TX_RX;
	  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart1) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

int UART_ReadByte(uint8_t *data) {
    if (uart_rx_buffer.head == uart_rx_buffer.tail) {
        return 0;  // 버퍼가 비어 있음
    }

    *data = uart_rx_buffer.buffer[uart_rx_buffer.tail];  // 데이터 읽기
    uart_rx_buffer.tail = (uart_rx_buffer.tail + 1) % UART_BUFFER_SIZE;  // 포인터 업데이트

    return 1;  // 읽기 성공
}