#include "Strange_Lepton.h"
#include "CMC.h"
using namespace lcio;

int Strange_Lepton::analyseMCParticle( LCCollection* Input_MCsLeptonCol, 
		Strange_Lepton_Output_Collection& NewPFOIsoLeptonCol, 
		Strange_Lepton_Information&info, Strange_Lepton_Function_Counter& counter) {


	std::vector<MCParticle*>            input_mcs_lepton =ToolSet::CMC::Get_MCParticle(Input_MCsLeptonCol);
	ReconstructedParticle* test;
    std::vector<ReconstructedParticle*> NewPFOIsoLepton = ToolSet::CRC::NewParticles(input_mcs_lepton,test);



	//add into output collections
	NewPFOIsoLeptonCol              .Add_Element_RCParticle(NewPFOIsoLepton);



    info.pfo_lepton .Get_PFOParticles(NewPFOIsoLepton);

	return(1);

}




