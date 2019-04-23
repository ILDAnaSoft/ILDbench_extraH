#include "Strange_Lepton.h"
#include "CMC.h"
using namespace lcio;

int Strange_Lepton::analyseMCParticle( LCCollection* Input_MCsLeptonCol,  LCCollection* Input_PFOLeptonCol, 
		Strange_Lepton_Output_Collection& NewPFOIsoLeptonCol, 
		LCRelationNavigator* navMCToPFO,  LCRelationNavigator* navPFOToMC, 
		Strange_Lepton_Information&info, Strange_Lepton_Function_Counter& counter) {


	std::vector<MCParticle*>            input_mcs_lepton =ToolSet::CMC::Get_MCParticle(Input_MCsLeptonCol);
	std::vector<ReconstructedParticle*> input_pfo_lepton =ToolSet::CRC::Get_POParticle(Input_PFOLeptonCol);


	std::vector<ReconstructedParticle*> output_pfo_lepton;

    ToolSet::CChain_Vec       _chain ;
    _chain.Set_ChainVec_FromRCFS(input_pfo_lepton,navPFOToMC);
    std::vector<MCParticle*>    chain_mc_from_rc=_chain.Get_FromRC_WeightedMC();

	ReconstructedParticle* test;
	std::vector<ReconstructedParticle*> NewPFOIsoLepton = ToolSet::CRC::NewParticles(chain_mc_from_rc,test);


    //vertex information
//  if( input_pfo_lepton.size()>1 ){
//  	if(Get_Best_Pair(NewPFOIsoLepton,output_pfo_lepton)){
//  		EVENT::Track* lep1=0,  *lep2=0; 
//  		EVENT::TrackVec trkvec1 = output_pfo_lepton[0]->getTracks();
//  		EVENT::TrackVec trkvec2 = output_pfo_lepton[1]->getTracks();
//  		if((trkvec1.size()>0)&&(trkvec2.size()>0)){
//  			lep1=trkvec1[0];
//  			lep2=trkvec2[0];

//  			VertexInfo vv;
//  			vv.addTrack( lep1 );
//  			vv.addTrack( lep2 );
//  			//beam spot constraint
//  			float xyz[3] = { 150e-6, 5e-6, 0.2  }; //mm
//  			vv.setBeamSpotSize( xyz  );
//  			vv.useIPcon( true  );

//  			TVector3 vtxPos = vv.getVertexPosition();
//  			float vtx = vtxPos[0];
//  			float vty = vtxPos[1];
//  			float vtz = vtxPos[2];
//  			float chi2 = vv.getVertexChisq();
//  			info.output_pfo_lepton.obv.Get_Vertex_Information(vv);

//  		////int HS_muon_num=0;
//  		////for(int i=0;i<input_mcs_lepton.size();i++){
//  		////	if(std::abs(input_mcs_lepton[i]->getPDG())==13){
//  		////		HS_muon_num++;
//  		////	}
//  		////}
//  		////if(HS_muon_num!=2){
//  		////	ToolSet::ShowMessage(1,"vtx",vtx,vty,vtz,chi2);
//  		////	ToolSet::ShowMessage(1,"no 2 muon",input_mcs_lepton);
//  		////}
//  		}
//  	}
//  }
//


	//ToolSet::ShowMessage(1,"mcs",input_mcs_lepton);

	info.input_mcs_lepton.Get_MCParticles(input_mcs_lepton);
	info.input_pfo_lepton.Get_PFOParticles(input_pfo_lepton);
	info.output_pfo_lepton.Get_PFOParticles(NewPFOIsoLepton);

////std::vector<std::vector<MCParticle*> > chain_head=_chain.Get_MCHead();
////std::vector<std::vector<MCParticle*> > chain_end =_chain.Get_MCEnd();

	////for(int i=0;i<_chain.Num();i++){
	////	if(chain_head[i].size()>0){
	////		if(std::abs(chain_head[i][0]->getPDG())!=13){
	////			ToolSet::ShowMessage(1,"begin not muon head",_nEvt,i);
	////			ToolSet::ShowMessage(1,"rc",i, chain_input[i]);
	////			ToolSet::ShowMessage(1,"mchead",chain_head[i]);
	////			ToolSet::ShowMessage(1,"mcend",chain_end[i]);
	////		}
	////	}
	////}

	//add into output collections

	NewPFOIsoLeptonCol              .Add_Element_RCParticle(NewPFOIsoLepton);


	return(1);

}




bool Strange_Lepton::Get_Best_Pair(std::vector<ReconstructedParticle*> in, std::vector<ReconstructedParticle*> &out) {
	int num=in.size();

	std::vector<TLorentzVector> inVector;
	for(int i=0;i<num;i++){
		TLorentzVector in_tmp= TLorentzVector( in[i]->getMomentum(), in[i]->getEnergy() );
		inVector.push_back(in_tmp);
	}

	float chi_min= 1000000.0;
	float chi_tmp=chi_min;
	float pair_mass_final = 999.99;

	TLorentzVector pair_mom;

	int choosei=1000,choosej=1000;
	for(int i=0;i<num-1;i++){
		for(int j=1;j<num;j++){
			pair_mom = inVector[i]+inVector[j];
			if(std::abs(pair_mom.M()-91.187)>40.0){
				continue;
			}
			if((in[i]->getCharge())*(in[j]->getCharge())>0){//Should be different sign lepton
				continue;
			}
			float  pair_mass=pair_mom.M();
			float  sigma_pair=1;

			chi_tmp = std::pow((pair_mass-91.187)/sigma_pair,2);

			if(chi_tmp<chi_min){
				chi_min = chi_tmp;
				choosei=i;
				choosej=j;
				pair_mass_final=pair_mass;
			}
		}
	}

	if(choosei!=1000 && choosej!=1000){
		if(in[choosei]->getCharge()>0){
			out.push_back(in[choosei]);
			out.push_back(in[choosej]);
		}
		else{
			out.push_back(in[choosej]);
			out.push_back(in[choosei]);
		}
		return(true);
	}
	return(false);
}


