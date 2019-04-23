/**
 * @brief Marlin processor for finding jet.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef Strange_Lepton_h
#define Strange_Lepton_h 1

#include "Strange_Lepton_Element_Observable.h"


// Only ILCSoft related header file
#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <EVENT/Vertex.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio ;
using namespace marlin ;




class Strange_Lepton : public Processor {

	public:

		virtual Processor*  newProcessor() { return new Strange_Lepton ; }

		Strange_Lepton() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		// input string 
		std::string _inputMCsLeptonCollection;
		std::string _inputPFOLeptonCollection;

		// input collection 
		LCCollection* _mcsLeptonCol;
		LCCollection* _pfoLeptonCol;

		// input relation 
		std::string _mcpfoRelation;
		std::string _pfomcRelation;
		LCRelationNavigator* _navpfomc;
		LCRelationNavigator* _navmcpfo;

		// input para

		// output collection 
		bool _output_switch_collection;
		std::string _outputPFOLeptonCollection;

		Strange_Lepton_Output_Collection _outputPFOLeptonCol;

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
				LCCollection* Input_PFOLeptonCol,
			Strange_Lepton_Output_Collection& NewPFOIsoLeptonCol, 
			LCRelationNavigator* navMCToPFO,  LCRelationNavigator* navPFOToMC, 
			Strange_Lepton_Information&info, Strange_Lepton_Function_Counter& counter) ;

		bool Get_Best_Pair(std::vector<ReconstructedParticle*> in, std::vector<ReconstructedParticle*> &out) ;
		//internal para 
		int  _nEvt; 
		int _nRun;

		Strange_Lepton_Global_Counter       _global_counter;
		Strange_Lepton_Single_Counter       _single_counter;
		Strange_Lepton_Information          _info;
		Strange_Lepton_Counter              _counter;

} ;

#endif

