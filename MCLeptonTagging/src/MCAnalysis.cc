#include "MCLeptonTagging.h"


bool MCLeptonTagging::analyseMCParticle( LCCollection* inputmcCol, MCLeptonTagging_Output_Collection &outputLeptonCol,MCLeptonTagging_Output_Collection &outputWoleptonCol, MCLeptonTagging_Information_Single &info, MCLeptonTagging_Function_Counter &counter){
	std::vector<MCParticle*> MCs =ToolSet::CMC::Get_MCParticle(inputmcCol);
	std::vector<MCParticle*> leps,woleps;

	checkIsoLeptons(MCs,leps,woleps);

	outputLeptonCol  .Add_Element_MCParticle(leps);
	outputWoleptonCol.Add_Element_MCParticle(woleps);

	if(_output_switch_root){
		info.Get_MCParticles(leps);
////	ToolSet::ShowMessage(1,"leps",leps);
		TLorentzVector combined_leps=ToolSet::CMC::Get_Sum_To_Lorentz(leps);
////	ToolSet::ShowMessage(1,"combined",combined_leps);
		info.obv.visible_energy=combined_leps.M();
		counter.pass_all++;
	}

	return(true);
}


void MCLeptonTagging::checkIsoLeptons(std::vector<MCParticle*> input, std::vector<MCParticle*> &IsoLep, std::vector<MCParticle*> &mcs_WO_IsoLep )
{
	std::vector<MCParticle*> leps     =ToolSet::CMC::Get_MCParticleType_Abs(input,_lep_type);
////ToolSet::ShowMessage(1,"origin leps",leps);
	TLorentzVector combined_leps=ToolSet::CMC::Get_Sum_To_Lorentz(leps);
////ToolSet::ShowMessage(1,"origin combined",combined_leps);
	std::vector<MCParticle*> leps_iso_origin, leps_not_iso;
	MCParticle*              new_mcs  ;
	std::vector<MCParticle*> new_other;
	int nmcs = leps.size();


//  ToolSet::ShowMessage(1,"begin");
//  ToolSet::ShowMessage(1,"inpug leps",leps);
    for( int i = 0; i < nmcs; i++ ){
//  	ToolSet::ShowMessage(1,"loop i",i);
    	if ( IsIsoLep( leps[i], input,new_mcs,new_other)){
    		IsoLep.push_back(new_mcs);
    		leps_iso_origin.push_back(input[i]);
    		input = new_other;
    	}
    }
    leps_not_iso=leps-leps_iso_origin;

    mcs_WO_IsoLep=new_other+leps_not_iso;


//  ToolSet::ShowMessage(2);
//  ToolSet::ShowMessage(1,"IsoLep",IsoLep);
//  ToolSet::ShowMessage(1,"Wo IsoLep",mcs_WO_IsoLep);
//  ToolSet::ShowMessage(1,"end");
	return;
}



