/**
 * @brief Marlin processor for finding isolated photons.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of ReconstructedParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef PandoraIsolatedPhotonFinder_h
#define PandoraIsolatedPhotonFinder_h 1

#include "PandoraIsolatedPhotonFinder_Element_Observable.h"

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

#include "TMVA/Reader.h" 

using namespace lcio ;
using namespace marlin ;

class PandoraIsolatedPhotonFinder : public Processor {

	public:

		virtual Processor*  newProcessor() { return new PandoraIsolatedPhotonFinder ; }

		PandoraIsolatedPhotonFinder() ;

		virtual void init() ;
		virtual void processRunHeader( LCRunHeader* run ) ;
		virtual void processEvent( LCEvent * evt ) ; 
		virtual void check( LCEvent * evt ) ; 
		virtual void end() ;

	protected:

		/** Input collection */
		std::string _inputMCsCollection;
		LCCollection*    _MCsCol;

		std::string _inputPFOsCollection;
		LCCollection*    _PFOCol;

		std::string _mcpfoRelation;
		std::string _pfomcRelation;
		LCRelationNavigator* _navmcpfo;
		LCRelationNavigator* _navpfomc;


		/** Output collection of isolated photons */
		std::string _outputIsoPhotonCollection;
		PandoraIsolatedPhotonFinder_Output_Collection _outputWoIsoPhotonCol;

		/** Output collection (all input with isolated photons removed) */
		std::string _outputWoIsoPhotonCollection;
		PandoraIsolatedPhotonFinder_Output_Collection _outputIsoPhotonCol;

		std::string _mva_weights;
		float       _mvaCut;

		bool _output_switch_root;
		bool _output_switch_collection;

		// output
		std::string _rootfilename;
		TFile*      _outfile;
		TTree*      _datatrain_sig;
		TTree*      _datatrain_bkg;
		void makeNTuple();

		/** If set to true, uses Energy cuts in the central region*/
		bool  _useEnergy;
		float _minEnergyCut;
		float _maxEnergyCut;

		bool  _usePolarAngle;
		float _minCosTheta;
		float _maxCosTheta;

		bool  _useForwardEnergy;
		float _minForwardEnergyCut;
		float _maxForwardEnergyCut;

		// if this is open, _maxCosTheta = _minForwardCosTheta automatically
		bool  _useForwardPolarAngle;
		float _minForwardCosTheta;
		float _maxForwardCosTheta;

		/** If set to true, uses rectangular cuts for isolation */
		bool _useIsolationCone;
		float _minCosConeAngle;
		float _maxCosConeAngle;
		float _ConeEnergyRatio;

		//internal para
		int   _nEvt;
		int   _nRun; 
		int   _pnum; 
 
 		// internal function 
 		void  Init  (LCEvent* evt); 
 		void  Finish(LCEvent* evt);
 		void  Counter(bool JPFO, LCEvent* evt);
 
 
		bool  analysePFOParticle( LCCollection* input_mc, LCCollection* input_pfo, PandoraIsolatedPhotonFinder_Output_Collection& outputPhoton, PandoraIsolatedPhotonFinder_Output_Collection& outputWoPhotonCol, PandoraIsolatedPhotonFinder_Information& info_isr, PandoraIsolatedPhotonFinder_Information& info_normal, PandoraIsolatedPhotonFinder_Function_Counter& counter);

		/** Returns true if pfo is an isolated photon */
		int IsIsolatedPhoton( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all, PandoraIsolatedPhotonFinder_Information_Single& info) ;

		/** Returns true if it passes photon ID cuts */
		void Get_IsoPhoton_Observable( ReconstructedParticle* pfo, std::vector<ReconstructedParticle*> all, float cone_cut, PandoraIsolatedPhotonFinder_Observable& obv) ;

		/** Returns true if it passes photon ID cuts */
		bool IsForwardPhoton( ReconstructedParticle* pfo ) ;

		/** Returns true if it passes photon ID cuts */
		bool IsCentralPhoton( ReconstructedParticle* pfo ) ;

		PandoraIsolatedPhotonFinder_Global_Counter       _global_counter;
		PandoraIsolatedPhotonFinder_Single_Counter       _single_counter;
		PandoraIsolatedPhotonFinder_Counter              _counter;
		PandoraIsolatedPhotonFinder_Information          _info_isr;
		PandoraIsolatedPhotonFinder_Information          _info_normal;


		//MVA input
		TMVA::Reader*     _reader;

		float _small_input_energy       ;
		float _small_num_incone_total   ;
		float _small_num_incone_charge  ;
	    float _small_num_incone_neutral ;
		float _small_num_incone_photon  ;
		float _small_num_incone_lepton  ;
	    float _small_num_incone_hadron  ; 
		float _small_cone_energy_total  ;
		float _small_cone_energy_charge ;
		float _small_cone_energy_neutral;
		float _small_cone_energy_photon ;
		float _small_cone_energy_lepton ;
		float _small_cone_energy_hadron ;
		float _small_cone_energy_ratio_total  ;
		float _small_cone_energy_ratio_charge ;
		float _small_cone_energy_ratio_neutral;
		float _small_cone_energy_ratio_photon ;
		float _small_cone_energy_ratio_lepton ;
		float _small_cone_energy_ratio_hadron ;
		float _small_cone_costheta            ;
		float _large_num_incone_total   ;
		float _large_num_incone_charge  ;
		float _large_num_incone_neutral ;
		float _large_num_incone_photon  ;
		float _large_num_incone_lepton  ;
		float _large_num_incone_hadron  ;
		float _large_cone_energy_total  ;
		float _large_cone_energy_charge ;
		float _large_cone_energy_neutral;
		float _large_cone_energy_photon ;
		float _large_cone_energy_lepton ;
		float _large_cone_energy_hadron ;
		float _large_cone_energy_ratio_total  ;
		float _large_cone_energy_ratio_charge ;
		float _large_cone_energy_ratio_neutral;
		float _large_cone_energy_ratio_photon ;
		float _large_cone_energy_ratio_lepton ;
		float _large_cone_energy_ratio_hadron ;
		float _large_cone_costheta            ;
} ;

#endif

