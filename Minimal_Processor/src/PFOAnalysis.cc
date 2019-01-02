#include "Minimal_Processor.h"
#include "CRC.h"


bool Minimal_Processor::analysePFOParticle(LCCollection* PFOs_col, LCRelationNavigator* navPFOToMC, Minimal_Processor_Information &info, Minimal_Processor_Counter& counter){

	std::vector<ReconstructedParticle*> pfo = ToolSet::CRC::Get_POParticle(PFOs_col);

	std::vector<std::vector<MCParticle*> > origin_source;
	origin_source= ToolSet::CRC::Get_MC_From_PFO_Vec(pfo,navPFOToMC);

	info.data_variable_vec.Get_PFOParticles_Information( pfo);

	counter.pass_all++ ;
	return(true);
}



