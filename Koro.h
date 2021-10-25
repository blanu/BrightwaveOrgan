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

    Stela fundamental = Stela(7, 0.0);
    Stela last = fundamental;
    Vento vento = Vento();
    
    void setShift(int newShift);
    
    void setRatio(int numerator, int denominator);
    Ratio getRatio();

    Stela getTone();

    Ratio lockedTuning[3][3] = {
      {Ratio(5, 3), Ratio(5, 4), Ratio(3*5, 8)},      
      {Ratio(4, 3), Ratio(1, 1), Ratio(3, 2)},      
      {Ratio(16, 3*5), Ratio(8, 5), Ratio(6, 5)}
    };    

    Ratio unlockedTuning[3][3] = {
      {Ratio(5, 3), Ratio(5, 1), Ratio(3*5, 1)},      
      {Ratio(1, 3), Ratio(1, 1), Ratio(3, 1)},      
      {Ratio(1, 3*5), Ratio(1, 5), Ratio(3, 5)}
    };        

  private:
      Stela start = Stela(7, 0.0);
      int shift = 0;
      Ratio ratio = Ratio(1, 1);
};

#endif
