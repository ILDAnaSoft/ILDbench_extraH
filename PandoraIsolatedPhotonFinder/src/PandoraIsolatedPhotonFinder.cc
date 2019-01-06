#include "PandoraIsolatedPhotonFinder.h"

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

PandoraIsolatedPhotonFinder aPandoraIsolatedPhotonFinder ;

PandoraIsolatedPhotonFinder::PandoraIsolatedPhotonFinder()
	: Processor("PandoraIsolatedPhotonFinder") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputCollection" ,
				"Input collection of ReconstructedParticles",
				_inputPFOsCollection,
				std::string("PandoraPFOs"));

		//Output Collection 
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputCollectionWithoutIsolatedPhoton",
				"Copy of input collection but without the isolated photon",
				_outputWoIsoPhotonCollection,
				std::string("PandoraPFOsWoIsoPhoton") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputCollectionIsolatedPhoton",
				"Output collection of isolated photon in non-forward region",
				_outputIsoPhotonCollection,
				std::string("PandoraIsoPhoton") );

		//Output root 
		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );

		//Input parameters 
		registerProcessorParameter( "UseEnergy",
				"Use energy cut",
				_useEnergy,
				bool(true));

		registerProcessorParameter( "MinimalEnergyCut",
				"The minimal energy for a isolated photon",
				_minEnergyCut,
				float(30));

		registerProcessorParameter( "MaximalEnergyCut",
				"The maximal energy for a isolated photon",
				_maxEnergyCut,
				float(-1));

		registerProcessorParameter( "UsePolarAngle",
				"Use cosine polar angle cut",
				_usePolarAngle,
				bool(true));

		registerProcessorParameter( "MinimalPolarAngle",
				"The minimal cosine polar angle for a isolated photon",
				_minCosTheta,
				float(0.0));

		registerProcessorParameter( "MaximalPollarAngle",
				"The maximal cosine polar angle for a isolated photon",
				_maxCosTheta,
				float(0.95));

		registerProcessorParameter( "UseForwardEnergy",
				"Use energy cut in the forward region",
				_useForwardEnergy,
				bool(true));

		registerProcessorParameter( "MinimalForwardEnergyCut",
				"The minimal energy for a isolated photon in the forward region",
				_minForwardEnergyCut,
				float(30));

		registerProcessorParameter( "MaximalForwardEnergyCut",
				"The maximal energy for a isolated photon in the forward region",
				_maxForwardEnergyCut,
				float(-1));

		registerProcessorParameter( "UseForwardAngle",
				"Use forward angle cut",
				_useForwardPolarAngle,
				bool(true));

		registerProcessorParameter( "MinimalForwardPollarAngle",
				"The minimal cosine angle to define a forward region",
				_minForwardCosTheta,
				float(0.95));

		registerProcessorParameter( "MaximalForwardPollarAngle",
				"The maximal cosine angle to define a forward region",
				_maxForwardCosTheta,
				float(0.98));

		registerProcessorParameter( "UseIsolationCone",
				"Define a cone using the photon as the axis, the other particle can not lie in the cone",
				_useIsolationCone,
				bool(false));

		registerProcessorParameter( "MinimalCosConeAngle",
				"The minimal cone size",
				_minCosConeAngle,
				float(-1));

		registerProcessorParameter( "MaximalCosConeAngle",
				"The maximal cone size",
				_maxCosConeAngle,
				float(0.9));

		registerProcessorParameter( "ConeEnergyRatio",
				"The maximal cone size",
				_ConeEnergyRatio,
				float(0.95));

	}


void PandoraIsolatedPhotonFinder::init() { 
	std::cout << "   init PandoraIsolatedPhotonFinder " << std::endl ;
	printParameters() ;

	_nEvt = 0;
	_nRun = 0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputWoIsoPhotonCol.Set_Switch(_output_switch_collection);
	_outputWoIsoPhotonCol.Set_Name(_outputWoIsoPhotonCollection);
	_outputIsoPhotonCol.Set_Switch(_output_switch_collection);
	_outputIsoPhotonCol.Set_Name(_outputIsoPhotonCollection);

	if(_output_switch_root){
		makeNTuple();
	}
}

void PandoraIsolatedPhotonFinder::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 












void PandoraIsolatedPhotonFinder::processEvent( LCEvent * evt ) { 
	Init(evt);

	bool JPFO=analysePFOParticle( _PFOCol, _outputIsoPhotonCol, _outputWoIsoPhotonCol,_info.isophoton,_counter.PFO) ;

	Counter(JPFO, evt);

	Finish(evt);
}




void PandoraIsolatedPhotonFinder::Counter(bool JPFO, LCEvent* evt){
	if(JPFO){
		_global_counter.pass_PFO++;
		_global_counter.pass_all++;
		_single_counter.pass_PFO++;
		_single_counter.pass_all++;
	}
	else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}
}






void PandoraIsolatedPhotonFinder::Init(LCEvent* evt) { 
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
		_PFOCol = evt->getCollection( _inputPFOsCollection ) ;
	}
	catch(...){
		std::cout << "no PFO without overlay in this event" << std::endl;
	}


	_outputWoIsoPhotonCol .Set_Collection_RCParticle();
	_outputIsoPhotonCol.Set_Collection_RCParticle();

}


void PandoraIsolatedPhotonFinder::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}
// Add mcs to new collection
	_outputWoIsoPhotonCol.Add_Collection(evt);
	_outputIsoPhotonCol.Add_Collection(evt);
}

void PandoraIsolatedPhotonFinder::check( LCEvent * evt ) { 
}

void PandoraIsolatedPhotonFinder::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();

}




void PandoraIsolatedPhotonFinder::makeNTuple() {

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


















































