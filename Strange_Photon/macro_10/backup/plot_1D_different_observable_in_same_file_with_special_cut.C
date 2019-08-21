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

void plot_1D_different_observable_in_same_file_with_special_cut(std::string input_name,std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<std::string> axis_name, std::vector<float> region,std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1|| axis_name.size()!=2){
		std::cout << "wrong input, please use region[3] and axistype[2] axis_name[2] for input";
	}

	std::string filename;

	filename=input_name+".root";
	std::vector<TH1F*> hvariable;
	hvariable.resize(title_name.size());

	TFile* in_file=new TFile(filename.c_str());

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.2,0.6,0.4,0.9);

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	string histo_name=x_name+y_name;
	TTree *MyLCTuple=(TTree*)in_file->Get("datatrain");

	int nevent = MyLCTuple->GetEntries();
	std::vector<float> *variable0=0,  *variable1=0, *variable2=0;
	TBranch *branch0=0;
	TBranch *branch1=0;
	TBranch *branch2=0;
	MyLCTuple->SetBranchAddress(title_name[0].c_str(), &variable0, &branch0);
	MyLCTuple->SetBranchAddress(title_name[1].c_str(), &variable1, &branch1);
	MyLCTuple->SetBranchAddress(title_name[2].c_str(), &variable2, &branch2);

	std::string hname=title_name[0]+"0";
	hvariable[0] = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);
	hvariable[0]->SetTitle(histo_name.c_str());
	hname=title_name[1]+"1";
	hvariable[1] = new TH1F(hname.c_str(),title_name[1].c_str(),region[0],region[1],region[2]);
	hvariable[1]->SetTitle(histo_name.c_str());
	hname=title_name[2]+"2";
	hvariable[2] = new TH1F(hname.c_str(),title_name[2].c_str(),region[0],region[1],region[2]);
	hvariable[2]->SetTitle(histo_name.c_str());

    for(int event=0;event<nevent;event++){
    	MyLCTuple->GetEntry(event);
    	for(unsigned int vsize=0;vsize<variable0->size();vsize++){
    		hvariable[0]->Fill(variable0->at(vsize));
    	}
    	for(unsigned int vsize=0;vsize<variable1->size();vsize++){
    		hvariable[1]->Fill(variable1->at(vsize));
    	}
    	for(unsigned int vsize=0;vsize<variable2->size();vsize++){
    		hvariable[2]->Fill(variable2->at(vsize));
    	}
    }

    hvariable[0]->SetLineColor(1);
    hvariable[0]->SetLineWidth(4);
    hvariable[0]->SetLineStyle(1);
    hvariable[1]->SetLineColor(1);
    hvariable[1]->SetLineWidth(2);
    hvariable[1]->SetLineStyle(1);
    hvariable[2]->SetLineColor(2);
    hvariable[2]->SetLineWidth(2);
    hvariable[2]->SetLineStyle(2);

//    leg->AddEntry(hvariable[0],leg_name[0].c_str(),"l");
    leg->AddEntry(hvariable[1],leg_name[1].c_str(),"l");
    leg->AddEntry(hvariable[2],leg_name[2].c_str(),"l");

    if(axistype[0]=="log"){
    	gPad->SetLogy();
    }

    THStack *s = new THStack();
    for(int i=1;i<title_name.size();i++){
    	s->Add(hvariable[i]);
    }

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

