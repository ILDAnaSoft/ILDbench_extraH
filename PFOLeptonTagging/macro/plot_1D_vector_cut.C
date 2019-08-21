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

void plot_1D_cut_pfo_mc_energy_diff_with_E_cos(std::string input_name,std::vector<std::string> title_name,std::vector<std::string> cut_name, std::vector<std::string> leg_name, std::vector<std::string> axis_name, std::vector<float> region,std::vector<string> axistype, long int eventnum) {

	if(region.size()!=3 || axistype.size()!=1|| axis_name.size()!=2){
		std::cout << "wrong input, please use region[3] and axistype[2] axis_name[2] for input";
	}

	std::cout << "title_name size " << title_name.size() << std::endl;
	std::cout << "cut_name   size " << cut_name.size() << std::endl;
	std::cout << "leg_name size " << leg_name.size() << std::endl;

	std::vector<TH1F*> hvariable;

	TFile* in_file=new TFile(input_name.c_str());

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.2,0.6,0.4,0.9);

	string x_name=axis_name[0];
	string y_name=axis_name[1];

	TTree *MyLCTuple=(TTree*)in_file->Get("datatrain");

	int nevent = MyLCTuple->GetEntries();
	std::vector<float> *variable0=0;
	TBranch *branch0=0;
	MyLCTuple->SetBranchAddress(title_name[0].c_str(), &variable0, &branch0);


	std::vector<float> *variable1=0, *variable2=0, *variable3=0, *variable4=0, *variable5=0;
	TBranch *branch1=0;
	TBranch *branch2=0;
	TBranch *branch3=0;
	TBranch *branch4=0;
	TBranch *branch5=0;
	MyLCTuple->SetBranchAddress(cut_name[0].c_str(), &variable1, &branch1);
	MyLCTuple->SetBranchAddress(cut_name[1].c_str(), &variable2, &branch2);
	MyLCTuple->SetBranchAddress(cut_name[2].c_str(), &variable3, &branch3);
	MyLCTuple->SetBranchAddress(cut_name[3].c_str(), &variable4, &branch4);
	MyLCTuple->SetBranchAddress(cut_name[4].c_str(), &variable5, &branch5);

    for(unsigned int i=0;i<leg_name.size();i++){
		std::string hname=leg_name[i]+"0";
		hvariable.push_back(new TH1F(hname.c_str(),leg_name[i].c_str(),region[0],region[1],region[2]));
	}

	if(nevent<eventnum){
		eventnum=nevent;
	}

    for(int event=0;event<eventnum;event++){
    	MyLCTuple->GetEntry(event);
    	for(unsigned int vsize=0;vsize<variable0->size();vsize++){
			float v4=variable4->at(vsize);
			float v5=std::abs(variable5->at(vsize));
			float v0=variable0->at(vsize)/v4;
			float v1=variable1->at(vsize);
			float v2=variable2->at(vsize);
			float v3=variable3->at(vsize);

			if(v4<100&&v5<0.996){
				hvariable[0]->Fill(v0);
			}
			else if(v4<100&&v5>0.996){
				hvariable[1]->Fill(v0);
			}
			else if(v4>100&&v5<0.996){
				hvariable[2]->Fill(v0);
			}
			else if(v4>100&&v5>0.996){
				hvariable[3]->Fill(v0);
			}
    	}
    }

    if(axistype[0]=="log"){
    	gPad->SetLogy();
    }


    THStack *s = new THStack();
    for(unsigned int i =0;i<leg_name.size();i++){
		hvariable[i]->SetLineColor(i+1);
		leg->AddEntry(hvariable[i],leg_name[i].c_str(),"l");
		s->Add(hvariable[i]);
	}

    s->Draw("nostack,HIST");
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

