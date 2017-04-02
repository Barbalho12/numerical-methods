./compile.sh
max=100
for i in `seq 5 $max`
do
    ./gen.exe $i
    echo $i
done
