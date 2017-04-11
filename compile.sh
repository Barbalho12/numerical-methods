echo "Compilando Fatoração LU... "
g++ -std=c++11 fatoracao_lu/fatoracao_lu.cpp -o bin/fatoracao_lu.exe

echo "Compilando Cholesky... "
g++ -std=c++11 cholesky/cholesky.cpp -o bin/cholesky.exe

echo  "Compilando Jacobi... "
g++ -std=c++11 jacobi/jacobi.cpp -o bin/jacobi.exe

echo  "Compilando Gauss Seidel... "
g++ -std=c++11 gauss_seidel/gauss_seidel.cpp -o bin/gauss_seidel.exe



