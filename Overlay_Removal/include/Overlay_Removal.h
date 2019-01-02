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

//class TFile;
//class TTree;


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

		bool _output_switch_collection;


		std::string _outputPFOwoOverlayCollection;
		LCCollectionVec* _ot_PFOwoOverlay;

		std::string _outputMCwoOverlayCollection;
		LCCollectionVec* _ot_MCwoOverlay;


		bool _output_switch_root;
		std::string _rootfilename;


		int  _nEvt; 
		int _nRun;


		// output 
		TFile* _otfile;
		TTree* _datatrain;


		//function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);


		/** Calculates the cone energy */
		std::vector<MCParticle*>            analyseMCParticle( LCCollection* MCs_col, Overlay_Removal_Information &info);
		std::vector<ReconstructedParticle*> analyseJet       ( LCCollection* Isolep, LCCollection* Jet_POs_col, Overlay_Removal_Information &info);


		void makeNTuple();


	public:
		Overlay_Removal_Information          _mc_info;
		Overlay_Removal_Information          _jet_info;
		Overlay_Removal_Global_Counter       _global_counter;

} ;

#endif

