#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <SparkFun_Qwiic_Keypad_Arduino_Library.h>

#include "Panel.h"
#include "Synthesizer.h"
#include "Controller.h"
#include "MIDI.h"

//byte redButtonAddress = 0x5B;
//byte greenButtonAddress = 0x6F;
//
//int redButtonBrightness = 0xFF;
//
//QwiicButton redButton;
//QwiicButton greenButton;

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

AudioMixer4 leftMixer;  AudioConnection leftMixerPatch(leftMixer, 0, output, 0);
AudioMixer4 rightMixer; AudioConnection rightMixerPatch(rightMixer, 0, output, 1);

Voice voice1(WAVEFORM_SINE); AudioConnection voice1WavePatch(voice1.wave, 0, voice1.env, 0); AudioConnection voice1EnvPatch(voice1.env, 0, leftMixer, 0);

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
Controller controller(mono);

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
  codec.volume(0.75);    

  AudioProcessorUsageMaxReset();
  AudioMemoryUsageMaxReset();

  leftMixer.gain(0, 1.0);
  leftMixer.gain(1, 0.0);
  leftMixer.gain(2, 0.0);
  leftMixer.gain(3, 0.0);
  
  rightMixer.gain(0, 1.0);
  rightMixer.gain(1, 1.0);
  rightMixer.gain(2, 1.0);
  rightMixer.gain(3, 1.0);

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
    Stela tone = panel.koro.vento.getStela(panel.koro.fundamental);
    voice1.setTone(tone);    

    // If we can hear the retuned note, then it becomes the last note we heard.
    if (panel.gate)
    {
      panel.koro.last = tone;
    }
  }

  if (panel.reratio)
  {
    // When we change the vento, we take into account the vento rising/falling.
    Stela tone = panel.koro.vento.getTone(panel.koro.fundamental, panel.koro.last);
    voice1.setTone(tone);    

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
      Stela tone = panel.koro.vento.getTone(panel.koro.fundamental, panel.koro.last);
      voice1.setTone(tone);
      panel.koro.last = tone;
      
      voice1.on();
    }
    else
    {
      voice1.off();
    }
  }
  
  if (panel.tone)
  {
    panel.tone = false;
    testTone();
  }

  usbMIDI.read(); 

  if (controller.changed[0])
  {
    if (controller.voices[0].on)
    {
      Stela tone = controller.voices[0].vento.getStela(koro.fundamental);
      voice1.setTone(tone);
      voice1.on();
    }
    else
    {
      voice1.off();      
    }
    
    controller.resetChanged();
  }

  delay(100);
}

void modeStartup()
{
//  if (redButton.isPressed())
//  {
//    redButton.LEDon(redButtonBrightness);
//    mode = StartingTuning;
//  }
//  else
//  {
////    synth.on(0);
//    AudioInterrupts();
//
//    delay(1000);
//
////    synth.off(0);
//  }
}

void modeStartingTuning()
{
//  // Waiting for button to release so that we can push it again to toggle out of tuning mode
//  if (!redButton.isPressed())
//  {
//    tuningBuffer = "";
//    mode = Tuning;    
//  }
}

void modeTuning()
{
//  // Check if the tuning mode button has been toggled, indicating that we should leave tuning mode.
//  if (redButton.isPressed())
//  {
//    mode = ExitingTuning;
//  }
//  else // Do some tuning!
//  {
//    keypad.updateFIFO();  // necessary for keypad to pull button from stack to readable register
//    char button = keypad.getButton();
//    
//    if (button != -1 && button != 0)
//    {
//      if (button == '#')
//      {
//        if (tuningBuffer.length() > 0)
//        {
//          if (tuningBuffer.length() == 2)
//          {
//            tuningBuffer.append("0");
//          }
//          
//          setExactTuning(tuningBuffer);        
//        }
//      }
//      else if (button == '*')
//      {
//        // ???
//      }
//      else // Numeric
//      {
//        tuningBuffer.append(button);
//        if (tuningBuffer.length() == 5)
//        {
//          setExactTuning(tuningBuffer);
//        }
//        else if(tuningBuffer.length() == 1)
//        {
//          // Add decimal point after first digit
//          tuningBuffer.append('.');
//        }
//      }
//    }
//     
//    byte gradoOffset = panel.encoderA.getCount();
//    if (gradoOffset != 0)
//    {
//      byte newGrado = grado + gradoOffset;
//      if (newGrado > 14)
//      {
//        newGrado = 14;
//      }
//  
//      if(newGrado < 1)
//      {
//        newGrado = 1;
//      }
//
//      if (newGrado != grado)
//      {
//        setGrado(newGrado);
//      }
//    }
//
//    byte arkoOffset = panel.encoderB.getCount();
//    if (arkoOffset != 0)
//    {
//      uint16_t newArko = arko + arkoOffset;
//      if (newArko > 10000)
//      {
//        newArko = newArko - 10000;
//      }
//
//      if (newArko < 0)
//      {
//        newArko = newArko + 10000;
//      }
//
//      if (newArko != arko)
//      {
//        setArko(newArko);
//      }
//    }
//  }
}

void modePlay()
{
  
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
  voice1.setTone(panel.koro.getTone());    
  
  voice1.on();    
  delay(1000);    
  voice1.off();
}
