#include "Extra_Scalar.h"
template<typename TOBVRECOIL>
bool Extra_Scalar::obvRecoil(std::vector<TOBVRECOIL> in, std::vector<TOBVRECOIL> &out) {
	int num=in.size();

	std::vector<TLorentzVector> inVector;
	for(int i=0;i<num;i++){
		TLorentzVector in_tmp= TLorentzVector( in[i]->getMomentum(), in[i]->getEnergy() );
		inVector.push_back(in_tmp);
	}

	float chi_min= 1000000.0;
	float chi_tmp=chi_min;
	float recoil_mass_final = 999.99;
	float pair_mass_final = 999.99;

	TLorentzVector collider;
	TLorentzVector recoil_mom;
	TLorentzVector pair_mom;
	collider.SetPxPyPzE            (_cmenergy*sin(0.014/2.0),0,0,_cmenergy);

	int choosei=1000,choosej=1000;
	for(int i=0;i<num-1;i++){
		for(int j=1;j<num;j++){
			pair_mom = inVector[i]+inVector[j];
			if(std::abs(pair_mom.M()-91.187)>40.0){
				continue;
			}
			if((in[i]->getCharge())*(in[j]->getCharge())>0){//Should be different sign lepton
				continue;
			}
			recoil_mom = collider-inVector[i]-inVector[j];
			float  recoil_mass=recoil_mom.M();
			float  pair_mass=pair_mom.M();
			float  sigma_pair=1;
			float  sigma_recoil=1;
		
			if(fabs(_hmass-10)<0.00001){
					sigma_pair  =2.06;
					sigma_recoil=4.26;
			}
			else if(fabs(_hmass-15)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=3.70;
			}
			else if(fabs(_hmass-20)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=3.20;
			}
			else if(fabs(_hmass-25)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=2.7;
			}
			else if(fabs(_hmass-30)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=2.17;
			}
			else if(fabs(_hmass-35)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=2.07;
			}
			else if(fabs(_hmass-40)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.97;
			}
			else if(fabs(_hmass-45)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.87;
			}
			else if(fabs(_hmass-50)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.79;
			}
			else if(fabs(_hmass-55)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.72;
			}
			else if(fabs(_hmass-60)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.66;
			}
			else if(fabs(_hmass-65)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.61;
			}
			else if(fabs(_hmass-70)<0.00001){
					sigma_pair  =2.06;
					sigma_recoil=1.55;
			}
			else if(fabs(_hmass-75)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.52;
			}
			else if(fabs(_hmass-80)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.49;
			}
			else if(fabs(_hmass-85)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.46;
			}
			else if(fabs(_hmass-90)<0.00001){
					sigma_pair  =2.07;
					sigma_recoil=1.43;
			}
			else if(fabs(_hmass-95)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.38;
			}
			else if(fabs(_hmass-100)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.33;
			}
			else if(fabs(_hmass-105)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.28;
			}
			else if(fabs(_hmass-110)<0.00001){
					sigma_pair  =2.03;
					sigma_recoil=1.24;
			}
			else if(fabs(_hmass-115)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.20;
			}
			else if(fabs(_hmass-120)<0.00001){
					sigma_pair  =2.05;
					sigma_recoil=1.13;
			}
			else if(fabs(_hmass-125)<0.00001){
					sigma_pair  =2.03;
					sigma_recoil=1.06;
			}
			else{
					sigma_pair  =2.05;
					sigma_recoil=1.13;
				//ShowMessage(2,"wrong hmass:",_hmass);
				
			}
			chi_tmp = std::pow((pair_mass-91.187)/sigma_pair,2)+std::pow((recoil_mass-_hmass)/sigma_recoil,2);

			if(chi_tmp<chi_min){
				chi_min = chi_tmp;
				choosei=i;
				choosej=j;
				recoil_mass_final=recoil_mass;
				pair_mass_final=pair_mass;
			}
		}
	}

	if(choosei!=1000 && choosej!=1000){
		if(in[choosei]->getCharge()>0){
			out.push_back(in[choosei]);
			out.push_back(in[choosej]);
		}
		else{
			out.push_back(in[choosej]);
			out.push_back(in[choosei]);
		}
		return(true);
	}
////else{
////	ToolSet::ShowMessage(2,"wrong pair",in);
////}
	return(false);
}


