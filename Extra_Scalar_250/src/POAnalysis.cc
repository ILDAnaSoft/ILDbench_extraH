#include "Extra_Scalar.h"
#include "Recoil_mass.h"

int Extra_Scalar::analysePhysicalObject(LCCollection* Leps,LCCollection* ISR, LCCollection* PFOWoMuonPhoton, Extra_Scalar_Information_Single &info, int label) {

	std::vector<ReconstructedParticle*> leps    =ToolSet::CRC::Get_POParticle(Leps);
	std::vector<ReconstructedParticle*> muon    =ToolSet::CRC::Get_POParticleType_Abs(leps,13);
	std::vector<ReconstructedParticle*> photon  =ToolSet::CRC::Get_POParticle(ISR);
	std::vector<ReconstructedParticle*> wophoton=ToolSet::CRC::Get_POParticle(PFOWoMuonPhoton);
	std::vector<ReconstructedParticle*> wo_muon_photon=wophoton-muon;

	if(!POCutMuon(muon,info.num_muon, info.vari_muon_plus,info.vari_muon_minus)){
		return(-1);
	}

	POCutPhoton(photon,info.num_photon,info.vari_photon_central,info.vari_photon_forward);

	std::vector<ReconstructedParticle*> muon_choosed, muon_combined, womuon_combined;
	bool Jrecoil=obvRecoil(muon,muon_choosed);
	std::vector<ReconstructedParticle*> muon_left=muon-muon_choosed;
	std::vector<ReconstructedParticle*> other=muon_left+wo_muon_photon;

	if(Jrecoil){
		//POCutMuonPair(muon_choosed,info.obv);
		
////    muon_combined    = ToolSet::CRC::Get_Isolated(muon_choosed, other, womuon_combined, 0.98);
////	bool JPOCut_recovery=POCutDetail(muon_combined,photon,womuon_combined,info.obv);
    	if(label==1){
    		muon_combined    = ToolSet::CRC::Get_Isolated(muon_choosed, other, womuon_combined, 0.98);
////		if(std::abs(muon_choosed[0]->getEnergy()-muon_combined[0]->getEnergy())>0.001){
////			ToolSet::ShowMessage(1,"combined",_nEvt);
////			ToolSet::ShowMessage(1,"muon choosed",muon_choosed[0]);
////			ToolSet::ShowMessage(1,"muon combined",muon_combined[0]);
////			ToolSet::ShowMessage(1,"other",other);
////		}
////		else if(std::abs(muon_choosed[1]->getEnergy()-muon_combined[1]->getEnergy())>0.001){
////			ToolSet::ShowMessage(1,"combined",_nEvt);
////			ToolSet::ShowMessage(1,"muon choosed",muon_choosed[1]);
////			ToolSet::ShowMessage(1,"muon combined",muon_combined[1]);
////			ToolSet::ShowMessage(1,"other",other);
////		}
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

