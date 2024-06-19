#ifndef EPS_H
#define EPS_H

#include <Arduino.h>
#include "EnpitShield.h"

#define PUSH_LONG 1000
#define PUSH_SHORT 100

void led(int led, bool s = true);
String stateDipsw();

#endif