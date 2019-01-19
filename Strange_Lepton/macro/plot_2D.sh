#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}

  mass_profile="{ \"../results/sm_2f_l_eL.pR_test\"  
 	 			}" 

 title_name="\"mc_variable_vec_endpointz\"";
 title_name1="\"mc_variable_vec_endpointr\"";
 axis_name="\"z(mm)\"";
 axis_name1="\"r(mm)\"";
 region="{ 200,-3000,3000,200,0,3000 }" 
 logtype="{ \"no\", \"no\" }" 
 root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype})"

 title_name="\"mc2_variable_vec_endpointz\"";
 title_name1="\"mc2_variable_vec_endpointr\"";
 axis_name="\"z(mm)\"";
 axis_name1="\"r(mm)\"";
 region="{ 200,-3000,3000,200,0,3000 }" 
 logtype="{ \"no\", \"no\" }" 
 root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype})"

 title_name="\"mc_variable_vec_endpointx\"";
 title_name1="\"mc_variable_vec_endpointy\"";
 axis_name="\"x(mm)\"";
 axis_name1="\"y(mm)\"";
 region="{ 200,-3000,3000,200,-3000,3000 }" 
 logtype="{ \"no\", \"no\" }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype})"

 title_name="\"mc2_variable_vec_endpointx\"";
 title_name1="\"mc2_variable_vec_endpointy\"";
 axis_name="\"x(mm)\"";
 axis_name1="\"y(mm)\"";
 region="{ 200,-3000,3000,200,-3000,3000 }" 
 logtype="{ \"no\", \"no\" }" 
 root -l -q -b plot_2D_vec.C"(${mass_profile},${title_name},${title_name1},${axis_name},${axis_name1},${region}, ${logtype})"

