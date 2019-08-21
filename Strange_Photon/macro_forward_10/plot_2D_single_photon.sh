#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}

 mass_profile="\"../results/single_photon_10_forward.root\"" 


#title_name="{\"pfo_check_particle_costheta_vec\",
#             \"pfo_check_particle_e_vec\"
#	    }";
#axis_name="{\"cos_{#theta}\",
#             \"E_{PFO}\"
#	    }";
#region="{ 200,-1,1,150,0,15}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"


#title_name="{\"pfo_check_particle_costheta_vec\",
#             \"pfo_check_particle_hcal_vec\",
#             \"pfo_check_particle_e_vec\"
#	    }";
#axis_name="{\"cos_{#theta}\",
#             \"E_{hcal}/E_{PFO}\"
#	    }";
#region="{ 200,-1,1,150,0,1.5}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec_ratio.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"

#title_name="{\"pfo_check_particle_costheta_vec\",
#             \"pfo_check_particle_ecal_vec\",
#             \"pfo_check_particle_e_vec\"
#	    }";
#axis_name="{\"cos_{#theta}\",
#             \"E_{ecal}/E_{PFO}\"
#	    }";
#region="{ 200,-1,1,150,0,1.5}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec_ratio.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"

#title_name="{\"pfo_check_particle_costheta_vec\",
#             \"pfo_check_particle_lumical_vec\",
#             \"pfo_check_particle_e_vec\"
#	    }";
#axis_name="{\"cos_{#theta}\",
#             \"E_{lumi}/E_{PFO}\"
#	    }";
#region="{ 200,-1,1,150,0,1.5}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec_ratio.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"


## for x-y plane
#title_name="{\"pfo_check_particle_e_vec\",
#             \"pfo_check_particle_lumical_vec\"
#	    }";
#axis_name="{\"E_{PFO}\",
#             \"E_{lumi}\"
#	    }";
#region="{ 150,0,15,150,0,15}" ;
#logtype="{ \"no\", \"no\" }";
#eventnum=10000;
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"

## for x-y plane
#title_name="{\"pfo_check_particle_e_vec\",
#             \"pfo_check_particle_ecal_vec\"
#	    }";
#axis_name="{\"E_{PFO}\",
#             \"E_{ecal}\"
#	    }";
#region="{ 150,0,15,150,0,15}" ;
#logtype="{ \"no\", \"no\" }";
#eventnum=10000;
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"


## for x-y plane
#title_name="{\"pfo_check_particle_e_vec\",
#             \"pfo_check_particle_hcal_vec\"
#	    }";
#axis_name="{\"E_{PFO}\",
#             \"E_{hcal}\"
#	    }";
#region="{ 150,0,15,150,0,15}" ;
#logtype="{ \"no\", \"no\" }";
#eventnum=10000;
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${axis_name},${region}, ${logtype}, ${eventnum})"


## energy ratio 





## energy difference



 #directly x-y
 cut_style="\"all_region\"";
 cut="{-1,0,15,-1,0.996,1}" 
 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_ecal_vec\"
 	    }";
 cut_name="{\"pfo_check_particle_lumical_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{ecal}\"
    	}";
 region="{ 300,-15,15,150,0,15}" ;
 logtype="{ \"no\", \"no\" }";
 eventnum=100000;
 root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} , ${region}, ${logtype}, ${eventnum}, ${cut_style})"



 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_hcal_vec\"
 	    }";
 #\"pfo_check_particle_hcal_vec\",
 cut_name="{\"pfo_check_particle_lumical_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{hcal}\"
    	}";
 region="{ 300,-15,15,150,0,15}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000
 root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} ,${region}, ${logtype}, ${eventnum}, ${cut_style})"


 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_lumical_vec\"
 	    }";
 #\"pfo_check_particle_hcal_vec\",
 cut_name="{\"pfo_check_particle_ecal_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{lumical}\"
    	}";
 region="{ 300,-15,15,150,0,15}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000
 root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} ,${region}, ${logtype}, ${eventnum}, ${cut_style})"


 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_e_vec\"
 	    }";
 #\"pfo_check_particle_hcal_vec\",
 cut_name="{\"pfo_check_particle_ecal_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{PFO}\"
    	}";
 region="{ 300,-15,15,150,0,15}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000
 root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} ,${region}, ${logtype}, ${eventnum}, ${cut_style})"


 # for v2/v3--v1 plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_ecal_vec\",
              \"pfo_check_particle_e_vec\"
 	    }";
 #\"pfo_check_particle_hcal_vec\",
 cut_name="{\"pfo_check_particle_lumical_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{ecal}/E_{e}\"
    	}";
 region="{ 300,-15,15,200,0,2}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000
 root -l -b -q plot_2D_vec_cut_ecal_over_hcal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} ,${region}, ${logtype}, ${eventnum}, ${cut_style})"


 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_hcal_vec\",
              \"pfo_check_particle_e_vec\"
 	    }";
 #\"pfo_check_particle_hcal_vec\",
 cut_name="{\"pfo_check_particle_lumical_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{hcal}/E_{e}\"
    	}";
 region="{ 300,-15,15,200,0,2}" 
 logtype="{ \"no\", \"no\" }";
 eventnum=100000;
 root -l -b -q plot_2D_vec_cut_ecal_over_hcal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} ,${region}, ${logtype}, ${eventnum}, ${cut_style})"


 # for x-y plane
 title_name="{\"mcs_check_py_obv_energy_difference\",
              \"pfo_check_particle_lumical_vec\",
              \"pfo_check_particle_e_vec\"
 	    }";
 cut_name="{\"pfo_check_particle_ecal_vec\",
    		\"pfo_check_particle_e_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{PFO}-E_{MC}\",
             \"E_{lumical}/E_{PFO}\"
    	}";
 region="{ 300,-15,15,200,0,2}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000
 root -l -b -q plot_2D_vec_cut_ecal_over_hcal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${cut} ,${region}, ${logtype}, ${eventnum}, ${cut_style})"

