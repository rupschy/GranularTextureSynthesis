/*
  ==============================================================================

    AudioEffect.cpp
    Created: 2 Mar 2021 4:01:32pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "AudioEffect.h"

float AudioEffect::processSample(float x, int c){
    return x;
}

void AudioEffect::processSignal(float *signal, const int numSamples, const int c){
    for (int n = 0; n < numSamples; n++){
        float x = *signal;
        x = processSample(x,c);
        signal[n] = x;
    }
}

void AudioEffect::prepare(float newFs){
    Fs = newFs;
}
