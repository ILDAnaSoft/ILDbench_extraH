#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/


 mass_profile="\"../results/2f_l_eL.pR.root\"";

 title_name="{\"mcs_check_py_obv_energy_difference\"
 	    }";
 cut_name="{
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 leg_name="{\"cos_{#theta}<0.7\", 
            \"cos_{#theta}>0.7\", 
 	    }";
		axis_name="{\"(E_{PFO}-E_{MC})/E_{PFO}\", 
            \"Events\"  
 	    }";
 region="{ 100,-0.15,0.15 }"; 
 cut_region="{
              {-1,5,15,0,0,0.7},
              {-1,5,15,0,7,1.0} 
}"
 axistype="{ \"normal\" }"; 
 eventnum=100000000
 root -l -q -b plot_1D_cut_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile}, ${title_name},${cut_name}, ${cut_region}, ${leg_name}, ${axis_name},${region}, ${axistype},${eventnum})"



