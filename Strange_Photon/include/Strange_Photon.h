/**
 * @brief Marlin processor for finding jet.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef Strange_Photon_h
#define Strange_Photon_h 1

#include "Strange_Photon_Element_Observable.h"


// Only ILCSoft related header file
#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>



using namespace lcio ;
using namespace marlin ;

class Strange_Photon : public Processor {

	public:

		virtual Processor*  newProcessor() { return new Strange_Photon ; }

		Strange_Photon() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		// input string 
		std::string _inputMCsCollection;
		std::string _inputPFOsCollection;

		std::string _mcpfoRelation;
		std::string _pfomcRelation;
		std::string _mctrkRelation;
		std::string _trkmcRelation;

		std::string _rootfilename;

		bool _output_switch_root;
		bool _output_switch_collection;

		std::string _outputPFOCollection;


		// input collection 
		LCCollection* _pfoCol;
		LCCollection* _mcCol;
		LCRelationNavigator* _navpfomc;
		LCRelationNavigator* _navmcpfo;
		LCRelationNavigator* _navtrkmc;
		LCRelationNavigator* _navmctrk;

		// output 
		TFile* _outfile;
		TTree* _datatrain;
		LCCollectionVec* _outPFOCol;

		//internal function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void Counter(int JMC, int JPFO, LCEvent* evt);

		/** Calculates the cone energy */
		int analyseMCParticle( LCCollection* MCs_col, LCRelationNavigator* navMCToPFO, Strange_Photon_Information &info, Strange_Photon_Information &info2, Strange_Photon_Counter& counter);
		int analysePFOParticle( LCCollection* PFOs_col, LCRelationNavigator* navPFOToMC, Strange_Photon_Information &info, Strange_Photon_Counter& counter);

    	/** Calculates the cone energy */
    	float getConeEnergy( MCParticle* mc ) ;


		void makeNTuple();
		//internal para 
		int  _nEvt; 
		int _nRun;

		Strange_Photon_Counter              _mc_counter;
		Strange_Photon_Counter              _pfo_counter;
		Strange_Photon_Global_Counter       _global_counter;
		Strange_Photon_Single_Counter       _single_counter;

		Strange_Photon_Information          _mc_info;
		Strange_Photon_Information          _mc2_info;
		Strange_Photon_Information          _pfo_info;

} ;

#endif

