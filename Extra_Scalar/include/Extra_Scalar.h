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
		void Counter(int JMC_HS,int JMC_PS, int JMC_DS,  int JPFO, int JPFO_MC_Cheating_Muon, int JPFO_MC_Cheating_ISR, int JPFO_MC_Cheating_ISR_Only, LCEvent* evt);
		void Init(LCEvent* evt);
		void Finish(LCEvent* evt); 


		template<typename TOBVRECOIL>
			bool obvRecoil(std::vector<TOBVRECOIL> in, std::vector<TOBVRECOIL> &out) ;

		int  analyseMCParticle( LCCollection* MuonCol, LCCollection* PhotonCol, LCCollection* WoPhotonCol,  Extra_Scalar_Information_Single &info) ;
		int  Get_MC_Observables( std::vector<MCParticle*> muon,  std::vector<MCParticle*> photon, std::vector<MCParticle*> wophoton,  Extra_Scalar_Information_Single &info_single) ;

		bool MCCutMuon( std::vector<MCParticle*> &MCs, Extra_Scalar_Number &num, Extra_Scalar_Variable& vari_plus, Extra_Scalar_Variable& vari_minus) ;
        void MCCutPhoton(std::vector<MCParticle*> &MCsPhoton,  Extra_Scalar_Number& num, Extra_Scalar_Variable &vari_central, Extra_Scalar_Variable &vari_forward);
		bool MCCutDetail(std::vector<MCParticle*> &choosed_lep, std::vector<MCParticle*> &photon, std::vector<MCParticle*> &MCsWoMuonPhoton, Extra_Scalar_Observable &obv);





		//		bool analysePhysicalObject( LCCollection* PFOWithoutIsoleps, LCCollection* Isoleps,Information &info) ;
//		bool analysePhysicalObject(LCCollection* PFO_col, LCCollection* PFOWithoutIsoleps, LCCollection* Isoleps,Information &info);
		int  analysePhysicalObject(LCCollection* Leps,LCCollection* ISR,LCCollection* PFOWoPhoton, Extra_Scalar_Information_Single &info, int label) ;
		bool POCutMuon  (std::vector<ReconstructedParticle*> &muon  , Extra_Scalar_Number& num, Extra_Scalar_Variable& vari_plus, Extra_Scalar_Variable& vari_minus) ;
		void POCutMuonPair( std::vector<ReconstructedParticle*> &muon, Extra_Scalar_Observable& obv) ;
        void POCutPhoton(std::vector<ReconstructedParticle*> &Photon, Extra_Scalar_Number&num,  Extra_Scalar_Variable& vari_central,  Extra_Scalar_Variable& vari_forward);
		bool POCutDetail(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon,  std::vector<ReconstructedParticle*> &PFOWoMuonPhoton, Extra_Scalar_Observable &obv);


		bool MCCut_Muon(std::vector<MCParticle*> &choosed_lep,  Extra_Scalar_Observable &obv);
		bool POCut_Muon(std::vector<ReconstructedParticle*> &choosed_lep,  Extra_Scalar_Observable &obv);
		bool POCut_Recoil    (std::vector<ReconstructedParticle*> in, std::vector<ReconstructedParticle*> &out) ;

		bool POCut_Global(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv);
		bool POCut_Global(std::vector<MCParticle*> &choosed_lep, std::vector<ReconstructedParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv);
		bool POCut_Global(std::vector<ReconstructedParticle*> &choosed_lep, std::vector<MCParticle*> &photon, std::vector<ReconstructedParticle*> &PFOWoMuonPhoton,  Extra_Scalar_Observable &obv);




		//Input collection name.
		std::string _inputPFOCollection;
		LCCollection* _PFOCol;
		std::string _inputMCsCollection;
		LCCollection* _MCsCol;

		std::string _inputPFOWoOverlayCollection;
		LCCollection* _PFOWoOverlayCol;

		std::string _inputMCHS_Collection;
		LCCollection* _MCHS_Col;
		std::string _inputMCHS_MuonCollection;
		LCCollection* _MCHS_MuonCol;
		std::string _inputMCHS_PhotonCollection;
		LCCollection* _MCHS_PhotonCol;
		std::string _inputMCHS_WoMuonPhotonCollection;
		LCCollection* _MCHS_WoMuonPhotonCol;

		std::string _inputMCPS_Collection;
		LCCollection* _MCPS_Col;
		std::string _inputMCPS_MuonCollection;
		LCCollection* _MCPS_MuonCol;
		std::string _inputMCPS_PhotonCollection;
		LCCollection* _MCPS_PhotonCol;
		std::string _inputMCPS_WoMuonPhotonCollection;
		LCCollection* _MCPS_WoMuonPhotonCol;

		std::string _inputMCDS_Collection;
		LCCollection* _MCDS_Col;
		std::string _inputMCDS_MuonCollection;
		LCCollection* _MCDS_MuonCol;
		std::string _inputMCDS_PhotonCollection;
		LCCollection* _MCDS_PhotonCol;
		std::string _inputMCDS_WoMuonPhotonCollection;
		LCCollection* _MCDS_WoMuonPhotonCol;

		std::string _inputPFOLepton_ConversionCollection;
		LCCollection* _PFOLepton_ConversionCol;

		std::string _inputPFOPhoton_ConversionCollection;
		LCCollection* _PFOPhoton_ConversionCol;
		std::string _inputPFOWoPhoton_ConversionCollection;
		LCCollection* _PFOWoPhoton_ConversionCol;
		std::string _inputPFOPhoton_OnlyCollection;
		LCCollection* _PFOPhoton_OnlyCol;
		std::string _inputPFOWoPhoton_onlyCollection;
		LCCollection* _PFOWoPhoton_OnlyCol;


		std::string _inputPFOMuonCollection;
		LCCollection* _PFOMuonCol;
		std::string _inputPFOWoMuonCollection;
		LCCollection* _PFOWoMuonCol;
		std::string _inputPFOPhotonCollection;
		LCCollection* _PFOPhotonCol;
		std::string _inputPFOWoPhotonCollection;
		LCCollection* _PFOWoPhotonCol;


		std::string _pfomcsRelation;
		LCRelationNavigator* _navpfomcs;
		std::string _mcspfoRelation;
		LCRelationNavigator* _navmcspfo;



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



