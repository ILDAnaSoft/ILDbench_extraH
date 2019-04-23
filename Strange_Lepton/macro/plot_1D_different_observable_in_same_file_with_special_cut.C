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

void plot_1D_different_observable_in_same_file_with_special_cut(std::string input_name,std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<float> region,std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}

	std::string filename;

	filename=input_name+".root";
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
	TTree *MyLCTuple=(TTree*)in_file->Get("datatrain");

	int nevent = MyLCTuple->GetEntries();
	float variable,variable2;
	std::vector<float> *variable1=0;
	TBranch *branch1=0;
	MyLCTuple->SetBranchAddress(title_name[0].c_str(), &variable);
	MyLCTuple->SetBranchAddress(title_name[1].c_str(), &variable1, &branch1);
	MyLCTuple->SetBranchAddress(title_name[2].c_str(), &variable2);

	std::string hname=title_name[0]+"0";
	hvariable[0] = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);
	hvariable[0]->SetTitle(axis_name.c_str());
	hname=title_name[0]+"1";
	hvariable[1] = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);
	hvariable[1]->SetTitle(axis_name.c_str());

	float num=0;
	float num1=0;
	for(int event=0;event<nevent;event++){
		MyLCTuple->GetEntry(event);
		int Jpdg=0;
		for(unsigned int vsize=0;vsize<variable1->size();vsize++){
			if(std::abs(variable1->at(vsize))==13){
				Jpdg++;
			}
		}
		if(!(variable>-10000.2&&variable<-10000)&&variable2>=2){
			if(Jpdg==2){
				num++;
				hvariable[0]->Fill(variable);
			}
			else{
				num1++;
				hvariable[1]->Fill(variable);
			}
		}
	}

	hvariable[0]->SetLineColor(1);
	hvariable[0]->SetLineWidth(4);
	hvariable[0]->SetLineStyle(1);
	hvariable[1]->SetLineColor(2);
	hvariable[1]->SetLineWidth(2);
	hvariable[1]->SetLineStyle(3);

	Double_t norm0 = 1;
	Double_t scale0= norm0/(hvariable[0]->Integral());
	hvariable[0]->Scale(scale0);

	Double_t norm1 = 1;
	Double_t scale1= norm1/(hvariable[1]->Integral());
	hvariable[1]->Scale(scale1);

	leg->AddEntry(hvariable[0],"have MCHS muon pair","l");
	leg->AddEntry(hvariable[1],"no MCHS muon pair","l");

	if(axistype[0]=="log"){
		gPad->SetLogy();
	}

	THStack *s = new THStack();
	for(int i=0;i<2;i++){
		s->Add(hvariable[i]);
	}
	std::cout << "num muon" << num << std::endl;
	std::cout << "num other " << num1 << std::endl;
	s->Draw("nostack, HIST");
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

