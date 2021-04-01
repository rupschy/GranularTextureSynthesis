/*
  ==============================================================================

    GrainCreator.cpp
    Created: 29 Mar 2021 2:42:00pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "GrainCreator.h"

// starting matrix will be: [1024 x 256]
void GrainCreator::createGrains(int & grainSize, int & numInputFrames){
    // needs both grainSize and numInputFrames from other classes
    
    // feed into matrix. once one line is triggered. Do: windowing of finished line AND take last half of finished line and give to the first half of next line
    
    // index for column and row
    int indexGrainSize = 0; //init max 1024
    int indexGrainNumber = 0; //init max 256
    
}

void GrainCreator::setSTFTGrains(){
    
}



void GrainCreator::arrangeOutputGrains(){
    
}
