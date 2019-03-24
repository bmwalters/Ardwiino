#include "../config/config.h"
#include "../shared/bootloader/Bootloader.h"
#include "../shared/controller/InputHandler.h"
#include "../shared/controller/output/OutputHandler.h"
#include "../shared/util.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include "pins.h"

InputHandler controller;
OutputHandler out;

int main() {
  out.init();
  controller.init();

  while (true) {
    controller.process();
    out.process(&controller.controller);
  }
}
