#ifndef _VOICE_H_
#define _VOICE_H_

#include "Stela.h"
#include "Ratio.h"
#include "Audio.h"

class Voice
{
  public:
    Voice(short waveType);
    virtual ~Voice();

    AudioEffectEnvelope env;
    AudioSynthWaveform wave;

    void setTone(Stela newTone);
    void on();
    void off();

  private:
    short waveType;
    Stela tone = Stela(7, 0.0);
};

#endif
