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
#include "TChain.h"
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

void plot_1D_two_observable_multi_files_seperate_sig_bkg(std::vector<std::string> input_name1,std::vector<std::string> input_name2, std::vector<std::string> bkg_name1, std::vector<std::string> bkg_name2,  std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<std::string>axis_name, std::vector<float> region,std::vector<float> leg_pos, std::vector<string> axistype) {

	if(region.size()!=3 || axistype.size()!=1, axis_name.size()!=2){
		std::cout << "wrong input, please use region[6] and axistype[2] and axis_name[2] for input";
	}


	std::vector<TChain> TChain_vec;
	TChain TChain1("datatrain");
	TChain TChain2("datatrain");
	TChain TChain_bkg1("datatrain");
	TChain TChain_bkg2("datatrain");
	std::vector<TH1F*> hvariable;
	hvariable.resize(4);

	int num1=input_name1.size();
	for(int i=0;i<num1;i++){
		TChain1.Add(input_name1[i].c_str());
	}

	int num2=input_name2.size();
	for(int i=0;i<num2;i++){
		TChain2.Add(input_name2[i].c_str());
	}

	int num_bkg1=bkg_name1.size();
	for(int i=0;i<num_bkg1;i++){
		TChain_bkg1.Add(bkg_name1[i].c_str());
	}

	int num_bkg2=bkg_name2.size();
	for(int i=0;i<num_bkg2;i++){
		TChain_bkg2.Add(bkg_name2[i].c_str());
	}
	//    TChain_vec.push_back(TChain1);
	//    TChain_vec.push_back(TChain2);


	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(leg_pos[0],leg_pos[1],leg_pos[2],leg_pos[3]);

	string x_name=axis_name[0];
	string y_name=axis_name[1];
	int colornum=0;
	int stylenum=0;


	//    for(int i=0;i<TChain_vec.size();i++){

	int i=0;
	float variable1;
	float variable2;
	float variable_bkg1;
	float variable_bkg2;
	long int tnum1=0;
	TChain1.SetBranchAddress(title_name[0].c_str(), &variable1);
	if(title_name.size()>1){
		TChain1.SetBranchAddress(title_name[1].c_str(), &variable2);
	}

	std::string hname=title_name[0]+"_0";
	hvariable[i] = new TH1F(hname.c_str(),hname.c_str(),region[0],region[1],region[2]);
	hvariable[i]->SetTitle(axis_name[0].c_str());

	long int nevent = TChain1.GetEntries();
	for(long int event=0;event<nevent;event++){
		TChain1.GetEntry(event);
		hvariable[i]->Fill(variable1);
		if(variable1>-100){
			tnum1++;
		}
		if(title_name.size()>1){
			hvariable[i]->Fill(variable2);
			if(variable2>-100){
				tnum1++;
			}
		}
	}
	hvariable[i]->SetLineColor(1);
	hvariable[i]->SetLineWidth(3);
	hvariable[i]->SetLineStyle(1);
	std::string legname=leg_name[i]+"_sig";
	leg->AddEntry(hvariable[i],legname.c_str(),"l");

	std::cout << "type 1 total number: " << nevent << " effective number: " <<tnum1 << std::endl;

	i=1;
	long int tnum2=0;
	TChain2.SetBranchAddress(title_name[0].c_str(), &variable1);
	if(title_name.size()>1){
		TChain2.SetBranchAddress(title_name[1].c_str(), &variable2);
	}

	hname=title_name[0]+"_1";
	hvariable[i] = new TH1F(hname.c_str(),hname.c_str(),region[0],region[1],region[2]);
	hvariable[i]->SetTitle(axis_name[0].c_str());

	nevent = TChain2.GetEntries();
	for(long int event=0;event<nevent;event++){
		TChain2.GetEntry(event);
		hvariable[i]->Fill(variable1);
	    if(variable1>-100){
	    	tnum2++;
	    }
		if(title_name.size()>1){
			hvariable[i]->Fill(variable2);
			if(variable2>-100){
				tnum2++;
			}
		}
	}

	hvariable[i]->SetLineColor(2);
	hvariable[i]->SetLineWidth(3);
	hvariable[i]->SetLineStyle(1);
	legname=leg_name[i]+"_sig";
	leg->AddEntry(hvariable[i],legname.c_str(),"l");


    i=2;
    long int tnum_bkg1=0;
    long int tnum_bkg2=0;
    TChain_bkg1.SetBranchAddress(title_name[0].c_str(), &variable_bkg1);
    if(title_name.size()>1){
    	TChain_bkg1.SetBranchAddress(title_name[1].c_str(), &variable_bkg2);
    }

    hname=title_name[0]+"_1";
    hvariable[i] = new TH1F(hname.c_str(),hname.c_str(),region[0],region[1],region[2]);
    hvariable[i]->SetTitle(axis_name[0].c_str());

    nevent = TChain_bkg1.GetEntries();
    for(long int event=0;event<nevent;event++){
    	TChain_bkg1.GetEntry(event);
    	hvariable[i]->Fill(variable_bkg1);
        if(variable_bkg1>-100){
        	tnum_bkg1++;
        }
    	if(title_name.size()>1){
    		hvariable[i]->Fill(variable_bkg2);
    		if(variable_bkg2>-100){
    			tnum_bkg1++;
    		}
    	}
    }
    std::cout << "type 2 total number: " << nevent << " effective number: " <<tnum_bkg1 << std::endl;

    hvariable[i]->SetLineColor(1);
    hvariable[i]->SetLineWidth(3);
    hvariable[i]->SetLineStyle(2);
    legname=leg_name[i-2]+"_bkg";
    leg->AddEntry(hvariable[i],legname.c_str(),"l");


    i=3;
    TChain_bkg2.SetBranchAddress(title_name[0].c_str(), &variable_bkg1);
    if(title_name.size()>1){
    	TChain_bkg2.SetBranchAddress(title_name[1].c_str(), &variable_bkg2);
    }

    hname=title_name[0]+"_1";
    hvariable[i] = new TH1F(hname.c_str(),hname.c_str(),region[0],region[1],region[2]);
    hvariable[i]->SetTitle(axis_name[0].c_str());

    nevent = TChain_bkg2.GetEntries();
    for(long int event=0;event<nevent;event++){
    	TChain_bkg2.GetEntry(event);
    	hvariable[i]->Fill(variable_bkg1);
        if(variable_bkg1>-100){
        	tnum_bkg2++;
        }
    	if(title_name.size()>1){
    		hvariable[i]->Fill(variable_bkg2);
    		if(variable_bkg2>-100){
    			tnum_bkg2++;
    		}
    	}
    }
    std::cout << "type 2 total number: " << nevent << " effective number: " <<tnum_bkg2 << std::endl;

    hvariable[i]->SetLineColor(2);
    hvariable[i]->SetLineWidth(3);
    hvariable[i]->SetLineStyle(2);
    legname=leg_name[i-2]+"_bkg";
    leg->AddEntry(hvariable[i],legname.c_str(),"l");


	if(axistype[0]=="log"){
		gPad->SetLogy();
	}


	THStack *s = new THStack();
	for(int i=0;i<leg_name.size()*2;i++){
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

	std::string macroname=title_name[0]+".C";
	c1->Save(macroname.c_str());


	return;
}
