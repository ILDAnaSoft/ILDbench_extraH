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

void plot_1D_photon_counting(std::string input_name,std::vector<std::string> leg_name, std::vector<string> axistype) {

	if(axistype.size()!=1){
		std::cout << "wrong input, please use axistype[2] for input";
	}

	std::string filename;

	filename=input_name;
	std::vector<TH1F*> hvariable;
	hvariable.resize(2);

	TFile* in_file=new TFile(filename.c_str());

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.2,0.6,0.4,0.9);

	string x_name="M_{Z}";
	string y_name="Events";
	string axis_name=x_name+y_name;
	int colornum=0;
	int stylenum=0;
	TTree *MyLCTuple_sig=(TTree*)in_file->Get("datatrain_sig");
	TTree *MyLCTuple_bkg=(TTree*)in_file->Get("datatrain_bkg");

	int nevent_sig = MyLCTuple_sig->GetEntries();
	int nevent_bkg = MyLCTuple_bkg->GetEntries();
	float  variable_sig;
	float variable1_sig;
	float  variable_bkg;
	float variable1_bkg;

	MyLCTuple_sig->SetBranchAddress("isophoton_numnum", &variable_sig);
	MyLCTuple_sig->SetBranchAddress("wophoton_numnum", &variable1_sig);
	MyLCTuple_bkg->SetBranchAddress("isophoton_numnum", &variable_bkg);
	MyLCTuple_bkg->SetBranchAddress("wophoton_numnum", &variable1_bkg);

	std::string hname=title_name[0]+"0";

	hvariable[0] = new TH1F("particle type","particle type",10,0,10);
	hvariable[0]->SetTitle("particle type");

	hvariable[1] = new TH1F("energy",300,0,300);
	hvariable[1]->SetTitle("energy");


	float num=0;
	float num1=0;
	for(int event=0;event<nevent;event++){
		MyLCTuple->GetEntry(event);
		if(!(variable>-10000.2&&variable<-10000)){
			num++;
			hvariable[0]->Fill(variable);
		}
		if(!(variable1>-10000.2&&variable1<-10000)){
			num1++;
			hvariable[1]->Fill(variable1);
		}
	}

	for(unsigned int i=0;i<title_name.size();i++){
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

	std::cout << "forward : " << num << std::endl;
	std::cout << "central : " << num1 << std::endl;
	std::cout << "total   : " << nevent << std::endl;
	std::cout << "ratio   : " << (num+num1)/nevent << std::endl;

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
