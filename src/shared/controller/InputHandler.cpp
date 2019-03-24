#include "InputHandler.h"
void InputHandler::process() {
  input.read_controller(&controller);
  // processTilt();
}
void InputHandler::init() {
  input.init();
  // IO::pinMode(PIN_GRAVITY, INPUT);
  // IO::enableADC();
}

void InputHandler::processTilt() {
  // controller.r_y = IO::digitalRead(PIN_GRAVITY) * 32767;
}