#!/bin/bash
if [[  $# != 2 ]]  ; then
	echo "usage: ./check_exist.sh l/s mass) "
	exit
fi
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/


folder_name=${HOME}/dust/light_higgs_10_410_e500_lcws_${1}5_2019_01/results_${2}


i=1
for file_name in ${folder_name}/*
do
	i=$((i+1))
    root -l -q -b check_exist.C"(\"${file_name}\")"
####if [[ $i == 7  ]];then
####	exit	
####fi
done


