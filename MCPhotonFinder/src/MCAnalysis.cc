#include "MCPhotonFinder.h"


bool MCPhotonFinder::analyseMCParticle( LCCollection* inputmcCol, MCPhotonFinder_Output_Collection& outputPhotonCol,MCPhotonFinder_Output_Collection &outputWoPhotonCol, MCPhotonFinder_Information_Single & info_photon, MCPhotonFinder_Information_Single & info_wophoton, MCPhotonFinder_Function_Counter  &counter){
	std::vector<MCParticle*> FS        =ToolSet::CMC::Get_MCParticle(inputmcCol);
	std::vector<MCParticle*> all_photon=ToolSet::CMC::Get_MCParticleType(FS,22);
	std::vector<MCParticle*> photon;
	std::vector<MCParticle*> wophoton;


	for (int i = 0; i < all_photon.size(); i++ ) {
		MCParticle* mc = all_photon[i];

		int output_iso =  IsIsolatedPhoton( mc, FS);
		if ((output_iso  == 1) || (output_iso == 2) ){
			photon.push_back(mc);
		} 
	}
	wophoton = FS-photon; 

	outputPhotonCol.Add_Element_MCParticle(photon);
	outputWoPhotonCol.Add_Element_MCParticle(wophoton);

	info_photon.Get_MCParticles(photon);
	info_wophoton.Get_MCParticles(wophoton);

	return(true);

}


int MCPhotonFinder::IsIsolatedPhoton( MCParticle* mc, std::vector<MCParticle*> all) {

	if ( IsIsoPhoton(mc, all)){
		if(IsCentralPhoton(mc)){
			return(1);
		}
		else if(IsForwardPhoton(mc)){
			return(2);
		}
		else{
			return(0);
		}
	}

	return -1;
}



bool MCPhotonFinder::IsIsoPhoton( MCParticle* mc, std::vector<MCParticle*> all ) {

	if(mc->getPDG()!=22){
		return false;
	}

	std::vector<MCParticle*> incone=ToolSet::CMC::Get_InCone(mc, all, _maxCosConeAngle);
	TLorentzVector sum_incone=ToolSet::CMC::Get_Sum_To_Lorentz(incone);
	float cone_energy=sum_incone.E();
	float mc_energy =mc->getEnergy();
	float energy_ratio = mc_energy/cone_energy;

	if(energy_ratio< _ConeEnergyRatio){
		return false;
	}
	return true;
}


float MCPhotonFinder::getConeEnergy( MCParticle* mc, std::vector<MCParticle*> all ) {
	float coneE = 0;

	TVector3 P( mc->getMomentum() );
	int nmc = all.size();
	for ( int i = 0; i < nmc; i++ ) {
		MCParticle* mc_i = all[i]; 

		// don't add itself to the cone energy
		TVector3 P_i( mc_i->getMomentum() );
		float cosTheta = P.Dot( P_i )/(P.Mag()*P_i.Mag());
		if ( cosTheta >= _maxCosConeAngle)
			coneE += mc_i->getEnergy(); 
	}

	return coneE;
}


bool MCPhotonFinder::IsCentralPhoton( MCParticle* mc) {
	float  energy = mc->getEnergy();
	float  p      = ToolSet::CMC::Cal_P(mc);
	float  angle  = std::abs(ToolSet::CMC::Cal_CosTheta(mc));
	// set cut
	if (_useEnergy){
		if(_maxEnergyCut > 0 && energy > _maxEnergyCut){
			//			ShowMessage(2,"not max energy cut, 0",energy);
			return false;
		}
		if(_minEnergyCut > 0 && energy<_minEnergyCut){
			//			ShowMessage(2,"not min energy cut, 0",energy);
			return false;
		}
	} 

	if (_usePolarAngle){
		if(_minCosTheta > 0 && angle<_minCosTheta ){
			//			ShowMessage(2,"not min angle cut, 0",angle);
			return false;
		}
		if(_maxCosTheta >0 && angle> _maxCosTheta){
			//			ShowMessage(2,"not max angle cut no forward, 0",angle);
			return false;
		}
	} 

	return true;
}



bool MCPhotonFinder::IsForwardPhoton( MCParticle* mc) {
	float energy = mc->getEnergy();
	float  p      = ToolSet::CMC::Cal_P(mc);
	float  angle  = std::abs(ToolSet::CMC::Cal_CosTheta(mc));
	// set cut
	if (_useForwardEnergy){
		if(_maxForwardEnergyCut > 0 && energy > _maxForwardEnergyCut){
			//			ShowMessage(2,"not max energy cut,  forward0",energy);
			return false;
		}
		if(_minForwardEnergyCut > 0 && energy<_minForwardEnergyCut){
			//			ShowMessage(2,"not min energy cut forward, 0",energy);
			return false;
		}
	} 

	if (_useForwardPolarAngle){
		if(_minForwardCosTheta > 0 && angle<_minForwardCosTheta ){
			//			ShowMessage(2,"not min angle cut forward, 0",angle);
			return false;
		}
		if(_maxForwardCosTheta >0 && angle> _maxForwardCosTheta){
			//ToolSet::ShowMessage(1,"not max angle cut forward, 0",angle,_maxForwardCosTheta);
			return false;
		}
	} 

	return true;
}

