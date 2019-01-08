#include "Minimal_Processor_Element_Observable.h"
void Minimal_Processor_Global_Counter::Fill_Data(TTree* tree){
	tree->Branch( "total_event_number"             , &nevt                     ,"total_event_number"              );
	tree->Branch( "total_run_number"               , &nrun                     ,"total_run_number"                );
	tree->Branch( "total_scale_factor"             , &gweight                  ,"total_scale_factor"              );
	tree->Branch( "total_pass_MCs"                 , &pass_MCs                 ,"total_pass_MCs"                  );
	tree->Branch( "total_pass_all"                 , &pass_all                 ,"total_pass_all"                  );
}

void Minimal_Processor_Single_Counter::Fill_Data(TTree* tree){
	tree->Branch( "event_number"             , &evt                      ,"event_number"              );
	tree->Branch( "run_number"               , &run                      ,"run_number"                );
	tree->Branch( "scale_factor"             , &weight                   ,"scale_factor"              );
	tree->Branch( "pass_MCs"                 , &pass_MCs                 ,"pass_MCs"                  );
	tree->Branch( "pass_all"                 , &pass_all                 ,"pass_all"                  );
}


void Minimal_Processor_Function_Counter::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pass_all").c_str()     , &pass_all,(prefix+"_pass_all").c_str()  );
}

void Minimal_Processor_Observable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_visible_energy").c_str()     , &visible_energy,(prefix+"_visible_energy").c_str()     );
	tree->Branch( (prefix+"_invisible_energy").c_str()   , &invisible_energy,(prefix+"_invisible_energy").c_str()   );
}

void Minimal_Processor_Variable::Get_MCParticle_Information( MCParticle* input) {
	pdg      =input->getPDG();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void Minimal_Processor_Variable::Get_PFOParticle_Information( ReconstructedParticle* input) {
	pdg      =input->getType();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void Minimal_Processor_Variable_Vec::Get_MCParticles_Information( std::vector<MCParticle*> input) {
	for(unsigned int i=0;i<input.size();i++){
		pdg      .push_back(input[i]->getPDG());
		p        .push_back(ToolSet::CMC::Cal_P(input[i]));
		pt       .push_back(ToolSet::CMC::Cal_PT(input[i]));
		costheta .push_back(ToolSet::CMC::Cal_CosTheta(input[i]));
		phi      .push_back(ToolSet::CMC::Cal_Azimuth(input[i]));
		e        .push_back(input[i]->getEnergy());
		mass     .push_back(input[i]->getMass());
	}
	return ;
}


void Minimal_Processor_Variable_Vec::Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) {
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


void Minimal_Processor_Variable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg").c_str()     , &pdg     ,(prefix+"_pdg").c_str()     );
	tree->Branch( (prefix+"_p").c_str()       , &p       ,(prefix+"_p").c_str()       );
	tree->Branch( (prefix+"_pt").c_str()      , &pt      ,(prefix+"_pt").c_str()      );
	tree->Branch( (prefix+"_costheta").c_str(), &costheta,(prefix+"_costheta").c_str());
	tree->Branch( (prefix+"_phi").c_str()     , &phi     ,(prefix+"_phi").c_str()     );
	tree->Branch( (prefix+"_e").c_str()       , &e       ,(prefix+"_e").c_str()       );
	tree->Branch( (prefix+"_mass").c_str()    , &mass    ,(prefix+"_mass").c_str()    );
}

void Minimal_Processor_Variable_Vec::Fill_Data(TTree* tree, std::string prefix){
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


void Minimal_Processor_Number::Get_MCParticles_Number( std::vector<MCParticle*> input) {
	num=input.size();
	for(unsigned int i=0;i<input.size();i++){
		if(input[i]->getCharge()>0){
			num_plus++;
		}
		else if(input[i]->getCharge()<0){
			num_minus++;
		}
		else{
			num_neutral++;
		}
		if(std::abs(ToolSet::CMC::Cal_CosTheta(input[i]))<0.95){
			num_central++;
		}
		else{
			num_forward++;
		}
	}
	return ;
}


void Minimal_Processor_Number::Get_PFOParticles_Number( std::vector<ReconstructedParticle*> input) {
	num=input.size();
	for(unsigned int i=0;i<input.size();i++){
		if(input[i]->getCharge()>0){
			num_plus++;
		}
		else if(input[i]->getCharge()<0){
			num_minus++;
		}
		else{
			num_neutral++;
		}
		if(std::abs(ToolSet::CMC::Cal_CosTheta(input[i]))<0.95){
			num_central++;
		}
		else{
			num_forward++;
		}
	}
	return ;
}

void Minimal_Processor_Number::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"num"            ).c_str()    , &num        ,(prefix+"num"            ).c_str()        );
	tree->Branch( (prefix+"num_plus"       ).c_str()    , &num_plus   ,(prefix+"num_plus"       ).c_str()        );
	tree->Branch( (prefix+"num_minus"      ).c_str()    , &num_minus  ,(prefix+"num_minus"      ).c_str()        );
	tree->Branch( (prefix+"num_neutral"    ).c_str()    , &num_neutral,(prefix+"num_neutral"    ).c_str()        );
	tree->Branch( (prefix+"num_central"    ).c_str()    , &num_central,(prefix+"num_central"    ).c_str()        );
	tree->Branch( (prefix+"num_forward"    ).c_str()    , &num_forward,(prefix+"num_forward"    ).c_str()        );
}

void Minimal_Processor_Information_Single::Get_MCParticles( std::vector<MCParticle*> input) {
	particle.Get_MCParticles_Information(input);
	num_particle.Get_MCParticles_Number(input);
}

void Minimal_Processor_Information_Single::Get_PFOParticles( std::vector<ReconstructedParticle*> input) {
	particle.Get_PFOParticles_Information(input);
	num_particle.Get_PFOParticles_Number(input);
}

void Minimal_Processor_Information_Single::Fill_Data(TTree* tree, std::string prefix){
	obv         .Fill_Data(tree,prefix+"_obv");
	particle    .Fill_Data(tree,prefix+"_particle");
	num_particle.Fill_Data(tree,prefix+"_num_particle");
}

