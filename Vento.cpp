#include <Arduino.h>
#include "Vento.h"

Vento::Vento(bool rising): rising(rising), tri(0), kvin(0)
{  
}

Vento::Vento(bool rising, int tri, int kvin): rising(rising), tri(tri), kvin(kvin)
{
}

Vento::~Vento()
{
}

Ratio Vento::getRatio()
{
  if ((tri==0) && (kvin==0))
  {
    return Ratio(1, 1);    
  }
  else
  {
    int N = 1;
    int D = 1;

    if (tri > 0)
    {
      N = N * (pow(3, tri));
    }
    else if (tri < 0)
    {
      D = D * (pow(3, -tri));      
    }

    if (kvin > 0)
    {
      N = N * (pow(5, kvin));
    }
    else if (kvin < 0)
    {
      D = D * (pow(5, -kvin));      
    }

    return Ratio(N, D);
  }
}

Stela Vento::getStela(Stela fundamental)
{
  Ratio ratio = getRatio();
  return fundamental.multiply(ratio);
}

Stela Vento::getRising(Stela fundamental, Stela reference)
{
  Stela result = getStela(fundamental);

  while (result.getStela() > reference.getStela())
  {
    result.setGrado(result.grado - 1);
  }

  while (result.getStela() < reference.getStela())
  {
    result.setGrado(result.grado + 1);
  }

  return result;
}

Stela Vento::getFalling(Stela fundamental, Stela reference)
{
  Stela result = getStela(fundamental);

  while (result.getStela() < reference.getStela())
  {
    result.setGrado(result.grado + 1);
  }

  while (result.getStela() > reference.getStela())
  {
    result.setGrado(result.grado - 1);
  }

  return result;
}

Stela Vento::getTone(Stela fundamental, Stela reference)
{
  if (rising)
  {
    return getRising(fundamental, reference);    
  }
  else
  {
    return getFalling(fundamental, reference);    
  }
}

void Vento::shiftTri(int shift)
{
  tri = tri + shift;
}

void Vento::shiftKvin(int shift)
{
  kvin = kvin + shift;  
}
