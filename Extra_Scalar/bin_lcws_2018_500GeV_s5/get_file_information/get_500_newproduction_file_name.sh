#!/bin/bash
#this script can get the slcio file name, and how many files and basic information about the channel; 

if [[ $# != 7 ]] ; then
	echo "usage: ./get_file_name.sh energy(250/350/500/1000) input_class_name (higgs/4f_WW/4f_ZZ/2f_Z..) final_state (leptonic/hadronic/e2/e1..) pol_in (LR/lr/RL...)  ILD_version, reconstruction_version,simulation_version "
	echo "recommand to use small letter for class name and final state name and polarization."
	exit
fi

energy=${1}
energy_version=${energy}-TDR_ws
input_class_name=${2,,}
input_final_states=${3,,}
pol_in=${4,,}
ILD_version=$5
reconstruction_version=$6
simulation_version=$7



if [[  ${input_class_name} == "aa_2f" || ${input_class_name} == "aa_minijet" ]] ; then
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

if [[ ${input_class_name} == "4f_ww" ]] ; then
	class_name="4f_WW"
	short_class_name="4f_ww"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250026
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250028
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10305
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10306
		fi
	elif [[ ${input_final_states} == "semileptonic" || ${input_final_states} == "sl" ]] ; then
		final_states="semileptonic"
		short_final_states="_sl"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250018
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250020
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10318
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10317
		fi
	elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
		final_states="hadronic"
		short_final_states="_h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250006
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250008
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10398
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10397
		fi
	else
		echo "no such 4f_ww final state"
		exit
	fi

elif [[ ${input_class_name} == "4f_zz" ]] ; then
	class_name="4f_ZZ"
	short_class_name="4f_zz"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250022
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250024
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10310
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10309
		fi
	elif [[ ${input_final_states} == "semileptonic" || ${input_final_states} == "sl" ]] ; then
		final_states="semileptonic"
		short_final_states="_sl"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250014
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250016
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10301
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10302
		fi
	elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
		final_states="hadronic"
		short_final_states="_h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250002
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250004
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10402
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10401
		fi
	else
		echo "no such 4f_zz final state"
		exit
	fi

elif [[ ${input_class_name} == "4f_zzww" || ${input_class_name} == "4f_zzwwmix" ]] ; then
	class_name="4f_ZZWWMix"
	short_class_name="4f_zzorww"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250030
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250032
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10314
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10313
		fi
	elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
		final_states="hadronic"
		short_final_states="_h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250010
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250012
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10405
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10406
		fi
	else
		echo "no such 4f_zzww final state"
		exit
	fi

elif [[ ${input_class_name} == "4f_szee" || ${input_class_name} == "4f_singlezee" ]] ; then
	class_name="4f_singleZee"
	short_class_name="4f_sze"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250034
			if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
				file_postid=10446
			elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
				file_postid=10445
			fi
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250036
			if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
				file_postid=10475
			elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
				file_postid=10476
			fi
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=250033
			if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
				file_postid=10442
			elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
				file_postid=10441
			fi
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=250035
			if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
				file_postid=10450
			elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
				file_postid=10449
			fi
		else
			exit
		fi
	elif [[ ${input_final_states} == "semileptonic" || ${input_final_states} == "sl" ]] ; then
		final_states="semileptonic"
		short_final_states="_sl"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250038
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250040
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=250037
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=250039
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10421
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10422
		fi
	else
		echo "no such 4f_szee final state"
		exit
	fi

elif [[ ${input_class_name} == "4f_sznn" || ${input_class_name} == "4f_singleznunu" ]] ; then
	class_name="4f_singleZnunu"
	short_class_name="4f_sznu"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250054
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250056
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10290
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10289
		fi
	elif [[ ${input_final_states} == "semileptonic" || ${input_final_states} == "sl" ]] ; then
		final_states="semileptonic"
		short_final_states="_sl"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250058
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250060
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10425
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10426
		fi
	else
		echo "no such 4f_sznn final state"
		exit
	fi

elif [[ ${input_class_name} == "4f_szsw" || ${input_class_name} == "4f_singlezsinglewmix" ]] ; then
	class_name="4f_singleZsingleWMix"
	short_class_name="4f_szeorsw"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250050
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250052
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=250049
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=250051
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10293
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10294
		fi
	else
		echo "no such 4f_szsw final state"
		exit
	fi

elif [[ ${input_class_name} == "4f_sw" || ${input_class_name} == "4f_singlew" ]] ; then
	class_name="4f_singleW"
	short_class_name="4f_sw"
	info_class_name="4f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250046
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250048
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=250045
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=250047
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10267
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10268
		fi
	elif [[ ${input_final_states} == "semileptonic" || ${input_final_states} == "sl" ]] ; then
		final_states="semileptonic"
		short_final_states="_sl"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250042
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250044
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=250041
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=250043
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10417
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10418
		fi
	else
		echo "no such 4f_sw final state"
		exit
	fi

elif [[ ${input_class_name} == "2f_z" ]] ; then
	class_name="2f_Z"
	short_class_name="2f_z"
	info_class_name="2f"
	if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
		final_states="leptonic"
		short_final_states="_l"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250106
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250108
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10255
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10256
		fi
	elif [[ ${input_final_states} == "bhabhag" || ${input_final_states} == "bha" ]] ; then
		final_states="bhabhag"
		short_final_states="_bhabhag"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250102
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250104
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=250101
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=250103
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10366
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10365
		fi
	elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
		final_states="hadronic"
		short_final_states="_h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250114
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250116
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10410
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10409
		fi
	else
		echo "no such 2f_z final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_eeww" ]] ; then
	class_name="6f_eeWW"
	short_class_name=""
	info_class_name="6f_eeWW"
	if [[ ${input_final_states} == "eeveev" ]] ; then
		final_states="ev"
		short_final_states=eeveev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108620
			file_id_gen=36942
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108621
			file_id_gen=36943
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108619
			file_id_gen=36941
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108622
			file_id_gen=36944
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10322
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10321
		fi
	elif [[ ${input_final_states} == "eevelv" ]] ; then
		final_states="ev"
		short_final_states=eevelv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108624
			file_id_gen=36946
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108625
			file_id_gen=36947
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108623
			file_id_gen=36945
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108626
			file_id_gen=36948
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10361
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10362
		fi
	elif [[ ${input_final_states} == "eevlev" ]] ; then
		final_states="ev"
		short_final_states=eevlev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108628
			file_id_gen=36954
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108629
			file_id_gen=36955
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108627
			file_id_gen=36953
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108630
			file_id_gen=36956
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10361
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10362
		fi
	elif [[ ${input_final_states} == "eevllv" ]] ; then
		final_states="ev"
		short_final_states=eevllv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108632
			file_id_gen=36958
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108633
			file_id_gen=36959
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108631
			file_id_gen=36957
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108634
			file_id_gen=36960
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10361
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10362
		fi
	elif [[ ${input_final_states} == "eeveyx" ]] ; then
		final_states="ev"
		short_final_states=eeveyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108636
			file_id_gen=36950
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108637
			file_id_gen=36951
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108635
			file_id_gen=36949
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108638
			file_id_gen=36952
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10322
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10321
		fi
	elif [[ ${input_final_states} == "eexyev" ]] ; then
		final_states="ev"
		short_final_states=eexyev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108640
			file_id_gen=36966
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108641
			file_id_gen=36967
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108639
			file_id_gen=36965
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108642
			file_id_gen=36968
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10322
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10321
		fi
	elif [[ ${input_final_states} == "eevlyx" ]] ; then
		final_states="ev"
		short_final_states=eevlyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108644
			file_id_gen=36962
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108645
			file_id_gen=36963
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108643
			file_id_gen=36961
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108646
			file_id_gen=36964
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10361
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10362
		fi
	elif [[ ${input_final_states} == "eexylv" ]] ; then
		final_states="ev"
		short_final_states=eexylv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108648
			file_id_gen=36970
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108649
			file_id_gen=36971
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108647
			file_id_gen=36969
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108650
			file_id_gen=36972
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10361
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10362
		fi
	elif [[ ${input_final_states} == "eexyyx" ]] ; then
		final_states="ev"
		short_final_states=eexyyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108652
			file_id_gen=36974
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108653
			file_id_gen=36975
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108651
			file_id_gen=36973
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108654
			file_id_gen=36976
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10322
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10321
		fi
	else
		echo "no such 6f_eeWW final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_llww" ]] ; then
	class_name="6f_llWW"
	short_class_name=""
	info_class_name="6f_llWW"
	if [[ ${input_final_states} == "llvelv" ]] ; then
		final_states=""
		short_final_states=llvelv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108576
			file_id_gen=36978
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108577
			file_id_gen=36979
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108575
			file_id_gen=36977
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llvlev" ]] ; then
		final_states=""
		short_final_states=llvlev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108578
			file_id_gen=36986
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108579
			file_id_gen=36987
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108580
			file_id_gen=36988
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llvllv" ]] ; then
		final_states=""
		short_final_states=llvllv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108581
			file_id_gen=36990
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108582
			file_id_gen=36991
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llveyx" ]] ; then
		final_states=""
		short_final_states=llveyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108584
			file_id_gen=36982
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108585
			file_id_gen=36983
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108583
			file_id_gen=36981
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llxyev" ]] ; then
		final_states=""
		short_final_states=llxyev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108586
			file_id_gen=36998
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108587
			file_id_gen=36999
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108588
			file_id_gen=37000
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llvlyx" ]] ; then
		final_states=""
		short_final_states=llvlyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108589
			file_id_gen=36994
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108590
			file_id_gen=36995
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llxylv" ]] ; then
		final_states=""
		short_final_states=llxylv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108591
			file_id_gen=37002
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108592
			file_id_gen=37003
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	elif [[ ${input_final_states} == "llxyyx" ]] ; then
		final_states=""
		short_final_states=llxyyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108593
			file_id_gen=37006
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108594
			file_id_gen=37007
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10358
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10357
		fi
	else
		echo "no such 6f_llWW final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_ttbar" ]] ; then
	class_name="6f_ttbar"
	short_class_name=""
	info_class_name="6f_ttbar"
	if [[ ${input_final_states} == "yyveev" ]] ; then
		final_states=""
		short_final_states=yyveev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108656
			file_id_gen=36874
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108657
			file_id_gen=36875
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108655
			file_id_gen=36873
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108658
			file_id_gen=36876
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10271
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10272
		fi
	elif [[ ${input_final_states} == "yyvelv" ]] ; then
		final_states=""
		short_final_states=yyvelv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108660
			file_id_gen=36878
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108661
			file_id_gen=36879
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108659
			file_id_gen=36877
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10276
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10275
		fi
	elif [[ ${input_final_states} == "yyvlev" ]] ; then
		final_states=""
		short_final_states=yyvlev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108662
			file_id_gen=36886
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108663
			file_id_gen=36887
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108664
			file_id_gen=36888
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10276
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10275
		fi
	elif [[ ${input_final_states} == "yyvllv" ]] ; then
		final_states=""
		short_final_states=yyvllv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108665
			file_id_gen=36890
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108666
			file_id_gen=36891
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10276
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10275
		fi
	elif [[ ${input_final_states} == "yyveyx" ]] ; then
		final_states=""
		short_final_states=yyveyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108668
			file_id_gen=36882
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108669
			file_id_gen=36883
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108667
			file_id_gen=36881
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10271
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10272
		fi
	elif [[ ${input_final_states} == "yyxyev" ]] ; then
		final_states=""
		short_final_states=yyxyev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108670
			file_id_gen=36898
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108671
			file_id_gen=36899
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108672
			file_id_gen=36900
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10429
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10430
		fi
	elif [[ ${input_final_states} == "yyvlyx" ]] ; then
		final_states=""
		short_final_states=yyvlyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108673
			file_id_gen=36894
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108674
			file_id_gen=36895
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10276
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10275
		fi
	elif [[ ${input_final_states} == "yyxylv" ]] ; then
		final_states=""
		short_final_states=yyxylv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108675
			file_id_gen=36902
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108676
			file_id_gen=36903
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10276
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10275
		fi
	elif [[ ${input_final_states} == "yyuyyu" ]] ; then
		final_states=""
		short_final_states=yyuyyu
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108677
			file_id_gen=000
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108678
			file_id_gen=000
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10433
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10434
		fi
	elif [[ ${input_final_states} == "yyuyyc" ]] ; then
		final_states=""
		short_final_states=yyuyyc
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108679
			file_id_gen=36910
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108680
			file_id_gen=36911
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10433
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10434
		fi
	elif [[ ${input_final_states} == "yycyyu" ]] ; then
		final_states=""
		short_final_states=yycyyu
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108681
			file_id_gen=36914
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108682
			file_id_gen=36915
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10437
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10438
		fi
	elif [[ ${input_final_states} == "yycyyc" ]] ; then
		final_states=""
		short_final_states=yycyyc
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108683
			file_id_gen=000
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108684
			file_id_gen=000
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10437
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10438
		fi
	else
		echo "no such 6f_ttbar final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_vvww" ]] ; then
	class_name="6f_vvWW"
	short_class_name=""
	info_class_name="6f_vvWW"
	if [[ ${input_final_states} == "vvveev" ]] ; then
		final_states=""
		short_final_states=vvveev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108596
			file_id_gen=37010
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108597
			file_id_gen=37011
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108595
			file_id_gen=37009
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108598
			file_id_gen=37012
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10354
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10353
		fi
	elif [[ ${input_final_states} == "vvvelv" ]] ; then
		final_states=""
		short_final_states=vvvelv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108600
			file_id_gen=37014
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108601
			file_id_gen=37015
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108599
			file_id_gen=37013
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10349
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10350
		fi
	elif [[ ${input_final_states} == "vvvlev" ]] ; then
		final_states=""
		short_final_states=vvvlev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108602
			file_id_gen=37022
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108603
			file_id_gen=37023
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108604
			file_id_gen=37024
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10349
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10350
		fi
	elif [[ ${input_final_states} == "vvvllv" ]] ; then
		final_states=""
		short_final_states=vvvllv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108605
			file_id_gen=37026
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108606
			file_id_gen=37027
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10349
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10350
		fi
	elif [[ ${input_final_states} == "vvveyx" ]] ; then
		final_states=""
		short_final_states=vvveyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108608
			file_id_gen=37018
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108609
			file_id_gen=37019
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108607
			file_id_gen=37017
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10354
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10353
		fi
	elif [[ ${input_final_states} == "vvxyev" ]] ; then
		final_states=""
		short_final_states=vvxyev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108610
			file_id_gen=37034
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108611
			file_id_gen=37035
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108612
			file_id_gen=37036
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10354
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10353
		fi
	elif [[ ${input_final_states} == "vvvlyx" ]] ; then
		final_states=""
		short_final_states=vvvlyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108613
			file_id_gen=37030
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108614
			file_id_gen=37031
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10349
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10350
		fi
	elif [[ ${input_final_states} == "vvxylv" ]] ; then
		final_states=""
		short_final_states=vvxylv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108615
			file_id_gen=37038
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108616
			file_id_gen=37039
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10349
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10350
		fi
	elif [[ ${input_final_states} == "vvxyyx" ]] ; then
		final_states=""
		short_final_states=vvxyyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108617
			file_id_gen=37042
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108618
			file_id_gen=37043
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10354
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10353
		fi
	else
		echo "no such 6f_vvWW final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_xxww" ]] ; then
	class_name="6f_xxWW"
	short_class_name=""
	info_class_name="6f_xxWW"
	if [[ ${input_final_states} == "xxveev" ]] ; then
		final_states=""
		short_final_states=xxveev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108502
			file_id_gen=37046
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108503
			file_id_gen=37047
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108501
			file_id_gen=37045
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108504
			file_id_gen=37048
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10346
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10345
		fi
	elif [[ ${input_final_states} == "xxvelv" ]] ; then
		final_states=""
		short_final_states=xxvelv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108506
			file_id_gen=37050
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108507
			file_id_gen=37051
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108505
			file_id_gen=37049
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10342
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10341
		fi
	elif [[ ${input_final_states} == "xxvlev" ]] ; then
		final_states=""
		short_final_states=xxvlev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108508
			file_id_gen=37058
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108509
			file_id_gen=37059
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108510
			file_id_gen=37060
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10342
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10341
		fi
	elif [[ ${input_final_states} == "xxvllv" ]] ; then
		final_states=""
		short_final_states=xxvllv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108511
			file_id_gen=37062
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108512
			file_id_gen=37063
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10342
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10341
		fi
	elif [[ ${input_final_states} == "xxveyx" ]] ; then
		final_states=""
		short_final_states=xxveyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108514
			file_id_gen=37054
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108515
			file_id_gen=37055
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108513
			file_id_gen=37053
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10346
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10345
		fi
	elif [[ ${input_final_states} == "xxxyev" ]] ; then
		final_states=""
		short_final_states=xxxyev
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108516
			file_id_gen=37070
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108517
			file_id_gen=37071
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108518
			file_id_gen=37072
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10346
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10345
		fi
	elif [[ ${input_final_states} == "xxvlyx" ]] ; then
		final_states=""
		short_final_states=xxvlyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108519
			file_id_gen=37066
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108520
			file_id_gen=37067
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10342
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10341
		fi
	elif [[ ${input_final_states} == "xxxylv" ]] ; then
		final_states=""
		short_final_states=xxxylv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108521
			file_id_gen=37074
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108522
			file_id_gen=37075
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10342
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10341
		fi
	elif [[ ${input_final_states} == "xxxyyx" ]] ; then
		final_states=""
		short_final_states=xxxyyx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108687
			file_id_gen=37078
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108688
			file_id_gen=37079
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10346
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10345
		fi
	else
		echo "no such 6f_xxWW final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_xxxxz" ]] ; then
	class_name="6f_xxxxZ"
	short_class_name=""
	info_class_name="6f_xxxxZ"
	if [[ ${input_final_states} == "vvvvxx" ]] ; then
		final_states=""
		short_final_states=vvvvxx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108523
			file_id_gen=37098
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108524
			file_id_gen=37099
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10338
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10337
		fi
	elif [[ ${input_final_states} == "vvvvyy" ]] ; then
		final_states=""
		short_final_states=vvvvyy
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108525
			file_id_gen=37102
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108526
			file_id_gen=37103
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10338
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10337
		fi
	elif [[ ${input_final_states} == "xxxxee" ]] ; then
		final_states=""
		short_final_states=xxxxee
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108528
			file_id_gen=37094
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108529
			file_id_gen=37095
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108527
			file_id_gen=37093
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108530
			file_id_gen=37096
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10338
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10337
		fi
	elif [[ ${input_final_states} == "xxxxvv" ]] ; then
		final_states=""
		short_final_states=xxxxvv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108531
			file_id_gen=37086
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108532
			file_id_gen=37087
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10338
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10337
		fi
	elif [[ ${input_final_states} == "xxxxll" ]] ; then
		final_states=""
		short_final_states=xxxxll
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108533
			file_id_gen=37090
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108534
			file_id_gen=37091
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10333
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10334
		fi
	elif [[ ${input_final_states} == "xxxxxx" ]] ; then
		final_states=""
		short_final_states=xxxxxx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108535
			file_id_gen=37082
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108536
			file_id_gen=37083
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10338
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10337
		fi
	else
		echo "no such 6f_xxxxZ final state"
		exit
	fi

