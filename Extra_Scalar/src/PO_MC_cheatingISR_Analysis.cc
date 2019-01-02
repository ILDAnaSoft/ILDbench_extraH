#include "Extra_Scalar.h"
#include "Recoil_mass.h"

bool Extra_Scalar::analysePO_MC_Cheating_ISR(LCCollection* Muon,LCCollection* Photon,LCCollection* PFOWoMuonPhoton,LCRelationNavigator* navmc, Extra_Scalar_Information_Single &info) {

//  std::vector<ReconstructedParticle*> pfos_recovery,choosedmuon_recovery;
//  std::vector<ReconstructedParticle*> leps_left;

//  std::vector<MCParticle*> iso_pandora_photon        =ToolSet::CMC::Get_MCParticle(PandoraIsoPhoton);



//  std::vector<ReconstructedParticle*> leps= ToolSet::CRC::Get_POParticle(Isoleps);
//  std::vector<ReconstructedParticle*> pfos= ToolSet::CRC::Get_POParticle(PFOsWithoutIsoleps);
//  std::vector<ReconstructedParticle*> PFOs= ToolSet::CRC::Get_POParticle(PFOs_col);

//  info.data_muon_de.pfo_num = PFOs.size();


//  std::vector<ReconstructedParticle*> muonminus=checkPOParticleType(leps,13);
//  std::vector<ReconstructedParticle*> muonplus=checkPOParticleType(leps,-13);
//  std::vector<ReconstructedParticle*> muon;
//  muon=muonminus+muonplus;
//  info.num_muon_de.num       = muon.size();
//  info.num_muon_de.num_plus  = muonplus.size();
//  info.num_muon_de.num_minus = muonminus.size();

//  if(POCutMuon(muon,info.num_muon,info.vari_muon)){
//  	std::vector<ReconstructedParticle*> choosedmuon;
//  	bool Jrecoil=obvRecoil(muon,choosedmuon);
//  	leps_left=leps-choosedmuon;
//  	if(Jrecoil){
//  		bool JPOCut=POCutDetail(pfos,leps_left,choosedmuon,info.data_muon_py_im);


//  		bool Jrecovery=checkRCIsoLepCone(choosedmuon,pfos,choosedmuon_recovery,pfos_recovery,info);
//  		bool JPOCut_recovery=POCutDetail(,choosedmuon_recovery,leps,pfos_recovery,,info.obv);
//  		MCCutPhoton(iso_pandora_photon,info.num_photon,info.vari_photon);
//  	}
//  	for(int i=0;i<choosedmuon_recovery.size();i++){
//  		delete choosedmuon_recovery[i];
//  	}
//  }


    return(true);
}

