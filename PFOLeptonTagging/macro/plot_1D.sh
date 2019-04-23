#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

  mass_profile="{ \"../results/2f_l_eL.pR_test.root\"  
 	 			}" 
 title_name="\"pfo_output_lepton_obv_inm\" ";
 region="{ 400,70,110}" 
 axistype="{ \"no\" }" 



root -l -q -b plot_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
#root -l -q -b plot_1D_vec.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"

