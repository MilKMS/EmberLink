/*
 * app_SegmentDisplay.c
 *
 *  Created on: Feb 17, 2025
 *      Author: aa
 */

#include "App/app_SegmentDisplay.h"

#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 7

const uint8_t digit_table[10] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111	// 9
};

void scanModeSegDisplay(void)
{
    static uint8_t ledStep = 0;   // LED가 이동하는 단계
    static uint32_t ledTick = 0;  // LED 점등 타이밍
    static uint8_t SegNum = 0;    // 현재 활성화할 세그먼트 인덱스 (0~2)

    static uint8_t SCAN_Mode_Seg[10][3] = {
        {0b10000000, 0b00000000, 0b00000000}, // 1
        {0b00000000, 0b10000000, 0b00000000}, // 2
        {0b00000000, 0b00000000, 0b10000000}, // 3
        {0b00000000, 0b00000000, 0b01000000}, // 4
        {0b00000000, 0b00000000, 0b00100000}, // 5
        {0b00000000, 0b00000000, 0b00010000}, // 6
        {0b00000000, 0b00010000, 0b00000000}, // 7
        {0b00010000, 0b00000000, 0b00000000}, // 8
        {0b00001000, 0b00000000, 0b00000000}, // 9
        {0b00000100, 0b00000000, 0b00000000}  // 10
    };

    static const uint8_t ledPath[10][2] = {
        {0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}, {2, 3},
        {1, 3}, {0, 3}, {0, 4}, {0, 5}
    };

    // 세그먼트 출력 핀 배열
    const uint16_t SEG_PINS[8] = {SEG_A_Pin, SEG_B_Pin, SEG_C_Pin, SEG_D_Pin, 
                                  SEG_E_Pin, SEG_F_Pin, SEG_G_Pin, SEG_DP_Pin};
    GPIO_TypeDef* SEG_PORTS[8] = {SEG_A_GPIO_Port, SEG_B_GPIO_Port, SEG_C_GPIO_Port, SEG_D_GPIO_Port, 
                                   SEG_E_GPIO_Port, SEG_F_GPIO_Port, SEG_G_GPIO_Port, SEG_DP_GPIO_Port};

    // 트랜지스터 제어 핀 배열 (세그먼트 위치 선택)
    const uint16_t SEG_TR_PINS[3] = {SEG_TR_1_Pin, SEG_TR_2_Pin, SEG_TR_3_Pin};
    GPIO_TypeDef* SEG_TR_PORTS[3] = {SEG_TR_1_GPIO_Port, SEG_TR_2_GPIO_Port, SEG_TR_3_GPIO_Port};

    // === [1] FND 내부 LED 순환 점등 ===
    if (HAL_GetTick() - ledTick >= 300) { // 300ms마다 LED 이동
        ledTick = HAL_GetTick();
        ledStep = (ledStep + 1) % 10; // 순환 이동
    }

    // 현재 점등할 FND 위치 & LED
    uint8_t targetSeg = ledPath[ledStep][0]; // 세그먼트 위치 (0:1번, 1:2번, 2:3번)

    // === [2] FND 디스플레이 스캔 ===
    
    // **모든 FND OFF (이전 값 제거)**
    for (uint8_t i = 0; i < 3; i++) {
        HAL_GPIO_WritePin(SEG_TR_PORTS[i], SEG_TR_PINS[i], GPIO_PIN_RESET);
    }
    for (uint8_t i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(SEG_PORTS[i], SEG_PINS[i], GPIO_PIN_RESET);
    }
    
    // **현재 점등할 FND만 선택**
    uint8_t segValue = SCAN_Mode_Seg[ledStep][targetSeg]; // 현재 점등할 FND의 LED 데이터

    // 선택된 세그먼트에 대해서만 점등
    for (uint8_t i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(SEG_PORTS[i], SEG_PINS[i], (segValue >> (7 - i)) & 1);
    }

    // 선택된 FND의 트랜지스터 ON
    HAL_GPIO_WritePin(SEG_TR_PORTS[targetSeg], SEG_TR_PINS[targetSeg], GPIO_PIN_SET);

}



