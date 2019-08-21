#include "PFOLeptonTagging.h"
#include "CMC.h"
using namespace lcio;

int PFOLeptonTagging::analysePOParticle( LCCollection* Input_PFOLeptonCol, LCCollection* Input_PFOWoLeptonCol, 
		PFOLeptonTagging_Output_Collection &NewPFOIsoLeptonCol,
		PFOLeptonTagging_Output_Collection &NewPFOWoIsoLeptonCol, 
		PFOLeptonTagging_Informatio n&info, PFOLeptonTagging_Function_Counter& counter){

	std::vector<ReconstructedParticle*> input_lepton =ToolSet::CRC::Get_POParticle(Input_PFOLeptonCol);
	std::vector<ReconstructedParticle*> input_other  =ToolSet::CRC::Get_POParticle(Input_PFOWoLeptonCol);
	std::vector<ReconstructedParticle*> leps,woleps,in_lep_cone, in_non_iso_cone;

	checkIsoLeptons(input_lepton,input_other,leps,in_lep_cone, in_non_iso_cone,woleps);

	//add into output collections
	NewPFOIsoLeptonCol  .Add_Element_RCParticle(leps);
	NewPFOWoIsoLeptonCol.Add_Element_RCParticle(woleps);

	if(_output_switch_root){
		info.pfo_lepton         .Get_PFOParticles(leps);
		info.pfo_other          .Get_PFOParticles(woleps);
		info.pfo_in_lep_cone    .Get_PFOParticles(in_lep_cone);
		info.pfo_in_non_iso_cone.Get_PFOParticles(in_non_iso_cone);

		TLorentzVector combined_leps =ToolSet::CRC::Get_Sum_To_Lorentz(leps);
		TLorentzVector combined_other=ToolSet::CRC::Get_Sum_To_Lorentz(woleps);

		info.pfo_lepton.obv.visible_energy=combined_leps .M();
		info.pfo_other .obv.visible_energy=combined_other.M();
		counter.pass_all++;
	}

	return(1);
}


void PFOLeptonTagging::checkIsoLeptons(std::vector<ReconstructedParticle*> input_leps, std::vector<ReconstructedParticle*> input_other,  std::vector<ReconstructedParticle*> &IsoLep, std::vector<ReconstructedParticle*> &In_lep_Cone, std::vector<ReconstructedParticle*> &in_non_iso_cone, std::vector<ReconstructedParticle*> &pfo_WO_IsoLep )
{
	std::vector<ReconstructedParticle*> leps      = ToolSet::CRC::Get_POParticleType_Abs(input_leps,_lep_type);
	std::vector<ReconstructedParticle*> leps_left = input_leps - leps;
	std::vector<ReconstructedParticle*> all_other = leps_left + input_other;

	std::vector<ReconstructedParticle*> leps_iso_origin, leps_not_iso;
	ReconstructedParticle*              new_pfo  =NULL;
	std::vector<ReconstructedParticle*> new_other;
	std::vector<ReconstructedParticle*> new_in_cone;

	//  ToolSet::ShowMessage(1,"begin");
	//  ToolSet::ShowMessage(1,"inpug leps",leps);
	int npfo = leps.size();
	for( int i = 0; i < npfo; i++ ){
		//  	ToolSet::ShowMessage(1,"loop i",i);
		bool JIso=IsIsoLep( leps[i], all_other, new_pfo, new_in_cone, new_other);
		if ( JIso){
			if(new_pfo!=NULL){
			////ToolSet::ShowMessage(1,"nevt",_nEvt);
			////ToolSet::ShowMessage(1,"origin pfo",leps[i]);
			////ToolSet::ShowMessage(1,"new_pfo",new_pfo);
			////if(new_in_cone.size()!=0){
			////	ToolSet::ShowMessage(1,"in cone",_nEvt,new_in_cone);
			////}
				IsoLep.push_back(new_pfo);
				leps_iso_origin.push_back(leps[i]);
				all_other = new_other;
				In_lep_Cone+= new_in_cone;
			}
			else{
				ToolSet::ShowMessage(1,"in PFOLeptonTagging::checkIsoLeptons, NULL pointer,  check the code",_nEvt);
			}
		}
		else{
			in_non_iso_cone+=new_in_cone;
		}
	}
	leps_not_iso=leps-leps_iso_origin;

	pfo_WO_IsoLep=new_other+leps_not_iso;

	//  ToolSet::ShowMessage(2);
	//  ToolSet::ShowMessage(1,"IsoLep",IsoLep);
	//  ToolSet::ShowMessage(1,"Wo IsoLep",pfo_WO_IsoLep);
	//  ToolSet::ShowMessage(1,"end");
	return;
}



