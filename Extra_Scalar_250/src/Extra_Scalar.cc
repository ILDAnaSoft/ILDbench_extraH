#include "Extra_Scalar.h"

Extra_Scalar aExtra_Scalar;

Extra_Scalar::Extra_Scalar() : Processor( "Extra_Scalar" ) {

	//modify processor description
	_description = "Extra_Scalar does whatever it does ...";

	//register steering parameters: name, description, class-variable, default value
	//Input basic collection of MC
	registerInputCollection( LCIO::MCPARTICLE,
			"MCParticleCollection", 
			"Name of the MC particle collection",
			_inputMCsCollection,
			std::string("MCParticle") );

	//Input collection from FastJet
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputAllPFOCollection", 
			"Name of the PFOs collection",
			_inputPFOCollection,
			std::string("PandoraPFOs") );









	//Input collection from MCPhotonFinder 
	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCHS_Collection",
			"Name of the MC collection",
			_inputMCHS_Collection,
			std::string("MCHS") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCHS_IsoLeptonCollection",
			"Name of the MC isolated lepton collection",
			_inputMCHS_MuonCollection,
			std::string("MCHS_Lepton") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCHS_IsoPhotonCollection",
			"Name of the MC isolated photon collection",
			_inputMCHS_PhotonCollection,
			std::string("MCHS_Photon") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCHS_WoIsoPhotonCollection", 
			"Name of the PFO after MC isolated Photon tagging collection",
			_inputMCHS_WoMuonPhotonCollection,
			std::string("MCHS_WoPhoton") );



	//Input collection from MCPhotonFinder 
	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCPS_Collection",
			"Name of the MC collection",
			_inputMCPS_Collection,
			std::string("MCPS") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCPS_IsoLeptonCollection",
			"Name of the MC isolated lepton collection",
			_inputMCPS_MuonCollection,
			std::string("MCPS_Lepton") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCPS_IsoPhotonCollection",
			"Name of the MC isolated photon collection",
			_inputMCPS_PhotonCollection,
			std::string("MCPS_Photon") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCPS_WoIsoPhotonCollection", 
			"Name of the PFO after MC isolated Photon tagging collection",
			_inputMCPS_WoMuonPhotonCollection,
			std::string("MCPS_WoPhoton") );




	//Input collection from MCPhotonFinder 
	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCDS_Collection",
			"Name of the MC collection",
			_inputMCDS_Collection,
			std::string("MCDS") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCDS_IsoLeptonCollection",
			"Name of the MC isolated photon collection",
			_inputMCDS_MuonCollection,
			std::string("MCDS_Lepton") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCDS_IsoPhotonCollection",
			"Name of the MC isolated photon collection",
			_inputMCDS_PhotonCollection,
			std::string("MCDS_Photon") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCDS_WoIsoPhotonCollection", 
			"Name of the PFO after MC isolated Photon tagging collection",
			_inputMCDS_WoMuonPhotonCollection,
			std::string("MCDS_WoPhoton") );




	//Input collection from Strange Lepton 
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOIsoLeptonConversionCollection", 
			"Name of the PFO Lepton after changing MC isolated Lepton",
			_inputPFOLepton_ConversionCollection,
			std::string("PFOIsoLeptonConversion") );




	//Input collection from Strange Photon 
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOIsoPhotonConversionCollection", 
			"Name of the PFO Photon after changing MC isolated Photon",
			_inputPFOPhoton_ConversionCollection,
			std::string("PFOIsoPhotonConversion") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOWoIsoPhotonConversionCollection", 
			"Name of the PFOs after remove related to MC isolated Photon",
			_inputPFOWoPhoton_ConversionCollection,
			std::string("PFORemovedIsoPhotonConversion") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOIsoPhotonOnlyCollection", 
			"Name of the PFOs after remove related to MC isolated Photon",
			_inputPFOPhoton_OnlyCollection,
			std::string("PFOIsoPhotonOnly") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOWoIsoPhotonOnlyCollection", 
			"Name of the PFOs after remove related to MC isolated Photon",
			_inputPFOWoPhoton_onlyCollection,
			std::string("PFORemovedIsoPhotonOnly") );





	//Input collection from IsolatedLeptonTaggingProcessor
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputIsolepsCollection",
			"Name of the isolated lepton collection",
			_inputPFOMuonCollection,
			std::string("Isoleps") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOWoIsolepsCollection", 
			"Name of the PFO after isolated lepton tagging collection",
			_inputPFOWoMuonCollection,
			std::string("PFOWoIsoleps") );



	//Input collection from PandoraIsolatedPhotonFinder 
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPandoraIsoPhotonCollection",
			"Name of the Pandora isolated photon collection",
			_inputPFOPhotonCollection,
			std::string("PandoraIsoPhoton") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPandoraPFOWoIsoPhotonCollection", 
			"Name of the PFO after Pandora isolated Photon tagging collection",
			_inputPFOWoPhotonCollection,
			std::string("PandoraPFOWoIsoPhoton") );






	//Input collection from Link 
	registerInputCollection( LCIO::LCRELATION,
			"InputRecoMCTruthLink",
			"Relation between MC and PFO particles",
			_pfomcsRelation,
			std::string("RecoMCTruthLink"));

	registerInputCollection( LCIO::LCRELATION,
			"InputMCTruthRecoLink",
			"Relation between PFO particles and MC",
			_mcspfoRelation,
			std::string("MCTruthRecoLink"));



	//Input parameters 
	registerProcessorParameter( "hmass",
			"For counting energetic charged particles in the collection after isolated lepton tagging",
			_hmass,
			float(125) );

	registerProcessorParameter( "cmenergy",
			"center of mass energy",
			_cmenergy,
			float(250.006126) );

	registerProcessorParameter( "RootFileName",
			"Name of Root file (default: output.root)",
			_rootfilename, 
			std::string("../result/output.root") );

}


