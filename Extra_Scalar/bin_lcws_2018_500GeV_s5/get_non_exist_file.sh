#!/bin/bash
if [[  $# != 1 ]]  ; then
	echo "usage: ./get_non_exist_file.sh file_name) "
	exit
fi
non_exist_files=$1
class_names=$(cut -f 1 -d "," $non_exist_files)
final_state_names=$(cut -f 2 -d "," $non_exist_files)
pol_names=$(cut -f 3 -d "," $non_exist_files)
mass_names=$(cut -f 4 -d "," $non_exist_files)
root_names=$(cut -f 5 -d "," $non_exist_files)
echo 'class_names=('${class_names[@]}')'
echo 'final_state_names=('${final_state_names[@]}')'
echo 'pol_names=('${pol_names[@]}')'
echo 'mass_names=('${mass_names[@]}')'
echo 'root_names=('${root_names[@]}')'

 echo '
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
    cd ${DIR}
    xml_folder=xml_500_lcws_s5
    xml_direction=${DIR}/../${xml_folder}
    classes_length=${#class_names[@]}
    for (( i=0; i<$(( $classes_length )); i++ )) 
    do
    	class_name=${class_names[i]}
    	final_state=${final_state_names[i]}
    	pol=${pol_names[i]}
    	mass=${mass_names[i]}

    	echo "--------${class_name}  $final_state  $pol  ${mass}  -------"

    	NewXml=${class_name}_${final_state}_${pol}_${mass}.xml
    	${HOME}/Code/HTCondor/run_it_on_condor.sh run.sh ${xml_folder}/${NewXml} 
		sleep 0.05

    done
 '
