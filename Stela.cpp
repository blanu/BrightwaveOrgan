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

  if (grado > 12)
  {
    grado = 12;
  }
  
  if (grado < 0)
  {
    grado = 0;
  }
  
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

void Stela::setHertz(float newHertz)
{
  hertz = newHertz;  
  stela = (float)log2(hertz);
  grado = (int)stela;
  arko = stela - grado;
}

float Stela::getFloat()
{
  return stela;
}

void Stela::setFloat(float newStela)
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
