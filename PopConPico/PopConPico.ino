#include "Joystick.h"
#include "Keyboard.h"
//for debugging, please rewrite to true
const bool DEBUG_MODE = false;

//Uncomment a board you want to use:

//for Pro Micro RP2040 -> Pin 9,8,7,6,5,21,23,20,22,26
//Please use with Arduino-Pico(https://github.com/earlephilhower/arduino-pico)
const int STAT_LED = 25;
const int D_PIN_OBJ[] = { 9, 8, 7, 6, 5, 21, 23, 20, 22, 26 };

//for Adafruit Feather RP2040
/*const int STAT_LED = 13;
const int D_PIN_OBJ[] = { 2, 3, 7, 8, 9, 6, 0, 1, 20, 19 };*/

// Keyboard Wait Time in milliseconds
const int MS_WAIT = 500;
bool QKS_MODE = false;
bool DIVA_MODE = false;

void dumpStates() {
  //for debug
  //Esc,1,2,3,4,5,6,7,8,9
  int stats[10] = {
    digitalRead(D_PIN_OBJ[0]),
    digitalRead(D_PIN_OBJ[1]), digitalRead(D_PIN_OBJ[2]), digitalRead(D_PIN_OBJ[3]),
    digitalRead(D_PIN_OBJ[4]), digitalRead(D_PIN_OBJ[5]), digitalRead(D_PIN_OBJ[6]),
    digitalRead(D_PIN_OBJ[7]), digitalRead(D_PIN_OBJ[8]), digitalRead(D_PIN_OBJ[9])
  };

  String dumpStat = "";
  for (int i = 0; i < 10; i++) {
    dumpStat += stats[i];
    if (i != 9) {
      dumpStat += ",";
    }
  }
  Serial.println(dumpStat);
  delay(1000);
}

void actionJoyBtn(int D_PIN_NUM, int JoyBtn) {
  if (digitalRead(D_PIN_NUM) == LOW) {
    Joystick.button(JoyBtn, true);
  } else {
    Joystick.button(JoyBtn, false);
  }
}

void actionKBKey(int D_PIN_NUM, char key) {
  if (digitalRead(D_PIN_NUM) == LOW) {
    Keyboard.press(key);
  } else {
    Keyboard.release(key);
  }
}

// for Pop'n Lively
void PopnMode() {
  if (digitalRead(D_PIN_OBJ[0]) == LOW) {
    actionKBKey(D_PIN_OBJ[1], '1');
    actionKBKey(D_PIN_OBJ[2], '2');
    actionKBKey(D_PIN_OBJ[3], '3');
    actionKBKey(D_PIN_OBJ[4], '4');
    actionKBKey(D_PIN_OBJ[5], '5');
    actionKBKey(D_PIN_OBJ[6], '6');
    actionKBKey(D_PIN_OBJ[7], '0');
    actionKBKey(D_PIN_OBJ[8], KEY_BACKSPACE);
    actionKBKey(D_PIN_OBJ[9], KEY_ESC);
  } else {
    // Button1-9
    actionJoyBtn(D_PIN_OBJ[1], 1);
    actionJoyBtn(D_PIN_OBJ[2], 2);
    actionJoyBtn(D_PIN_OBJ[3], 3);
    actionJoyBtn(D_PIN_OBJ[4], 4);
    actionJoyBtn(D_PIN_OBJ[5], 5);
    actionJoyBtn(D_PIN_OBJ[6], 6);
    actionJoyBtn(D_PIN_OBJ[7], 7);
    actionJoyBtn(D_PIN_OBJ[8], 8);
    actionJoyBtn(D_PIN_OBJ[9], 9);
  }
}

// for DIVA Mega39's+
// Green Button + Plug
void DIVAMode() {
  if (digitalRead(D_PIN_OBJ[0]) == LOW) {
    actionKBKey(D_PIN_OBJ[1], 'R');
    actionKBKey(D_PIN_OBJ[2], KEY_UP_ARROW);
    actionKBKey(D_PIN_OBJ[3], KEY_LEFT_ARROW);
    actionKBKey(D_PIN_OBJ[4], 'Q');
    actionKBKey(D_PIN_OBJ[5], KEY_RETURN);
    actionKBKey(D_PIN_OBJ[6], 'E');
    actionKBKey(D_PIN_OBJ[7], KEY_RIGHT_ARROW);
    actionKBKey(D_PIN_OBJ[8], KEY_DOWN_ARROW);
    actionKBKey(D_PIN_OBJ[9], KEY_ESC);
  } else {
    // Button1-9
    actionJoyBtn(D_PIN_OBJ[1], 1);
    actionJoyBtn(D_PIN_OBJ[2], 2);
    actionJoyBtn(D_PIN_OBJ[3], 3);
    //actionJoyBtn(D_PIN_OBJ[4], 4);
    //actionJoyBtn(D_PIN_OBJ[5], 5);
    //actionJoyBtn(D_PIN_OBJ[6], 6);
    actionJoyBtn(D_PIN_OBJ[7], 4);
    actionJoyBtn(D_PIN_OBJ[8], 5);
    actionJoyBtn(D_PIN_OBJ[9], 6);
  }
}

// for QuizKnock STADIUM
// Red Button + Plug
void QKSMode() {
  if (digitalRead(D_PIN_OBJ[0]) == LOW) {
    actionKBKey(D_PIN_OBJ[5], 'g');
    actionKBKey(D_PIN_OBJ[2], 'q');
    actionKBKey(D_PIN_OBJ[4], 'w');
    actionKBKey(D_PIN_OBJ[6], 'e');
    actionKBKey(D_PIN_OBJ[8], 'r');
    actionKBKey(D_PIN_OBJ[1], 'a');
    actionKBKey(D_PIN_OBJ[3], 's');
    actionKBKey(D_PIN_OBJ[7], 'd');
    actionKBKey(D_PIN_OBJ[9], 'f');
  } else {
    actionKBKey(D_PIN_OBJ[5], KEY_RETURN);
    actionKBKey(D_PIN_OBJ[2], '1');
    actionKBKey(D_PIN_OBJ[4], '2');
    actionKBKey(D_PIN_OBJ[6], '3');
    actionKBKey(D_PIN_OBJ[8], '4');
    actionKBKey(D_PIN_OBJ[1], '5');
    actionKBKey(D_PIN_OBJ[3], '6');
    actionKBKey(D_PIN_OBJ[7], 'x');
    actionKBKey(D_PIN_OBJ[9], 'c');
  }
}

void setup() {
  for (int i = 0; i <= 9; i++) {
    pinMode(D_PIN_OBJ[i], INPUT_PULLUP);
  }

  if (DEBUG_MODE) {
    Serial.begin(9600);
  } else {
    pinMode(STAT_LED, OUTPUT);
    if (digitalRead(D_PIN_OBJ[5]) == LOW) {
      digitalWrite(STAT_LED, HIGH);
      QKS_MODE = true;
      Keyboard.begin();
    } else if (digitalRead(D_PIN_OBJ[3]) == LOW
               || digitalRead(D_PIN_OBJ[7]) == LOW) {
      digitalWrite(STAT_LED, HIGH);
      DIVA_MODE = true;
      Keyboard.begin();
      Joystick.begin();
    } else {
      Keyboard.begin();
      Joystick.begin();
    }
  }
}

void loop() {
  if (DEBUG_MODE) {
    dumpStates();
  } else {
    if (QKS_MODE) {
      QKSMode();
    } else if (DIVA_MODE) {
      DIVAMode();
    } else {
      PopnMode();
    }
    delay(16);
  }
}