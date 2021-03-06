/*
  ==============================================================================

    Granulate.cpp
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/
#include "Granulate.h"
#include "AudioEffect.h"

// Constructor
Granulate::Granulate(){}
void Granulate::processSignal(float *signal, const int numSamples, const int c){
    for (int n = 0; n < numSamples; n++){
        float x = *signal;
        x = processSample(x,c);
        signal[n] = x;
    }
}
float Granulate::processSample(float x, int c){
    
    float y = gain * x;
    
    return y;
    
}

void Granulate::prepare(float newFs){
    Fs = newFs;
}

void Granulate::setGrainSize(float newGrainSize){
    grainSize = newGrainSize;
}

void Granulate::setAlgorithm(float newAlgorithm){
    algorithm = newAlgorithm;
}

void Granulate::setPermutation(float newPermutation){
    permutation = newPermutation;
}

void Granulate::setGainValue(float newGain){
    gain = newGain;
}

float Granulate::smoothFilter(float x, int c){
    x = x;
    return x;
}
