/*
  ==============================================================================

    Granulate.h
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

class Granulate {
    
public:

    //Constructor
    Granulate();
    
    float processSample(float x);
    
    void setGrainSize(float newGrainSize);
    
    void setAlgorithm(float newAlgorithm);

private:

    float grainSize = 128.f;
    
    float algorithm = 1.f; // 1 = Asynchronous 2 = Synchronous 3 = Smart
    
    
};
