/*
 * app.h
 *
 *  Created on: Feb 13, 2025
 *      Author: aa
 */

#ifndef INC_APP_APP_CORE_H_
#define INC_APP_APP_CORE_H_

#include "main.h"
#include "App/app_SegmentDisplay.h"
#include "App/app_Interrupt.h"
#include "App/app_uart.h"
#include "App/Global.h"
#include "App/app_GpioControl.h"
#include "App/app_GlobalVar.h"
#include "stdbool.h"
#include "string.h"

extern void AppCore(void);

typedef struct {
 
	uint8_t TxSendFlag;
	uint16_t ReceivedCounter;

	uint8_t DataReceived;
	uint8_t TxReady;
	uint8_t TxRetryCount;

}UartControl;
extern UartControl UC;

typedef struct {

	/* 255 BroadCast ID */
	uint8_t SlaveID;

	/* 0: 화재 상태 반환, 1: 센서 접점 Off */
	uint8_t Status;
	
	/* Input ID */
	uint8_t Id;

	/* Error Code 
		0: No Error
		1: Data Error
		2: Command Error / ID Input Error
		3: CRC Error
	*/
	uint8_t ErrorCode;

	/* CRC */
	uint16_t crc16;

}RxDataFrame;


typedef struct{

	/* 스캔 중인 센서 ID */
	uint8_t SensorID; // 1 ~ 254
	uint16_t UartDelay; // 100ms Rx 딜레이
	uint8_t scanCount; // 에러나 무응답으로 인한 몇번 스캔 했는지
	uint8_t Command; // 전송한 커맨드

	uint8_t RxBuffer[5];

}ScanModeStatus;
extern ScanModeStatus SMStatus;

typedef enum{
    NONE = 0,
    SCAN,   // 1
    INPUT,  // 2
    TEST,   // 3
    MEMORY  // 4
}ModePositionType;

typedef struct {

	/*
		0: Noting
		1: Scan Mode
		2: Input Mode
		3: Test Mode
		4: Memory Mode
	*/
	ModePositionType ModePosition;


	/*
		일정 시간 카운트 후 Scan Mode로 복귀
	*/
	uint16_t ChangeTime;

}PagePosition;

/* -------------------------------------------------- */
typedef struct {
	uint8_t id;
	uint8_t fireFlag;
	uint8_t wireFlag;
}SensorStatus;

typedef struct {
    uint8_t Counter;
	SensorStatus Ids[255]; // 1 ~ 200
}SensorCollection;
/* -------------------------------------------------- */


typedef struct {

	PagePosition PP;
	// ID 메모리
	SensorCollection SC;

}AppMemory;

AppMemory M;

#endif /* INC_APP_APP_CORE_H_ */
