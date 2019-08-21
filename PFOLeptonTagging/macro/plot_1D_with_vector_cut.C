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

void plot_1D_with_vector_cut(std::vector<std::string> input_name,std::string title_name,std::vector<std::string> cut_name, std::vector<float> cut_value, std::vector<float> region,std::vector<std::string> axistype, std::vector<std::string> axis_name, std::vector<std::string> legname) {

	if(region.size()!=3 || axistype.size()!=1){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}

	std::vector<std::string> filename;

	int num=input_name.size();
	for(int i=0;i<num;i++){
		filename.push_back(input_name[i] );
	}
	std::vector<TFile*> in_file;
	std::vector<TH1F*> hvariable;
	hvariable.resize(filename.size());

	Int_t color_vector[2];
	color_vector[0]=4;
	color_vector[1]=2;
	Int_t style_vector[2];
	style_vector[0]=1;
	style_vector[1]=2;
	for(int i=0;i<filename.size();i++){
		TFile* in_file_tmp=new TFile(filename[i].c_str());
		in_file.push_back(in_file_tmp);
	}

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.7,0.7,0.9,0.9);

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	string all_axis_name=x_name+y_name;
	int colornum=1;
    for(int i=0;i<filename.size();i++){
    	TTree *MyLCTuple=(TTree*)in_file[i]->Get("datatrain");

    	int nevent = MyLCTuple->GetEntries();
    	float variable;
    	MyLCTuple->SetBranchAddress(title_name.c_str(), &variable);

		std::vector<float> *variable1=0;
		TBranch *branch1=0;
		MyLCTuple->SetBranchAddress(cut_name[0].c_str(), &variable1, &branch1);
		
		std::stringstream num;
		std::string fnum;
		num << i;
		num >> fnum;
		std::string hname=title_name+fnum;
    	hvariable[i] = new TH1F(hname.c_str(),title_name.c_str(),region[0],region[1],region[2]);
    	hvariable[i]->SetTitle(all_axis_name.c_str());


    	for(int event=0;event<nevent;event++){
    		MyLCTuple->GetEntry(event);
			for(unsigned int vsize=0;vsize<variable1->size();vsize++){
				float v1;
				if(cut_value[0]==-1){
					v1=std::abs(variable1->at(vsize));
					if(v1<cut_value[1]){
						hvariable[i]->Fill(variable);
					}
				}
				else if(cut_value[0]==0){
					hvariable[i]->Fill(variable);
				}
				else if(cut_value[0]==1){
					if(v1>cut_value[1]&&v1<cut_value[2]){
						hvariable[i]->Fill(variable);
					}
				}
			}
    	}

		colornum++;
    	hvariable[i]->SetLineColor(color_vector[colornum]);
    	hvariable[i]->SetLineStyle(style_vector[colornum]);
    	leg->AddEntry(hvariable[i],legname[i].c_str(),"l");
    }

	if(axistype[0]=="log"){
		gPad->SetLogy();
	}


    THStack *s = new THStack();
    for(int i=0;i<filename.size();i++){
    	s->Add(hvariable[i]);
    }
    s->Draw("nostack");
	s->GetYaxis()->SetTitle(y_name.c_str());
	s->GetXaxis()->SetTitle(x_name.c_str());
    leg->Draw();

    c1->Update();
    TImage *img = TImage::Create();
    img->FromPad(c1);
    std::string pngname=title_name+".png";
    img->WriteImage(pngname.c_str());


	return;
}
