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

// Per-Sample Functions
float Granulate::processMakeupGain(float x, int c){
    float y = makeupGainValue * x;
    return y;
}

// Per-Run Functions
void Granulate::prepare(float newFs){
    Fs = newFs;
}
    //Sliders
void Granulate::setVarianceValue(int newVariance){
    varianceValue = newVariance;
    
    if (varianceValue == 1){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);
    }
    if (varianceValue == 2){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    if (varianceValue == 3){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    if (varianceValue == 4){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    if (varianceValue == 5){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    if (varianceValue == 6){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    if (varianceValue == 7){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    if (varianceValue == 8){
        int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
        std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);

    }
    
    
}
void Granulate::setMakeupGainValue(float newGain){
    makeupGainValue = newGain;
}
void Granulate::setWetDryValue(float newWetDryValue){
    wetDryValue = newWetDryValue;
}
    // ComboBoxes
void Granulate::setAlgorithm(int newAlgorithm){
    algorithm = newAlgorithm;
}
void Granulate::setGrainSize(int newGrainSize){
    grainSize = newGrainSize;
}
void Granulate::setOverlap(float newOverlap){
    overlap = newOverlap;

}
    // Buttons
void Granulate::setSmoothState(bool newSmoothState, bool newNotSmoothState){
    smoothState = newSmoothState;
    notSmoothState = newNotSmoothState;
}
//Smoothing filter not implemented
float Granulate::setSmoothFilter(float x, int c){
    x = x;
    return x;
}








//void Granulate::setInputArray(float x, int channel){
//    inputArray[inputArrayCount][channel] = x;
//    inputArrayCount++;
//    if (inputArrayCount >= arraySize){
//        inputArrayCount = 0;
//        // Any other processing functions with array buffer need to be called here.
//    }
//}
float Granulate::setInputMatrix(float x, int channel){
    inputMatrix[indexC][indexR][channel] = x;
    indexR++;
    if (indexR >= matrixR){
        // grain is finished, go to next one.
        indexR = 0;
        indexC++;
        // if a new array is need, initialize array of 1024 and create loop here for single grain creation for freq processing I/e FFT
    }
    if (indexC >= matrixC){
        indexC = 0;
        
    }
    //pass input sample into output buffer
    return inputMatrix[indexC][indexR][channel];
}

void Granulate::setPermParameters(int &grainSize){
    //If Overlap
//    int gHop = floor(grainSize/2);
//    float numInputFrames = (float)floor((arrayLength-grainSize+gHop)/gHop);
//    float outLengthS = 2*(arrayLength/Fs); // Should use Fs not 48000
//    float outLengthN = outLengthS*Fs; // Should use Fs not 48000
//    float framesOut = floor((outLengthN-grainSize+gHop/gHop));
    
    // if no overlap
    int simpleNumInputFrames = floor(inputArrayLength/grainSize);
    int simpleFramesOut = floor(outputArrayLength/grainSize);
    
    int outputArrayIndex[512] = {0};
    if (sizeof(outputArrayIndex) != simpleFramesOut){
        int g = simpleFramesOut;
        outputArrayIndex[g] = {0};
    }
    
    for (int n = 0; n < simpleFramesOut; n++){
        outputArrayIndex[n] = n;
    }
    
    if (simpleNumInputFrames != matrixR){
        simpleNumInputFrames = floor(inputArrayLength/grainSize);
    }
}

void Granulate::setPermutationSet(int & grainSize){
    int simpleNumInputFrames = floor(inputArrayLength/grainSize);
    int simpleFramesOut = floor(outputArrayLength/grainSize);
    
    int outputArrayIndex[512] = {0};
    if (sizeof(outputArrayIndex) != simpleFramesOut){
        int g = simpleFramesOut;
        outputArrayIndex[g] = {0};
    }
    
    int frameDif = abs((int(simpleFramesOut)-(int)simpleNumInputFrames));
    for (int i = 0; i < simpleFramesOut; i++){
        outputArrayIndex[i] = i;
    }
//    Randomization of values within the scale from 0 ==> outFrames
    int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
    std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);
    
//    Change array from 0 -> outFrames to 0 -> numInputFrames
    for (int j = 0; j < simpleFramesOut; j++){
        if (outputArrayIndex[j] > simpleNumInputFrames - 1){
            outputArrayIndex[j] = abs(outputArrayIndex[j] - frameDif);
            if (outputArrayIndex[j] <= -1){
                outputArrayIndex[j] = 0;
            }
        if (outputArrayIndex[j] >= frameDif){
            outputArrayIndex[j] = frameDif - outputArrayIndex[j];
        }
        }
        else {
            outputArrayIndex[j] = outputArrayIndex[j];
        }
    }
}

float Granulate::outputArray(int channel){
     float x = inputMatrix[indexC][outputArrayIndex[indexR]][channel];
    indexR++;
    outIndex++;
    if (indexR >=matrixR){
//        if grain is complete, then move to next one...
        indexR = 0;
        indexC++;
    }
    if (indexC >= matrixC){
        indexC = 0;
    }
    return x;
}
























//Functions unusable for the time being.
//float* Granulate::hanning(int N, short itype){
//       HANNING   Hanning window.
//       HANNING(N) returns the N-point symmetric Hanning window in a column
//       vector.  Note that the first and last zero-weighted window samples
//       are not included.
//
//       HANNING(N,'symmetric') returns the same result as HANNING(N).
//
//       HANNING(N,'periodic') returns the N-point periodic Hanning window,
//       and includes the first zero-weighted window sample.
//
//        itype = 1 --> periodic
//        itype = 0 --> symmetric
//        default itype=0 (symmetric)
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
//    maybe use the same calculation from sorted grainMatrix config
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