elif [[ ${input_class_name} == "6f_yyyyz" ]] ; then
	class_name="6f_yyyyZ"
	short_class_name=""
	info_class_name="6f_yyyyZ"
	if [[ ${input_final_states} == "eeeeee" ]] ; then
		final_states=""
		short_final_states=eeeeee
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108538
			file_id_gen=37150
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108539
			file_id_gen=37151
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108537
			file_id_gen=37149
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108540
			file_id_gen=37152
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10330
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10329
		fi
	elif [[ ${input_final_states} == "eeeell" ]] ; then
		final_states=""
		short_final_states=eeeell
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108542
			file_id_gen=37146
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108543
			file_id_gen=37147
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108541
			file_id_gen=37145
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108544
			file_id_gen=37148
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10326
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10325
		fi
	elif [[ ${input_final_states} == "llllee" ]] ; then
		final_states=""
		short_final_states=llllee
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108546
			file_id_gen=37142
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108547
			file_id_gen=37143
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108545
			file_id_gen=37141
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108548
			file_id_gen=37144
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10326
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10325
		fi
	elif [[ ${input_final_states} == "llllll" ]] ; then
		final_states=""
		short_final_states=llllll
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108549
			file_id_gen=37138
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108550
			file_id_gen=37139
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10326
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10325
		fi
	elif [[ ${input_final_states} == "eeeexx" ]] ; then
		final_states=""
		short_final_states=eeeexx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108552
			file_id_gen=37130
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108553
			file_id_gen=37131
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108551
			file_id_gen=37129
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108554
			file_id_gen=37132
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10330
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10329
		fi
	elif [[ ${input_final_states} == "eeeeyy" ]] ; then
		final_states=""
		short_final_states=eeeeyy
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108556
			file_id_gen=37134
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108557
			file_id_gen=37135
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108555
			file_id_gen=37133
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108558
			file_id_gen=37136
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10330
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10329
		fi
	elif [[ ${input_final_states} == "eellxx" ]] ; then
		final_states=""
		short_final_states=eellxx
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108560
			file_id_gen=37122
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108561
			file_id_gen=37123
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108559
			file_id_gen=37121
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108562
			file_id_gen=37124
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10326
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10325
		fi
	elif [[ ${input_final_states} == "eellyy" ]] ; then
		final_states=""
		short_final_states=eellyy
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108564
			file_id_gen=37126
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108565
			file_id_gen=37127
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108563
			file_id_gen=37125
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108566
			file_id_gen=37128
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10326
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10325
		fi
	elif [[ ${input_final_states} == "yyyyee" ]] ; then
		final_states=""
		short_final_states=yyyyee
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108568
			file_id_gen=37118
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108569
			file_id_gen=37119
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108567
			file_id_gen=37117
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108570
			file_id_gen=37120
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10330
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10329
		fi
	elif [[ ${input_final_states} == "yyyyll" ]] ; then
		final_states=""
		short_final_states=yyyyll
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108571
			file_id_gen=37114
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108572
			file_id_gen=37115
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10326
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10325
		fi
	elif [[ ${input_final_states} == "yyyyyy" ]] ; then
		final_states=""
		short_final_states=yyyyyy
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108573
			file_id_gen=37106
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108574
			file_id_gen=37107
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10330
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10329
		fi
	elif [[ ${input_final_states} == "yyyyvv" ]] ; then
		final_states=""
		short_final_states=yyyyvv
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108685
			file_id_gen=37110
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108686
			file_id_gen=37111
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10330
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10329
		fi
	else
		echo "no such 6f_yyyyZ final state"
		exit
	fi


