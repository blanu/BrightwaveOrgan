#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <SparkFun_Qwiic_Keypad_Arduino_Library.h>

#include "Panel.h"
#include "Synthesizer.h"
#include "Controller.h"
#include "StringVoice.h"

KEYPAD keypad; //Create instance of this object

enum Mode
{
  Startup,
  StartingTuning,
  Tuning,
  ExitingTuning,
  Play
};

Mode mode = Startup;

uint16_t grado = 7;
uint16_t arko = 0;

AudioControlSGTL5000 codec;
AudioOutputI2S output;
AudioOutputUSB outputUSB; 

AudioMixer4 leftMixer;  AudioConnection leftMixerPatch(leftMixer, 0, outputUSB, 0);
AudioMixer4 rightMixer; AudioConnection rightMixerPatch(rightMixer, 0, outputUSB, 1);

AudioMixer4 mixer0; AudioConnection mixer0Patch(mixer0, 0, leftMixer, 0);
AudioMixer4 mixer1; AudioConnection mixer1Patch(mixer1, 0, leftMixer, 1);
AudioMixer4 mixer2; AudioConnection mixer2Patch(mixer2, 0, rightMixer, 0);
AudioMixer4 mixer3; AudioConnection mixer3Patch(mixer3, 0, rightMixer, 1);

//Voice voices[16] = {
//  Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE),
//  Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE),
//  Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE),
//  Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE), Voice(WAVEFORM_SINE)
//};

StringVoice voices[16] = {
  StringVoice(), StringVoice(), StringVoice(), StringVoice(),
  StringVoice(), StringVoice(), StringVoice(), StringVoice(),
  StringVoice(), StringVoice(), StringVoice(), StringVoice(),
  StringVoice(), StringVoice(), StringVoice(), StringVoice()
};

//AudioConnection voice0WavePatch(voices[0].wave, 0, voices[0].env, 0); AudioConnection voice0EnvPatch(voices[0].env, 0, mixer0, 0);
//AudioConnection voice1WavePatch(voices[1].wave, 0, voices[1].env, 0); AudioConnection voice1EnvPatch(voices[1].env, 0, mixer0, 1);
//AudioConnection voice2WavePatch(voices[2].wave, 0, voices[2].env, 0); AudioConnection voice2EnvPatch(voices[2].env, 0, mixer0, 2);
//AudioConnection voice3WavePatch(voices[3].wave, 0, voices[3].env, 0); AudioConnection voice3EnvPatch(voices[3].env, 0, mixer0, 3);
//AudioConnection voice4WavePatch(voices[4].wave, 0, voices[4].env, 0); AudioConnection voice4EnvPatch(voices[4].env, 0, mixer1, 0);
//AudioConnection voice5WavePatch(voices[5].wave, 0, voices[5].env, 0); AudioConnection voice5EnvPatch(voices[5].env, 0, mixer1, 1);
//AudioConnection voice6WavePatch(voices[6].wave, 0, voices[6].env, 0); AudioConnection voice6EnvPatch(voices[6].env, 0, mixer1, 2);
//AudioConnection voice7WavePatch(voices[7].wave, 0, voices[7].env, 0); AudioConnection voice7EnvPatch(voices[7].env, 0, mixer1, 3);
//AudioConnection voice8WavePatch(voices[8].wave, 0, voices[8].env, 0); AudioConnection voice8EnvPatch(voices[8].env, 0, mixer2, 0);
//AudioConnection voice9WavePatch(voices[9].wave, 0, voices[9].env, 0); AudioConnection voice9EnvPatch(voices[9].env, 0, mixer2, 1);
//AudioConnection voice10WavePatch(voices[10].wave, 0, voices[10].env, 0); AudioConnection voice10EnvPatch(voices[10].env, 0, mixer2, 2);
//AudioConnection voice11WavePatch(voices[11].wave, 0, voices[11].env, 0); AudioConnection voice11EnvPatch(voices[11].env, 0, mixer2, 3);
//AudioConnection voice12WavePatch(voices[12].wave, 0, voices[12].env, 0); AudioConnection voice12EnvPatch(voices[12].env, 0, mixer3, 0);
//AudioConnection voice13WavePatch(voices[13].wave, 0, voices[13].env, 0); AudioConnection voice13EnvPatch(voices[13].env, 0, mixer3, 1);
//AudioConnection voice14WavePatch(voices[14].wave, 0, voices[14].env, 0); AudioConnection voice14EnvPatch(voices[14].env, 0, mixer3, 2);
//AudioConnection voice15WavePatch(voices[15].wave, 0, voices[15].env, 0); AudioConnection voice15EnvPatch(voices[15].env, 0, mixer3, 3);

