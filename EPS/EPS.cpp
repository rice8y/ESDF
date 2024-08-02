#include "EPS.h"

void led(int led, bool s = true)
{
  int state = s ? HIGH : LOW;
  switch (led)
  {
  case 0:
    digitalWrite(PIN_LED0, state);
    break;
  case 1:
    digitalWrite(PIN_LED1, state);
    break;
  case 2:
    digitalWrite(PIN_LED2, state);
    break;
  case 3:
    digitalWrite(PIN_LED3, state);
    break;
  default:
    break;
  }
}

int stateDipsw() { 
  int state = 0;
  state |= (digitalRead(PIN_DIPSW1) == HIGH) << 3;
  state |= (digitalRead(PIN_DIPSW2) == HIGH) << 2;
  state |= (digitalRead(PIN_DIPSW3) == HIGH) << 1;
  state |= (digitalRead(PIN_DIPSW4) == HIGH);
  return state;
}

void initLeds()
{
  pinMode(PIN_LED0, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
}

void initDipsws()
{
  pinMode(PIN_DIPSW1, INPUT);
  pinMode(PIN_DIPSW2, INPUT);
  pinMode(PIN_DIPSW3, INPUT);
  pinMode(PIN_DIPSW4, INPUT);
}

void initSws()
{
  pinMode(PIN_SW0, INPUT);
  pinMode(PIN_SW1, INPUT);
}