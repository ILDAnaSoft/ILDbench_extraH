/**
 * @brief Marlin processor for finding isolated photons.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of MCParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef MCLeptonTagging_h
#define MCLeptonTagging_h 1

#include "MCLeptonTagging_Element_Observable.h"

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

class MCLeptonTagging : public Processor {

	public:

		virtual Processor*  newProcessor() { return new MCLeptonTagging ; }

		MCLeptonTagging() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		/** Input collection */
		std::string _inputMCsCollection;

		/** Output collection of isolated photons */
		std::string _outputLeptonCollection;

		/** Output collection (all input with isolated photons removed) */
		std::string _outputMCsWoLeptonCollection;

		LCCollection*    _MCsCol;
		MCLeptonTagging_Output_Collection _outputLeptonCol;
		MCLeptonTagging_Output_Collection _outputWoLeptonCol;

		bool _output_switch_root;
		bool _output_switch_collection;

		// input para
		int   _lep_type;

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


		bool analyseMCParticle( LCCollection* inputmcCol, MCLeptonTagging_Output_Collection &outputLeptonCol,MCLeptonTagging_Output_Collection &outputWoleptonCol, MCLeptonTagging_Information_Single &info, MCLeptonTagging_Function_Counter &counter);
		void checkIsoLeptons(std::vector<MCParticle*> input, std::vector<MCParticle*> &IsoLep, std::vector<MCParticle*> &mcs_WO_IsoLep );
		bool IsIsoLep( MCParticle* mcs, std::vector<MCParticle*> allmcs) ;
		bool IsCharged( MCParticle* mcs ) ;
		int  IsLepton( MCParticle* mcs ) ;


		//self-defined variable
		MCLeptonTagging_Single_Counter       _single_counter;
		MCLeptonTagging_Global_Counter       _global_counter;
		MCLeptonTagging_Counter              _counter;
		MCLeptonTagging_Information          _info;
		CLEPTON_CUT                          _cut;
} ;

#endif

