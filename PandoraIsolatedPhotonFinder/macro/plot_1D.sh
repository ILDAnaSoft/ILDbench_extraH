#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"

cd ${DIR}/


 mass_profile="{ \"../results/output_PFO_wo_overlay\"
 	 			}"; 
 title_name="{\"isophoton_particle_e_vec\"
 	    }";
 leg_name="{\"IsoPhoton\"
 	    }";
 region="{ 200,0,400}" 
 axistype="{ \"normal\" }" 

 root -l -q -b plot_1D_different_observable_vec.C"(${mass_profile}, ${title_name} ,${leg_name}, ${region}, ${axistype})"
