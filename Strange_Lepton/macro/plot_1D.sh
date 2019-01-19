#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

  mass_profile="{ \"../results/sm_2f_l_eL.pR\"  
 	 			}" 
 title_name="\"mc_variable_vec_endpointz\"";
 region="{ 200,-3000,3000 }" 
 axistype="{ \"no\" }" 



#root -l -q -b plot_1D.C "(${mass_profile})"

#root -l -q -b plot_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
 root -l -q -b plot_1D_vec.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"


#mass_profile="{ \"../results/sm_2f_l_eL.pR\"  
#	 			}" 
#mass_profile1="{ \"../results/sm_2f_l_eL.pR_test\"  
#	 			}" 
#title_name="\"mc_variable_vec_endpointz\"";
#region="{ 200,-3000,3000 }" 
#axistype="{ \"no\" }" 

#root -l -q -b plot_1D_vec_ratio.C"(${mass_profile},${mass_profile1}, ${title_name} , ${region}, ${axistype})"
