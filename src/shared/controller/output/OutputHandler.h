#pragma once

#include "../../../config/config.h"
#include "../Controller.h"
#include "../util.h"

#if OUTPUT_TYPE == XINPUT
#include "XInputOutput.h"
#elif OUTPUT_TYPE == GAMEPAD
#include "GamepadOutput.h"
#elif OUTPUT_TYPE == KEYBOARD
#include "KeyboardOutput.h"
#endif

class OutputHandler {
public:
#if OUTPUT_TYPE == XINPUT
  static XInputOutput output;
#elif OUTPUT_TYPE == GAMEPAD
  static GamepadOutput output;
#elif OUTPUT_TYPE == KEYBOARD
  static KeyboardOutput output;
#endif
  void process(Controller *controller);
  void init();
};

extern "C" {
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);
}
