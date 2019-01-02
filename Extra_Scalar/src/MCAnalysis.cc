#include "Extra_Scalar.h"
#include "Recoil_mass.h"

bool Extra_Scalar::analyseMCParticle( LCCollection* AllMC,   Extra_Scalar_Information &info) {
	//generate all basic sorts 
	std::vector<MCParticle*> hs_FS, py_ex_FS, py_im_FS, de_FS;
	Get_All_Level_FS(AllMC, hs_FS, py_ex_FS, py_im_FS, de_FS);
	Get_MC_Observables( hs_FS,     info.hs);
	Get_MC_Observables( py_ex_FS,  info.py_ex);
	Get_MC_Observables( py_im_FS,  info.py_im);
	Get_MC_Observables( de_FS,     info.de);

	return(true);
}


void Extra_Scalar::Get_All_Level_FS(LCCollection* AllMC, std::vector<MCParticle*> &hard_scattering, std::vector<MCParticle*> &pythia_explicit, std::vector<MCParticle*> &pythia_stable, std::vector<MCParticle*> &detector){
	std::vector<MCParticle*> MCs     =ToolSet::CMC::Get_MCParticle(AllMC);

	hard_scattering =ToolSet::CMC::Get_MC_HardScattering_FS(MCs);
	pythia_stable   =ToolSet::CMC::Get_MC_PythiaShowering_FS(MCs);
	detector        =ToolSet::CMC::Get_MC_DetectorSimulating_FS(MCs);

	_chain.Set_ChainVec(hard_scattering);
	_chain.Set_RC();
    std::vector<std::vector<MCParticle*> >                           end = _chain.Get_MCEnd();
	pythia_explicit= ToolSet::Vec_Expand_VecVec(end);
}




bool Extra_Scalar::Get_MC_Observables( std::vector<MCParticle*> FS,   Extra_Scalar_Information_Single &info_single) {
	// for all detecter final state
	std::vector<MCParticle*> photon =ToolSet::CMC::Get_MCParticleType(FS,22);

	std::vector<MCParticle*> muon   =ToolSet::CMC::Get_MCParticleType_Abs(FS,13);

	std::vector<MCParticle*> muon_choosed, muon_combined, womuon_combined;

	if(!MCCutMuon(muon, info_single.num_muon, info_single.vari_muon)){
		return(false);
	}

	MCCutPhoton(photon, info_single.num_photon, info_single.vari_photon);

	bool Jrecoil=obvRecoil(muon,muon_choosed);

	if(Jrecoil){
		muon_combined    = ToolSet::CMC::Get_Isolated(muon_choosed, FS, womuon_combined, 0.98);
		bool JMCCut      = MCCutDetail(muon_combined, photon, womuon_combined, info_single.obv);
	}
	else{
		return(false);
	}


	for(int i=0;i<muon_combined.size();i++){
		delete muon_combined[i];
	}

	return(true);
}






