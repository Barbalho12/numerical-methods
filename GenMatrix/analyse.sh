max=1000
for i in `seq 5 $max`
do
    ./gen.exe $i
    echo $i
done