#include "Overlay_Removal.h"
#include "CMC.h"
using namespace lcio;

std::vector<MCParticle*> Overlay_Removal::analyseMCParticle( LCCollection* Allmc, Overlay_Removal_Information& info) {
	//generate all basic sorts 
    std::vector<MCParticle*> MCs          =ToolSet::CMC::Get_MCParticle(Allmc);

    std::vector<MCParticle*> de=ToolSet::CMC::Get_MC_DetectorSimulating_FS(MCs);
    std::vector<MCParticle*> MCs_wo_overlay=ToolSet::CMC::Get_Visible(de);

	info.data_wo_overlay           .Get_MCParticles_Information(MCs_wo_overlay);
	info.data_observable_wo_overlay.Get_MCParticles_Information(MCs_wo_overlay);

	return(MCs_wo_overlay);
}

