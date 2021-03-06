#include "Minimal_Processor.h"
#include "CMC.h"
using namespace lcio;

bool Minimal_Processor::analyseMCParticle( LCCollection* Allmc,  LCRelationNavigator* navMCToPFO,  Minimal_Processor_Information_Single &info, Minimal_Processor_Function_Counter& counter) {
	//generate all basic sorts 
    std::vector<MCParticle*> MCs          =ToolSet::CMC::Get_MCParticle(Allmc);

    std::vector<MCParticle*> hs_FS        =ToolSet::CMC::Get_MC_HardScattering_FS(MCs);

    std::vector<MCParticle*> hs_higgs     =ToolSet::CMC::Get_MCParticleType(hs_FS,25);

    info.Get_MCParticles(hs_FS);

	counter.pass_all++;
	return(true);
}




