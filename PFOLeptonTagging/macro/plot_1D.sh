#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

  mass_profile="{ \"../results/2f_l_eL.pR_test.root\",
                  \"../results/2f_l_eL.pR_test_s5.root\"  
 	 			}" 
  title_name="\"pfo_output_lepton_obv_inm\" "
  axis_name="{
    \"M_{#mu^{+}#mu^{-}} (GeV)\",
    \"Events/0.1GeV\"
  	 			}" 
  region="{ 250,80,105}" 

#title_name="\"pfo_input_lepton_obv_sigma_inm\" ";
#region="{ 500,0,5}" 
 cut_name="{ \"pfo_input_lepton_particle_costheta_vec\",
 	 			}" 
 cut_value="{0, 0.7}" 
 axistype="{ \"no\" }" 
#axis_name="{
#\"#sigma(M_{#mu^{+}#mu^{-}}) (GeV)\",
#   \"Events/0.01GeV\"
#	 			}" 
 leg_name="{ \"ILD-L\",
             \"ILD-S\"  
 	 			}" 



#root -l -q -b plot_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
root -l -q -b plot_1D_with_vector_cut.C"(${mass_profile}, ${title_name} ,${cut_name},${cut_value}, ${region}, ${axistype}, ${axis_name}, ${leg_name})"
#root -l -q -b plot_1D_vec.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"

