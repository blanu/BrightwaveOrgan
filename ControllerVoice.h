#ifndef _CONTROLLERVOICE_H_
#define _CONTROLLERVOICE_H_

#include "Vento.h"

class ControllerVoice
{
  public:
    ControllerVoice();
    ControllerVoice(bool on, Vento vento);
    virtual ~ControllerVoice();

    bool on;
    Vento vento;
    
  private:
};

#endif
