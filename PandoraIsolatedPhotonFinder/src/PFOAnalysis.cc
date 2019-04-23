#include "PandoraIsolatedPhotonFinder.h"


bool PandoraIsolatedPhotonFinder::analysePFOParticle(LCCollection* input_mc, LCCollection* input_pfo, PandoraIsolatedPhotonFinder_Output_Collection& outputPhotonCol, PandoraIsolatedPhotonFinder_Output_Collection& outputWoPhotonCol, PandoraIsolatedPhotonFinder_Information& info_isr, PandoraIsolatedPhotonFinder_Information& info_normal, PandoraIsolatedPhotonFinder_Function_Counter& counter){
	std::vector<MCParticle*> input_mcs_photon=ToolSet::CMC::Get_MCParticle(input_mc);
	std::vector<ReconstructedParticle*> FS=ToolSet::CRC::Get_POParticle(input_pfo);
	std::vector<ReconstructedParticle*> all_photon=ToolSet::CRC::Get_POParticleType(FS,22);

	std::vector<ReconstructedParticle*> isr_photon;
	std::vector<ReconstructedParticle*> photon;
	std::vector<ReconstructedParticle*> non_isr_photon;
	std::vector<ReconstructedParticle*> others_wo_photon;
	std::vector<ReconstructedParticle*> others_wo_isrphoton;


	//only for training, make no use of TMVA::Reader
	if(_output_switch_root&&!_output_switch_collection){

		ToolSet::CChain_Vec       _photon_chain;
		_photon_chain.Set_ChainVec(input_mcs_photon,_navmcpfo,_navpfomc);

		isr_photon=_photon_chain.Get_WeightedRC_MaxEnergy(22);
		non_isr_photon=all_photon-isr_photon;

		others_wo_isrphoton=FS-isr_photon;
		others_wo_photon   =FS-all_photon;

		for (int i = 0; i < isr_photon.size(); i++ ) {
			ReconstructedParticle* mc = isr_photon[i];
			if(mc==NULL){continue;}

			if(mc==0){continue;}
			int output_iso =  IsIsolatedPhoton( mc, FS, info_isr.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}

		for (int i = 0; i < non_isr_photon.size(); i++ ) {
			ReconstructedParticle* mc = non_isr_photon[i];

			int output_iso =  IsIsolatedPhoton( mc, FS, info_normal.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}
	}
	//will calculate MVA output, MVAReader will contribute, and will separate isr and non isr into two trees
	else if(_output_switch_root&&_output_switch_collection){

		ToolSet::CChain_Vec       _photon_chain;
		_photon_chain.Set_ChainVec(input_mcs_photon,_navmcpfo,_navpfomc);


		isr_photon=_photon_chain.Get_WeightedRC_MaxEnergy(22);
		non_isr_photon=all_photon-isr_photon;

		others_wo_isrphoton=FS-isr_photon;
		others_wo_photon   =FS-all_photon;

		for (int i = 0; i < isr_photon.size(); i++ ) {
			ReconstructedParticle* mc = isr_photon[i];
			if(mc==NULL){continue;}

			if(mc==0){continue;}
			int output_iso =  IsIsolatedPhoton( mc, FS, info_isr.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}


		for (int i = 0; i < non_isr_photon.size(); i++ ) {
			ReconstructedParticle* mc = non_isr_photon[i];

			int output_iso =  IsIsolatedPhoton( mc, FS, info_normal.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}
	}
	// only calculate MVA output for all events
	else{
		for (int i = 0; i < all_photon.size(); i++ ) {
			ReconstructedParticle* mc = all_photon[i];

			int output_iso =  IsIsolatedPhoton( mc, FS, info_isr.isophoton);
			if ((output_iso  == 1) || (output_iso == 2) ){
				photon.push_back(mc);
			} 
		}
		non_isr_photon=all_photon-photon;
		others_wo_isrphoton=FS-photon;
		others_wo_photon   =FS-all_photon;
	}

	for(int i=0;i<photon.size();i++){
		_pnum++;
	}
	outputPhotonCol  .Add_Element_RCParticle(photon);
	outputWoPhotonCol.Add_Element_RCParticle(others_wo_isrphoton);

	info_isr.isophoton.Get_PFOParticles(photon);
	info_isr.wophoton.Get_PFOParticles(others_wo_isrphoton);

	info_normal.isophoton.Get_PFOParticles(non_isr_photon);
	info_normal.wophoton.Get_PFOParticles(others_wo_photon);

	return(true);
}


int PandoraIsolatedPhotonFinder::IsIsolatedPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all, PandoraIsolatedPhotonFinder_Information_Single& info) {

	if(pfo->getType()!=22){
		return 0;
	}

	int pos=0;
	if(IsCentralPhoton(pfo)){
		pos=1;
	}
	else if(IsForwardPhoton(pfo)){
		pos=2;
	}
	else{
		return(0);
	}


	bool JISO=false;
	if(_useIsolationCone){
		Get_IsoPhoton_Observable(pfo, all, _minCosConeAngle, info.obv_small);
		Get_IsoPhoton_Observable(pfo, all, _maxCosConeAngle, info.obv_large);


		if(_output_switch_root&&!_output_switch_collection){
			JISO=true;
		}
		else{
			_small_input_energy             =info.obv_small.input_energy.back();
			_small_num_incone_total         =info.obv_small.num_incone_total.back();
			_small_num_incone_charge        =info.obv_small.num_incone_charge.back();
			_small_num_incone_neutral       =info.obv_small.num_incone_neutral.back();
			_small_num_incone_photon        =info.obv_small.num_incone_photon.back();
			_small_num_incone_lepton        =info.obv_small.num_incone_lepton.back();
			_small_num_incone_hadron        =info.obv_small.num_incone_hadron.back();

			_small_cone_energy_total        =info.obv_small.cone_energy_total.back();
			_small_cone_energy_charge       =info.obv_small.cone_energy_charge.back();
			_small_cone_energy_neutral      =info.obv_small.cone_energy_neutral.back();
			_small_cone_energy_photon       =info.obv_small.cone_energy_photon.back();
			_small_cone_energy_lepton       =info.obv_small.cone_energy_lepton.back();
			_small_cone_energy_hadron       =info.obv_small.cone_energy_hadron.back();

			_small_cone_energy_ratio_total  =info.obv_small.cone_energy_ratio_total.back();
			_small_cone_energy_ratio_charge =info.obv_small.cone_energy_ratio_charge.back();
			_small_cone_energy_ratio_neutral=info.obv_small.cone_energy_ratio_neutral.back();
			_small_cone_energy_ratio_photon =info.obv_small.cone_energy_ratio_photon.back();
			_small_cone_energy_ratio_lepton =info.obv_small.cone_energy_ratio_lepton.back();
			_small_cone_energy_ratio_hadron =info.obv_small.cone_energy_ratio_hadron.back();
			_small_cone_costheta            =info.obv_small.cone_costheta.back();

			_large_num_incone_total         =info.obv_large.num_incone_total.back();
			_large_num_incone_charge        =info.obv_large.num_incone_charge.back();
			_large_num_incone_neutral       =info.obv_large.num_incone_neutral.back();
			_large_num_incone_photon        =info.obv_large.num_incone_photon.back();
			_large_num_incone_lepton        =info.obv_large.num_incone_lepton.back();
			_large_num_incone_hadron        =info.obv_large.num_incone_hadron.back();

			_large_cone_energy_total        =info.obv_large.cone_energy_total.back();
			_large_cone_energy_charge       =info.obv_large.cone_energy_charge.back();
			_large_cone_energy_neutral      =info.obv_large.cone_energy_neutral.back();
			_large_cone_energy_photon       =info.obv_large.cone_energy_photon.back();
			_large_cone_energy_lepton       =info.obv_large.cone_energy_lepton.back();
			_large_cone_energy_hadron       =info.obv_large.cone_energy_hadron.back();

			_large_cone_energy_ratio_total  =info.obv_large.cone_energy_ratio_total.back();
			_large_cone_energy_ratio_charge =info.obv_large.cone_energy_ratio_charge.back();
			_large_cone_energy_ratio_neutral=info.obv_large.cone_energy_ratio_neutral.back();
			_large_cone_energy_ratio_photon =info.obv_large.cone_energy_ratio_photon.back();
			_large_cone_energy_ratio_lepton =info.obv_large.cone_energy_ratio_lepton.back();
			_large_cone_energy_ratio_hadron =info.obv_large.cone_energy_ratio_hadron.back();
			_large_cone_costheta            =info.obv_large.cone_costheta.back();

			float mva_output = _reader->EvaluateMVA( "BDTGmethod" );
			info.obv_small.mva_output.push_back(mva_output);
			if(mva_output>_mvaCut){
				JISO=true;
			}
		}

	}
	else{
		JISO=true;
	}


	if (JISO){
		return(pos);
	}

	return -1;
}



void PandoraIsolatedPhotonFinder::Get_IsoPhoton_Observable( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all, float cone_cut, PandoraIsolatedPhotonFinder_Observable& obv) {

	obv.input_energy             .push_back(pfo->getEnergy());
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

	obv.num_incone_total         .push_back(incone_wo_leading_photon.size());
	obv.num_incone_charge        .push_back(incone_charge           .size());
	obv.num_incone_neutral       .push_back(incone_neutral          .size());
	obv.num_incone_photon        .push_back(incone_photon           .size());
	obv.num_incone_lepton        .push_back(incone_lepton           .size());
	obv.num_incone_hadron        .push_back(incone_hadron           .size());

	obv.cone_energy_total        .push_back(sum_incone_total  .E());
	obv.cone_energy_charge       .push_back(sum_incone_charge .E());
	obv.cone_energy_neutral      .push_back(sum_incone_neutral.E());
	obv.cone_energy_photon       .push_back(sum_incone_photon .E());
	obv.cone_energy_lepton       .push_back(sum_incone_lepton .E());
	obv.cone_energy_hadron       .push_back(sum_incone_hadron .E());

	obv.cone_energy_ratio_total  .push_back(obv.input_energy.back() /obv.cone_energy_total.back()   );
	obv.cone_energy_ratio_charge .push_back(obv.cone_energy_charge.back()  /obv.input_energy.back() );
	obv.cone_energy_ratio_neutral.push_back(obv.cone_energy_neutral.back() /obv.input_energy.back() );
	obv.cone_energy_ratio_photon .push_back(obv.cone_energy_photon.back()  /obv.input_energy.back() );
	obv.cone_energy_ratio_lepton .push_back(obv.cone_energy_lepton.back()  /obv.input_energy.back() );
	obv.cone_energy_ratio_hadron .push_back(obv.cone_energy_hadron.back()  /obv.input_energy.back() );

	obv.cone_costheta            .push_back( TMath::Cos(sum_incone_wo_leading_photon.Angle(lorentz_input.Vect())));

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