void Extra_Scalar::init() { 

	//streamlog_out(DEBUG) << "   init called  " << std::endl;
	std::cout << "init called" << std::endl;
	std::cout << "the output root file is " << _rootfilename << std::endl; 

	// usually a good idea to
	printParameters();

	// make Ntuple
	makeNTuple();

	_nRun = 0;
	_nEvt = 0;

	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

}

void Extra_Scalar::processRunHeader( LCRunHeader* run ) { 
	_nRun++;
} 




void Extra_Scalar::processEvent( LCEvent * evt ) 
{ 
	Init(evt);


    int  JMC_HS=analyseMCParticle( _MCHS_MuonCol, _MCHS_PhotonCol,_MCHS_WoMuonPhotonCol,_info.hs);

    int  JMC_PS=analyseMCParticle( _MCPS_MuonCol, _MCPS_PhotonCol,_MCPS_WoMuonPhotonCol,_info.py);

    int  JMC_DS=analyseMCParticle( _MCDS_MuonCol, _MCDS_PhotonCol,_MCDS_WoMuonPhotonCol,_info.de);


	int JPFO                      =analysePhysicalObject(_PFOMuonCol        ,_PFOPhotonCol            ,_PFOWoPhotonCol, _info.po      ,1);

////if((JMC_HS!=1||JMC_PS!=1||JMC_DS!=1)&&JPFO==1){
////	std::vector<MCParticle*> muon_hs    =ToolSet::CMC::Get_MCParticle(_MCHS_MuonCol);
////	std::vector<MCParticle*> muon_ps    =ToolSet::CMC::Get_MCParticle(_MCPS_MuonCol);
////	std::vector<MCParticle*> muon_ds    =ToolSet::CMC::Get_MCParticle(_MCDS_MuonCol);
////	std::vector<ReconstructedParticle*> muon_pfo   =ToolSet::CRC::Get_POParticle(_PFOMuonCol);
////	ToolSet::ShowMessage(1,"mc_hs",muon_hs);
////	ToolSet::ShowMessage(1,"mc_ps",muon_ps);
////	ToolSet::ShowMessage(1,"mc_ds",muon_ds);
////	ToolSet::ShowMessage(1,"pfo",muon_pfo);
////}
    int JPFO_MC_Cheating_Muon     =analysePhysicalObject(_PFOLepton_ConversionCol, _PFOPhotonCol           , _PFOWoPhotonCol, _info.po_cmuon,2);

    int JPFO_MC_Cheating_ISR      =analysePhysicalObject(_PFOMuonCol             , _PFOPhoton_ConversionCol, _PFOWoPhoton_ConversionCol, _info.po_cisr ,1);
 
    int JPFO_MC_Cheating_ISR_Only =analysePhysicalObject(_PFOMuonCol        , _PFOPhoton_OnlyCol, _PFOWoPhoton_OnlyCol, _info.po_cisr_only ,1);

////if(std::abs(_info.po_cisr.obv.kcut_zmass-_info.po.obv.kcut_zmass)>0.001){
////	std::vector<ReconstructedParticle*> leps    =ToolSet::CRC::Get_POParticle(_PFOMuonCol);
////	std::vector<ReconstructedParticle*> muon    =ToolSet::CRC::Get_POParticleType_Abs(leps,13);
////	ToolSet::ShowMessage(1,"not same muon",_info.po_cisr.obv.kcut_zmass,_info.po.obv.kcut_zmass);
////	ToolSet::ShowMessage(1,"not same muon",muon);
////}

  	Counter(JMC_HS, JMC_PS, JMC_DS, JPFO, JPFO_MC_Cheating_Muon, JPFO_MC_Cheating_ISR, JPFO_MC_Cheating_ISR_Only, evt);

	Finish(evt);
}




