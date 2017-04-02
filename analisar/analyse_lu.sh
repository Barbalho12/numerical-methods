./compile.sh
rm database.txt
lenght=100

echo -e "-------------------------------------------------"
echo "Resolvendo sistemas e salvando saída em database.txt"
echo ''
for i in `seq 5 $lenght`
do
    ./fatLU.exe instances/m_$i.txt instances/v_$i.txt $i $i y >> database.txt

    echo -e "\e[1A--- Progresso: $i%"
done

echo "Gerando Gráfico .."
# Intall gnuplot : sudo apt-get update && sudo apt-get install gnuplot-x11
gnuplot gnuplot_script.gnu
# echo "\n" >> database.txt