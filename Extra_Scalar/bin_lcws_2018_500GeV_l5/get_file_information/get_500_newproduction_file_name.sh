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

if [[ ${input_final_states} == "leptonic" || ${input_final_states} == "l" ]] ; then
	final_states="leptonic"
	short_final_states="_l"
elif [[ ${input_final_states} == "semileptonic" || ${input_final_states} == "sl" ]] ; then
	final_states="semileptonic"
	short_final_states="_sl"
elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
	final_states="hadronic"
	short_final_states="_h"
elif [[ ${input_final_states} == "bhabhag" || ${input_final_states} == "bha" ]] ; then
	final_states="bhabhag"
	short_final_states="_bhabhag"
elif [[ ${input_final_states} == "e1" ]] ; then
	final_states="e1"
	short_final_states="e1e1h"
elif [[ ${input_final_states} == "e2" ]] ; then
	final_states="e2"
	short_final_states="e2e2h"
elif [[ ${input_final_states} == "n" ]] ; then
	final_states="n"
	short_final_states="nnh"
elif [[ ${input_final_states} == "q" ]] ; then
	final_states="q"
	short_final_states="qqh"
elif [[ ${input_final_states} == "f" ]] ; then
	final_states="f"
	short_final_states="ffh_mumu"
else
	final_states=${input_final_states}
	short_final_states=${input_final_states}
fi

if [[ ${input_class_name} == "4f_ww" ]] ; then
	class_name="4f_WW"
	short_class_name="4f_ww"
	info_class_name="4f"

elif [[ ${input_class_name} == "4f_zz" ]] ; then
	class_name="4f_ZZ"
	short_class_name="4f_zz"
	info_class_name="4f"

elif [[ ${input_class_name} == "4f_zzww" || ${input_class_name} == "4f_zzwwmix" ]] ; then
	class_name="4f_ZZWWMix"
	short_class_name="4f_zzorww"
	info_class_name="4f"

elif [[ ${input_class_name} == "4f_szee" || ${input_class_name} == "4f_singlezee" ]] ; then
	class_name="4f_singleZee"
	short_class_name="4f_sze"
	info_class_name="4f"

elif [[ ${input_class_name} == "4f_sznn" || ${input_class_name} == "4f_singleznunu" ]] ; then
	class_name="4f_singleZnunu"
	short_class_name="4f_sznu"
	info_class_name="4f"

elif [[ ${input_class_name} == "4f_szsw" || ${input_class_name} == "4f_singlezsinglewmix" ]] ; then
	class_name="4f_singleZsingleWMix"
	short_class_name="4f_szeorsw"
	info_class_name="4f"

elif [[ ${input_class_name} == "4f_sw" || ${input_class_name} == "4f_singlew" ]] ; then
	class_name="4f_singleW"
	short_class_name="4f_sw"
	info_class_name="4f"

elif [[ ${input_class_name} == "2f_z" ]] ; then
	class_name="2f_Z"
	short_class_name="2f_z"
	info_class_name="2f"

elif [[ ${input_class_name} == "6f_eeww" ]] ; then
	class_name="6f_eeWW"
	short_class_name=""

elif [[ ${input_class_name} == "6f_llww" ]] ; then
	class_name="6f_llWW"
	short_class_name=""

elif [[ ${input_class_name} == "6f_ttbar" ]] ; then
	class_name="6f_ttbar"
	short_class_name=""

elif [[ ${input_class_name} == "6f_vvww" ]] ; then
	class_name="6f_vvWW"
	short_class_name=""

elif [[ ${input_class_name} == "6f_xxww" ]] ; then
	class_name="6f_xxWW"
	short_class_name=""

elif [[ ${input_class_name} == "6f_xxxxz" ]] ; then
	class_name="6f_xxxxZ"
	short_class_name=""

elif [[ ${input_class_name} == "6f_yyyyz" ]] ; then
	class_name="6f_yyyyZ"
	short_class_name=""
	info_class_name="6f_yyyyZ"

