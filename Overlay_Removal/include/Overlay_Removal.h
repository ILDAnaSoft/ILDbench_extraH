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

		std::string _inputPFOCollection;
		LCCollection* _in_pfoCol;

		std::string _inputJetPFOCollection;
		LCCollection* _in_jetpoCol;

		std::string _inputIsolepsCollection;
		LCCollection* _in_islCol;



		bool _output_switch_collection;
		std::string _outputPFOWoOverlayCollection;
		Overlay_Removal_Output_Collection _outputPFOWoOverlayCol;
		std::string _outputPFOOverlayCollection;
		Overlay_Removal_Output_Collection _outputPFOOverlayCol;


		// output 
		bool _output_switch_root;
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
		void  Counter(bool JPFO, LCEvent* evt);


		/** Calculates the cone energy */
		bool analyseJet( LCCollection* PFOCol, LCCollection* IsolepCol, LCCollection* Jet_POs_col, Overlay_Removal_Output_Collection& PFOWoOverlayCol, Overlay_Removal_Output_Collection& PFOOverlayCol,  Overlay_Removal_Information_Single &info_wo_overlay,  Overlay_Removal_Information_Single &info_overlay);




	public:
		Overlay_Removal_Global_Counter      _global_counter;
		Overlay_Removal_Single_Counter      _single_counter;
		Overlay_Removal_Counter             _counter;
		Overlay_Removal_Information         _info;

} ;

#endif

