/**
 * @brief Marlin processor for finding isolated photons.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef PandoraIsolatedPhotonFinder_h
#define PandoraIsolatedPhotonFinder_h 1

#include "PandoraIsolatedPhotonFinder_Element_Observable.h"

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/ReconstructedParticle.h>
#include <EVENT/MCParticle.h>
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;

class PandoraIsolatedPhotonFinder : public Processor {

	public:

		virtual Processor*  newProcessor() { return new PandoraIsolatedPhotonFinder ; }

		PandoraIsolatedPhotonFinder() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		/** Input collection */
		std::string _input_PFOsCollection;

		/** Output collection of isolated photons */
		std::string _output_IsoPhotonCollection;

		/** Output collection (all input with isolated photons removed) */
		std::string _output_WoIsoPhotonCollection;

		LCCollection* _input_PFOCol;
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
		bool _useIsolationCone;
		float _minCosConeAngle;
		float _maxCosConeAngle;
		float _ConeEnergyRatio;

		int   _nEvt; 


		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);


		bool  analysePFOParticle( LCCollection* input_pfo, LCCollectionVec* output_photon,LCCollectionVec* output_other, PandoraIsolatedPhotonFinder_Single_Counter& counter);


		/** Calculates the cone energy */
		float getConeEnergy( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all) ;


		/** Returns true if pfo is an isolated photon */
		int IsIsolatedPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all) ;

		/** Returns true if it passes photon ID cuts */
		bool IsIsoPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all) ;

		/** Returns true if it passes photon ID cuts */
		bool IsForwardPhoton( ReconstructedParticle* pfo ) ;

		/** Returns true if it passes photon ID cuts */
		bool IsCentralPhoton( ReconstructedParticle* pfo ) ;

		PandoraIsolatedPhotonFinder_Single_Counter       _photon_counter;
		PandoraIsolatedPhotonFinder_Global_Counter       _global_counter;
		PandoraIsolatedPhotonFinder_Information          _photon_info;
} ;

#endif

