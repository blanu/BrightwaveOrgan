#ifndef _KORO_H_
#define _KORO_H_

#include <Wire.h>
#include <SerLCD.h>
#include <SparkFun_Qwiic_Twist_Arduino_Library.h>

#include "Stela.h"
#include "Ratio.h"
#include "Audio.h"
#include "Vento.h"

class Koro
{
  public:
    Koro();
    virtual ~Koro();

    Vento vento = Vento();

    void setStartHertz(float hertz);
    void setArkoShift(int newArkoShift);    
    void setGradoShift(int newGradoShift);
    Stela getFundamental();
    Stela getTone();
  private:
    Stela start = Stela(7, 0.0);
    int arkoShift = 0;
    int gradoShift = 0;
};

#endif
