#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}

  mass_profile="{ \"../results/higgs_e2_eL.pR\"  
 	 			}" 

 title_name="\"mc_electron_endpointx\"";
 title_name1="\"mc_electron_endpointy\"";
 axis_name="\"x(mm)\"";
 axis_name1="\"y(mm)\"";
 region="{ 200,-300,300,200,-300,300 }" 
 logtype="{ \"log\", \"log\" }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype})"

 title_name="\"mc_electron_endpointx\"";
 title_name1="\"mc_electron_endpointz\"";
 axis_name="\"x(mm)\"";
 axis_name1="\"z(mm)\"";
 region="{ 200,-300,300,200,-1000,1000 }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype} )"

 title_name="\"mc_electron_endpointy\"";
 title_name1="\"mc_electron_endpointz\"";
 axis_name="\"y(mm)\"";
 axis_name1="\"z(mm)\"";
 region="{ 200,-300,300,200,-1000,1000 }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype} )"

 title_name="\"mc_electron_vertexx\"";
 title_name1="\"mc_electron_vertexz\"";
 axis_name="\"x(mm)\"";
 axis_name1="\"z(mm)\"";
 region="{ 200,-2,2,200,-2,2 }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype} )"

 title_name="\"mc_electron_vertexy\"";
 title_name1="\"mc_electron_vertexz\"";
 axis_name="\"y(mm)\"";
 axis_name1="\"z(mm)\"";
 region="{ 200,-2,2,200,-2,2 }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype} )"

 title_name="\"mc_electron_vertexx\"";
 title_name1="\"mc_electron_vertexy\"";
 axis_name="\"x(mm)\"";
 axis_name1="\"y(mm)\"";
 region="{ 200,-2,2,200,-2,2 }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype} )"

 title_name="\"mc_electron_costheta\"";
 title_name1="\"mc_electron_e\"";
 axis_name="\"costheta\"";
 axis_name1="\"E (GeV)\"";
 region="{ 200,-1,1,300,0,0.3}" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype} )"

#root -l -q -b plot_2D.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1}, ${region} , ${logtype} )"
