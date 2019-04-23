#include "Strange_Photon_Element_Observable.h"
void Strange_Photon_Global_Counter::Fill_Data(TTree* tree){
	tree->Branch( "total_event_number"             , &nevt                     ,"total_event_number"              );
	tree->Branch( "total_run_number"               , &nrun                     ,"total_run_number"                );
	tree->Branch( "total_scale_factor"             , &gweight                  ,"total_scale_factor"              );
	tree->Branch( "total_pass_MCs1"                , &pass_MCs1                ,"total_pass_MCs1"                 );
	tree->Branch( "total_pass_MCs2"                , &pass_MCs2                ,"total_pass_MCs2"                 );
	tree->Branch( "total_pass_all"                 , &pass_all                 ,"total_pass_all"                  );
}

void Strange_Photon_Single_Counter::Fill_Data(TTree* tree){
	tree->Branch( "event_number"             , &evt                      ,"event_number"              );
	tree->Branch( "run_number"               , &run                      ,"run_number"                );
	tree->Branch( "scale_factor"             , &weight                   ,"scale_factor"              );
	tree->Branch( "pass_MCs1"                , &pass_MCs1                ,"pass_MCs1"                 );
	tree->Branch( "pass_MCs2"                , &pass_MCs2                ,"pass_MCs2"                 );
	tree->Branch( "pass_all"                 , &pass_all                 ,"pass_all"                  );
}


void Strange_Photon_Function_Counter::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pass_all").c_str()     , &pass_all,(prefix+"_pass_all").c_str()  );
}

void Strange_Photon_Observable::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pfo_minus_mc_energy").c_str(), &visible_energy,(prefix+"_pfo_minus_mc_energy").c_str()  );
	tree->Branch( (prefix+"_invisible_energy").c_str()   , &invisible_energy,(prefix+"_invisible_energy").c_str()   );
	tree->Branch( (prefix+"_energy_difference").c_str()  , &energy_difference);
	tree->Branch( (prefix+"_photon_head").c_str()  , &photon_head);

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

	std::vector<lcio::Cluster*> clusters = input->getClusters();
	for ( std::vector<lcio::Cluster*>::const_iterator iCluster=clusters.begin();
			iCluster!=clusters.end();
			++iCluster) {
		ecal    += (*iCluster)->getSubdetectorEnergies()[0];
		hcal    += (*iCluster)->getSubdetectorEnergies()[1];
		yoke    += (*iCluster)->getSubdetectorEnergies()[2];
		lumical += (*iCluster)->getSubdetectorEnergies()[3];
		lhcal   += (*iCluster)->getSubdetectorEnergies()[4];
		beamcal += (*iCluster)->getSubdetectorEnergies()[5];

		float ehit=0;
		CalorimeterHitVec hits     = (*iCluster)->getCalorimeterHits();
		for ( std::vector<lcio::CalorimeterHit*>::const_iterator iHit=hits.begin();
				iHit!=hits.end();
				++iHit) {
			ehit+= (*iHit)->getEnergy();
			ToolSet::ShowMessage(1,"hit energy",ehit);
		}
		ToolSet::ShowMessage(1,"total hit energy",ehit);
		ToolSet::ShowMessage(1,"total cluster energy",(*iCluster)->getEnergy());
	}
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

		std::vector<lcio::Cluster*> clusters = input[i]->getClusters();
		float ecal_i=0, hcal_i=0, yoke_i=0, lumical_i=0,lhcal_i=0,beamcal_i=0;
		for ( std::vector<lcio::Cluster*>::const_iterator iCluster=clusters.begin();
				iCluster!=clusters.end();
				++iCluster) {
			ecal_i    += (*iCluster)->getSubdetectorEnergies()[0];
			hcal_i    += (*iCluster)->getSubdetectorEnergies()[1];
			yoke_i    += (*iCluster)->getSubdetectorEnergies()[2];
			lumical_i += (*iCluster)->getSubdetectorEnergies()[3];
			lhcal_i   += (*iCluster)->getSubdetectorEnergies()[4];
			beamcal_i += (*iCluster)->getSubdetectorEnergies()[5];
		}
		ecal   .push_back(ecal_i);
		hcal   .push_back(hcal_i);
		yoke   .push_back(yoke_i);
		lumical.push_back(lumical_i);
		lhcal  .push_back(lhcal_i);
		beamcal.push_back(beamcal_i);
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
	tree->Branch( (prefix+"_ecal").c_str()    , &ecal    ,(prefix+"_ecal").c_str()    );
	tree->Branch( (prefix+"_hcal").c_str()    , &hcal    ,(prefix+"_hcal").c_str()    );
	tree->Branch( (prefix+"_yoke").c_str()    , &yoke    ,(prefix+"_yoke").c_str()    );
	tree->Branch( (prefix+"_lumical").c_str() , &lumical ,(prefix+"_lumical").c_str() );
	tree->Branch( (prefix+"_lhcal").c_str()   , &lhcal   ,(prefix+"_lhcal").c_str()   );
	tree->Branch( (prefix+"_beamcal").c_str() , &beamcal ,(prefix+"_beamcal").c_str() );
}

