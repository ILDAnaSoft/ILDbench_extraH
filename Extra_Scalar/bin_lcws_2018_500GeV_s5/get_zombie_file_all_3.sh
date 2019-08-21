#!/bin/bash


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}

mass_profile=(105 110 115 120 130 135 140 160 180 200 )
mass_length=${#mass_profile[@]}
for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}
####./check_exist.sh l ${mass} >> zombie_files_${mass}.dat
####cat zombie_files_${mass}.dat | grep "Zombie file is :" | sed "s/results_/;/g" | cut -d ";" -f 2 >> zombie_class_name_${mass}.dat
####./get_zombie_file.sh ${mass} >> run_zombie_file_${mass}.sh
####chmod +x run_zombie_file_${mass}.sh
####./run_zombie_file_${mass}.sh
	./check_exist.sh s ${mass} >> zombie_files_${mass}.dat
	cat zombie_files_${mass}.dat | grep "Zombie file is :" | sed "s/results_/;/g" | cut -d ";" -f 2 >> zombie_class_name.dat
done



