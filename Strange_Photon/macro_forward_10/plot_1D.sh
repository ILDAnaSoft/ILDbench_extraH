#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/


 #mass_profile="\"../results/higgs_e2_eL.pR\"";
 mass_profile="\"../results/2f_l_eL.pR.root\"";

 title_name="{\"mcs_check_py_obv_energy_difference\"
 	    }";
 cut_name="{\"pfo_check_particle_ecal_vec\",
    		\"pfo_check_particle_hcal_vec\",
    		\"pfo_check_particle_lumical_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 leg_name="{\"E_{PFO}<100 & cos_{#theta}<0.996\", 
            \"E_{PFO}<100 & cos_{#theta}>0.996\", 
            \"E_{PFO}>100 & cos_{#theta}<0.996\", 
            \"E_{PFO}>100 & cos_{#theta}>0.996\" 
 	    }";
		axis_name="{\"(E_{PFO}-E_{MC})/E_{PFO}\", 
            \"Events\"  
 	    }";
 #region="{ 100,-50,50 }"; 
 region="{ 100,-0.15,0.15 }"; 
 axistype="{ \"normal\" }"; 
 eventnum=100000000
 root -l -q -b plot_1D_cut_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile}, ${title_name},${cut_name}, ${leg_name}, ${axis_name},${region}, ${axistype},${eventnum})"


#mass_profile="\"../results/higgs_e2_eL.pR\"";
#mass_profile="\"../results/2f_l_eL.pR.root\"";

#title_name="{\"pfo_check_particle_costheta_vec\"
#	    }";
#cut_name="{
#           \"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_ecal_vec\",
#   		\"pfo_check_particle_hcal_vec\",
#   		\"pfo_check_particle_lumical_vec\"
#	    }";
#leg_name="{\"E_{PFO}\", 
#           \"E_{ecal}/E_{PFO}\", 
#           \"E_{hcal}/E_{PFO}\", 
#           \"E_{lumical}/E_{PFO}\" 
#	    }";
#axis_name="{\"cos_{#theta}\", 
#           \"ratio\"  
#	    }";
#region="{ 100,-1,1 }"; 
#axistype="{ \"normal\" }"; 
#eventnum=10000000
#root -l -q -b plot_1D_vec_constituent_ratio.C"(${mass_profile}, ${title_name},${cut_name}, ${leg_name}, ${axis_name},${region}, ${axistype},${eventnum})"

