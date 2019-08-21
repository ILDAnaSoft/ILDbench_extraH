#include "Analyse_Summarize_Plot.h"


void Analyse_Summarize_Plot_Complete_Pre(CDraw &para){

	std::vector<std::vector<std::string> >sig_name;
			


	//bool only_lr                        = false;
    //if(para.scenario.Run_Ratio_Vec().size()==2){
    //	only_lr =true;
    //}
////for(int i=-1;i<2;i=i+2){
////	for(int j=-1;j<2;j=j+2){
////		if(only_lr){
////			if(i==j){continue;}
////		}
	int i=-1;
	int j=1;
			para.path.event_file              = para.default_path.event_file   + Int_to_String(i) + Int_to_String(j);
			para.path.output_file             = para.default_path.output_file  + Int_to_String(i) + Int_to_String(j);
			para.path.single_plot             = para.default_path.single_plot  + Int_to_String(i) + Int_to_String(j);
			para.path.combine_plot            = para.default_path.combine_plot + Int_to_String(i) + Int_to_String(j);
			para.path.horizontal_summary_plot = para.default_path.horizontal_summary_plot + Int_to_String(i) + Int_to_String(j);

			std::vector<std::string> sig_name_temp;
			AFile file_name;
			for(int i=0;i<para.signal_scan.property_num;i++){
				para.flow.signal_property= para.signal_scan.properties[i];
				get_file_name(para,file_name);
				if(para.flow.plot_object=="final_cut"){
					sig_name_temp.push_back(file_name.output_total.CUT_file);
				}
				else if(para.flow.plot_object=="before_cut"){
					ShowMessage(2,file_name.output[0].CUT_file);
					ShowMessage(2,"mass",para.flow.signal_property);
					sig_name_temp.push_back(file_name.output[0].CUT_file);
				}
				else if(para.flow.plot_object=="origin_cut"){
					ShowMessage(2,file_name.output[0].MVA_file);
					ShowMessage(2,"mass",para.flow.signal_property);
					sig_name_temp.push_back(file_name.output[0].MVA_file);
				}
			}
			get_file_name(para,file_name);
			if(para.flow.plot_object=="before_cut"){
				for(unsigned int i=1;i<file_name.output.size();i++){
					ShowMessage(2,"bkg",file_name.output[i].CUT_file);
					sig_name_temp.push_back(file_name.output[i].CUT_file);
				}
			}
			if(para.flow.plot_object=="origin_cut"){
		    	for(unsigned int i=1;i<file_name.output.size();i++){
		    		ShowMessage(2,"bkg",file_name.output[i].MVA_file);
		    		sig_name_temp.push_back(file_name.output[i].MVA_file);
		    	}
			}
			sig_name.push_back(sig_name_temp);
////	}
////}

	para.path= para.default_path;
	get_file_name(para,file_name);


	Analyse_Summarize_Plot_Complete(para,sig_name,file_name);

}





