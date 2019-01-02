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


	}


void MCLevelClassify::init() { 
	std::cout << "   init MCLevelClassify " << std::endl ;
	_nEvt = 0;
	_nRun = 0;
	printParameters() ;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();
}

void MCLevelClassify::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 












void MCLevelClassify::processEvent( LCEvent * evt ) { 
	Init(evt);

	bool JMC=analyseMCParticle( _MCsCol, _outputHSCol, _outputPSCol, _outputDSCol) ;

	Counter(JMC, evt);

	Finish(evt);
}





void MCLevelClassify::Counter(int JMC, LCEvent* evt){
	if(JMC==1){
		_global_counter.pass_MCs++;
		_single_counter.pass_MCs++;
	}
	else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}
}


void MCLevelClassify::Init(LCEvent* evt) { 
	_nEvt++;
	_global_counter.nevt=_nEvt;
	_global_counter.nrun=_nRun;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

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


	_outputHSCol= new LCCollectionVec( LCIO::MCPARTICLE) ;
	_outputHSCol->setSubset(true) ;

	_outputPSCol= new LCCollectionVec( LCIO::MCPARTICLE);
	_outputPSCol->setSubset(true);

	_outputDSCol= new LCCollectionVec( LCIO::MCPARTICLE);
	_outputDSCol->setSubset(true);

	ToolSet::CMC::Set_Nav_From_MC_To_RC(_navmcspfo);
}


void MCLevelClassify::Finish(LCEvent* evt) { 
	// Add pfos to new collection
	evt->addCollection(_outputHSCol,_outputHardScatteringCollection.c_str() );
	evt->addCollection(_outputPSCol,_outputPythiaStableCollection.c_str());
	evt->addCollection(_outputDSCol,_outputDetectorSimulationCollection.c_str());
	streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		<< "   in run:  " << evt->getRunNumber() 
		<< std::endl ;
}

void MCLevelClassify::check( LCEvent * evt ) { 
}

void MCLevelClassify::end() { 
	std::cout << "MCLevelClassify::end()  " << name() 
		<< " processed " << _nEvt << " events in " << _nRun << " runs "
		<< std::endl ;

}
















