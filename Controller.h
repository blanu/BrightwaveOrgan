#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <Arduino.h>

#include "Stela.h"
#include "Ratio.h"
#include "Vento.h"
#include "Audio.h"
#include "ControllerVoice.h"

enum ControllerMode
{
  mono,
  poly,
  mpe
};

class Controller
{
  public:
    Controller(ControllerMode mode);
    virtual ~Controller();

    ControllerVoice voices[16];
    bool changed[16] = {
      false, false, false, false,      
      false, false, false, false,      
      false, false, false, false,      
      false, false, false, false
    };    

    void handleNoteOff(byte channel, byte note, byte velocity);
    void handleNoteOn(byte channel, byte note, byte velocity);
    void handleAfterTouchPoly(byte channel, byte note, byte velocity);
    void handleControlChange(byte channel, byte control, byte value);
    void handleProgramChange(byte channel, byte program);
    void handleAfterTouch(byte channel, byte pressure);
    void handlePitchChange(byte channel, int pitch);
    void handleSystemExclusiveChunk(const byte *data, uint16_t length, bool last);
    void handleSystemExclusive(byte *data, unsigned int length);
    void handleTimeCodeQuarterFrame(byte data);
    void handleSongPosition(uint16_t beats);
    void handleSongSelect(byte songNumber);
    void handleTuneRequest();
    void handleClock();
    void handleStart();
    void handleContinue();
    void handleStop();
    void handleActiveSensing();
    void handleSystemReset();
    void handleRealTimeSystem(byte realtimebyte);

    Vento getVento(int noteNumber);
    void resetChanged();
    
  private:
    ControllerMode mode;
    byte lastNote;

    int findVoice(byte note);
    int allocateVoice();
};

#endif
