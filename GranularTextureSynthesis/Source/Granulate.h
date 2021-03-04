/*
  ==============================================================================

    Granulate.h
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include "AudioEffect.h"


class Granulate : public AudioEffect
{
public:

    //Constructor
    Granulate();
    
    void processSignal(float * signal, const int numSamples, const int c);
    
    float processSample(float x,int c) ;
    
    void setGrainSize(float newGrainSize);
    
    void setAlgorithm(float newAlgorithm);
    
    void prepare(float newFs);
    
    void setPermutation(float newPermutation);

private:

    float grainSize = 128.f;
    
    float algorithm = 1.f; // 1 = Asynchronous 2 = Synchronous 3 = Smart
    
    float permutation = {0.f};
    
};
