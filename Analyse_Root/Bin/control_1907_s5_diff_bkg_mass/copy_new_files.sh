#!/bin/bash
if [[  $# != 4 ]]  ; then
	echo "usage: ./copy_new_files.sh path_file Bkg_file flow_file var_file"

	exit
fi



input_path_file=$1
input_Bkg_file=$2
input_flow_file=$3
input_var_file=$4

mass_profile=(10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120 125 130 135 140 145 150 155 160 165 170 175 180 185 190 195 200 205 210 215 220 225 230 235 240 245 250 255 260 265 270 275 280 285 290 295 300 305 310 315 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
mass_length=${#mass_profile[@]}

for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}
	mass_array=(${mass})
    path_file="path_"${mass}".dat"
    cp ${input_path_file} ${path_file}
    ../change_para.sh word ${mass}  path 30 $mass_array 

    Bkg_file="Bkg_Sort_"${mass}".dat"
    cp ${input_Bkg_file} ${Bkg_file}
    ../change_para.sh word ${mass}  Bkg_Sort 30 $mass_array 

    flow_file="flow_"${mass}".dat"
    cp ${input_flow_file} ${flow_file}
    ../change_para.sh word ${mass}  flow 30 $mass_array 

    var_file="Var/Var_nh_"${mass}".dat"
    cp ${input_var_file} ${var_file}

done

