#pragma once
#ifndef ANALYSE_SUMMARIZE_PLOT_H
#define ANALYSE_SUMMARIZE_PLOT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>
#include <vector>
#include <inttypes.h>
#include "yaml-cpp/yaml.h"
#include <cmath>


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
#include <iomanip>
#include <map>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


#include "Function/Fbasic.h" 
#include "Function/Ffile.h" 
#include "Lib/MessageFormat.h"
#include "Class/DrawClass.h"
#include "AnalyseClass/AnalyseClass.h"
#include "AnalyseClass/Plot.h"
#include "Abasic.h"
#include "Make_Table.h"
#include "AnalyseClass/File.h"


void Analyse_Summarize_Plot_Pre(CDraw &para);

void Analyse_Summarize_Plot(CDraw &para, std::vector<std::string> &sig_name, std::vector<std::string> &file_short_name,AFile& file_name);

void Analyse_Summarize_Plot_Complete_Pre(CDraw &para);

void Analyse_Summarize_Plot_Complete(CDraw &para, std::vector<std::vector<std::string> >&sig_name, AFile& file_name);
#endif