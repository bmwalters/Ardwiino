#include "../../shared/config/eeprom.h"
#include "../../shared/input/input_handler.h"
#include "../../shared/util.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/wdt.h>
#include <stddef.h>
#include <util/delay.h>
#define SERIAL_UBBRVAL(Baud) ((((F_CPU / 16) + (Baud / 2)) / (Baud)) - 1)
size_t controller_index = 0;
controller_t controller;
bool done = false;
int main(void) {
  UBRR0 = 8;
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
  // Notify the usb processor so that it knows we are about to wait for the
  // config
  while (!bit_is_set(UCSR0A, RXC0)) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = 0xFE;
  }
  for (size_t i = 0; i < sizeof(config_t); i++) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    ((uint8_t *)&config)[i] = UDR0;
  }
  config.input_type = WII;
  input_init();
  while (1) {
    input_tick(&controller);
    while (controller_index < sizeof(controller_t) + 2) {
      loop_until_bit_is_set(UCSR0A, UDRE0);
      if (controller_index < 2) {
        UDR0 = controller_index == 0 ? 'm' : 'a';
      } else {
        UDR0 = ((uint8_t *)&controller)[controller_index - 2];
      }
      controller_index++;
    }
    controller_index = 0;
    if (bit_is_set(UCSR0A, RXC0) && UDR0 == 'r') {
      cli();
      wdt_enable(WDTO_15MS);
      for (;;) {}
    }
  }
}