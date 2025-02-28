/*
 * system_core.c
 *
 *  Created on: Feb 13, 2025
 *      Author: aa
 */
#include "App/app_core.h"

AppMemory M;

#define USE_LINE_A                                                       \
	do                                                                   \
	{                                                                    \
		HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_RESET); \
		HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_SET);   \
	} while (0)

#define USE_LINE_B                                                       \
	do                                                                   \
	{                                                                    \
		HAL_GPIO_WritePin(LINE_A_GPIO_Port, LINE_A_Pin, GPIO_PIN_RESET); \
		HAL_GPIO_WritePin(LINE_B_GPIO_Port, LINE_B_Pin, GPIO_PIN_SET);   \
	} while (0)

#define RECEIVE_TIMEOUT 300 // ms

UartControl UC = {0};

ScanModeStatus SMStatus = {0};

uint16_t Modbus_CRC16(uint8_t *data, uint16_t length)
{
	uint16_t crc = 0xFFFF; // 초기값

	for (uint16_t i = 0; i < length; i++)
	{
		crc ^= data[i]; // 바이트 XOR
		for (uint8_t j = 0; j < 8; j++)
		{
			if (crc & 0x0001)
			{ // LSB가 1이면 XOR
				crc = (crc >> 1) ^ 0xA001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}
	return crc; // LSB-first 출력
}

void UartScan()
{

	static uint8_t buffer[5];
	uint8_t index = 0;

	uint8_t TargetID = SMStatus.SensorID;

	if (UC.TxReady)
	{

		// ID 범위 체크
		if (TargetID < 1 || TargetID > 254)
		{
			SMStatus.SensorID = 1;
			TargetID = 1;
		}

		// ID 활성화 체크
		if (!(M.SC.Ids[TargetID].id))
		{
			SMStatus.SensorID++;
			return;
		}

		buffer[index++] = SMStatus.SensorID;
		buffer[index++] = 1;					// Type
		SMStatus.Command = buffer[index++] = 0; // ControlCommand
		uint16_t crc16 = Modbus_CRC16(buffer, index);

		buffer[index++] = (crc16 & 0xFF);
		buffer[index++] = (crc16 >> 8);

		HAL_UART_Transmit_IT(&huart1, buffer, sizeof(uint8_t) * 5);
		HAL_UART_Receive_IT(&huart1, SMStatus.RxBuffer, sizeof(uint8_t) * 5);

		UC.TxReady = 0;
		UC.TxSendFlag = 1;
		UC.DataReceived = 0;
		UC.ReceivedCounter = 0;
	}

	// 응답 체크
	if (UC.TxSendFlag && !UC.DataReceived && (UC.ReceivedCounter > RECEIVE_TIMEOUT))
	{

		if (UC.TxRetryCount > 3)
		{
			M.SC.Ids[TargetID].wireFlag = 1;
			// USE_LINE_B;
			//  3회 이상 시도 후 무응답 시 단선 라인 변경 후 통신 시도 해볼 것
		}
		else
		{
			HAL_UART_AbortReceive_IT(&huart1);
			UC.TxRetryCount++;
		}
		UC.TxReady = 1;
	}

	if (UC.TxSendFlag && UC.DataReceived)
	{
		// 수신 성공 값이 유효한지 체크 해야함.

		uint8_t rBuffer[5];
		memcpy(rBuffer, SMStatus.RxBuffer, sizeof(SMStatus.RxBuffer));

		uint16_t rxCrc = Modbus_CRC16(rBuffer, 3);
		uint16_t receivedCrc = rBuffer[3] | (rBuffer[4] << 8);

		if (rxCrc == receivedCrc)
		{
			// CRC 검증 성공
			RxDataFrame RData;
			RData.SlaveID = rBuffer[0];
			RData.Status = rBuffer[1];
			RData.ErrorCode = rBuffer[2];
			RData.crc16 = receivedCrc;
			// 상태 체크 후 다음 ID로 건너가기
			// 데이터를 넘겨주기만해
			if (!RData.Status)
			{
				// 상태가 0일시 FireFlag ON
				M.SC.Ids[RData.SlaveID].fireFlag = 1;
				M.SC.Counter++;
			}
			// 에러 코드 체크 필요
		}
		else
		{
			// CRC Error 송신
		}

		SMStatus.SensorID++;
		UC.TxSendFlag = 0;
		UC.DataReceived = 0;
		UC.TxReady = 1;
	}
}

void StatusScan()
{
	static uint8_t activeIDs[250];
	static uint8_t activeCount = 0;
	static uint8_t currentIdx = 0;
	static uint32_t lastUpdateTime = 0;
	static uint32_t lastScanTime = 0;
	static uint8_t TargetID = 0;

	static uint8_t TestId = 0;

	uint32_t currentTime = HAL_GetTick();

	// 🔹 1. 활성화된 ID 목록을 1000ms마다 갱신 (불필요한 연산 방지)
	if (currentTime - lastScanTime > 1000)
	{
		TestId++;
		lastScanTime = currentTime;
		activeCount = 0; // 개수 초기화
		for (uint8_t i = 0; i < 250; i++)
		{
			if (M.SC.Ids[i].fireFlag || M.SC.Ids[i].wireFlag)
			{
				activeIDs[activeCount++] = i;
			}
		}
	}

	if (currentTime - lastUpdateTime > 1000)
	{
		lastUpdateTime = currentTime;

		TargetID = activeIDs[currentIdx];
		// uint8_t FFlag = M.SC.Ids[TargetID].fireFlag;
		// uint8_t WFlag = M.SC.Ids[TargetID].wireFlag;

		// FND_Display();

		currentIdx = (currentIdx + 1) % activeCount;
	}

	FND_Display(TestId);
}

void ScanMode()
{

	/*
		기본 동작모드
		메모리에 등록된 ID를 가지고 순차적으로 통신을 시도
	*/
	// UART Scanning
	UartScan();

	// Status Scanning
	StatusScan();
}

void InputMode()
{

	/*
		Mode 버튼 입력 시 변경
		센서를 통신 포트에 연결 후 ID를 주입하기 위한 모드
		ID를 주입 후 확인 메시지를 받아야함 안올시 100ms 대기 후 3번 통신 시도
		세번 다 실패시 에러 표시
		실패 조건 - 통신 무응답, 주입 ID와 다른 ID 수신

		주입 성공 시 해당 ID 메모리에 저장

		메모리 확인 후 이미 입력된 ID는 제외 후 제일 낮은 숫자부터 표기 1부터 99까지 가능

		동작 순서
		ID 메모리를 전부를 읽어야 하나 비어있는 숫자
	*/
}

void TestMode()
{

	/*
		미정
	*/
}

void MemoryMode()
{

	/*
		저장된 ID 수정 또는 삭제 등등 예정
	*/
}

uint8_t TestId = 0;
uint32_t lastFNDTime = 0;
uint32_t FndcurrentTime = 0;


// Main Function
void AppCore(void)
{

	uint8_t arr[5] = {1, 2, 3, 4, 5};

	uint8_t GPIO_FLAG = 0;
	HAL_Delay(5000);
	GPIO_FLAG = SwitchModeSelector();

	SWDIO_To_GPIO(GPIO_FLAG);

	/* Init Start */
	USE_LINE_A;
	UART_Init();

	/* 초기 진입 시 메모리에서 ID 읽어오기 */
	/* CRC 오류면 다시 읽어보고 3번 오류면 알람 발생? */

	M.SC.Ids[1].id = 1;
	M.SC.Ids[2].id = 2;
	M.SC.Ids[3].id = 3;
	M.SC.Ids[4].id = 4;
	M.SC.Counter = 4;

	M.PP.ModePosition = 1;
	/* Init End*/

	ledOff();

	for (;;)
	{

		switch (M.PP.ModePosition)
		{
		case NONE:
			// Nothing
			break;
		case SCAN:
			// ScanMode();
			FndcurrentTime = HAL_GetTick();

			// 🔹 1. 활성화된 ID 목록을 1000ms마다 갱신 (불필요한 연산 방지)
			if (FndcurrentTime - lastFNDTime > 1000)
			{
				lastFNDTime = FndcurrentTime;
				TestId++;
			}
			FND_Display(TestId);

			if (!UartDelayCount)
			{
				HAL_UART_Transmit_IT(&huart1, arr, 5);
				UartDelayCount = 5000;
			}

			break;
		case INPUT:
			InputMode();
			break;
		case TEST:
			TestMode();
			break;
		case MEMORY:
			MemoryMode();
			break;
		default:
			break;
		}
	}
}
