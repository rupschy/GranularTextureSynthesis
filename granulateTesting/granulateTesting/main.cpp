//
//  main.cpp
//  granulateTesting
//
//  Created by John Rupsch on 4/5/21.
//

#include <iostream>
#include <cmath>
//int ** generateMatrix(int rows, int cols){
//    int** temp = new int*[rows];
//
//    for (int i = 0; i < rows; ++i){
//        temp[i] = new int[cols];
//    }
//    return temp;
//}

//void printMatrix(int** matrix, int rows, int cols){
//    for (int i = 0; i<rows; ++i){
//        for (int j = 0; j < cols; ++j){
//            std::cout << matrix[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}

//void populateMatrix(int** matrix, int rows, int cols, int * src, int src_size){
//    if (rows*cols != src_size){
//        exit(-1);
//    }
//    int pos = 0;
//    for (int i = 0; i < rows; ++i){
//        for (int j = 0; j < cols; ++j){
//            matrix[i][j] = src[pos++];
//        }
//    }
//}

//int** addMatrices(int** matA, int** matB, int a_rows, int a_cols){
//    int** resultMat = generateMatrix(a_rows, a_cols);
//
//    for (int i = 0; i < a_rows; ++i){
//        for (int j = 0; j < a_cols; ++j){
//            resultMat[i][j] = matA[i][j] + matB[i][j];
//        }
//    }
//
//        return resultMat;
//}

void makeArray(int x);
void makeMatrix(int x);

int main() {

    int arrayS = 32;
    int* k = 0;
    int array[32] = {0};

    for (int n = 0; n < 32; ++n){
        array[n] = n;
    }

//    int size = sizeof(array)/sizeof(array[0]);
//    std::random_shuffle(array,array+size);

    int matrixR = 4;
    int indexR = 0;
    int matrixC = 8;
    int indexC = 0;

    int matrix[4][8] = {0};

    for (int indexC = 0; indexC < 8; ++indexC){
        matrix[indexR][indexC] = array[*k++];
        
//        k = k + 1;
        
        
        if (int k = 32){
            k = 0;
        }
        


        if (indexC = 8){
//            k = k;
            indexR = indexR+1;
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
