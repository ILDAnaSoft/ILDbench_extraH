#include "Strange_Photon.h"
#include "CRC.h"


int Strange_Photon::analysePFOParticle(LCCollection* PFOs_col, LCRelationNavigator* navPFOToMC, Strange_Photon_Information_Single &info, Strange_Photon_Function_Counter& counter){

	std::vector<ReconstructedParticle*> pfo = ToolSet::CRC::Get_POParticle(PFOs_col);

	std::vector<std::vector<MCParticle*> > origin_source;
	origin_source=ToolSet::CRC::Get_MC_From_PFO_Vec(pfo,navPFOToMC);

	//info.data_variable_vec.Get_PFOParticles_Information( pfo);

	return(1);
}