AudioConnection voice0EnvPatch(voices[0].wave, 0, mixer0, 0);
AudioConnection voice1EnvPatch(voices[1].wave, 0, mixer0, 1);
AudioConnection voice2EnvPatch(voices[2].wave, 0, mixer0, 2);
AudioConnection voice3EnvPatch(voices[3].wave, 0, mixer0, 3);
AudioConnection voice4EnvPatch(voices[4].wave, 0, mixer1, 0);
AudioConnection voice5EnvPatch(voices[5].wave, 0, mixer1, 1);
AudioConnection voice6EnvPatch(voices[6].wave, 0, mixer1, 2);
AudioConnection voice7EnvPatch(voices[7].wave, 0, mixer1, 3);
AudioConnection voice8EnvPatch(voices[8].wave, 0, mixer2, 0);
AudioConnection voice9EnvPatch(voices[9].wave, 0, mixer2, 1);
AudioConnection voice10EnvPatch(voices[10].wave, 0, mixer2, 2);
AudioConnection voice11EnvPatch(voices[11].wave, 0, mixer2, 3);
AudioConnection voice12EnvPatch(voices[12].wave, 0, mixer3, 0);
AudioConnection voice13EnvPatch(voices[13].wave, 0, mixer3, 1);
AudioConnection voice14EnvPatch(voices[14].wave, 0, mixer3, 2);
AudioConnection voice15EnvPatch(voices[15].wave, 0, mixer3, 3);

float calculateStela(uint16_t grado, uint16_t arko)
{
  float fgrado = float(grado);
  float farko = float(arko) / 10000;

  return fgrado + farko;
}

float stela = calculateStela(grado, arko);

String tuningBuffer = "";

Koro koro;
Panel panel(koro);
ControllerMode synthMode = poly;
Controller controller(synthMode);

void setup() {
  setupSerial();
  setupMIDI();
  setupI2C();
  setupAudio();
  setupPanel();
  setupKeypad();

  panel.process();
  panel.koro.setShift(panel.encoderACount);
  testTone();
}

void setupSerial()
{
  Serial.begin(9600);

  while(!Serial) {delay(100);}
  Serial.println("Brightwave Organ");
  Serial.println("Setup Serial OK");
}

void setupAudio()
{
  AudioMemory(20);
  codec.enable();
  codec.volume(0.45);    

  AudioProcessorUsageMaxReset();
  AudioMemoryUsageMaxReset();

  leftMixer.gain(0, 0.36);
  leftMixer.gain(1, 0.36);
  leftMixer.gain(2, 0.0);
  leftMixer.gain(3, 0.0);
  
  rightMixer.gain(0, 0.36);
  rightMixer.gain(1, 0.36);
  rightMixer.gain(2, 0.0);
  rightMixer.gain(3, 0.0);

  mixer0.gain(0, 0.75);
  mixer0.gain(1, 0.75);
  mixer0.gain(2, 0.75);
  mixer0.gain(3, 0.75);

  mixer1.gain(0, 0.75);
  mixer1.gain(1, 0.75);
  mixer1.gain(2, 0.75);
  mixer1.gain(3, 0.75);  

  mixer2.gain(0, 0.75);
  mixer2.gain(1, 0.75);
  mixer2.gain(2, 0.75);
  mixer2.gain(3, 0.75);

  mixer3.gain(0, 0.75);
  mixer3.gain(1, 0.75);
  mixer3.gain(2, 0.75);
  mixer3.gain(3, 0.75);
  
  Serial.println("Setup Audio OK");
}

void setupPanel()
{
  panel.lcd.clear();
  panel.lcd.print("Brightwave Organ");
}

void setupI2C()
{
  Wire.begin(); //Join I2C bus  

  Serial.println("Setup I2C OK");    
}

void setupKeypad()
{
  if (!keypad.begin())
  {
    Serial.println("Keypad FAIL");
    return;
  }

  Serial.println("Keypad version:");
  Serial.println(keypad.getVersion());

  Serial.println("Setup Keypad OK");
}