elif [[ ${input_class_name} == "higgs" ]] ; then
	class_name="higgs"
	short_class_name=""
	info_class_name="higgs"

elif [[ ${input_class_name} == "nh" || ${input_class_name} == "np-light-higgs" ]] ; then
	class_name="np-light-higgs"
	short_class_name=""
	info_class_name="np-light-higgs"
	final_states="e2"
	short_final_states="np-lmh_mh${input_final_states}_e2e2h"

elif [[ ${input_class_name} == "aa_2f" ]] ; then
	class_name="aa"
	short_class_name="aa"
	if [[ ${input_final_states} == "ee" ]] ; then
		final_states="2f"
		short_final_states="_ee"
		info_class_name="aa_2f"
	elif [[ ${input_final_states} == "ll" ]] ; then
		final_states="2f"
		short_final_states="_ll"
		info_class_name="aa_2f"
	elif [[ ${input_final_states} == "xx" ]] ; then
		final_states="2f"
		short_final_states="_xx"
		info_class_name="aa_2f"
	elif [[ ${input_final_states} == "yy" ]] ; then
		final_states="2f"
		short_final_states="_yy"
		info_class_name="aa_2f"
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
	elif [[ ${input_final_states} == "min1020m1" ]] ; then
		final_states="minijet"
		short_final_states="min_10_20_m1"
		info_class_name="aa_minijet"
	elif [[ ${input_final_states} == "min2040m1" ]] ; then
		final_states="minijet"
		short_final_states="min_20_40_m1"
		info_class_name="aa_minijet"
	elif [[ ${input_final_states} == "min40xxm1" ]] ; then
		final_states="minijet"
		short_final_states="min_40_xx_m1"
	elif [[ ${input_final_states} == "min0410m4" ]] ; then
		final_states="minijet"
		short_final_states="min_04_10_m4"
	elif [[ ${input_final_states} == "min1020m4" ]] ; then
		final_states="minijet"
		short_final_states="min_10_20_m4"
	elif [[ ${input_final_states} == "min2040m4" ]] ; then
		final_states="minijet"
		short_final_states="min_20_40_m4"
	elif [[ ${input_final_states} == "min40xxm4" ]] ; then
		final_states="minijet"
		short_final_states="min_40_xx_m4"
	elif [[ ${input_final_states} == "hadronic" || ${input_final_states} == "h" ]] ; then
		final_states="hadronic"
		short_final_states="aa"
	else
		echo "no such aa final state"
		exit
	fi
else
	echo "no such class name"

fi



data_source=/pnfs/desy.de/ilc/prod/ilc/mc-opt-3/ild/dst-merged
if [[ ${class_name} == "higgs" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}_"ffh"/${ILD_version}/${reconstruction_version}
elif [[ ${class_name:0:3} == "6f_" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
elif [[ ${class_name} == "np-light-higgs" ]] ; then
	data_folder=${data_source}/${energy_version}/${class_name}/${ILD_version}/${reconstruction_version}
else
	data_folder=${data_source}/${energy_version}/${class_name}_${final_states}/${ILD_version}/${reconstruction_version}
fi





short_name=${short_class_name}${short_final_states}
file_name_aux1=.n001.d_dstm_${file_postid}

#file_name_basic=r${reconstruction_version}.s${simulation_version}.m${ILD_version}.E${energy_version}.I${file_id}.P${short_name}.${polarization}${file_name_aux1}
file_name_basic=r${reconstruction_version}.s${simulation_version}.m${ILD_version}.E${energy_version}.*.P${short_name}.${polarization}*
file_name_ext=.slcio



if [ ! -d ${data_folder} ] ; then
	echo "no such folder, please check! you input folder is " ${data_folder}
	exit
fi



echo "in folder:" ${data_folder} " \n like following file " ${file_name_basic}
echo "channel is:  ${class_name} ${final_states} ${pol_in} is--------"

for j in ${data_folder}/${file_name_basic}  
do
	if [[ ${j##*.} == "slcio" ]]; then
		echo "file_name:    "${j}
	fi
done
