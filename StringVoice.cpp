#include "StringVoice.h"
#include "Stela.h"
#include "Ratio.h"
#include <Arduino.h>

StringVoice::StringVoice()
{ 
}

StringVoice::~StringVoice()
{
  wave.noteOff(0.0);
}

void StringVoice::setTone(Stela newTone)
{
  tone = newTone;
}

void StringVoice::on()
{
  wave.noteOn(tone.hertz, 1.0);
}

void StringVoice::off()
{
  wave.noteOff(0.0);
}
