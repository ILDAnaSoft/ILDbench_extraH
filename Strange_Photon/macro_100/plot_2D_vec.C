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

void plot_2D_vec(std::string input_name,std::vector<std::string> title_name, std::vector<std::string> axis_name,std::vector<float> region,std::vector<string> axistype, long int eventnum) {

	if(title_name.size()!=2 || axis_name.size()!=2 || region.size()!=6 || axistype.size()!=2){
		std::cout << "wrong input, please use title_name[2] and axis_name[2] and region[6] and axistype[2] for input";
		return;
	}

	TFile* in_file=new TFile(input_name.c_str());

	TCanvas *c1=new TCanvas("c1","c1",1000,700);
	gPad->SetLogy();
	gStyle->SetOptStat(0);

	// Create the three pads
	TPad *center_pad = new TPad("center_pad", "center_pad",0.0,0.0,0.90,0.90);
	center_pad->Draw();

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	TTree *MyLCTuple=(TTree*)in_file->Get("datatrain");

	int nevent = MyLCTuple->GetEntries();
	std::vector<float> *variable0=0;
	std::vector<float> *variable1=0;
	TBranch *branch0=0;
	TBranch *branch1=0;
	// these two for x-y plane 
	MyLCTuple->SetBranchAddress(title_name[0].c_str(), &variable0, &branch0);
	MyLCTuple->SetBranchAddress(title_name[1].c_str(), &variable1, &branch1);

	std::stringstream num;
	std::string fname=title_name[0]+"_"+title_name[1];
	TH2F* fvariable = new TH2F(fname.c_str(),"",region[0],region[1],region[2],region[3],region[4],region[5]);


	//for(int event=0;event<nevent;event++){
	if(nevent<eventnum){
		eventnum=nevent;
	}

	int pnum=0;
	for(int event=0;event<eventnum;event++){
		MyLCTuple->GetEntry(event);
		for(unsigned int vsize=0;vsize<min(variable0->size(),variable1->size());vsize++){
			float v0=variable0->at(vsize);
			float v1=variable1->at(vsize);
			fvariable->Fill(v0,v1);
		}
	}


	center_pad->cd();
	//gStyle->SetPalette(kSolar);
	fvariable->GetYaxis()->SetTitle(y_name.c_str());
	fvariable->GetXaxis()->SetTitle(x_name.c_str());
	fvariable->Draw("COLZ");

	c1->Update();
	c1->Modified();
	c1->Update();
	gSystem->ProcessEvents();

	TImage *img_2d = TImage::Create();
	img_2d->FromPad(c1);
	std::string pngname_2d=fname+".png";
	std::cout<<pngname_2d << std::endl;
	img_2d->WriteImage(pngname_2d.c_str());
	return;
}
