#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

channel=$1
para=$2
file_name="\"$1$2\""

cd ${DIR}
echo ${DIR}

#mass_profile="{ \"../results/higgs_e2_eL.pR\"  
# mass_profile="{ \"../results/2f_l_eL.pR\"  
#	 			}" 

## for x-y plane
#title_name0="\"mcs_check_py_particle_endpointx\"";
#title_name1="\"mcs_check_py_particle_endpointy\"";
#title_name2="\"mcs_check_py_obv_energy_difference\"";
#axis_name0="\"x(mm)\"";
#axis_name1="\"y(mm)\"";
#region="{ 600,-3000,3000,600,-3000,3000}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec_cut.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"



#mass_profile="{ \"../results/higgs_e2_eL.pR\"  
#mass_profile="{ \"../results/2f_l_eL.pR\"  
#	 			}" 

 # for x-y plane
#title_name0="\"pfo_check_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_e_vec\"";
#title_name2="\"mcs_check_de_obv_photon_head\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{PFO}\"";
#region="{ 60,-100,100,60,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"

#title_name0="\"mcs_check_py_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_e_vec\"";
#title_name2="\"mcs_check_de_obv_photon_head\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{PFO}\"";
#region="{ 60,-100,100,60,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"

#title_name0="\"mcs_check_de_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_e_vec\"";
#title_name2="\"mcs_check_de_obv_photon_head\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{PFO}\"";
#region="{ 60,-100,100,60,0,300}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"

#title_name0="\"pfo_check_obv_energy_difference\"";
#title_name1="\"mcs_check_de_obv_energy_difference\"";
#title_name2="\"mcs_check_de_obv_photon_head\"";
#axis_name0="\"E_{PFO}-E_{MCHS}\"";
#axis_name1="\"E_{PFO}-E_{MCDE}\"";
#region="{ 60,-100,100,60,-100,100}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"

#title_name0="\"pfo_check_obv_energy_difference\"";
#title_name1="\"mcs_check_py_obv_energy_difference\"";
#title_name2="\"mcs_check_de_obv_photon_head\"";
#axis_name0="\"E_{PFO}-E_{MCHS}\"";
#axis_name1="\"E_{PFO}-E_{MCPY}\"";
#region="{ 60,-100,100,60,-100,100}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


#title_name0="\"mcs_check_de_obv_energy_difference\"";
#title_name1="\"mcs_check_py_obv_energy_difference\"";
#title_name2="\"mcs_check_de_obv_photon_head\"";
#axis_name0="\"E_{PFO}-E_{MCDS}\"";
#axis_name1="\"E_{PFO}-E_{MCPS}\"";
#region="{ 60,-100,100,60,-100,100}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


##mass_profile="{ \"../results/higgs_e2_eL.pR\"  
#  mass_profile="{ \"../results/2f_l_eL.pR\"  
# 	 			}" 
## for x-y plane
#title_name0="\"mcs_check_py_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_hcal_vec\"";
#title_name2="\"pfo_check_particle_e_vec\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{hcal}/E\"";
#region="{ 100,-80,80,100,0,0.1}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec_cut_ecal.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


##mass_profile="{ \"../results/higgs_e2_eL.pR\"  
#  mass_profile="{ \"../results/2f_l_eL.pR\"  
# 	 			}" 
## for x-y plane
#title_name0="\"mcs_check_py_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_ecal_vec\"";
#title_name2="\"pfo_check_particle_e_vec\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{ecal}/E\"";
#region="{ 100,-80,80,100,0,0.005}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec_cut_ecal.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


##mass_profile="{ \"../results/higgs_e2_eL.pR\"  
#  mass_profile="{ \"../results/2f_l_eL.pR\"  
# 	 			}" 
## for x-y plane
#title_name0="\"mcs_check_py_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_ecal_vec\"";
#title_name2="\"pfo_check_particle_hcal_vec\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{ecal}/E_{hcal}\"";
#region="{ 100,-80,80,100,0,1}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000000
#root -l -b -q plot_2D_vec_cut_ecal.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


##mass_profile="{ \"../results/higgs_e2_eL.pR\"  
   mass_profile="{ \"../results/2f_l_eL.pR\"  
  	 			}" 
 # for x-y plane
 title_name0="\"mcs_check_py_obv_energy_difference\"";
 title_name1="\"pfo_check_particle_lumical_vec\"";
 title_name2="\"pfo_check_particle_e_vec\"";
 axis_name0="\"E_{PFO}-E_{MC}\"";
 axis_name1="\"E_{lumical}/E_{PFO}\"";
 region="{ 100,-80,80,100,0.95,1}" 
 logtype="{ \"no\", \"no\" }" 
 eventnum=100000000
 root -l -b -q plot_2D_vec_cut_ecal.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


##mass_profile="{ \"../results/higgs_e2_eL.pR\"  
#  mass_profile="{ \"../results/2f_l_eL.pR\"  
# 	 			}" 
## for x-y plane
#title_name0="\"mcs_check_py_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_ecal_vec\"";
#title_name2="\"pfo_check_particle_hcal_vec\"";
#title_name3="\"pfo_check_particle_e_vec\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{ecal}/E_{hcal}\"";
#region="{ 100,-80,80,100,0,1000}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000
#root -l -b -q plot_2D_vec_ecal_extra_cut.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${title_name3}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


#  mass_profile="{ \"../results/2f_l_eL.pR\"  
# 	 			}" 
## for x-y plane
#title_name0="\"mcs_check_py_obv_energy_difference\"";
#title_name1="\"pfo_check_particle_hcal_vec\"";
#title_name2="\"pfo_check_particle_ecal_vec\"";
#title_name3="\"pfo_check_particle_e_vec\"";
#axis_name0="\"E_{PFO}-E_{MC}\"";
#axis_name1="\"E_{ecal}/E_{hcal}\"";
#region="{ 100,-80,80,100,0,01}" 
#logtype="{ \"no\", \"no\" }" 
#eventnum=100000
#root -l -b -q plot_2D_vec_ecal_extra_cut.C"(${mass_profile},${title_name0},${title_name1},${title_name2}, ${title_name3}, ${axis_name0},${axis_name1},${region}, ${logtype}, ${eventnum})"