elif [[ ${input_class_name} == "higgs" ]] ; then
	class_name="higgs"
	short_class_name=""
	info_class_name="higgs"
	if [[ ${input_final_states} == "e1" ]] ; then
		final_states="e1"
		short_final_states=e1e1h
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=106516
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=106517
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=106515
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=106518
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10263
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10264
		fi
	elif [[ ${input_final_states} == "e2" ]] ; then
		final_states="e2"
		short_final_states=e2e2h
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=106519
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=106520
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10263
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10264
		fi
	elif [[ ${input_final_states} == "e3" ]] ; then
		final_states="e3"
		short_final_states=e3e3h
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=106521
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=106522
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10263
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10264
		fi
	elif [[ ${input_final_states} == "n" ]] ; then
		final_states="n"
		short_final_states=nnh
		if [[ ${polarization} == "eL.pR" ]] ; then
			echo "no such file"
			exit
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=106524
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10297
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10298
		fi
	elif [[ ${input_final_states} == "q" ]] ; then
		final_states="q"
		short_final_states=qqh
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=106525
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=106526
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10297
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10298
		fi
	elif [[ ${input_final_states} == "f" ]] ; then
		final_states="f"
		short_final_states=ffh_mumu
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=108162
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=108163
		elif [[ ${polarization} == "eL.pL"  ]] ; then
			file_id=108161
		elif [[ ${polarization} == "eR.pR"  ]] ; then
			file_id=108164
		else
			exit
		fi
		if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
			file_postid=10260
		elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
			file_postid=10259
		fi
	else
		echo "no such higgs final state"
		exit
	fi

