#include "PandoraIsolatedPhotonFinder.h"


bool PandoraIsolatedPhotonFinder::analysePFOParticle(LCCollection* input_mc, LCCollection* input_pfo, PandoraIsolatedPhotonFinder_Output_Collection& outputPhotonCol, PandoraIsolatedPhotonFinder_Output_Collection& outputWoPhotonCol, PandoraIsolatedPhotonFinder_Information& info_isr, PandoraIsolatedPhotonFinder_Information& info_normal, PandoraIsolatedPhotonFinder_Function_Counter& counter){
	std::vector<MCParticle*> input_mcs_photon=ToolSet::CMC::Get_MCParticle(input_mc);
	std::vector<ReconstructedParticle*> FS=ToolSet::CRC::Get_POParticle(input_pfo);
	std::vector<ReconstructedParticle*> all_photon=ToolSet::CRC::Get_POParticleType(FS,22);

	std::vector<ReconstructedParticle*> isr_photon;
	std::vector<ReconstructedParticle*> photon;
	std::vector<ReconstructedParticle*> wophoton;


	if(_output_switch_root&&!_output_switch_collection){
		ToolSet::CChain_Vec       _photon_chain;
		_photon_chain.Set_ChainVec(input_mcs_photon,_navmcpfo,_navpfomc);

		isr_photon=_photon_chain.Get_WeightedRC_MaxEnergy(22);
		wophoton=all_photon-isr_photon;

		for (int i = 0; i < isr_photon.size(); i++ ) {
			ReconstructedParticle* mc = isr_photon[i];

			if(mc==0){continue;}
			int output_iso =  IsIsolatedPhoton( mc, FS, info_isr.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}

		for (int i = 0; i < wophoton.size(); i++ ) {
			ReconstructedParticle* mc = wophoton[i];

			int output_iso =  IsIsolatedPhoton( mc, FS, info_normal.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}
	}

	else{
		for (int i = 0; i < all_photon.size(); i++ ) {
			ReconstructedParticle* mc = all_photon[i];

			int output_iso =  IsIsolatedPhoton( mc, FS, info_isr.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}
		wophoton=FS-all_photon;
	}

	for(int i=0;i<photon.size();i++){
		_pnum++;
	}
	outputPhotonCol  .Add_Element_RCParticle(photon);
	outputWoPhotonCol.Add_Element_RCParticle(wophoton);

	info_isr.isophoton.Get_PFOParticles(photon);
	info_isr.wophoton.Get_PFOParticles(wophoton);

	return(true);
}


int PandoraIsolatedPhotonFinder::IsIsolatedPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all, PandoraIsolatedPhotonFinder_Information_Single& info) {

	if(pfo->getType()!=22){
		return false;
	}

	Get_IsoPhoton_Observable(pfo, all, _minCosConeAngle, info.obv_small);
	Get_IsoPhoton_Observable(pfo, all, _maxCosConeAngle, info.obv_large);


	bool JISO=false;
	if(_output_switch_root&&!_output_switch_collection){
		JISO=true;
	}
	else{
		float mva_output = _reader->EvaluateMVA( "BDTGmethod" );
		info.obv_small.mva_output=mva_output;
		if(mva_output>_mvaCut){
			JISO=true;
		}
	}


	if (JISO){
		if(IsCentralPhoton(pfo)){
			return(1);
		}
		else if(IsForwardPhoton(pfo)){
			return(2);
		}
		else{
			return(0);
		}
	}

	return -1;
}



void PandoraIsolatedPhotonFinder::Get_IsoPhoton_Observable( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all, float cone_cut, PandoraIsolatedPhotonFinder_Observable& obv) {

	obv.input_energy             =pfo->getEnergy();
	TLorentzVector lorentz_input=TLorentzVector(pfo->getMomentum(),pfo->getEnergy());

	std::vector<ReconstructedParticle*> incone                  =ToolSet::CRC::Get_InCone(pfo, all,cone_cut);
	std::vector<ReconstructedParticle*> incone_wo_leading_photon=incone- pfo;
	//the following vectors don't contain input pfo photon.
	std::vector<ReconstructedParticle*> incone_charge           =ToolSet::CRC::Get_POParticleType(incone_wo_leading_photon,"charge");
	std::vector<ReconstructedParticle*> incone_neutral          =incone_wo_leading_photon-incone_charge;
	std::vector<ReconstructedParticle*> incone_photon           =ToolSet::CRC::Get_POParticleType(incone_wo_leading_photon,22);
	std::vector<ReconstructedParticle*> incone_lepton           =ToolSet::CRC::Get_POParticleType(incone_wo_leading_photon,"lepton");
	std::vector<ReconstructedParticle*> incone_hadron           =ToolSet::CRC::Get_POParticleType(incone_wo_leading_photon,"hadron");

	TLorentzVector sum_incone_total                             =ToolSet::CRC::Get_Sum_To_Lorentz(incone        );
	TLorentzVector sum_incone_wo_leading_photon                 =ToolSet::CRC::Get_Sum_To_Lorentz(incone_wo_leading_photon);
	TLorentzVector sum_incone_charge                            =ToolSet::CRC::Get_Sum_To_Lorentz(incone_charge );
	TLorentzVector sum_incone_neutral                           =ToolSet::CRC::Get_Sum_To_Lorentz(incone_neutral);
	TLorentzVector sum_incone_photon                            =ToolSet::CRC::Get_Sum_To_Lorentz(incone_photon );
	TLorentzVector sum_incone_lepton                            =ToolSet::CRC::Get_Sum_To_Lorentz(incone_lepton );
	TLorentzVector sum_incone_hadron                            =ToolSet::CRC::Get_Sum_To_Lorentz(incone_hadron );

	obv.num_incone_total         =incone_wo_leading_photon.size();
	obv.num_incone_charge        =incone_charge           .size();
	obv.num_incone_neutral       =incone_neutral          .size();
	obv.num_incone_photon        =incone_photon           .size();
	obv.num_incone_lepton        =incone_lepton           .size();
	obv.num_incone_hadron        =incone_hadron           .size();

	obv.cone_energy_total        =sum_incone_total  .E();
	obv.cone_energy_charge       =sum_incone_charge .E();
	obv.cone_energy_neutral      =sum_incone_neutral.E();
	obv.cone_energy_photon       =sum_incone_photon .E();
	obv.cone_energy_lepton       =sum_incone_lepton .E();
	obv.cone_energy_hadron       =sum_incone_hadron .E();

	obv.cone_energy_ratio_total  =obv.input_energy/obv.cone_energy_total;
	obv.cone_energy_ratio_charge =obv.cone_energy_charge /obv.input_energy;
	obv.cone_energy_ratio_neutral=obv.cone_energy_neutral/obv.input_energy;
	obv.cone_energy_ratio_photon =obv.cone_energy_photon /obv.input_energy;
	obv.cone_energy_ratio_lepton =obv.cone_energy_lepton /obv.input_energy;
	obv.cone_energy_ratio_hadron =obv.cone_energy_hadron /obv.input_energy;

	obv.cone_costheta            = TMath::Cos(sum_incone_wo_leading_photon.Angle(lorentz_input.Vect()));

}


bool PandoraIsolatedPhotonFinder::IsCentralPhoton( ReconstructedParticle* pfo) {
	float  energy = pfo->getEnergy();
	float  p      = ToolSet::CMC::Cal_P(pfo);
	float  angle  = std::abs(ToolSet::CMC::Cal_CosTheta(pfo));
	// set cut
	if (_useEnergy){
		if(_maxEnergyCut > 0 && energy > _maxEnergyCut){
			return false;
		}
		if(_minEnergyCut > 0 && energy<_minEnergyCut){
			return false;
		}
	} 

	if (_usePolarAngle){
		if(_minCosTheta > 0 && angle<_minCosTheta ){
			return false;
		}
		if(_maxCosTheta >0 && angle> _maxCosTheta){
			return false;
		}
	} 

	return true;
}



bool PandoraIsolatedPhotonFinder::IsForwardPhoton( ReconstructedParticle* pfo) {
	float energy = pfo->getEnergy();
	float  p      = ToolSet::CMC::Cal_P(pfo);
	float  angle  = std::abs(ToolSet::CMC::Cal_CosTheta(pfo));
	// set cut
	if (_useForwardEnergy){
		if(_maxForwardEnergyCut > 0 && energy > _maxForwardEnergyCut){
			return false;
		}
		if(_minForwardEnergyCut > 0 && energy<_minForwardEnergyCut){
			return false;
		}
	} 

	if (_useForwardPolarAngle){
		if(_minForwardCosTheta > 0 && angle<_minForwardCosTheta ){
			return false;
		}
		if(_maxForwardCosTheta >0 && angle> _maxForwardCosTheta){
			return false;
		}
	} 

	return true;
}