void setupMIDI()
{
  usbMIDI.setHandleNoteOff(handleNoteOff);
  usbMIDI.setHandleNoteOn(handleNoteOn);
  usbMIDI.setHandleAfterTouchPoly(handleAfterTouchPoly);
  usbMIDI.setHandleControlChange(handleControlChange);
  usbMIDI.setHandleProgramChange(handleProgramChange);
  usbMIDI.setHandleAfterTouch(handleAfterTouch);
  usbMIDI.setHandlePitchChange(handlePitchChange);
  usbMIDI.setHandleSystemExclusive(handleSystemExclusiveChunk);
  usbMIDI.setHandleTimeCodeQuarterFrame(handleTimeCodeQuarterFrame);
  usbMIDI.setHandleSongPosition(handleSongPosition);
  usbMIDI.setHandleSongSelect(handleSongSelect);
  usbMIDI.setHandleTuneRequest(handleTuneRequest);
  usbMIDI.setHandleClock(handleClock);
  usbMIDI.setHandleStart(handleStart);
  usbMIDI.setHandleContinue(handleContinue);
  usbMIDI.setHandleStop(handleStop);
  usbMIDI.setHandleActiveSensing(handleActiveSensing);
  usbMIDI.setHandleSystemReset(handleSystemReset);
  usbMIDI.setHandleRealTimeSystem(handleRealTimeSystem);  

  Serial.println("MIDI OK");
}

void loop()
{
  Serial.println("Main Loop");

  panel.process();

  if (panel.retune)
  {
    panel.retune = false;

    // Ignore vento rising/falling on retune.
    Stela tone = panel.koro.vento.getTone(panel.koro.fundamental);

    // FIXME - poly mode
    voices[0].setTone(tone);    

    // If we can hear the retuned note, then it becomes the last note we heard.
    if (panel.gate)
    {
      panel.koro.last = tone;
    }
  }

  if (panel.reratio)
  {
    // When we change the vento, we take into account the vento rising/falling.
    Stela tone = panel.koro.vento.getTone(panel.koro.fundamental);

    // FIXME - poly mode
    voices[0].setTone(tone);    

    // If we can hear the reratioed note, then it becomes the last note we heard.
    if (panel.gate)
    {
      panel.koro.last = tone;
    }    
  }

  if (panel.trigger)
  {
    panel.trigger = false;

    if (panel.gate)
    {
      Stela tone = panel.koro.vento.getTone(panel.koro.fundamental);

      // FIXME - poly mode
      voices[0].setTone(tone);
      voices[0].on();
      panel.koro.last = tone;      
    }
    else
    {
      voices[0].off();
    }
  }
  
  if (panel.tone)
  {
    panel.tone = false;
    testTone();
  }

  usbMIDI.read(); 

  switch (synthMode)
  {
    case mono:
      if (controller.changed[0])
      {
        if (controller.voices[0].on)
        {          
          Stela tone = controller.voices[0].vento.getTone(panel.koro.fundamental);
          
          voices[0].setTone(tone);
          voices[0].on();
        }
        else
        {
          voices[0].off();      
        }
        
        controller.resetChanged();
      }

    case poly:
    { // Curlies requied to allow a variable declaration inside a case    
      for (int index = 0; index < 16; index++)
      {
        if (controller.changed[index])
        {
          if (controller.voices[index].on)
          {
            Stela tone = controller.voices[index].vento.getTone(panel.koro.fundamental);          
            voices[index].setTone(tone);
            voices[index].on();
          }
          else
          {
            voices[index].off();      
          }      
        }  
      }
      
      controller.resetChanged();    
    }
    default:
      return;
  }
}

void setGrado(byte newGrado)
{
  grado = newGrado;
  stela = calculateStela(grado, arko);
}

void setArko(byte newArko)
{
  arko = newArko;
  stela = calculateStela(grado, arko);
}

void modeExitingTuning()
{
//  // Waiting for button to release so that we can push it again to toggle into tuning mode
//  if (!redButton.isPressed())
//  {
//    mode = Play;    
//  }
}

void setExactTuning(String buffer)
{
  float newStela = buffer.toFloat();
  uint16_t newGrado = (uint16_t)newStela;
  float fgrado = (float)newGrado;
  float farko = (newStela - fgrado) * 10000.0;
  uint16_t newArko = farko;

  stela = newStela;
  grado = newGrado;
  arko = newArko;
}

void testTone()
{
  Serial.println("testTone()");

  // We ignore the vento rising/falling for test tones and we do not remember a test tone as the last note we heard.
  voices[0].setTone(panel.koro.getTone());    
  
  voices[0].on();    
  delay(1000);    
  voices[0].off();
}
