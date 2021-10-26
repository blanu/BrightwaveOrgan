#include <Arduino.h>
#include "Panel.h"

Panel::Panel(Koro koro): koro(koro)
{ 
  Serial.println("Panel constructor");

  setupEncoders();
  setupJoystick();
  setupButtons();
  setupDisplay();

  process();
  
  updateDisplay();
  updateEncoders();
}

Panel::~Panel()
{
}

void Panel::setupDisplay()
{
  lcd.begin(Wire);
  lcd.setBacklight(255, 255, 255);
  lcd.setContrast(5);  
    
  lcd.clear();      
}

void Panel::setupEncoders()
{
  if (!encoderA.begin())
  {
    Serial.println("Encoder A FAIL");
    return;
  }

  if (!encoderB.begin())
  {
    Serial.println("Encoder B FAIL");
    return;
  }

  if (!encoderC.begin())
  {
    Serial.println("Encoder C FAIL");
    return;
  }

  Serial.println("Setup Encoders OK");  
}

void Panel::setupJoystick()
{
  if (!joystick.begin())
  {
    Serial.println("Joystick FAIL");
    return;
  }
}

void Panel::setupButtons()
{
  if (!blueArcadeButton.begin(0x6E))
  {
    Serial.println("Blue arcade button FAIL");
    return;
  }

  if (!redArcadeButton.begin(0x6F))
  {
    Serial.println("Red arcade button FAIL");
    return;
  }

  Serial.println("Buttons OK");
}

void Panel::process()
{  
  bool update = false;
  tone = false;
  retune = false;
  reratio = false;
  rejoy = false;
  
  int newCount = encoderA.getCount();
  if (newCount != encoderACount)
  {
    update = true;
    retune = true;    
    
    if (newCount > encoderACount)
    {
      retuneIsRising = true;
    }
    else
    {
      retuneIsRising = false;
    }
    
    encoderACount = newCount;

    koro.setShift(encoderACount);
  }

  bool newEncoderAPressed = encoderA.isPressed(); 
  if (newEncoderAPressed != encoderAPressed)
  {
    update = true;
    encoderAPressed = newEncoderAPressed;

    if (encoderAPressed)
    {
      tone = true;
    }
  }

  int newHorizontal = joystick.getHorizontal();
  int newVertical = joystick.getVertical();

  if (joySwapAxes)
  {
    int temp = newHorizontal;
    newHorizontal = newVertical;
    newVertical = temp;
  }
  
  if (newHorizontal != horizontal)
  {
    rejoy = true;
    horizontal = newHorizontal;
  }
  
  if (newVertical != vertical)
  {
    rejoy = true;
    vertical = newVertical;
  }

  if (joystick.checkButton())
  {
    update = true;
    octaveLock = !octaveLock;
  }

  bool newBlueArcadeButtonIsPressed = blueArcadeButton.isPressed();
  if (newBlueArcadeButtonIsPressed != blueArcadeButtonIsPressed)
  {
    blueArcadeButtonIsPressed = newBlueArcadeButtonIsPressed;
    
    update = true;
    trigger = true;
    gate = blueArcadeButtonIsPressed;
  }

  bool newRedArcadeButtonIsPressed = redArcadeButton.isPressed();
  if (newRedArcadeButtonIsPressed != redArcadeButtonIsPressed)
  {
    redArcadeButtonIsPressed = newRedArcadeButtonIsPressed;
    
    update = true;
    trigger = true;
    gate = redArcadeButtonIsPressed;
  }

  if (rejoy)
  {
    reratio = updateJoystick();
    if (reratio)
    {
      update = true;
    }
  }

  if (update)
  {
    updateDisplay();
    updateEncoders();
  }
}

void Panel::updateDisplay()
{
  lcd.clear();
  lcd.print("Brightwave Organ");    
  
  lcd.setCursor(0, 1);
  lcd.print("Stela ");
  lcd.print(koro.fundamental.getStela());
  lcd.print(" ");
  lcd.print("Hz ");
  lcd.print(int(koro.fundamental.hertz));  

  Ratio ratio = koro.vento.getRatio();
  lcd.setCursor(0, 2);
//  lcd.print("Vento ");
//  lcd.print(koro.vento.tri);
//  lcd.print(" ");
//  lcd.print(koro.vento.kvin);
  lcd.print("Ratio ");
  lcd.print(ratio.numerator);
  lcd.print(" ");
  lcd.print(ratio.denominator);

  Stela tone = koro.vento.getTone(koro.fundamental);
  lcd.setCursor(11, 2);
  lcd.print("Hz");
  lcd.setCursor(14, 2);
  lcd.print(int(tone.hertz));

  lcd.setCursor(0, 3);
  if (encoderAPressed)
  {
    lcd.print("X");    
  }
  else
  {
    lcd.print("O");
  }

  if (blueArcadeButtonIsPressed)
  {
    lcd.print("X");        
  }
  else
  {
    lcd.print("O");    
  }

  if (octaveLock)
  {
    lcd.setCursor(16, 3);
    lcd.print("Lock");
  }
}