elif [[ ${input_class_name} == "nh" || ${input_class_name} == "np-light-higgs" ]] ; then
	class_name="np-light-higgs"
	short_class_name=""
	info_class_name="np-light-higgs"
	if [[ ${ILD_version} == "ILD_l5_o1_v02" ]]; then
		file_postid=10929
	elif [[ ${ILD_version} == "ILD_s5_o1_v02" ]]; then
		file_postid=10928
	fi
	if [[ ${input_final_states} == "10" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh10_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250260
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250261
		else
			exit
		fi
	elif [[ ${input_final_states} == "15" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh15_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250262
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250263
		else
			exit
		fi
	elif [[ ${input_final_states} == "20" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh20_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250264
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250265
		else
			exit
		fi
	elif [[ ${input_final_states} == "25" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh25_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250266
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250267
		else
			exit
		fi
	elif [[ ${input_final_states} == "30" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh30_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250268
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250269
		else
			exit
		fi
	elif [[ ${input_final_states} == "35" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh35_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250270
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250271
		else
			exit
		fi
	elif [[ ${input_final_states} == "40" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh40_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250272
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250273
		else
			exit
		fi
	elif [[ ${input_final_states} == "45" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh45_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250274
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250275
		else
			exit
		fi
	elif [[ ${input_final_states} == "50" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh50_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250276
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250277
		else
			exit
		fi
	elif [[ ${input_final_states} == "55" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh55_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250278
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250279
		else
			exit
		fi
	elif [[ ${input_final_states} == "60" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh60_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250280
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250281
		else
			exit
		fi
	elif [[ ${input_final_states} == "65" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh65_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250282
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250283
		else
			exit
		fi
	elif [[ ${input_final_states} == "70" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh70_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250284
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250285
		else
			exit
		fi
	elif [[ ${input_final_states} == "75" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh75_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250286
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250287
		else
			exit
		fi
	elif [[ ${input_final_states} == "80" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh80_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250288
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250289
		else
			exit
		fi
	elif [[ ${input_final_states} == "85" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh85_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250290
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250291
		else
			exit
		fi
	elif [[ ${input_final_states} == "90" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh90_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250292
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250293
		else
			exit
		fi
	elif [[ ${input_final_states} == "95" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh95_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250294
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250295
		else
			exit
		fi
	elif [[ ${input_final_states} == "100" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh100_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250296
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250297
		else
			exit
		fi
	elif [[ ${input_final_states} == "105" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh105_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250298
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250299
		else
			exit
		fi
	elif [[ ${input_final_states} == "110" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh110_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250300
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250301
		else
			exit
		fi
	elif [[ ${input_final_states} == "115" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh115_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250302
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250303
		else
			exit
		fi
	elif [[ ${input_final_states} == "120" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh120_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250304
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250305
		else
			exit
		fi
	elif [[ ${input_final_states} == "130" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh130_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250308
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250309
		else
			exit
		fi
	elif [[ ${input_final_states} == "135" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh135_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250310
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250311
		else
			exit
		fi
	elif [[ ${input_final_states} == "140" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh140_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250312
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250313
		else
			exit
		fi
	elif [[ ${input_final_states} == "145" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh145_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250314
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250315
		else
			exit
		fi
	elif [[ ${input_final_states} == "150" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh150_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250316
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250317
		else
			exit
		fi
	elif [[ ${input_final_states} == "155" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh155_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250318
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250319
		else
			exit
		fi
	elif [[ ${input_final_states} == "160" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh160_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250320
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250321
		else
			exit
		fi
	elif [[ ${input_final_states} == "165" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh165_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250322
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250323
		else
			exit
		fi
	elif [[ ${input_final_states} == "170" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh170_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250324
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250325
		else
			exit
		fi
	elif [[ ${input_final_states} == "175" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh175_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250326
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250327
		else
			exit
		fi
	elif [[ ${input_final_states} == "180" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh180_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250328
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250329
		else
			exit
		fi
	elif [[ ${input_final_states} == "185" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh185_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250330
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250331
		else
			exit
		fi
	elif [[ ${input_final_states} == "190" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh190_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250332
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250333
		else
			exit
		fi
	elif [[ ${input_final_states} == "195" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh195_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250334
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250335
		else
			exit
		fi
	elif [[ ${input_final_states} == "200" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh200_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250336
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250337
		else
			exit
		fi
	elif [[ ${input_final_states} == "205" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh210_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250338
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250339
		else
			exit
		fi
	elif [[ ${input_final_states} == "210" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh215_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250340
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250341
		else
			exit
		fi
	elif [[ ${input_final_states} == "215" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh215_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250342
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250343
		else
			exit
		fi
	elif [[ ${input_final_states} == "220" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh220_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250344
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250345
		else
			exit
		fi
	elif [[ ${input_final_states} == "225" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh225_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250346
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250347
		else
			exit
		fi
	elif [[ ${input_final_states} == "230" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh230_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250348
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250349
		else
			exit
		fi
	elif [[ ${input_final_states} == "235" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh235_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250350
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250351
		else
			exit
		fi
	elif [[ ${input_final_states} == "240" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh240_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250352
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250353
		else
			exit
		fi
	elif [[ ${input_final_states} == "245" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh245_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250354
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250355
		else
			exit
		fi
	elif [[ ${input_final_states} == "250" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh250_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250356
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250357
		else
			exit
		fi
	elif [[ ${input_final_states} == "255" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh255_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250358
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250359
		else
			exit
		fi
	elif [[ ${input_final_states} == "260" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh260_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250360
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250361
		else
			exit
		fi
	elif [[ ${input_final_states} == "265" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh265_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250362
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250363
		else
			exit
		fi
	elif [[ ${input_final_states} == "270" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh270_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250364
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250365
		else
			exit
		fi
	elif [[ ${input_final_states} == "275" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh275_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250366
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250367
		else
			exit
		fi
	elif [[ ${input_final_states} == "280" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh280_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250368
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250369
		else
			exit
		fi
	elif [[ ${input_final_states} == "285" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh285_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250370
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250371
		else
			exit
		fi
	elif [[ ${input_final_states} == "290" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh290_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250372
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250373
		else
			exit
		fi
	elif [[ ${input_final_states} == "295" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh295_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250374
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250375
		else
			exit
		fi
	elif [[ ${input_final_states} == "300" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh300_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250376
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250377
		else
			exit
		fi
	elif [[ ${input_final_states} == "305" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh305_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250378
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250379
		else
			exit
		fi
	elif [[ ${input_final_states} == "310" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh310_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250380
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250381
		else
			exit
		fi
	elif [[ ${input_final_states} == "315" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh315_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250382
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250383
		else
			exit
		fi
	elif [[ ${input_final_states} == "320" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh320_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250384
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250385
		else
			exit
		fi
	elif [[ ${input_final_states} == "325" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh325_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250386
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250387
		else
			exit
		fi
	elif [[ ${input_final_states} == "330" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh330_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250388
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250389
		else
			exit
		fi
	elif [[ ${input_final_states} == "335" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh335_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250390
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250391
		else
			exit
		fi
	elif [[ ${input_final_states} == "340" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh340_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250392
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250393
		else
			exit
		fi
	elif [[ ${input_final_states} == "345" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh345_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250394
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250395
		else
			exit
		fi
	elif [[ ${input_final_states} == "350" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh350_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250396
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250397
		else
			exit
		fi
	elif [[ ${input_final_states} == "355" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh355_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250398
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250399
		else
			exit
		fi
	elif [[ ${input_final_states} == "360" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh360_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250400
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250401
		else
			exit
		fi
	elif [[ ${input_final_states} == "365" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh365_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250402
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250403
		else
			exit
		fi
	elif [[ ${input_final_states} == "370" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh370_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250404
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250405
		else
			exit
		fi
	elif [[ ${input_final_states} == "375" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh375_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250406
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250407
		else
			exit
		fi
	elif [[ ${input_final_states} == "380" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh380_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250408
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250409
		else
			exit
		fi
	elif [[ ${input_final_states} == "385" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh385_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250410
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250411
		else
			exit
		fi
	elif [[ ${input_final_states} == "390" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh390_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250412
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250413
		else
			exit
		fi
	elif [[ ${input_final_states} == "395" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh395_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250414
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250415
		else
			exit
		fi
	elif [[ ${input_final_states} == "400" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh400_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250416
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250417
		else
			exit
		fi
	elif [[ ${input_final_states} == "405" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh405_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250418
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250419
		else
			exit
		fi
	elif [[ ${input_final_states} == "408" ]] ; then
		final_states="e2"
		short_final_states="np-lmh_mh408_e2e2h"
		if [[ ${polarization} == "eL.pR" ]] ; then
			file_id=250420
		elif [[ ${polarization} == "eR.pL"  ]] ; then
			file_id=250421
		else
			exit
		fi
	else
		echo "no such np-light-higgs final state"
		exit
	fi

elif [[ ${input_class_name} == "aa_2f" ]] ; then
	class_name="aa"
	short_class_name="aa"
	if [[ ${input_final_states} == "ee" ]] ; then
		final_states="2f"
		short_final_states="_ee"
		info_class_name="aa_2f"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37761
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37762
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37763
		elif [[ ${polarization} == "eB.pB"  ]] ; then
			file_id=37764
		else
			exit
		fi
	elif [[ ${input_final_states} == "ll" ]] ; then
		final_states="2f"
		short_final_states="_ll"
		info_class_name="aa_2f"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37765
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37766
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37767
		elif [[ ${polarization} == "eB.pB"  ]] ; then
			file_id=37768
		else
			exit
		fi
	elif [[ ${input_final_states} == "xx" ]] ; then
		final_states="2f"
		short_final_states="_xx"
		info_class_name="aa_2f"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37769
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37770
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37771
		elif [[ ${polarization} == "eB.pB"  ]] ; then
			file_id=37772
		else
			exit
		fi
	elif [[ ${input_final_states} == "yy" ]] ; then
		final_states="2f"
		short_final_states="_yy"
		info_class_name="aa_2f"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37773
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37774
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37775
		elif [[ ${polarization} == "eB.pB"  ]] ; then
			file_id=37776
		else
			exit
		fi
	else
		echo "no such higgs final state"
		exit
	fi
elif [[ ${input_class_name} == "aa_minijet" ]] ; then
	class_name="aa"
	short_class_name="aa"
	if [[ ${input_final_states} == "min0410m1" ]] ; then
		final_states="minijet"
		short_final_states="min_04_10_m1"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37833
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37834
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37835
		else
			exit
		fi
	elif [[ ${input_final_states} == "min1020m1" ]] ; then
		final_states="minijet"
		short_final_states="min_10_20_m1"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37837
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37838
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37839
		else
			exit
		fi
	elif [[ ${input_final_states} == "min2040m1" ]] ; then
		final_states="minijet"
		short_final_states="min_20_40_m1"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37841
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37842
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37843
		else
			exit
		fi
	elif [[ ${input_final_states} == "min40xxm1" ]] ; then
		final_states="minijet"
		short_final_states="min_40_xx_m1"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37845
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37846
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37847
		else
			exit
		fi
	elif [[ ${input_final_states} == "min0410m4" ]] ; then
		final_states="minijet"
		short_final_states="min_04_10_m4"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37849
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37850
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37851
		else
			exit
		fi
	elif [[ ${input_final_states} == "min1020m4" ]] ; then
		final_states="minijet"
		short_final_states="min_10_20_m4"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37853
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37854
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37855
		else
			exit
		fi
	elif [[ ${input_final_states} == "min2040m4" ]] ; then
		final_states="minijet"
		short_final_states="min_20_40_m4"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37857
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37858
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37859
		else
			exit
		fi
	elif [[ ${input_final_states} == "min40xxm4" ]] ; then
		final_states="minijet"
		short_final_states="min_40_xx_m4"
		info_class_name="aa_minijet"
		if [[ ${polarization} == "eW.pW" ]] ; then
			file_id=37861
		elif [[ ${polarization} == "eW.pB"  ]] ; then
			file_id=37862
		elif [[ ${polarization} == "eB.pW"  ]] ; then
			file_id=37863
		else
			exit
		fi
	elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
		final_states="hadronic"
		short_final_states="aa"
		info_class_name="aa_lowpt"
	else
		echo "no such aa final state"
		exit
	fi
else
	echo "no such class name"

fi



data_source=/pnfs/desy.de/ilc/prod/ilc/mc-opt-3/ild/dst-merged
info_source=/pnfs/desy.de/ilc/prod/ilc/mc-dbd.log/generated 
info_source_spe=/afs/desy.de/user/y/ywang/Code/MyTest2/bin_500/get_file_information/metaspe
if [[ ${class_name} == "higgs" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}_"ffh"/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_eeWW" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_llWW" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_ttbar" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_vvWW" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_xxWW" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_xxxxZ" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "6f_yyyyZ" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "np-light-higgs" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
else
	data_folder=${data_source}/${energy_version}/${class_name}_${final_states}/${ILD_version}/${reconstruction_version}
fi
info_folder=${info_source}/${energy_version}
info_folder_spe=${info_source_spe}/${energy_version}





short_name=${short_class_name}${short_final_states}
file_name_aux1=.n001.d_dstm_${file_postid}

file_name_basic=r${reconstruction_version}.s${simulation_version}.m${ILD_version}.E${energy_version}.I${file_id}.P${short_name}.${polarization}${file_name_aux1}
file_name_ext=.slcio

if [[  ${input_class_name} == "aa_2f" || ${input_class_name} == "aa_minijet" ]] ; then
	info_name=${info_folder}/${info_class_name}/E0${energy_version}.P${short_name}.Gwhizard-1.95.${polarization}.I${file_id}.txt
elif [[ ${class_name} == "6f_eeWW" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
elif [[ ${class_name} == "6f_llWW" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
elif [[ ${class_name} == "6f_ttbar" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	if [[ ${short_final_states} == "yyuyyu" ]]; then
		info_name=${info_folder_spe}/${info_class_name}/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
	elif [[ ${short_final_states} == "yycyyc" ]]; then
		info_name=${info_folder_spe}/${info_class_name}/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
	else
		info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
	fi
elif [[ ${class_name} == "6f_vvWW" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
elif [[ ${class_name} == "6f_xxWW" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
elif [[ ${class_name} == "6f_xxxxZ" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
elif [[ ${class_name} == "6f_yyyyZ" ]] ; then
	short_name_cut=` echo $short_name | cut -f2 -d "_" `
	info_name=${info_folder}/"6f"/E0${energy_version}.P${short_name_cut}.Gwhizard-1.95.${polarization}.I${file_id_gen}.txt
elif [[ ${class_name} == "np-light-higgs" ]] ; then
	short_name_cut=${short_name}
	info_name=${info_folder_spe}/${info_class_name}/E${energy_version}.P${short_name_cut}.Gwhizard-1_95.${polarization}.I${file_id}.txt
else
	info_name=${info_folder}/${info_class_name}/E${energy_version}.P${short_name}.Gwhizard-1_95.${polarization}.I${file_id}.txt
fi









if [ ! -d ${data_folder} ] ; then
	echo "no such folder, please check!"
	exit
fi

	for j in ${data_folder}/${file_name_basic}* 
	do
		fnum=$[fnum+1]
	done
	if [ $j == 0 ] ; then
		echo "file does not exist ${data_folder}/${file_name_basic}*"   
		exit
	fi

fnum=0

for j in ${data_folder}/${file_name_basic}* 
do
	fnum=$[fnum+1]
done







echo "channel is:  ${class_name} ${final_states} ${pol_in} is--------"
echo "info_name:    "${info_name}
xection=` grep "cross_section_in_fb" ${info_name} | cut -d "=" -f2 | sed -e "s/ //g" `
xection_err=` grep "cross_section_error_in_fb" ${info_name} | cut -d "=" -f2 | sed -e "s/ //g" `
lumi=` grep "luminosity" ${info_name} | cut -d "=" -f2 | sed -e "s/ //g" `
totnum=` grep "total_number_of_events" ${info_name} | cut -d "=" -f2 | sed -e "s/ //g" `
echo "xection is:      "${xection}
echo "xection err is:  "${xection_err}
echo "luminosity is:   "${lumi}
echo "totnum is:       "${totnum}


slcio_totnum=0
echo  "file number is:  "$fnum
for j in ${data_folder}/${file_name_basic}* 
do
	full_file_name=$j
	echo "file_name:    "${full_file_name}
	if [[ ${input_class_name} == "aa_minijet" ]]; then
		(( slcio_totnum = totnum ))
	else
		anainfo=" anajob $full_file_name 1 "
		slcio_num=` eval $anainfo | grep "number of events" | cut -d "," -f2 | cut -d ":" -f2  | sed -e "s/ ]//g" `
		echo "file_number:  " $slcio_num
		(( slcio_totnum = slcio_totnum + slcio_num ))
	fi
done
echo "total_file_number:  " $slcio_totnum

