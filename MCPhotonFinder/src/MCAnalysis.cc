#include "MCPhotonFinder.h"


bool MCPhotonFinder::analyseMCParticle( LCCollection* input_mc, LCCollectionVec* output_photon,LCCollectionVec* output_other, MCPhotonFinder_Single_Counter& counter){
	std::vector<MCParticle*> py_FS                 =ToolSet::CMC::Get_MCParticle(input_mc);
	std::vector<MCParticle*> py_all_photon=ToolSet::CMC::Get_MCParticleType(py_FS,22);
	std::vector<MCParticle*> py_photon;

    for (int i = 0; i < py_all_photon.size(); i++ ) {
    	MCParticle* mc = py_all_photon[i];

    	int output_iso =  IsIsolatedPhoton( mc, py_FS);
    	if ((output_iso  == 1) || (output_iso == 2) ){
			py_photon.push_back(py_all_photon[i]);
    		counter.pass_all++;
    		output_photon->addElement( mc );
    	} 
		else{
    		output_other->addElement( mc );
		}
    }

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

	float cone_energy=getConeEnergy(mc,all);
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
	float  p      = TVector3( mc->getMomentum() ).Mag();
	float  angle  = abs(TVector3( mc->getMomentum() ).CosTheta());
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
		if(_maxCosTheta >0 && _useForwardPolarAngle && angle> _minForwardCosTheta){
//			ShowMessage(2,"not max angle cut with forward, 0",angle);
			return false;
		}
		if(_maxCosTheta >0 && !_useForwardPolarAngle && angle> _maxCosTheta){
//			ShowMessage(2,"not max angle cut no forward, 0",angle);
			return false;
		}
	} 

	return true;
}



bool MCPhotonFinder::IsForwardPhoton( MCParticle* mc) {
	float energy = mc->getEnergy();
	float  p      = TVector3( mc->getMomentum() ).Mag();
	float  angle  = abs(TVector3( mc->getMomentum() ).CosTheta());
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