bool MCLeptonTagging::IsIsoLep( MCParticle* mcs, std::vector<MCParticle*> allmcs, MCParticle* &new_mcs, std::vector<MCParticle*> &new_all_others) {

//    ToolSet::ShowMessage(1,"input mcs",mcs);
    if ( !IsCharged(mcs) ){
    	return false;
    }
//  ToolSet::ShowMessage(1,"is charged");

    int leptype= IsLepton(mcs);

//  ToolSet::ShowMessage(1,"is lepton", leptype);
    if ( leptype==0 ){
    	return false;
    }

//  ToolSet::ShowMessage(1,"lepton type",_lep_type);
    if ( _lep_type!=0 ){
    	if ( leptype!=_lep_type ){
    		return false;
    	}
    }


//  ToolSet::ShowMessage(1,"begin isolation ","");

    // isolation condition
    //
    std::vector<MCParticle*> incone=ToolSet::CMC::Get_InCone(mcs, allmcs, _maxCosConeAngle);
//    ToolSet::ShowMessage(1,"in cone",incone);
	if(incone.size()==1){
		//if only input particle -> isolated
		new_mcs = mcs;
		new_all_others=allmcs;
		return true;
	}


	std::vector<MCParticle*> leps  =ToolSet::CMC::Get_MCParticleType(incone,"lepton");
	std::vector<MCParticle*> woleps=incone-leps;
	std::vector<MCParticle*> photon=ToolSet::CMC::Get_MCParticleType(woleps,22);
	std::vector<MCParticle*> wophoton=woleps-photon;
	std::vector<MCParticle*> recovery_leps=leps+photon;


	if(wophoton.size()==0){
		// in the cone, only has leptons, or leptons+photons
		if(leps.size()==1){
			// if only 1 lepton + n photons,  recover a new lepton, which = this lepton + photons
			new_mcs=ToolSet::CMC::Get_Sum(recovery_leps);
			new_all_others = allmcs;
			return true;
		}
		else{
			// if has 2 or more leptons + n photons,  
			// find the energetic leading lepton and subleading lepton, if current lepton doesn't belongs to these two lepton, it may radiated from others
			// if the current lepton is one of the two most energetic leptons, then set a new cone, whose radii = half of the leptons' angle distance, 
			// recover the photon in this lepton cone.
			std::sort(leps.begin(),leps.end(),ToolSet::CMC::Compare_as_E);
			if(mcs!=leps[0]&&mcs!=leps[1]){
				return false;
			}

			TVector3 P_1( leps[0]->getMomentum() );

			TVector3 P_2( leps[1]->getMomentum() );

			float new_coneangle= P_1.Dot( P_2)/(P_1.Mag()*P_2.Mag());
			std::vector<MCParticle*> new_incone=ToolSet::CMC::Get_InCone(mcs, incone, new_coneangle);
			new_mcs=ToolSet::CMC::Get_Sum(new_incone);

			std::vector<MCParticle*> new_left=incone-new_incone;
			new_all_others = allmcs+new_left;
			return true;
		}
	}

	// in the cone, there are many other particles,  get the cone energy of cone
	if(leps.size()==1){
		// if only 1 lepton, lepton +photon energy is the domain -> isolated
		TLorentzVector wophoton_incone=ToolSet::CMC::Get_Sum_To_Lorentz(wophoton);
		TLorentzVector recoveryleps_incone=ToolSet::CMC::Get_Sum_To_Lorentz(recovery_leps);

		float wophoton_energy    =wophoton_incone.E();
		float recovery_energy=recoveryleps_incone.E();
		if(recovery_energy/(recovery_energy+wophoton_energy)>_ConeEnergyRatio){
			new_mcs = ToolSet::CMC::Get_Sum(incone); 
			new_all_others= allmcs; 
			return true;
		}
	}
	else{
		// if has 2 or more leptons   
		// find the energetic leading lepton and subleading lepton, if current lepton doesn't belongs to these two lepton, it may radiated from others
		// if the current lepton is one of the two most energetic leptons, then need the first two leptons+photons energy domain in the cone.
		std::sort(leps.begin(),leps.end(),ToolSet::CMC::Compare_as_E);
		if(mcs!=leps[0]&&mcs!=leps[1]){
			return false;
		}

		leps.resize(2);
		recovery_leps.clear();
		recovery_leps=leps+photon;

		TLorentzVector wophoton_incone=ToolSet::CMC::Get_Sum_To_Lorentz(wophoton);
		TLorentzVector recoveryleps_incone=ToolSet::CMC::Get_Sum_To_Lorentz(recovery_leps);

		float wophoton_energy    =wophoton_incone.E();
		float recovery_energy=recoveryleps_incone.E();


		if(recovery_energy/(recovery_energy+wophoton_energy)>_ConeEnergyRatio){
		// set a new cone, whose radii = half of the leptons' angle distance, 
		// recover the photon in this lepton cone.
			TVector3 P_1( leps[0]->getMomentum() );

			TVector3 P_2( leps[1]->getMomentum() );

			float new_coneangle= P_1.Dot( P_2)/(P_1.Mag()*P_2.Mag());
			std::vector<MCParticle*> new_incone=ToolSet::CMC::Get_InCone(mcs, incone, new_coneangle);
			new_mcs=ToolSet::CMC::Get_Sum(new_incone);

			std::vector<MCParticle*> new_left=incone-new_incone;
			new_all_others = allmcs+new_left;
			return true;
		}
	}

	return false;

}



bool MCLeptonTagging::IsCharged( MCParticle* mcs ) {
	if ( mcs->getCharge() == 0 ) return false;
	return true;
}



int MCLeptonTagging::IsLepton( MCParticle* mcs) {

	bool Jmin_E=false;
	bool Jcostheta=false;
	int pdg=std::abs(mcs->getPDG());
	if(pdg!=11&&pdg!=13){
		return(0);
	}
	if( mcs->getEnergy()> _MinEnergy){
		return(pdg);
	}
	else{
		return(0);
	}

}


