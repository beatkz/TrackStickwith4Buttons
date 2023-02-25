#include "Mouse.h"
#include "Keyboard.h"
//for debugging, please rewrite to true
const bool DEBUG_MODE = false;

//Uncomment a board you want to use:

/*
//for Arduino Leonardo
const int PIN_X = A0;  // Pi Pico -> Pin31
const int PIN_Y = A1;  // Pi Pico -> Pin32
const int STAT_LED = 13;
const int D_PIN_OBJ[] = { 7, 6, 5, 4, 3, 2, 11, 10, 9, 8 };
const String STICK_ORIENTATION = "portrait";
*/

//for Pi Pico -> Pin 21,22,17,16,15,14,24,25,26,27
//Please use with Arduino-Pico(https://github.com/earlephilhower/arduino-pico)
const int PIN_X = A0;  // Pi Pico -> Pin31
const int PIN_Y = A1;  // Pi Pico -> Pin32
const int STAT_LED = 25;
const int D_PIN_OBJ[] = { 16, 17, 13, 12, 11, 10, 18, 19, 20, 21 };
const String STICK_ORIENTATION = "landscape";

// Keyboard Wait Time in milliseconds
const int MS_WAIT = 500;
const int CENTER_RANGE = 75;
bool ClickMode = false;

int relCfromVolval(int volval) {
  int relC = volval - 500;
  if (abs(relC) < CENTER_RANGE) {
    return 0;
  } else {
    return relC;
  }
}

int mouseVelfromRelC(int relC) {
  const int SLOW_RANGE = 128;
  const int MID_RANGE = 192;
  const int HIGH_RANGE = 256;
  const int baseVel = 4;
  int mouseVel = 0;
  int absC = abs(relC);

  if (absC > CENTER_RANGE && absC <= SLOW_RANGE) {
    mouseVel = baseVel;
  } else if (absC > SLOW_RANGE && absC <= MID_RANGE) {
    mouseVel = baseVel * 2;
  } else if (absC > MID_RANGE && absC <= HIGH_RANGE) {
    mouseVel = baseVel * 3;
  } else if (absC > HIGH_RANGE) {
    mouseVel = baseVel * 4;
  }

  if (relC < 0) {
    return -(mouseVel);
  } else {
    return mouseVel;
  }
}

void dumpStates(int stX, int stY) {
  //for debug
  //stX,stY,Ent,LClk,1,2,3,4,5,6,7,8
  int stats[12] = {
    stX, stY, digitalRead(D_PIN_OBJ[0]), digitalRead(D_PIN_OBJ[1]),
    digitalRead(D_PIN_OBJ[2]), digitalRead(D_PIN_OBJ[3]), digitalRead(D_PIN_OBJ[4]), digitalRead(D_PIN_OBJ[5]),
    digitalRead(D_PIN_OBJ[6]), digitalRead(D_PIN_OBJ[7]), digitalRead(D_PIN_OBJ[8]), digitalRead(D_PIN_OBJ[9])
  };

  String dumpStat = "";
  for (int i = 0; i < 12; i++) {
    dumpStat += stats[i];
    if (i != 11) {
      dumpStat += ",";
    }
  }
  Serial.println(dumpStat);
  delay(1000);
}

void actionClick(int relX, int relY) {
  if (digitalRead(D_PIN_OBJ[0]) == LOW
      || digitalRead(D_PIN_OBJ[1]) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else if (Mouse.isPressed(MOUSE_LEFT)) {
    Mouse.release(MOUSE_LEFT);
  }
  actionHID(relX, relY);
}

void actionEnter(int relX, int relY) {
  if (digitalRead(D_PIN_OBJ[0]) == LOW) {
    Keyboard.write(KEY_RETURN);
    delay(MS_WAIT);
  }

  if (digitalRead(D_PIN_OBJ[1]) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else if (Mouse.isPressed(MOUSE_LEFT)) {
    Mouse.release(MOUSE_LEFT);
  }

  actionHID(relX, relY);
}

void actionHID(int relX, int relY) {
  if (abs(relX) > CENTER_RANGE || abs(relY) > CENTER_RANGE) {
    Mouse.move(mouseVelfromRelC(relX), mouseVelfromRelC(relY), 0);
  }

  // KeyPad
  if (digitalRead(D_PIN_OBJ[2]) == LOW) {
    Keyboard.write('1');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[3]) == LOW) {
    Keyboard.write('2');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[4]) == LOW) {
    Keyboard.write('3');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[5]) == LOW) {
    Keyboard.write('4');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[6]) == LOW) {
    Keyboard.write('5');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[7]) == LOW) {
    Keyboard.write('6');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[8]) == LOW) {
    Keyboard.write('7');
    delay(MS_WAIT);
  } else if (digitalRead(D_PIN_OBJ[9]) == LOW) {
    Keyboard.write('8');
    delay(MS_WAIT);
  }
  delay(16);
}

void setup() {
  for (int i = 0; i <= 9; i++) {
    pinMode(D_PIN_OBJ[i], INPUT_PULLUP);
  }

  if (DEBUG_MODE) {
    Serial.begin(9600);
  } else {
    pinMode(STAT_LED, OUTPUT);
    if (digitalRead(D_PIN_OBJ[1]) == LOW) {
      ClickMode = true;
      digitalWrite(STAT_LED, HIGH);
    }
    Mouse.begin();
    Keyboard.begin();
  }
}

void loop() {
  int valX = analogRead(PIN_X);
  int valY = analogRead(PIN_Y);
  int relX = relCfromVolval(valX);
  int relY = relCfromVolval(valY);

  if (STICK_ORIENTATION == "portrait") {
    relY = -relY;
  }

  if (DEBUG_MODE) {
    dumpStates(valX, valY);
  } else {
    if (ClickMode) {
      actionClick(relX, relY);
    } else {
      actionEnter(relX, relY);
    }
  }
}