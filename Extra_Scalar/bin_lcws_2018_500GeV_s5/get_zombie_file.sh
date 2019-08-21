#!/bin/bash

if [[  $# != 1 ]]  ; then
	echo "usage: ./get_zombie_file.sh file_name) "
	exit
fi

	mass=${1}

	DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
	cd ${DIR}

	mass_names=($(cut -d "/" -f 1 zombie_class_name_${mass}.dat))
	root_names=($(cut -d "/" -f 1 zombie_class_name_${mass}.dat))
	class_names1=($(cut -d "/" -f 2 zombie_class_name_${mass}.dat | cut -d "_" -f 1) )
	class_names2=($(cut -d "/" -f 2 zombie_class_name_${mass}.dat | cut -d "_" -f 2) )
	final_state_names=($(cut -d "/" -f 2 zombie_class_name_${mass}.dat | cut -d "_" -f 3) )
	pol_names=($(cut -d "/" -f 2 zombie_class_name_${mass}.dat | cut -d "_" -f 4 | sed "s/\.root//g") )


	class_names=()
    classes1_length=${#class_names1[@]}
    for (( i=0; i<$(( $classes1_length )); i++ )) 
    do

		new_class=${class_names1[i]}"_"${class_names2[i]}
		class_names+=(${new_class})
	done

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
        	pol_in=${pol_names[i]}
    		if [[  ${pol_in} == "eL.pR" ]] ; then
    			pol="lr"
    		elif [[ ${pol_in} == "eR.pL" ]] ; then
    			pol="rl"
    		elif [[ ${pol_in} == "eL.pL" ]] ; then
    			pol="ll"
    		elif [[ ${pol_in} == "eR.pR" ]] ; then
    			pol="rr"
    		fi
        	mass=${mass_names[i]}
     
        	echo "--------${class_name}  $final_state  $pol  ${mass}  -------"
     
        	NewXml=${class_name}_${final_state}_${pol}_${mass}.xml
        	${HOME}/Code/HTCondor/run_it_on_condor.sh run.sh ${xml_folder}/${NewXml} 
    		sleep 0.05
    	done
        '
