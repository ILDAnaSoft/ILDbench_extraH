#include "PFOLeptonTagging.h"
#include "CMC.h"
using namespace lcio;

int PFOLeptonTagging::analysePOParticle( LCCollection* Input_PFOLeptonCol,  LCCollection* Input_PFOWoLeptonCol, 
		LCCollection* Input_MCsCol,
		PFOLeptonTagging_Output_Collection &NewPFOIsoLeptonCol,
		PFOLeptonTagging_Output_Collection &NewPFOWoIsoLeptonCol, 
		PFOLeptonTagging_Information &info, PFOLeptonTagging_Function_Counter& counter){

	std::vector<ReconstructedParticle*> input_lepton =ToolSet::CRC::Get_POParticle(Input_PFOLeptonCol);
	std::vector<ReconstructedParticle*> input_other  =ToolSet::CRC::Get_POParticle(Input_PFOWoLeptonCol);
	std::vector<ReconstructedParticle*> choosed_leps, others;
	std::vector<MCParticle*>            input_mclepton=ToolSet::CMC::Get_MCParticle(Input_MCsCol);

	if(input_mclepton.size()>=2){
		lepnum++;
	}

	POCut_Detail(input_lepton, input_other, choosed_leps, others, info);
	MCCut_Detail(input_mclepton, info);


	//add into output collections
	NewPFOIsoLeptonCol  .Add_Element_RCParticle(choosed_leps);
	NewPFOWoIsoLeptonCol.Add_Element_RCParticle(others);

	return(1);
}


bool PFOLeptonTagging::POCut_Detail(std::vector<ReconstructedParticle*> &input_leps,  std::vector<ReconstructedParticle*> &input_others, std::vector<ReconstructedParticle*> &out_leps, std::vector<ReconstructedParticle*> &out_others, PFOLeptonTagging_Information &info){

	bool JMuon=POCut_Muon(input_leps,info.pfo_input_lepton);
	if(!JMuon){
		return(false);
	}

	info.pfo_input_other          .Get_PFOParticles(input_others);


	std::vector<ReconstructedParticle*> choosed_leps;
	bool Jrecoil=POCut_Recoil(input_leps, choosed_leps);
	if(!Jrecoil){
		return(false);
	}


	POCut_Observable(choosed_leps, info.pfo_input_lepton.obv);


	std::vector<ReconstructedParticle*> others_with_left_lepton;
	others_with_left_lepton = input_leps - choosed_leps + input_others;

	//FSR recovery
    out_leps = ToolSet::CRC::Get_Isolated(choosed_leps, others_with_left_lepton, out_others, 0.99);

  	POCut_Observable(out_leps, info.pfo_output_lepton.obv);

	POCut_Muon(out_leps,info.pfo_output_lepton);
	info.pfo_output_other         .Get_PFOParticles(out_others);

	return(true);
}



bool PFOLeptonTagging::POCut_Muon( std::vector<ReconstructedParticle*> &muon, PFOLeptonTagging_Information_Single& info) {
	std::vector<ReconstructedParticle*> muonplus =ToolSet::CRC::Get_POParticleType(muon, 13);
	std::vector<ReconstructedParticle*> muonminus=ToolSet::CRC::Get_POParticleType(muon,-13);
	int numt = muon.size();
	int nump = muonplus .size();
	int numm = muonminus.size();
	info.Get_PFOParticles(muon);

	if(numt<2) {
		return(false);
	}
	if(nump<1) {
		return(false);
	}
	if(numm<1) {
		return(false);
	}

	return(true);
}

bool PFOLeptonTagging::POCut_MuonPair( std::vector<ReconstructedParticle*> &muon, PFOLeptonTagging_Observable& obv) {
	EVENT::Track* lep1=0,  *lep2=0; 
	EVENT::TrackVec trkvec1 = muon[0]->getTracks();
	EVENT::TrackVec trkvec2 = muon[1]->getTracks();

	if((trkvec1.size()>0)&&(trkvec2.size()>0)){
		lep1=trkvec1[0];
		lep2=trkvec2[0];

		VertexInfo vv;
		vv.addTrack( lep1 );
		vv.addTrack( lep2 );
		//beam spot constraint
		float xyz[3] = { 150e-6, 5e-6, 0.2  }; //mm
		vv.setBeamSpotSize( xyz  );
		vv.useIPcon( true  );

		TVector3 vtxPos = vv.getVertexPosition();
		float vtx = vtxPos[0];
		float vty = vtxPos[1];
		float vtz = vtxPos[2];
		float chi2 = vv.getVertexChisq();
		obv.Get_Vertex_Information(vv);
	}

	return(true);
}


