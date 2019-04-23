#include "Extra_Scalar.h"

bool Extra_Scalar::POCutDetail(std::vector<ReconstructedParticle*> &choosed_lep,  std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton, Extra_Scalar_Observable &obv){

	TLorentzVector pair=ToolSet::CRC::Get_Sum_To_Lorentz(choosed_lep);
	obv.kcut_zmass     =pair.M();
	obv.kcut_zpt       =pair.Pt();

	obv.lep_pair_costheta     =pair.CosTheta();
	obv.lep_pair_costheta_pair=ToolSet::CMC::Cal_CosTheta(choosed_lep[0],choosed_lep[1]);

	obv.lep_pair_azimuth      =pair.Phi();
	obv.lep_pair_azimuth_pair =ToolSet::CMC::Cal_Acoplanarity(choosed_lep[0],choosed_lep[1]);

	TLorentzVector recoil=ToolSet::CRC::Get_InVisible_To_Lorentz(choosed_lep);
	obv.kcut_recoil_mass=recoil.M();




	std::vector<ReconstructedParticle*> visible_vec=PFOWoMuonPhoton+photon;

	TLorentzVector visible=ToolSet::CRC::Get_Sum_To_Lorentz(visible_vec);

	std::vector<ReconstructedParticle*> invisible_vec=visible_vec+choosed_lep;

	TLorentzVector allvisible=ToolSet::CRC::Get_Sum_To_Lorentz(invisible_vec);

	TLorentzVector invisible=ToolSet::CRC::Get_InVisible_To_Lorentz(invisible_vec);

	float invis_costheta=invisible.CosTheta();
	float invis_e       =invisible.E();
	obv.kcut_invis_costheta=invis_costheta;
	obv.kcut_invis_e       =invis_e;

	obv.kcut_vis_all_e=allvisible.E();
	obv.kcut_vis_e    =visible.E();


		TLorentzVector no_photon= ToolSet::CRC::Get_InVisible_To_Lorentz(photon); 


		TVector3 boostvec=-no_photon.BoostVector();

		TLorentzVector no_photon_cms= no_photon;
		TLorentzVector pair_cms= pair;
		TLorentzVector leading_lepton_cms= TLorentzVector(choosed_lep[0]->getMomentum(),choosed_lep[0]->getEnergy());
		TLorentzVector subleading_lepton_cms= TLorentzVector(choosed_lep[1]->getMomentum(),choosed_lep[1]->getEnergy());


		if(no_photon.M()>0){
			no_photon_cms.Boost(boostvec);
			pair_cms.Boost(boostvec);
			leading_lepton_cms.Boost(boostvec);
			subleading_lepton_cms.Boost(boostvec);
		}


		obv.photon_lepton_costheta1=leading_lepton_cms.CosTheta();
		obv.photon_lepton_costheta2=subleading_lepton_cms.CosTheta();
		
		obv.photon_lepton_phi1=leading_lepton_cms.Phi();
		obv.photon_lepton_phi2=subleading_lepton_cms.Phi();

		obv.photon_lepton_pair_costheta=pair_cms.CosTheta();
		obv.photon_lepton_pair_costheta_pair=TMath::Cos(subleading_lepton_cms.Angle(leading_lepton_cms.Vect()));
		
		obv.photon_lepton_pair_azimuth=pair_cms.Phi();
		obv.photon_lepton_pair_azimuth_pair =TMath::Pi()-std::abs(subleading_lepton_cms.DeltaPhi(leading_lepton_cms));
		


	//  Opal's observables
	obv.opal_lep_isolation1        =ToolSet::CRC::Get_IsolationAngle(choosed_lep[0],PFOWoMuonPhoton);
	obv.opal_lep_isolation2        =ToolSet::CRC::Get_IsolationAngle(choosed_lep[1],PFOWoMuonPhoton);
	obv.opal_zmass                 =pair.M();
	obv.opal_lep_pair_pz           =pair.Pz();
	obv.opal_invis_momentum        =invisible.P();
	obv.opal_invis_costheta        =invisible.CosTheta();
	obv.opal_lep_pair_acoplanarity =ToolSet::CMC::Cal_Acoplanarity(choosed_lep[0],choosed_lep[1]);

	return(true);

}






bool Extra_Scalar::POCut_Muon(std::vector<ReconstructedParticle*> &choosed_lep,  Extra_Scalar_Observable &obv){

	TLorentzVector pair=ToolSet::CRC::Get_Sum_To_Lorentz(choosed_lep);
	obv.kcut_zmass=pair.M();
	obv.kcut_zpt=pair.Pt();

	obv.lep_pair_costheta     =pair.CosTheta();
	obv.lep_pair_costheta_pair=ToolSet::CMC::Cal_CosTheta(choosed_lep[0],choosed_lep[1]);

	obv.lep_pair_azimuth      =pair.Phi();
	obv.lep_pair_azimuth_pair =ToolSet::CMC::Cal_Acoplanarity(choosed_lep[0],choosed_lep[1]);

	TLorentzVector recoil=ToolSet::CRC::Get_InVisible_To_Lorentz(choosed_lep);
	obv.kcut_recoil_mass=recoil.M();

	return(true);
}

