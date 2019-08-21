#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/


 #mass_profile="\"../results/higgs_e2_eL.pR\"";
# mass_profile="\"../results/2f_l_eL.pR\"";

#title_name="{\"pfo_check_obv_energy_difference\",
#             \"mcs_check_py_obv_energy_difference\",
#             \"mcs_check_de_obv_energy_difference\" 
#	    }";
#leg_name="{\"E_{PFO}-E_{MCHS}\", 
#           \"E_{PFO}-E_{MCPS}\", 
#           \"E_{PFO}-E_{MCDS}\" 
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\", 
#           \"Events\"  
#	    }";
#region="{ 350,-50,50 }"; 
#axistype="{ \"normal\" }"; 
#root -l -q -b plot_1D_different_observable_in_same_file_with_special_cut.C"(${mass_profile}, ${title_name} ,${leg_name}, ${axis_name},${region}, ${axistype})"


##mass_profile="\"../results/higgs_e2_eL.pR\"";
#mass_profile="\"../results/2f_l_eL.pR\"";

#title_name="{\"mcs_check_py_obv_energy_difference\",
#   		  \"mcs_lostenergy_photon_obv_mc_minus_pfo_energy\" 
#   	}";
#   		  #\"mcs_lostenergy_photon_obv_pfo_minus_mc_energy\" 
#leg_name="{\"E_{PFO}-E_{MCPS}\", 
#   		\"E_{all PFO}-E_{MCPS}\" 
#   	}";
#axis_name="{\"E_{PFO}-E_{MC}\", 
#   		\"Events\"  
#   	}";
#region="{ 350,-50,50 }"; 
#axistype="{ \"normal\" }"; 
#root -l -q -b plot_1D_different_observable_in_same_file_vec_var.C"(${mass_profile}, ${title_name} ,${leg_name}, ${axis_name},${region}, ${axistype})"



##mass_profile="\"../results/higgs_e2_eL.pR\"";
#mass_profile="\"../results/2f_l_eL.pR\"";

#title_name="{\"mcs_check_py_obv_energy_difference\",
#   		  \"mcs_lostenergy_photon_obv_pfo_minus_mc_energy\" 
#   	}";
#leg_name="{\"E_{PFO}-E_{MCPS}\", 
#   		\"E_{all PFO}-E_{MCPS}\" 
#   	}";
#axis_name="{\"E_{PFO}-E_{MC}\", 
#   		\"Events\"  
#   	}";
#region="{ 350,-50,50 }"; 
#axistype="{ \"normal\" }"; 
#root -l -q -b plot_1D_different_observable_in_same_file_vec_var.C"(${mass_profile}, ${title_name} ,${leg_name}, ${axis_name},${region}, ${axistype})"



#mass_profile="\"../results/higgs_e2_eL.pR\"";
# mass_profile="\"../results/2f_l_eL.pR\"";

#title_name="{\"mcs_check_py_obv_energy_difference\",
#   		  \"pfo_check_particle_ecal_vec\",
#   		  \"pfo_check_particle_hcal_vec\",
#   		  \"pfo_check_particle_e_vec\"
#	    }";
#leg_name="{\"E_{PFO}<100\", 
#           \"E_{ecal}/E_{hcal}>1 & E_{PFO}>100\", 
#           \"E_{ecal}/E_{hcal}<1 & E_{PFO}>100\" 
#	    }";
#axis_name="{\"E_{PFO}-E_{MC}\", 
#           \"Events\"  
#	    }";
#region="{ 350,-50,50 }"; 
#axistype="{ \"normal\" }"; 
#root -l -q -b plot_1D_different_observable_in_same_file_with_extra_cut.C"(${mass_profile}, ${title_name} ,${leg_name}, ${axis_name},${region}, ${axistype})"

##mass_profile="\"../results/higgs_e2_eL.pR\"";
#mass_profile="\"../results/2f_l_eL.pR\"";

#title_name="{\"mcs_lostenergy_photon_particle_e_vec\",
#   		  \"mcs_lostenergy_photon_obv_pfo_minus_mc_energy\" 
#   	}";
#leg_name="{\"E_{MCPS}<100 GeV\", 
#   		\"E_{MCPS}>100 GeV\" 
#   	}";
#axis_name="{\"(E_{PFO}-E_{MC})\", 
#   		\"Events\"  
#   	}";
#region="{ 350,-50,50 }"; 
#axistype="{ \"normal\" }"; 
#root -l -q -b plot_1D_mc_photon_difference_seperate.C"(${mass_profile}, ${title_name} ,${leg_name}, ${axis_name},${region}, ${axistype})"

