./compile.sh
max=100
for i in `seq 5 $max`
do
    ./gen.exe $i c
    echo $i
done
