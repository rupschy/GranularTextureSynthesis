/*
  ==============================================================================

    Granulate.cpp
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/
#include "Granulate.h"
#include "AudioEffect.h"
#include <iostream>
#include "AccelerateFFT.h"
using namespace std;

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

float Granulate::setFramesOut(float Fs, int grainSize, int N){
    int gHop = floor(grainSize/2);
    float outLengthS = 2*N;
    float outLengthN = outLengthS*Fs;
    float framesOut = floor((outLengthN-grainSize+gHop)/gHop);
    
    return framesOut;
}



//void Granulate::setInputArray(float x, int channel){
//    inputArray[inputArrayCount][channel] = x;
//    inputArrayCount++;
//    if (inputArrayCount >= arraySize){
//        inputArrayCount = 0;
//        // Any other processing functions with array buffer need to be called here.
//    }
//}


// Functional to create grains but cant work for windowing and setting overlap
void Granulate::setInputMatrix(float x, int channel){
    inputMatrix[inputArrayCount][inputArraySizeCount][channel] = x;
    
//    grainFFTMatrix[arraySize][arrayLengthSize][channel] = AccelerateFFT(x);
    
    inputArrayCount++;
    inputArraySizeCount++;
    
    if (inputArrayCount >= arraySize){
        inputArrayCount = 0;
    }
    if (inputArraySizeCount >= arrayLengthSize){
//        inputMatrix[inputArrayCount][inputArraySizeCount][channel];
        inputArraySizeCount = 0;
//        Other processing should be done here
    }
    loopCount = loopCount + 1;
    if (int loopCount = arrayLength){
        
    }
}

// What steps left?
// 1. Split audio buffers per channel into grains either by analysis or by grainSize
// 2. Compute moving average filtering in boolean function in PProcessor.cpp
// 3. convert grains into frequency domain for further processing
// 4. Find permutation and calculate number of grains needed???? Maybe not....
            // Maybe base this off of the entire length of N? that may be based from the DAW though...
// 5. Do frequency shift from .getSize(). Maybe further frequency processing. This could be where the neural network could process??
// 6. Convert back to time domain istft etc
// 7. Get order from permutation matrix for re-implementation into output per channel



// New Functions in order of operation
//_______________________________________________________________________________
void Granulate::setPermParameters(int grainSize, int lenInN){
    int gHop = floor(grainSize/2);
    float numInputFrames = (float)floor((lenInN-grainSize+gHop)/gHop);
    
    
    float outLengthS = 2*(lenInN/48000.f); // Should use Fs not 48000
    float outLengthN = outLengthS*48000.f; // Should use Fs not 48000
    float framesOut = floor((outLengthN-grainSize+gHop/gHop));
}

int Granulate::setPermutationSet(int permutationSet, float framesOut, float numInputFrames, int grainSize){
    // Initialize parameters for boolean to augment permutation
    int frameDif = abs((int(framesOut)-(int)numInputFrames));
    int newPermutation[(int)framesOut];
    for (int i = 0; i < framesOut; i++){
        newPermutation[i] = i;
    }
//    Randomization of values within the scale from 0 -> outFrames
    int sizePerm = sizeof(newPermutation)/sizeof(newPermutation[0]);
    std::random_shuffle(newPermutation,newPermutation+sizePerm);
    
//    Change array from 0 -> outFrames to 0 -> numInputFrames
    for (int j = 0; j < framesOut; j++){
        if (newPermutation[j] > numInputFrames){
            newPermutation[j] = abs(newPermutation[j] - frameDif);
            if (newPermutation[j] == -1){
                newPermutation[j] = 0;
            }
        }
        else {
            newPermutation[j] = newPermutation[j];
        }
    }
    
    
    
    return newPermutation[(int)framesOut];
}


void Granulate::setGrainMatrix(float x, int channel, int** matrix, int rows, int cols, int * src, int src_size){
    int pos = 0;
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            matrix[i][j] = src[pos++];
        }
    }
}
