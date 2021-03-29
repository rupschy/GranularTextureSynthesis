/*
  ==============================================================================

    Permutation.cpp
    Created: 29 Mar 2021 2:42:29pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "Permutation.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


Permutation::Permutation(){}
int Permutation::setPerm(float framesOut, float numInputFrames){
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
            newPermutation[j] = newPermutation[j] - frameDif;
            if (newPermutation[j] == -1){
                newPermutation[j] = 2;
            }
        }
        else {
            newPermutation[j] = newPermutation[j];
        }
    }


    
    return newPermutation[iFramesOut];
}
