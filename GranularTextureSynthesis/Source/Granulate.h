/*
  ==============================================================================

    Granulate.h
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include "AudioEffect.h"
#include <JuceHeader.h>
#include "Permutation.h"
#include "GrainCreator.h"



class Granulate : public AudioEffect
{
public:

    //Constructor
    Granulate();
    
    void processSignal(float * signal, const int numSamples, const int c);
    
    float processSample(float x,int c) ;
    
    void setGrainSize(int newGrainSize);
    
    void setAlgorithm(float newAlgorithm);
    
    void prepare(float newFs);
    
    void setPermutation(float newPermutation);
    
    void setGainValue(float newGain);
    
    float smoothFilter(float x, int c);
    
    void setVarianceValue(int newVariance);
    
    
    void splitBuffer(float * leftChannel, float * rightChannel, const int N);
    void splitBuffer(juce::AudioBuffer<float>& buffer);
    
//    int setLenIn(const int newlenIn);
    
    float setFramesOut(float Fs, int grainSize, int N);
    
    // Take in sample, from PProcessor, input into array, fill array, when count to max, then do processing
    void setInputArray(float x, int channel);
    

private:

    int grainSize = 800;
    
    float algorithm = 1.f; // 1 = Asynchronous 2 = Synchronous 3 = Smart
    
    float permutation = {0.f};
    
    float gain = 1.f;
    
    int variance = 0;
    
    // array for reading in buffers from DAW
    static const int arraySize = 262144;
    float inputArray[arraySize][2] = {{0.f}};
    int inputArrayCount = 0;

    
    
    

    
};
