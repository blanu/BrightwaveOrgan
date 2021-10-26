#include "ControllerVoice.h"

ControllerVoice::ControllerVoice(): on(false), note(0), vento(Vento(0, 0, 0, 0))
{
}

ControllerVoice::ControllerVoice(bool on, byte note, Vento vento): on(on), note(note), vento(vento)
{  
}

ControllerVoice::~ControllerVoice()
{
}
