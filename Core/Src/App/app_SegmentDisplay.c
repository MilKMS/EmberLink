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
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111   // 9
};

uint8_t SCAN_Mode_Seg[10][3][8] = {
		/* Binary로 변경 */
		/* A, B, C, D, E, F, G, DP */
		/* 1  2  3  4  5  6  7  8  */
		{{1,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}},//1
		{{0,0,0,0,0,0,0,0}, {1,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}},//2
		{{0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {1,0,0,0,0,0,0,0}},//3
		{{0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,1,0,0,0,0,0,0}},//4
		{{0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,1,0,0,0,0,0}},//5
		{{0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,1,0,0,0,0}},//6
		{{0,0,0,0,0,0,0,0}, {0,0,0,1,0,0,0,0}, {0,0,0,0,0,0,0,0}},//7
		{{0,0,0,1,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}},//8
		{{0,0,0,0,1,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}},//9
		{{0,0,0,0,0,1,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}},//10

};

void scanModeSegDisplay(uint8_t Pos, uint8_t SegNum){

	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_A]);
	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_B]);
	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_C]);
	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_D]);
	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_E]);
	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_F]);
	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_G]);
	HAL_GPIO_WritePin(SEG_DP_GPIO_Port, SEG_DP_Pin, SCAN_Mode_Seg[Pos][SegNum][SEG_DP]);

	switch(SegNum){
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
