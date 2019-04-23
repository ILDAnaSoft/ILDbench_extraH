#include "Extra_Scalar.h"
#include "Recoil_mass.h"

int Extra_Scalar::analyseMCParticle( LCCollection* MuonCol, LCCollection* PhotonCol, LCCollection* WoPhotonCol,  Extra_Scalar_Information_Single &info) {
	//generate all basic sorts 
	std::vector<MCParticle*> muon    =ToolSet::CMC::Get_MCParticle(MuonCol);
	std::vector<MCParticle*> photon  =ToolSet::CMC::Get_MCParticle(PhotonCol);
	std::vector<MCParticle*> wophoton=ToolSet::CMC::Get_MCParticle(WoPhotonCol);
	int JMC=Get_MC_Observables( muon, photon, wophoton,  info);

	return(JMC);
}


int Extra_Scalar::Get_MC_Observables( std::vector<MCParticle*> muon,  std::vector<MCParticle*> photon, std::vector<MCParticle*> wophoton,  Extra_Scalar_Information_Single &info_single) {
	// for all detecter final state

	std::vector<MCParticle*> muon_choosed, muon_combined, womuon_combined;

	if(!MCCutMuon(muon, info_single.num_muon, info_single.vari_muon_plus, info_single.vari_muon_minus)){
		return(-1);
	}

	MCCutPhoton(photon, info_single.num_photon, info_single.vari_photon_central,info_single.vari_photon_forward);

	bool Jrecoil=obvRecoil(muon,muon_choosed);
	std::vector<MCParticle*> muon_left=muon-muon_choosed;
	std::vector<MCParticle*> other=muon_left+wophoton;

	if(Jrecoil){
	//	muon_combined    = ToolSet::CMC::Get_Isolated(muon_choosed, wophoton, womuon_combined, 0.98);
	//	bool JMCCut      = MCCutDetail(muon_combined, photon, womuon_combined, info_single.obv);
		bool JMCCut      = MCCutDetail(muon_choosed, photon, other, info_single.obv);
	}
	else{
		return(-2);
	}


	for(int i=0;i<muon_combined.size();i++){
		delete muon_combined[i];
	}

	return(1);
}






