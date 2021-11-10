#ifndef _WHEEL_H_
#define _WHEEL_H_

#include <Arduino.h>

struct RGB
{
  byte R;
  byte G;
  byte B;
};

RGB Wheel(float position, float brightness);

#endif
