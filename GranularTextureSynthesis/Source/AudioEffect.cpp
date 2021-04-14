/*
  ==============================================================================

    AudioEffect.cpp
    Created: 2 Mar 2021 4:01:32pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "AudioEffect.h"

//float AudioEffect::processMakeupGain(float x, int c){
//    
//    return x;
//}
//
//void AudioEffect::processSignal(float *signal, const int numSamples, const int c){
//    for (int n = 0; n < numSamples; n++){
//        float x = *signal;
//        x = processMakeupGain(x,c);
//        signal[n] = x;
//    }
//}

void AudioEffect::prepare(float newFs){
    Fs = newFs;
}
