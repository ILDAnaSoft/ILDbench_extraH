#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}
echo "-------- enter ${DIR} -------"

xml_folder=xml_500_lcws_s5
xml_direction=${DIR}/../${xml_folder}

	#class_names=("2f_z" "4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw" "2f" "higgs" "aa_2f" "6f_eeWW" "6f_llWW" "6f_ttbar" "6f_vvWW" "6f_xxWW" "6f_xxxxZ" "6f_yyyyZ")
    class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar" )
    final_state_names=("yycyyc" "yyuyyc" "yyxylv")
    pol_names=("lr" "lr" "lr")
    mass_names=("10" "10" "10")
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
	final_state_names=("yycyyc" "yycyyu" "yyxylv")
	pol_names=("lr" "lr" "lr")
	mass_names=("20" "20" "20")
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

    class_names=("2f_z" "2f_z" "4f_ww" "6f_ttbar")
    final_state_names=("h" "h" "h" "yyxylv")
    pol_names=("lr" "rl" "lr" "lr")
    mass_names=("30" "30" "30" "30")
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
	final_state_names=("h" "yycyyc" "yyxylv")
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


	class_names=("2f_z" "6f_ttbar" "6f_ttbar")
	final_state_names=("h" "yycyyu" "yyxylv")
	pol_names=("lr" "lr" "lr")
	mass_names=("50" "50" "50" )
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


	class_names=("4f_ww" )
	final_state_names=("sl" )
	pol_names=("lr" )
	mass_names=("60" ) 
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



	class_names=("2f_z" ) 
	final_state_names=("h" ) 
	pol_names=("lr" ) 
	mass_names=("70" ) 
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


	class_names=("2f_z" "2f_z" "4f_ww" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "h" "h" "yycyyc" "yycyyu") 
	pol_names=("lr" "rl" "lr" "lr" "lr" ) 
	mass_names=("80" "80" "80" "80" "80" ) 
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


	class_names=("2f_z" "2f_z" "4f_ww" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "h" "h" "yycyyc" "yycyyu" "yyuyyu" ) 
	pol_names=("lr" "rl" "lr" "lr" "lr" "rl" ) 
	mass_names=("85" "85" "85" "85" "85" "85" ) 
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
	final_state_names=("yycyyc" "yyuyyc" "yyuyyu" "yyxyev" "yyxylv" )
	pol_names=("lr" "lr" "lr" "lr" "lr" ) 
	mass_names=("90" "90" "90" "90" "90" ) 
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


	class_names=("4f_szee" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("sl" "yycyyu" "yyuyyu" "yyxyev" "yyxylv" )
	pol_names=("rl" "lr" "lr" "lr" "lr" ) 
	mass_names=("95" "95" "95" "95" "95" ) 
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


	class_names=("4f_szee" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("l" "yycyyu" "yyuyyc" )
	pol_names=("lr" "lr" "lr" ) 
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


	class_names=("2f_z" "4f_szee" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "l" "yycyyc" "yycyyu" "yyxylv" "yyxylv" ) 
	pol_names=("rl" "lr" "lr" "lr" "lr" "rl" ) 
	mass_names=("105" "105" "105" "105"  "105" "105" ) 
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


	class_names=("2f_z" "4f_ww" ) 
	final_state_names=("h" "h" ) 
	pol_names=("rl" "lr" ) 
	mass_names=("110" "110" ) 
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


	class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("yycyyu" "yyuyyu" "yyxylv" )
	pol_names=("lr" "rl" "lr" ) 
	mass_names=("115" "115" "115" ) 
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


	class_names=("6f_ttbar" ) 
	final_state_names=("yycyyu" )
	pol_names=("rl" ) 
	mass_names=("120" ) 
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


	class_names=("4f_zzww" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "yycyyc" "yyuyyu" "yyuyyu" "yyxylv" )
	pol_names=("lr" "lr" "lr" "rl"  "lr" ) 
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

	class_names=("6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("yycyyc" "yyuyyu" "yyuyyu" "yyxylv" )
	pol_names=("lr" "lr" "rl"  "lr" ) 
	mass_names=("135" "135" "135" "135" ) 



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

	class_names=("2f_z" "4f_ww" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" "6f_ttbar" ) 
	final_state_names=("h" "h" "yycyyc" "yycyyu" "yyuyyc" "yyuyyu" "yyveyx" "yyxylv" "yyxylv" )
	pol_names=("lr" "lr" "lr" "lr" "rl"  "rl" "rl" "lr" "rl" ) 
	mass_names=("140" "140" "140" "140" "140" "140" "140" "140" "140" ) 



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

