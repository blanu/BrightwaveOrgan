#ifndef _STELA_H_
#define _STELA_H_

#include "Ratio.h"

class Stela
{
  public:
    Stela(int grado, float arko);
    Stela(float hertz);
    
    virtual ~Stela();

    int grado;
    float arko;    
    float hertz;

    void setGrado(int newGrado);
    void setArko(float newArko);
    void setHertz(float hertz);

    void shiftGrado(int shift);
    
    float getFloat();
    void setFloat(float newStela);

    Stela multiply(Ratio ratio);

  private:
    float stela;
};

#endif
