#include "MCLevelClassify.h"


bool MCLevelClassify::analyseMCParticle( LCCollection* inputmcCol, MCLevelClassify_Output_Collection& outputHSCol,MCLevelClassify_Output_Collection& outputPSCol, MCLevelClassify_Output_Collection& outputDSCol, MCLevelClassify_Information& info, MCLevelClassify_Function_Counter &counter){
	std::vector<MCParticle*> MCs =ToolSet::CMC::Get_MCParticle(inputmcCol);
	std::vector<MCParticle*> HS  =ToolSet::CMC::Get_MC_HardScattering_FS(MCs);
	std::vector<MCParticle*> PS  =ToolSet::CMC::Get_MC_PythiaShowering_FS(MCs);
	std::vector<MCParticle*> DS  =ToolSet::CMC::Get_MC_DetectorSimulating_FS(MCs);

    std::vector<MCParticle*> HS_wo_overlay=ToolSet::CMC::Get_Visible(HS);
    std::vector<MCParticle*> PS_wo_overlay=ToolSet::CMC::Get_Visible(PS);
    std::vector<MCParticle*> DS_wo_overlay=ToolSet::CMC::Get_Visible(DS);

	outputHSCol.Add_Element_MCParticle(HS_wo_overlay);
	outputPSCol.Add_Element_MCParticle(PS_wo_overlay);
	outputDSCol.Add_Element_MCParticle(DS_wo_overlay);

	if(_output_switch_root){
		info.HS_info.Get_MCParticles(HS);
		info.PS_info.Get_MCParticles(PS);
		info.DS_info.Get_MCParticles(DS);
	}

	return(true);

}


