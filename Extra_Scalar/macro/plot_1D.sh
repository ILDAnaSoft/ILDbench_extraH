#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

 mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
 mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"

 title_name="{\"po_vari_photon_central_e\",
              \"po_isr_vari_photon_central_e\" 
 	    }";
 leg_name="{\"large\",
            \"small\" 
 	    }";
		axis_name="{\"(E^{#gamma}_{PFO}-E^{#gamma}_{MC})/E_{PFO}^{#gamma}\",
            \"Events\"}";
 region="{ 200,-1,1}" 
 leg_pos="{0.2,0.65,0.4,0.95}" 
 axistype="{ \"log\" }" 
 root -l -q -b plot_1D_different_observable_in_same_multi_file.C"(${mass_profile1},${mass_profile2},${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"



#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"

#title_name="{\"po_vari_photon_central_e\",
#             \"py_vari_photon_forward_e\" 
#	    }";
#leg_name="{\"laorge\",
#           \"small\" 
#	    }";
#axis_name="{\"E_{#gamma}\",
#           \"Events\"}";
#region="{ 300,0,300}" 
#leg_pos="{0.4,0.65,0.6,0.95}" 
#axistype="{ \"log\" }" 
#root -l -q -b plot_1D_multi_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"

#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"

#title_name="{\"po_vari_photon_central_e\",
#             \"po_vari_photon_forward_e\" 
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#axis_name="{\"E_{#gamma}\",
#           \"Events\"}";
#region="{ 300,0,300}" 
#leg_pos="{0.4,0.65,0.6,0.95}" 
#axistype="{ \"log\" }" 
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"


#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_vari_photon_central_costheta\",
#             \"po_vari_photon_forward_costheta\" 
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{ 200,-1,1}" 
#leg_pos="{0.4,0.6,0.6,0.9}" 
#axistype="{ \"log\" }" 
#axis_name="{\"cos#theta_{#gamma}\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"


#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";
#title_name="{\"po_vari_muon_plus_e\",
#             \"po_vari_muon_minus_e\" 
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{ 300,0,300}" 
#leg_pos="{0.2,0.3,0.4,0.6}" 
#axistype="{ \"log\" }" 
#axis_name="{\"E_{#mu}\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"

#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_vari_muon_plus_costheta\",
#             \"po_vari_muon_minus_costheta\" 
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{ 200,-1,1}" 
#leg_pos="{0.4,0.6,0.6,0.9}" 
#axistype="{ \"log\" }" 
#axis_name="{\"cos#theta_{#mu}\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"

#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_obv_kcut_zmass\"
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{ 80,50,130}" 
#leg_pos="{0.2,0.3,0.4,0.6}" 
#axistype="{ \"normal\" }" 
#axis_name="{\"E_{#mu^{+}#mu^{-}}\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"

#mass_profile1="{\"${HOME}/dust/Event_Analyse_1901_l5_po_with_overlay/results-11/20_MVA/nh_20_20_20.root\"}"
#mass_profile2="{\"${HOME}/dust/Event_Analyse_1901_s5_po_with_overlay/results-11/20_MVA/nh_20_20_20.root\"}"

#title_name="{\"MVA\"
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{ 200,-1,1}" 
#leg_pos="{0.2,0.3,0.4,0.6}" 
#axistype="{ \"normal\" }" 
#axis_name="{\"MVA2\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files.C"(${mass_profile1}, ${mass_profile2}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"



#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_obv_kcut_zpt\"
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{ 100,0,300}" 
#leg_pos="{0.2,0.3,0.4,0.6}" 
#axistype="{ \"log\" }" 
#axis_name="{\"PT_{#mu^{+}#mu^{-}}\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"


#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_obv_lep_pair_costheta_pair\"
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{200,-1,1}" 
#leg_pos="{0.5,0.25,0.7,0.55}" 
#axistype="{ \"log\" }" 
#axis_name="{\"cos#theta_{#mu^{+}#mu^{-}}\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"


#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_obv_lep_pair_azimuth_pair\"
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{315,0,3.15}" 
#leg_pos="{0.6,0.6,0.8,0.9}" 
#axistype="{ \"log\" }" 
#axis_name="{\"acoplanar\",
#           \"Events\"}";
#root -l -q -b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"


#mass_profile1="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_20/nh_20_eL.pR.root\"}"
#mass_profile2="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_20/nh_20_eL.pR.root\"}"""
#mass_profile3="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/higgs_e2_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_2019_01_with_overlay/results_30/4f_sznn_l_eL.pR.root\"}";
#mass_profile4="{\"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/2f_z_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/higgs_e2_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_zz_sl_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_szee_l_eL.pR.root\",
#                \"${HOME}/dust/light_higgs_10_410_e500_lcws_s5_2019_01/results_30/4f_sznn_l_eL.pR.root\"}";

#title_name="{\"po_obv_kcut_recoil_mass\"
#	    }";
#leg_name="{\"large\",
#           \"small\" 
#	    }";
#region="{250,0,500}" 
#leg_pos="{0.6,0.6,0.8,0.9}" 
#axistype="{ \"normal\" }" 
#axis_name="{\"M_{recoil}\",
#           \"Events\"}";
#root -l -q- b plot_1D_two_observable_multi_files_seperate_sig_bkg.C"(${mass_profile1}, ${mass_profile2}, ${mass_profile3}, ${mass_profile4}, ${title_name} ,${leg_name}, ${axis_name}, ${region}, ${leg_pos}, ${axistype})"

