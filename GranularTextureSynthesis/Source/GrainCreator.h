/*
  ==============================================================================

    GrainCreator.h
    Created: 29 Mar 2021 2:42:00pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include "AudioEffect.h"
#include <JuceHeader.h>
#include "STFT.h"

class GrainCreator
{
public:
    GrainCreator();
    
    // This function should cut original signal into grains, window them, an store in matrix of dimensions [grainSize,numInputFrames]
    void createGrains(int & grainSize, int & numInputFrames); // needs grainSize & needs numInputFrames
    
    
    
    // This function should take each grain and convert into the frequency domain using STFT.h. It should also randomize the frequency bins for each respective grain. Should output multi-dimensional array of [nfft,mfft,numGrains] dimensions
    // This funciton also converts the multi-dimensional arrays back into the time domain and initializes new grain matrix of length [grainSize,numInputFrames]
    void setSTFTGrains();
    
    // This function will take in the multi-dimensional time-domain array from setSTFTGrains and create a matrix of dimensions [grainSize, framesOut]. this will call each new grain and change their order from permutation created in setPermutationSet()
    void arrangeOutputGrains();
    
    // This function takes the array from arrangeOutputGrains() and will order grains for output per channel
    void outputArray();
    
    
private:
    
    
};
