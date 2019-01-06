/**
 * @brief Marlin processor for finding jet.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef Overlay_Removal_h
#define Overlay_Removal_h 1

#include "Overlay_Removal_Element_Observable.h"

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;

class Overlay_Removal : public Processor {

	public:

		virtual Processor*  newProcessor() { return new Overlay_Removal ; }

		Overlay_Removal() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		// input 
		std::string _inputMCsCollection;
		LCCollection* _in_mcCol;

		std::string _input_mcpfoRelation;
		LCRelationNavigator* _nav_MC_to_PFO;

		std::string _inputJetPOsCollection;
		LCCollection* _in_jetpoCol;

		std::string _inputIsolepsCollection;
		LCCollection* _in_islCol;



		std::string _outputPFOWoOverlayCollection;
		Overlay_Removal_Output_Collection _outputPFOWoOverlayCol;

		std::string _outputMCsWoOverlayCollection;
		Overlay_Removal_Output_Collection _outputMCsWoOverlayCol;


		bool _output_switch_collection;
		bool _output_switch_root;

		// output 
		std::string _rootfilename;
		TFile*      _outfile;
		TTree*      _datatrain;
		void makeNTuple();


		//internal para
		int  _nEvt; 
		int _nRun;




		//function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void  Counter(bool JMC, LCEvent* evt);


		/** Calculates the cone energy */
		std::vector<MCParticle*>            analyseMCParticle( LCCollection* MCs_col, Overlay_Removal_Information_Single &info);
		std::vector<ReconstructedParticle*> analyseJet       ( LCCollection* Isolep, LCCollection* Jet_POs_col, Overlay_Removal_Information_Single &info);




	public:
		Overlay_Removal_Global_Counter      _global_counter;
		Overlay_Removal_Single_Counter      _single_counter;
		Overlay_Removal_Counter             _counter;
		Overlay_Removal_Information         _info;

} ;

#endif

