#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>


using namespace std;

typedef std::vector<std::vector<float>> matriz;
typedef std::vector<float> vetor;

double d = 0;
// double det( matriz &mat){
//     return det(3, mat);
// }

double calculateDeterminant(vector<double> matrix){
    if(matrix.size()==0) {
	    return 0;
    }

	int numOfRows = sqrt(matrix.size());
	
	//1x1 matrix
	if(numOfRows==1) {
		return matrix[0];
	}else if(numOfRows==2) {
		return ((matrix[0]*matrix[3])-(matrix[1]*matrix[2]));
	}else{
		double determinant=0;
		vector<double> minorMatrix;
		int l=0;
		
		for(int i=0; i<numOfRows; i++){
			for(int j=0; j < numOfRows; j++){
				for(int k=0; k<matrix.size(); k++){
					if(k==(numOfRows*l + j)){
					    if(l<numOfRows){
					        l++;
					        
					    }
						continue;
					}
					minorMatrix.push_back(matrix[k]);
				}
			}
			determinant += (matrix[i]*pow(-1,i+2))*calculateDeterminant(minorMatrix);
			minorMatrix.clear(); //reset for reusing on next iteration
			l=0;
		}
		return determinant;
	}
	
}

double det(int n, matriz mat){
    int c, i, j, subi, subj;
    matriz submat(10, vetor(10, 0));
    if (n == 2)  {
        return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
    }
    else {  
        for(; c < n; c++) {  
            subi = 0;  
            for(; i < n; i++){  
                subj = 0;
                for(; j < n; j++){    
                    if (j == c){
                        continue;
                    }
                    submat[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
            d = d + (pow(-1 ,c) * mat[0][c] * det(n - 1, submat));
        }
    }
    return d;
}

int main(){
    int n = 3;
    matriz mat(10, vetor(10, 0));
    mat[0][0] = 1;  mat[0][1] = 1;  mat[0][2] = 3;
    mat[1][0] = 2;  mat[1][1] = 2;  mat[1][2] = 3;
    mat[2][0] = 3;  mat[2][1] = 6;  mat[2][2] = 9;
    cout << det(3, mat) << endl;
    
    vector<double> _matrix(9, 0);
	for(int i = 0, a = 0; i < n; i++){
		for(int j = i; j < n; j++, a++){
			_matrix[a] = mat[i][j];
		}
	}
	cout << calculateDeterminant(_matrix) << endl;
}