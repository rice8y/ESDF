#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "EPS.h"
#include "Music.h"

#define DEBOUNCE_DELAY 100

int mm = 0, ss = 0;
int m = 0, s = 0;
int cnt = 0;
int buff0 = 0, buff1 = 0;
bool startFlag = false;
int memory[4];
int hist[2];
bool resetFlag = false;
bool fastFlag = true;
const unsigned long doubleClickThreshold = 350;

unsigned long lastDebounceTime0 = 0;
unsigned long lastDebounceTime1 = 0;

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  matrix.begin(0x70);
  Serial.begin(9600);
  initLeds();
  initDipsws();
  pinMode(PIN_BUZZER, OUTPUT);
  for (int i = 0; i < 4; i++) {
    memory[i] = 0;
  }
  for (int i = 0; i < 2; i++) {
    hist[i] = -1;
  }
}

void loop() {
  buffStates();
  switch (stateDipsw()) {
    case 0b0000:
      displayEmpty();
      break;
    case 0b1000:
      setTime(&mm, &ss);
      display(mm, ss);
      break;
    case 0b0100:
      setTime(&m, &s);
      display(m, s);
      break;
    case 0b0010:
      setCount(&cnt);
      displayCount(cnt);
      break;
    case 0b0001:
      display(mm, ss);
      handleStartBotton(PIN_SW0, &startFlag, lastDebounceTime0, mm, ss, m, s, cnt);
      delay(30);
      if (startFlag) {
        doTimer();
        initCondition();
      }
      break;
    case 0b1111:
      handleButton(PIN_SW0, &resetFlag, lastDebounceTime0);
      if (resetFlag) {
        reset();
        resetFlag = false;
      }
      break;
  }
  delay(10);
}

void handleStartBotton(int pin, bool *flag, unsigned long &lastDebounceTime, int mm, int ss, int m, int s, int cnt) {
  if (digitalRead(pin) == HIGH) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      if ((mm + ss > 0) || (cnt > 0 && m + s > 0)) {
        *flag = true;
      }
    }
    lastDebounceTime = millis();
  }
}

void handleButton(int pin, bool *flag, unsigned long &lastDebounceTime) {
  if (digitalRead(pin) == HIGH) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      *flag = true;
    }
    lastDebounceTime = millis();
  }
}

void initCondition() {
  mm = 0;
  ss = 0;
  m = 0;
  s = 0;
  cnt = 0;
  lastDebounceTime0 = 0;
  lastDebounceTime1 = 0;
  resetFlag = false;
  startFlag = false;
  fastFlag = true;
}

void setTime(int *minutes, int *seconds) {
  handleTimeButton(PIN_SW0, seconds, lastDebounceTime0);
  handleTimeButton(PIN_SW1, minutes, lastDebounceTime1);
  limit(minutes, seconds);
}

void handleTimeButton(int pin, int *value, unsigned long &lastDebounceTime) {
  if (digitalRead(pin) == HIGH) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      *value += 1;
    }
    lastDebounceTime = millis();
  }
}

void limit(int *m, int *s) {
  if (*s >= 60) {
    *m += 1;
    *s = 0;
  }
  if ((*s) < 0) {
    (*s) = 0;
  }
  if (*m > 99) {
    *m = 99;
  }
  if ((*m) < 0) {
    (*m) = 0;
  }
}

void setCount(int *cnt) {
  handleCountButton(PIN_SW0, cnt, 1, lastDebounceTime0);
  handleCountButton(PIN_SW1, cnt, -1, lastDebounceTime1);
  if ((*cnt) > 9999) {
    (*cnt) = 9999;
  }
  if ((*cnt) < 0) {
    (*cnt) = 0;
  }
}

void handleCountButton(int pin, int *value, int increment, unsigned long &lastDebounceTime) {
  if (digitalRead(pin) == HIGH) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      *value += increment;
    }
    lastDebounceTime = millis();
  }
}

void display(int minutes, int seconds) {
  matrix.writeDigitNum(0, minutes / 10, false);
  matrix.writeDigitNum(1, minutes % 10, false);
  matrix.writeDigitNum(2, 2, false);
  matrix.writeDigitNum(3, seconds / 10, false);
  matrix.writeDigitNum(4, seconds % 10, false);
  matrix.writeDisplay();
}

void displayError() {
  matrix.print("----");
  matrix.writeDisplay();
}

void displayEmpty() {
  matrix.print("");
  matrix.writeDisplay();
}

void displayCount(int cnt) {
  matrix.print(cnt);
  matrix.writeDisplay();
}

void timer(int *minutes, int *seconds, bool buzzer = true) {
  buff0 = (*seconds);
  buff1 = (*minutes);
  while (1) {
    display(*minutes, *seconds);
    if ((*seconds)-- == 0) {
      if ((*minutes)-- > 0) {
        (*seconds) = 59;
      } else {
        break;
      }
    }
    for (int i = 0; i < 10; i++) {
      stop();
      delay(100);
    }
  }
  if (buzzer && !resetFlag) {
    tone(PIN_BUZZER, nc5, 500);
  } else if (!buzzer && !resetFlag) {
    while (1) {
      playMusic(PIN_BUZZER, alert_2, 120);
      if (stateDipsw() == 0b0000) {
        break;
      }
    }
  }
  delay(1000);
  display(*minutes, *seconds);
  (*seconds) = buff0;
  (*minutes) = buff1;
}

void doTimer() {
  for (int i = 0; i <= cnt; i++) {
    if (i != cnt) {
      timer(&mm, &ss);
      timer(&m, &s);
    } else {
      timer(&mm, &ss, false);
    }
  }
}

void buffStates() {
  int current = stateDipsw();
  if (memory[3] != current) {
    for (int i = 1; i < 4; i++) {
      memory[i - 1] = memory[i];
    }
    memory[3] = current;
  }
}

void reset() {
  if (memory[0] == 0b1000 && memory[3] == 0b1111) {
    mm = 0;
    ss = 0;
    display(mm, ss);
  } else if (memory[0] == 0b0100 && memory[3] == 0b1111) {
    m = 0;
    s = 0;
    display(m, s);
  } else if (memory[0] == 0b0010 && memory[3] == 0b1111) {
    cnt = 0;
    displayCount(cnt);
  }
}

void buttonHistory(int value) {
  hist[0] = hist[1];
  hist[1] = value;
}

void stop() {
  bool sw0Pressed = false;
  bool sw1Pressed = false;
  unsigned long pressStartTime = 0;

  sw0Pressed = isButtonPressed(PIN_SW0, lastDebounceTime0);
  sw1Pressed = isButtonPressed(PIN_SW1, lastDebounceTime1);
  buttonHistory(int(sw0Pressed));

  if (hist[0] == 0 && hist[1] == 1) {
    delay(10);
    hist[0] = -1;
    hist[1] = -1;
    while (1) {
      sw0Pressed = isButtonPressed(PIN_SW0, lastDebounceTime0);
      sw1Pressed = isButtonPressed(PIN_SW1, lastDebounceTime1);
      buttonHistory(int(sw0Pressed));

      if (hist[0] == 0 && hist[1] == 1) {
        break;
      } else if (sw1Pressed) {
        initCondition();
        display(mm, ss);
        resetFlag = true;
        break;
      }

      delay(20);
    }
  }
}

bool isButtonPressed(int pin, unsigned long &lastDebounceTime) {
  bool state = false;
  if (digitalRead(pin) == HIGH) {
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
      state = true;
      lastDebounceTime = millis();
    }
  }
  return state;
}
