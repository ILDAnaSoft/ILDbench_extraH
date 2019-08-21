#!/bin/bash

if [[  $# != 2 ]]  ; then
	echo "usage: ./get_all_polarization input_class_name (all/2f/4f/higgs/4f_WW/4f_ZZ..) final_state (l/sl/h/lep/e2/e1..) "
	exit
fi

class_name=${1,,}
final_state=${2,,}
pol_profile=("lr" "rl" "ll" "rr")

for pol_in in "${pol_profile[@]}" 
do
	k=0
	info=" ./get_500_newproduction_information.sh  ${class_name} ${final_state} ${pol_in} "
		echo ""
		echo "pol:  "${pol_in}
			file_name=` eval $info | grep "file_name" | cut -d ":" -f2 | sed -e "s/    //g"  `
			echo "file:  "${class_name}
			echo -e "${file_name}"
			echo "end of file:  "${class_name}
		echo "end of pol:  "${pol_in}
done

