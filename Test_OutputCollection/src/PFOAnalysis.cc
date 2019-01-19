#include "Test_OutputCollection.h"
bool Test_OutputCollection::analysePFOParticle(LCCollection* PFO_col1,LCCollection* PFO_col2,  Test_OutputCollection_Information_Single &info1,Test_OutputCollection_Information_Single &info2,  Test_OutputCollection_Function_Counter& counter1,  Test_OutputCollection_Function_Counter& counter2){

    //data prepared
	
	if(PFO_col1!=0){
		std::vector<ReconstructedParticle*> pfo1 = ToolSet::CRC::Get_POParticle(PFO_col1);
		ToolSet::ShowMessage(2,"pfo1",_nEvt,pfo1);
		
		TLorentzVector sum_pfo1=ToolSet::CRC::Get_Sum_To_Lorentz(pfo1);
		TLorentzVector inv_pfo1=ToolSet::CRC::Get_InVisible_To_Lorentz(pfo1);
		info1.obv.visible_energy  =sum_pfo1.E();
		info1.obv.invisible_energy=inv_pfo1.E();
		info1.Get_PFOParticles(pfo1);
		counter1.pass_all++ ;
	}

	if(PFO_col2!=0){
		std::vector<ReconstructedParticle*> pfo2 = ToolSet::CRC::Get_POParticle(PFO_col2);
		ToolSet::ShowMessage(2,"pfo2",pfo2);
		
		TLorentzVector sum_pfo2=ToolSet::CRC::Get_Sum_To_Lorentz(pfo2);
		TLorentzVector inv_pfo2=ToolSet::CRC::Get_InVisible_To_Lorentz(pfo2);
		info2.obv.visible_energy  =sum_pfo2.E();
		info2.obv.invisible_energy=inv_pfo2.E();
		info2.Get_PFOParticles(pfo2);
		counter2.pass_all++ ;
	}
	return(true);
}


