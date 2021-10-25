#include <Arduino.h>
#include "Controller.h"

Controller::Controller(ControllerMode mode): mode(mode)
{ 
  Serial.println("Controller constructor");
}

Controller::~Controller()
{
}

void Controller::handleNoteOff(byte channel, byte note, byte velocity)
{
  switch (mode)
  {
    case mono:
      if (voices[0].on)
      {
        voices[0].on = false;
        changed[0] = true;
      }
      else
      {
        return;
      }
    default:
      return;
  }  
}

void Controller::handleNoteOn(byte channel, byte note, byte velocity)
{
  switch (mode)
  {
    case mono:
      if (voices[0].on)
      {
        Vento newVento = getVento(note);
        if (voices[0].vento != newVento)
        {
          voices[0].vento = newVento;
          changed[0] = true;
        }
      }
      else
      {
        voices[0].on = true;        
        voices[0].vento = getVento(note);
        changed[0] = true;
      }
    default:
      return;
  }
}

void Controller::handleAfterTouchPoly(byte channel, byte note, byte velocity) {}
void Controller::handleControlChange(byte channel, byte control, byte value) {}
void Controller::handleProgramChange(byte channel, byte program) {}
void Controller::handleAfterTouch(byte channel, byte pressure) {}
void Controller::handlePitchChange(byte channel, int pitch) {}
void Controller::handleSystemExclusiveChunk(const byte *data, uint16_t length, bool last) {}
void Controller::handleSystemExclusive(byte *data, unsigned int length) {}
void Controller::handleTimeCodeQuarterFrame(byte data) {}
void Controller::handleSongPosition(uint16_t beats) {}
void Controller::handleSongSelect(byte songNumber) {}
void Controller::handleTuneRequest() {}
void Controller::handleClock() {}
void Controller::handleStart() {}
void Controller::handleContinue() {}
void Controller::handleStop() {}
void Controller::handleActiveSensing() {}
void Controller::handleSystemReset() {}
void Controller::handleRealTimeSystem(byte realtimebyte) {}

Vento Controller::getVento(int noteNumber)
{
  switch (noteNumber)
  {
    case 32:
      return Vento(-2, 0, -1, 0);
    case 34:
      return Vento(-2, -2, 0, 0);
    case 36:
      return Vento(-1, 0, 0, 0);
    case 37:
      return Vento(-1, -1, -1, 0);
    case 38:
      return Vento(-1, 2, 0, 0);
    case 39:
      return Vento(-1, 1, -1, 0);
    case 40:
      return Vento(-1, 1, 0, 0);
    case 41:
      return Vento(-1, 0, -1, 0);
    case 42:
      return Vento(-1, 0, -1, 1);
    case 43:
      return Vento(-1, 1, 0, 0);
    case 44:
      return Vento(-1, 0, -1, 0);
    case 45:
      return Vento(-1, -1, 1, 0);
    case 46:
      return Vento(-1, -2, 0, 0);
    case 47:
      return Vento(-1, 1, 1, 0);
    case 48:
      return Vento(0, 0, 0, 0);
    case 49:
      return Vento(0, -1, -1, 0);
    case 50:
      return Vento(0, 2, 0, 0);
    case 51:
      return Vento(0, 1, -1, 0);
    case 52:
      return Vento(0, 1, 0, 0);
    case 53:
      return Vento(0, 0, -1, 0);
    case 54:
      return Vento(0, 0, -1, 1);
    case 55:
      return Vento(0, 1, 0, 0);
    case 56:
      return Vento(0, 0, -1, 0);
    case 57:
      return Vento(0, -1, 1, 0);
    case 58:
      return Vento(0, -2, 0, 0);
    case 59:
      return Vento(0, 1, 1, 0);
    case 60:
      return Vento(1, 0, 0, 0);
    case 61:
      return Vento(1, -1, -1, 0);
    case 62:
      return Vento(1, 2, 0, 0);
    case 63:
      return Vento(1, 1, -1, 0);
    case 64:
      return Vento(1, 1, 0, 0);
    case 65:
      return Vento(1, 0, -1, 0);
    case 66:
      return Vento(1, 0, -1, 1);
    case 67:
      return Vento(1, 1, 0, 0);
    case 68:
      return Vento(1, 0, -1, 0);
    case 69:
      return Vento(1, -1, 1, 0);
    case 70:
      return Vento(1, -2, 0, 0);
    case 71:
      return Vento(1, 1, 1, 0);
    case 72:
      return Vento(2, 0, 0, 0);
    case 73:
      return Vento(2, -1, -1, 0);
    case 74:
      return Vento(2, 2, 0, 0);
    case 75:
      return Vento(2, 1, -1, 0);
    case 76:
      return Vento(2, 1, 0, 0);
    case 77:
      return Vento(2, 0, -1, 0);
    case 78:
      return Vento(2, 0, -1, 1);
    case 79:
      return Vento(2, 1, 0, 0);
    case 80:
      return Vento(2, 0, -1, 0);
    case 81:
      return Vento(2, -1, 1, 0);
    case 82:
      return Vento(2, -2, 0, 0);
    case 83:
      return Vento(2, 1, 1, 0);
    case 84:
      return Vento(3, 0, 0, 0);
    case 85:
      return Vento(3, -1, -1, 0);
    case 86:
      return Vento(3, 2, 0, 0);
    case 87:
      return Vento(3, 1, -1, 0);
    case 88:
      return Vento(3, 1, 0, 0);
    case 90:
      return Vento(3, 0, -1, 1);
    case 92:
      return Vento(3, 0, -1, 0);
    
    default:
      return Vento(0, 0, 0, 0);
  }
}

void Controller::resetChanged()
{
  changed[0] = false;
  changed[1] = false;
  changed[2] = false;
  changed[3] = false;
  changed[4] = false;
  changed[5] = false;
  changed[6] = false;
  changed[7] = false;
  changed[8] = false;
  changed[9] = false;
  changed[10] = false;
  changed[11] = false;
  changed[12] = false;
  changed[13] = false;
  changed[14] = false;
  changed[15] = false;
}
