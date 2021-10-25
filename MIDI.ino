void handleNoteOff(byte channel, byte note, byte velocity)
{
  controller.handleNoteOff(channel, note, velocity);
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
  controller.handleNoteOn(channel, note, velocity);
  panel.lcd.clear();
  panel.lcd.print("NoteOn ");
  panel.lcd.print(channel);
  panel.lcd.print(" ");
  panel.lcd.print(note);
  panel.lcd.print(" ");
  panel.lcd.print(velocity);
}

void handleAfterTouchPoly(byte channel, byte note, byte velocity)
{
  controller.handleAfterTouchPoly(channel, note, velocity);
}

void handleControlChange(byte channel, byte control, byte value)
{
  controller.handleControlChange(channel, control, value);
}

void handleProgramChange(byte channel, byte program)
{
  controller.handleProgramChange(channel, program);
}

void handleAfterTouch(byte channel, byte pressure)
{
  controller.handleAfterTouch(channel, pressure);
}

void handlePitchChange(byte channel, int pitch)
{
  controller.handlePitchChange(channel, pitch);
}

void handleSystemExclusiveChunk(const byte *data, uint16_t length, bool last)
{
  controller.handleSystemExclusiveChunk(data, length, last);
}

void handleSystemExclusive(byte *data, unsigned int length)
{
  controller.handleSystemExclusive(data, length);
}

void handleTimeCodeQuarterFrame(byte data)
{
  controller.handleTimeCodeQuarterFrame(data);
}

void handleSongPosition(uint16_t beats)
{
  controller.handleSongPosition(beats);
}

void handleSongSelect(byte songNumber)
{
  controller.handleSongSelect(songNumber);
}

void handleTuneRequest()
{
  controller.handleTuneRequest();
}

void handleClock()
{
  controller.handleClock();
}

void handleStart()
{
  controller.handleStart();
}

void handleContinue()
{
  controller.handleContinue();
}

void handleStop()
{
  controller.handleStop();
}

void handleActiveSensing()
{
  controller.handleActiveSensing();
}

void handleSystemReset()
{
  controller.handleSystemReset();
}

void handleRealTimeSystem(byte realtimebyte)
{
  controller.handleRealTimeSystem(realtimebyte);
}
