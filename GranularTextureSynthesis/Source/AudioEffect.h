/*
  ==============================================================================

    AudioEffect.h
    Created: 2 Mar 2021 4:01:32pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

class AudioEffect{
public:
//    virtual float processMakeupGain(float x, int c) = 0;
//    
//    virtual void processSignal(float * signal, const int numSamples, const int c)= 0;
//    
    void prepare(float newFs);
    
protected:
    float Fs;
    
private:
    
};
