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

void plot_1D_different_observable_vec_different_tree(std::vector<std::string> input_name,std::vector<std::string> title_name,std::vector<std::string> leg_name, std::vector<std::string> tree_name,std::vector<float> region,std::vector<string> axistype){

	if(region.size()!=3 || axistype.size()!=1){
		std::cout << "wrong input, please use region[6] and axistype[2] for input";
	}



	std::vector<TFile*> in_file;

	for(int i=0;i<input_name.size();i++){
		TFile* in_file_tmp=new TFile(input_name[i].c_str());
		in_file.push_back(in_file_tmp);
	}

	TCanvas *c1=new TCanvas("c1"," ",1000,700);
	auto leg = new TLegend(0.4,0.6,0.6,0.8);
	//leg->SetHeader("e^{+}e^{-}->#mu^{+}#mu^{-} + X @ 500 GeV","C"); 

	string x_name=";M (GeV)";
	string y_name=";Events";
	string axis_name=x_name+y_name;
	int colornum=1;
	THStack *s = new THStack();

	for(int i=0;i<input_name.size();i++){
		int stylenum=1;
		std::vector<TH1F*> hvariable_i;
		for(int j=0;j<tree_name.size();j++){
			std::cout << "tree "<<tree_name[j]<<std::endl;
			TTree *MyLCTuple=(TTree*)in_file[i]->Get(tree_name[j].c_str());

			std::vector<float> *variable=0;
			TBranch *branch=0;
			MyLCTuple->SetBranchAddress(title_name[0].c_str(), &variable, &branch);

			std::stringstream num, num1;
			std::string fnum, fnum1;
			num << i;
			num >> fnum;
			num1 << j;
			num1 >> fnum1;
			std::string hname=title_name[0]+"_"+fnum+"_"+fnum1;
			std::cout << hname << std::endl;
			hvariable_i.push_back(new TH1F(hname.c_str(),hname.c_str(),region[0],region[1],region[2]));
			hvariable_i[j]->SetTitle(axis_name.c_str());


			int nevent = MyLCTuple->GetEntries();
			for(int event=0;event<nevent;event++){
				MyLCTuple->GetEntry(event);
				for(unsigned int vsize=0;vsize<variable->size();vsize++){
					hvariable_i[j]->Fill(variable->at(vsize));
				}
			}

			hvariable_i[j]->SetLineColor(colornum);
			hvariable_i[j]->SetLineWidth(3);
			hvariable_i[j]->SetLineStyle(stylenum);
			hvariable_i[j]->GetYaxis()->SetTitle(y_name.c_str());
			hvariable_i[j]->GetXaxis()->SetTitle(x_name.c_str());
			std::string legname=leg_name[j];
			if(i==0){
				leg->AddEntry(hvariable_i[j],legname.c_str(),"l");
			}
			s->Add(hvariable_i[j]);

			stylenum++;
		}
		colornum++;
		if(colornum==3||colornum==5||colornum==8||colornum==10||colornum==11){
			colornum++;
		}
	}


	if(axistype[0]=="log"){
		gPad->SetLogy();
	}

	s->Draw("nostack");
	leg->Draw();

	c1->Update();
	TImage *img = TImage::Create();
	img->FromPad(c1);
	std::string pngname=title_name[0]+".png";
	img->WriteImage(pngname.c_str());


	return;
}
