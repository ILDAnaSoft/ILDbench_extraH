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

void plot_1D_different_observable_in_same_multi_file(std::vector<std::string> input_name,std::vector<std::string> input_name2 ,std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<std::string> axis_name, std::vector<float> region,std::vector<float> leg_pos, std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}

	TChain TChain1("datatrain");
	TChain TChain2("datatrain");
	int num1=input_name.size();
	for(int i=0;i<num1;i++){
		TChain1.Add(input_name[i].c_str());
	}

	int num2=input_name2.size();
	for(int i=0;i<num2;i++){
		TChain2.Add(input_name2[i].c_str());
	}

	std::vector<TH1F*> hvariable;
	hvariable.resize(title_name.size());


	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(leg_pos[0],leg_pos[1],leg_pos[2],leg_pos[3]);

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	int colornum=0;
	int stylenum=0;

	float variable;
	float variable1;
	TChain1.SetBranchAddress(title_name[0].c_str(), &variable);
	TChain1.SetBranchAddress(title_name[1].c_str(), &variable1);

	std::string hname=title_name[0]+"0";
	hvariable[0] = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);
	hvariable[0]->SetTitle(axis_name[0].c_str());


	long int nevent = TChain1.GetEntries();
	for(int event=0;event<nevent;event++){
		TChain1.GetEntry(event);
		if(variable<-10000){
			continue;
		}
		float ratio=(variable-variable1)/variable;
		hvariable[0]->Fill(ratio);
	}

	TChain2.SetBranchAddress(title_name[0].c_str(), &variable);
	TChain2.SetBranchAddress(title_name[1].c_str(), &variable1);
	hname=title_name[0]+"1";
	hvariable[1] = new TH1F(hname.c_str(),title_name[1].c_str(),region[0],region[1],region[2]);
	hvariable[1]->SetTitle(axis_name[0].c_str());

	nevent = TChain2.GetEntries();
	for(int event=0;event<nevent;event++){
		TChain2.GetEntry(event);
		if(variable<-10000){
			continue;
		}
		float ratio=(variable-variable1)/variable;
		hvariable[1]->Fill(ratio);
	}



	for(unsigned int i=0;i<2;i++){
		colornum++;
		stylenum++;
		if(colornum==3||colornum==5||colornum==8||colornum==10||colornum==11){
			colornum++;
		}

		hvariable[i]->SetLineColor(colornum);
		hvariable[i]->SetLineWidth(4);
		hvariable[i]->SetLineStyle(stylenum);
		std::string legname=leg_name[i];
		leg->AddEntry(hvariable[i],legname.c_str(),"l");
	}

	if(axistype[0]=="log"){
		gPad->SetLogy();
	}

	THStack *s = new THStack();
	for(int i=0;i<title_name.size();i++){
		s->Add(hvariable[i]);
	}
	s->Draw("nostack");
	leg->Draw();
	s->GetYaxis()->SetTitle(y_name.c_str());
	s->GetXaxis()->SetTitle(x_name.c_str());

	c1->Update();
	TImage *img = TImage::Create();
	img->FromPad(c1);
	std::string pngname=title_name[0]+".png";
	img->WriteImage(pngname.c_str());


	return;
}
