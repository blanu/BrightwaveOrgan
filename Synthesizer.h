#ifndef _SYNTHESIZER_H_
#define _SYNTHESIZER_H_

#include "Stela.h"
#include "Ratio.h"
#include "Audio.h"
#include "Voice.h"
#include "Koro.h"

class Synthesizer
{
  public:
    Synthesizer(Koro koro);
    virtual ~Synthesizer();

    void setupMixer();
    void on(int voice);
    void off(int voice);

  private:
    Koro koro;
  
    Ratio unu = Ratio(1, 1);
        
//    Voice voice1;
//    Voice voice2 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice3 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice4 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice5 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice6 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice7 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice8 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice9 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice10 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice11 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice12 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice13 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice14 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice15 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice voice16 = Voice(WAVEFORM_SINE, &start, &unu);
//    Voice *voices[16] = {
//      &voice1, &voice2, &voice3, &voice4, 
//      &voice5, &voice6, &voice7, &voice8, 
//      &voice9, &voice10, &voice11, &voice12, 
//      &voice13, &voice14, &voice15, &voice16
//    };

//    // Create 16 waveforms, one for each MIDI channel
//    AudioSynthWaveform sine0, sine1, sine2, sine3;
//    AudioSynthWaveform sine4, sine5, sine6, sine7;
//    AudioSynthWaveform sine8, sine9, sine10, sine11;
//    AudioSynthWaveform sine12, sine13, sine14, sine15;
//    AudioSynthWaveform *waves[16] = {
//      &sine0, &sine1, &sine2, &sine3,
//      &sine4, &sine5, &sine6, &sine7,
//      &sine8, &sine9, &sine10, &sine11,
//      &sine12, &sine13, &sine14, &sine15
//    };
//    
//    AudioEffectEnvelope env1, env2, env3;
//    AudioEffectEnvelope env4, env5, env6, env7;
//    AudioEffectEnvelope env8, env9, env10, env11;
//    AudioEffectEnvelope env12, env13, env14, env15;
//    AudioEffectEnvelope *envs[16] = {
//      &voices[0]->env, &env1, &env2, &env3,
//      &env4, &env5, &env6, &env7,
//      &env8, &env9, &env10, &env11,
//      &env12, &env13, &env14, &env15
//    };
//    
//    AudioConnection voice1Patch;
//    AudioConnection patchCord02 = AudioConnection(sine1, env1);
//    AudioConnection patchCord03 = AudioConnection(sine2, env2);
//    AudioConnection patchCord04 = AudioConnection(sine3, env3);
//    AudioConnection patchCord05 = AudioConnection(sine4, env4);
//    AudioConnection patchCord06 = AudioConnection(sine5, env5);
//    AudioConnection patchCord07 = AudioConnection(sine6, env6);
//    AudioConnection patchCord08 = AudioConnection(sine7, env7);
//    AudioConnection patchCord09 = AudioConnection(sine8, env8);
//    AudioConnection patchCord10 = AudioConnection(sine9, env9);
//    AudioConnection patchCord11 = AudioConnection(sine10, env10);
//    AudioConnection patchCord12 = AudioConnection(sine11, env11);
//    AudioConnection patchCord13 = AudioConnection(sine12, env12);
//    AudioConnection patchCord14 = AudioConnection(sine13, env13);
//    AudioConnection patchCord15 = AudioConnection(sine14, env14);
//    AudioConnection patchCord16 = AudioConnection(sine15, env15);
//    
//    AudioMixer4 mixer1;
//    AudioMixer4 mixer2;
//    AudioMixer4 mixer3;
//    AudioMixer4 mixer4;
//    
//    AudioConnection patchCord17 = AudioConnection(voices[0]->env, 0, mixer1, 0);
//    AudioConnection patchCord18 = AudioConnection(env1, 0, mixer1, 1);
//    AudioConnection patchCord19 = AudioConnection(env2, 0, mixer1, 2);
//    AudioConnection patchCord20 = AudioConnection(env3, 0, mixer1, 3);
//    AudioConnection patchCord21 = AudioConnection(env4, 0, mixer2, 0);
//    AudioConnection patchCord22 = AudioConnection(env5, 0, mixer2, 1);
//    AudioConnection patchCord23 = AudioConnection(env6, 0, mixer2, 2);
//    AudioConnection patchCord24 = AudioConnection(env7, 0, mixer2, 3);
//    AudioConnection patchCord25 = AudioConnection(env8, 0, mixer3, 0);
//    AudioConnection patchCord26 = AudioConnection(env9, 0, mixer3, 1);
//    AudioConnection patchCord27 = AudioConnection(env10, 0, mixer3, 2);
//    AudioConnection patchCord28 = AudioConnection(env11, 0, mixer3, 3);
//    AudioConnection patchCord29 = AudioConnection(env12, 0, mixer4, 0);
//    AudioConnection patchCord30 = AudioConnection(env13, 0, mixer4, 1);
//    AudioConnection patchCord31 = AudioConnection(env14, 0, mixer4, 2);
//    AudioConnection patchCord32 = AudioConnection(env15, 0, mixer4, 3);
//    
    
//    
//    AudioConnection patchCord33 = AudioConnection(mixer1, 0, mixerLeft, 0);
//    AudioConnection patchCord34 = AudioConnection(mixer2, 0, mixerLeft, 1);
//    AudioConnection patchCord35 = AudioConnection(mixer3, 0, mixerLeft, 2);
//    AudioConnection patchCord36 = AudioConnection(mixer4, 0, mixerLeft, 3);
//    AudioConnection patchCord37 = AudioConnection(mixer1, 0, mixerRight, 0);
//    AudioConnection patchCord38 = AudioConnection(mixer2, 0, mixerRight, 1);
//    AudioConnection patchCord39 = AudioConnection(mixer3, 0, mixerRight, 2);
//    AudioConnection patchCord40 = AudioConnection(mixer4, 0, mixerRight, 3);
//    
//    AudioConnection          patchCord41 = AudioConnection(mixerLeft, 0, audioOut, 0);
//    AudioConnection          patchCord42 = AudioConnection(mixerRight, 0, audioOut, 1);    
};

#endif
