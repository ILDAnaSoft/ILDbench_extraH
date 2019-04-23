#include "Extra_Scalar_Element_Observable.h"
void Extra_Scalar_Global_Counter::Fill_Data(TTree* tree){
	tree->Branch( "total_event_number"             , &nevt                     ,"total_event_number"              );
	tree->Branch( "total_run_number"               , &nrun                     ,"total_run_number"                );
	tree->Branch( "total_scale_factor"             , &gweight                  ,"total_scale_factor"              );
	tree->Branch( "total_pass_MCs"                 , &pass_MCs                 ,"total_pass_MCs"                  );
	tree->Branch( "total_pass_PFO"                 , &pass_PFO                 ,"total_pass_PFO"                  );
	tree->Branch( "total_pass_PFO_MC_Cheating_Muon", &pass_PFO_MC_Cheating_Muon,"total_pass_PFO_MC_Cheating_Muon" );
	tree->Branch( "total_pass_PFO_MC_Cheating_ISR" , &pass_PFO_MC_Cheating_ISR ,"total_pass_PFO_MC_Cheating_ISR"  );
	tree->Branch( "total_pass_PFO_MC_Cheating_ISR_Only" , &pass_PFO_MC_Cheating_ISR_Only ,"total_pass_PFO_MC_Cheating_ISR_Only"  );
	tree->Branch( "total_pass_all"                 , &pass_all                 ,"total_pass_all"                  );
}

void Extra_Scalar_Single_Counter::Fill_Data(TTree* tree){
	tree->Branch( "event_number"             , &evt                      ,"event_number"              );
	tree->Branch( "run_number"               , &run                      ,"run_number"                );
	tree->Branch( "scale_factor"             , &weight                   ,"scale_factor"              );
	tree->Branch( "pass_MCs"                 , &pass_MCs                 ,"pass_MCs"                  );
	tree->Branch( "pass_PFO"                 , &pass_PFO                 ,"pass_PFO"                  );
	tree->Branch( "pass_PFO_MC_Cheating_Muon", &pass_PFO_MC_Cheating_Muon,"pass_PFO_MC_Cheating_Muon" );
	tree->Branch( "pass_PFO_MC_Cheating_ISR" , &pass_PFO_MC_Cheating_ISR ,"pass_PFO_MC_Cheating_ISR"  );
	tree->Branch( "pass_PFO_MC_Cheating_ISR_Only" , &pass_PFO_MC_Cheating_ISR_Only ,"pass_PFO_MC_Cheating_ISR_Only"  );
	tree->Branch( "pass_all"                 , &pass_all                 ,"pass_all"                  );
}

void Extra_Scalar_Function_Counter::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pass_num").c_str()     , &pass_all   ,(prefix+"_pass_all").c_str()     );
	tree->Branch( (prefix+"_pass_energy").c_str()  , &pass_num   ,(prefix+"_pass_num").c_str()     );
	tree->Branch( (prefix+"_pass_all").c_str()     , &pass_energy,(prefix+"_pass_energy").c_str()  );
}


void Extra_Scalar_Observable::Get_Vertex_Information( VertexInfo &vv) {
	TVector3 vtxPos = vv.getVertexPosition();
	vtx = vtxPos[0];
	vty = vtxPos[1];
	vtz = vtxPos[2];
	chi2 = vv.getVertexChisq();
	return ;
}