void Analyse_Summarize_Plot_Complete(CDraw &para, std::vector<std::vector<std::string> >&sig_name, AFile& file_name){

	int _colornum[100];
	int _stylenum[50];
	(void) _stylenum;
	_colornum[0] =kRed-2;
	_colornum[1] =kRed;
	_colornum[2] =kRed+2;
	_colornum[3] =kBlue-2;
	_colornum[4] =kBlue;
	_colornum[5] =kBlue+2;
	_colornum[6] =kMagenta-2;
	_colornum[7] =kMagenta;
	_colornum[8] =kMagenta+2;
	_colornum[9] =kCyan-2;
	_colornum[10]=kCyan;
	_colornum[11]=kCyan+2;
	_colornum[12]=kOrange-2;
	_colornum[13]=kOrange;
	_colornum[14]=kOrange+2;
	_colornum[15]=kPink-2;
	_colornum[16]=kPink;
	_colornum[17]=kPink+2;
	_colornum[18]=kAzure;
	_colornum[19]=kViolet;
	_colornum[20]=kSpring-3;
	_colornum[21]=kSpring-2;
	_colornum[22]=kSpring-1;
	_colornum[23]=kSpring;
	_colornum[24]=kSpring+1;
	_colornum[25]=kSpring+2;
	_colornum[26]=kSpring+3;
	_colornum[27]=kGreen-3;
	_colornum[28]=kGreen-2;
	_colornum[29]=kGreen-1;
	_colornum[30]=kGreen;
	_colornum[31]=kGreen+1;
	_colornum[32]=kGreen+2;
	_colornum[33]=kGreen+3;
	_colornum[34]=kTeal-3;
	_colornum[35]=kTeal-2;
	_colornum[36]=kTeal-1;
	_colornum[37]=kTeal;
	_colornum[38]=kTeal+1;
	_colornum[39]=kTeal+2;
	_colornum[40]=kTeal+3;
	for(int i=41;i<100;i++){
		_colornum[i]=10;
	}

	_stylenum[0] =1 ;
	_stylenum[1] =7 ;
	_stylenum[2] =3 ;
	_stylenum[3] =7 ;
	_stylenum[4] =3 ;
	_stylenum[5] =5 ;
	_stylenum[6] =7 ;
	_stylenum[7] =8 ;
	_stylenum[8] =9 ;
	_stylenum[9] =10;
	for(int i=10;i<50;i++){
		_stylenum[i]=10;
	}
	int num_temp=sig_name.size();

	APlot plot;

	for(unsigned int k=0;k<para.var.var.size();k++){
    	if(k!=3){
    		continue;
    	}
		Avariable info=para.var.var[k];
		if(info.plot_switch){

			std::string cname=info.c_name+"_"+Int_to_String(k);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);
			std::string leg_name  = "e^{+}e^{-}#rightarrow  #mu^{+}#mu^{-}h";
			std::string x_name    = info.x_name;
			std::string y_name    = info.y_name;
			if(info.norm_switch){
				y_name = "Normalized "+y_name;
			}
			std::string axis_name = info.title_name;
			int x_bin             = info.x_bin;
			float x_min           = info.x_min;
			float x_max           = info.x_max;
			std::vector<TH1F*> hvariable;
			hvariable.resize(sig_name[0].size());
			std::string title_name= info.title_name;
////		for(unsigned int i=0;i<sig_name[0].size();i++){
////			std::string hname=title_name+"_"+Int_to_String(i);
////			hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max);
////			hvariable[i]->SetTitle(hname.c_str());
////		}
			for(int i=0;i<para.signal_scan.property_num;i++){
				std::string hname=title_name+"_"+Int_to_String(i);
				hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max);
				hvariable[i]->SetTitle(hname.c_str());
			}
			for(unsigned int i=para.signal_scan.property_num;i<sig_name[0].size();i++){
				std::string hname=title_name+"_"+Int_to_String(i);
				hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max);
				hvariable[i]->SetTitle(hname.c_str());
			}

			auto leg = new TLegend(info.leg_left,info.leg_up,info.leg_right,info.leg_down);
			leg->Clear();
			leg->SetHeader(leg_name.c_str(),"l"); 
			for(int j=0;j<num_temp;j++){
				int num=sig_name[j].size();
				std::vector<TFile*> in_file;
				for(int i=0;i<num;i++){
					TFile* in_file_tmp=new TFile(sig_name[j][i].c_str());
					in_file.push_back(in_file_tmp);
					TTree *MyLCTuple; 
					if(para.flow.plot_object=="final_cut"){
						MyLCTuple=(TTree*)in_file[i]->Get("sig");
					}
					else{
						MyLCTuple=(TTree*)in_file[i]->Get(para.file.root_head_name.c_str());
					}

					int nevent = MyLCTuple->GetEntries();
					float variable;
					double weight;
					MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);
					MyLCTuple->SetBranchAddress("weight", &weight);



					for(int event=0;event<nevent;event++){
						MyLCTuple->GetEntry(event);
						hvariable[i]->Fill(variable,weight);
					}

					if(j==num_temp-1){
						if(i<para.signal_scan.property_num){
							//plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],_stylenum[i]);
							//plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],0);
							//plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],0);
            			    hvariable[i]->SetLineColor(_colornum[i]);
							hvariable[i]->SetFillColor(_colornum[i]);
							std::string legname=para.signal_scan.properties[i]+" GeV";
								leg->AddEntry(hvariable[i],legname.c_str(),"l");
						}
						else{
							//int bkg_color=i-para.mass_scan.mass_num+20;
							int bkg_color=28;
							//plot.Set_Line_Style(para,info,hvariable[i],_colornum[bkg_color],0);
						    hvariable[i]->SetLineColor(_colornum[bkg_color]);
						}
					}
				}
				if(j==num_temp-1){
					leg->AddEntry(hvariable[num-1],"SM backgrounds","f");
				}
			}


			int i = 8;
			THStack *ss = new THStack();
			if(info.log_switch){
				gPad->SetLogy();
				ss->SetMinimum(info.log_min);
			}
			for(unsigned int j=para.signal_scan.property_num;j<sig_name[0].size();j++){
				//int bkg_color=j-para.mass_scan.mass_num+20;
				int bkg_color=28;
				if(hvariable[j]->GetEntries()!=0){
					hvariable[j]->SetFillColor(_colornum[bkg_color]);
					ss->Add(hvariable[j]);
				}
			}
			if(hvariable[i]->GetEntries()!=0){
				ss->Add(hvariable[i]);
			}
			ss->Draw("hist");
			ss->GetYaxis()->SetTitle(y_name.c_str());
			ss->GetXaxis()->SetTitle(x_name.c_str());

			//for(int i=para.mass_scan.mass_num-1;i>0;i--){
			for(int i=0;i<para.signal_scan.property_num;i++){
				if(i==8){
					continue;
				}
				THStack *ss = new THStack();
				if(info.log_switch){
					gPad->SetLogy();
					ss->SetMinimum(info.log_min);
				}
				for(unsigned int j=para.signal_scan.property_num;j<sig_name[0].size();j++){
					//int bkg_color=j-para.mass_scan.mass_num+20;
					int bkg_color=28;
					if(hvariable[j]->GetEntries()!=0){
						hvariable[j]->SetFillColor(_colornum[bkg_color]);
						ss->Add(hvariable[j]);
					}
				}
				if(hvariable[i]->GetEntries()!=0){
					ss->Add(hvariable[i]);
				}
				ss->Draw("hist,Same");
				ss->GetYaxis()->SetTitle(y_name.c_str());
				ss->GetXaxis()->SetTitle(x_name.c_str());
			}
			leg->SetMargin(0.3);
			leg->Draw();

			plot.Print_Plot(info, file_name.folder[6]+info.title_name+"_summary.png");

			delete info.c;
		}
	}


	return;
}

