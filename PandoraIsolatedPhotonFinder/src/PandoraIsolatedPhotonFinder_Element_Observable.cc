#include "PandoraIsolatedPhotonFinder_Element_Observable.h"
void PandoraIsolatedPhotonFinder_Global_Counter::Fill_Data(TTree* tree){
	tree->Branch( "total_event_number"             , &nevt                     ,"total_event_number"              );
	tree->Branch( "total_run_number"               , &nrun                     ,"total_run_number"                );
	tree->Branch( "total_scale_factor"             , &gweight                  ,"total_scale_factor"              );
	tree->Branch( "total_pass_PFO"                 , &pass_PFO                 ,"total_pass_PFO"                  );
	tree->Branch( "total_pass_all"                 , &pass_all                 ,"total_pass_all"                  );
}

void PandoraIsolatedPhotonFinder_Single_Counter::Fill_Data(TTree* tree){
	tree->Branch( "event_number"             , &evt                      ,"event_number"              );
	tree->Branch( "run_number"               , &run                      ,"run_number"                );
	tree->Branch( "scale_factor"             , &weight                   ,"scale_factor"              );
	tree->Branch( "pass_PFO"                 , &pass_PFO                 ,"pass_PFO"                  );
	tree->Branch( "pass_all"                 , &pass_all                 ,"pass_all"                  );
}


void PandoraIsolatedPhotonFinder_Function_Counter::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pass_all").c_str()     , &pass_all,(prefix+"_pass_all").c_str()  );
}


void PandoraIsolatedPhotonFinder_Observable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_input_energy"      ).c_str(),        &input_energy             ,(prefix+"_input_energy").c_str()          );
	tree->Branch( (prefix+"_num_incone_total"  ).c_str(),        &num_incone_total         ,(prefix+"_num_incone_total").c_str()      );
	tree->Branch( (prefix+"_num_incone_charge" ).c_str(),        &num_incone_charge        ,(prefix+"_num_incone_charge").c_str()     );
	tree->Branch( (prefix+"_num_incone_neutral").c_str(),        &num_incone_neutral       ,(prefix+"_num_incone_neutral").c_str()    );
	tree->Branch( (prefix+"_num_incone_photon" ).c_str(),        &num_incone_photon        ,(prefix+"_num_incone_photon").c_str()     );
	tree->Branch( (prefix+"_num_incone_lepton" ).c_str(),        &num_incone_lepton        ,(prefix+"_num_incone_lepton").c_str()     );
	tree->Branch( (prefix+"_num_incone_hadron" ).c_str(),        &num_incone_hadron        ,(prefix+"_num_incone_hadron").c_str()     );

	tree->Branch( (prefix+"_cone_energy_total"  ).c_str(),       &cone_energy_total        ,(prefix+"_cone_energy_total").c_str()      );
	tree->Branch( (prefix+"_cone_energy_charge" ).c_str(),       &cone_energy_charge       ,(prefix+"_cone_energy_charge").c_str()     );
	tree->Branch( (prefix+"_cone_energy_neutral").c_str(),       &cone_energy_neutral      ,(prefix+"_cone_energy_neutral").c_str()    );
	tree->Branch( (prefix+"_cone_energy_photon" ).c_str(),       &cone_energy_photon       ,(prefix+"_cone_energy_photon").c_str()     );
	tree->Branch( (prefix+"_cone_energy_lepton" ).c_str(),       &cone_energy_lepton       ,(prefix+"_cone_energy_lepton").c_str()     );
	tree->Branch( (prefix+"_cone_energy_hadron" ).c_str(),       &cone_energy_hadron       ,(prefix+"_cone_energy_hadron").c_str()     );

	tree->Branch( (prefix+"_cone_energy_ratio_total"  ).c_str(), &cone_energy_ratio_total  ,(prefix+"_cone_energy_ratio_total").c_str()      );
	tree->Branch( (prefix+"_cone_energy_ratio_charge" ).c_str(), &cone_energy_ratio_charge ,(prefix+"_cone_energy_ratio_charge").c_str()     );
	tree->Branch( (prefix+"_cone_energy_ratio_neutral").c_str(), &cone_energy_ratio_neutral,(prefix+"_cone_energy_ratio_neutral").c_str()    );
	tree->Branch( (prefix+"_cone_energy_ratio_photon" ).c_str(), &cone_energy_ratio_photon ,(prefix+"_cone_energy_ratio_photon").c_str()     );
	tree->Branch( (prefix+"_cone_energy_ratio_lepton" ).c_str(), &cone_energy_ratio_lepton ,(prefix+"_cone_energy_ratio_lepton").c_str()     );
	tree->Branch( (prefix+"_cone_energy_ratio_hadron" ).c_str(), &cone_energy_ratio_hadron ,(prefix+"_cone_energy_ratio_hadron").c_str()     );

	tree->Branch( (prefix+"_cone_costheta" ).c_str(), &cone_costheta,(prefix+"_cone_costheta").c_str()     );
	tree->Branch( (prefix+"_mva_output" ).c_str(), &mva_output,(prefix+"_mva_output").c_str()     );
}

