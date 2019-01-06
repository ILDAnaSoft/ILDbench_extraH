/**
 * @brief Marlin processor for finding isolated photons.
 * @author Yan Wang <yan.wang@desy.de>
 * @version $Id:$
 *
 * Given a list of MCParticle, identify isolated photons
 * based on the ecal energy, photon identification,
 */
#ifndef Extra_Scalar_h
#define Extra_Scalar_h  

#include "Extra_Scalar_Element_Observable.h"

#include <marlin/Processor.h>
#include <marlin/VerbosityLevels.h>
#include <lcio.h>

#include <EVENT/LCCollection.h>
#include <EVENT/LCParameters.h>
#include <UTIL/LCRelationNavigator.h>

using namespace lcio;
using namespace marlin;
using namespace IMPL;

class Extra_Scalar : public Processor{

	public:

		virtual Processor* newProcessor() { return new Extra_Scalar; }

		Extra_Scalar();

		//Called at the begin of the job before anything is read.
		//Use to initialize the processor, e.g. book histograms.
		virtual void init();

		//Called for every run.
		virtual void processRunHeader( LCRunHeader* run );

		//Called for every event - the working horse.
		virtual void processEvent( LCEvent* evt ); 

		virtual void check( LCEvent* evt ); 

		//Called after data processing for clean up.
		virtual void end();

	protected:

		//Prepare NTuple to check the data
		void makeNTuple();
		void Counter(bool JMC, bool JPFO, bool JPFO_MC_Cheating_Muon, bool JPFO_MC_Cheating_ISR, LCEvent* evt);
		void Init(LCEvent* evt);
		void Finish(LCEvent* evt); 


		template<typename TOBVRECOIL>
			bool obvRecoil(std::vector<TOBVRECOIL> in, std::vector<TOBVRECOIL> &out) ;

		bool analyseMCParticle( LCCollection* Allmc, Extra_Scalar_Information &info) ;
		void Get_All_Level_FS(LCCollection* allMC, std::vector<MCParticle*> &hard_scattering, std::vector<MCParticle*> &pythia_explicit, std::vector<MCParticle*> &pythia_stable, std::vector<MCParticle*> &detector);
		bool Get_MC_Observables( std::vector<MCParticle*> FS,   Extra_Scalar_Information_Single &info_single) ;

		bool MCCutMuon( std::vector<MCParticle*> MCs, Extra_Scalar_Number &num, Extra_Scalar_Variable_Vec& vari) ;
        void MCCutPhoton(std::vector<MCParticle*> &MCsPhoton,  Extra_Scalar_Number& num, Extra_Scalar_Variable_Vec &vari);
		bool MCCutDetail(std::vector<MCParticle*> &choosed_lep, std::vector<MCParticle*> &photon, std::vector<MCParticle*> &MCsWoMuonPhoton, Extra_Scalar_Observable &obv);





		//		bool analysePhysicalObject( LCCollection* PFOWithoutIsoleps, LCCollection* Isoleps,Information &info) ;
//		bool analysePhysicalObject(LCCollection* PFO_col, LCCollection* PFOWithoutIsoleps, LCCollection* Isoleps,Information &info);
		bool analysePhysicalObject(LCCollection* Leps,LCCollection* ISR,LCCollection* PFOWoMuonPhoton, Extra_Scalar_Information_Single &info) ;
		bool POCutMuon  (std::vector<ReconstructedParticle*> &muon  , Extra_Scalar_Number& num, Extra_Scalar_Variable_Vec& vari) ;
        void POCutPhoton(std::vector<ReconstructedParticle*> &Photon, Extra_Scalar_Number&num,  Extra_Scalar_Variable_Vec& vari);
		bool POCutDetail(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon,  std::vector<ReconstructedParticle*> &PFOWoMuonPhoton, Extra_Scalar_Observable &obv);


		bool MCCut_Muon(std::vector<MCParticle*> &choosed_lep,  Extra_Scalar_Observable &obv);
		bool POCut_Muon(std::vector<ReconstructedParticle*> &choosed_lep,  Extra_Scalar_Observable &obv);

		bool POCut_Global(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv);
		bool POCut_Global(std::vector<MCParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv);
		bool POCut_Global(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<MCParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv);



		bool analysePO_MC_Cheating_Muon(LCCollection* Muon,LCCollection* Photon,LCCollection* PFOWoMuonPhoton,LCRelationNavigator* navmc, Extra_Scalar_Information_Single &info) ;
		bool analysePO_MC_Cheating_ISR (LCCollection* Muon,LCCollection* Photon,LCCollection* PFOWoMuonPhoton,LCRelationNavigator* navmc, Extra_Scalar_Information_Single &info) ;



		//Input collection name.
		std::string _inputPFOCollection;
		LCCollection* _PFOCol;
		std::string _inputMCsCollection;
		LCCollection* _MCsCol;

		std::string _pfomcsRelation;
		LCRelationNavigator* _navpfomcs;
		std::string _mcspfoRelation;
		LCRelationNavigator* _navmcspfo;

		std::string _inputPFOWoOverlayCollection;
		LCCollection* _PFOWoOverlayCol;
		std::string _inputMCsWoOverlayCollection;
		LCCollection* _MCsWoOverlayCol;

		std::string _inputPFOMuonCollection;
		LCCollection* _PFOMuonCol;
		std::string _inputPFOWoMuonCollection;
		LCCollection* _PFOWoMuonCol;
		std::string _inputPFOPhotonCollection;
		LCCollection* _PFOPhotonCol;
		std::string _inputPFOWoMuonPhotonCollection;
		LCCollection* _PFOWoMuonPhotonCol;

		std::string _inputMCsMuonCollection;
		LCCollection* _MCsMuonCol;
		std::string _inputMCsWoMuonCollection;
		LCCollection* _MCsWoMuonCol;
		std::string _inputMCsPhotonCollection;
		LCCollection* _MCsPhotonCol;
		std::string _inputMCsWoMuonPhotonCollection;
		LCCollection* _MCsWoMuonPhotonCol;

		std::string _inputMCsPhotonConversionCollection;
		LCCollection* _MCsPhotonConversionCol;
		std::string _inputMCsWoPhotonConversionCollection;
		LCCollection* _MCsWoPhotonConversionCol;
		std::string _inputMCsPFOWoPhotonCollection;
		LCCollection* _MCsPFOWoPhotonCol;




		// input para
		float _hmass;
		float _cmenergy;


		//output
		std::string _rootfilename;
		TFile*      _otfile;
		TTree*      _datatrain;


		// private global para
		int _nRun;
		int _nEvt;

		Extra_Scalar_Global_Counter       _global_counter;
		Extra_Scalar_Single_Counter       _single_counter;

		Extra_Scalar_Counter              _counter;

		Extra_Scalar_Information          _info;

		ToolSet::CChain_Vec               _photon_chain ;
		ToolSet::CChain_Vec               _muon_chain ;
		ToolSet::CChain_Vec               _chain ;

};

#endif



