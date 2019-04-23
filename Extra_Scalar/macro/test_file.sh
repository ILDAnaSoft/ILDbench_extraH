#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

xml_direction=${DIR}/../xml_500_lcws_s5
mass_profile=(30) 
mass_length=${#mass_profile[@]}

for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}
	folder="/afs/desy.de/user/y/ywang/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_${mass}/"

	class_names=("4f" "2f" "higgs" "aa_2f" "6f_eeWW" "6f_llWW" "6f_ttbar" "6f_vvWW" "6f_xxWW" "6f_xxxxZ" "6f_yyyyZ")


	classes_length=${#class_names[@]}

	for (( i=0; i<$(( $classes_length )); i++ )) 
	do
		class_name=${class_names[i]}

		echo "$class_name" 

		if [[ ${class_name} = "higgs" ]] ; then
			class_name_array="higgs"
			input_final_state=("e2")
		elif [[ ${class_name} = "nh" ]] ; then
			class_name_array="nh"
			input_final_state=(${mass})
		elif [[ ${class_name} = "2f" ]] ; then
			class_name_array="2f_z"
			input_final_state=("l" "bha" "h")
		elif [[ ${class_name} = "4f" ]] ; then
			class_name_array=("4f_ww" "4f_zz" "4f_zzww" "4f_szee" "4f_sznn" "4f_szsw" "4f_sw")
			input_final_state=("l" "sl" "h")
		elif [[ ${class_name} = "aa_2f" ]] ; then
			class_name_array=("aa_2f")
			input_final_state=("ee" "ll" "xx" "yy")
		elif [[ ${class_name} = "aa_minijet" ]] ; then
			class_name_array=("aa_minijet")
		elif [[ ${class_name} = "6f_eeww" ]] ; then
			class_name_array=("6f_eeww")
			input_final_state=("eeveev" "eevelv" "eevlev" "eevllv" "eeveyx" "eexyev" "eevlyx" "eexylv" "eexyyx")
			#input_final_state=("eeveev")
		elif [[ ${class_name} = "6f_llww" ]] ; then
			class_name_array=("6f_llww")
			input_final_state=("llvelv" "llvlev" "llvllv" "llveyx" "llxyev" "llvlyx" "llxylv" "llxyyx")
		elif [[ ${class_name} = "6f_ttbar" ]] ; then
			class_name_array=("6f_ttbar")
			input_final_state=("yyveev" "yyvelv" "yyvlev" "yyvllv" "yyveyx" "yyxyev" "yyvlyx" "yyxylv" "yyuyyu" "yyuyyc" "yycyyu" "yycyyc")
		elif [[ ${class_name} = "6f_vvww" ]] ; then
			class_name_array=("6f_vvww")
			input_final_state=("vvveev"  "vvvelv"  "vvvlev"  "vvvllv"  "vvveyx"  "vvvyev"  "vvvlyx"  "vvxylv"  "vvxyyx")
		elif [[ ${class_name} = "6f_xxww" ]] ; then
			class_name_array=("6f_xxww")
			input_final_state=("xxveev" "xxvelv" "xxvlev" "xxvllv" "xxveyx" "xxxyev" "xxvlyx" "xxxylv" "xxxyyx")
		elif [[ ${class_name} = "6f_xxxxz" ]] ; then
			class_name_array=("6f_xxxxz")
			input_final_state=("vvvvxx" "vvvvyy" "xxxxee" "xxxxvv" "xxxxll" "xxxxxx")
		elif [[ ${class_name} = "6f_yyyyz" ]] ; then
			class_name_array=("6f_yyyyz")
			input_final_state=("eeeeee" "eeeell" "llllee" "llllll" "eeeexx" "eeeeyy" "eellxx" "eellyy" "yyyyee" "yyyyll" "yyyyyy" "yyyyvv")
		else
			class_name_array=${class_name}
			input_final_state=("l" "sl" "h")
		fi	


		pol_profile=("lr" "rl" "ll" "rr")
		pol_length=${#pol_profile[@]}

		final_state_length=${#input_final_state[@]}
		class_name_length=${#class_name_array[@]}


		for (( k=0; k<$(( $class_name_length)); k++ ))
		do
			sub_class_name=${class_name_array[k]}
			echo "$class_name_array" 
			echo "$sub_class_name" 
			echo "$input_final_state" 
			echo "$pol_profile" 
			for (( l=0; l<$(( $final_state_length )); l++ ))
			do
				final_state=${input_final_state[l]}
				for (( m=0; m<$(( $pol_length )); m++ ))
				do
					pol_in=${pol_profile[m]}

					if [[  ${class_name} == "aa_2f" || ${class_name} == "aa_minijet" ]] ; then
						if [[  ${pol_in} == "lr" ]] ; then
							polarization="eW.pW"
						elif [[ ${pol_in} == "rl" ]] ; then
							polarization="eW.pB"
						elif [[ ${pol_in} == "ll" ]] ; then
							polarization="eB.pW"
						elif [[ ${pol_in} == "rr" ]] ; then
							polarization="eB.pB"
						else
							echo "no such input pol"
						fi
					else
						if [[  ${pol_in} == "lr" ]] ; then
							polarization="eL.pR"
						elif [[ ${pol_in} == "rl" ]] ; then
							polarization="eR.pL"
						elif [[ ${pol_in} == "ll" ]] ; then
							polarization="eL.pL"
						elif [[ ${pol_in} == "rr" ]] ; then
							polarization="eR.pR"
						else
							echo "no such input pol"
						fi
					fi

					NewXml=${class_name}_${final_state}_${pol_in}_${mass}.xml
					if [[ -a ${xml_direction}/${NewXml} ]] ; then

						mass_profile="{ \"$folder${sub_class_name}_${final_state}_${polarization}".root"\"}" 
						echo ${mass_profile}
					fi

				done
			done
		done


		#root -l -q -b test_corrupted_file.C"($mass_profile)"
	done

done
