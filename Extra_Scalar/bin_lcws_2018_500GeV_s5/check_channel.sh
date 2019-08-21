#!/bin/bash
if [[ $# == 2 ]] ; then
	input_class_name=${1,,}
	mass=${2,,}
fi



DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}



if [[ ${input_class_name} = "higgs" ]] ; then
	class_name_array="higgs"
	input_final_state=("e2")
elif [[ ${input_class_name} = "nh" ]] ; then
	class_name_array="nh"
	input_final_state=(${mass})
elif [[ ${input_class_name} = "2f" ]] ; then
	class_name_array="2f_z"
	input_final_state=("l" "bha" "h")
elif [[ ${input_class_name} = "4f" ]] ; then
	class_name_array=("4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw")
	input_final_state=("l" "sl" "h")
elif [[ ${input_class_name} = "aa_2f" ]] ; then
	class_name_array=("aa_2f")
	input_final_state=("ee" "ll" "xx" "yy")
elif [[ ${input_class_name} = "aa_minijet" ]] ; then
	class_name_array=("aa_minijet")
elif [[ ${input_class_name} = "6f_eeww" ]] ; then
	class_name_array=("6f_eeww")
	input_final_state=("eeveev" "eevelv" "eevlev" "eevllv" "eeveyx" "eexyev" "eevlyx" "eexylv" "eexyyx")
	#input_final_state=("eeveev")
elif [[ ${input_class_name} = "6f_llww" ]] ; then
	class_name_array=("6f_llww")
	input_final_state=("llvelv" "llvlev" "llvllv" "llveyx" "llxyev" "llvlyx" "llxylv" "llxyyx")
elif [[ ${input_class_name} = "6f_ttbar" ]] ; then
	class_name_array=("6f_ttbar")
	input_final_state=("yyveev" "yyvelv" "yyvlev" "yyvllv" "yyveyx" "yyxyev" "yyvlyx" "yyxylv" "yyuyyu" "yyuyyc" "yycyyu" "yycyyc")
elif [[ ${input_class_name} = "6f_vvww" ]] ; then
	class_name_array=("6f_vvww")
	input_final_state=("vvveev"  "vvvelv"  "vvvlev"  "vvvllv"  "vvveyx"  "vvvyev"  "vvvlyx"  "vvxylv"  "vvxyyx")
elif [[ ${input_class_name} = "6f_xxww" ]] ; then
	class_name_array=("6f_xxww")
	input_final_state=("xxveev" "xxvelv" "xxvlev" "xxvllv" "xxveyx" "xxxyev" "xxvlyx" "xxxylv" "xxxyyx")
elif [[ ${input_class_name} = "6f_xxxxz" ]] ; then
	class_name_array=("6f_xxxxz")
	input_final_state=("vvvvxx" "vvvvyy" "xxxxee" "xxxxvv" "xxxxll" "xxxxxx")
elif [[ ${input_class_name} = "6f_yyyyz" ]] ; then
	class_name_array=("6f_yyyyz")
	input_final_state=("eeeeee" "eeeell" "llllee" "llllll" "eeeexx" "eeeeyy" "eellxx" "eellyy" "yyyyee" "yyyyll" "yyyyyy" "yyyyvv")
else
	class_name_array=${input_class_name}
	input_final_state=("l" "sl" "h")
fi	

pol_profile=("eL.pR" "eR.pL" "eL.pL" "eR.pR")
pol_short=("lr" "rl" "ll" "rr")
pol_length=${#pol_profile[@]}

final_state_length=${#input_final_state[@]}
class_name_length=${#class_name_array[@]}


folder_name=${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_${mass}/
xml_folder=xml_500_lcws_s5
xml_direction=${DIR}/../${xml_folder}
	for (( k=0; k<$(( $class_name_length)); k++ ))
	do
		class_name=${class_name_array[k]}
		for (( i=0; i<$(( $final_state_length )); i++ ))
		do
			final_state=${input_final_state[i]}
			for (( j=0; j<$(( $pol_length )); j++ ))
			do
				pol=${pol_profile[j]}
				root_name=${folder_name}/${class_name}_${final_state}_${pol}.root 
				pol_s=${pol_short[j]}
				NewXml=${class_name}_${final_state}_${pol_s}_${mass}.xml
				if [[ -a ${xml_direction}/${NewXml} ]] ; then
					if [[ ! -a ${root_name} ]] ; then
							echo "${class_name}, ${final_state},  ${pol_s},  ${mass},  $root_name"
					fi
				fi
			done
		done
	done


