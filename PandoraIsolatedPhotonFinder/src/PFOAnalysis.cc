#include "PandoraIsolatedPhotonFinder.h"


bool PandoraIsolatedPhotonFinder::analysePFOParticle( LCCollection* input_pfo, PandoraIsolatedPhotonFinder_Output_Collection& outputPhotonCol, PandoraIsolatedPhotonFinder_Output_Collection& outputWoPhotonCol, PandoraIsolatedPhotonFinder_Information_Single& info_photon, PandoraIsolatedPhotonFinder_Information_Single& info_wophoton, PandoraIsolatedPhotonFinder_Function_Counter& counter){
	std::vector<ReconstructedParticle*> FS =ToolSet::CRC::Get_POParticle(input_pfo);
	std::vector<ReconstructedParticle*> all_photon=ToolSet::CRC::Get_POParticleType(FS,22);
	std::vector<ReconstructedParticle*> photon;
	std::vector<ReconstructedParticle*> wophoton;

	for (int i = 0; i < all_photon.size(); i++ ) {
		ReconstructedParticle* mc = all_photon[i];

		int output_iso =  IsIsolatedPhoton( mc, FS);
		if ((output_iso  == 1) || (output_iso == 2) ){
			photon.push_back(mc);
		} 
	}

	wophoton=FS-photon;

	outputPhotonCol  .Add_Element_RCParticle(photon);
	outputWoPhotonCol.Add_Element_RCParticle(wophoton);

	info_photon.Get_PFOParticles(photon);
	info_wophoton.Get_PFOParticles(wophoton);

	return(true);
}


int PandoraIsolatedPhotonFinder::IsIsolatedPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all) {

	if ( IsIsoPhoton(pfo, all)){
		if(IsCentralPhoton(pfo)){
			return(1);
		}
		else if(IsForwardPhoton(pfo)){
			return(2);
		}
		else{
			return(0);
		}
	}

	return -1;
}



bool PandoraIsolatedPhotonFinder::IsIsoPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all ) {

	if(pfo->getType()!=22){
		return false;
	}

	float cone_energy=getConeEnergy(pfo,all);
	float pfo_energy =pfo->getEnergy();
	float energy_ratio = pfo_energy/cone_energy;
	if(energy_ratio< _ConeEnergyRatio){
		return false;
	}
	return true;
}


float PandoraIsolatedPhotonFinder::getConeEnergy( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all ) {
	float coneE = 0;

	TVector3 P( pfo->getMomentum() );
	int npfo = all.size();
	for ( int i = 0; i < npfo; i++ ) {
		ReconstructedParticle* pfo_i = all[i]; 

		// don't add itself to the cone energy
		TVector3 P_i( pfo_i->getMomentum() );
		float cosTheta = P.Dot( P_i )/(P.Mag()*P_i.Mag());
		if ( cosTheta >= _maxCosConeAngle)
			coneE += pfo_i->getEnergy(); 
	}

	return coneE;
}


bool PandoraIsolatedPhotonFinder::IsCentralPhoton( ReconstructedParticle* pfo) {
	float  energy = pfo->getEnergy();
	float  p      = ToolSet::CMC::Cal_P(pfo);
	float  angle  = std::abs(ToolSet::CMC::Cal_CosTheta(pfo));
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



bool PandoraIsolatedPhotonFinder::IsForwardPhoton( ReconstructedParticle* pfo) {
	float energy = pfo->getEnergy();
	float  p      = ToolSet::CMC::Cal_P(pfo);
	float  angle  = std::abs(ToolSet::CMC::Cal_CosTheta(pfo));
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
//			ShowMessage(2,"not max angle cut forward, 0",angle);
			return false;
		}
	} 

	return true;
}