bool PFOLeptonTagging::IsIsoLep( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> allpfo, ReconstructedParticle* &new_pfo, std::vector<ReconstructedParticle*> &new_in_cone, std::vector<ReconstructedParticle*> &new_all_others) {

	//    ToolSet::ShowMessage(1,"input pfo",pfo);
	if ( !IsCharged(pfo) ){
		return false;
	}
	//  ToolSet::ShowMessage(1,"is charged");

	int leptype= IsLepton(pfo);

	//  ToolSet::ShowMessage(1,"is lepton", leptype);
	if ( leptype==0 ){
		return false;
	}

	if ( _lep_type!=0 ){
		if ( leptype!=_lep_type ){
			return false;
		}
	}


	//  ToolSet::ShowMessage(1,"begin isolation ","");

	// isolation condition
	//
	std::vector<ReconstructedParticle*> incone=ToolSet::CRC::Get_InCone(pfo, allpfo, _maxCosConeAngle);
	if(incone.size()==1){
		//if only input particle -> isolated
		new_pfo = pfo;
		new_all_others=allpfo -pfo;
		return true;
	}


	std::vector<ReconstructedParticle*> leps  =ToolSet::CRC::Get_POParticleType(incone,"lepton");
	std::vector<ReconstructedParticle*> woleps=incone-leps;
	std::vector<ReconstructedParticle*> photon=ToolSet::CRC::Get_POParticleType(woleps,22);
	std::vector<ReconstructedParticle*> wophoton=woleps-photon;


	// in the cone, there are many other particles,  get the cone energy of cone
	std::vector<ReconstructedParticle*> output_other;
	ReconstructedParticle* output_lep;

	if(leps.size()==1){
		bool Jrecover=Get_One_Lepton_Recovery(pfo,leps,photon,wophoton,output_lep);
		if(Jrecover){
			new_pfo = output_lep;
			new_all_others = allpfo - incone;
			new_in_cone = incone;
		}
		else{
			new_pfo = pfo;
			new_all_others = allpfo - pfo;
			new_in_cone = incone;
		}
		return(Jrecover);
	}
	else{
		bool Jrecover=Get_Two_Lepton_Recovery(pfo,leps,photon,wophoton,output_lep,output_other);
		if(Jrecover){
			new_pfo = output_lep;
			new_in_cone = incone-output_other;
			new_all_others = allpfo - new_in_cone;
		}
		else{
			new_pfo = pfo;
			new_all_others = allpfo - pfo;
			new_in_cone = incone-output_other;
		}
		return(Jrecover);
	}

	return false;
}

bool PFOLeptonTagging::Get_One_Lepton_Recovery(ReconstructedParticle* origin_pfo, std::vector<ReconstructedParticle*> leps, std::vector<ReconstructedParticle*> photon, std::vector<ReconstructedParticle*> wo_lep_photon, ReconstructedParticle* &output_lep){
	if(leps.size()!=1){
		return(false);
	}

	if(origin_pfo!=leps[0]){
		return(false);
	}

	std::vector<ReconstructedParticle*> leps_photons=leps+photon;
	std::vector<ReconstructedParticle*> all_wo_leps=photon+wo_lep_photon;
	std::vector<ReconstructedParticle*> all=all_wo_leps+leps;


	TLorentzVector wophoton_incone=ToolSet::CRC::Get_Sum_To_Lorentz(wo_lep_photon);
	TLorentzVector recoveryleps_incone=ToolSet::CRC::Get_Sum_To_Lorentz(leps_photons);

	float wophoton_energy    =wophoton_incone.E();
	float recovery_energy=recoveryleps_incone.E();
	if(recovery_energy/(recovery_energy+wophoton_energy)<_ConeEnergyRatio){
		return false;
	}

	TLorentzVector photonvector=ToolSet::CRC::Get_Sum_To_Lorentz(photon);
	if(photonvector.E()>origin_pfo->getEnergy()/2){
		return(false);
	}

	output_lep = ToolSet::CRC::Get_Sum(all); 
	return true;
}


