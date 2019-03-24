#include "GamepadOutput.h"

#if OUTPUT_TYPE == GAMEPAD

/** Buffer to hold the previously generated HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevGamepadHIDReportBuffer[sizeof(USB_GamepadReport_Data_t)];

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Gamepad_HID_Interface =
    {
        .Config =
            {
                .InterfaceNumber              = INTERFACE_ID_Joystick,
                .ReportINEndpoint             =
                    {
                        .Address              = JOYSTICK_EPADDR,
                        .Size                 = JOYSTICK_EPSIZE,
                        .Banks                = 1,
                    },
                .PrevReportINBuffer           = PrevGamepadHIDReportBuffer,
                .PrevReportINBufferSize       = sizeof(PrevGamepadHIDReportBuffer),
            },
    };

uint16_t last_controller_buttons = 0;

GamepadOutput::GamepadOutput() {}

void GamepadOutput::init() {
  wdt_enable(WDTO_2S);
  USB_Init();
  sei();
}

void GamepadOutput::update(Controller controller) {
  USB_USBTask();
  wdt_reset();

  // grab button state from controller
  last_controller_buttons = controller.buttons;
  if (controller.r_x < -8000) {
    bit_set(last_controller_buttons, K_WHAMMY);
  }
  if (controller.r_y == 32767) {
    bit_set(last_controller_buttons, SELECT);
  }

  HID_Device_USBTask(&Gamepad_HID_Interface);
}

void GamepadOutput::usb_connect() {
  // IO::digitalWrite(PIN_DPAD_LED, 0);
  // IO::digitalWrite(PIN_BOARD_LED, 1);
}

void GamepadOutput::usb_disconnect() {
  // IO::digitalWrite(PIN_DPAD_LED, 1);
  // IO::digitalWrite(PIN_BOARD_LED, 0);
}

void GamepadOutput::usb_configuration_changed() {
  bool ConfigSuccess = true;
  ConfigSuccess &= HID_Device_ConfigureEndpoints(&Gamepad_HID_Interface);
  USB_Device_EnableSOFEvents();
  // IO::digitalWrite(PIN_BOARD_LED, configSuccess ? 0 : 1);
}

void GamepadOutput::usb_control_request() {
  HID_Device_ProcessControlRequest(&Gamepad_HID_Interface);
}

void GamepadOutput::usb_start_of_frame() {
  HID_Device_MillisecondElapsed(&Gamepad_HID_Interface);
}

bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, uint8_t *const ReportID,
    const uint8_t ReportType, void *ReportData, uint16_t *const ReportSize) {

  USB_GamepadReport_Data_t* JoystickReport = (USB_GamepadReport_Data_t*)ReportData;

  // update report
  JoystickReport->Button = last_controller_buttons;

  *ReportSize = sizeof(USB_GamepadReport_Data_t);

  return false;
}

void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo, const uint8_t ReportID,
    const uint8_t ReportType, const void *ReportData,
    const uint16_t ReportSize) {
  // Unused (but mandatory for the HID class driver) in this class, since there are no Host->Device reports
}

#endif
