#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;



int main(int argc, const char * argv[]){
	
	int n = 10;
	bool espelhada = false;
	
	string path = "instances/";
	string n_instance = "10";
	
	if(argc > 1){
		n = atoi(argv[1]);
		n_instance = argv[1];
	}if(argc > 2){
		if( string(argv[2]) == "c"){
			espelhada = true;
		}
	}
	
	string mfile_path = path+"m_"+n_instance+".txt";
	string vfile_path = path+"v_"+n_instance+".txt";

	double matrix[n][n];
	double vetor[n];
	
	random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1.0, 100.0);
	
	if(!espelhada)
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			matrix[i][j] = dist(mt);
		}
	}
	
	double det(vector<double> _matrix){
		
	}
	
	if(espelhada)
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			
			matrix[j][i] = dist(mt);
			if(j!=i){
				matrix[i][j] = matrix[j][i];
			}
		}
	}
	
	// vector<double> _matrix;
	// for(int i = 0; i < n; i++){
	// 	for(int j = i; j < n; j++){
	// 		_matrix.push_back(matrix[i][j] );
	// 	}
	// }
	// cour << det(_matrix) << endl;
	
	for(int i = 0; i < n; i++){
		double soma = 0;
		for(int j = 0; j < n; j++){
			vetor[i] += matrix[i][j];
		}
	}
	
	
	
	ofstream mfile(mfile_path);

	if (mfile.is_open()){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				mfile << matrix[i][j];
				if(j+1 != n){
					mfile << "\t";
				}
			}
			mfile << endl;
		}
		mfile.close();
	}
	
	ofstream vfile(vfile_path);

	if (vfile.is_open()){
		for(int i = 0; i < n; i++){
			vfile << vetor[i] << endl;
		}
		vfile.close();
	}

	return 0;
}