void Extra_Scalar_Observable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"kcut_zmass"               ).c_str()    , &kcut_zmass                      ,(prefix+"kcut_zmass"               ).c_str()        );
	tree->Branch( (prefix+"kcut_zpt"                 ).c_str()    , &kcut_zpt                        ,(prefix+"kcut_zpt"                 ).c_str()        );
	tree->Branch( (prefix+"kcut_invis_costheta"      ).c_str()    , &kcut_invis_costheta             ,(prefix+"kcut_invis_costheta"      ).c_str()        );
	tree->Branch( (prefix+"kcut_invis_e"             ).c_str()    , &kcut_invis_e                    ,(prefix+"kcut_invis_e"             ).c_str()        );
	tree->Branch( (prefix+"kcut_recoil_mass"         ).c_str()    , &kcut_recoil_mass                ,(prefix+"kcut_recoil_mass"         ).c_str()        );
	tree->Branch( (prefix+"kcut_vis_e"               ).c_str()    , &kcut_vis_e                      ,(prefix+"kcut_vis_e"               ).c_str()        );
	tree->Branch( (prefix+"kcut_vis_all_e"           ).c_str()    , &kcut_vis_all_e                  ,(prefix+"kcut_vis_all_e"           ).c_str()        );

	tree->Branch( (prefix+"photon_lepton_costheta1"  ).c_str()    , &photon_lepton_costheta1         ,(prefix+"photon_lepton_costheta1"  ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_costheta2"  ).c_str()    , &photon_lepton_costheta2         ,(prefix+"photon_lepton_costheta2"  ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_phi1"       ).c_str()    , &photon_lepton_phi1              ,(prefix+"photon_lepton_phi1"       ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_phi2"       ).c_str()    , &photon_lepton_phi2              ,(prefix+"photon_lepton_phi2"       ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_pair_costheta"       ).c_str()    , &photon_lepton_pair_costheta      ,(prefix+"photon_lepton_pair_costheta"      ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_pair_costheta_pair"  ).c_str()    , &photon_lepton_pair_costheta_pair ,(prefix+"photon_lepton_pair_costheta_pair" ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_pair_azimuth"        ).c_str()    , &photon_lepton_pair_azimuth       ,(prefix+"photon_lepton_pair_azimuth"       ).c_str()        );
	tree->Branch( (prefix+"photon_lepton_pair_azimuth_pair"   ).c_str()    , &photon_lepton_pair_azimuth_pair  ,(prefix+"photon_lepton_pair_azimuth_pair"  ).c_str()        );

	tree->Branch( (prefix+"lep_pair_costheta"        ).c_str()    , &lep_pair_costheta               ,(prefix+"lep_pair_costheta"        ).c_str()        );
	tree->Branch( (prefix+"lep_pair_costheta_pair"   ).c_str()    , &lep_pair_costheta_pair          ,(prefix+"lep_pair_costheta_pair"   ).c_str()        );
	tree->Branch( (prefix+"lep_pair_azimuth"         ).c_str()    , &lep_pair_azimuth                ,(prefix+"lep_pair_azimuth"         ).c_str()        );
	tree->Branch( (prefix+"lep_pair_azimuth_pair"    ).c_str()    , &lep_pair_azimuth_pair           ,(prefix+"lep_pair_azimuth_pair"    ).c_str()        );

	tree->Branch( (prefix+"opal_lep_isolation1"      ).c_str()    , &opal_lep_isolation1             ,(prefix+"opal_lep_isolation1"      ).c_str()        );
	tree->Branch( (prefix+"opal_lep_isolation2"      ).c_str()    , &opal_lep_isolation2             ,(prefix+"opal_lep_isolation2"      ).c_str()        );
	tree->Branch( (prefix+"opal_zmass"               ).c_str()    , &opal_zmass                      ,(prefix+"opal_zmass"               ).c_str()        );
	tree->Branch( (prefix+"opal_lep_pair_pz"         ).c_str()    , &opal_lep_pair_pz                ,(prefix+"opal_lep_pair_pz"         ).c_str()        );
	tree->Branch( (prefix+"opal_invis_momentum"      ).c_str()    , &opal_invis_momentum             ,(prefix+"opal_invis_momentum"      ).c_str()        );
	tree->Branch( (prefix+"opal_invis_costheta"      ).c_str()    , &opal_invis_costheta             ,(prefix+"opal_invis_costheta"      ).c_str()        );
	tree->Branch( (prefix+"opal_lep_pair_acoplanarity").c_str()   , &opal_lep_pair_acoplanarity      ,(prefix+"opal_lep_pair_acoplanarity").c_str()        );

	tree->Branch( (prefix+"_vtx").c_str(), &vtx, (prefix+"_vtx").c_str()  );
	tree->Branch( (prefix+"_vty").c_str(), &vty, (prefix+"_vty").c_str()  );
	tree->Branch( (prefix+"_vtz").c_str(), &vtz, (prefix+"_vtz").c_str()  );
	tree->Branch( (prefix+"_chi2").c_str(), &chi2, (prefix+"_chi2").c_str()  );
}

void Extra_Scalar_Variable::Get_MCsParticle_Information( MCParticle* input) {
	pdg      =input->getPDG();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void Extra_Scalar_Variable::Get_PFOParticle_Information( ReconstructedParticle* input) {
	pdg      =input->getType();
	p        =ToolSet::CMC::Cal_P(input);
	pt       =ToolSet::CMC::Cal_PT(input);
	costheta =ToolSet::CMC::Cal_CosTheta(input);
	phi      =ToolSet::CMC::Cal_Azimuth(input);
	e        =input->getEnergy();
	mass     =input->getMass();
	return ;
}

void Extra_Scalar_Variable_Vec::Get_MCsParticles_Information( std::vector<MCParticle*> input) {
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


void Extra_Scalar_Variable_Vec::Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) {
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


void Extra_Scalar_Variable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg").c_str()     , &pdg     ,(prefix+"_pdg").c_str()     );
	tree->Branch( (prefix+"_p").c_str()       , &p       ,(prefix+"_p").c_str()       );
	tree->Branch( (prefix+"_pt").c_str()      , &pt      ,(prefix+"_pt").c_str()      );
	tree->Branch( (prefix+"_costheta").c_str(), &costheta,(prefix+"_costheta").c_str());
	tree->Branch( (prefix+"_phi").c_str()     , &phi     ,(prefix+"_phi").c_str()     );
	tree->Branch( (prefix+"_e").c_str()       , &e       ,(prefix+"_e").c_str()       );
	tree->Branch( (prefix+"_mass").c_str()    , &mass    ,(prefix+"_mass").c_str()    );
}

void Extra_Scalar_Variable_Vec::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg_vec")          .c_str()  , &pdg          );
	tree->Branch( (prefix+"_p_vec")            .c_str()  , &p            );
	tree->Branch( (prefix+"_pt_vec")           .c_str()  , &pt           );
	tree->Branch( (prefix+"_costheta_vec")     .c_str()  , &costheta     );
	tree->Branch( (prefix+"_phi_vec")          .c_str()  , &phi          );
	tree->Branch( (prefix+"_e_vec")            .c_str()  , &e            );
	tree->Branch( (prefix+"_mass_vec")         .c_str()  , &mass         );
}




void Extra_Scalar_Number::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"num"            ).c_str()    , &num        ,(prefix+"num"            ).c_str()        );
	tree->Branch( (prefix+"num_plus"       ).c_str()    , &num_plus   ,(prefix+"num_plus"       ).c_str()        );
	tree->Branch( (prefix+"num_minus"      ).c_str()    , &num_minus  ,(prefix+"num_minus"      ).c_str()        );
	tree->Branch( (prefix+"num_neutral"    ).c_str()    , &num_neutral,(prefix+"num_neutral"    ).c_str()        );
	tree->Branch( (prefix+"num_central"    ).c_str()    , &num_central,(prefix+"num_central"    ).c_str()        );
	tree->Branch( (prefix+"num_forward"    ).c_str()    , &num_forward,(prefix+"num_forward"    ).c_str()        );
}
