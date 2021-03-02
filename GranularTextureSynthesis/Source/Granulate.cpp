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
void Granulate::processSignal(float * signal, const int numSamples, const int c){
    for (int n = 0; n < numSamples; n++){
        float x = *signal;
        x = processSample(x,c);
        signal[n] = x;
    }
}
float Granulate::processSample(float x, int c){
    
    float y = x;
    
    return y;
    
}

void Granulate::setGrainSize(float newGrainSize){
    grainSize = newGrainSize;
}

void Granulate::setAlgorithm(float newAlgorithm){
    algorithm = newAlgorithm;
}
