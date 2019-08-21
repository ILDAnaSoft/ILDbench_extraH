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

void plot_1D_different_observable_in_same_file_with_extra_cut(std::string input_name,std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<std::string> axis_name, std::vector<float> region,std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1|| axis_name.size()!=2){
		std::cout << "wrong input, please use region[3] and axistype[2] axis_name[2] for input";
	}

	std::string filename;

	filename=input_name+".root";
	TH1F* hvariable;
	TH1F* hvariable1;
	TH1F* hvariable2;

	TFile* in_file=new TFile(filename.c_str());

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.2,0.6,0.4,0.9);

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	TTree *MyLCTuple=(TTree*)in_file->Get("datatrain");

	int nevent = MyLCTuple->GetEntries();
	std::vector<float> *variable0=0,  *variable1=0, *variable2=0, *variable3=0;
	TBranch *branch0=0;
	TBranch *branch1=0;
	TBranch *branch2=0;
	TBranch *branch3=0;
	MyLCTuple->SetBranchAddress(title_name[0].c_str(), &variable0, &branch0);
	MyLCTuple->SetBranchAddress(title_name[1].c_str(), &variable1, &branch1);
	MyLCTuple->SetBranchAddress(title_name[2].c_str(), &variable2, &branch2);
	MyLCTuple->SetBranchAddress(title_name[3].c_str(), &variable3, &branch3);

	std::string hname=title_name[0]+"0";
	hvariable = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);
	hname=title_name[0]+"1";
	hvariable1 = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);
	hname=title_name[0]+"2";
	hvariable2 = new TH1F(hname.c_str(),title_name[0].c_str(),region[0],region[1],region[2]);

    for(int event=0;event<nevent;event++){
    	MyLCTuple->GetEntry(event);
    	for(unsigned int vsize=0;vsize<variable0->size();vsize++){
			float ratio=variable1->at(vsize)/variable2->at(vsize);
			if(variable3->at(vsize)<100){
				hvariable->Fill(variable0->at(vsize));
			}
			else{
				if(ratio>1){
					hvariable1->Fill(variable0->at(vsize));
				}
				else{
					std::cout << "ecal " << variable1->at(vsize) << " hcal " << variable2->at(vsize) << " pfo " << variable3->at(vsize) << std::endl;
					hvariable2->Fill(variable0->at(vsize));
				}
			}
    	}
    }

    hvariable->SetLineColor(1);
    hvariable1->SetLineColor(2);
    hvariable2->SetLineColor(3);

    leg->AddEntry(hvariable,leg_name[0].c_str(),"l");
    leg->AddEntry(hvariable1,leg_name[1].c_str(),"l");
    leg->AddEntry(hvariable2,leg_name[2].c_str(),"l");

    if(axistype[0]=="log"){
    	gPad->SetLogy();
    }

    THStack *s = new THStack();
    s->Add(hvariable);
    s->Add(hvariable1);
    s->Add(hvariable2);

    s->Draw("HIST");
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

