#!/bin/bash
if [[  $# != 3 ]]  ; then
	echo "usage: ./get_weight.sh input_class_name (higgs/4f_WW/4f_ZZ..) final_state (l/sl/h/e2/e1..) pol (lr/rl/ll/rr) "
	exit
fi
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

class_name=${1,,}
input_final_state=${2,,}
pol=${3,,}


if [[ ${input_final_state} = "l" ]] ; then
	final_states=("leptonic")
elif [[ ${input_final_state} = "bha" ]] ; then
	final_states=("bhabhag")
elif [[ ${input_final_state} = "sl" ]] ; then
	final_states=("semileptonic")
elif [[ ${input_final_state} = "h" ]] ; then
	final_states=("hadronic")
else
	final_states=("${input_final_state}")
fi


direction=${DIR}
if [[ -a ${direction}/all_events.dat ]] ; then
	file_name=${direction}/all_events.dat
else
	echo "no all_events.dat in the folder."${direction}
fi

class_content=" sed -n \"/^class name:\ \ ${class_name}$/,/^end of class:\ \ ${class_name}$/p\"  "
final_state_content=" sed -n \"/^final_state name:\ \ ${final_states}$/,/^end of final_state:\ \ ${final_states}$/p\"  "
pol_content=" sed -n \"/^pol:\ \ ${pol}$/,/^end of pol:\ \ ${pol}$/p\"  "
file_content=" sed -n -e \"/^file:\ \ ${class_name}$/,/^end of file:\ \ ${class_name}$/ { /^file:\ \ ${class_name}$/d; /^end of file:\ \ ${class_name}$/d; p; } \"  "
eval ${class_content} ${file_name} | eval ${final_state_content} | eval ${pol_content} | eval ${file_content}

