#include "Overlay_Removal.h"
#include "CRC.h"


std::vector<ReconstructedParticle*> Overlay_Removal::analyseJet( LCCollection* ISL,  LCCollection* Jet_POs_col, Overlay_Removal_Information &info){

	std::vector<ReconstructedParticle*> isl         = ToolSet::CRC::Get_POParticle(ISL);
	std::vector<ReconstructedParticle*> jet_POs_col = ToolSet::CRC::Get_POParticle(Jet_POs_col);

	std::vector<ReconstructedParticle*> po_wo_overlay = jet_POs_col + isl;

	info.data_wo_overlay           .Get_PFOParticles_Information(po_wo_overlay);

	info.data_observable_wo_overlay.Get_PFOParticles_Information(po_wo_overlay);

	return(po_wo_overlay);
}


