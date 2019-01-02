#include "MCLevelClassify.h"


bool MCLevelClassify::analyseMCParticle( LCCollection* inputmcCol, LCCollectionVec* outputHSCol,LCCollectionVec* outputPSCol, LCCollectionVec* outputDSCol){
	std::vector<MCParticle*> MCs =ToolSet::CMC::Get_MCParticle(inputmcCol);
	std::vector<MCParticle*> HS  =ToolSet::CMC::Get_MC_HardScattering_FS(MCs);
	std::vector<MCParticle*> PS  =ToolSet::CMC::Get_MC_PythiaShowering_FS(MCs);
	std::vector<MCParticle*> DS  =ToolSet::CMC::Get_MC_DetectorSimulating_FS(MCs);

    for (int i = 0; i < HS.size(); i++ ) {
    	outputHSCol->addElement(HS[i]);
    }

    for (int i = 0; i < PS.size(); i++ ) {
    	outputPSCol->addElement(PS[i]);
    }

    for (int i = 0; i < DS.size(); i++ ) {
    	outputDSCol->addElement(DS[i]);
    }

}


