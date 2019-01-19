/**
 * @brief Marlin processor for finding jet.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef Test_OutputCollection_h
#define Test_OutputCollection_h 1

#include "Test_OutputCollection_Element_Observable.h"
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




class Test_OutputCollection : public Processor {

	public:

		virtual Processor*  newProcessor() { return new Test_OutputCollection ; }

		Test_OutputCollection() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		// input string 
		std::string _inputPFOCollection1;
		std::string _inputMCsCollection1;
		std::string _inputPFOCollection2;
		std::string _inputMCsCollection2;


		// input collection 
		LCCollection* _pfoCol1;
		LCCollection* _mcCol1;
		LCCollection* _pfoCol2;
		LCCollection* _mcCol2;

		// input para
		// none

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
		bool analyseMCParticle ( LCCollection* MCs_col1,LCCollection* MCs_col2,  Test_OutputCollection_Information_Single &info1,Test_OutputCollection_Information_Single &info2,  Test_OutputCollection_Function_Counter& counter1,  Test_OutputCollection_Function_Counter& counter2);
    	bool analysePFOParticle( LCCollection* PFO_col1,LCCollection* PFO_col2,  Test_OutputCollection_Information_Single &info1,Test_OutputCollection_Information_Single &info2,  Test_OutputCollection_Function_Counter& counter1,  Test_OutputCollection_Function_Counter& counter2);


    	//internal para 
    	int  _nEvt; 
    	int _nRun;

    	Test_OutputCollection_Counter              _counter;
    	Test_OutputCollection_Global_Counter       _global_counter;
    	Test_OutputCollection_Single_Counter       _single_counter;
    	Test_OutputCollection_Information          _info;

} ;

#endif

