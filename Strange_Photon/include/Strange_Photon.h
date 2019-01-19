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
		std::string _inputMCsPhotonCollection;
		std::string _inputMCsWoPhotonCollection;
		std::string _inputPFOPhotonCollection;
		std::string _inputPFOWoPhotonCollection;

		std::string _mcpfoRelation;
		std::string _pfomcRelation;
		std::string _mctrkRelation;
		std::string _trkmcRelation;



		// input collection 
		LCCollection* _mcsPhotonCol;
		LCCollection* _mcsWoPhotonCol;
		LCCollection* _pfoPhotonCol;
		LCCollection* _pfoWoPhotonCol;

		LCRelationNavigator* _navpfomc;
		LCRelationNavigator* _navmcpfo;
		LCRelationNavigator* _navtrkmc;
		LCRelationNavigator* _navmctrk;

		// input para
		float _minEnergyDifferenceRatio;

		// output collection 
		bool _output_switch_collection;
		std::string _outputMCsLostEnergyPhotonCollection;
		std::string _outputPFOLostEnergyPhotonCollection;
		std::string _outputPFOLostEnergyPhoton_CombinedCollection;
		std::string _outputPFOPhoton_ConversionCollection;
		std::string _outputPFOWoPhoton_ConversionCollection;
		std::string _outputPFOPhoton_OnlyCollection;
		std::string _outputPFOWoPhoton_OnlyCollection;
		std::string _outputPFOLostEnergyPhoton_RCOnlyCollection;

		Strange_Photon_Output_Collection _outputMCsLostEnergyPhotonCol;
		Strange_Photon_Output_Collection _outputPFOLostEnergyPhotonCol;
		Strange_Photon_Output_Collection _outputPFOLostEnergyPhoton_CombinedCol;
		Strange_Photon_Output_Collection _outputPFOPhoton_ConversionCol;
		Strange_Photon_Output_Collection _outputPFOWoPhoton_ConversionCol;
		Strange_Photon_Output_Collection _outputPFOPhoton_OnlyCol;
		Strange_Photon_Output_Collection _outputPFOWoPhoton_OnlyCol;
		Strange_Photon_Output_Collection _outputPFOLostEnergyPhoton_RCOnlyCol;

		// output root 
		bool _output_switch_root;
		std::string _rootfilename;
		TFile* _outfile;
		TTree* _datatrain;
		void makeNTuple();

		//internal function
		void  Init  (LCEvent* evt); 
		void  Finish(LCEvent* evt);
		void Counter(int JMC1, int JMC2, LCEvent* evt);

		/** Calculates the cone energy */
		int analyseMCParticle_Conversion( LCCollection* Input_MCsPhotonCol, LCCollection* Input_MCsWoPhotonCol, 
				LCCollection* Input_PFOPhotonCol, LCCollection* Input_PFOWoPhotonCol, 
				Strange_Photon_Output_Collection& PFOLostEnergyPhotonCol,    Strange_Photon_Output_Collection& PFOLostEnergyPhoton_CombinedCol, 
				Strange_Photon_Output_Collection& MCsLostEnergyPhotonCol,    
				Strange_Photon_Output_Collection& PFOPhoton_ConversionCol, Strange_Photon_Output_Collection& PFOWoPhoton_ConversionCol, 
				LCRelationNavigator* navMCToPFO, LCRelationNavigator* navPFOToMC,   
				Strange_Photon_Information&info, Strange_Photon_Function_Counter& counter) ;


		int analyseMCParticle_OnlyPhoton( LCCollection* Input_MCsPhotonCol, LCCollection* Input_MCsWoPhotonCol, 
				LCCollection* Input_PFOPhotonCol, LCCollection* Input_PFOWoPhotonCol, 
				Strange_Photon_Output_Collection& PFOLostEnergyPhoton_RCOnlyCol, 
				Strange_Photon_Output_Collection& PFOPhoton_OnlyCol, Strange_Photon_Output_Collection& PFOWoPhoton_OnlyCol, 
				LCRelationNavigator* navMCToPFO, LCRelationNavigator* navPFOToMC,   
				Strange_Photon_Information&info, Strange_Photon_Function_Counter& counter) ;


		//internal para 
		int  _nEvt; 
		int _nRun;

		Strange_Photon_Global_Counter       _global_counter;
		Strange_Photon_Single_Counter       _single_counter;
		Strange_Photon_Information          _info;
		Strange_Photon_Counter              _counter;

} ;

#endif

