#ifndef _PANEL_H_
#define _PANEL_H_

#include <Wire.h>
#include <SerLCD.h>
#include <SparkFun_Qwiic_Twist_Arduino_Library.h>
#include "SparkFun_Qwiic_Joystick_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_joystick

#include "Stela.h"
#include "Ratio.h"
#include "Audio.h"
#include "Koro.h"
#include "Synthesizer.h"
#include <SparkFun_Qwiic_Button.h>

class Panel
{
  public:
    Panel(Koro koro);
    virtual ~Panel();

    SerLCD lcd;

    int encoderACount = 0;
    bool encoderAPressed = false;
    int encoderBCount = 0;

    bool tone = false;
    bool retune = false;
    bool retuneIsRising = false;
    bool reratio = false;
    bool gate = false;
    bool trigger = false;
    bool octaveLock = true;
    bool centered = true;
    bool rejoy = false;
    bool rising = true;
    bool autotune = false;
    float autotuneHertz = 0.0;

    int horizontal = 0;
    int vertical = 0;

    bool blueArcadeButtonIsPressed = false;
    bool redArcadeButtonIsPressed = false;

    void process();

    Koro koro;

  private:
    int lastUpdate = 0;
    float lastAutoHertz = 0.0;
    
    TWIST encoderA;
    TWIST encoderB;
    TWIST encoderC;    

    int encoderAZero;
    int encoderBZero;
    
    JOYSTICK joystick;
    QwiicButton blueArcadeButton;
    QwiicButton redArcadeButton;
  
    bool joySwapAxes = true;
    bool joyFlipVertical = false;
    bool joyFlipHorizontal = true;
  
    void setupEncoders();
    void setupJoystick();
    void setupButtons();
    void setupDisplay();
    
    void updateEncoders();
    bool updateJoystick();
    void updateDisplay();
    void updateAutotune();

    bool joySoftQuantize();
    bool joyHardQuantize();
};

#endif
