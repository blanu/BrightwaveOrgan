#ifndef _CONTROLLERVOICE_H_
#define _CONTROLLERVOICE_H_

#include <Arduino.h>
#include "Vento.h"

class ControllerVoice
{
  public:
    ControllerVoice();
    ControllerVoice(bool on, byte note, Vento vento);
    virtual ~ControllerVoice();

    bool on;
    byte note;
    Vento vento;
    
  private:
};

#endif
