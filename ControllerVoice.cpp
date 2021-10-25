#include "ControllerVoice.h"

ControllerVoice::ControllerVoice(): on(false), vento(Vento(0, 0, 0, 0))
{
}

ControllerVoice::ControllerVoice(bool on, Vento vento): on(on), vento(vento)
{  
}

ControllerVoice::~ControllerVoice()
{
}
