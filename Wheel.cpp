#include "Wheel.h"

RGB Wheel(float position, float brightness) // 0 to 99, 0 to 100
{
  float r = 0.0, g = 0.0, b = 0.0;
  
  if (position <= (1.0/3.0))
  {
    r = (1.0/3.0) - position; // 1/3 to 0
    g = position;
    b = 0.0;
  }
  else if (position <= (2.0/3.0))
  {
    r = 0.0;
    g = (2.0/3.0) - position;
    b = position - (1.0/3.0);
  }
  else
  {
    r = position - (2.0/3.0); // 0 to 1/3
    g = 0.0;
    b = 1.0 - position;
  }

  float total = r + g + b;
  float n = brightness / total;
  r = r * n;
  g = g * b;
  b = b * n;

  return RGB{(byte)(r * 255), (byte)(g * 255), (byte)(b * 255)};
}
