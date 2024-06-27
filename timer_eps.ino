#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "EPS.h"

#define PUSH_SHORT 5
#define PUSH_LONG 100
#define STEP 10

int mm = 0, ss = 0;
int m = 0, s = 0;
int cnt = 0;
int cntHigh0 = 0, cntHigh1 = 0;
int buff0 = 0, buff1 = 0;
int memory[4];

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
}

void loop() {
  buffStates();
  switch (stateDipsw()) {
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
      if (digitalRead(PIN_SW0) == HIGH) {
        cntHigh0++;
      } else {
        if (cntHigh0 >= PUSH_SHORT) {
          doTimer();
          initCondition();
        }
        cntHigh0 = 0;
      }
      break;
    case 0b1111:
      if (digitalRead(PIN_SW0) == HIGH) {
        cntHigh0++;
      } else {
        if (cntHigh0 >= PUSH_SHORT) {
          reset();
        }
        cntHigh0 = 0;
      }
      break;
  }
  delay(10);
}

void initCondition() {
  mm = 0;
  ss = 0;
  m = 0;
  s = 0;
  cnt = 0;
}

void setTime(int *minutes, int *seconds) {
  if (digitalRead(PIN_SW0) == HIGH) {
    cntHigh0++;
    if (cntHigh0 >= PUSH_LONG) {
      (*seconds) += (cntHigh0 % STEP == 0);
    }
  } else {
    if (cntHigh0 >= PUSH_SHORT) {
      (*seconds)++;
    }
    cntHigh0 = 0;
  }
  if (digitalRead(PIN_SW1) == HIGH) {
    cntHigh1++;
    if (cntHigh1 >= PUSH_LONG) {
      (*minutes) += (cntHigh1 % STEP == 0);
    }
  } else {
    if (cntHigh1 >= PUSH_SHORT) {
      (*minutes)++;
    }
    cntHigh1 = 0;
  }

  // if (reset()) {
  //   *minutes = 0;
  //   *seconds = 0;
  // }
  limit(minutes, seconds);
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
  if (digitalRead(PIN_SW0) == HIGH) {
    cntHigh0++;
    if (cntHigh0 >= PUSH_LONG) {
      (*cnt) += (cntHigh0 % STEP == 0);
    }
  } else {
    if (cntHigh0 >= PUSH_SHORT) {
      (*cnt)++;
    }
    cntHigh0 = 0;
  }
  if (digitalRead(PIN_SW1) == HIGH) {
    cntHigh1++;
    if (cntHigh1 >= PUSH_LONG) {
      (*cnt)--;
    }
  } else {
    if (cntHigh1 >= PUSH_SHORT) {
      (*cnt)--;
    }
    cntHigh1 = 0;
  }
  if ((*cnt) > 9999) {
    (*cnt) = 9999;
  }
  if ((*cnt) < 0) {
    (*cnt) = 0;
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
    delay(1000);
  }
  if (buzzer) {
    tone(PIN_BUZZER, 523, 500);
  }
  delay(1000);
  display(*minutes, *seconds);
  (*seconds) = buff0;
  (*minutes) = buff1;
}

void doTimer() {
  for (int i = 0; i <= cnt; i++) {
    timer(&mm, &ss);
    if (i != cnt) {
      timer(&m, &s);
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
  for (int i = 0; i < 4; i++) {
    Serial.println(String(i) + ": " + String(memory[i]));
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
