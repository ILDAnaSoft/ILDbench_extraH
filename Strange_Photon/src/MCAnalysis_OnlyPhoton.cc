#include "Strange_Photon.h"
#include "CMC.h"
using namespace lcio;

int Strange_Photon::analyseMCParticle_OnlyPhoton( LCCollection* Input_MCsPhotonCol, LCCollection* Input_MCsWoPhotonCol, 
		LCCollection* Input_PFOPhotonCol, LCCollection* Input_PFOWoPhotonCol, 
		Strange_Photon_Output_Collection& PFOLostEnergyPhoton_RCOnlyCol, 
		Strange_Photon_Output_Collection& NewPFOIsoPhotonCol, Strange_Photon_Output_Collection& NewPFORemovedIsoPhotonCol, 
		LCRelationNavigator* navMCToPFO,  LCRelationNavigator* navPFOToMC, 
		Strange_Photon_Information&info, Strange_Photon_Function_Counter& counter) {




	//declare input vector
	std::vector<MCParticle*>            input_mcs_photon   =ToolSet::CMC::Get_MCParticle(Input_MCsPhotonCol);
	std::vector<MCParticle*>            input_mcs_wophoton =ToolSet::CMC::Get_MCParticle(Input_MCsWoPhotonCol);
	std::vector<ReconstructedParticle*> input_pfo_photon   =ToolSet::CRC::Get_POParticle(Input_PFOPhotonCol);
	std::vector<ReconstructedParticle*> input_pfo_wophoton =ToolSet::CRC::Get_POParticle(Input_PFOWoPhotonCol);


	//declare output vector
	std::vector<ReconstructedParticle*>      NewPFOIsoPhoton;
	std::vector<ReconstructedParticle*>      NewPFORemovedIsoPhoton;

	std::vector<ReconstructedParticle*>      PFOLostEnergyPhoton;
	std::vector<ReconstructedParticle*>      PFOLostEnergyPhoton_RCOnly;

	std::vector<MCParticle*>                 MCsLostEnergyPhoton;



	// if no mcs isolated photon,  then don't need corrections for pandora photon, nothing happens.
	if(input_mcs_photon.size()==0){

		//prepare data 
		NewPFOIsoPhoton          = input_pfo_photon; 
		NewPFORemovedIsoPhoton   = input_pfo_wophoton; 


		//prepare collections
		// completely same with input pfo photon and wo_photon 
		NewPFOIsoPhotonCol       .Add_Element_RCParticle(NewPFOIsoPhoton);
		NewPFORemovedIsoPhotonCol.Add_Element_RCParticle(NewPFORemovedIsoPhoton);

		// no lost energy photon, so no elements here
		NewPFOIsoPhotonCol              .Add_Element_RCParticle(NewPFOIsoPhoton);
		NewPFORemovedIsoPhotonCol       .Add_Element_RCParticle(NewPFORemovedIsoPhoton);
		PFOLostEnergyPhoton_RCOnlyCol   .Add_Element_RCParticle(PFOLostEnergyPhoton_RCOnly);
		return(0);
	}


	// if has mcs isolated photon,  check whether having lost energy photon
	ToolSet::CChain_Vec       _photon_chain ;
	_photon_chain.Set_ChainVec(input_mcs_photon,navMCToPFO,navPFOToMC);



	bool has_lost_energy_photon=false;
	for(unsigned int i=0;i<_photon_chain.Num();i++){
		MCParticle*                          original_mc= _photon_chain.Get_MCInput()[i];
		float                                mc_energy  = original_mc->getEnergy();
		std::vector<ReconstructedParticle*>  rc_photon_vec= _photon_chain.Get_WeightedRC(22)[i];

		float pfo_energy=0;
		int   max_num=-1;
        for(unsigned int i=0;i<rc_photon_vec.size();i++){
        	float energy=rc_photon_vec[i]->getEnergy();
        	if(energy>pfo_energy){
        		pfo_energy=energy;
        		max_num=i;
        	}
        }

        ReconstructedParticle*  rc_photon=NULL;
        if(max_num>-1){
        	rc_photon=rc_photon_vec[max_num];
        }

        std::vector<ReconstructedParticle*>  related_rc = _photon_chain.Get_Flat_RC()[i];

        if(std::abs(mc_energy-pfo_energy)/mc_energy>_minEnergyDifferenceRatio){
        	// store data
        	//info.photon.Get_MCParticles_Information(_photon_chain.Get_FromRC_MC()[i]);
        	info.mcs_lostenergy_photon.obv.visible_energy=mc_energy-pfo_energy;

        	//This includes all the particles coming from the mc photon, so it includes the constituents both in the input pfo photon and input pfo_wo_photon collections.
        	PFOLostEnergyPhoton+=related_rc;
			if(rc_photon!=NULL){
				PFOLostEnergyPhoton_RCOnly.push_back(rc_photon);
			}
        	MCsLostEnergyPhoton.push_back(original_mc);


        	has_lost_energy_photon=true;
        }
	}



	if(!has_lost_energy_photon){
		// still the same as the input
		//prepare data 
		NewPFOIsoPhoton          = input_pfo_photon; 
		NewPFORemovedIsoPhoton   = input_pfo_wophoton; 


		//prepare collections
		// completely same with input pfo photon and wo_photon 
		NewPFOIsoPhotonCol       .Add_Element_RCParticle(NewPFOIsoPhoton);
		NewPFORemovedIsoPhotonCol.Add_Element_RCParticle(NewPFORemovedIsoPhoton);

		PFOLostEnergyPhoton_RCOnlyCol   .Add_Element_RCParticle(PFOLostEnergyPhoton_RCOnly);
		return(0);
	}



    std::vector<ReconstructedParticle*> PFOLostEnergyPhoton_Left=ToolSet::Vec_Difference(input_pfo_photon,PFOLostEnergyPhoton);

    ReconstructedParticle* test;
    std::vector<ReconstructedParticle*> MCsLostEnergyPhoton_To_PFO = ToolSet::CRC::NewParticles(MCsLostEnergyPhoton,test);


    NewPFOIsoPhoton        = PFOLostEnergyPhoton_Left + MCsLostEnergyPhoton_To_PFO; 
    NewPFORemovedIsoPhoton = ToolSet::Vec_Difference(input_pfo_wophoton,PFOLostEnergyPhoton);


	//add into output collections
	NewPFOIsoPhotonCol              .Add_Element_RCParticle(NewPFOIsoPhoton);
	NewPFORemovedIsoPhotonCol       .Add_Element_RCParticle(NewPFORemovedIsoPhoton);
	PFOLostEnergyPhoton_RCOnlyCol   .Add_Element_RCParticle(PFOLostEnergyPhoton_RCOnly);


    info.pfo_photon_only               .Get_PFOParticles(NewPFOIsoPhoton);
    info.pfo_wophoton_only             .Get_PFOParticles(NewPFORemovedIsoPhoton);
    info.pfo_lostenergy_photon_rconly  .Get_PFOParticles(PFOLostEnergyPhoton_RCOnly);

	// finish
	return(1);

}




