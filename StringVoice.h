#ifndef _STRINGVOICE_H_
#define _STRINGVOICE_H_

#include "Stela.h"
#include "Ratio.h"
#include "Audio.h"

class StringVoice
{
  public:
    StringVoice();
    virtual ~StringVoice();

    AudioSynthKarplusStrong wave;

    void setTone(Stela newTone);
    void on();
    void off();

  private:
    Stela tone = Stela(7, 0.0);
};

#endif
