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

int m = 3;
int n = 3;
string arquivoA = "matrizA.txt";
string arquivoB = "vetorB.txt";
matriz A(m, vetor(n, 0));
vetor B(m, 0);	

double tempoPrint;
bool analyseMod = false;


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

void copyFromTo(vetor &X, vetor &Y) {
	for(int i = 0; i < m; i++){
		Y[i] = X[i];
	}
}

void lerArgs(int argc, const char * argv[]){
	if(argc > 1){
		arquivoA = string(argv[1]);
	}if(argc > 2){
		arquivoB = string(argv[2]);
	}if(argc > 3){
		m = atoi(argv[3]);
		n = m;
	}if(argc > 4){
		n = atoi(argv[4]);
	}if(argc > 5){
		if( string(argv[5]) == "y"){
			analyseMod = true;
		}
			
	}
	
	A = matriz(m, vetor(n, 0));
	B = vetor(m, 0);	
}

void showMatriz(string label, matriz &X){
	if(analyseMod) return;
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
	if(analyseMod) return;
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
	if(analyseMod) return;
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
				//Z[i][j] += X[i][j] * Y[j][k];
				Z[i][j] += X[i][k] * Y[k][j];
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

vetor difenca(vetor &X, vetor &Y) {
	vetor Z(m, 0);
	for(int i = 0; i < m; i++){
		Z[i] = X[i] - Y[i];
	}
	return Z;
}

matriz difenca(matriz &X, matriz &Y) {
	matriz Z(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i][j] = X[i][j] - Y[i][j];
		}
	}
	return Z;
}

vetor soma(vetor &X, vetor &Y) {
	vetor Z(m, 0);
	for(int i = 0; i < m; i++){
		Z[i] = X[i] + Y[i];
	}
	return Z;
}

matriz soma(matriz &X, matriz &Y) {
	matriz Z(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i][j] = X[i][j] + Y[i][j];
		}
	}
	return Z;
}

matriz negativo(matriz &X) {
	matriz Z(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			Z[i][j] = -1 * X[i][j];
		}
	}
	return Z;
}

vetor negativo(vetor &X) {
	vetor Z(m, 0);
	for(int i = 0; i < m; i++){
		Z[i] = -1 * X[i];
	}
	return Z;
}

float norma(vetor &X) {
	float Z =0;
	for(int i = 0; i < m; i++){
		Z += X[i]*X[i];
	}
	Z = sqrt(Z);
	return Z;
}

void showTime(double tempoTotal){
	if(analyseMod){
		cout << m << "\t" << (tempoTotal-tempoPrint)*1000 << endl;
		return;
	}
	cout << "----------------------------"  << endl;
	cout << "Tempo Algortimo: " << (tempoTotal-tempoPrint)*1000 << " ms"<< endl;
	cout << "Tempo Total: " << (tempoTotal*1000) << " ms"<< endl;
}
matriz diag(matriz &X) {
	matriz Z(m, vetor(n, 0));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if (i == j)
				Z[i][j] = X[i][j];
			else
				Z[i][j] = 0;
		}
	}
	return Z;
}

matriz diag_(matriz &X) {
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

vetor T(vetor &X) {
	vetor Z(m, 0);
	matriz D_(m, vetor(n, 0));
	matriz D(m, vetor(n, 0));
	matriz auxM(m, vetor(n, 0));
	vetor auxV(m, 0);
	vetor auxV1(m, 0);

	D_ = diag_(A);
	D = diag(A);
	auxM = difenca(A, D);
	auxV = product(auxM, X);
	auxV = product(D_, auxV);
	auxV = negativo(auxV);
	auxV1 = product(D_, B);
	Z = soma(auxV, auxV1);

	return Z;
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

bool validate(matriz &A){
	matriz D = diag(A);
	matriz D_ = diag_(A); 
	matriz D_A = difenca(A, D);
	matriz X = product( D_ , D_A );
	for(int i = 0; i < n; i++){
		float soma = 0.0;
		for(int j = 0; j < n; j++){
			soma += fabs(X[i][j]);
		}
		if (soma > 1){
			
			return false;
		}
	}
	return true;
}

void jacobi(){
	
	lerA();
	if(!validate(A)){
		showMatriz("A", A);
		cout << "\nA matriz não melhora a aproximação!" <<"\n\n";
		return;
	}
	
	
	lerB();
	vetor X(n, 0);
	vetor Xe(n, 0);
	vetor Xs(n, 0);
	vetor Xaux(n, 0);
	float E = 0.01;
	float normaX;
	
	pivotacao(A, B);

	showMatriz("A", A);
	showVector("B",B);

	for (int i = 0; i < m; ++i)
	{
		srand (time(NULL));
		Xe[i] = rand() % 10;
	}
	showVector("Xe",Xe);


	float normaX_anterior = 1;
	do
	{
		copyFromTo(Xe, Xaux);
		Xs = T(Xe);
		copyFromTo(Xs, Xe);
		X = difenca(Xe, Xaux);
		normaX = norma(X);
		cout << "norma = " << normaX << " >>> " << ((normaX_anterior/normaX)*100) << "%" << "\n\n";
		normaX_anterior = normaX;
		
	} while (normaX > E );

	
	showResult(Xs);

}


int main(int argc, const char * argv[]){
	
	auto t1 = std::chrono::high_resolution_clock::now();

	lerArgs(argc, argv);	//		./jacobi matrizA.txt vetorB.txt 3 3
	
	jacobi();
	
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tempo = t2 - t1;
	double tempoTotal = tempo.count();
	
	showTime(tempoTotal);
	
	return 0;
}