#include "Extra_Scalar.h"
#include "Recoil_mass.h"

bool Extra_Scalar::analysePO_MC_Cheating_Muon(LCCollection* Muon,LCCollection* Photon,LCCollection* PFOWoMuonPhoton,LCRelationNavigator* navmc, Extra_Scalar_Information_Single &info) {

////std::vector<ReconstructedParticle*> pfos_recovery,choosedmuon_recovery;

////std::vector<ReconstructedParticle*> iso_pandora_photon        =checkPOFinalState(PandoraIsoPhoton);
////std::vector<ReconstructedParticle*> iso_pandora_forward_photon=checkPOFinalState(PandoraIsoForwardPhoton);



////std::vector<MCParticle*> MCs            =ToolSet::CMC::Get_MCParticle(MC_col);
////std::vector<MCParticle*> de_FS          =ToolSet::CMC::Get_MC_DetectorSimulating_FS(MCs);
////std::vector<MCParticle*> mc_muon        =ToolSet::CMC::Get_MCParticleType_Abs(de_FS,13);
////std::vector<MCParticle*> mc_muon_iso    =ToolSet::CMC::Get_Isolated(mc_muon,de_FS);
////std::vector<ReconstructedParticle*> leps;
////if(mc_muon_iso.size()>1){
////	leps= ToolSet::CRC::Get_A_PFO_From_MC_Vec(mc_muon_iso,navmc);
////}
////std::vector<ReconstructedParticle*> PFOs=checkPOFinalState(PFOs_col);
////std::vector<ReconstructedParticle*> pfos=PFOs-leps;

////info.data_muon_de.pfo_num = PFOs.size();


////info.num_muon_de.num       = mc_muon_iso.size();
////info.num_muon_de.num_plus  = 1;
////info.num_muon_de.num_minus = 1;

////std::vector<MCParticle*> choosedmuon;
////std::vector<ReconstructedParticle*> leps_left;
////bool Jrecoil=obvRecoil(mc_muon_iso,choosedmuon);

////if(Jrecoil){
////	MCCut_Muon(choosedmuon,info.num_muon,info.vari_muon);
////	POCut_Global(pfos,leps_left,choosedmuon,info.obv);

////	bool Jrecovery=checkRCIsoLepCone(choosedmuon,pfos,choosedmuon_recovery,pfos_recovery,info);
////	bool JPOCut_recovery=POCutDetail(pfos_recovery,leps_left,choosedmuon_recovery,info.obv);
////	POCutPhoton(iso_pandora_photon,info.num_photon,info.vari_photon);
////}
////for(int i=0;i<choosedmuon_recovery.size();i++){
////	delete choosedmuon_recovery[i];
////}


	return(true);
}

