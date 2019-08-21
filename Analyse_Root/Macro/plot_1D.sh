#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

 mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_l5_2019_01/results_10/nh_10_eL.pR\"
 	 			}"; 
 title_name=\"po_obv_sigma_inm\"
 leg_name="{\"Large\",
            \"Small\",
 	    }";
 region="{ 50,0,10.0 }" 
 axistype="{ \"nor\" }" 
 root -l -q -b plot_1D.C"(${mass_profile}, ${title_name}, ${region}, ${axistype})"

#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws/results_40/nh_40_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5/results_40/nh_40_eL.pR\",
#	 			}"; 
#title_name="{\"po_wo_overlay_kcut_zmass\",
#             \"po_wo_overlay_kcut_zmass\",
#	    }";
#leg_name="{\"Large\",
#           \"Small\",
#	    }";
#region="{ 50,70,120.0 }" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"


#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws/results_40/nh_40_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5/results_40/nh_40_eL.pR\",
#	 			}"; 
#title_name="{\"po_wo_overlay_kcut_zpt\",
#             \"po_wo_overlay_kcut_zpt\",
#	    }";
#leg_name="{\"Large\",
#           \"Small\",
#	    }";
#region="{ 130,0,260}" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws/results_40/nh_40_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5/results_40/nh_40_eL.pR\",
#	 			}"; 
#title_name="{\"po_wo_overlay_kcut_invis_e\",
#             \"po_wo_overlay_kcut_invis_e\",
#	    }";
#leg_name="{\"Large\",
#           \"Small\",
#	    }";
#region="{ 250,-50,200}" 
#axistype="{ \"nor\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws/results_40/nh_40_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5/results_40/nh_40_eL.pR\",
#	 			}"; 
#title_name="{\"po_wo_overlay_lep_pair_costheta_pair\",
#             \"po_wo_overlay_lep_pair_costheta_pair\",
#	    }";
#leg_name="{\"Large\",
#           \"Small\",
#	    }";
#region="{ 200,-1,1}" 
#axistype="{ \"log\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws/results_40/nh_40_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5/results_40/nh_40_eL.pR\",
#	 			}"; 
#title_name="{\"po_wo_overlay_lep_pair_costheta\",
#             \"po_wo_overlay_lep_pair_costheta\",
#	    }";
#leg_name="{\"Large\",
#           \"Small\",
#	    }";
#region="{ 200,-1,1}" 
#axistype="{ \"log\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/nh_30_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/nh_30_eL.pR\" 
#	 			}"; 
#title_name="{\"po_isr_vari_photon_central_e\",
#             \"po_isr_vari_photon_central_e\" 
#	    }";
#leg_name="{\"PFO\",
#           \"cheat ISR\" 
#	    }";
#region="{ 200,0,400}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\" 
#	 			}"; 
#title_name="{\"po_obvkcut_zmass\",
#             \"po_isr_obvkcut_zmass\" 
#	    }";
#leg_name="{\"PFO\",
#           \"cheat isr\" 
#	    }";
#region="{ 400,60,140}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_240/nh_240_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_240/nh_240_eL.pR\" 
#	 			}"; 
#title_name="{\"po_obvkcut_zmass\",
#             \"po_cmuon_obvkcut_zmass\" 
#	    }";
#leg_name="{\"PFO\",
#           \"cheat muon\" 
#	    }";
#region="{ 400,60,140}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"



#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/nh_30_eL.pR\"
#	 			}"; 
#title_name=\"po_isr_obv_kcut_zmass\"
#region="{ 400,60,120}" 
#axistype="{ \"normal\" }" 
#root -l fit_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"


#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\" 
#	 			}"; 
#title_name="{\"po_obv_photon_lepton_pair_azimuth_pair\",
#             \"py_obv_photon_lepton_pair_azimuth_pair\", 
#             \"po_cmuon_obv_photon_lepton_pair_azimuth_pair\" 
#	    }";
#leg_name="{\"PFO\",
#           \"PY\", 
#           \"cheat muon\" 
#	    }";
#region="{ 320,0,3.2}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"

#mass_profile="{ \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR\" 
#	 			}"; 
#title_name="{\"po_obv_lep_pair_costheta\",
#             \"py_obv_lep_pair_costheta\", 
#             \"po_cmuon_obv_lep_pair_costheta\" 
#	    }";
#leg_name="{\"PFO\",
#           \"PY\", 
#           \"cheat muon\" 
#	    }";
#region="{ 200,-1,1}" 
#axistype="{ \"normal\" }" 
#root -l -q -b plot_1D_different_observable.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
