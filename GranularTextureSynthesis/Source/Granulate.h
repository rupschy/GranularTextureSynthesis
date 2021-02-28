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

private:

    float grainSize = 128.f;
};
