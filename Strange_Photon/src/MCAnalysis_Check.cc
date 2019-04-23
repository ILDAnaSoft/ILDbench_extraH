#include "Strange_Photon.h"
#include "CMC.h"
using namespace lcio;

int Strange_Photon::analyseMCParticle_Check( LCCollection* Input_MCsPhotonCol, LCCollection* Input_MCsWoPhotonCol, 
		LCCollection* Input_PFOPhotonCol, LCCollection* Input_PFOWoPhotonCol, 
		LCRelationNavigator* navMCToPFO,  LCRelationNavigator* navPFOToMC, 
		Strange_Photon_Information&info, Strange_Photon_Function_Counter& counter) {




	//declare input vector
	std::vector<MCParticle*>            input_mcs_photon   =ToolSet::CMC::Get_MCParticle(Input_MCsPhotonCol);
	std::vector<MCParticle*>            input_mcs_wophoton =ToolSet::CMC::Get_MCParticle(Input_MCsWoPhotonCol);
	std::vector<ReconstructedParticle*> input_pfo          =ToolSet::CRC::Get_POParticle(Input_PFOPhotonCol);
	std::vector<ReconstructedParticle*> input_pfo_photon   =ToolSet::CRC::Get_POParticleType(input_pfo,22);
	std::vector<ReconstructedParticle*> input_pfo_wophoton =ToolSet::CRC::Get_POParticle(Input_PFOWoPhotonCol);

	for(int i=0;i<input_pfo_photon.size();i++){
		float ecal_i=0, hcal_i=0, yoke_i=0, lumical_i=0,lhcal_i=0,beamcal_i=0;
		std::vector<lcio::Cluster*> clusters = input_pfo_photon[i]->getClusters();
		int counter=0;
		for ( std::vector<lcio::Cluster*>::const_iterator iCluster=clusters.begin();
				iCluster!=clusters.end();
				++iCluster) {
			//			ToolSet::ShowMessage(1,"cluster",counter);
			counter++;
			ecal_i    += (*iCluster)->getSubdetectorEnergies()[0];
			hcal_i    += (*iCluster)->getSubdetectorEnergies()[1];
			yoke_i    += (*iCluster)->getSubdetectorEnergies()[2];
			lumical_i += (*iCluster)->getSubdetectorEnergies()[3];
			lhcal_i   += (*iCluster)->getSubdetectorEnergies()[4];
			beamcal_i += (*iCluster)->getSubdetectorEnergies()[5];
		}
	//	if(lumical_i>input_pfo_photon[i]->getEnergy()){
////		ToolSet::ShowMessage(1,"lumical > pfo energy",input_pfo_photon[i]);
////		ToolSet::ShowMessage(1,"lumical",lumical_i);
////		ToolSet::ShowMessage(1,"photon",input_pfo_photon);
////		ToolSet::ShowMessage(1,"ecal",ecal_i);
////		ToolSet::ShowMessage(1,"hcal",hcal_i);
////		ToolSet::ShowMessage(1,"yoke",yoke_i);
////		ToolSet::ShowMessage(1,"lhcal",lhcal_i);
////		ToolSet::ShowMessage(1,"beamcal",beamcal_i);
	//	}
	}

	//declare output vector
	std::vector<ReconstructedParticle*>      PFOLostEnergyPhoton;
	std::vector<ReconstructedParticle*>      PFOLostEnergyPhoton_Combined;

	std::vector<MCParticle*>                 MCsLostEnergyPhoton;


	for(int i=0;i<input_pfo.size();i++){
		_pnum++;
	}

	// if has mcs isolated photon,  check whether having lost energy photon
	ToolSet::CChain_Vec       _chain ;
	_chain.Set_ChainVec_FromRCFS(input_pfo_photon,navPFOToMC);
	std::vector<ReconstructedParticle*>    chain_input     =_chain.Get_RCInput()   ;
	std::vector<std::vector<MCParticle*> > chain_head      =_chain.Get_MCHead()    ;
	std::vector<std::vector<MCParticle*> > chain_end       =_chain.Get_MCEnd()     ;
	std::vector<std::vector<MCParticle*> > chain_fromrc_mc =_chain.Get_FromRC_MC() ;
	std::vector<std::vector<MCParticle*> > chain_end_py    =_chain.Get_MCEnd_PYFS();

	std::vector<MCParticle*>               chain_mc_de      ;
	std::vector<MCParticle*>               chain_mc_py      ;
	std::vector<MCParticle*>               chain_mc_de_other;
	std::vector<MCParticle*>               chain_mc_py_other;
	std::vector<MCParticle*>               chain_mc_hs      ;


	for(int i=0;i<_chain.Num();i++){

		MCParticle* linked_mc_hs_photon;
		float mc_hs_max_energy=0;
		int   mc_hs_max_pos=-1;
		for(int j=0;j<chain_head[i].size();j++){
			float this_energy=chain_head[i][j]->getEnergy();
			if(this_energy>mc_hs_max_energy){
				mc_hs_max_pos=j;
				mc_hs_max_energy=this_energy;
			}
		}
		if(mc_hs_max_pos!=-1){
			linked_mc_hs_photon=chain_head[i][mc_hs_max_pos];
			chain_mc_hs.push_back(linked_mc_hs_photon);
			info.pfo_check.obv.energy_difference.push_back(chain_input[i]->getEnergy()-linked_mc_hs_photon->getEnergy());


			if(chain_head[i][mc_hs_max_pos]->isOverlay()){
				info.pfo_check.obv.photon_head.push_back(-22);
			}
			else{
				info.pfo_check.obv.photon_head.push_back(chain_head[i][mc_hs_max_pos]->getPDG());
			}
		}



		std::vector<MCParticle*>   chain_end_de_photon =ToolSet::CMC::Get_MCParticleType(chain_fromrc_mc[i],22);
		std::vector<MCParticle*>   chain_end_de_other  =chain_fromrc_mc[i]-chain_end_de_photon;
		MCParticle* linked_mc_de_photon;
		float mc_de_max_energy=0;
		int   mc_de_max_pos=-1;
		for(int j=0;j<chain_end_de_photon.size();j++){
			float this_energy=chain_end_de_photon[j]->getEnergy();
			if(this_energy>mc_de_max_energy){
				mc_de_max_pos=j;
				mc_de_max_energy=this_energy;
			}
		}
		if(mc_de_max_pos!=-1){
			linked_mc_de_photon=chain_end_de_photon[mc_de_max_pos];
			chain_mc_de.push_back(linked_mc_de_photon);
			info.mcs_check_de.obv.energy_difference.push_back(chain_input[i]->getEnergy()-linked_mc_de_photon->getEnergy());
		}
		else{
			MCParticle* linked_mc_de_other;
			float mc_de_max_energy_other=0;
			int   mc_de_max_pos_other=-1;
			for(int j=0;j<chain_end_de_other.size();j++){
				float this_energy=chain_end_de_other[j]->getEnergy();
				if(this_energy>mc_de_max_energy_other){
					mc_de_max_pos_other=j;
					mc_de_max_energy_other=this_energy;
				}
			}
			if(mc_de_max_pos_other!=-1){
				linked_mc_de_other=chain_end_de_other[mc_de_max_pos_other];
				chain_mc_de_other.push_back(linked_mc_de_other);
				info.mcs_check_de_other.obv.energy_difference.push_back(chain_input[i]->getEnergy()-linked_mc_de_other->getEnergy());
			}
		}




		std::vector<MCParticle*>   chain_end_py_photon =ToolSet::CMC::Get_MCParticleType(chain_end_py[i],22);
		std::vector<MCParticle*>   chain_end_py_other  =chain_end_py[i]-chain_end_py_photon;
		MCParticle* mc_end_photon;
		float mc_end_max_energy=0;
		int   mc_end_max_pos=-1;
		for(int j=0;j<chain_end_py_photon.size();j++){
			float this_energy=chain_end_py_photon[j]->getEnergy();
			if(this_energy>mc_end_max_energy){
				mc_end_max_pos=j;
				mc_end_max_energy=this_energy;
			}
		}
		if(mc_end_max_pos!=-1){
			mc_end_photon=chain_end_py_photon[mc_end_max_pos];
			chain_mc_py.push_back(mc_end_photon);
			info.mcs_check_py.obv.energy_difference.push_back(chain_input[i]->getEnergy()-mc_end_photon->getEnergy());
		}
		else{
			MCParticle* linked_mc_py_other;
			float mc_py_max_energy_other=0;
			int   mc_py_max_pos_other=-1;
			for(int j=0;j<chain_end_py_other.size();j++){
				float this_energy=chain_end_py_other[j]->getEnergy();
				if(this_energy>mc_py_max_energy_other){
					mc_py_max_pos_other=j;
					mc_py_max_energy_other=this_energy;
				}
			}
			if(mc_py_max_pos_other!=-1){
				linked_mc_py_other=chain_end_py_other[mc_py_max_pos_other];
				chain_mc_py_other.push_back(linked_mc_py_other);
				info.mcs_check_py_other.obv.energy_difference.push_back(chain_input[i]->getEnergy()-linked_mc_py_other->getEnergy());
			}
		}
	}

////ToolSet::ShowMessage(1,"input photon difference py",info.mcs_check_py.obv.energy_difference);
////ToolSet::ShowMessage(1,"input photon difference de",info.mcs_check_de.obv.energy_difference);

	info.pfo_check.Get_PFOParticles(chain_input);
	info.mcs_check_de.Get_MCParticles(chain_mc_de);
	info.mcs_check_py.Get_MCParticles(chain_mc_py);
	info.mcs_check_de_other.Get_MCParticles(chain_mc_de_other);
	info.mcs_check_py_other.Get_MCParticles(chain_mc_py_other);
	// finish
	return(1);

}




