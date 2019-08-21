#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}

##mass_profile="\"../results/higgs_e2_eL.pR.root\""
#mass_profile="\"../results/2f_l_eL.pR.root\"" 

#title_name0="\"pfo_check_particle_costheta_vec\"";
#title_name1="\"pfo_check_particle_hcal_vec\"";
#axis_name0="\"cos_{#theta}\"";
#axis_name1="\"E_{hcal}\"";
#region="{ 100,0.996,1,300,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"



##mass_profile="\"../results/higgs_e2_eL.pR.root\""
#mass_profile="\"../results/2f_l_eL.pR.root\"" 

#title_name0="\"pfo_check_particle_costheta_vec\"";
#title_name1="\"pfo_check_particle_lumical_vec\"";
#axis_name0="\"cos_{#theta}\"";
#axis_name1="\"E_{lumi}\"";
#region="{ 100,0.996,1,300,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"

##mass_profile="\"../results/higgs_e2_eL.pR.root\""
#mass_profile="\"../results/2f_l_eL.pR.root\"" 

#title_name0="\"pfo_check_particle_costheta_vec\"";
#title_name1="\"pfo_check_particle_e_vec\"";
#axis_name1="\"cos_{#theta}\"";
#axis_name0="\"E_{PFO}\"";
#region="{ 200,-1,1,300,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=10000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"

 cut_style="\"ll\"";
 #mass_profile="\"../results/higgs_e2_eL.pR.root\""
  mass_profile="\"../results/2f_l_eL.pR.root\""
 # for x-y plane
 title_name="{\"pfo_check_particle_lumical_vec\",
              \"pfo_check_particle_e_vec\"
 	    }";
 #\"pfo_check_particle_hcal_vec\",
 cut_name="{\"pfo_check_particle_hcal_vec\",
    		\"pfo_check_particle_ecal_vec\",
    		\"pfo_check_particle_costheta_vec\"
 	    }";
 axis_name="{\"E_{lumical}\",
             \"E_{PFO}\"
    	}";
 region="{ 300,0,300,300,0,300}" ;
 logtype="{ \"no\", \"no\" }";
 eventnum=10000;
 root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"


##mass_profile="\"../results/higgs_e2_eL.pR.root\""
# mass_profile="\"../results/2f_l_eL.pR.root\""
## for x-y plane
#title_name="{\"mcs_check_py_obv_energy_difference\",
#             \"pfo_check_particle_ecal_vec\"
#	    }";
#cut_name="{\"pfo_check_particle_lumical_vec\",
#   		\"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_costheta_vec\"
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\",
#            \"E_{ecal}\"
#   	}";
#region="{ 60,-80,80,300,0,2}" ;
#logtype="{ \"no\", \"no\" }";
#eventnum=100000;
#root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"



##mass_profile="\"../results/higgs_e2_eL.pR.root\""
# mass_profile="\"../results/2f_l_eL.pR.root\""
## for x-y plane
#title_name="{\"mcs_check_py_obv_energy_difference\",
#             \"pfo_check_particle_hcal_vec\"
#	    }";
##\"pfo_check_particle_hcal_vec\",
#cut_name="{\"pfo_check_particle_lumical_vec\",
#   		\"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_costheta_vec\"
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\",
#            \"E_{hcal}\"
#   	}";
#region="{ 60,-80,80,100,0,20}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000
#root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"


##mass_profile="\"../results/higgs_e2_eL.pR.root\""
# mass_profile="\"../results/2f_l_eL.pR.root\""
## for x-y plane
#title_name="{\"mcs_check_py_obv_energy_difference\",
#             \"pfo_check_particle_ecal_vec\",
#             \"pfo_check_particle_hcal_vec\"
#	    }";
##\"pfo_check_particle_hcal_vec\",
#cut_name="{\"pfo_check_particle_lumical_vec\",
#   		\"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_costheta_vec\"
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\",
#            \"E_{ecal}/E_{hcal}\"
#   	}";
#region="{ 60,-80,80,100,0,10}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000
#root -l -b -q plot_2D_vec_cut_ecal_over_hcal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"

##mass_profile="\"../results/higgs_e2_eL.pR.root\""
# mass_profile="\"../results/2f_l_eL.pR.root\""
## for x-y plane
#title_name="{\"mcs_check_py_obv_energy_difference\",
#             \"pfo_check_particle_lumical_vec\"
#	    }";
##\"pfo_check_particle_hcal_vec\",
#cut_name="{\"pfo_check_particle_ecal_vec\",
#   		\"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_costheta_vec\"
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\",
#            \"E_{lumical}\"
#   	}";
#region="{ 60,-80,80,100,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000
#root -l -b -q plot_2D_vec_cut_ecal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"

##mass_profile="\"../results/higgs_e2_eL.pR.root\""
# mass_profile="\"../results/2f_l_eL.pR.root\"";
## for x-y plane
#title_name="{\"pfo_check_particle_costheta_vec\",
#             \"pfo_check_particle_hcal_vec\",
#             \"pfo_check_particle_ecal_vec\"
#	    }";
##\"pfo_check_particle_hcal_vec\",
#cut_name="{\"pfo_check_particle_lumical_vec\",
#   		\"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_phi_vec\"
#	    }";
#axis_name="{\"cos#theta\",
#            \"E_{hcal}/E_{ecal}\"
#   	}";
#region="{ 200,-0.996,0.996,100,0,0.1}"; 
#logtype="{ \"no\", \"no\" }";
#eventnum=100000;
#cut_style="\"x\"";
#root -l -b -q plot_2D_vec_cut_ecal_over_hcal_and_pfo_mc_energy_diff_with_E_cos.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"


##mass_profile="\"../results/higgs_e2_eL.pR.root\""
# mass_profile="\"../results/2f_l_eL.pR.root\""
## for x-y plane
#title_name="{\"pfo_check_particle_lumical_vec\",
#             \"pfo_check_particle_ecal_vec\",
#             \"pfo_check_particle_hcal_vec\"
#	    }";
#cut_name="{\"pfo_check_particle_e_vec\",
#   		\"pfo_check_particle_costheta_vec\"
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\",
#            \"E_{ecal}/E_{hcal}\"
#   	}";
#region="{ 60,-80,80,100,0,100}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000
#root -l -b -q plot_2D_vec_constituent_ratio.C"(${mass_profile},${title_name},${cut_name}, ${axis_name},${region}, ${logtype}, ${eventnum}, ${cut_style})"

