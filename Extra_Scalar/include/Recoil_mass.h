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


