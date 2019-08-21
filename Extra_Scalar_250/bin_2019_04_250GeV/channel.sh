#!/bin/bash
if [[ $# == 3 ]] ; then
	echo "begin to cal events!" 
	input_class_name=${1,,}
	info=${2,,}
	mass=${3,,}
elif [[ $# == 4 ]] ; then
	echo "begin to cal events!" 
	input_class_name=${1,,}
	input_final_state=${2,,}
	info=${3,,}
	mass=${4,,}
else
	echo "usage: ./channel.sh class_name [final_state] info mass" 
	exit
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

pol_profile=("lr" "rl" "ll" "rr")
pol_length=${#pol_profile[@]}

final_state_length=${#input_final_state[@]}
class_name_length=${#class_name_array[@]}

echo ""
echo "has setting all variables!"
echo ""

xml_folder=xml_250GeV_2019_04_
xml_direction=${DIR}/../${xml_folder}
	echo "begin to generate samples!"
	echo ""
	for (( k=0; k<$(( $class_name_length)); k++ ))
	do
		class_name=${class_name_array[k]}
		for (( i=0; i<$(( $final_state_length )); i++ ))
		do
			final_state=${input_final_state[i]}
			for (( j=0; j<$(( $pol_length )); j++ ))
			do
				pol=${pol_profile[j]}
				NewXml=${class_name}_${final_state}_${pol}_${mass}.xml
				echo "generate samples for: "${NewXml} 
 				${DIR}/set_xml.sh ${class_name} ${final_state} ${pol} ${mass}
				if [[ -a ${xml_direction}/${NewXml} ]] ; then
					if [[ $info == "subjob" ]] ; then
						echo "--------${class_name} ${final_state} ${pol} ${mass}  -------"
						${HOME}/Code/HTCondor/run_it_on_condor.sh run.sh ${xml_folder}/${NewXml} 
						sleep 1
					else
						${DIR}/run.sh ${xml_folder}/${NewXml} 
						sleep 1
					fi
				fi
				echo ""
			done
		done
	done


