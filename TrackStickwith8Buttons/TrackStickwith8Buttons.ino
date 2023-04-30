#include "Mouse.h"
#include "Keyboard.h"
//for debugging, please rewrite to true
const bool DEBUG_MODE = false;

//Uncomment a board you want to use:
#define ARDUINO_LEO
//#define RPPICO_RP2040

#ifdef ARDUINO_LEO
  //for Arduino Leonardo
  const int STAT_LED = 13;
  const int D_PIN_OBJ[] = { 7 };
  const String STICK_ORIENTATION = "portrait";
#endif

#ifdef RPPICO_RP2040
//Actual Pin No for Pi Pico -> Stick: 21,31,32 col:11,10,9 row:7,6,5,4
//Please use with Arduino-Pico(https://github.com/earlephilhower/arduino-pico)
const int STAT_LED = 25;
const int D_PIN_OBJ[] = { 16 };
const String STICK_ORIENTATION = "landscape";
#endif

const int PIN_X = A0;  // Pi Pico -> Pin31
const int PIN_Y = A1;  // Pi Pico -> Pin32
const int ROWS = 3;
const int ROW_PIN[ROWS] = {9, 8, 7};
const int COLS = 5;
const int COL_PIN[COLS] = {6, 5, 4, 3, 2};
const int PAGES = 3;

int page;
int maxpage;

bool stats2D[ROWS][COLS];
bool preStats2D[ROWS][COLS];

char keymaps[PAGES][ROWS][COLS] = {
  {
    //page 0
    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'},
    {'9', '0', 'x', 'c'}
  },
  {
    //page 1
    {'q', 'w', 'e', 'r'},
    {'a', 's', 'd', 'f'},
    {KEY_BACKSPACE, 'g', 'x', 'c'}
  },
  {
    //page 2
    {KEY_BACKSPACE, '7', '8', '9'},
    {KEY_RETURN, '4', '5', '6'},
    {'0', '1', '2', '3'}
  }
};

// Keyboard Wait Time in milliseconds
const int MS_WAIT = 100;
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

void scanStats2D() {
  for (int i = 0; i < ROWS; i++) {
    digitalWrite(ROW_PIN[i], LOW);
    for (int j = 0; j < COLS; j++) {
      stats2D[i][j] = digitalRead(COL_PIN[j]);
      if (!DEBUG_MODE
          && !(j == 0)
          && (stats2D[i][j] != preStats2D[i][j])) {
        if (stats2D[i][j] == LOW) {
          Keyboard.press(keymaps[page][i][j - 1]);
        } else {
          Keyboard.release(keymaps[page][i][j - 1]);
        }
        preStats2D[i][j] = stats2D[i][j];
      }
    }
    digitalWrite(ROW_PIN[i], HIGH);
  }
}

void dumpStates(int stX, int stY) {
  //for debug
  //stX,stY,Ent,LClk,1,2,3,4,5,6,7,8
  scanStats2D();
  int stats[ROWS + 1][COLS] = {
    {stX, stY, digitalRead(D_PIN_OBJ[0]), -1, -1},
    {stats2D[0][0], stats2D[0][1], stats2D[0][2], stats2D[0][3], stats2D[0][4]},
    {stats2D[1][0], stats2D[1][1], stats2D[1][2], stats2D[1][3], stats2D[1][4]},
    {stats2D[2][0], stats2D[2][1], stats2D[2][2], stats2D[2][3], stats2D[2][4]}
  };

  String dumpStat;
  for (int i = 0; i < 4; i++) {
    dumpStat = "";
    for (int j = 0; j < COLS; j++) {
      dumpStat += stats[i][j];
      dumpStat += " ";
    }
    Serial.println(dumpStat);
  }
  delay(1000);
}

void actionClick(int relX, int relY) {
  scanStats2D();
  if (digitalRead(D_PIN_OBJ[0]) == LOW || stats2D[0][0] == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else if (Mouse.isPressed(MOUSE_LEFT)) {
    Mouse.release(MOUSE_LEFT);
  }
  actionHID(relX, relY);
}

void actionEnter(int relX, int relY) {
  scanStats2D();
  if (digitalRead(D_PIN_OBJ[0]) == LOW) {
    Keyboard.write(KEY_RETURN);
    delay(MS_WAIT);
  }

  if (stats2D[0][0] == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  } else if (Mouse.isPressed(MOUSE_LEFT)) {
    Mouse.release(MOUSE_LEFT);
  }

  actionHID(relX, relY);
}

void changePage() {
  if (stats2D[1][0] == LOW) {
    if (page == maxpage) {
      page = 0;
    } else {
      page++;
    }
    blinkLED(page);
    delay(MS_WAIT);
  } else if (stats2D[2][0] == LOW) {
    if (page == 0) {
      page = maxpage;
    } else {
      page--;
    }
    blinkLED(page);
    delay(MS_WAIT);
  }
}

void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(STAT_LED, LOW);
    delay(50);
    digitalWrite(STAT_LED, HIGH);
    delay(50);
  }
  if (times == 0) {
    digitalWrite(STAT_LED, LOW);
  }
}

void actionHID(int relX, int relY) {
  if (abs(relX) > CENTER_RANGE || abs(relY) > CENTER_RANGE) {
    Mouse.move(mouseVelfromRelC(relX), mouseVelfromRelC(relY), 0);
  }
  changePage();

  delay(16);
}

void initStats() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      stats2D[i][j] = HIGH;
      preStats2D[i][j] = HIGH;
    }
    digitalWrite(ROW_PIN[i], HIGH);
  }
}

void setup() {
  for (int i = 0; i < ROWS; i++) {
    pinMode(ROW_PIN[i], OUTPUT);
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(COL_PIN[i], INPUT_PULLUP);
  }

  initStats();

  if (DEBUG_MODE) {
    Serial.begin(9600);
  } else {
    pinMode(STAT_LED, OUTPUT);
    if (digitalRead(D_PIN_OBJ[0]) == LOW) {
      ClickMode = true;
      digitalWrite(STAT_LED, HIGH);
    }
    page = 0;
    maxpage = PAGES - 1;
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