void PandoraIsolatedPhotonFinder_Variable::Get_MCParticle_Information( MCParticle* input) {
	pdg      =input->getPDG();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void PandoraIsolatedPhotonFinder_Variable::Get_PFOParticle_Information( ReconstructedParticle* input) {
	pdg      =input->getType();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void PandoraIsolatedPhotonFinder_Variable_Vec::Get_MCParticles_Information( std::vector<MCParticle*> input) {
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


void PandoraIsolatedPhotonFinder_Variable_Vec::Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) {
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


void PandoraIsolatedPhotonFinder_Variable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg").c_str()     , &pdg     ,(prefix+"_pdg").c_str()     );
	tree->Branch( (prefix+"_p").c_str()       , &p       ,(prefix+"_p").c_str()       );
	tree->Branch( (prefix+"_pt").c_str()      , &pt      ,(prefix+"_pt").c_str()      );
	tree->Branch( (prefix+"_costheta").c_str(), &costheta,(prefix+"_costheta").c_str());
	tree->Branch( (prefix+"_phi").c_str()     , &phi     ,(prefix+"_phi").c_str()     );
	tree->Branch( (prefix+"_e").c_str()       , &e       ,(prefix+"_e").c_str()       );
	tree->Branch( (prefix+"_mass").c_str()    , &mass    ,(prefix+"_mass").c_str()    );
}

void PandoraIsolatedPhotonFinder_Variable_Vec::Fill_Data(TTree* tree, std::string prefix){
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

void PandoraIsolatedPhotonFinder_Number::Get_MCParticles_Number( std::vector<MCParticle*> input) {
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


void PandoraIsolatedPhotonFinder_Number::Get_PFOParticles_Number( std::vector<ReconstructedParticle*> input) {
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

void PandoraIsolatedPhotonFinder_Number::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"num"            ).c_str()    , &num        ,(prefix+"num"            ).c_str()        );
	tree->Branch( (prefix+"num_plus"       ).c_str()    , &num_plus   ,(prefix+"num_plus"       ).c_str()        );
	tree->Branch( (prefix+"num_minus"      ).c_str()    , &num_minus  ,(prefix+"num_minus"      ).c_str()        );
	tree->Branch( (prefix+"num_neutral"    ).c_str()    , &num_neutral,(prefix+"num_neutral"    ).c_str()        );
	tree->Branch( (prefix+"num_central"    ).c_str()    , &num_central,(prefix+"num_central"    ).c_str()        );
	tree->Branch( (prefix+"num_forward"    ).c_str()    , &num_forward,(prefix+"num_forward"    ).c_str()        );
}


void PandoraIsolatedPhotonFinder_Information_Single::Get_MCParticles( std::vector<MCParticle*> input) {
	particle.Get_MCParticles_Information(input);
	num.Get_MCParticles_Number(input);
}

void PandoraIsolatedPhotonFinder_Information_Single::Get_PFOParticles( std::vector<ReconstructedParticle*> input) {
	particle.Get_PFOParticles_Information(input);
	num.Get_PFOParticles_Number(input);
}

void PandoraIsolatedPhotonFinder_Information_Single::Fill_Data(TTree* tree, std::string prefix){
	obv_small        .Fill_Data(tree,prefix+"_obv_small");
	obv_large        .Fill_Data(tree,prefix+"_obv_large");
	particle         .Fill_Data(tree,prefix+"_particle");
	num              .Fill_Data(tree,prefix+"_num");
}
