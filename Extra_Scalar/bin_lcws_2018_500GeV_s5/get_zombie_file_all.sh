#!/bin/bash


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}

#mass_profile=(10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
mass_profile=(10 20 30 40 50 60 70 80 85 90 95 100 )
mass_length=${#mass_profile[@]}
for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}
####./check_exist.sh s ${mass} >> zombie_files_${mass}.dat
####cat zombie_files_${mass}.dat | grep "Zombie file is :" | sed "s/results_/;/g" | cut -d ";" -f 2 >> zombie_class_name_${mass}.dat
####./get_zombie_file.sh ${mass} >> run_zombie_file_${mass}.sh
####chmod +x run_zombie_file_${mass}.sh
####./run_zombie_file_${mass}.sh
	./check_exist.sh s ${mass} >> zombie_files_${mass}.dat
	cat zombie_files_${mass}.dat | grep "Zombie file is :" | sed "s/results_/;/g" | cut -d ";" -f 2 >> zombie_class_name.dat
done



