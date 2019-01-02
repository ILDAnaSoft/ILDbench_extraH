#include "Extra_Scalar.h"
#include "Recoil_mass.h"

bool Extra_Scalar::analysePhysicalObject(LCCollection* Leps,LCCollection* ISR, LCCollection* PFOWoMuonPhoton, Extra_Scalar_Information_Single &info) {

	std::vector<ReconstructedParticle*> photon  =ToolSet::CRC::Get_POParticle(ISR);
	std::vector<ReconstructedParticle*> leps    =ToolSet::CRC::Get_POParticle(Leps);
	std::vector<ReconstructedParticle*> muon    =ToolSet::CRC::Get_POParticleType_Abs(leps,13);
	std::vector<ReconstructedParticle*> other   =ToolSet::CRC::Get_POParticle(PFOWoMuonPhoton);

	if(!POCutMuon(muon,info.num_muon, info.vari_muon)){
		return(false);
	}

	POCutPhoton(photon,info.num_photon,info.vari_photon);

	std::vector<ReconstructedParticle*> muon_choosed, muon_combined, womuon_combined;
	bool Jrecoil=obvRecoil(muon,muon_choosed);
	if(Jrecoil){
	    muon_combined    = ToolSet::CRC::Get_Isolated(muon_choosed, other, womuon_combined, 0.98);
		bool JPOCut_recovery=POCutDetail(muon_combined,photon,womuon_combined,info.obv);
	}
	else{
		return(false);
	}


	for(int i=0;i<muon_combined.size();i++){
		delete muon_combined[i];
	}

	return(true);
}

