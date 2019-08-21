#include "Fram.h"
void Fram(CDraw &para)
{
	//read in the cross section
	ShowMessage(1,"begin to choose analysis mode"); 
	para.time.Begin_Time();

	if (para.flow.begin_object == "Find_Cut" ){
		Analyse_Find_Cut(para);
	}
	else if (para.flow.begin_object == "Complete_Run" ){
		Analyse_Complete(para);
	}
	else if (para.flow.begin_object == "Complete_MVA_Train" ){
		Analyse_Complete_MVA_Train(para);
	}
	else if (para.flow.begin_object == "Complete_MVA_Attach" ){
		Analyse_Complete_MVA_Attach(para);
	}
	else if (para.flow.begin_object == "Full_Pol" ){
		Analyse_Complete_Pol(para);
	}
	else if (para.flow.begin_object == "Complete_Direct_Cut" ){
		Analyse_Complete_Direct_Cut(para);
	}
	else if (para.flow.begin_object == "Complete_Direct_Cut_And_After" ){
		Analyse_Complete_Direct_Cut_And_After(para);
	}
	else if (para.flow.begin_object == "Pre_Cut" ){
		Analyse_Pre_Cut(para);
	}
	else if (para.flow.begin_object == "Direct_Cut" || para.flow.begin_object == "Direct_Cut_ReWeight" ){
		Analyse_Direct_Cut_Pre(para);
	}
	else if (para.flow.begin_object == "MVA_Train" ){
		Analyse_MVA_Train_Pre(para);
	}
	else if (para.flow.begin_object == "MVA_Attach" ){
		Analyse_MVA_Attach_Pre(para);
	}
	else if (para.flow.begin_object == "Sensitivity" ){
		Analyse_Sensitivity_Pre(para);
	}
	else if (para.flow.begin_object == "Complete_Sensitivity" ){
		Analyse_Sensitivity_Complete(para);
	}
	else if (para.flow.begin_object == "Summarize_Sensitivity" ){
		Analyse_Summarize_Sensitivity_Pre(para);
	}
	else if (para.flow.begin_object == "Get_Exclusion_Limit" ){
		Analyse_Get_Exclusion_Limits(para);
	}
	else if (para.flow.begin_object == "Signal_Scan" ){
		Analyse_Signal_Scan_Pre(para);
	}
	else if (para.flow.begin_object == "Summarize_Plot" ){
		Analyse_Summarize_Plot_Pre(para);
	}
	else if (para.flow.begin_object == "Complete_Summarize_Plot" ){
		Analyse_Summarize_Plot_Complete_Pre(para);
	}
	else if (para.flow.begin_object == "Summarize_Cut_Efficiency_Plot" ){
		Analyse_Summarize_Cut_Efficiency_Plot(para);
	}
	else if (para.flow.begin_object == "Summarize_Complete_Cut_Efficiency_Plot" ){
		Analyse_Complete_Summarize_Cut_Efficiency_Plot(para);
	}
	else if (para.flow.begin_object == "Make_Table" ){
		Make_Table_Pre(para);
	}
	else if (para.flow.begin_object == "Make_Efficiency_Plot" ){
		Make_Efficiency_Plot_Pre(para);
	}
	else if (para.flow.begin_object == "Make_Complete_Efficiency_Plot" ){
		Make_Complete_Efficiency_Plot_Pre(para);
	}
	else if (para.flow.begin_object == "Make_Complete_Table" ){
		Make_Complete_Table_Pre(para);
	}
	else{
		ShowMessage(1,"wrong begin_object in control/flow.dat");
		ShowMessage(1,"You chose a wrong begin_object as ", para.flow.begin_object);
		ShowMessage(1,"You Can Choose The Following Operations", "Complete_Run" );
		ShowMessage(2,"", "Complete_MVA_Train" );
		ShowMessage(2,"", "Complete_MVA_Attach" );
		ShowMessage(2,"", "Full_Pol" );
		ShowMessage(2,"", "Complete_Direct_Cut" );
		ShowMessage(2,"", "Complete_Direct_Cut_And_After" );
		ShowMessage(2,"", "Pre_Cut" );
		ShowMessage(2,"", "Direct_Cut" );
		ShowMessage(2,"", "Direct_Cut_ReWeight" );
		ShowMessage(2,"", "MVA_Train" );
		ShowMessage(2,"", "MVA_Attach" );
		ShowMessage(2,"", "Sensitivity" );
		ShowMessage(2,"", "Complete_Sensitivity" );
		ShowMessage(2,"", "Summarize_Sensitivity" );
		ShowMessage(2,"", "Get_Exclusion_Limit" );
		ShowMessage(2,"", "Signal_Scan" );
		ShowMessage(2,"", "Summarize_Plot" );
		ShowMessage(2,"", "Complete_Summarize_Plot" );
		ShowMessage(2,"", "Summarize_Cut_Efficiency_Plot" );
		ShowMessage(2,"", "Summarize_Complete_Cut_Efficiency_Plot" );
		ShowMessage(2,"", "Make_Table" );
		ShowMessage(2,"", "Make_Efficiency_Plot" );
		ShowMessage(2,"", "Make_Complete_Efficiency_Plot" );
		ShowMessage(2,"", "Make_Complete_Table" );
		ShowMessage(2,"", "Find_Cut" );
		return;
	}

	Record_Attach(para);

	ShowMessage(2);
	para.time.Current_Time();
	ShowMessage(2,"For this calculation ", para.flow.begin_object);
	para.time.Time_Interval();

	Record_Close(para);

}




