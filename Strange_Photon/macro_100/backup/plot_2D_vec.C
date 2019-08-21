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

void plot_2D_vec(std::vector<std::string> input_name,std::string title_name,std::string title_name1,std::string title_name2, std::string axis_name,std::string axis_name1,std::vector<float> region,std::vector<string> axistype, long int eventnum) {

	if(region.size()!=6 || axistype.size()!=2){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
		return;
	}

	std::vector<std::string> filename;

	int num=input_name.size();
	for(int i=0;i<num;i++){
		filename.push_back(input_name[i] +".root");
	}
	std::vector<TFile*> in_file;
	std::vector<TH2F*> fvariable;
	fvariable.resize(filename.size());

	for(int i=0;i<filename.size();i++){
		TFile* in_file_tmp=new TFile(filename[i].c_str());
		in_file.push_back(in_file_tmp);
	}

	TCanvas *c1=new TCanvas("c1","c1",1000,700);
	gPad->SetLogy();
	gStyle->SetOptStat(0);


	// Create the three pads
	TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.90,0.90);
	center_pad->Draw();


	string x_name=axis_name;
	string y_name=axis_name1;
	int colornum=0;
	for(int i=0;i<filename.size();i++){
		TTree *MyLCTuple=(TTree*)in_file[i]->Get("datatrain");

		int nevent = MyLCTuple->GetEntries();
		std::vector<float> *variable0=0;
		std::vector<float> *variable1=0;
		std::vector<float> *variable2=0;
		TBranch *branch0=0;
		TBranch *branch1=0;
		TBranch *branch2=0;
		// these two for x-y plane 
		MyLCTuple->SetBranchAddress(title_name.c_str(), &variable0, &branch0);
		MyLCTuple->SetBranchAddress(title_name1.c_str(), &variable1, &branch1);
		MyLCTuple->SetBranchAddress(title_name2.c_str(), &variable2, &branch2);

		std::stringstream num;
		std::string fname=title_name+"_"+title_name1;
		fvariable[i]  = new TH2F(fname.c_str(),"",region[0],region[1],region[2],region[3],region[4],region[5]);


		//for(int event=0;event<nevent;event++){
		if(nevent<eventnum){
			eventnum=nevent;
		}

		int pnum=0;
		for(int event=0;event<eventnum;event++){
			MyLCTuple->GetEntry(event);
			for(unsigned int vsize=0;vsize<min(variable0->size(),variable1->size());vsize++){
				//condition for classification
				//fvariable[i]->Fill(variable0->at(vsize),variable1->at(vsize),variable2->at(vsize));
    			if(variable0->at(vsize)>5){
    			//	pnum++;
    				//fvariable[i]->Fill(variable0->at(vsize),variable1->at(vsize),variable2->at(vsize));
    				fvariable[i]->Fill(variable0->at(vsize),variable1->at(vsize));
    			}
			}
		}

		std::cout << "total number " << nevent << std::endl;
		std::cout << "problem number " << pnum << std::endl;
		colornum++;
		if(colornum==3||colornum==5||colornum==8||colornum==10||colornum==11){
			colornum++;
		}

		center_pad->cd();
	  	//gStyle->SetPalette(kSolar);
		fvariable[i]->GetYaxis()->SetTitle(y_name.c_str());
		fvariable[i]->GetXaxis()->SetTitle(x_name.c_str());
		fvariable[i]->Draw("COLZ");

		c1->Update();
		c1->Modified();
		c1->Update();
		gSystem->ProcessEvents();

		TImage *img_2d = TImage::Create();
		img_2d->FromPad(c1);
		std::string pngname_2d=fname+".png";
		std::cout<<pngname_2d << std::endl;
		img_2d->WriteImage(pngname_2d.c_str());
	}





		return;
	}
