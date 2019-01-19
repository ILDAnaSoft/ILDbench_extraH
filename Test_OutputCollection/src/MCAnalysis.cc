#include "Test_OutputCollection.h"
bool Test_OutputCollection::analyseMCParticle ( LCCollection* MCs_col1,LCCollection* MCs_col2,  Test_OutputCollection_Information_Single &info1,Test_OutputCollection_Information_Single &info2,  Test_OutputCollection_Function_Counter& counter1,  Test_OutputCollection_Function_Counter& counter2){
	//generate all basic sorts 
	if(MCs_col1!=0){
		std::vector<MCParticle*> MCs1          =ToolSet::CMC::Get_MCParticle(MCs_col1);
		
		TLorentzVector sum_mcs1=ToolSet::CMC::Get_Sum_To_Lorentz(MCs1);
		TLorentzVector inv_mcs1=ToolSet::CMC::Get_InVisible_To_Lorentz(MCs1);
		info1.obv.visible_energy  =sum_mcs1.E();
		info1.obv.invisible_energy=inv_mcs1.E();
		info1.Get_MCParticles(MCs1);
		counter1.pass_all++;
	}


	if(MCs_col2!=0){
		std::vector<MCParticle*> MCs2          =ToolSet::CMC::Get_MCParticle(MCs_col2);
		
		TLorentzVector sum_mcs2=ToolSet::CMC::Get_Sum_To_Lorentz(MCs2);
		TLorentzVector inv_mcs2=ToolSet::CMC::Get_InVisible_To_Lorentz(MCs2);
		info2.obv.visible_energy  =sum_mcs2.E();
		info2.obv.invisible_energy=inv_mcs2.E();
		info2.Get_MCParticles(MCs2);
		counter2.pass_all++;
	}
	return(true);
}