bool Extra_Scalar::MCCut_Muon(std::vector<MCParticle*> &choosed_lep,  Extra_Scalar_Observable &obv){

	TLorentzVector pair=ToolSet::CMC::Get_Sum_To_Lorentz(choosed_lep);
	obv.kcut_zmass=pair.M();
	obv.kcut_zpt=pair.Pt();

	obv.lep_pair_costheta     =pair.CosTheta();
	obv.lep_pair_costheta_pair=ToolSet::CMC::Cal_CosTheta(choosed_lep[0],choosed_lep[1]);

	obv.lep_pair_azimuth      =pair.Phi();
	obv.lep_pair_azimuth_pair =ToolSet::CMC::Cal_Acoplanarity(choosed_lep[0],choosed_lep[1]);

	TLorentzVector recoil=ToolSet::CMC::Get_InVisible_To_Lorentz(choosed_lep);
	obv.kcut_recoil_mass=recoil.M();

	return(true);
}


bool Extra_Scalar::POCut_Global(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv){

	std::vector<ReconstructedParticle*> visible_vec=PFOWoMuonPhoton+photon;

	TLorentzVector visible=ToolSet::CRC::Get_Sum_To_Lorentz(visible_vec);

	std::vector<ReconstructedParticle*> invisible_vec=visible_vec+choosed_lep;

	TLorentzVector allvisible=ToolSet::CRC::Get_Sum_To_Lorentz(invisible_vec);

	TLorentzVector invisible=ToolSet::CRC::Get_InVisible_To_Lorentz(invisible_vec);

	float invis_costheta=invisible.CosTheta();
	float invis_e       =invisible.E();
	obv.kcut_invis_costheta=invis_costheta;
	obv.kcut_invis_e       =invis_e;

	obv.kcut_vis_all_e=allvisible.E();
	obv.kcut_vis_e    =visible.E();

	return(true);
}


bool Extra_Scalar::POCut_Global(std::vector<MCParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv){

	std::vector<ReconstructedParticle*> visible_vec=PFOWoMuonPhoton+photon;

	TLorentzVector visible=ToolSet::CRC::Get_Sum_To_Lorentz(visible_vec);

	std::vector<ReconstructedParticle*> invisible_vec=visible_vec;

	TLorentzVector allvisible1=ToolSet::CRC::Get_Sum_To_Lorentz(invisible_vec);
	TLorentzVector allvisible2=ToolSet::CMC::Get_Sum_To_Lorentz(choosed_lep);
	TLorentzVector allvisible =allvisible1 + allvisible2;
	

	TLorentzVector invisible=ToolSet::CRC::Get_InVisible_To_Lorentz(invisible_vec);

	float invis_costheta=invisible.CosTheta();
	float invis_e       =invisible.E();
	obv.kcut_invis_costheta=invis_costheta;
	obv.kcut_invis_e       =invis_e;

	obv.kcut_vis_all_e=allvisible.E();
	obv.kcut_vis_e    =visible.E();
	return(true);

}




bool Extra_Scalar::POCut_Global(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<MCParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv){

	TLorentzVector visible1=ToolSet::CRC::Get_Sum_To_Lorentz(PFOWoMuonPhoton);
	TLorentzVector visible2=ToolSet::CMC::Get_Sum_To_Lorentz(photon);
	TLorentzVector visible3=ToolSet::CRC::Get_Sum_To_Lorentz(choosed_lep);
	std::vector<TLorentzVector> allvisible_vec;
	std::vector<TLorentzVector> visible_womuon_vec;
	allvisible_vec.push_back(visible1);
	allvisible_vec.push_back(visible2);
	visible_womuon_vec=allvisible_vec;
	allvisible_vec.push_back(visible3);
	TLorentzVector invisible=ToolSet::CLV::Get_InVisible(allvisible_vec);
	TLorentzVector allvisible=ToolSet::CLV::Get_InVisible(allvisible_vec);
	TLorentzVector visible_womuon=ToolSet::CLV::Get_InVisible(visible_womuon_vec);

	obv.kcut_invis_costheta=invisible.CosTheta();
	obv.kcut_invis_e       =invisible.E();

	obv.kcut_vis_all_e=allvisible.E();
	obv.kcut_vis_e    =visible_womuon.E();
	return(true);

}




