#ifndef INC_APP_APP_UART_H_
#define INC_APP_APP_UART_H_
#include "main.h"
#include "App/Global.h"

#define UART_BUFFER_SIZE 256  // 링 버퍼 크기

typedef struct {
    uint8_t buffer[UART_BUFFER_SIZE];  // 데이터 저장 버퍼
    volatile uint16_t head;  // 쓰기 포인터 (ISR에서 변경)
    volatile uint16_t tail;  // 읽기 포인터 (메인 루프에서 변경)
} UART_RingBuffer;

extern UART_RingBuffer uart_rx_buffer;
extern void UART_Init();

#endif /* INC_APP_APP_UART_H_ */