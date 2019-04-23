#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}

  mass_profile="{ \"../results/nh_eL.pR\"  
 	 			}" 

 # for x-y plane
 title_name="\"pfo_in_non_iso_cone_particle_costheta_vec\"";
 title_name1="\"pfo_in_non_iso_cone_particle_phi_vec\"";
 # for condition judge ment
 title_name2="\"pfo_in_non_iso_cone_particle_pdg_vec\"";
 # for weight
 title_name3="\"pfo_in_non_iso_cone_particle_e_vec\"";
 axis_name="\"cos#theta\"";
 axis_name1="\"#phi\"";
 region="{ 200,-1,1,200,-3.15,3.15}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100
 root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${title_name2}, ${title_name3}, ${axis_name},${axis_name1},${region}, ${logtype}, ${eventnum})"
