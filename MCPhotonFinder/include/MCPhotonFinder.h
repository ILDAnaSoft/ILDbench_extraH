/**
 * @brief Marlin processor for finding isolated photons.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of MCParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef MCPhotonFinder_h
#define MCPhotonFinder_h 

#include "MCPhotonFinder_Element_Observable.h"

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;

class MCPhotonFinder : public Processor {

	public:

		virtual Processor*  newProcessor() { return new MCPhotonFinder ; }

		MCPhotonFinder() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

    public:
	protected:

    	/** Input collection */
    	std::string _input_MCsCollection;

    	/** Output collection of isolated photons */
    	std::string _output_IsoPhotonCollection;

    	/** Output collection (all input with isolated photons removed) */
    	std::string _output_WoIsoPhotonCollection;


    	LCCollection*    _input_MCsCol;
		LCCollectionVec* _output_WoIsoPhotonCol;
	    LCCollectionVec* _output_IsoPhotonCol;

    	/** If set to true, uses Energy cuts in the central region*/
    	bool  _useEnergy;
    	float _minEnergyCut;
    	float _maxEnergyCut;

    	bool  _usePolarAngle;
    	float _minCosTheta;
    	float _maxCosTheta;

    	bool  _useForwardEnergy;
    	float _minForwardEnergyCut;
    	float _maxForwardEnergyCut;

		// if this is open, _maxCosTheta = _minForwardCosTheta automatically
    	bool  _useForwardPolarAngle;
    	float _minForwardCosTheta;
    	float _maxForwardCosTheta;


    	/** If set to true, uses rectangular cuts for isolation */
    	bool  _useIsolationCone;
    	float _minCosConeAngle;
    	float _maxCosConeAngle;
    	float _ConeEnergyRatio;


		int   _nEvt;

		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);

		bool  analyseMCParticle( LCCollection* input_mc, LCCollectionVec* output_photon,LCCollectionVec* output_mcother, MCPhotonFinder_Single_Counter& counter);

    	/** Calculates the cone energy */
    	float getConeEnergy( MCParticle* mc, std::vector<MCParticle*> all ) ;

    	/** Returns true if mc is an isolated photon */
    	int  IsIsolatedPhoton( MCParticle* mc, std::vector<MCParticle*> all) ;

    	/** Returns true if it passes photon ID cuts */
    	bool IsIsoPhoton( MCParticle* mc, std::vector<MCParticle*> all) ;

    	/** Returns true if it passes photon ID cuts */
    	bool IsForwardPhoton( MCParticle* mc ) ;

    	/** Returns true if it passes photon ID cuts */
    	bool IsCentralPhoton( MCParticle* mc ) ;

		MCPhotonFinder_Single_Counter       _photon_counter;
		MCPhotonFinder_Global_Counter       _global_counter;
		MCPhotonFinder_Information          _photon_info;

} ;

#endif

