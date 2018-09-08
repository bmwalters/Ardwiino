#include "WiiExtension.h"
extern "C" {
  #include "XInputPad.h"
  #include "util.h"
}
void WiiExtension::setup() {
    extension.begin();
    extension.connect();
}
void WiiExtension::read_controller(WiiController* controller) {
    boolean success = extension.update();
    if (!success) {
        extension.connect();
        return;
    }
    ExtensionType conType = extension.getConnectedID();

		switch (conType) {
        case(ExtensionType::DJTurntableController):
        break;
	      case(ExtensionType::Nunchuk):
            bit_write(nchuk.buttonC(), controller->digital_buttons_2, XBOX_A);
            bit_write(nchuk.buttonZ(), controller->digital_buttons_2, XBOX_B);
            controller->l_x = (nchuk.joyX() - 128) * 256;
            controller->l_y = (nchuk.joyY() - 128) * 256;
            controller->r_x = (nchuk.rollAngle()) * 182;
            controller->r_y = (nchuk.pitchAngle()) * 182;
		    break;
        case(ExtensionType::DrumController):
            controller->l_x = (drum.joyX()-32)*2048;
            controller->l_y = (drum.joyY()-32)*2048;
            bit_write(drum.drumGreen(), controller->digital_buttons_2, XBOX_A);
            bit_write(drum.drumRed(), controller->digital_buttons_2, XBOX_B);
            bit_write(drum.cymbalYellow(), controller->digital_buttons_2, XBOX_Y);
            bit_write(drum.drumBlue(), controller->digital_buttons_2, XBOX_X);
            bit_write(drum.cymbalOrange(), controller->digital_buttons_2, XBOX_LB);
            bit_write(drum.bassPedal(), controller->digital_buttons_2, XBOX_RB);
            bit_write(drum.buttonPlus(), controller->digital_buttons_1, XBOX_START);
            bit_write(drum.buttonMinus(), controller->digital_buttons_1, XBOX_BACK);
        break;
        case(ExtensionType::GuitarController):
            controller->r_y = 0;
            controller->r_x = (guitar.whammyBar()-14)*1024;
            
            if(!digitalRead(4)) {
                controller->r_y = 32767;
            }
            bit_write(guitar.strumUp() || guitar.joyY()>40, controller->digital_buttons_1, XBOX_DPAD_UP);
            bit_write(guitar.strumDown() || guitar.joyY()<20, controller->digital_buttons_1, XBOX_DPAD_DOWN);
            bit_write(guitar.joyX()<20, controller->digital_buttons_1, XBOX_DPAD_LEFT);
            bit_write(guitar.joyX()>40, controller->digital_buttons_1, XBOX_DPAD_RIGHT);
            bit_write(guitar.buttonPlus(), controller->digital_buttons_1, XBOX_START);
            bit_write(guitar.buttonMinus(), controller->digital_buttons_1, XBOX_BACK);
            bit_write(guitar.fretGreen(), controller->digital_buttons_2, XBOX_A);
            bit_write(guitar.fretRed(), controller->digital_buttons_2, XBOX_B);
            bit_write(guitar.fretYellow(), controller->digital_buttons_2, XBOX_Y);
            bit_write(guitar.fretBlue(), controller->digital_buttons_2, XBOX_X);
            bit_write(guitar.fretOrange(), controller->digital_buttons_2, XBOX_LB);
        break;

  			case(ExtensionType::ClassicController):
            controller->l_x = (classic.leftJoyX()-32)*1024;
            controller->l_y = (classic.leftJoyY()-32)*1024;
            controller->r_x = (classic.rightJoyX()-16)*2048;
            controller->r_y = (classic.rightJoyY()-16)*2048;
            controller->lt = (classic.triggerL()-16)*2048;
            controller->rt = (classic.triggerR()-16)*2048;
            bit_write(classic.dpadUp(), controller->digital_buttons_1, XBOX_DPAD_UP);
            bit_write(classic.dpadDown(), controller->digital_buttons_1, XBOX_DPAD_DOWN);
            bit_write(classic.dpadLeft(), controller->digital_buttons_1, XBOX_DPAD_LEFT);
            bit_write(classic.dpadRight(), controller->digital_buttons_1, XBOX_DPAD_RIGHT);
            bit_write(classic.buttonStart(), controller->digital_buttons_1, XBOX_START);
            bit_write(classic.buttonSelect(), controller->digital_buttons_1, XBOX_BACK);
            bit_write(classic.buttonHome(), controller->digital_buttons_2, XBOX_HOME);
            bit_write(classic.buttonA(), controller->digital_buttons_2, XBOX_A);
            bit_write(classic.buttonB(), controller->digital_buttons_2, XBOX_B);
            bit_write(classic.buttonY(), controller->digital_buttons_2, XBOX_Y);
            bit_write(classic.buttonX(), controller->digital_buttons_2, XBOX_X);
            bit_write(classic.buttonZL(), controller->digital_buttons_2, XBOX_LB);
            bit_write(classic.buttonZR(), controller->digital_buttons_2, XBOX_RB);
				break;
			default:
        break;
    }
}