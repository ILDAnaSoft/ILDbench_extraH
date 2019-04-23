#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/


#mass_profile="\"../results/2f_l_eL.pR\"";

#title_name="{\"pfo_lepton_obv_vtx\",
#             \"pfo_lepton_HS_pdg_vec\" 
#	    }";
#leg_name="{\"vtx\" 
#	    }";
#region="{ 2000,-0.0001,0.0001}" 
#region="{ 2000,-0.5,0.5}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable_in_same_file.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



 mass_profile="\"../results/2f_l_eL.pR\"";

 title_name="{\"pfo_lepton_obv_vtz\",
              \"pfo_lepton_HS_pdg_vec\",
              \"pfo_lepton_num_pfonum\" 
 	    }";
 leg_name="{\"vtz\" 
 	    }";
 region="{ 200,-2,2}" 
 #region="{ 2000,-0.01,0.01}" 
 axistype="{ \"normal\" }" 
 root -l -q -b plot_1D_different_observable_in_same_file_with_special_cut.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



#mass_profile="\"../results/4f_zz_sl_eL.pR\"";

#title_name="{\"pfo_lepton_obv_chi2\",
#             \"pfo_lepton_HS_pdg_vec\",
#             \"pfo_lepton_num_pfonum\" 
#	    }";
#leg_name="{\"vtx\" 
#	    }";
#region="{ 2000,0,100}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable_in_same_file_with_special_cut.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