bool PFOLeptonTagging::POCut_Recoil(std::vector<ReconstructedParticle*> in, std::vector<ReconstructedParticle*> &out) {
	int num=in.size();
	if(num<2){
		return(false);
	}

	float chi_min= 1000000.0;
	float chi_tmp=chi_min;
	float recoil_mass_final = 999.99;
	float pair_mass_final = 999.99;

	int choosei=1000,choosej=1000;
	for(int i=0;i<num-1;i++){
		for(int j=1;j<num;j++){
			std::vector<ReconstructedParticle*> test_pair;
			test_pair.push_back(in[i]);
			test_pair.push_back(in[j]);
			TLorentzVector pair_mom = ToolSet::CRC::Get_Sum_To_Lorentz(test_pair);
			TLorentzVector recoil_mom = ToolSet::CRC::Get_InVisible_To_Lorentz(test_pair);
			float  recoil_mass=recoil_mom.M();
			float  pair_mass=pair_mom.M();
			if(std::abs(pair_mass-91.187)>40.0){
				continue;
			}
			if((in[i]->getCharge())*(in[j]->getCharge())>0){//Should be different sign lepton
				continue;
			}
			float  sigma_pair=1;
			float  sigma_recoil=1;
		
			sigma_pair  = ToolSet::CRC::Get_Resolution_Invariant_Mass(in[i],in[j],91.187);
			sigma_recoil= ToolSet::CRC::Get_Resolution_Invariant_Mass(in[i],in[j],_hmass);

			chi_tmp = std::pow((pair_mass-91.187)/sigma_pair,2)+std::pow((recoil_mass-_hmass)/sigma_recoil,2);

			if(chi_tmp<chi_min){
				chi_min = chi_tmp;
				choosei=i;
				choosej=j;
				recoil_mass_final=recoil_mass;
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


bool PFOLeptonTagging::POCut_Observable(std::vector<ReconstructedParticle*> &choosed_leps,  PFOLeptonTagging_Observable &obv){
	//default 2 muons.

	TLorentzVector pair=ToolSet::CRC::Get_Sum_To_Lorentz(choosed_leps);
	TLorentzVector recoil=ToolSet::CRC::Get_InVisible_To_Lorentz(choosed_leps);

	obv.combined_inm=pair.M();
	obv.sigma_inm = ToolSet::CRC::Get_Resolution_Invariant_Mass(choosed_leps[0],choosed_leps[1],91.187);
	obv.combined_pt=pair.Pt();
	obv.recoil_mass=recoil.M();
	obv.sigma_recoil= ToolSet::CRC::Get_Resolution_Invariant_Mass(choosed_leps[0],choosed_leps[1],_hmass);

	obv.lepton_pair_costheta     =pair.CosTheta();
	obv.lepton_pair_costheta_pair=ToolSet::CMC::Cal_CosTheta(choosed_leps[0],choosed_leps[1]);

	obv.lepton_pair_azimuth      =pair.Phi();
	obv.lepton_pair_azimuth_pair =ToolSet::CMC::Cal_Acoplanarity(choosed_leps[0],choosed_leps[1]);

	return(true);
}


bool PFOLeptonTagging::MCCut_Detail(std::vector<MCParticle*> &input_leps, PFOLeptonTagging_Information &info){

	std::vector<MCParticle*> muonplus =ToolSet::CMC::Get_MCParticleType(input_leps, 13);
	std::vector<MCParticle*> muonminus=ToolSet::CMC::Get_MCParticleType(input_leps,-13);
	int numt = input_leps.size();
	int nump = muonplus .size();
	int numm = muonminus.size();
	info.mcs_input_lepton.Get_MCsParticles(muon_pair);
	if(numt<2) {
		return(false);
	}
	if(nump<1) {
		return(false);
	}
	if(numm<1) {
		return(false);
	}

	std::vector<MCParticle*> muon_pair;
	muon_pair.push_back(muonplus[0]);
	muon_pair.push_back(muonminus[0]);
	TLorentzVector pair=ToolSet::CMC::Get_Sum_To_Lorentz(muon_pair);
	TLorentzVector recoil=ToolSet::CMC::Get_InVisible_To_Lorentz(muon_pair);

	info.mcs_input_lepton.obv.combined_inm=pair.M();
	info.mcs_input_lepton.obv.combined_pt=pair.Pt();
	info.mcs_input_lepton.obv.recoil_mass=recoil.M();

	return(true);
}

