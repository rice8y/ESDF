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

String stateDipsw()
{
  int state[4];
  state[0] = digitalRead(PIN_DIPSW1);
  state[1] = digitalRead(PIN_DIPSW2);
  state[2] = digitalRead(PIN_DIPSW3);
  state[3] = digitalRead(PIN_DIPSW4);

  String stateString = "";
  for (int i = 0; i < 4; i++)
  {
    stateString += (state[i] == HIGH) ? "1" : "0";
  }
  return stateString;
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