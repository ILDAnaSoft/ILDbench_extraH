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

		/** Output collection of different levels*/
		std::string _outputHardScatteringCollection;
		std::string _outputPythiaStableCollection;
		std::string _outputDetectorSimulationCollection;

		LCCollection*    _MCsCol;
		MCLevelClassify_Output_Collection _outputHSCol;
		MCLevelClassify_Output_Collection _outputPSCol;
		MCLevelClassify_Output_Collection _outputDSCol;

		bool _output_switch_root;
		bool _output_switch_collection;


		std::string _pfomcsRelation;
		LCRelationNavigator* _navpfomcs;
		std::string _mcspfoRelation;
		LCRelationNavigator* _navmcspfo;

		// output
		std::string _rootfilename;
		TFile*      _outfile;
		TTree*      _datatrain;
		void makeNTuple();


		// internal para
		int   _nEvt; 
		int   _nRun; 


		// internal function 
		void Init  (LCEvent* evt); 
		void Finish(LCEvent* evt);
		void Counter(bool JMC, LCEvent* evt);


		//bool analyseMCParticle( LCCollection* inputmcCol, LCCollectionVec* outputHSCol,LCCollectionVec* outputPSCol, LCCollectionVec* outputDSCol, MCLevelClassify_Information& info, MCLevelClassify_Function_Counter &counter);
		bool analyseMCParticle( LCCollection* inputmcCol, MCLevelClassify_Output_Collection& outputHSCol,MCLevelClassify_Output_Collection& outputPSCol, MCLevelClassify_Output_Collection& outputDSCol, MCLevelClassify_Information& info, MCLevelClassify_Function_Counter &counter);


		//self-defined variable
		MCLevelClassify_Single_Counter       _single_counter;
		MCLevelClassify_Global_Counter       _global_counter;
		MCLevelClassify_Counter              _counter;
		MCLevelClassify_Information          _info;
} ;

#endif