void Analyse_Summarize_Plot_Pre(CDraw &para){
	ShowMessage(2,"begin summarize plots");
	AFile file_name;
	std::vector<std::string> sig_name;
	std::vector<std::string> file_short_name;

	get_file_name(para,file_name);
	if(para.flow.plot_object=="before_cut"){
    	for(int i=0;i<file_name.output_sort.Sort_Num();i++){
			for(int j=0;j<file_name.output_sort.Sub_Sort_Num(i);j++){
    			std::string a_sort_name=file_name.output_sort.Sub_Sort_Name(i,j);
    			std::string b_sort_name=file_name.input_sort.Default_Sub_Sort_Name(i,j);
				if(Is_File_Exist(a_sort_name)){
					sig_name.push_back(a_sort_name);
					file_short_name.push_back(b_sort_name);
				}
			}
    	}
	}

	Analyse_Summarize_Plot(para,sig_name,file_short_name,file_name);

}





void Analyse_Summarize_Plot(CDraw &para, std::vector<std::string> &sig_name, std::vector<std::string> &file_short_name,AFile& file_name){

	int _colornum[100];
	int _stylenum[50];
	(void) _stylenum;
	_colornum[0] =kRed-2;
	_colornum[1] =kRed;
	_colornum[2] =kRed+2;
	_colornum[3] =kBlue-2;
	_colornum[4] =kBlue;
	_colornum[5] =kBlue+2;
	_colornum[6] =kMagenta-2;
	_colornum[7] =kMagenta;
	_colornum[8] =kMagenta+2;
	_colornum[9] =kCyan-2;
	_colornum[10]=kCyan;
	_colornum[11]=kCyan+2;
	_colornum[12]=kTeal-2;
	_colornum[13]=kTeal-1;
	_colornum[14]=kTeal;
	_colornum[15]=kTeal+1;
	_colornum[16]=kTeal+2;
	_colornum[17]=kAzure-2;
	_colornum[18]=kAzure;
	_colornum[19]=kViolet;
	_colornum[20]=kSpring-3;
	_colornum[21]=kSpring-2;
	_colornum[22]=kSpring-1;
	_colornum[23]=kSpring;
	_colornum[24]=kSpring+1;
	_colornum[25]=kSpring+2;
	_colornum[26]=kSpring+3;
	_colornum[27]=kGreen-3;
	_colornum[28]=kGreen-2;
	_colornum[29]=kGreen-1;
	_colornum[30]=kGreen;
	_colornum[31]=kGreen+1;
	_colornum[32]=kGreen+2;
	_colornum[33]=kGreen+3;
	_colornum[34]=kOrange-3;
	_colornum[35]=kOrange-2;
	_colornum[36]=kOrange-1;
	_colornum[37]=kOrange;
	_colornum[38]=kOrange+1;
	_colornum[39]=kOrange+2;
	_colornum[40]=kOrange+3;
	for(int i=41;i<100;i++){
		_colornum[i]=kRed;
	}


	_stylenum[0] =1 ;
	_stylenum[1] =7 ;
	_stylenum[2] =3 ;
	_stylenum[3] =7 ;
	_stylenum[4] =3 ;
	_stylenum[5] =5 ;
	_stylenum[6] =7 ;
	_stylenum[7] =8 ;
	_stylenum[8] =9 ;
	_stylenum[9] =10;
	for(int i=10;i<50;i++){
		_stylenum[i]=10;
	}
	int num=sig_name.size();

	APlot plot;

	for(unsigned int k=0;k<para.var.var.size();k++){
    	if(k!=3){
    		continue;
    	}
		Avariable info=para.var.var[k];
		if(info.plot_switch){
			std::vector<TFile*> in_file;
			for(int i=0;i<num;i++){
				ShowMessage(2,"bkg",sig_name[i]);
				TFile* in_file_tmp=new TFile(sig_name[i].c_str());
				in_file.push_back(in_file_tmp);
			}

			std::string cname=info.c_name+"_"+Int_to_String(k);
			info.c=new TCanvas(cname.c_str()," ",info.c_width,info.c_height);
			std::vector<TH1F*> hvariable;
			std::string title_name= info.title_name;
			//std::string leg_name  = info.latex_name+"  distribution";
			std::string leg_name  = "e^{+}e^{-}#rightarrow  #mu^{+}#mu^{-}h";
			std::string x_name    = info.x_name;
			std::string y_name    = info.y_name;
			if(info.norm_switch){
				y_name = "Normalized "+y_name;
			}
			std::string axis_name = info.title_name;
			int x_bin             = info.x_bin;
			float x_min           = info.x_min;
			float x_max           = info.x_max;

			auto leg = new TLegend(info.leg_left,info.leg_up,info.leg_right,info.leg_down);
			leg->Clear();
			leg->SetHeader(leg_name.c_str(),"l"); 
			for(int i=0;i<num;i++){
				TTree *MyLCTuple; 
				if(para.flow.plot_object=="final_cut"){
					MyLCTuple=(TTree*)in_file[i]->Get("sig");
				}
				else{
					MyLCTuple=(TTree*)in_file[i]->Get(para.file.root_head_name.c_str());
				}

				int nevent = MyLCTuple->GetEntries();
			    if(nevent==0){
			    	continue;
			    }
				float variable;
				double weight;
				MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);
				MyLCTuple->SetBranchAddress("weight", &weight);

				std::string hname=title_name+"_"+Int_to_String(i);
				hvariable.push_back(new TH1F(hname.c_str(),title_name.c_str(),x_bin,x_min,x_max));
				hvariable.back()->SetTitle(hname.c_str());


				for(int event=0;event<nevent;event++){
					MyLCTuple->GetEntry(event);
					hvariable.back()->Fill(variable,weight);
				}

////			if(i<para.mass_scan.mass_num){
////				//plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],_stylenum[i]);
////				//plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],0);
////				//plot.Set_Line_Style(para,info,hvariable[i],_colornum[i],0);
////                hvariable.back()->SetLineColor(kWhite);
////				hvariable.back()->SetFillColor(kWhite);
////            ////hvariable[i]->SetLineColor(_colornum[i]);
////			////hvariable[i]->SetFillColor(_colornum[i]);
////				std::string legname=Float_to_String(para.mass_scan.mass[i])+" GeV";
////				leg->AddEntry(hvariable[i],legname.c_str(),"l");
////			}
////			else{
					//int bkg_color=i-para.mass_scan.mass_num+2;
					int bkg_color=i*3+1;
					//int bkg_color=28;
					//plot.Set_Line_Style(para,info,hvariable.back(),_colornum[bkg_color],0);
				if(hvariable.back()->GetEntries()!=0){
				    hvariable.back()->SetLineColor(_colornum[bkg_color]);
				    hvariable.back()->SetFillColor(_colornum[bkg_color]);
					leg->AddEntry(hvariable.back(),file_short_name[i].c_str(),"f");
				}
			}
  			//leg->AddEntry(hvariable.back(),"SM backgrounds","f");


			//int i = 0;
			THStack *ss = new THStack();
			if(info.log_switch){
				gPad->SetLogy();
				ss->SetMinimum(info.log_min);
			}
			//for(int j=para.mass_scan.mass_num;j<hvariable.size();j++){
			for(unsigned int j=0;j<hvariable.size();j++){
				//int bkg_color=j-para.mass_scan.mass_num+20;
				//int bkg_color=j;
				//int bkg_color=28;
				if(hvariable[j]->GetEntries()!=0){
////				if(j==0){
////					hvariable[j]->SetFillColor(kWhite);
////				}
////				else{
////					//hvariable[j]->SetFillColor(_colornum[bkg_color]);
					ss->Add(hvariable[j]);
////				}
					ShowMessage(2,"hvariable is",hvariable[j]->GetName());
				}
				else{
					ShowMessage(2,"hvariable is 0");
				}
			}
		////if(hvariable[i]->GetEntries()!=0){
		////	ss->Add(hvariable[i]);
		////}
			ss->Draw("hist");
			ss->GetYaxis()->SetTitle(y_name.c_str());
			ss->GetXaxis()->SetTitle(x_name.c_str());

			//for(int i=para.mass_scan.mass_num-1;i>0;i--){
		////for(int i=0;i<para.mass_scan.mass_num;i++){
		////	if(i==0){
		////		continue;
		////	}
		////	THStack *ss = new THStack();
		////	if(info.log_switch){
		////		gPad->SetLogy();
		////		ss->SetMinimum(info.log_min);
		////	}
		////	for(int j=para.mass_scan.mass_num;j<num;j++){
		////		int bkg_color=j-para.mass_scan.mass_num+20;
		////		//int bkg_color=28;
		////		if(hvariable[j]->GetEntries()!=0){
		////			hvariable[j]->SetFillColor(_colornum[bkg_color]);
		////			ss->Add(hvariable[j]);
		////		}
		////	}
		////	if(hvariable[i]->GetEntries()!=0){
		////		ss->Add(hvariable[i]);
		////	}
		////	ss->Draw("hist,Same");
		////	ss->GetYaxis()->SetTitle(y_name.c_str());
		////	ss->GetXaxis()->SetTitle(x_name.c_str());
		////}
			leg->SetMargin(0.3);
			leg->Draw();

			plot.Print_Plot(info, file_name.folder[6]+info.title_name+"_summary.png");

			delete info.c;
		}
	}


	return;
}

