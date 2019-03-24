#include "OutputHandler.h"

#if OUTPUT_TYPE == XINPUT
  XInputOutput OutputHandler::output;
#elif OUTPUT_TYPE == GAMEPAD
  GamepadOutput OutputHandler::output;
#elif OUTPUT_TYPE == KEYBOARD
  KeyboardOutput OutputHandler::output;
#endif

void OutputHandler::process(Controller *controller) {
  if (bit_check(controller->buttons, START) &&
      bit_check(controller->buttons, SELECT)) {
    bootloader();
  }
  output.update(*controller);
}

void OutputHandler::init() {
  output.init();
}

extern "C" {
void EVENT_USB_Device_Connect(void) { OutputHandler::output.usb_connect(); }
void EVENT_USB_Device_Disconnect(void) { OutputHandler::output.usb_disconnect(); }
void EVENT_USB_Device_ConfigurationChanged(void) {
  OutputHandler::output.usb_configuration_changed();
}
void EVENT_USB_Device_ControlRequest(void) { OutputHandler::output.usb_control_request(); }
void EVENT_USB_Device_StartOfFrame(void) { OutputHandler::output.usb_start_of_frame(); }
}