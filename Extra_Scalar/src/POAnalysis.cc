#include "Extra_Scalar.h"
#include "Recoil_mass.h"

int Extra_Scalar::analysePhysicalObject(LCCollection* Leps,LCCollection* ISR, LCCollection* PFOWoMuonPhoton, Extra_Scalar_Information_Single &info, int label) {

	std::vector<ReconstructedParticle*> leps    =ToolSet::CRC::Get_POParticle(Leps);
	std::vector<ReconstructedParticle*> muon    =ToolSet::CRC::Get_POParticleType_Abs(leps,13);
	std::vector<ReconstructedParticle*> photon  =ToolSet::CRC::Get_POParticle(ISR);
	std::vector<ReconstructedParticle*> wophoton=ToolSet::CRC::Get_POParticle(PFOWoMuonPhoton);

	if(!POCutMuon(muon,info.num_muon, info.vari_muon_plus,info.vari_muon_minus)){
		return(-1);
	}

	POCutPhoton(photon,info.num_photon,info.vari_photon_central,info.vari_photon_forward);

	std::vector<ReconstructedParticle*> muon_choosed, muon_combined, womuon_combined;
	bool Jrecoil=obvRecoil(muon,muon_choosed);
	std::vector<ReconstructedParticle*> muon_left=muon-muon_choosed;
	std::vector<ReconstructedParticle*> other=muon_left+wophoton;

	if(Jrecoil){
////    muon_combined    = ToolSet::CRC::Get_Isolated(muon_choosed, other, womuon_combined, 0.98);
////	bool JPOCut_recovery=POCutDetail(muon_combined,photon,womuon_combined,info.obv);
    	if(label==1){
    		muon_combined    = ToolSet::CRC::Get_Isolated(muon_choosed, other, womuon_combined, 0.98);
    	}
    	else{
    		muon_combined  =  muon_choosed;
    		womuon_combined  = other;
    	}
  		bool JPOCut_recovery=POCutDetail(muon_combined,photon,womuon_combined,info.obv);
	}
	else{
		return(-2);
	}


    if(label==1){
		for(int i=0;i<muon_combined.size();i++){
			delete muon_combined[i];
		}
	}

	return(1);
}

