#include "Voice.h"
#include "Stela.h"
#include "Ratio.h"
#include <Arduino.h>

Voice::Voice(short waveType): waveType(waveType)
{ 
  Serial.println("Voice constructor");

  wave.begin(1.0, tone.hertz, waveType);
  
  env.attack(9.2);
  env.hold(2.1);
  env.decay(31.4);
  env.sustain(0.6);
  env.release(84.5);
}

Voice::~Voice()
{
  env.noteOff();
}

void Voice::setTone(Stela newTone)
{
  tone = newTone;
  wave.begin(1.0, tone.hertz, waveType);
}

void Voice::on()
{
  Serial.println(tone.hertz);
  env.noteOn();
}

void Voice::off()
{
  env.noteOff();
}

//void Voice::multiply()
//{
//  float newHertz = (fundamental.hertz * ratio->numerator) / ratio->denominator;
//  float newStela = log2(newHertz);
//  int newGrado = (int)newStela;
//  float newArko = newStela - newGrado;
//    
//  frequency->setGrado(newGrado);
//  frequency->setArko(newArko);
//}