void Extra_Scalar::Counter(int JMC_HS,int JMC_PS, int JMC_DS,  int JPFO, int JPFO_MC_Cheating_Muon, int JPFO_MC_Cheating_ISR, int JPFO_MC_Cheating_ISR_Only, LCEvent* evt){
    if(JMC_HS==1&&JMC_PS==1&&JMC_DS==1){
    	_global_counter.pass_MCs++;
    	_single_counter.pass_MCs++;
    }
    else{
//		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ", _nEvt);
    }
	
    if(JPFO==1){
    	_global_counter.pass_PFO++;
    	_single_counter.pass_PFO++;
    }
    else{
//		ToolSet::ShowMessage(1,"in processEvent: not pass analysePFOParticle ",_nEvt);
    }

    if(JPFO_MC_Cheating_Muon==1){
    	_global_counter.pass_PFO_MC_Cheating_Muon++;
    	_single_counter.pass_PFO_MC_Cheating_Muon++;
    }
    else{
//		ToolSet::ShowMessage(1,"in processEvent: not pass analysePO_MC_Cheating_Muon",_nEvt);
    }

    if(JPFO_MC_Cheating_ISR==1){
    	_global_counter.pass_PFO_MC_Cheating_ISR++;
    	_single_counter.pass_PFO_MC_Cheating_ISR++;
    }
    else{
//		ToolSet::ShowMessage(1,"in processEvent: not pass analysePO_MC_Cheating_ISR",_nEvt);
    }

    if(JPFO_MC_Cheating_ISR_Only==1){
    	_global_counter.pass_PFO_MC_Cheating_ISR_Only++;
    	_single_counter.pass_PFO_MC_Cheating_ISR_Only++;
    }
    else{
//		ToolSet::ShowMessage(1,"in processEvent: not pass analysePO_MC_Cheating_ISR",_nEvt);
    }

	if(JMC_HS==1&&JMC_PS==1&&JMC_DS==1&&JPFO==1&&JPFO_MC_Cheating_Muon==1&&JPFO_MC_Cheating_ISR==1&&JPFO_MC_Cheating_ISR_Only==1){
		_global_counter.pass_all++;

    	_single_counter.pass_all++;
	}
}



