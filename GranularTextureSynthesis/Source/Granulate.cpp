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
        float x = signal[n]; // get value at memory location
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

void Granulate::setGrainSize(int newGrainSize){
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

void Granulate::setVarianceValue(int newVariance){
    variance = newVariance;
}





void Granulate::splitBuffer(float * leftChannel, float * rightChannel,  const int N){
    for (int n = 0; n < N; n++){
        float L = leftChannel[n];
        float R = rightChannel[n];
        
    }
    
}

void Granulate::splitBuffer(juce::AudioBuffer<float>& buffer){
    float * leftChannel = buffer.getWritePointer(0);
    float * rightChannel = buffer.getWritePointer(1);
    int N = buffer.getNumSamples();
    splitBuffer(leftChannel, rightChannel, N);
    
};







// What steps left?
// 1. Split audio buffers per channel into grains either by analysis or by grainSize
// 2. Compute moving average filtering in boolean function in PProcessor.cpp
// 3. convert grains into frequency domain for further processing
// 4. Find permutation and calculate number of grains needed???? Maybe not....
            // Maybe base this off of the entire length of N? that may be based from the DAW though...
// 5. Do frequency shift from .getSize(). Maybe further frequency processing. This could be where the neural network could process??
// 6. Convert back to time domain istft etc
// 7. Get order from permutation matrix for re-implementation into output per channel
