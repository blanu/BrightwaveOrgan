#include <Arduino.h>
#include "Koro.h"

Koro::Koro()
{ 
  Serial.println("Koro constructor");
}

Koro::~Koro()
{
}

void Koro::setStartHertz(float hertz)
{
  start = Stela(hertz);
}

void Koro::setArkoShift(int newArkoShift)
{
  arkoShift = newArkoShift;
}

void Koro::setGradoShift(int newGradoShift)
{
  gradoShift = newGradoShift;
}

Stela Koro::getFundamental()
{
  float grado = float(start.grado) + gradoShift;

  int modShift = arkoShift % 100;
  float floatArkoShift = float(modShift) / 100.0;
  
  float arko = start.arko + floatArkoShift;
    
  if (arko > 1.0)
  {
    arko = arko - 1.0;
  }

  if (arko < 0)
  {
    arko = arko + 1.0;
  }

  return Stela(grado, arko);
}

Stela Koro::getTone()
{
  Stela fundamental = getFundamental();
  return vento.getTone(fundamental);
}