bool PFOLeptonTagging::Get_Two_Lepton_Recovery(ReconstructedParticle* origin_pfo, std::vector<ReconstructedParticle*> leps, std::vector<ReconstructedParticle*> photon, std::vector<ReconstructedParticle*> wo_lep_photon, ReconstructedParticle* &output_lep, std::vector<ReconstructedParticle*> &output_other){
	if(leps.size()<2){
		return(false);
	}

	std::vector<ReconstructedParticle*> leps_photons=leps+photon;
	std::vector<ReconstructedParticle*> all_wo_leps=photon+wo_lep_photon;
	std::vector<ReconstructedParticle*> all=all_wo_leps+leps;

	std::sort(leps.begin(),leps.end(),ToolSet::CRC::Compare_as_E);
	// origin pfo should be leading/subleading lepton
	int origin_pos=0;
	if(origin_pfo==leps[0]){
		origin_pos = 0;
	}
	else if(origin_pfo==leps[1]){
		origin_pos = 1;
	}
	else{
		return false;
	}

	leps.resize(2);
	leps_photons.clear();
	leps_photons=leps+photon;

	TLorentzVector wophoton_incone=ToolSet::CRC::Get_Sum_To_Lorentz(wo_lep_photon);
	TLorentzVector recoveryleps_incone=ToolSet::CRC::Get_Sum_To_Lorentz(leps_photons);

	float wophoton_energy    =wophoton_incone.E();
	float recovery_energy=recoveryleps_incone.E();


	if(recovery_energy/(recovery_energy+wophoton_energy)<_ConeEnergyRatio){
		return(false);
	}


	// leps + photons domain
	// set a new cone, whose radii = the leptons' angle distance * lepton's energy ratio, 
	// recover the photon in this lepton cone.
	TVector3 P_1( leps[0]->getMomentum() );

	TVector3 P_2( leps[1]->getMomentum() );

	float new_coneangle= P_1.Dot( P_2)/(P_1.Mag()*P_2.Mag());
	float cone_ratio   = leps[origin_pos]->getEnergy()/(leps[0]->getEnergy()+leps[1]->getEnergy());

	std::vector<ReconstructedParticle*> new_incone=ToolSet::CRC::Get_InCone(origin_pfo, all, new_coneangle*cone_ratio);

	std::vector<ReconstructedParticle*> new_left  =all-new_incone;
	std::vector<ReconstructedParticle*> new_leps  =ToolSet::CRC::Get_POParticleType(new_incone,"lepton");
	std::vector<ReconstructedParticle*> new_woleps=new_incone-new_leps;
	std::vector<ReconstructedParticle*> new_photon=ToolSet::CRC::Get_POParticleType(new_woleps,22);
	std::vector<ReconstructedParticle*> new_wophoton=new_woleps-new_photon;
	if(new_wophoton.size()!=0){
		return(false);
	}
	TLorentzVector newphotonvector=ToolSet::CRC::Get_Sum_To_Lorentz(new_photon);
	if(newphotonvector.E()>origin_pfo->getEnergy()/2){
		return(false);
	}


	output_lep  =ToolSet::CRC::Get_Sum(new_incone);
	output_other= new_left;
	return(true);

}



bool PFOLeptonTagging::IsCharged( ReconstructedParticle* pfo ) {
	if ( pfo->getCharge() == 0 ) return false;
	return true;
}



int PFOLeptonTagging::IsLepton( ReconstructedParticle* pfo) {

	bool Jmin_E=false;
	bool Jcostheta=false;
	int pdg=std::abs(pfo->getType());
	if(pdg!=11&&pdg!=13){
		return(0);
	}
	if( pfo->getEnergy()> _MinEnergy){
		return(pdg);
	}
	else{
		return(0);
	}

}


