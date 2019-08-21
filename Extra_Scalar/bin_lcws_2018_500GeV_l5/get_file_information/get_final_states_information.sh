#!/bin/bash

if [[  $# != 2 ]]  ; then
	echo "usage: ./get_final_states_infomation input_class_name (all/2f/4f/higgs/4f_WW/4f_ZZ..) final_state (l/sl/h/lep/e2/e1..)" 
	exit
fi


input_class_name=${1,,}
input_final_state=${2,,}




if [[ ${input_class_name} = "higgs" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("e1" "e2" "e3" "n" "q" )
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_eeww" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("eeveev" "eevelv" "eevlev" "eevllv" "eeveyx" "eexyev" "eevlyx" "eexylv" "eexyyx")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_llww" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("llvelv" "llvlev" "llvllv" "llveyx" "llxyev" "llvlyx" "llxylv" "llxyyx")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_ttbar" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("yyveev" "yyvelv" "yyvlev" "yyvllv" "yyveyx" "yyxyev" "yyvlyx" "yyxylv" "yyuyyu" "yyuyyc" "yycyyu" "yycyyc")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_vvww" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("vvveev"  "vvvelv"  "vvvlev"  "vvvllv"  "vvveyx"  "vvxyev"  "vvvlyx"  "vvxylv"  "vvxyyx")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_xxww" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("xxveev" "xxvelv" "xxvlev" "xxvllv" "xxveyx" "xxxyev" "xxvlyx" "xxxylv" "xxxyyx")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_xxxxz" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("vvvvxx" "vvvvyy" "xxxxee" "xxxxvv" "xxxxll" "xxxxxx")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "6f_yyyyz" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("eeeeee" "eeeell" "llllee" "llllll" "eeeexx" "eeeeyy" "eellxx" "eellyy" "yyyyee" "yyyyll" "yyyyyy" "yyyyvv")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "nh" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=(10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "2f_z" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("leptonic" "semileptonic" "hadronic" "bhabhag")
	elif [[ ${input_final_state} = "lep" ]] ; then
		final_states=("leptonic" "bhabhag")
	elif [[ ${input_final_state} = "l" ]] ; then
		final_states=("leptonic")
	elif [[ ${input_final_state} = "sl" ]] ; then
		final_states=("semileptonic")
	elif [[ ${input_final_state} = "h" ]] ; then
		final_states=("hadronic")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "aa_2f" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("ee" "ll" "xx" "yy" )
	elif [[ ${input_final_state} = "2f" ]] ; then
		final_states=("ee" "ll" "xx" "yy")
	else
		final_states=${input_final_state}
	fi
elif [[ ${input_class_name} = "aa_minijet" ]] ; then
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("min0410m1" "min1020m1" "min2040m1" "min40xxm1" "min0410m4" "min1020m4" "min2040m4" "min40xxm4" )
	elif [[ ${input_final_state} = "minijet" ]] ; then
		final_states=("min0410m1" "min1020m1" "min2040m1" "min40xxm1" "min0410m4" "min1020m4" "min2040m4" "min40xxm4")
	else
		final_states=${input_final_state}
	fi
else
	if [[ ${input_final_state} = "all" ]] ; then
		final_states=("leptonic" "semileptonic" "hadronic")
	elif [[ ${input_final_state} = "l" ]] ; then
		final_states=("leptonic")
	elif [[ ${input_final_state} = "sl" ]] ; then
		final_states=("semileptonic")
	elif [[ ${input_final_state} = "h" ]] ; then
		final_states=("hadronic")
	else
		final_states=("${input_final_state}")
	fi
fi	


class_name=${input_class_name}


for j in "${final_states[@]}"
do
	final_state=${j}

	echo "final_state name:  "${final_state}
	info=" ./get_all_polarization.sh ${class_name} ${final_state} "
	eval $info
	echo "end of final_state:  "${final_state}
done
