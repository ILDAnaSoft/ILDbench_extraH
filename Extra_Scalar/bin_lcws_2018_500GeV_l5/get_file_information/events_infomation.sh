#!/bin/bash
if [[  $# != 2 ]]  ; then
	echo "usage: ./events input_class_name (all/2f/4f/higgs/4f_WW/4f_zz..) final_state (l/sl/h/lep/e2/e1..)  "
	exit
fi

input_class_name=${1,,}
final_state=${2,,}


four=("4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw")
six=("6f_eeww" "6f_llww" "6f_ttbar" "6f_vvww" "6f_xxww" "6f_xxxxz" "6f_yyyyz")
two=("2f_z") 
higgs=("higgs") 
nh=("nh") 
aa=("aa_2f" "aa_minijet") 
all=("4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw" "2f_z" "aa_2f" "aa_minijet" "higgs" "nh" "6f_eeww" "6f_llww" "6f_ttbar" "6f_vvww" "6f_xxww" "6f_xxxxz" "6f_yyyyz")


if [[ ${input_class_name} == "4f" ]] ; then
	class_name=("${four[@]}")
elif [[ ${input_class_name} == "2f" ]] ; then
	class_name=("${two[@]}")
elif [[ ${input_class_name} == "all" ]] ; then
	class_name=("${all[@]}")
elif [[ ${input_class_name} == "higgs" ]] ; then
	class_name=("${higgs[@]}")
elif [[ ${input_class_name} == "6f" ]] ; then
	class_name=("${six[@]}")
elif [[ ${input_class_name} == "nh" ]] ; then
	class_name=("${nh[@]}")
elif [[ ${input_class_name} == "aa" ]] ; then
	class_name=("${aa[@]}")
else
	class_name=("${input_class_name}")
fi


class_length=${#class_name[@]}

for i in ${class_name[@]}
do
		echo "class name:  "${i}
		info=" ./get_final_states_information.sh ${i} ${final_state}  "
		eval $info
		echo "end of class:  "${i}
done
