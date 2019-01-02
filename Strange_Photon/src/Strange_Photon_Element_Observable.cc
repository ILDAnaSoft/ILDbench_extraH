#include "Strange_Photon_Element_Observable.h"
void Strange_Photon_Global_Counter::Fill_Data(TTree* tree){
	tree->Branch( "total_event_number", &nevt,"total_event_number"     );
	tree->Branch( "total_pass_mc", &pass_mc,"total_pass_mc"     );
	tree->Branch( "total_pass_pfo", &pass_pfo,"total_pass_pfo"     );
	tree->Branch( "total_pass_all", &pass_all,"total_pass_all"     );
}

void Strange_Photon_Single_Counter::Fill_Data(TTree* tree){
	tree->Branch( "event_number", &nevt,"event_number"     );
	tree->Branch( "run_number", &nrun,"run_number"     );
	tree->Branch( "weight", &weight,"weight"     );
	tree->Branch( "pass_mc", &pass_mc,"pass_mc"     );
	tree->Branch( "pass_pfo", &pass_pfo,"pass_pfo"     );
	tree->Branch( "pass_all", &pass_all,"pass_all"     );
}

void Strange_Photon_Counter::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pass_all").c_str()     , &pass_all,(prefix+"_pass_all").c_str()     );
}


void Strange_Photon_Observable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_visible_energy").c_str()     , &visible_energy,(prefix+"_visible_energy").c_str()     );
}

void Strange_Photon_Variable::Get_MCParticle_Information( MCParticle* input) {
	pdg      =input->getPDG();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void Strange_Photon_Variable::Get_PFOParticle_Information( ReconstructedParticle* input) {
	pdg      =input->getType();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void Strange_Photon_Variable_Vec::Get_MCParticles_Information( std::vector<MCParticle*> input) {
	for(unsigned int i=0;i<input.size();i++){
		pdg      .push_back(input[i]->getPDG());
		p        .push_back(ToolSet::CMC::Cal_P(input[i]));
		pt       .push_back(ToolSet::CMC::Cal_PT(input[i]));
		costheta .push_back(ToolSet::CMC::Cal_CosTheta(input[i]));
		phi      .push_back(ToolSet::CMC::Cal_Azimuth(input[i]));
		e        .push_back(input[i]->getEnergy());
		mass     .push_back(input[i]->getMass());
		endpointx.push_back(input[i]->getEndpoint()[0]);
		endpointy.push_back(input[i]->getEndpoint()[1]);
		endpointz.push_back(input[i]->getEndpoint()[2]);
		endpointr.push_back(std::sqrt(std::pow(input[i]->getEndpoint()[0],2)+std::pow(input[i]->getEndpoint()[1],2)));
		vertexx.push_back(input[i]->getVertex()[0]);
		vertexy.push_back(input[i]->getVertex()[1]);
		vertexz.push_back(input[i]->getVertex()[2]);
		vertexr.push_back(std::sqrt(std::pow(input[i]->getVertex()[0],2)+std::pow(input[i]->getVertex()[1],2)));
	}
	return ;
}


void Strange_Photon_Variable_Vec::Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) {
	// energy
	for(unsigned int i=0;i<input.size();i++){
		pdg      .push_back(input[i]->getType());
		p        .push_back(ToolSet::CMC::Cal_P(input[i]));
		pt       .push_back(ToolSet::CMC::Cal_PT(input[i]));
		costheta .push_back(ToolSet::CMC::Cal_CosTheta(input[i]));
		phi      .push_back(ToolSet::CMC::Cal_Azimuth(input[i]));
		e        .push_back(input[i]->getEnergy());
		mass     .push_back(input[i]->getMass());
	}

	return ;
}


void Strange_Photon_Variable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg").c_str()     , &pdg     ,(prefix+"_pdg").c_str()     );
	tree->Branch( (prefix+"_p").c_str()       , &p       ,(prefix+"_p").c_str()       );
	tree->Branch( (prefix+"_pt").c_str()      , &pt      ,(prefix+"_pt").c_str()      );
	tree->Branch( (prefix+"_costheta").c_str(), &costheta,(prefix+"_costheta").c_str());
	tree->Branch( (prefix+"_phi").c_str()     , &phi     ,(prefix+"_phi").c_str()     );
	tree->Branch( (prefix+"_e").c_str()       , &e       ,(prefix+"_e").c_str()       );
	tree->Branch( (prefix+"_mass").c_str()    , &mass    ,(prefix+"_mass").c_str()    );
}

void Strange_Photon_Variable_Vec::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg_vec")          .c_str()  , &pdg          );
	tree->Branch( (prefix+"_p_vec")            .c_str()  , &p            );
	tree->Branch( (prefix+"_pt_vec")           .c_str()  , &pt           );
	tree->Branch( (prefix+"_costheta_vec")     .c_str()  , &costheta     );
	tree->Branch( (prefix+"_phi_vec")          .c_str()  , &phi          );
	tree->Branch( (prefix+"_e_vec")            .c_str()  , &e            );
	tree->Branch( (prefix+"_mass_vec")         .c_str()  , &mass         );
	tree->Branch( (prefix+"_endpointr"          ).c_str(), &endpointr            );
	tree->Branch( (prefix+"_endpointx"          ).c_str(), &endpointx            );
	tree->Branch( (prefix+"_endpointy"          ).c_str(), &endpointy            );
	tree->Branch( (prefix+"_endpointz"          ).c_str(), &endpointz            );
	tree->Branch( (prefix+"_vertexr"          ).c_str(), &vertexr            );
	tree->Branch( (prefix+"_vertexx"          ).c_str(), &vertexx            );
	tree->Branch( (prefix+"_vertexy"          ).c_str(), &vertexy            );
	tree->Branch( (prefix+"_vertexz"          ).c_str(), &vertexz            );
}

