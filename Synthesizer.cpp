#include "Synthesizer.h"
#include <Arduino.h>

Synthesizer::Synthesizer(Koro koro): koro(koro)
{  
  Serial.println("Synthesizer Constructor");
  
  // reduce the gain on some channels, so half of the channels
  // are "positioned" to the left, half to the right, but all
  // are heard at least partially on both ears
//  mixerLeft.gain(1, 0.36);
//  mixerLeft.gain(3, 0.36);
//  mixerRight.gain(0, 0.36);
//  mixerRight.gain(2, 0.36);
//  
//  mixer1.gain(0, 0.75);
//  mixer1.gain(1, 0.0);
//  mixer1.gain(2, 0.0);
//  mixer1.gain(3, 0.0);
//  mixer2.gain(0, 0.15);
//  mixer2.gain(1, 0.0);
//  mixer2.gain(2, 0.0);
//  mixer2.gain(3, 0.0);

}

Synthesizer::~Synthesizer()
{
  
}

void Synthesizer::on(int voice)
{
  if (voice >= 1 && voice < 16)
  {
//    voices[voice-1]->on();
  }
}

void Synthesizer::off(int voice)
{
  if (voice >= 1 && voice < 16)
  {
//    voices[voice-1]->off();
  }
}
