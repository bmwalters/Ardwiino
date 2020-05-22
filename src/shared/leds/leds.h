#pragma once
#include "../input/input_handler.h"
#include "../controller/controller.h"
#include "../config/eeprom.h"
#include "led_colours.h"
#define NUM_LEDS XBOX_BTN_COUNT + XBOX_AXIS_COUNT
void initLEDs(void);
void tickLEDs(Controller_t *controller);