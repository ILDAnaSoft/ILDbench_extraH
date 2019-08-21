#!/bin/bash
if [[  $# != 1 ]]  ; then
	echo "usage: ./run_all.sh subjob/no) "
	exit
fi

sub=$1

mass_profile=(10 20 30 40 50 60 70 80 85 90 95 100 105 110 115 120 130 135 140 160 180 200 220 240 260 280 290 300 310 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 408)

mass_length=${#mass_profile[@]}

for (( j=0; j<$(( $mass_length)); j++ )) 
do
	mass=${mass_profile[j]}

	echo "----- submit job for hmass = ${mass} GeV -----"
	if [[ ${sub} == "subjob" ]] ; then
        ${HOME}/Code/HTCondor/run_it_on_condor.sh ./Bin/run_1901_s5_po_with_overlay.sub ${mass}
        sleep 1 
	else
        ./Bin/run_1901_s5_po_with_overlay.sub ${mass}
	fi

done

