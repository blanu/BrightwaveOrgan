#include "Stela.h"
#include "Ratio.h"
#include <cmath>

Stela::Stela(float hertz): hertz(hertz)
{
  stela = log2(hertz);
  grado = (int)stela;
  arko = stela - grado;
}

Stela::Stela(int grado, float arko): grado(grado), arko(arko)
{
  stela = ((float)grado) + arko;
  
  hertz = pow(2, stela);
}

Stela::~Stela()
{
  
}

void Stela::setGrado(int newGrado)
{
  grado = newGrado;
  
  stela = ((float)grado) + arko;
  
  hertz = pow(2, stela);  
}

void Stela::shiftGrado(int shift)
{
  setGrado(grado + shift);
}

void Stela::setArko(float newArko)
{
  arko = newArko;
  
  stela = ((float)grado) + arko;
  
  hertz = pow(2, stela);  
}

float Stela::getStela()
{
  return stela;
}

void Stela::setStela(float newStela)
{
  stela = newStela;
  grado = int(stela);
  arko = stela - grado;
  hertz = pow(2, stela);
}

Stela Stela::multiply(Ratio ratio)
{
  float oldHertz = hertz;
  float newHertz = (oldHertz * float(ratio.numerator)) / float(ratio.denominator);
  
  return Stela(newHertz);
}
