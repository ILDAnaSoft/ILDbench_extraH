#include "MCLevelClassify.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <cmath>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <IMPL/LCCollectionVec.h>

// ----- include for verbosity dependend logging ---------
#include <marlin/VerbosityLevels.h>

#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>

using namespace lcio ;
using namespace marlin ;
using namespace std;

MCLevelClassify aMCLevelClassify ;

MCLevelClassify::MCLevelClassify()
	: Processor("MCLevelClassify") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputCollection" ,
				"Input collection of MCParticles",
				_inputMCsCollection,
				std::string("MCParticle"));

		//Output Collection 
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputCollectionHardScattering",
				"Output collection of Hard Scattering particles",
				_outputHardScatteringCollection,
				std::string("MCHS") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputCollectionPythiaStable",
				"Output collection of Pythia Stable particles",
				_outputPythiaStableCollection,
				std::string("MCPS") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputCollectionDetectorSimulation",
				"Output collection of Detector Simulation particles",
				_outputDetectorSimulationCollection,
				std::string("MCDS") );


		//Input collection from IsolatedLeptonTaggingProcessor
		registerInputCollection( LCIO::LCRELATION,
				"InputRecoMCTruthLink",
				"Relation between MC and PFO particles",
				_pfomcsRelation,
				std::string("RecoMCTruthLink"));

		registerInputCollection( LCIO::LCRELATION,
				"InputMCTruthRecoLink",
				"Relation between PFO particles and MC",
				_mcspfoRelation,
				std::string("MCTruthRecoLink"));

		//Output root 
		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );

	}


void MCLevelClassify::init() { 
	std::cout << "   init MCLevelClassify " << std::endl ;
	_nEvt = 0;
	_nRun = 0;
	printParameters() ;
	_global_counter.Init();
	_single_counter.Init();
	_counter       .Init();

	_outputHSCol.Set_Switch(_output_switch_collection);
	_outputHSCol.Set_Name(_outputHardScatteringCollection);
	_outputPSCol.Set_Switch(_output_switch_collection);
	_outputPSCol.Set_Name(_outputPythiaStableCollection);
	_outputDSCol.Set_Switch(_output_switch_collection);
	_outputDSCol.Set_Name(_outputDetectorSimulationCollection);

	if(_output_switch_root){
		makeNTuple();
	}
}

void MCLevelClassify::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 












void MCLevelClassify::processEvent( LCEvent * evt ) { 
	Init(evt);

	bool JMC=analyseMCParticle( _MCsCol, _outputHSCol, _outputPSCol, _outputDSCol, _info, _counter.MCs) ;

	Counter(JMC, evt);

	Finish(evt);
}





void MCLevelClassify::Counter(bool JMC, LCEvent* evt){
	if(JMC){
		_global_counter.pass_MCs++;
		_global_counter.pass_all++;
		_single_counter.pass_MCs++;
		_single_counter.pass_all++;
	}
	else{
		ToolSet::ShowMessage(2,"in processEvent: not pass analyseMCParticle ");
	}
}


void MCLevelClassify::Init(LCEvent* evt) { 
	_nEvt++;
	_global_counter.nevt=_nEvt;
	_global_counter.nrun=_nRun;
	_global_counter.gweight=1;
	if( _nEvt % 50 == 0 ){
		if(_output_switch_collection&&!_output_switch_root){
		}
		else{
			ToolSet::ShowMessage(1,"processing event",_nEvt);
		}
	} 

	_info.Init();
	_counter.Init();
	_single_counter.Init();

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run  =evt->getRunNumber();

	try{
		_MCsCol= evt->getCollection( _inputMCsCollection) ;
	}
	catch(...){
		std::cout << "no MCs in this event" << std::endl;
	}
	_navpfomcs = new LCRelationNavigator( evt->getCollection( _pfomcsRelation ) );
	_navmcspfo = new LCRelationNavigator( evt->getCollection( _mcspfoRelation ) );

	_outputHSCol.Set_Collection_MCParticle() ;
	_outputPSCol.Set_Collection_MCParticle() ;
	_outputDSCol.Set_Collection_MCParticle() ;

	ToolSet::CMC::Set_Nav_From_MC_To_RC(_navmcspfo);
}


void MCLevelClassify::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}
	_outputHSCol.Add_Collection(evt);
	_outputPSCol.Add_Collection(evt);
	_outputDSCol.Add_Collection(evt);
}

void MCLevelClassify::check( LCEvent * evt ) { 
}

void MCLevelClassify::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();

}


void MCLevelClassify::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	//Define root tree
	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_counter       .Fill_Data(_datatrain);
	_info          .Fill_Data(_datatrain);
	return;

}




































