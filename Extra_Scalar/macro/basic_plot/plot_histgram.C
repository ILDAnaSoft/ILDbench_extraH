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

void plot_histgram(std::vector<std::string> mhmass) {

	std::vector<std::string> filename;

	int num=mhmass.size();
	for(int i=0;i<num;i++){
		filename.push_back(mhmass[i] +".root");
	}
	std::vector<TFile*> in_file;
	std::vector<TH1F*> hvariable;
	hvariable.resize(filename.size());

	for(int i=0;i<filename.size();i++){
		TFile* in_file_tmp=new TFile(filename[i].c_str());
		in_file.push_back(in_file_tmp);
	}

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.7,0.7,0.9,0.9);
	leg->SetHeader("e^{+}e^{-}->#mu^{+}#mu^{-} + X @ 250 GeV","C"); 
	gPad->SetLogy();

	string title_name="mc_muon_gen_higgs_channle";
	string x_name=";"+title_name+ "(GeV/c^{2})";
	string y_name=";Events";
	string axis_name=x_name+y_name;
	int colornum=0;
    for(int i=0;i<filename.size();i++){
    	TTree *MyLCTuple=(TTree*)in_file[i]->Get("datatrain");

    	int nevent = MyLCTuple->GetEntries();
    	float variable;
    	MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);

		std::stringstream num;
		std::string fnum;
		num << i;
		num >> fnum;
		std::string hname=title_name+fnum;
    	hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),300,0,300);
    	hvariable[i]->SetTitle(axis_name.c_str());


		int n05=0;
		int n04=0;
		int n15=0;
		int n21=0;
		int n22=0;
		int n23=0;
		int n24=0;
		int n25=0;
		int other=0;
    	for(int event=0;event<nevent;event++){
    		MyLCTuple->GetEntry(event);
			if(variable>24.9&&variable<25.1){
				n25++;
			}
			else  if(variable>23.9&&variable<24.1){
				n24++;
			}
			else  if(variable>22.9&&variable<23.1){
				n23++;
			}
			else  if(variable>21.9&&variable<22.1){
				n22++;
			}
			else  if(variable>20.9&&variable<21.1){
				n21++;
			}
			else  if(variable>14.9&&variable<15.1){
				n15++;
			}
			else  if(variable>4.9&&variable<5.1){
				n05++;
			}
			else  if(variable>3.9&&variable<4.1){
				n04++;
			}
			else{
				std::cout<<variable<<std::endl;
				other++;
			}
    		hvariable[i]->Fill(variable);
    	}

		std::cout<<"bb   " <<float(n05)/float(nevent)<<std::endl;
		std::cout<<"cc   " <<float(n04)/float(nevent)<<std::endl;
		std::cout<<"gg   " <<float(n21)/float(nevent)<<std::endl;
		std::cout<<"tata " <<float(n15)/float(nevent)<<std::endl;
		std::cout<<"ww   " <<float(n24)/float(nevent)<<std::endl;
		std::cout<<"zz   " <<float(n23)/float(nevent)<<std::endl;
		std::cout<<"aa   " <<float(n22)/float(nevent)<<std::endl;
		std::cout<<"az   " <<float(n25)/float(nevent)<<std::endl;
		std::cout<<"other" <<float(other)/float(nevent)<<std::endl;
    	colornum++;
    	if(colornum==3||colornum==5||colornum==8||colornum==10||colornum==11){
    		colornum++;
    	}
    	hvariable[i]->SetLineColor(colornum);
    	std::string legname=filename[i];
    	leg->AddEntry(hvariable[i],legname.c_str(),"l");
    }



    THStack *s = new THStack();
    for(int i=0;i<filename.size();i++){
    	s->Add(hvariable[i]);
    }
    s->Draw("nostack");
    leg->Draw();

    c1->Update();
    TImage *img = TImage::Create();
    img->FromPad(c1);
    std::string pngname=title_name+".png";
    img->WriteImage(pngname.c_str());


	return;
}
