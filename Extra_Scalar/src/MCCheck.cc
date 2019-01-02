#include "Extra_Scalar.h"

bool Extra_Scalar::MCCutDetail(std::vector<MCParticle*> &choosed_lep,  std::vector<MCParticle*> &photon, std::vector<MCParticle*> &MCsWoMuonPhoton, Extra_Scalar_Observable &obv){

	TLorentzVector pair=ToolSet::CMC::Get_Sum_To_Lorentz(choosed_lep);
	float zmass=pair.M();
	obv.kcut_zmass=zmass;

	float zpt=pair.Pt();
	obv.kcut_zpt=zpt;


	std::vector<MCParticle*> visible_vec=MCsWoMuonPhoton;

	TLorentzVector visible=ToolSet::CMC::Get_Sum_To_Lorentz(visible_vec);

	std::vector<MCParticle*> invisible_vec=visible_vec+choosed_lep;

	TLorentzVector allvisible=ToolSet::CMC::Get_Sum_To_Lorentz(invisible_vec);

	TLorentzVector invisible=ToolSet::CMC::Get_InVisible_To_Lorentz(invisible_vec);

	float invis_costheta=invisible.CosTheta();
	float invis_e       =invisible.E();

	obv.kcut_invis_costheta=invis_costheta;
	obv.kcut_invis_e       =invis_e;


	obv.lep_pair_costheta     =pair.CosTheta();
	obv.lep_pair_costheta_pair=ToolSet::CMC::Cal_CosTheta(choosed_lep[0],choosed_lep[1]);
	obv.lep_pair_azimuth      =pair.Phi();
	obv.lep_pair_azimuth_pair =ToolSet::CMC::Cal_Acoplanarity(choosed_lep[0],choosed_lep[1]);

	TLorentzVector recoil=ToolSet::CMC::Get_InVisible_To_Lorentz(choosed_lep);
	obv.kcut_recoil_mass=recoil.M();


	obv.kcut_vis_all_e=allvisible.E();
	obv.kcut_vis_e    =visible.E();

	//  Opal's observables
	obv.opal_lep_isolation1        =ToolSet::CMC::Get_IsolationAngle(choosed_lep[0],MCsWoMuonPhoton);
	obv.opal_lep_isolation2        =ToolSet::CMC::Get_IsolationAngle(choosed_lep[1],MCsWoMuonPhoton);
	obv.opal_zmass                 =zmass;
	obv.opal_lep_pair_pz           =pair.Pz();
	obv.opal_invis_momentum        =invisible.P();
	obv.opal_invis_costheta        =invisible.CosTheta();
	obv.opal_lep_pair_acoplanarity =ToolSet::CMC::Cal_Acoplanarity(choosed_lep[0],choosed_lep[1]);

	return(true);

}



