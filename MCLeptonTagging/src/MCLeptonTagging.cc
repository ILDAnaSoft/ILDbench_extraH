#include "MCLeptonTagging.h"

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

MCLeptonTagging aMCLeptonTagging ;

MCLeptonTagging::MCLeptonTagging()
	: Processor("MCLeptonTagging") {

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
				"OutputCollectionWoLepton",
				"Output collection of Without Isolated Lepton",
				_outputMCsWoLeptonCollection,
				std::string("MCWoLepton") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputCollectionLepton",
				"Output collection of Isolated Lepton",
				_outputLeptonCollection,
				std::string("MCLepton") );

		//Input parameters 
		registerProcessorParameter( "",
				"wants to output which type particle elec/muon (11/13), default are both",
				_lep_type,
				int(0) );

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


void MCLeptonTagging::init() { 
	std::cout << "   init MCLeptonTagging " << std::endl ;
	_nEvt = 0;
	_nRun = 0;
	printParameters() ;
	_global_counter.Init();
	_single_counter.Init();
	_counter       .Init();


	_outputLeptonCol.Set_Switch(_output_switch_collection);
	_outputLeptonCol.Set_Name(_outputLeptonCollection);
	_outputWoLeptonCol.Set_Switch(_output_switch_collection);
	_outputWoLeptonCol.Set_Name(_outputMCsWoLeptonCollection);

	if(_output_switch_root){
		makeNTuple();
	}
}

void MCLeptonTagging::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 












void MCLeptonTagging::processEvent( LCEvent * evt ) { 
	Init(evt);

	bool JMC=analyseMCParticle( _MCsCol, _outputLeptonCol, _outputWoLeptonCol, _info.isolep,_counter.MCs) ;

	Counter(JMC, evt);

	Finish(evt);
}





void MCLeptonTagging::Counter(bool JMC, LCEvent* evt){
	if(JMC){
		_global_counter.pass_MCs++;
		_global_counter.pass_all++;
		_single_counter.pass_MCs++;
		_single_counter.pass_all++;
	}
	else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}
}


void MCLeptonTagging::Init(LCEvent* evt) { 
	_nEvt++;
	_global_counter.nevt=_nEvt;
	_global_counter.nrun=_nRun;
	_global_counter.gweight=1;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

	_info.Init();
	_counter.Init();
	_single_counter.Init();

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run   =evt->getRunNumber();

	try{
		_MCsCol= evt->getCollection( _inputMCsCollection) ;
	}
	catch(...){
		std::cout << "no MCs without overlay in this event" << std::endl;
	}


	_outputLeptonCol  .Set_Collection_MCParticle() ;
	_outputWoLeptonCol.Set_Collection_MCParticle() ;

}


void MCLeptonTagging::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}
	_outputLeptonCol  .Add_Collection(evt);
	_outputWoLeptonCol.Add_Collection(evt);

}

void MCLeptonTagging::check( LCEvent * evt ) { 
}

void MCLeptonTagging::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
}


void MCLeptonTagging::makeNTuple() {

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

























