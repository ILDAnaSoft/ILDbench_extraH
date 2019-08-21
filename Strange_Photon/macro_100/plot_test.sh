#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}


 mass_profile="\"../results/single_photon_10.root\"" 
 cut_style="\"all\"";



 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_lumical_vec\",
              \"pfo_check_particle_e_vec\"
 	    }";
 cut_name="{\"mcs_check_py_particle_e_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"(E_{PFO}-E_{MC})/E_{MC}\",
             \"E_{lumical}/E_{PFO}\"
    	}";
 # cut[0] ==-1 not use first cut
 # cut[0] ==0  use first cut   cut[1] <     cut_name[1]  < cut[2]
 # cut[0] ==1  use first cut   cut[1] < abs(cut_name[1]) < cut[2]
 # same for cut[3],cut[4],cut[5]
 cut="{-1,0,15,-1,0.996,1}" 
 region="{ 200,-1,1,150,0,1.5}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000
 root -l -b -q plot_2D_vec_cut_ecal_over_hcal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut}, ${region}, ${logtype}, ${eventnum}, ${cut_style})"