void Strange_Photon_Variable_Vec::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"_pdg_vec")          .c_str(), &pdg          );
	tree->Branch( (prefix+"_p_vec")            .c_str(), &p            );
	tree->Branch( (prefix+"_pt_vec")           .c_str(), &pt           );
	tree->Branch( (prefix+"_costheta_vec")     .c_str(), &costheta     );
	tree->Branch( (prefix+"_phi_vec")          .c_str(), &phi          );
	tree->Branch( (prefix+"_e_vec")            .c_str(), &e            );
	tree->Branch( (prefix+"_mass_vec")         .c_str(), &mass         );
	tree->Branch( (prefix+"_ecal_vec")         .c_str(), &ecal         );
	tree->Branch( (prefix+"_hcal_vec")         .c_str(), &hcal         );
	tree->Branch( (prefix+"_yoke_vec")         .c_str(), &yoke         );
	tree->Branch( (prefix+"_lumical_vec")      .c_str(), &lumical      );
	tree->Branch( (prefix+"_lhcal_vec")        .c_str(), &lhcal        );
	tree->Branch( (prefix+"_beamcal_vec")      .c_str(), &beamcal      );
	tree->Branch( (prefix+"_endpointr")        .c_str(), &endpointr    );
	tree->Branch( (prefix+"_endpointx")        .c_str(), &endpointx    );
	tree->Branch( (prefix+"_endpointy")        .c_str(), &endpointy    );
	tree->Branch( (prefix+"_endpointz")        .c_str(), &endpointz    );
	tree->Branch( (prefix+"_vertexr")          .c_str(), &vertexr      );
	tree->Branch( (prefix+"_vertexx")          .c_str(), &vertexx      );
	tree->Branch( (prefix+"_vertexy")          .c_str(), &vertexy      );
	tree->Branch( (prefix+"_vertexz")          .c_str(), &vertexz      );
}


void Strange_Photon_Number::Get_MCParticle_Number( MCParticle* input) {
	if(input->getCharge()>0){
		num_plus++;
	}
	else if(input->getCharge()<0){
		num_minus++;
	}
	else{
		num_neutral++;
	}
	if(std::abs(ToolSet::CMC::Cal_CosTheta(input))<0.95){
		num_central++;
	}
	else{
		num_forward++;
	}
	return ;
}


void Strange_Photon_Number::Get_PFOParticle_Number( ReconstructedParticle* input) {
	if(input->getCharge()>0){
		num_plus++;
	}
	else if(input->getCharge()<0){
		num_minus++;
	}
	else{
		num_neutral++;
	}
	if(std::abs(ToolSet::CMC::Cal_CosTheta(input))<0.95){
		num_central++;
	}
	else{
		num_forward++;
	}
	return ;
}
void Strange_Photon_Number::Get_MCParticles_Number( std::vector<MCParticle*> input) {
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


void Strange_Photon_Number::Get_PFOParticles_Number( std::vector<ReconstructedParticle*> input) {
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

void Strange_Photon_Number::Fill_Data(TTree* tree, std::string prefix){
	tree->Branch( (prefix+"num"            ).c_str()    , &num        ,(prefix+"num"            ).c_str()        );
	tree->Branch( (prefix+"num_plus"       ).c_str()    , &num_plus   ,(prefix+"num_plus"       ).c_str()        );
	tree->Branch( (prefix+"num_minus"      ).c_str()    , &num_minus  ,(prefix+"num_minus"      ).c_str()        );
	tree->Branch( (prefix+"num_neutral"    ).c_str()    , &num_neutral,(prefix+"num_neutral"    ).c_str()        );
	tree->Branch( (prefix+"num_central"    ).c_str()    , &num_central,(prefix+"num_central"    ).c_str()        );
	tree->Branch( (prefix+"num_forward"    ).c_str()    , &num_forward,(prefix+"num_forward"    ).c_str()        );
}

void Strange_Photon_Information_Single::Get_MCParticles( std::vector<MCParticle*> input) {
	particle.Get_MCParticles_Information(input);
	num.Get_MCParticles_Number(input);
}

void Strange_Photon_Information_Single::Get_PFOParticles( std::vector<ReconstructedParticle*> input) {
	particle.Get_PFOParticles_Information(input);
	num.Get_PFOParticles_Number(input);
}

void Strange_Photon_Information_Single::Fill_Data(TTree* tree, std::string prefix){
	obv         .Fill_Data(tree,prefix+"_obv");
	particle    .Fill_Data(tree,prefix+"_particle");
	num.Fill_Data(tree,prefix+"_num");
}
