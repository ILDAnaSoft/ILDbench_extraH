#!/bin/bash

if [[  $# != 1 ]]  ; then
	echo "usage: ./check_non_exist_file_all.sh mass) "
	exit
fi

#mass_profile=(10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120 125 130 135 140 145 150 155 160 165 170 175 180 185 190 195 200 205 210 215 220 225 230 235 240 245 250 255 260 265 270 275 280 285 290 295 300 305 310 315 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405)
#mass_profile=(10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
#mass_profile=(10) 
#mass_length=${#mass_profile[@]}

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}

#for (( j=0; j<$(( $mass_length)); j++ )) 
#do
####mass=${mass_profile[j]}

####class_names=("nh" "4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw" "2f" "higgs" "aa_2f" "6f_eeWW" "6f_llWW" "6f_ttbar" "6f_vvWW" "6f_xxWW" "6f_xxxxZ" "6f_yyyyZ")
####classes_length=${#class_names[@]}

####for (( i=0; i<$(( $classes_length )); i++ )) 
####do
####	class_name=${class_names[i]}

####	./check_channel.sh ${class_name} ${mass}
#    done
#done

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}

mass=${1}

class_names=("nh" "4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw" "2f" "higgs" "aa_2f" "6f_eeWW" "6f_llWW" "6f_ttbar" "6f_vvWW" "6f_xxWW" "6f_xxxxZ" "6f_yyyyZ")
classes_length=${#class_names[@]}

for (( i=0; i<$(( $classes_length )); i++ )) 
do
	class_name=${class_names[i]}

	./check_channel.sh ${class_name} ${mass}
done

