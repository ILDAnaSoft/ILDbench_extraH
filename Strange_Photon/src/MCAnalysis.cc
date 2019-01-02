#include "Strange_Photon.h"
#include "CMC.h"
using namespace lcio;

int Strange_Photon::analyseMCParticle( LCCollection* Allmc,  LCRelationNavigator* navMCToPFO,  Strange_Photon_Information &info, Strange_Photon_Information &info2, Strange_Photon_Counter& counter) {
	//generate all basic sorts 
	ToolSet::CMC::Set_Nav_From_MC_To_RC(navMCToPFO);

	std::vector<MCParticle*> MCs          =ToolSet::CMC::Get_MCParticle(Allmc);

	std::vector<MCParticle*> py_FS        =ToolSet::CMC::Get_MC_PythiaShowering_FS(MCs);
	std::vector<MCParticle*> hs_FS        =ToolSet::CMC::Get_MC_HardScattering_FS(MCs);

	std::vector<MCParticle*> py_all_photon=ToolSet::CMC::Get_MCParticleType(py_FS,22);

	std::vector<MCParticle*> py_photon;

	for (int i = 0; i < py_all_photon.size(); i++ ) {
		MCParticle* mc = py_all_photon[i];
		if ( mc->getEnergy()<100 ){
			continue;
		} 

		if(std::abs(ToolSet::CMC::Cal_CosTheta(mc))>0.98){
			continue;
		} 

		if ( IsIsolatedPhoton( mc, py_FS ) ==1){
			//satisfy isolation photon condition
			py_photon.push_back(py_all_photon[i]);
		} 
	}

	if(py_photon.size()==0){return(0);}


	// get lost energy photon
	ToolSet::CChain_Vec         _photon_chain ;
	_photon_chain.Set_ChainVec(py_photon,_navmcpfo,_navpfomc);

	std::vector<ReconstructedParticle*>      MC_photon_conversion;
	std::vector<MCParticle*>                 lost_energy_mc_photon;


	bool has_lost_energy_photon=false;
	for(unsigned int i=0;i<_photon_chain.Num();i++){

		float mc_energy  = _photon_chain.Get_MCInput()[i]->getEnergy();
		float pfo_energy = _photon_chain.Get_Combined_RC()[i]->getEnergy();
		if(mc_energy-pfo_energy>20){

			// store data
			info.data_variable_vec.Get_MCParticles_Information(_photon_chain.Get_FromRC_MC()[i]);
			info.data_observable.visible_energy=mc_energy-pfo_energy;

			MC_photon_conversion.push_back(_photon_chain.Get_Combined_RC()[i]);
			lost_energy_mc_photon.push_back(_photon_chain.Get_MCInput()[i]);
			has_lost_energy_photon=true;
		}
	}

	// store data
	info2    .data_variable_vec.Get_MCParticles_Information(lost_energy_mc_photon);
	_pfo_info.data_variable_vec.Get_PFOParticles_Information(MC_photon_conversion);

	// finish
	counter.pass_all++;
	_photon_chain.Clear();


	if(has_lost_energy_photon){
		return(1);
	}

	return(0);
}



int Strange_Photon::IsIsolatedPhoton( MCParticle* mc, std::vector<MCParticle*> all ) {

	if ( IsIsoPhoton(mc, all) ==1 ){
		return 1;
	}

	return -1;
}



int Strange_Photon::IsIsoPhoton( MCParticle* mc, std::vector<MCParticle*> all ) {

	if(mc->getPDG()!=22){
		return -1;
	}

	float cone_energy=getConeEnergy(mc,all);
	float mc_energy =mc->getEnergy();
	float energy_ratio = mc_energy/cone_energy;
	if(energy_ratio< _ConeEnergyRatio){
		return -2;
	}
	return 1;
}


float Strange_Photon::getConeEnergy( MCParticle* mc, std::vector<MCParticle*> all ) {
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


