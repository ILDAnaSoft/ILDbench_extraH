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

void plot_1D_vec_ratio(std::vector<std::string> input_name,std::vector<std::string> input_name1, std::string title_name,std::vector<float> region,std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}

	std::vector<std::string> filename;
	std::vector<std::string> filename1;

	int num=input_name.size();
	for(int i=0;i<num;i++){
		filename.push_back(input_name[i] +".root");
		filename1.push_back(input_name1[i] +".root");
	}
	std::vector<TFile*> in_file;
	std::vector<TFile*> in_file1;
	std::vector<TH1F*> hvariable;
	std::vector<TH1F*> hvariable1;
	hvariable.resize(filename.size());
	hvariable1.resize(filename1.size());

	for(int i=0;i<filename.size();i++){
		TFile* in_file_tmp=new TFile(filename[i].c_str());
		TFile* in_file_tmp1=new TFile(filename1[i].c_str());
		in_file.push_back(in_file_tmp);
		in_file1.push_back(in_file_tmp1);
	}

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.5,0.7,0.7,0.9);
	leg->SetHeader("e^{+}e^{-}->#mu^{+}#mu^{-} + X @ 250 GeV","C"); 

	string x_name=";"+title_name+ "(mm)";
	string y_name=";Events";
	string axis_name=x_name+y_name;
	int colornum=1;
    for(int i=0;i<filename.size();i++){
    	TTree *MyLCTuple=(TTree*)in_file[i]->Get("datatrain");
    	TTree *MyLCTuple1=(TTree*)in_file1[i]->Get("datatrain");

    	int nevent = MyLCTuple->GetEntries();
    	int nevent1 = MyLCTuple1->GetEntries();
		std::vector<float> *variable=0;
		TBranch *branch=0;
		std::vector<float> *variable1=0;
		TBranch *branch1=0;
		MyLCTuple->SetBranchAddress(title_name.c_str(), &variable, &branch);
		MyLCTuple1->SetBranchAddress(title_name.c_str(), &variable1, &branch1);

		std::stringstream num;
		std::string fnum;
		num << i;
		num >> fnum;
		std::string hname=title_name+fnum;
    	hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),region[0],region[1],region[2]);
    	hvariable[i]->SetTitle(axis_name.c_str());
		std::string hname1=title_name+fnum+"de";
    	hvariable1[i] = new TH1F(hname1.c_str(),title_name.c_str(),region[0],region[1],region[2]);
    	hvariable1[i]->SetTitle(axis_name.c_str());


    	for(int event=0;event<nevent;event++){
    		MyLCTuple->GetEntry(event);
			for(unsigned int vsize=0;vsize<variable->size();vsize++){
				hvariable[i]->Fill(variable->at(vsize));
			}
		}
    	for(int event=0;event<nevent1;event++){
    		MyLCTuple1->GetEntry(event);
			for(unsigned int vsize=0;vsize<variable1->size();vsize++){
				hvariable1[i]->Fill(variable1->at(vsize));
			}
		}

		colornum++;
		if(colornum==3||colornum==5||colornum==8||colornum==10||colornum==11){
			colornum++;
		}
    	hvariable[i]->Divide(hvariable1[i]);
    	hvariable[i]->SetLineColor(colornum);
    	std::string legname=filename[i];
    	leg->AddEntry(hvariable[i],legname.c_str(),"l");
    }

	if(axistype[0]=="log"){
		gPad->SetLogy();
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
    std::string pngname=title_name+"ratio.png";
    img->WriteImage(pngname.c_str());

    THStack *s1 = new THStack();
    for(int i=0;i<filename1.size();i++){
    	s1->Add(hvariable1[i]);
    }
    s1->Draw("nostack");

    c1->Update();
    TImage *img1 = TImage::Create();
    img1->FromPad(c1);
    std::string pngname1=title_name+"ratio1.png";
    img1->WriteImage(pngname1.c_str());


	return;
}
