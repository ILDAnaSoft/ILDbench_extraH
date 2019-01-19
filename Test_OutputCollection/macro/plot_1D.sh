#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/

  mass_profile="{ \"../results/higgs_e2_eL.pR\"  
 	 			}" 
 title_name="\"mc_electron_p\"";
 region="{ 300,0,0.3 }" 
 axistype="{ \"log\" }" 



#root -l -q -b plot_1D.C "(${mass_profile})"

#root -l -q -b plot_1D_vec.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
root -l -q -b plot_1D.C"(${mass_profile}, ${title_name} , ${region}, ${axistype})"
