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


void check_exist(std::string input_name) {

	TFile* in_file=new TFile(input_name.c_str());

	if(in_file->IsZombie()){
        std::cout<< "Zombie file is : " << input_name << std::endl;
        return;
	}
////TTree *MyLCTuple=(TTree*)in_file->Get("datatrain");

////int nevent = MyLCTuple->GetEntries();

////std::cout << "file exist: " << input_name << " event number: " << nevent << std::endl;

////return;
}
