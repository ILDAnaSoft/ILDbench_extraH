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
				_input_PFOsCollection,
				std::string("PandoraPFOs"));

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputCollectionWithoutIsolatedPhoton",
				"Copy of input collection but without the isolated photon",
				_output_WoIsoPhotonCollection,
				std::string("PandoraPFOsWithoutIsoPhoton") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputCollectionIsolatedPhoton",
				"Output collection of isolated photon in non-forward region",
				_output_IsoPhotonCollection,
				std::string("PandoraIsoPhoton") );

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
	_nEvt = 0;
	printParameters() ;
}

void PandoraIsolatedPhotonFinder::processRunHeader( LCRunHeader* run) { 
} 












void PandoraIsolatedPhotonFinder::processEvent( LCEvent * evt ) { 
	Init(evt);

	analysePFOParticle( _input_PFOCol, _output_IsoPhotonCol, _output_WoIsoPhotonCol,_photon_counter) ;

	Finish(evt);
}









void PandoraIsolatedPhotonFinder::Init(LCEvent* evt) { 
	_nEvt++;
	_global_counter.nevt=_nEvt;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

	_photon_counter.Init();
	_photon_info.Init();

	_photon_counter.nevt  =evt->getEventNumber();
	_photon_counter.weight=evt->getWeight();
	_photon_counter.nrun  =evt->getRunNumber();

	_input_PFOCol = evt->getCollection( _input_PFOsCollection ) ;

	// Output PFOs removed isolated photon 
	_output_WoIsoPhotonCollection= new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE ) ;
	_output_WoIsoPhotonCol->setSubset(true) ;

	// Output PFOs of isolated photon 
	_output_IsoPhotonCol = new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	_output_IsoPhotonCol->setSubset(true);

}


void PandoraIsolatedPhotonFinder::Finish(LCEvent* evt) { 
    // Add pfos to new collection
    evt->addCollection(_output_WoIsoPhotonCol, _output_WoIsoPhotonCollection.c_str() );
    evt->addCollection(_output_IsoPhotonCol,   _output_IsoPhotonCollection.c_str());
        streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
    	<< "   in run:  " << evt->getRunNumber() 
    	<< std::endl ;
}

void PandoraIsolatedPhotonFinder::check( LCEvent * evt ) { 
}

void PandoraIsolatedPhotonFinder::end() { 
	std::cout << "PandoraIsolatedPhotonFinder::end()  " << std::endl;
	std::cout << "the total number         " << _photon_counter.nevt           << std::endl;
    std::cout << "the total photon number  " << _photon_counter.pass_all << std::endl;

}
