void Panel::updateEncoders()
{
  float toneMin = 5.0;
  float toneMax = 9.0;
  
  float tone = koro.fundamental.getStela(); // unsigned float 5.0-12.0
  if (tone < toneMin)
  {
    tone = toneMin;
  }

  if (tone > toneMax)
  {
    tone = toneMax;
  }
  
  float toneRange = toneMax - toneMin;
  float colorRange = 255.0;
  int colorMax = 255;
  float color = ((tone - toneMin) / toneRange) * colorRange;
  int quantizedColor = int(color);
  
  int blueLevel = quantizedColor;
  int redLevel = colorMax - blueLevel;
  int greenColor = 0;
  if (encoderAPressed)
  {
    greenColor = 255;
  }
  
  encoderA.setColor(redLevel, greenColor, blueLevel); //Set Red and Blue LED brightnesses to half of max.
}

bool Panel::updateJoystick()
{
//  return joySoftQuantize();
  return joyHardQuantize();
}

bool Panel::joySoftQuantize()
{
  return false;
  
//  int lower = 0;
//  int upper = 1023;
//  int center = upper / 2;
//  int lowerThird = upper / 3;
//  int upperThird = lowerThird * 2;
//  int centerLower = center - 5;
//  int centerUpper = center + 5;
//
//  int tuningX = 0;
//  int tuningY = 0;
//
//  Ratio oldRatio = koro.getRatio();

//  if (horizontal > upperThird)
//  {
//    // right side
//    if (vertical > upperThird)
//    {
//      // top right - 15/8
//      if (horizontal == upper || vertical == upper) // snap
//      {
//        tuningX = 1;
//        tuningY = 1;
//      }
//      else
//      {
//        tuningX = 0;
//        tuningY = 0;
//      }
//    }
//    else if (vertical > lowerThird)
//    {
//      // right - 3/2
//      if (horizontal == upper) // snap
//      {
//        tuningX = 1;
//        tuningY = 0;
//      }
//      else
//      {
//        tuningX = 0;
//        tuningY = 0;
//      }      
//    }
//    else
//    {
//      // lower right - 6/5
//      if ((horizontal == upper) || (vertical == lower)) // snap
//      {
//        tuningX = 2;
//        tuningY = 2;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }            
//    }
//  }
//  else if (horizontal > lowerThird)
//  {
//    // middle column
//    if (vertical > upperThird)
//    {
//      // top side - 5/4
//      if (vertical == upper) // snap
//      {
//        tuningX = 1;
//        tuningY = 0;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }          
//    }
//    else if (vertical > lowerThird)
//    {
//      // center - 1/1
//      if ((horizontal >= centerLower) && (horizontal <= centerUpper) && (vertical >= centerLower) && (vertical <= centerUpper)) // snap
//      {
//        tuningX = 1;
//        tuningY = 1;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }                
//    }
//    else
//    {
//      // bottom side - 8/5
//      if (vertical == lower) // snap
//      {
//        tuningX = 1;
//        tuningY = 2;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }                
//    }
//  }
//  else
//  {
//    // left side
//    if (vertical > upperThird)
//    {
//      // top left - 5/3
//      if (horizontal == lower || vertical == upper) // snap
//      {
//        tuningX = 0;
//        tuningY = 0;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }          
//    }
//    else if (vertical > lowerThird)
//    {
//      // left side - 4/3
//      if (horizontal == lower) // snap
//      {
//        tuningX = 0;
//        tuningY = 1;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }                
//    }
//    else
//    {
//      // bottom left - 16/15
//      if (horizontal == lower || vertical == lower) // snap
//      {
//        tuningX = 0;
//        tuningY = 2;
//      }
//      else
//      {
//        // FIXME
//        tuningX = 1;
//        tuningY = 1;
//      }                      
//    }
//  }

//  koro.tone.shiftTri(tuningX);
//  koro.tone.shiftKvin(tuningY);
//
//  if (octaveLock)
//  {
//    Ratio newRatio = koro.lockedTuning[tuningY][tuningX];
//    koro.setRatio(newRatio.numerator, newRatio.denominator);
//    return (oldRatio.numerator != newRatio.numerator) || (oldRatio.denominator != newRatio.denominator);
//  }
//  else
//  {
//    Ratio newRatio = koro.unlockedTuning[tuningY][tuningX];
//    koro.setRatio(newRatio.numerator, newRatio.denominator);
//    return (oldRatio.numerator != newRatio.numerator) || (oldRatio.denominator != newRatio.denominator);    
//  }
}

bool Panel::joyHardQuantize()
{
  int lower = 0;
  int upper = 1023;
  int center = upper / 2;
  int centerLower = center - 5;
  int centerUpper = center + 5;

  int tri = 0;
  int kvin = 0;

  if (centered)
  {
    if (horizontal == lower)
    {
      centered = false;
      tri = -1;    
    }
    else if (horizontal == upper)
    {
      centered = false;
      tri = 1;
    }

    if (vertical == lower)
    {
      centered = false;
      kvin = -1;      
    }
    else if (vertical == upper)
    {
      centered = false;
      kvin = 1;
    }
  }
  else if ((horizontal >= centerLower) && (horizontal <= centerUpper) && (vertical >= centerLower) && (vertical <= centerUpper)) // snap
  {
    centered = true;
  }

  bool changed = (tri != 0) || (kvin != 0);
  if (changed)
  {
    koro.vento.shiftTri(tri);
    koro.vento.shiftKvin(kvin);    
  }

  return changed;
}
