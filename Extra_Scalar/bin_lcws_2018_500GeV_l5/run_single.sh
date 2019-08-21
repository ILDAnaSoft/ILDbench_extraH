#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}
echo "-------- enter ${DIR} -------"

xml_folder=xml_500_lcws_l5
xml_direction=${DIR}/../${xml_folder}

	#class_names=("2f_z" "4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw" "2f_z" "higgs" "aa_2f_z" "6f_eeWW" "6f_llWW" "6f_ttbar" "6f_vvWW" "6f_xxWW" "6f_xxxxZ" "6f_yyyyZ")
#mass_profile=(10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)



    class_names=("2f_z" "2f_z" "2f_z" "4f_sw" "4f_sw" "4f_sznn" "4f_szsw" "4f_zz" "4f_zzww" "higgs")
    final_state_names=("h" "h" "bha" "l" "sl" "l" "l" "sl" "h" "e2") 
    pol_names=("lr" "rl" "rl" "lr" "rl" "rr" "lr" "rr" "rl" "rl" "rl") 
    mass_names=("10" "10" "10" "10" "10" "10" "10" "10" "10" "10" "10") 
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
    	sleep 1 
    done


    class_names=("2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar")
    final_state_names=("h" "yycyyc" "yycyyu" "yyxylv")
    pol_names=("rl" "lr" "lr" "lr")
    mass_names=("20" "20" "20" "20")
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
    	sleep 1 
    done


    class_names=("2f_z" "6f_ttbar")
    final_state_names=("h" "yyxylv")
    pol_names=("rl" "lr")
    mass_names=("30" "30")
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
    	sleep 1 
    done


	class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar")
	final_state_names=("yycyyu" "yyuyyu" "yyxylv")
	pol_names=("lr" "lr" "lr")
	mass_names=("40" "40" "40")
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
    	sleep 1 
    done


	class_names=("2f_z" "2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "h" "yycyyc" "yycyyu" "yyuyyu" "yyuyyu" "yyxylv")
	pol_names=("lr" "rl" "lr" "lr" "lr" "rl" "lr")
	mass_names=("50" "50" "50" "50" "50" "50" "50")
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
    	sleep 1 
    done



	class_names=("2f_z" "2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "h" "yycyyc" "yyuyyu" "yyxylv")
	pol_names=("lr" "rl" "lr" "lr" "lr")
	mass_names=("60" "60" "60" "60" "60")
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
    	sleep 1 
    done


	class_names=("2f_z" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "yyuyyu" "yyxylv")
	pol_names=("rl" "lr" "lr")
	mass_names=("70" "70" "70")
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
    	sleep 1 
    done


	class_names=("2f_z" "2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "h" "yycyyc" "yyuyyc" "yyxyev" "yyxylv")
	pol_names=("lr" "rl" "lr" "lr" "lr" "lr")
	mass_names=("80" "80" "80" "80" "80" "80") 
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
    	sleep 1 
    done


	class_names=("2f_z" "2f_z" "4f_ww" "6f_ttbar" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "h" "sl" "yycyyc" "yycyyu" "yyxylv")
	pol_names=("lr" "rl" "lr" "lr" "lr" "lr")
	mass_names=("85" "85" "85" "85" "85" "85") 
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
    	sleep 1 
    done


	class_names=("2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "yycyyc" "yycyyu" "yyxylv" ) 
	pol_names=("rl" "lr" "lr" "lr" ) 
	mass_names=("90" "lr" "90" "90" ) 
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
    	sleep 1 
    done


	class_names=("2f_z" "4f_szee" "4f_ww" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "l" "h" "yycyyu" "yyuyyc" "yyxylv" ) 
	pol_names=("rl" "rl" "lr" "lr" "rl" "lr" ) 
	mass_names=("95" "95" "95" "95" "95" "95" ) 
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
    	sleep 1 
    done


	class_names=("2f_z" "2f_z" "6f_ttbar" ) 
	final_state_names=("h" "h" "yycyyc" ) 
	pol_names=("lr" "rl" "lr" ) 
	mass_names=("100" "100" "100" ) 
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
    	sleep 1 
    done



	class_names=("2f_z" "2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "h" "yyuyyc" "yyuyyu" "yyxylv")
	pol_names=("lr" "rl" "lr" "lr" "lr")
	mass_names=("105" "105" "105" "105" "105") 
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
    	sleep 1 
    done


	class_names=("2f_z" "2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" )
	final_state_names=("h" "h" "yycyyu" "yyuyyc" "yyxylv" "yyxylv" )
	pol_names=("lr" "rl" "lr" "lr" "lr" "rl")
	mass_names=("110" "110" "110" "110" "110" "110" ) 
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
    	sleep 1 
    done


	class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" )
	final_state_names=("yycyyc" "yyuyyu" "yyxylv" "yyxylv" )
	pol_names=("lr" "lr" "lr" "rl")
	mass_names=("115" "115" "115" "115" ) 
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
    	sleep 1 
    done


	class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" )
	final_state_names=("yyuyyc" "yyuyyc" "yyuyyu" "yyxylv" "yyxylv" )
	pol_names=("lr" "rl" "lr" "lr" "rl")
	mass_names=("120" "120" "120" "120" "120" ) 
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
    	sleep 1 
    done


	class_names=("2f_z" "2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" )
	final_state_names=("h" "h" "yycyyc" "yycyyc" "yyxylv" )
	pol_names=("lr" "rl" "lr" "rl" "lr" ) 
	mass_names=("130" "130" "130" "130" "130" ) 
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
    	sleep 1 
    done


	class_names=("2f_z" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" )
	final_state_names=("h" "yycyyc" "yycyyu" "yyuyyu" "yyxylv" )
	pol_names=("lr" "lr" "lr" "lr" "lr" ) 
	mass_names=("135" "135" "135" "135" "135" ) 
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
    	sleep 1 
    done


	class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" )
	final_state_names=("yycyyc" "yyuyyc" "yyuyyu" "yyveyx" "yyxylv" "yyxylv" )
	pol_names=("lr" "lr" "lr" "lr" "lr" "lr" ) 
	mass_names=("140" "140" "140" "140" "140" "140" ) 



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
    	sleep 1 
    done

