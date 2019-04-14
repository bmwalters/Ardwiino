#include "InputHandler.h"
void InputHandler::process() {
  input.read_controller(&controller);
  processTilt();
}
void InputHandler::init() {
  input.init();
#if TILT_SENSOR == GRAVITY
  IO::pinMode(PIN_GRAVITY, INPUT_PULLUP);
  IO::enableADC();
#endif
}

void InputHandler::processTilt() {
  controller.r_y = IO::digitalRead(PIN_GRAVITY) * 32767;
}