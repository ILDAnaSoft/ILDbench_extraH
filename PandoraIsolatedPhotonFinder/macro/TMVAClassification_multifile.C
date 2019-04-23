/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides examples for the training and testing of the
/// TMVA classifiers.
///
/// As input data is used a toy-MC sample consisting of four Gaussian-distributed
/// and linearly correlated input variables.
/// The methods to be used can be switched on and off by means of booleans, or
/// via the prompt command, for example:
///
///     root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)
///
/// (note that the backslashes are mandatory)
/// If no method given, a default set of classifiers is used.
/// The output file "TMVA.root" can be analysed with the use of dedicated
/// macros (simply say: root -l <macro.C>), which can be conveniently
/// invoked through a GUI that will appear at the end of the run of this macro.
/// Launch the GUI via the command:
///
///     root -l ./TMVAGui.C
///
/// You can also compile and run the example with the following commands
///
///     make
///     ./TMVAClassification <Methods>
///
/// where: `<Methods> = "method1 method2"` are the TMVA classifier names
/// example:
///
///     ./TMVAClassification Fisher LikelihoodPCA BDT
///
/// If no method given, a default set is of classifiers is used
///
/// - Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Root Macro: TMVAClassification
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker


#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification_multifile( TString myMethodList = "" )
{
	// The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
	// if you use your private .rootrc, or run from a different directory, please copy the
	// corresponding lines from .rootrc

	// Methods to be processed can be given as an argument; use format:
	//
	//     mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)

	//---------------------------------------------------------------
	// This loads the library
	TMVA::Tools::Instance();

	// Default MVA methods to be trained + tested
	std::map<std::string,int> Use;

	// Neural Networks (all are feed-forward Multilayer Perceptrons)
	Use["BDTG"]             = 1; // Recommended ANN
	// ---------------------------------------------------------------

	std::cout << std::endl;
	std::cout << "==> Start TMVAClassification" << std::endl;

	// Select methods (don't look at this code - not of interest)
	if (myMethodList != "") {
		for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

		std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
		for (UInt_t i=0; i<mlist.size(); i++) {
			std::string regMethod(mlist[i]);

			if (Use.find(regMethod) == Use.end()) {
				std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
				for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
				std::cout << std::endl;
				return 1;
			}
			Use[regMethod] = 1;
		}
	}

	// --------------------------------------------------------------------------------------------------

	// Here the preparation phase begins

	// Read training and test data
	// (it is also possible to use ASCII format as input -> see TMVA Users Guide)
	TString ftrain_h_e2     = "../results/higgs_e2_lr.root";
	TString ftrain_2f_z     = "../results/2f_l_lr.root";
	TString ftrain_4f_zz_l  = "../results/4f_zz_l_lr.root";
	TString ftrain_4f_zz_sl = "../results/4f_zz_sl_lr.root";
	TString ftrain_4f_sz_ee = "../results/4f_szee_l_lr.root";
	TString ftrain_4f_sz_nn = "../results/4f_sznn_l_lr.root";

	TString ftest_h_e2     = "../results/higgs_e2_lr_test.root";
	TString ftest_2f_z     = "../results/2f_l_lr_test.root";
	TString ftest_4f_zz_l  = "../results/4f_zz_l_lr_test.root";
	TString ftest_4f_zz_sl = "../results/4f_zz_sl_lr_test.root";
	TString ftest_4f_sz_ee = "../results/4f_szee_l_lr_test.root";
	TString ftest_4f_sz_nn = "../results/4f_sznn_l_lr_test.root";

	std::cout << "--- TMVAClassification       : Using input traing file: " << ftrain_h_e2 << std::endl;
	std::cout << "--- TMVAClassification       : Using input traing file: " << ftrain_2f_z << std::endl;
	std::cout << "--- TMVAClassification       : Using input traing file: " << ftrain_4f_zz_l << std::endl;
	std::cout << "--- TMVAClassification       : Using input traing file: " << ftrain_4f_zz_sl << std::endl;
	std::cout << "--- TMVAClassification       : Using input traing file: " << ftrain_4f_sz_ee << std::endl;
	std::cout << "--- TMVAClassification       : Using input traing file: " << ftrain_4f_sz_nn << std::endl;

	// Register the training and test trees

	TChain chainSigTrain("datatrain_sig");
	TChain chainSigTest("datatrain_sig");
	TChain chainBkgTrain("datatrain_bkg");
	TChain chainBkgTest("datatrain_bkg");


	chainSigTrain.Add(ftrain_h_e2);
	chainSigTrain.Add(ftrain_2f_z);
	chainSigTrain.Add(ftrain_4f_zz_l);
	chainSigTrain.Add(ftrain_4f_zz_sl);
	chainSigTrain.Add(ftrain_4f_sz_ee);
	chainSigTrain.Add(ftrain_4f_sz_nn);

	chainBkgTrain.Add(ftrain_h_e2);
	chainBkgTrain.Add(ftrain_2f_z);
	chainBkgTrain.Add(ftrain_4f_zz_l);
	chainBkgTrain.Add(ftrain_4f_zz_sl);
	chainBkgTrain.Add(ftrain_4f_sz_ee);
	chainBkgTrain.Add(ftrain_4f_sz_nn);

	chainSigTest.Add(ftest_h_e2);
	chainSigTest.Add(ftest_2f_z);
	chainSigTest.Add(ftest_4f_zz_l);
	chainSigTest.Add(ftest_4f_zz_sl);
	chainSigTest.Add(ftest_4f_sz_ee);
	chainSigTest.Add(ftest_4f_sz_nn);

	chainBkgTest.Add(ftest_h_e2);
	chainBkgTest.Add(ftest_2f_z);
	chainBkgTest.Add(ftest_4f_zz_l);
	chainBkgTest.Add(ftest_4f_zz_sl);
	chainBkgTest.Add(ftest_4f_sz_ee);
	chainBkgTest.Add(ftest_4f_sz_nn);

	TChain* sigTrain = &chainSigTrain;
	TChain* sigTest  = &chainSigTest;
	TChain* bkgTrain = &chainBkgTrain;
	TChain* bkgTest  = &chainBkgTest;

	// Create a ROOT output file where TMVA will store ntuples, histograms, etc.
	TString outfileName( "TMVA.root" );
	TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

	// Create the factory object. Later you can choose the methods
	// whose performance you'd like to investigate. The factory is
	// the only TMVA object you have to interact with
	//
	// The first argument is the base of the name of all the
	// weightfiles in the directory weight/
	//
	// The second argument is the output file for the training results
	// All TMVA output can be suppressed by removing the "!" (not) in
	// front of the "Silent" argument in the option string
	TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
			"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

	TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
	// If you wish to modify default settings
	// (please check "src/Config.h" to see all available global options)
	//
	//    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
	//    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

	// Define the input variables that shall be used for the MVA training
	// note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
	// [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
	dataloader->AddVariable( "isophoton_obv_small_input_energy"       ,  'F' );
	dataloader->AddVariable( "isophoton_obv_small_num_incone_total"         , 'F' );
	dataloader->AddVariable( "isophoton_obv_small_num_incone_lepton"        , 'F' );
	dataloader->AddVariable( "isophoton_obv_small_cone_energy_ratio_total"  , 'F'  );
	dataloader->AddVariable( "isophoton_obv_small_cone_energy_ratio_photon" , 'F'  );
	dataloader->AddVariable( "isophoton_obv_small_cone_energy_ratio_lepton" , 'F'  );
	dataloader->AddVariable( "isophoton_obv_small_cone_costheta"            , 'F'  );
	dataloader->AddVariable( "isophoton_obv_large_cone_energy_ratio_charge" , 'F'  );
	dataloader->AddVariable( "isophoton_obv_large_cone_energy_ratio_neutral", 'F'  );
	dataloader->AddVariable( "isophoton_obv_large_cone_costheta"            , 'F'  );

//  dataloader->AddVariable( "isophoton_obv_large_cone_energy_ratio_hadron" , 'F'  );
//  dataloader->AddVariable( "isophoton_obv_large_cone_energy_ratio_photon" , 'F'  );
//  dataloader->AddVariable( "isophoton_obv_large_cone_energy_ratio_lepton" , 'F'  );
//  dataloader->AddVariable( "isophoton_obv_small_num_incone_charge"        , 'F' );
//  dataloader->AddVariable( "isophoton_obv_large_cone_energy_ratio_total"  , 'F'  );
//  dataloader->AddVariable( "isophoton_obv_small_num_incone_photon"        , 'F' );
//  dataloader->AddVariable( "isophoton_obv_small_cone_energy_ratio_charge" , 'F'  );
//  dataloader->AddVariable( "isophoton_obv_small_cone_energy_ratio_hadron" , 'F'  );
//  dataloader->AddVariable( "isophoton_obv_small_cone_energy_ratio_neutral", 'F'  );


	//dataloader->AddVariable( "isophoton_obv_small_cone_energy_total"  ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_small_cone_energy_charge" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_small_cone_energy_photon" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_small_cone_energy_lepton" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_small_cone_energy_hadron" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_large_cone_energy_total"  ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_large_cone_energy_charge" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_large_cone_energy_photon" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_large_cone_energy_lepton" ,  'F'  );
	//dataloader->AddVariable( "isophoton_obv_large_cone_energy_hadron" ,  'F'  );
	//
	// You can add so-called "Spectator variables", which are not used in the MVA training,
	// but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
	// input variables, the response values of all trained MVAs, and the spectator variables

	// global event weights per tree (see below for setting event-wise weights)
	Double_t sigWeight     = 1.0;
	Double_t bkgWeight = 1.0;

	// You can add an arbitrary number of signal or background trees
	//dataloader->AddSignalTree    ( signalTree,     signalWeight );
	//dataloader->AddBackgroundTree( background, backgroundWeight );

	// To give different trees for training and testing, do as follows:
	//
	dataloader->AddSignalTree    ( sigTrain, sigWeight, "Training" );
	dataloader->AddSignalTree    ( sigTest,  sigWeight, "Test" );
	dataloader->AddBackgroundTree( bkgTrain, bkgWeight, "Training" );
	dataloader->AddBackgroundTree( bkgTest,  bkgWeight, "Test" );

	// Use the following code instead of the above two or four lines to add signal and background
	// training and test events "by hand"
	// NOTE that in this case one should not give expressions (such as "var1+var2") in the input
	//      variable definition, but simply compute the expression before adding the event
	// ```cpp
	// // --- begin ----------------------------------------------------------
	// std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
	// Float_t  treevars[4], weight;
	//
	// // Signal
	// for (UInt_t ivar=0; ivar<4; ivar++) signalTree->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
	// for (UInt_t i=0; i<signalTree->GetEntries(); i++) {
	//    signalTree->GetEntry(i);
	//    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
	//    // add training and test events; here: first half is training, second is testing
	//    // note that the weight can also be event-wise
	//    if (i < signalTree->GetEntries()/2.0) dataloader->AddSignalTrainingEvent( vars, signalWeight );
	//    else                              dataloader->AddSignalTestEvent    ( vars, signalWeight );
	// }
	//
	// // Background (has event weights)
	// background->SetBranchAddress( "weight", &weight );
	// for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
	// for (UInt_t i=0; i<background->GetEntries(); i++) {
	//    background->GetEntry(i);
	//    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
	//    // add training and test events; here: first half is training, second is testing
	//    // note that the weight can also be event-wise
	//    if (i < background->GetEntries()/2) dataloader->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
	//    else                                dataloader->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
	// }
	// // --- end ------------------------------------------------------------
	// ```
	// End of tree registration

	// Set individual event weights (the variables must exist in the original TTree)
	// -  for signal    : `dataloader->SetSignalWeightExpression    ("weight1*weight2");`
	// -  for background: `dataloader->SetBackgroundWeightExpression("weight1*weight2");`
	//   dataloader->SetBackgroundWeightExpression( "weight" );

	// Apply additional cuts on the signal and background samples (can be different)
	/*
	   &&isophoton_obv_large_num_incone_hadron>0     \
	   &&isophoton_obv_large_cone_energy_total>0     \
	   &&isophoton_obv_large_cone_energy_charge>0    \
	   &&isophoton_obv_large_cone_energy_photon>0    \
	   &&isophoton_obv_large_cone_energy_hadron>0    \
	   &&isophoton_obv_small_num_incone_neutral>=0\
	   &&isophoton_obv_small_cone_energy_ratio_charge>=0  \
	   &&isophoton_obv_small_cone_energy_ratio_hadron>=0  \
	   &&isophoton_obv_small_cone_energy_ratio_neutral>=0 \
	   &&isophoton_obv_small_cone_energy_ratio_photon>=0  \
	   &&isophoton_obv_small_num_incone_photon>=0 \
	   &&isophoton_obv_large_cone_energy_ratio_total>0\
	   &&isophoton_obv_small_num_incone_charge>=0 \
	   &&isophoton_obv_large_cone_energy_ratio_charge>0  \
	   &&isophoton_obv_large_cone_energy_ratio_lepton>0  \

&&isophoton_obv_large_cone_energy_ratio_hadron>=0\
&&isophoton_obv_large_cone_energy_ratio_photon>=0\
&&isophoton_obv_large_cone_energy_ratio_lepton>=0\
&&isophoton_obv_small_num_incone_charge>=0\
&&isophoton_obv_large_cone_energy_ratio_total>=0\
&&isophoton_obv_small_num_incone_photon>=0\
&&isophoton_obv_small_cone_energy_ratio_charge>=0\
&&isophoton_obv_small_cone_energy_ratio_hadron>=0\
&&isophoton_obv_small_cone_energy_ratio_neutral>=0\
*/
	TCut mycuts =    "\
isophoton_obv_small_input_energy>= 0\
&&isophoton_obv_small_num_incone_total>=0  \
&&isophoton_obv_small_num_incone_lepton>=0 \
&&isophoton_obv_small_cone_energy_ratio_total>=0   \
&&isophoton_obv_small_cone_energy_ratio_photon>0  \
&&isophoton_obv_small_cone_energy_ratio_lepton>=0  \
&&isophoton_obv_small_cone_costheta>= -1\
&&isophoton_obv_large_cone_energy_ratio_charge>=0 \
&&isophoton_obv_large_cone_energy_ratio_neutral>=0 \
&&isophoton_obv_large_cone_costheta>= -1\
";

	TCut mycutb = mycuts;




	// Tell the dataloader how to use the training and testing events
	//
	// If no numbers of events are given, half of the events in the tree are used
	// for training, and the other half for testing:
	//
	//    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
	//
	// To also specify the number of testing events, use:
	//
	//    dataloader->PrepareTrainingAndTestTree( mycut,
	//         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
	dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
			"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

	// ### Book MVA methods
	//
	// Please lookup the various method configuration options in the corresponding cxx files, eg:
	// src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
	// it is possible to preset ranges in the option string in which the cut optimisation should be done:
	// "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

	// Cut optimisation

	// TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
	if (Use["BDTG"])
		factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
				"!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

	// For an example of the category classifier usage, see: TMVAClassificationCategory
	//
	// --------------------------------------------------------------------------------------------------
	//  Now you can optimize the setting (configuration) of the MVAs using the set of training events
	// STILL EXPERIMENTAL and only implemented for BDT's !
	//
	//     factory->OptimizeAllMethods("SigEffAt001","Scan");
	//     factory->OptimizeAllMethods("ROCIntegral","FitGA");
	//
	// --------------------------------------------------------------------------------------------------

	// Now you can tell the factory to train, test, and evaluate the MVAs
	//
	// Train MVAs using the set of training events
	factory->TrainAllMethods();

	// Evaluate all MVAs using the set of test events
	factory->TestAllMethods();

	// Evaluate and compare performance of all configured MVAs
	factory->EvaluateAllMethods();

	// --------------------------------------------------------------

	// Save the output
	outputFile->Close();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification is done!" << std::endl;

	delete factory;
	delete dataloader;
	// Launch the GUI for the root macros
	if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

	return 0;
}

int main( int argc, char** argv )
{
	// Select methods (don't look at this code - not of interest)
	TString methodList;
	for (int i=1; i<argc; i++) {
		TString regMethod(argv[i]);
		if(regMethod=="-b" || regMethod=="--batch") continue;
		if (!methodList.IsNull()) methodList += TString(",");
		methodList += regMethod;
	}
	return TMVAClassification_multifile(methodList);
}

