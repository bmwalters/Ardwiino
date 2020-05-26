int PIN_B = 5;
int PIN_R = 6;
int PIN_G = 7;
int PIN_Y = 8;
int PIN_O = 9;

int PIN_START = 3;
int PIN_SELECT = 4;

int PIN_STRUMUP = 14;
int PIN_STRUMDOWN = 15;

int PIN_WHAMMY = A0;

int PIN_TILT = 2;

// TXLED0 / TXLED1
int RXLED = 17;

int PIN_POWERSWITCH = 10;
int PIN_POWERLED = 16;

void setup()
{
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output

  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");

  Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
  Serial1.println("Initialize Serial Hardware UART Pins");

  pinMode(PIN_G, INPUT_PULLUP);
  pinMode(PIN_R, INPUT_PULLUP);
  pinMode(PIN_Y, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  pinMode(PIN_O, INPUT_PULLUP);

  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_SELECT, INPUT_PULLUP);

  pinMode(PIN_STRUMUP, INPUT_PULLUP);
  pinMode(PIN_STRUMDOWN, INPUT_PULLUP);
  
  pinMode(PIN_TILT, INPUT_PULLUP);
  
  pinMode(PIN_POWERSWITCH, INPUT_PULLUP);
  pinMode(PIN_POWERLED, OUTPUT);

  digitalWrite(PIN_POWERLED, LOW);
}

void loop()
{
  if (digitalRead(PIN_G) == 0) {
//    Keyboard.write('G');
    Serial.write("g,");
  }
  if (digitalRead(PIN_R) == 0) {
    Serial.write("r,");
  }
  if (digitalRead(PIN_Y) == 0) {
    Serial.write("y,");
  }
  if (digitalRead(PIN_B) == 0) {
    Serial.write("b,");
  }
  if (digitalRead(PIN_O) == 0) {
    Serial.write("o,");
  }
  
  if (digitalRead(PIN_START) == 0) {
    Serial.write("start,");
  }
  if (digitalRead(PIN_SELECT) == 0) {
    Serial.write("select,");
  }
  
  if (digitalRead(PIN_STRUMUP) == 0) {
    Serial.write("strumup,");
  }
  if (digitalRead(PIN_STRUMDOWN) == 0) {
    Serial.write("strumdown,");
  }
  
  if (digitalRead(PIN_TILT) == 0) {
    Serial.write("tilt,");
  }

  /*
  if (digitalRead(PIN_POWERSWITCH) == 0) {
    Serial.write("power,");
    digitalWrite(PIN_POWERLED, LOW);
  } else {
    digitalWrite(PIN_POWERLED, HIGH);
  }
  */

  Serial.print(' ');

  Serial.print("Whammy: ");
  Serial.print(analogRead(PIN_WHAMMY));
  
  Serial.print('\n');

  delay(100);
}
