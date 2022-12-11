#include "Mouse.h"
#include "Keyboard.h"
//for debugging, please rewrite to true
const bool DEBUG_MODE = false;

//for Arduino and Raspberry Pi Pico
const int PIN_X = A0;  // Pi Pico -> Pin31
const int PIN_Y = A1;  // Pi Pico -> Pin32

//for Arduino Micro
//const int D_PIN_OBJ[] = {2, 3, 4, 6, 9, 12};

//for Arduino Leonardo and Raspberry Pi Pico
//for Pi Pico -> Pin 10,9,7,6,5,4
const int D_PIN_OBJ[] = { 7, 6, 5, 4, 3, 2 };

const String STICK_ORIENTATION = "portrait";
//const String STICK_ORIENTATION = "landscape";

// Keyboard Wait Time in milliseconds
const int MS_WAIT = 500;

const int CENTER_RANGE = 75;

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
  //stX,stY,stPush,W,R,Y,G,B
  int stats[8] = {
    stX, stY,
    digitalRead(D_PIN_OBJ[0]),
    digitalRead(D_PIN_OBJ[1]),
    digitalRead(D_PIN_OBJ[2]),
    digitalRead(D_PIN_OBJ[3]),
    digitalRead(D_PIN_OBJ[4]),
    digitalRead(D_PIN_OBJ[5])
  };

  String dumpStat = "";
  for (int i = 0; i < 8; i++) {
    dumpStat += stats[i];
    if (i != 7) {
      dumpStat += ",";
    }
  }
  Serial.println(dumpStat);
  delay(1000);
}

void actionHID(int relX, int relY) {
  if(abs(relX) > CENTER_RANGE || abs(relY) > CENTER_RANGE){
    Mouse.move(mouseVelfromRelC(relX), mouseVelfromRelC(relY), 0);
  }

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
  }

  delay(16);
}

void setup() {
  for (int i = 0; i <= 5; i++) {
    pinMode(D_PIN_OBJ[i], INPUT_PULLUP);
  }
  if (DEBUG_MODE) {
    Serial.begin(9600);
  } else {
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
    actionHID(relX, relY);
  }
}