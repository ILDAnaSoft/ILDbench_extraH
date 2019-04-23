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

void plot_1D_different_observable(std::vector<std::string> input_name,std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<float> region,std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}

	if(input_name.size()!=title_name.size()){
		std::cout << "wrong input, please use the same size for input_name and title_name";
	}

	if(input_name.size()!=leg_name.size()){
		std::cout << "wrong input, please use the same size for input_name and title_name";
	}

	std::vector<std::string> filename;

	int num=input_name.size();
	for(int i=0;i<num;i++){
		filename.push_back(input_name[i] +".root");
	}
	std::vector<TFile*> in_file;
	std::vector<TH1F*> hvariable;
	hvariable.resize(filename.size());

	for(int i=0;i<filename.size();i++){
		TFile* in_file_tmp=new TFile(filename[i].c_str());
		in_file.push_back(in_file_tmp);
	}

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.2,0.6,0.4,0.9);

	string x_name="M_{Z}";
	string y_name="Events";
	string axis_name=x_name+y_name;
	int colornum=0;
	int stylenum=0;
    for(int i=0;i<filename.size();i++){
    	TTree *MyLCTuple=(TTree*)in_file[i]->Get("datatrain");

    	int nevent = MyLCTuple->GetEntries();
    	float variable;
    	MyLCTuple->SetBranchAddress(title_name[i].c_str(), &variable);

		std::stringstream num;
		std::string fnum;
		num << i;
		num >> fnum;
		std::string hname=title_name[i]+fnum;
    	hvariable[i] = new TH1F(hname.c_str(),title_name[i].c_str(),region[0],region[1],region[2]);
    	hvariable[i]->SetTitle(axis_name.c_str());


    	for(int event=0;event<nevent;event++){
    		MyLCTuple->GetEntry(event);
    		hvariable[i]->Fill(variable);
    	}

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
    for(int i=0;i<filename.size();i++){
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
