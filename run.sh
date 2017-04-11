MA="matrizA.txt"
VB="vetorB.txt"
N=3
N=$2

# if [("$N" -lt "2") || ("$N" -gt "100")] then
#     N="3"
# fi

if [ "$1" = 'l' ]; then
   ./bin/fatoracao_lu.exe fatoracao_lu/$MA fatoracao_lu/$VB $N $N
elif [ "$1" = 'c'  ]; then
   ./bin/cholesky.exe cholesky/$MA cholesky/$VB $N $N
elif [ "$1" = 'j'  ]; then
   ./bin/jacobi.exe jacobi/$MA jacobi/$VB $N $N
elif [ "$1" = 'g'  ]; then
   ./bin/gauss_seidel.exe gauss_seidel/$MA gauss_seidel/$VB $N $N
else
    echo " l = Fatoração LU"
    echo " c = Cholesky"
    echo " j = Jacobi"
    echo " g = Gauss Seidel"
fi
