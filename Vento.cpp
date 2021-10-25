#include <Arduino.h>
#include "Vento.h"

Vento::Vento(): du(0), tri(0), kvin(0), sep(0)
{  
}

Vento::Vento(int du, int tri, int kvin, int sep): du(du), tri(tri), kvin(kvin), sep(sep)
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

Stela Vento::getTone(Stela fundamental, Stela reference)
{
  return getStela(fundamental);
}

void Vento::shiftTri(int shift)
{
  tri = tri + shift;
}

void Vento::shiftKvin(int shift)
{
  kvin = kvin + shift;  
}

bool Vento::operator==(const Vento& rhs) const
{
  if (du != rhs.du) {return false;}
  if (tri != rhs.tri) {return false;}
  if (kvin != rhs.kvin) {return false;}
  if (sep != rhs.sep) {return false;}

  return true;
}

bool Vento::operator!=(const Vento& rhs) const
{
  if (du == rhs.du) {return true;}
  if (tri == rhs.tri) {return true;}
  if (kvin == rhs.kvin) {return true;}
  if (sep == rhs.sep) {return true;}

  return false;
}
