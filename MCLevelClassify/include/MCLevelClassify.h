/**
 * @brief Marlin processor for finding isolated photons.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of MCParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef MCLevelClassify_h
#define MCLevelClassify_h 1

#include "MCLevelClassify_Element_Observable.h"

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/MCParticle.h>
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;

class MCLevelClassify : public Processor {

	public:

		virtual Processor*  newProcessor() { return new MCLevelClassify ; }

		MCLevelClassify() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		/** Input collection */
		std::string _inputMCsCollection;

		/** Output collection of isolated photons */
		std::string _outputHardScatteringCollection;

		/** Output collection (all input with isolated photons removed) */
		std::string _outputPythiaStableCollection;
		std::string _outputDetectorSimulationCollection;

		LCCollection*    _MCsCol;
		LCCollectionVec* _outputHSCol;
	    LCCollectionVec* _outputPSCol;
	    LCCollectionVec* _outputDSCol;

		std::string _pfomcsRelation;
		LCRelationNavigator* _navpfomcs;
		std::string _mcspfoRelation;
		LCRelationNavigator* _navmcspfo;

		int   _nEvt; 
		int   _nRun; 


		void Init  (LCEvent* evt); 
		void Finish(LCEvent* evt);
		void Counter(int JMC, LCEvent* evt);


		bool analyseMCParticle( LCCollection* inputmcCol, LCCollectionVec* outputHSCol,LCCollectionVec* outpuwPSCol, LCCollectionVec* outpuDSCol);


		MCLevelClassify_Single_Counter       _single_counter;
		MCLevelClassify_Global_Counter       _global_counter;
		MCLevelClassify_Counter              _counter;
		MCLevelClassify_Information          _info;
} ;

#endif

