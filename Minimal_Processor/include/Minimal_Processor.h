/**
 * @brief Marlin processor for finding jet.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef Minimal_Processor_h
#define Minimal_Processor_h 1

#include "Minimal_Processor_Element_Observable.h"
#include <string>
#include <map>

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;




class Minimal_Processor : public Processor {

	public:

		virtual Processor*  newProcessor() { return new Minimal_Processor ; }

		Minimal_Processor() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		// input string 
		std::string _inputPFOsCollection;
		std::string _inputMCsCollection;

		std::string _mcpfoRelation;
		std::string _pfomcRelation;
		std::string _mctrkRelation;
		std::string _trkmcRelation;




		// input collection 
		LCCollection* _pfoCol;
		LCCollection* _mcCol;

		LCRelationNavigator* _navpfomc;
		LCRelationNavigator* _navmcpfo;
		LCRelationNavigator* _navtrkmc;
		LCRelationNavigator* _navmctrk;

		// input para
		// none



		// output collection 
		bool _output_switch_collection;
		std::string _outputPFOCollection;
		Minimal_Processor_Output_Collection _outputPFOCol;

		// output root 
		bool _output_switch_root;
		std::string _rootfilename;
		TFile* _outfile;
		TTree* _datatrain;
		void makeNTuple();

		//internal function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void Counter(bool JMC, bool JPFO, LCEvent* evt);

		/** Calculates the cone energy */
		bool analyseMCParticle( LCCollection* MCs_col, LCRelationNavigator* navMCToPFO, Minimal_Processor_Information_Single &info, Minimal_Processor_Function_Counter& counter);
		bool analysePFOParticle( LCCollection* PFOs_col, Minimal_Processor_Output_Collection& outputPFOCol, LCRelationNavigator* navPFOToMC, Minimal_Processor_Information_Single &info, Minimal_Processor_Function_Counter& counter);




		//internal para 
		int  _nEvt; 
		int _nRun;

		Minimal_Processor_Counter              _counter;
		Minimal_Processor_Global_Counter       _global_counter;
		Minimal_Processor_Single_Counter       _single_counter;
		Minimal_Processor_Information          _info;

} ;

#endif

