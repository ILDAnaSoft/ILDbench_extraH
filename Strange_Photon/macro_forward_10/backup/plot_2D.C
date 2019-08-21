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

void plot_2D(std::vector<std::string> input_name,std::string title_name,std::string title_name1,std::string axis_name,std::string axis_name1,std::vector<float> region,std::vector<string> axistype) {

	if(region.size()!=6 || axistype.size()!=2){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}
	std::vector<std::string> filename;

	int num=input_name.size();
	for(int i=0;i<num;i++){
		filename.push_back(input_name[i] +".root");
	}
	std::vector<TFile*> in_file;
	std::vector<TH1D*> dvariable;
	std::vector<TH1D*> dvariable1;
	std::vector<TH2F*> fvariable;
	dvariable.resize(filename.size());
	dvariable1.resize(filename.size());
	fvariable.resize(filename.size());

	for(int i=0;i<filename.size();i++){
		TFile* in_file_tmp=new TFile(filename[i].c_str());
		in_file.push_back(in_file_tmp);
	}

	TCanvas *c1=new TCanvas("c1","c1",1000,700);
	gPad->SetLogy();
	gStyle->SetOptStat(0);


	// Create the three pads
	TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.60,0.65);
	center_pad->Draw();

	TPad* right_pad = new TPad("right_pad", "right_pad",0.65,0.0,1.0,0.65);
	right_pad->Draw();

	TPad* top_pad = new TPad("top_pad", "top_pad",0.0,0.65,0.60,1.0);
	top_pad->Draw();



	string x_name=axis_name;
	string y_name=axis_name1;
	int colornum=0;
	for(int i=0;i<filename.size();i++){
		TTree *MyLCTuple=(TTree*)in_file[i]->Get("datatrain");

		int nevent = MyLCTuple->GetEntries();
		float variable=0;
		float variable1=0;
		TBranch *branch=0;
		TBranch *branch1=0;
		MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);
		MyLCTuple->SetBranchAddress(title_name1.c_str(),&variable1);

		std::stringstream num;
		std::string fname=title_name+"_"+title_name1;
		fvariable[i]  = new TH2F(fname.c_str(),"",region[0],region[1],region[2],region[3],region[4],region[5]);


		for(int event=0;event<nevent;event++){
			MyLCTuple->GetEntry(event);
			fvariable[i]->Fill(variable,variable1);
		}

		dvariable[i] = fvariable[i]->ProjectionX();
		dvariable1[i]= fvariable[i]->ProjectionY();

		colornum++;
		if(colornum==3||colornum==5||colornum==8||colornum==10||colornum==11){
			colornum++;
		}
		dvariable[i]->SetFillColor(colornum+1);
		dvariable1[i]->SetFillColor(colornum-2);

		center_pad->cd();
		gStyle->SetPalette(1);
		fvariable[i]->GetYaxis()->SetTitle(y_name.c_str());
	    fvariable[i]->GetXaxis()->SetTitle(x_name.c_str());
		fvariable[i]->Draw("COLZ");

		top_pad->cd();
		if(axistype[0]=="log"){
			top_pad->SetLogy();
		}
		dvariable[i]->Draw("bar");

		right_pad->cd();
		if(axistype[1]=="log"){
			right_pad->SetLogx();
		}
		dvariable1[i]->Draw("hbar");

		c1->Update();
		TImage *img_2d = TImage::Create();
		img_2d->FromPad(c1);
		std::string pngname_2d=fname+".png";
		std::cout<<pngname_2d << std::endl;
		img_2d->WriteImage(pngname_2d.c_str());

	}



	return;
}
