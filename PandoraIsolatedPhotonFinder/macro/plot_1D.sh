#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

#mass_profile="{ \"../results/higgs_e2_lr_application\",
#                \"../results/higgs_e2_lr_application\",
#	 			}"; 
#mass_profile="{ \"../results/2f_l_lr_application\",
#                \"../results/2f_l_lr_application\",
#	 			}"; 
#mass_profile="{ \"../results/4f_zz_l_lr_application\",
#                \"../results/4f_zz_l_lr_application\",
#	 			}"; 
 mass_profile="{ \"../results/single_photon_10_application\",
                 \"../results/single_photon_10_application\" 
 	 			}"; 
 title_name="{\"isophoton_obv_small_mva_output\",
              \"isophoton_obv_small_mva_output\"
 	    }";
 leg_name="{\"isr\",
            \"non isr\" 
 	    }";
 tree_name="{\"datatrain_sig\",
             \"datatrain_bkg\" 
 	    }";
 #region="{ 100,-1,1}" 
 region="{ 100,-1,1}" 
 axistype="{ \"normal\" }" 

 #root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
 root -l -q -b plot_1D_different_observable_vec.C"(${mass_profile}, ${title_name} ,${leg_name}, ${tree_name}, ${region}, ${axistype})"




#mass_profile="{ \"../results/higgs_e2_lr_test\",
#                \"../results/h_e2_lr_HS\"
#	 			}"; 
#title_name="{\"isophoton_particle_e_vec\",
#             \"isophoton_particle_e_vec\"
#	    }";
#leg_name="{\"new PFO energy\",
#           \"MC energy\"
#	    }";
#tree_name="{\"datatrain_sig\",
#           \"datatrain\"
#	    }";
##region="{ 100,-1,1}" 
#region="{ 30,0,300}" 
#axistype="{ \"normal\" }" 

#root -l -q -b plot_1D_different_observable_vec.C"(${mass_profile}, ${title_name} ,${leg_name},${tree_name}, ${region}, ${axistype})"




 #mass_profile="{ \"../results/higgs_e2_lr_test\"
#mass_profile="{ \"../results/2f_l_lr\",
#                \"../results/2f_z_l_lr_PS\",
#                \"../../../git_check/ILDbench_extraH/PandoraIsolatedPhotonFinder/results/output_PFO\"
#	 			}"; 
#title_name="{\"isophoton_particle_e_vec\",
#             \"isophoton_particle_e_vec\",
#             \"isophoton_particle_e_vec\"
#	    }";
#leg_name="{\"new PFO energy\",
#           \"MC energy\",
#           \"old PFO energy\"
#	    }";
#tree_name="{\"datatrain_sig\",
#           \"datatrain\",
#           \"datatrain\"
#	    }";
##region="{ 100,-1,1}" 
#region="{ 30,0,300}" 
#axistype="{ \"normal\" }" 

#root -l -q -b plot_1D_different_observable_vec.C"(${mass_profile}, ${title_name} ,${leg_name},${tree_name}, ${region}, ${axistype})"


#mass_profile="{\"../results/2f_l_lr_application.root\",
#                \"../results/4f_zz_l_lr_application.root\"}"
#                \"../results/4f_zz_sl_lr_application.root\"}";
#mass_profile="{\"../results/higgs_e2_lr_application.root\",
#               \"../results/4f_zz_l_lr_application.root\",
#               \"../results/2f_l_lr_application.root\",
#               \"../results/4f_zz_sl_lr_application.root\"}";

#title_name="{\"isophoton_obv_small_mva_output\"
#	    }";
#leg_name="{\"isr\",
#           \"non isr\" 
#	    }";
#tree_name="{\"datatrain_sig\",
#            \"datatrain_bkg\" 
#	    }";
#region="{ 100,-1,1}" 
#axistype="{ \"log\" }" 

#root -l plot_1D_different_observable_vec_different_tree.C"(${mass_profile}, ${title_name} ,${leg_name}, ${tree_name}, ${region}, ${axistype})"


