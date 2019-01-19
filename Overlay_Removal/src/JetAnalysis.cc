#include "Overlay_Removal.h"
#include "CRC.h"


bool Overlay_Removal::analyseJet( LCCollection* PFOCol, LCCollection* IsolepCol, LCCollection* Jet_POs_col, Overlay_Removal_Output_Collection& PFOWoOverlayCol, Overlay_Removal_Output_Collection& PFOOverlayCol,  Overlay_Removal_Information_Single &info_wo_overlay,  Overlay_Removal_Information_Single &info_overlay){

	std::vector<ReconstructedParticle*> FS          = ToolSet::CRC::Get_POParticle(PFOCol);
	std::vector<ReconstructedParticle*> isl         = ToolSet::CRC::Get_POParticle(IsolepCol);
	std::vector<ReconstructedParticle*> jet_POs_col = ToolSet::CRC::Get_POParticle(Jet_POs_col);

	std::vector<ReconstructedParticle*> po_wo_overlay = jet_POs_col + isl;
	std::vector<ReconstructedParticle*> po_overlay    = FS-po_wo_overlay;

	info_wo_overlay.Get_PFOParticles(po_wo_overlay);
	info_overlay   .Get_PFOParticles(po_overlay);

	PFOWoOverlayCol.Add_Element_RCParticle(po_wo_overlay);
	PFOOverlayCol  .Add_Element_RCParticle(po_overlay);

	return(true);
}


