#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "EPS.h"
#define PUSH_SHORT 5
#define PUSH_LONG 200
const int duration = 1500;
bool flag1 = false;
int cntSw0 = 0, cntSw1 = 0;
int cntHigh0 = 0, cntHigh1 = 0;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  pinMode(PIN_SW0, INPUT);
  pinMode(PIN_SW1, INPUT);
  pinMode(PIN_DIPSW1, INPUT);
  pinMode(PIN_DIPSW2, INPUT);
  pinMode(PIN_DIPSW3, INPUT);
  pinMode(PIN_DIPSW4, INPUT);
  pinMode(PIN_LED0, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  initTimer();
}

void loop() {
  mode();
  if (flag1) {
    countPush();
    setDisplay(cntSw1, cntSw0);
  }
  if (!flag1 && (cntSw0 > 0 || cntSw1 > 0)) {
    if (digitalRead(PIN_SW0) == HIGH) {
      cntHigh0++;
    } else {
      if (cntHigh0 >= PUSH_SHORT) {
        setTimer(cntSw1, cntSw0);
        initTimer();
      }
      cntHigh0 = 0;
    }
  }
}

void mode() {
  if (stateDipsw() == "1000") {
    led(3);
    flag1 = true;
  } else {
    led(3, false);
    flag1 = false;
  }
}

void countPush() {
  if (digitalRead(PIN_SW0) == HIGH) {
    if (cntHigh0 <= PUSH_LONG) {
      cntHigh0++;
    }
  } else {
    if (cntHigh0 >= PUSH_SHORT) {
      cntSw0++;
    }
    cntHigh0 = 0;
  }
  if (digitalRead(PIN_SW1) == HIGH) {
    if (cntHigh1 <= PUSH_LONG) {
      cntHigh1++;
    }
  } else {
    if (cntHigh1 >= PUSH_SHORT) {
      cntSw1++;
    }
    cntHigh1 = 0;
  }
}

void initTimer() {
  cntSw0 = 0;
  cntSw1 = 0;
  matrix.writeDigitNum(0, 0, false);
  matrix.writeDigitNum(1, 0, false);
  matrix.writeDigitNum(2, 2, false);
  matrix.writeDigitNum(3, 0, false);
  matrix.writeDigitNum(4, 0, false);
  matrix.writeDisplay();
}

void setDisplay(int mm, int ss) {
  if (mm > 99 || ss > 59 || mm < 0 || ss < 0) {
    return;
  }
  if (ss < 10) {
    matrix.writeDigitNum(4, ss);
  } else {
    matrix.writeDigitNum(3, ss / 10);
    matrix.writeDigitNum(4, ss % 10);
  }
  if (mm < 10) {
    matrix.writeDigitNum(1, mm);
  } else {
    matrix.writeDigitNum(0, mm / 10);
    matrix.writeDigitNum(1, mm % 10);
  }
  matrix.writeDisplay();
}

void setTimer(int mm, int ss) {
  if (mm > 99 || ss > 59 || mm < 0 || ss < 0) {
    return;
  }
  for (int m = mm; m >= 0; m--) {
    if (m == mm) {
      for (int s = ss; s >= 0; s--) {
        matrix.writeDigitNum(0, m / 10);
        matrix.writeDigitNum(1, m % 10);
        matrix.writeDigitNum(3, s / 10);
        matrix.writeDigitNum(4, s % 10);
        matrix.writeDisplay();
        if (m == 0 && s == 0) {
          finish();
        }
        delay(1000);
      }
    } else {
      for (int s = 59; s >= 0; s--) {
        matrix.writeDigitNum(0, m / 10, false);
        matrix.writeDigitNum(1, m % 10, false);
        matrix.writeDigitNum(3, s / 10, false);
        matrix.writeDigitNum(4, s % 10, false);
        matrix.writeDisplay();
        delay(1000);
      }
    }
  }
}

void finish() {
  pinMode(PIN_BUZZER, OUTPUT);
  tone(PIN_BUZZER, 600, duration);
  delay(1000);
}
