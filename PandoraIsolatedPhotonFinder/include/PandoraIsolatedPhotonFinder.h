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

#include <EVENT/LCCollection.h>
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
		std::string _inputPFOsCollection;

		/** Output collection of isolated photons */
		std::string _outputIsoPhotonCollection;

		/** Output collection (all input with isolated photons removed) */
		std::string _outputWoIsoPhotonCollection;

		LCCollection*    _PFOCol;
		PandoraIsolatedPhotonFinder_Output_Collection _outputWoIsoPhotonCol;
	    PandoraIsolatedPhotonFinder_Output_Collection _outputIsoPhotonCol;

		bool _output_switch_root;
		bool _output_switch_collection;

		// output
		std::string _rootfilename;
		TFile*      _outfile;
		TTree*      _datatrain;
		void makeNTuple();

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

		//internal para
		int   _nEvt;
		int   _nRun; 

		// internal function 
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void  Counter(bool JPFO, LCEvent* evt);


		bool  analysePFOParticle( LCCollection* input_pfo, PandoraIsolatedPhotonFinder_Output_Collection& outputPhoton, PandoraIsolatedPhotonFinder_Output_Collection& outputWoPhotonCol, PandoraIsolatedPhotonFinder_Information_Single& info, PandoraIsolatedPhotonFinder_Function_Counter& counter);


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

		PandoraIsolatedPhotonFinder_Global_Counter       _global_counter;
		PandoraIsolatedPhotonFinder_Single_Counter       _single_counter;
		PandoraIsolatedPhotonFinder_Counter              _counter;
		PandoraIsolatedPhotonFinder_Information          _info;
} ;

#endif

