/*
  ==============================================================================

    GrainCreator.cpp
    Created: 29 Mar 2021 2:42:00pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "GrainCreator.h"
#include "STFT.h"

// starting matrix will be: [1024 x 256]
void GrainCreator::createGrains(int & grainSize, int & numInputFrames){
    // needs both grainSize and numInputFrames from other classes
    
    // feed into matrix. once one line is triggered. Do: windowing of finished line AND take last half of finished line and give to the first half of next line
    
    // index for column and row
    int indexGrainSize = 0; //init max 1024
    int indexGrainNumber = 0; //init max 256

    
}


void GrainCreator::setGrainMatrix(float x){
    int grainHop = grainLength/2;
    grainMatrix[indexGrainSize][indexGrainNumber] =x;
    indexGrainSize++;
    if (indexGrainSize >= grainLength){
        grainMatrix[indexGrainSize-grainHop][indexGrainNumber] = grainMatrix[indexGrainSize-indexGrainSize][indexGrainNumber+1];
        
        indexGrainNumber++;
        
        indexGrainSize = 0;
        
        
        
        
//        for (unsigned int i = 0; i < sizeof(grainMatrix)/sizeof(grainMatrix[0]); i++){
//            for (unsigned int j = 0; j < sizeof(grainMatrix[0])/sizeof(float); j++){
//                grainMatrix[i][j] = x;
//            }
//        }
    }
}

void GrainCreator::setSTFTGrains(float x){
//    Use STFT here
    float X = STFT(float x);
}




// should use  & newPermutation?
void GrainCreator::arrangeOutputGrains(){
//    Use newPermutation here to re-order grains accordingly

    
}
