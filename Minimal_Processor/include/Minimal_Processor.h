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
#include <lcio.h>

#include <EVENT/ReconstructedParticle.h>
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <UTIL/LCRelationNavigator.h>
#include <IMPL/LCCollectionVec.h>
#include <marlin/VerbosityLevels.h>


#include "TTree.h"
#include "TFile.h"
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>


//header in the ToolSet
#include "CPrint.h"
#include "CFormat.h"
#include "CVector.h"

class TFile;
class TTree;

using namespace lcio ;
using namespace marlin ;
using namespace std;
using ToolSet::operator<<;
using ToolSet::operator+;
using ToolSet::operator-;

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

		//function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);

		/** Calculates the cone energy */
		bool analyseMCParticle( LCCollection* MCs_col, LCRelationNavigator* navMCToPFO, Minimal_Processor_Information &info, Minimal_Processor_Counter& counter);
		bool analysePFOParticle( LCCollection* PFOs_col, LCRelationNavigator* navPFOToMC, Minimal_Processor_Information &info, Minimal_Processor_Counter& counter);


		void makeNTuple();


		//para for recording information
		int  _nEvt; 
		int _nRun;

		Minimal_Processor_Counter              _mc_counter;
		Minimal_Processor_Counter              _pfo_counter;
		Minimal_Processor_Global_Counter       _global_counter;

		Minimal_Processor_Information          _mc_info;
		Minimal_Processor_Information          _pfo_info;

} ;

#endif