/*
void scanModeSegDisplay(uint8_t Pos, uint8_t SegNum)
{

	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_A]);
	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_B]);
	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_C]);
	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_D]);
	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_E]);
	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_F]);
	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_G]);
	HAL_GPIO_WritePin(SEG_DP_GPIO_Port, SEG_DP_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_DP]);

	switch (SegNum)
	{
	case 0:
		HAL_GPIO_WritePin(SEG_TR_1_GPIO_Port, SEG_TR_1_Pin, 1);
		HAL_GPIO_WritePin(SEG_TR_2_GPIO_Port, SEG_TR_2_Pin, 0);
		HAL_GPIO_WritePin(SEG_TR_3_GPIO_Port, SEG_TR_3_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(SEG_TR_1_GPIO_Port, SEG_TR_1_Pin, 0);
		HAL_GPIO_WritePin(SEG_TR_2_GPIO_Port, SEG_TR_2_Pin, 1);
		HAL_GPIO_WritePin(SEG_TR_3_GPIO_Port, SEG_TR_3_Pin, 0);
		break;
	case 2:
		HAL_GPIO_WritePin(SEG_TR_1_GPIO_Port, SEG_TR_1_Pin, 0);
		HAL_GPIO_WritePin(SEG_TR_2_GPIO_Port, SEG_TR_2_Pin, 0);
		HAL_GPIO_WritePin(SEG_TR_3_GPIO_Port, SEG_TR_3_Pin, 1);
		break;
	default:
		HAL_GPIO_WritePin(SEG_TR_1_GPIO_Port, SEG_TR_1_Pin, 0);
		HAL_GPIO_WritePin(SEG_TR_2_GPIO_Port, SEG_TR_2_Pin, 0);
		HAL_GPIO_WritePin(SEG_TR_3_GPIO_Port, SEG_TR_3_Pin, 0);
		break;
	}
}
*/

// ✅ GPIO 핀을 설정하는 함수 추가
void SetFNDOutput(uint8_t pattern) {
    HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, pattern & 0b1);
    HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, (pattern >> 1) & 0b1);
    HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, (pattern >> 2) & 0b1);
    HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, (pattern >> 3) & 0b1);
    HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, (pattern >> 4) & 0b1);
    HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, (pattern >> 5) & 0b1);
    HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, (pattern >> 6) & 0b1);
    HAL_GPIO_WritePin(SEG_DP_GPIO_Port, SEG_DP_Pin, (pattern >> 7) & 0b1);
}

void FND_Display(uint8_t DisplayNum) {
	uint8_t digits[3];

	digits[0] = DisplayNum / 100;
	digits[1] = (DisplayNum % 100) / 10;
	digits[2] = DisplayNum % 10;

	// 현재 표시할 자리
    uint8_t value = digits[SegTrPos - 1];  
    uint8_t pattern = digit_table[value];  // 현재 자리 숫자의 7세그먼트 패턴

	// 🔹 GPIO 핀 출력 설정을 함수화하여 반복 줄이기
    SetFNDOutput(pattern);

	// 🔹 FND 자리 선택
    HAL_GPIO_WritePin(SEG_TR_1_GPIO_Port, SEG_TR_1_Pin, (SegTrPos == 1) ? 1 : 0);
    HAL_GPIO_WritePin(SEG_TR_2_GPIO_Port, SEG_TR_2_Pin, (SegTrPos == 2) ? 1 : 0);
    HAL_GPIO_WritePin(SEG_TR_3_GPIO_Port, SEG_TR_3_Pin, (SegTrPos == 3) ? 1 : 0);
	
	return;
}

void FndFireAndWireDisplay(uint8_t DisplayNum, uint8_t FireFlag, uint8_t WireFlag) {
	uint8_t digits[3];

	digits[0] = DisplayNum / 100;
	digits[1] = (DisplayNum % 100) / 10;
	digits[2] = DisplayNum % 10;

	// 현재 표시할 자리
    uint8_t value = digits[SegTrPos - 1];  
    uint8_t pattern = digit_table[value];  // 현재 자리 숫자의 7세그먼트 패턴

	// 🔹 GPIO 핀 출력 설정을 함수화하여 반복 줄이기
    SetFNDOutput(pattern);

	// 🔹 FND 자리 선택
    HAL_GPIO_WritePin(SEG_TR_1_GPIO_Port, SEG_TR_1_Pin, (SegTrPos == 1) ? 1 : 0);
    HAL_GPIO_WritePin(SEG_TR_2_GPIO_Port, SEG_TR_2_Pin, (SegTrPos == 2) ? 1 : 0);
    HAL_GPIO_WritePin(SEG_TR_3_GPIO_Port, SEG_TR_3_Pin, (SegTrPos == 3) ? 1 : 0);
	
	return;
}