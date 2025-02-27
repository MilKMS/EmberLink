#ifndef INC_APP_APP_GPIOCONTROL_H_
#define INC_APP_APP_GPIOCONTROL_H_

#include "main.h"
#include "App/app_Interrupt.h"

extern void ledOff();
extern void SWDIO_To_GPIO(uint8_t Flag);
extern uint8_t SwitchModeSelector();
#endif