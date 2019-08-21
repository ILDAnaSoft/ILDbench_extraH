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
		std::string _inputPFOLeptonCollection;
		std::string _inputPFOWoLeptonCollection;
		std::string _inputMCsLeptonCollection;


		// input collection 
		LCCollection* _PFOLeptonCol;
		LCCollection* _PFOWoLeptonCol;
		LCCollection* _MCsLeptonCol;

		// input para
		float _center_energy;
		float _hmass;
		long long int lepnum;


		// output collection 
		bool _output_switch_collection;
		std::string _outputPFOLeptonCollection;
		std::string _outputPFOWoLeptonCollection;

		PFOLeptonTagging_Output_Collection _outputPFOLeptonCol;
		PFOLeptonTagging_Output_Collection _outputPFOWoLeptonCol;

		// output root 
		bool _output_switch_root;
		std::string _rootfilename;
		TFile* _outfile;
		TTree* _datatrain;
		void makeNTuple();

		//internal function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void Counter(int JPFO, LCEvent* evt);

		/** Calculates the cone energy */

		int analysePOParticle( LCCollection* Input_PFOLeptonCol, LCCollection* Input_PFOWoLeptonCol, 
				LCCollection* Input_MCsCol,
				PFOLeptonTagging_Output_Collection& NewPFOIsoLeptonCol, 
				PFOLeptonTagging_Output_Collection& NewPFOWoIsoLeptonCol, 
				PFOLeptonTagging_Information&info, PFOLeptonTagging_Function_Counter& counter) ;


		bool POCut_Detail    (std::vector<ReconstructedParticle*> &input_leps,  std::vector<ReconstructedParticle*> &input_others, std::vector<ReconstructedParticle*> &out_leps, std::vector<ReconstructedParticle*> &out_others, PFOLeptonTagging_Information &info);
		bool POCut_Muon      ( std::vector<ReconstructedParticle*> &muon, PFOLeptonTagging_Information_Single& info) ;
		bool POCut_MuonPair  ( std::vector<ReconstructedParticle*> &muon, PFOLeptonTagging_Observable& obv) ;
		bool POCut_Recoil    (std::vector<ReconstructedParticle*> in, std::vector<ReconstructedParticle*> &out) ;
		bool POCut_Observable(std::vector<ReconstructedParticle*> &choosed_leps,  PFOLeptonTagging_Observable &obv);
		bool MCCut_Detail    (std::vector<MCParticle*> &input_leps, PFOLeptonTagging_Information &info);

		//internal para 
		int  _nEvt; 
		int _nRun;

		PFOLeptonTagging_Global_Counter       _global_counter;
		PFOLeptonTagging_Single_Counter       _single_counter;
		PFOLeptonTagging_Information          _info;
		PFOLeptonTagging_Counter              _counter;

} ;

#endif

