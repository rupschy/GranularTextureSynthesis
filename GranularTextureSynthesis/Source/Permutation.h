/*
  ==============================================================================

    Permutation.h
    Created: 29 Mar 2021 2:42:29pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include "AudioEffect.h"
#include <JuceHeader.h>

class Permutation
{
public:
    Permutation();

//    sets parameters for use in later functions in/out of class
    void setParameters(int & grainSize, int & lenInN);
    
    int setPermutationSet(int permutationSet, float framesOut, float numInputFrames, int grainSize);
    
protected:
    float framesOut;
    float numInputFrames;
    
private:
    
    
    
};
