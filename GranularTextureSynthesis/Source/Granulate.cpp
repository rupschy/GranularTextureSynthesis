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

float Granulate::setSmoothFilter(float x, int c){
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
























//float* Granulate::hanning(int N, short itype){
////       HANNING   Hanning window.
////       HANNING(N) returns the N-point symmetric Hanning window in a column
////       vector.  Note that the first and last zero-weighted window samples
////       are not included.
////
////       HANNING(N,'symmetric') returns the same result as HANNING(N).
////
////       HANNING(N,'periodic') returns the N-point periodic Hanning window,
////       and includes the first zero-weighted window sample.
////
////        itype = 1 --> periodic
////        itype = 0 --> symmetric
////        default itype=0 (symmetric)
//        int half, i, idx, n;
//        float *w;
//        w = (float*) calloc(N, sizeof(float));
//        memset(w, 0, N*sizeof(float));
//        if(itype==1)    //periodic function
//            n = N-1;
//        else
//            n = N;
//        if(n%2==0)
//        {
//            half = n/2;
//            for(i=0; i<half; i++) //CALC_HANNING   Calculates Hanning window samples.
//                w[i] = 0.5 * (1 - cos(2*M_PI*(i+1) / (n+1)));
//            idx = half-1;
//            for(i=half; i<n; i++) {
//                w[i] = w[idx];
//                idx--;
//            }
//        }
//        else
//        {
//            half = (n+1)/2;
//            for(i=0; i<half; i++) //CALC_HANNING   Calculates Hanning window samples.
//                w[i] = 0.5 * (1 - cos(2*M_PI*(i+1) / (n+1)));
//            idx = half-2;
//            for(i=half; i<n; i++) {
//                w[i] = w[idx];
//                idx--;
//            }
//        }
//        if(itype==1)    //periodic function
//        {
//            for(i=N-1; i>=1; i--)
//                w[i] = w[i-1];
//            w[0] = 0.0;
//        }
//        return(w);
//}
//float Granulate::mAverage(float x, int channel){
//    const int size = 1024;
//    int l_size = 16;
//    float sum = 0.f;
//    float mAvg = 0.f; // should be an array of values not a global average
////    maybe use the same calculation from sorted grainMatrix config
//    for (int i = 0; i <= (size - l_size); i++){
//        sum = 0;
//
//        for (int j = 0; j < i + l_size; j++){
//            sum += x; // x needs to be the full grain of 1024 samples
//        }
//
//        mAvg = sum/l_size;
//    }
//    return mAvg;
//}

