/**
 * @brief Marlin processor for finding jet.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef PFOLeptonTagging_h
#define PFOLeptonTagging_h 1

#include "PFOLeptonTagging_Element_Observable.h"


// Only ILCSoft related header file
#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;




class PFOLeptonTagging : public Processor {

	public:

		virtual Processor*  newProcessor() { return new PFOLeptonTagging ; }

		PFOLeptonTagging() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		// input string 
		std::string _inputMCsLeptonCollection;


		// input collection 
		LCCollection* _mcsLeptonCol;

		// input para

		// output collection 
		bool _output_switch_collection;
		std::string _outputPFOLeptonCollection;

		PFOLeptonTagging_Output_Collection _outputPFOLeptonCol;

		// output root 
		bool _output_switch_root;
		std::string _rootfilename;
		TFile* _outfile;
		TTree* _datatrain;
		void makeNTuple();

		//internal function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void Counter(int JMC1, LCEvent* evt);

		/** Calculates the cone energy */

		int analyseMCParticle( LCCollection* Input_MCsLeptonCol, 
			PFOLeptonTagging_Output_Collection& NewPFOIsoLeptonCol, 
			PFOLeptonTagging_Information&info, PFOLeptonTagging_Function_Counter& counter) ;

		//internal para 
		int  _nEvt; 
		int _nRun;

		PFOLeptonTagging_Global_Counter       _global_counter;
		PFOLeptonTagging_Single_Counter       _single_counter;
		PFOLeptonTagging_Information          _info;
		PFOLeptonTagging_Counter              _counter;

} ;

#endif