void Extra_Scalar::Init(LCEvent* evt){
	_nEvt++;

	_global_counter.nevt=_nEvt;
	_global_counter.nrun=_nRun;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

	_info.Init();
	_counter.Init();
	_single_counter.Init();

	_photon_chain .Init();
	_muon_chain   .Init();

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.run   =evt->getRunNumber();
	_single_counter.weight=evt->getWeight();

	// fill histogram from LCIO data :
	_PFOCol    = evt->getCollection( _inputPFOCollection) ;
	_MCsCol    = evt->getCollection( _inputMCsCollection ) ;
	_navpfomcs = new LCRelationNavigator( evt->getCollection( _pfomcsRelation ) );
	_navmcspfo = new LCRelationNavigator( evt->getCollection( _mcspfoRelation ) );

	ToolSet::CMC::Set_Nav_From_MC_To_RC(_navmcspfo);
	ToolSet::CMC::Set_Collider_Energy(_cmenergy);

	//mc hs
	try{
		_MCHS_Col= evt->getCollection( _inputMCHS_Collection);
	}
	catch(...){
		std::cout << "no mc hs in this event" << std::endl;
	}
	try{
		_MCHS_MuonCol= evt->getCollection( _inputMCHS_MuonCollection);
	}
	catch(...){
		std::cout << "no mc hs isolated leptons in this event" << std::endl;
	}

	try{
		_MCHS_PhotonCol= evt->getCollection( _inputMCHS_PhotonCollection);
	}
	catch(...){
		std::cout << "no mc hs photons in this event" << std::endl;
	}

	try{
		_MCHS_WoMuonPhotonCol= evt->getCollection( _inputMCHS_WoMuonPhotonCollection);
	}
	catch(...){
		std::cout << "no mc hs particles in this event" << std::endl;
	}


	//mc ps
	try{
		_MCPS_Col= evt->getCollection( _inputMCPS_Collection);
	}
	catch(...){
		std::cout << "no mc ps in this event" << std::endl;
	}

	try{
		_MCPS_MuonCol= evt->getCollection( _inputMCPS_MuonCollection);
	}
	catch(...){
		std::cout << "no mc ps isolated leptons in this event" << std::endl;
	}

	try{
		_MCPS_PhotonCol= evt->getCollection( _inputMCPS_PhotonCollection);
	}
	catch(...){
		std::cout << "no mc ps photons in this event" << std::endl;
	}

	try{
		_MCPS_WoMuonPhotonCol= evt->getCollection( _inputMCPS_WoMuonPhotonCollection);
	}
	catch(...){
		std::cout << "no mc ps particles in this event" << std::endl;
	}


	//mc ds
	try{
		_MCDS_Col= evt->getCollection( _inputMCDS_Collection);
	}
	catch(...){
		std::cout << "no mc ds in this event" << std::endl;
	}

	try{
		_MCDS_MuonCol= evt->getCollection( _inputMCDS_MuonCollection);
	}
	catch(...){
		std::cout << "no mc ds isolated leptons in this event" << std::endl;
	}

	try{
		_MCDS_PhotonCol= evt->getCollection( _inputMCDS_PhotonCollection);
	}
	catch(...){
		std::cout << "no mc ds photons in this event" << std::endl;
	}

	try{
		_MCDS_WoMuonPhotonCol= evt->getCollection( _inputMCDS_WoMuonPhotonCollection);
	}
	catch(...){
		std::cout << "no mc ds particles in this event" << std::endl;
	}



	//strange lepton
	try{
		_PFOLepton_ConversionCol= evt->getCollection( _inputPFOLepton_ConversionCollection);
	}
	catch(...){
		std::cout << "no PFO Lepton conversion in this event" << std::endl;
	}


	//strange photon
	try{
		_PFOPhoton_ConversionCol= evt->getCollection( _inputPFOPhoton_ConversionCollection);
	}
	catch(...){
		std::cout << "no PFO Photon conversion in this event" << std::endl;
	}

	try{
		_PFOWoPhoton_ConversionCol= evt->getCollection( _inputPFOWoPhoton_ConversionCollection);
	}
	catch(...){
		std::cout << "no PFO wo Photon conversion in this event" << std::endl;
	}

	try{
		_PFOPhoton_OnlyCol= evt->getCollection( _inputPFOPhoton_OnlyCollection);
	}
	catch(...){
		std::cout << "no PFO Photon only instead in this event" << std::endl;
	}

	try{
		_PFOWoPhoton_OnlyCol= evt->getCollection( _inputPFOWoPhoton_onlyCollection);
	}
	catch(...){
		std::cout << "no PFO Photon only instead in this event" << std::endl;
	}


	//isolated lepton
	try{
		_PFOMuonCol = evt->getCollection( _inputPFOMuonCollection );
	}
	catch(...){
		std::cout << "no pandora isolated leptons in this event" << std::endl;
	}

	try{
		_PFOWoMuonCol = evt->getCollection( _inputPFOWoMuonCollection );
	}
	catch(...){
		std::cout << "no pandora pfos after isolated lepton tagging in this event" << std::endl;
	}


	//isolated photon 
	try{
		_PFOPhotonCol= evt->getCollection( _inputPFOPhotonCollection);
	}
	catch(...){
		std::cout << "no Pandora isolated photon in this event" << std::endl;
	}

	try{
		_PFOWoPhotonCol = evt->getCollection( _inputPFOWoPhotonCollection );
	}
	catch(...){
		std::cout << "no pfos after Pandora isolated photon tagging in this event" << std::endl;
	}

    _chain.Set_Nav(_navmcspfo,_navpfomcs);
}

void Extra_Scalar::Finish(LCEvent* evt) { 

	_datatrain->Fill();

	// delete
    delete _navmcspfo;
    delete _navpfomcs;

	streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
                  	     << "   in run:  " << evt->getRunNumber() 
		                 << std::endl ;
}

void Extra_Scalar::check( LCEvent * evt ) { 
	// nothing to check here - could be used to fill checkplots in reconstruction processor
}


void Extra_Scalar::end(){ 

	std::cout << "Extra_Scalar::end()  " << name() 
	 	      << " processed " << _nEvt << " events in " << _nRun << " runs "
	 	      << std::endl ;

	_otfile->cd();
	_datatrain->Write();
	_otfile->Close();

}



void Extra_Scalar::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_otfile = new TFile( _rootfilename.c_str() , "RECREATE" );

	//Define root tree
	_datatrain= new TTree( "datatrain" , "events" );
	//event number

	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_counter       .Fill_Data(_datatrain);
	_info          .Fill_Data(_datatrain);
	return;
}

