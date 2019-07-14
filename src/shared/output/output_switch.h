#pragma once
#include "../util.h"
#include "output_handler.h"
typedef struct {
  uint16_t buttons;
  uint8_t hat;
  uint8_t l_x;
  uint8_t l_y;
  uint8_t r_x;
  uint8_t r_y;
} USB_SwitchReport_Data_t;
void switch_init(event_pointers *events, USB_ClassInfo_HID_Device_t *hid_device);