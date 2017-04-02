#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

typedef std::vector<std::vector<float>> matriz;
typedef std::vector<float> vetor;

int m =4;
int n =4;
string arquivoA = "matrizA.txt";
string arquivoB = "vetorB.txt";
matriz A(m, vetor(n, 0));
vetor B(m, 0);	

double tempoPrint;


int lerA(void){
	ifstream arq;
	arq.open(arquivoA.c_str());
	if(arq.is_open()){
		for(int i = 0; i < m; i++){
			for (int j = 0; j < n; ++j){
				arq >> A[i][j];
			}
		}
		arq.close();
	} else {
		cout << "FU!";
	}
	return 0;
}

int lerB(void){
	ifstream arq;
	arq.open(arquivoB.c_str());
	if(arq.is_open()){
		for(int i = 0; i < m; i++){
			arq >> B[i];
		}
		arq.close();
	} else {
		cout <<"Falta o vetorB";
	}
	return 0;
}

void copyFromTo(matriz &X, matriz &Y) {
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Y[i][j] = X[i][j];
		}
	}
}

void lerArgs(int argc, const char * argv[]){
	if(argc > 1)
		arquivoA = string(argv[1]);
	if(argc > 2)
		arquivoB = string(argv[2]);
	if(argc > 3)
		m = atoi(argv[3]);
		n = m;
	if(argc > 4)
		n = atoi(argv[4]);
}

void showMatriz(string label, matriz &X){
	auto t1 = std::chrono::high_resolution_clock::now();
	
	cout << "___________" << label<< "___________" << endl;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			cout << X[i][j]<<"\t";
		}
		cout << endl;
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	tempoPrint += tempo.count();
}

void showVector(string label, vetor &X){
	auto t1 = std::chrono::high_resolution_clock::now();
	
	cout << "___________" << label<< "___________" << endl;
	for (int i = 0; i < m; ++i){
		cout << X[i]<<"\n";
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	tempoPrint += tempo.count();
}

void showResult(vetor &X){
	auto t1 = std::chrono::high_resolution_clock::now();
	
	cout << "___________" << "RESULTADO" << "___________" << endl;
	for (int i = 0; i < m; ++i){
		cout << "X" << i << " = " << X[i]<< endl;
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	tempoPrint += tempo.count();
}

void identity(matriz &X) {
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(i==j){
				X[i][j] = 1;
			}else{
				X[i][j] = 0;
			}
		}
	}
}

matriz product(matriz &X, matriz &Y) {
	matriz Z(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				Z[i][j] += X[i][j] * Y[j][k];
			}
		}
	}
	return Z;
}

vetor product(matriz &X, vetor &Y) {
	vetor Z(m, 0);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i] += X[i][j] * Y[j];
		}
	}
	return Z;
}

matriz diag(matriz &X) {
	matriz Z(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if (i == j)
				Z[i][j] = 1/X[i][j];
			else
				Z[i][j] = 0;
		}
	}
	return Z;
}

void showTime(double tempoTotal){
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}


void pivotacao(matriz &X, vetor &Y){
	float pv, modulo;
	int linha;
	float auxA[n], auxb;
	for (int i = 0; i < n-1; ++i)
	{
		if (X[i][i] < 0)
				pv = -1*X[i][i];
			else
				pv = X[i][i];
		linha = i;
		for (int j = i+1; j < n; ++j)
		{
			if (X[j][i] < 0)
				modulo = -1*X[j][i];
			else
				modulo = X[j][i];

			if (modulo > pv)
			{
				pv = modulo;
				linha = j;
			}
		}

		if (linha != i)
		{
			for (int k = 0; k < n; ++k)
			{
				auxA[k] = X[i][k];
				X[i][k] = X[linha][k];
				X[linha][k]= auxA[k];
			}
			auxb = Y[i];
			Y[i] = Y[linha];
			Y[linha] = auxb;
		}
	}
}


void cholesky(){
	
	lerA();
	lerB();
	vetor X(n, 0);
	
	pivotacao(A, B);

	showMatriz("A", A);
	showVector("B",B);

	matriz U(m, vetor(n, 0));
	matriz L_(m, vetor(n, 0));
	matriz G(m, vetor(n, 0));
	matriz D_(m, vetor(n, 0));
	matriz aux(m, vetor(n, 0));

	copyFromTo(A, U);

	//𝐿−1 ← I
	identity(L_);

	for (int i = 0; i < n-1; ++i){
		
		//Gi <-- I
		identity(G);

		//𝑔𝑗𝑖 ← −𝑢𝑗𝑖/𝑢𝑖𝑖
		for (int j = i+1; j < n ; ++j){
			G[j][i] = (-1*U[j][i])/U[i][i];
		}
		showMatriz("G"+to_string(i),G);

		//L¹ <== Gi * L¹
		matriz L(m, vetor(n, 0));
		
		L_ = product(G, L_);
		showMatriz("L_",L_);

		//U <== Gi * U
		U = product(G, U);
		showMatriz("U",U);

		//b <== Gi * b
		B = product(G, B);
		showVector("B", B);

	}
	
	D_ = diag(U);
	showMatriz("D_",D_);
	aux = product(L_,D_);
	X = product(aux, B);

	showResult(X);
}


int main(int argc, const char * argv[]){
	
	auto t1 = std::chrono::high_resolution_clock::now();

	lerArgs(argc, argv);	//		./cholesky matrizA.txt vetorB.txt 3 3
	
	cholesky();
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	
	showTime(tempoTotal);
	
	return 0;
}