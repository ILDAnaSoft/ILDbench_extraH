#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitter.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH3.h"
#include "THStack.h"
#include "TImage.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TMath.h"
#include "TMatrix.h"
#include "TMatrixT.h"
#include "TMinuit.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TTree.h"
#include "TPaveStats.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string> 
#include <time.h> 
#include <vector>


#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

void plot_multi_file_with_reference_line(std::string folder_name, std::vector<std::vector<std::string> > input_name, std::string title_name,std::string tree_name, std::vector<std::string> leg_name, std::vector<std::vector<float> > fit_region, std::vector<float> region,std::vector<string> axis_name, std::vector<string> axistype, long int event_num){

	if(region.size()!=3 || axistype.size()!=2){
		std::cout << "wrong input, please use region[6] and axistype[1] for input";
	}

	int num=input_name.size();
	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	std::vector<TLine*> line;
	line.resize(num);

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	string hvariable_name=x_name+y_name;
	int colornum=0;
	int stylenum=0;
	std::string hname=title_name;
	THStack *s = new THStack();


	std::vector<TH1F*> hvariable;
	hvariable.resize(num);
	for(int n=0;n<num;n++){
		std::vector<std::string> file_name=input_name[n];
		int fnum=file_name.size();
		hvariable[n] = new TH1F(hname.c_str(),hname.c_str(),region[0],region[1],region[2]);
		hvariable[n]->SetTitle(hvariable_name.c_str());
		for(int i=0;i<fnum;i++){
			std::string all_file_name=folder_name+file_name[i]+"_PfoAnalysis.root";
			TFile* in_file=new TFile(all_file_name.c_str());

			TTree *MyLCTuple=(TTree*)in_file->Get(tree_name.c_str());

			int nevent = MyLCTuple->GetEntries();
			Float_t variable=0;
			MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);

			if(nevent<event_num){
				event_num=nevent;
			}


			for(int event=0;event<event_num;event++){
				MyLCTuple->GetEntry(event);
				hvariable[n]->Fill(variable);
			}
		}

		hvariable[n]->Fit("gaus","R","same",fit_region[n][0],fit_region[n][1]);

		hvariable[n]->GetYaxis()->SetTitle(y_name.c_str());
		hvariable[n]->GetXaxis()->SetTitle(x_name.c_str());
		hvariable[n]->SetLineColor(1);
		hvariable[n]->SetLineWidth(2);
		hvariable[n]->SetLineStyle(1);



	}
	if(axistype[0]=="log"){
		gPad->SetLogx();
	}
	if(axistype[1]=="log"){
		gPad->SetLogy();
	}

	for(int n=0;n<num;n++){
		s->Add(hvariable[n]);
	}
	s->Draw("nostack");
	s->GetYaxis()->SetTitle(y_name.c_str());
	s->GetXaxis()->SetTitle(x_name.c_str());
	c1->Modified(); 
	c1->Update();

	for(int n=0;n<num;n++){
		float max_line=hvariable[n]->GetMaximum();
		line[n] = new TLine(fit_region[n][2],0,fit_region[n][2],max_line);
		line[n]->SetLineColor(kRed);
		line[n]->SetLineWidth(2);
		line[n]->Draw();

		float posy_d=0.8;
		float posy_u=0.9;
		float posx_d=0.15+n*0.2;
		float posx_u=0.35+n*0.2;
		if(n>3){
			posy_d=0.65;
			posy_u=0.75;
			posx_d=0.15+(n-3)*0.2;
			posx_u=0.35+(n-3)*0.2;
		}
		if(n>6){
			posy_d=0.5;
			posy_u=0.6;
			posx_d=0.35+(n-6)*0.2;
			posx_u=0.55+(n-6)*0.2;
		}
		
		auto leg = new TLegend(posx_d,posy_d,posx_u,posy_u);
		float mean=hvariable[n]->GetFunction("gaus")->GetParameter(1);
		float ratio=100*(mean/fit_region[n][2]-1);
		stringstream tmp;
		tmp << setprecision(3) << fit_region[n][2];
		std::string leg_mc=tmp.str();
		tmp.str(string());

		tmp << setprecision(4) << mean;
		std::string leg_energy=tmp.str();
		tmp.str(string());

		tmp << setprecision(3) << ratio;
		std::string leg_ratio =tmp.str();
		tmp.str(string());
		std::string leg_entry1="E_{MC}="+leg_mc+" GeV";
		std::string leg_entry2="#bar{E_{PFO}} = "+leg_energy+" GeV";
		std::string leg_entry3="#Delta E/E_{MC}="+leg_ratio+"%"; 
		leg->AddEntry(hvariable[n],leg_entry1.c_str(),""); 
		leg->AddEntry(hvariable[n],leg_entry2.c_str(),""); 
		leg->AddEntry(hvariable[n],leg_entry3.c_str(),""); 
		leg->SetBorderSize(0);
		leg->Draw();

	}

	c1->Modified(); 
	c1->Update();

	TImage *img = TImage::Create();
	img->FromPad(c1);
	std::string pngname=title_name+".png";
	img->WriteImage(pngname.c_str());


	return;
}
