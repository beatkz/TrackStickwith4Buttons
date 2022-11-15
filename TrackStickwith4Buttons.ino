#include "Mouse.h"
#include "Keyboard.h"
const int PIN_X = A0;

const int PIN_Y = A1;
//const int D_PIN_OBJ[] = {2, 3, 4, 6, 9, 12}; //for Arduino Micro
const int D_PIN_OBJ[] = { 7, 6, 5, 4, 3, 2 };  //for Arduino Leonardo

// Keyboard Wait Time in milliseconds
const int MS_WAIT = 200;

const int CENTER_RANGE = 50;

int relCfromVolval(int volval) {
  int relC = volval - 512;
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

void setup() {
  for (int i = 0; i <= 5; i++) {
    pinMode(D_PIN_OBJ[i], INPUT_PULLUP);
  }
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  int valX = analogRead(PIN_X);
  int valY = analogRead(PIN_Y);
  int relX = relCfromVolval(valX);
  int relY = -(relCfromVolval(valY));

  Mouse.move(mouseVelfromRelC(relX), mouseVelfromRelC(relY), 0);

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