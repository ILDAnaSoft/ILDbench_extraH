#include "MCLeptonTagging.h"


bool MCLeptonTagging::analyseMCParticle( LCCollection* inputmcCol, LCCollectionVec* outputleptonCol,LCCollectionVec* outpuwWoleptonCol, MCLeptonTagging_Information_Single &info, MCLeptonTagging_Function_Counter &counter){
	std::vector<MCParticle*> MCs =ToolSet::CMC::Get_MCParticle(inputmcCol);
	std::vector<MCParticle*> leps,woleps;

	checkIsoLeptons(MCs,leps,woleps);

	info.leps.Get_MCParticles_Information(leps);
	for(unsigned int i=0;i<leps.size();i++){
		if(leps[i]->getCharge()>0){
			info.num_muon.num_plus++;
		}
		else if(leps[i]->getCharge()<0){
			info.num_muon.num_minus++;
		}
		else{
			info.num_muon.num_neutral++;
		}
		info.num_muon.num++;
	}

	counter.pass_all++;

	return(true);
}


void MCLeptonTagging::checkIsoLeptons(std::vector<MCParticle*> input, std::vector<MCParticle*> &IsoLep, std::vector<MCParticle*> &mcs_WO_IsoLep )
{
	int nmcs = input.size();
	for( int i = 0; i < nmcs; i++ )
	{
		if ( IsIsoLep( input[i], input)) 
		{
			IsoLep.push_back(input[i]);
		}
		else 
		{
			mcs_WO_IsoLep.push_back(input[i]);
		}
	}
	return;
}



bool MCLeptonTagging::IsIsoLep( MCParticle* mcs, std::vector<MCParticle*> allmcs) {
	if ( !IsCharged(mcs) ){
		return false;
	}

	if ( IsLepton(mcs)==0 ){
		return false;
	}

	if ( _lep_type!=0 ){
		if ( IsLepton(mcs)!=_lep_type ){
			return false;
		}
	}

	std::vector<MCParticle*> incone=ToolSet::CMC::Get_InCone(mcs, allmcs, 0.95);
	bool JIsolated=true;
	for(unsigned int i=1;i<incone.size();i++){
		if(incone[i]->getPDG()!=22){
			JIsolated=false;
			break;
		}
	}
	if(!JIsolated){
		return false;
	}

	return true;

}



bool MCLeptonTagging::IsCharged( MCParticle* mcs ) {
	if ( mcs->getCharge() == 0 ) return false;
	return true;
}



int MCLeptonTagging::IsLepton( MCParticle* mcs) {

	bool Jmin_E=false;
	bool Jcostheta=false;
	int pdg=std::abs(mcs->getPDG());
	if(pdg!=11&&pdg!=13){
		return(0);
	}
	if( mcs->getEnergy()> _cut.MinEnergy){
		Jmin_E = true;
	}
	if( std::abs(ToolSet::CMC::Cal_CosTheta(mcs)) < _cut.detector_costheta){
		Jcostheta= true;
	}


	if(Jmin_E&&Jcostheta){
		return(pdg);
	}
	else{
		return(0);
	}

}


