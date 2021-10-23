#include <Arduino.h>
#include "Koro.h"

Koro::Koro()
{ 
  Serial.println("Koro constructor");
}

Koro::~Koro()
{
}

void Koro::setShift(int newShift)
{
  float arkoShift = float(newShift) / 100.0f;
  float oldStela = start.getStela();
  float newStela = oldStela + arkoShift;
  fundamental.setStela(newStela);  
}

void Koro::setRatio(int numerator, int denominator)
{
  ratio = Ratio(numerator, denominator);
}

Ratio Koro::getRatio()
{
  return ratio;
}

Stela Koro::getTone()
{
  return fundamental.multiply(ratio);
}
