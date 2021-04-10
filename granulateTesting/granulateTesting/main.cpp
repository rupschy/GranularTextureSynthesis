//
//  main.cpp
//  granulateTesting
//
//  Created by John Rupsch on 4/5/21.
//

#include <iostream>
#include <cmath>


int main() {

    int arrayS = 32;
    int outArrayS = 64;
    int* k = 0;
    int array[32] = {0};
    int outArrayIndex[8] = {0};
    int simpleNumInputFrames = 32/8;
    int simpleFramesOut = 64/8;
    int frameDif = abs(simpleFramesOut- simpleNumInputFrames);

    int outArray[64] = {0};
    
    for (int n = 0; n < 32; n++){
        array[n] = n;
    }

    for (int n = 0; n < 8; n++){
        outArrayIndex[n] = n;
    }
    
    int size = sizeof(array)/(sizeof(array[0]));
    std::random_shuffle(array,array+size);
    
    for (int j = 0; j < simpleFramesOut; j++){
        // *** added -1 to line below for 2*input size
        if (outArrayIndex[j] > simpleNumInputFrames-1){
            outArrayIndex[j] = outArrayIndex[j] - frameDif;
            if (outArrayIndex[j] <= -1){
                outArrayIndex[j] = 0;
            }
        if (outArrayIndex[j] >= frameDif){
            outArrayIndex[j] = frameDif - outArrayIndex[j];
        }
        }
        else {
            outArrayIndex[j] = outArrayIndex[j];
        }
    }
    
    int oSize = sizeof(outArrayIndex)/sizeof(outArrayIndex[0]);
    std::random_shuffle(outArrayIndex,outArrayIndex+oSize);

    
    int matrixR = 4; //indexCount
    int indexR = 0; // indexCount
    int matrixC = 8; // grainLength
    int indexC = 0; // grainLength
    int matrix[8][4] = {0};
    // FUNCTIONAL
    for (int k = 0; k < arrayS; ++k){
        // no loop, k just turns into x.
        matrix[indexC][indexR] = array[k];
        indexR++;
        if (indexR >= matrixR){
            // grain is finished, go to the next column
            indexR = 0;
            indexC++;
//             if new array needed, initialize above and create loop for single grain here
        }
        if (indexC >= matrixC){
            indexC = 0;
        }
    }
    
    
    
    
    
    

    
    // creating output
    //fill array inside from matrix
    for (int k =0; k<outArrayS; ++k){
        //randomize indexes
        //change randArray[k] into x.
        
        
        outArray[k] = matrix[outArrayIndex[indexC]][indexR];
        indexR++;
        if (indexR >=matrixR){
            indexR = 0;
            indexC++;
        }
        if (indexC >= matrixC){
            indexC = 0;
        }
    }
    
    
    
    return 0;
}



    
//int main () {
//  int numbers[]={1,2,3,4,5};
//  int remainders[5];
//  std::transform (numbers, numbers+5, remainders, std::bind2nd(std::modulus<int>(),2));
//  for (int i=0; i<5; i++)
//    std::cout << numbers[i] << " is " << (remainders[i]==0?"even":"odd") << '\n';
//  return 0;
//}
    
//    int m1_src[] = {1,2,3,4};
//    int m1_rows = 2, m1_cols = 2;
//    int** m1 = generateMatrix(m1_rows, m1_cols);
//    populateMatrix(m1,m1_rows, m1_cols, m1_src, 4);
//
//
//    int m2_src[] = {4,3,2,1};
//    int m2_rows = 2, m2_cols = 2;
//    int** m2 = generateMatrix(m2_rows, m2_cols);
//    populateMatrix(m2, m2_rows, m2_cols, m2_src, 4);
//
//    printMatrix(m1, m1_rows,m1_cols);
//    printMatrix(m2,m2_rows, m2_cols);
//
//    //Result matrix
////    int** result = generateMatrix(m1_rows, m1_cols);
//
//    int** result = addMatrices(m1, m2, m1_rows, m1_cols);
//
//    printMatrix(result, m1_rows, m1_cols);
    
    
    
    
    
    
    
//    return 0;
//}
//for (int indexR = 0; indexR < 4; indexR++){
//            for (int i = 0; i < 32; ++i){
//                matrix[indexR][indexC] = array[i];
//
//
//
//                if (indexR >= matrixR){
//                    indexR = 0;
//                }
//                if (indexC >= matrixC){
//                    indexC = 0;
//                }
