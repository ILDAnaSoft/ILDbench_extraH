#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

# mass_profile="{ \"../results/jet_8_r_08\",
#                 \"../results/jet_10_r_08\", 
#                 \"../results/jet_8_r_08\", 
#                 \"../results/jet_6_r_08\", 
#                 \"../results/jet_4_r_08\"  
#	 			}" 
#title_name="{\"po_observable_wo_overlay_visible_energy\",
#             \"jet_observable_wo_overlay_visible_energy\",
#             \"jet_observable_wo_overlay_visible_energy\",
#             \"jet_observable_wo_overlay_visible_energy\",
#             \"jet_observable_wo_overlay_visible_energy\"
#	    }";
#leg_name="{\"PFO with MCTruth information\",
#             \"Njet = 10, R=0.8\",
#             \"Njet = 8, R=0.8\",
#             \"Njet = 6, R=0.8\",
#             \"Njet = 4, R=0.8\"
#	    }";
#region="{ 100,0,600.0 }" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} , ${leg_name}, ${region}, ${axistype})"
  mass_profile="{ \"../results/jet_6_r_08\",
                  \"../results/jet_6_r_13\", 
                  \"../results/jet_6_r_10\", 
                  \"../results/jet_6_r_08\", 
                  \"../results/jet_6_r_06\"  
 	 			}" 
 title_name="{\"po_observable_wo_overlay_visible_energy\",
              \"jet_observable_wo_overlay_visible_energy\",
              \"jet_observable_wo_overlay_visible_energy\",
              \"jet_observable_wo_overlay_visible_energy\",
              \"jet_observable_wo_overlay_visible_energy\"
 	    }";
 leg_name="{\"PFO with MCTruth information\",
              \"Njet = 6, R=1.3\",
              \"Njet = 6, R=1.0\",
              \"Njet = 6, R=0.8\".
              \"Njet = 6, R=0.6\"
 	    }";
 region="{ 100,0,600.0 }" 
 axistype="{ \"nor\" }" 
 root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} , ${leg_name}, ${region}, ${axistype})"

# mass_profile="{ \"../results/jet_8_r_08\",
#                 \"../results/jet_8_r_08\", 
#                 \"../results/jet_8_r_08\", 
#	 			}"; 
#title_name="{\"mc_observable_wo_overlay_visible_energy\",
#             \"mc_observable_py_visible_energy\",
#             \"po_observable_wo_overlay_visible_energy\",
#	    }";
#leg_name="{\"MC \",
#             \"mc_observable_py_visible_energy\",
#             \"po_observable_wo_overlay_visible_energy\",
#	    }";
#region="{ 100,0,600.0 }" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} , ${leg_name}, ${region}, ${axistype})"


#mass_profile="{ \"../results/jet_8_r_08\",
#                 \"../results/jet_8_r_08\", 
#	 			}"; 
#title_name="{\"mc_observable_py_visible_energy\",
#             \"po_observable_wo_overlay_visible_energy\",
#	    }";
#leg_name="{\"MC Stable Particle\",
#             \"PFO\",
#	    }";
#region="{ 100,-0.01,600.0 }" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



#root -l -q -b plot_1D.C "(${mass_profile})"

#root -l -q -b plot_1D_vec.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
#root -l -q -b plot_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"


# mass_profile="{ \"../results/jet_8_r_08\",
#                 \"../results/jet_8_r_16\", 
#	 			}"; 
#title_name="{\"mc_overlay_pt_vec\",
#             \"po_overlay_pt_vec\",
#	    }";
#leg_name="{\"MCTruth\",
#             \"PFO\",
#	    }";
#region="{ 100,-0.01,10.0 }" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable_vec.C"(${mass_profile}, ${title_name} , ${leg_name}, ${region}, ${axistype})"



# root -l -q -b plot_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
