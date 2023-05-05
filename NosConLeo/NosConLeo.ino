//for debugging, please rewrite to true
const bool DEBUG_MODE = false;

//Uncomment a board you want to use:
//#define ARDUINO_LEO
//#define ARDUINO_UNO
#define AE_RP2040

#ifdef ARDUINO_LEO
//for Arduino Leonardo
const int BUTTONS = 16;
const int STAT_LED = 13;
const int D_PIN_OBJ[] = {
  2, 3, 4, 5, 6, 7, 8, 9,
  10, 11, 12, 13, 18, 19, 20, 21
};
#endif

#ifdef ARDUINO_UNO
//for Arduino Uno
const int BUTTONS = 16;
const int STAT_LED = 13;
const int D_PIN_OBJ[] = {
  2, 3, 4, 5, 6, 7, 8, 9,
  10, 11, 12, 18, 17, 16, 15, 14
};
#endif


#ifdef AE_RP2040
//Actual Pin No for Pi Pico -> Stick: 21,31,32 col:11,10,9 row:7,6,5,4
//Please use with Arduino-Pico(https://github.com/earlephilhower/arduino-pico)
const int BUTTONS = 25;
const int STAT_LED = 25;
const int D_PIN_OBJ[] = {
  15, 14, 13, 12, 11, 10, 9, 8,
  7, 6, 5, 4, 3, 2, 16,
  17, 18, 19, 20, 21, 22,
  23, 24, 26, 28
};
#endif

int pushStat[BUTTONS];
int prevStat[BUTTONS];
bool velSwPressed;
const unsigned char NOTE_MAP[] = {
  0x24, 0x26, 0x28, 0x29, 0x2b, 0x2d, 0x2f,
  0x30, 0x32, 0x34, 0x35, 0x37, 0x39, 0x3b,
  0x3c, 0x3e, 0x40, 0x41, 0x43, 0x45, 0x47,
  0x48, 0x4a, 0x4c
};

void scanStats() {
  const int MAX_CH = BUTTONS;
  for (int ch = 0; ch < MAX_CH; ch++) {
    pushStat[ch] = digitalRead(D_PIN_OBJ[ch]);
  }
}

void dumpStates() {
  //for debug
  scanStats();

  String dumpStat;
  dumpStat = "";
  for (int i = 0; i < BUTTONS; i++) {
    dumpStat += pushStat[i];
    dumpStat += " ";
  }
  Serial.println(dumpStat);
  delay(1000);
}

void setup() {
  for (int i = 0; i < BUTTONS; i++) {
    pinMode(D_PIN_OBJ[i], INPUT_PULLUP);
    pushStat[i] = LOW;
    prevStat[i] = LOW;
  }

  if (DEBUG_MODE) {
    Serial.begin(115200);
  } else {
    Serial.begin(115200);
    velSwPressed = false;
    pinMode(STAT_LED, OUTPUT);
  }
}

void loop() {
  if (DEBUG_MODE) {
    dumpStates();
  } else {
    actionMIDI();
  }
}

void actionMIDI() {
  const int MAX_CH = BUTTONS;

  for (int ch = 0; ch < MAX_CH; ch++) {
    pushStat[ch] = digitalRead(D_PIN_OBJ[ch]);
    if (pushStat[ch] != prevStat[ch]) {
      if (pushStat[ch] == HIGH) {
        if (ch == 0) {
          velSwPressed = false;
          digitalWrite(STAT_LED, LOW);
        } else {
          NoteOff(NOTE_MAP[ch - 1]);
        }
      } else {
        if (ch == 0) {
          velSwPressed = true;
          digitalWrite(STAT_LED, HIGH);
        } else {
          NoteOn(NOTE_MAP[ch - 1], velSwPressed);
        }
      }
      prevStat[ch] = pushStat[ch];
    }
  }
}

void NoteOn(unsigned char noteno, bool velSwPressed) {
  if (velSwPressed) {
    Serial.write(0x90); Serial.write(noteno); Serial.write(0x7f);
  } else {
    Serial.write(0x90); Serial.write(noteno); Serial.write(0x40);
  }
}

void NoteOff(unsigned char noteno) {
  Serial.write(0x80); Serial.write(noteno); Serial.write((byte)0x00);
}
