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

#include "AccelerateFFT.h"



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
    
    float setSmoothFilter(float x, int c);
    float mAverage(float x, int channel);
    
//    void setVarianceValue(int newVariance);
    
    
//    void splitBuffer(float * leftChannel, float * rightChannel, const int N);
//    void splitBuffer(juce::AudioBuffer<float>& buffer);
    
//    int setLenIn(const int newlenIn);
    
//    float setFramesOut(float Fs, int grainSize, int N);
    
    // Take in sample, from PProcessor, input into array, fill array, when count to max, then do processing
    void setInputArray(float x, int channel);
    void setInputMatrix(float x, int channel);
    
    
    
    // Permutation functions
    //_______________________________________________________________________________________________________
    //    sets parameters for use in later functions in/out of class
    void setPermParameters(int grainSize, int lenInN);
    
    void setPermutationSet(int & grainSize);
    
    
    
    
    // grainCreation functions
    //_______________________________________________________________________________________________________
    // This function should cut original signal into grains, window them, an store in matrix of dimensions [grainSize,numInputFrames]
//    void createGrains(int & grainSize, int & numInputFrames); // needs grainSize & needs numInputFrames
    
//    void setGrainMatrix(float x, int channel, int** matrix, int rows, int cols, int * src, int src_size);
    
    // This function should take each grain and convert into the frequency domain using STFT.h. It should also randomize the frequency bins for each respective grain. Should output multi-dimensional array of [nfft,mfft,numGrains] dimensions
    // This funciton also converts the multi-dimensional arrays back into the time domain and initializes new grain matrix of length [grainSize,numInputFrames]
//    void setSTFTGrains(float x);
    
    // This function will take in the multi-dimensional time-domain array from setSTFTGrains and create a matrix of dimensions [grainSize, framesOut]. this will call each new grain and change their order from permutation created in setPermutationSet()
    void arrangeOutputGrains();
    
    // This function takes the array from arrangeOutputGrains() and will order grains for output per channel
    float outputArray(float x, int channel);
    
    
    
    
    
    
    float* hanning(int N, short itype);


private:

    int grainSize = 1024;
    
    float algorithm = 1.f; // 1 = Asynchronous 2 = Synchronous 3 = Smart
    
    float permutation = {0.f};
    
    float gain = 1.f;
    
    int variance = 0;
    
    // array for reading in buffers from DAW
//    static const int arraySize = 262144;
//    float inputArray[arraySize][2] = {{0.f}};
//    int inputArrayCount = 0;
    
    
    static const int matrixR = 256;
    int indexR = 0; // grain number
    static const int matrixC = 1024;
    int indexC = 0; // grain length
    

    
    float inputMatrix[matrixC][matrixR][2] = {0.f};
    
    // Permutation functions
    //_______________________________________________________________________________________________________
    float framesOut;
    float numInputFrames;
    int simpleNumInputFrames = 256;
    int simpleFramesOut = 512;
    
    // grainCreation functions
    static const int inputArrayLength = 262144;
    static const int outputArrayLength = 2*inputArrayLength;
    
    int outputArrayIndex[512] = {0};
    
    float outputArrayF[outputArrayLength][2] = {0.f};
    
    //Output index initialization
    int oMatrixR = floor(outputArrayLength/grainSize);
    int oIndexR = 0;
    int oMatrixC = floor(outputArrayLength/simpleFramesOut);
    int oIndexC = 0;
    int outIndex = 0;
    
    
//
};
