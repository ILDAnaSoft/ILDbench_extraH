#!/bin/bash


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}

mass_profile=(220 240 260 280 290 300 310 320 325 330 335 340 )
mass_length=${#mass_profile[@]}
for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}
####./check_exist.sh l ${mass} >> zombie_files_${mass}.dat
####cat zombie_files_${mass}.dat | grep "Zombie file is :" | sed "s/results_/;/g" | cut -d ";" -f 2 >> zombie_class_name_${mass}.dat
####./get_zombie_file.sh ${mass} >> run_zombie_file_${mass}.sh
####chmod +x run_zombie_file_${mass}.sh
####./run_zombie_file_${mass}.sh
	./check_exist.sh l ${mass} >> zombie_files_${mass}.dat
	cat zombie_files_${mass}.dat | grep "Zombie file is :" | sed "s/results_/;/g" | cut -d ";" -f 2 >> zombie_class_name.dat
done



