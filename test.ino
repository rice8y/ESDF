#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
const int ledPin = 5;

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
}

void loop() {
  initTimer();
  delay(1000);
  setTimer(1, 30);
}

void initTimer() {
  matrix.writeDigitNum(0, 0, false);
  matrix.writeDigitNum(1, 0, false);
  matrix.writeDigitNum(2, 2, false);
  matrix.writeDigitNum(3, 0, false);
  matrix.writeDigitNum(4, 0, false);
  matrix.writeDisplay();
}

void setTimer(int mm, int ss) {
  if (mm > 99 || ss > 59 || mm < 0 || ss < 0) {
    return;
  }
  for (int m = mm; m >= 0; m--) {
    if (m == mm) {
      for (int s = ss; s >= 0; s--) {
        matrix.writeDigitNum(0, m / 10, false);
        matrix.writeDigitNum(1, m % 10, false);
        matrix.writeDigitNum(3, s / 10, false);
        matrix.writeDigitNum(4, s % 10, false);
        matrix.writeDisplay();
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
  finish();
}

void finish() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(5000);
  digitalWrite(ledPin, LOW);
}
