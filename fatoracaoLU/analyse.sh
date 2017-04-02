max=1000
for i in `seq 5 $max`
do
    ./fatLU.exe instances/m_$i.txt instances/v_$i.txt $i $i y > database.txt
done