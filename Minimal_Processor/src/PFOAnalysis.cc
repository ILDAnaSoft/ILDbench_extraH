#include "Minimal_Processor.h"

bool Minimal_Processor::analysePFOParticle(LCCollection* PFOs_col, Minimal_Processor_Output_Collection& outputPFOCol, LCRelationNavigator* navPFOToMC, Minimal_Processor_Information_Single &info, Minimal_Processor_Function_Counter& counter){

    //data prepared
	std::vector<ReconstructedParticle*> pfo = ToolSet::CRC::Get_POParticle(PFOs_col);

	std::vector<std::vector<MCParticle*> > origin_source;
	origin_source= ToolSet::CRC::Get_MC_From_PFO_Vec(pfo,navPFOToMC);


	//data recorded
	outputPFOCol.Add_Element_RCParticle(pfo);

	info.Get_PFOParticles(pfo);

	counter.pass_all++ ;
	return(true);
}



