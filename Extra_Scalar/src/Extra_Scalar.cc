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
			std::string("MCParticlesSkimmed") );

	//Input collection from FastJet
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputAllPFOCollection", 
			"Name of the PFOs collection",
			_inputPFOCollection,
			std::string("PandoraPFOs") );




	//Input collection from IsolatedLeptonTaggingProcessor
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







	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOwoOverlayCollection", 
			"The input after removing the overlay",
			_inputPFOWoOverlayCollection,
			std::string("PFOwoOverlay") );


	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCwoOverlayCollection", 
			"The input after removing the overlay",
			_inputMCsWoOverlayCollection,
			std::string("MCwoOverlay") );





	//Input collection from IsolatedLeptonTaggingProcessor
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputIsolepsCollection",
			"Name of the isolated lepton collection",
			_inputPFOMuonCollection,
			std::string("Isoleps") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPFOWithoutIsolepsCollection", 
			"Name of the PFO after isolated lepton tagging collection",
			_inputPFOWoMuonCollection,
			std::string("PFOWithoutIsoleps") );

	//Input collection from PandoraIsolatedPhotonFinder 
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPandoraIsoPhotonCollection",
			"Name of the Pandora isolated photon collection",
			_inputPFOPhotonCollection,
			std::string("PandoraIsoPhoton") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputPandoraPFOWithoutIsoPhotonCollection", 
			"Name of the PFO after Pandora isolated Photon tagging collection",
			_inputPFOWoMuonPhotonCollection,
			std::string("PandoraPFOWithoutIsoPhoton") );





	//Input collection from MCPhotonFinderX 
	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCsMuonCollection",
			"Name of the MC isolated photon collection",
			_inputMCsMuonCollection,
			std::string("MCsMuon_Pythia") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCsWoMuonCollection",
			"Name of the MC isolated photon collection",
			_inputMCsWoMuonCollection,
			std::string("MCsPhoton_Pythia") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCIsoPhotonCollection",
			"Name of the MC isolated photon collection",
			_inputMCsPhotonCollection,
			std::string("MCsPhoton_Pythia") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCsWithoutIsoPhotonCollection", 
			"Name of the PFO after MC isolated Photon tagging collection",
			_inputMCsWoMuonPhotonCollection,
			std::string("MCsWithoutIsoPhoton_Pythia") );






	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCIsoPhotonConversionCollection",
			"Name of the MC isolated photon collection",
			_inputMCsPhotonConversionCollection,
			std::string("MCsPhoton_Conversion") );

	registerInputCollection( LCIO::MCPARTICLE,
			"InputMCsWithoutIsoPhotonConversionCollection", 
			"Name of the PFO after MC isolated Photon tagging collection",
			_inputMCsWoPhotonConversionCollection,
			std::string("MCsWithoutIsoPhoton_Conversion") );

	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputMCPFOWithoutIsoPhotonCollection", 
			"Name of the PFOs after MC isolated Photon tagging collection",
			_inputMCsPFOWoPhotonCollection,
			std::string("PFOWithoutIsoPhoton") );

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

	bool JOverlay, JMC,JPFO, JPFO_MC_Cheating_Muon, JPFO_MC_Cheating_ISR;

	JMC=analyseMCParticle(_MCsCol,_info);

	JPFO=analysePhysicalObject(_PFOMuonCol,_PFOPhotonCol,_PFOWoMuonPhotonCol, _info.po);

	JPFO_MC_Cheating_Muon=analysePO_MC_Cheating_Muon(_MCsMuonCol, _PFOPhotonCol, _PFOWoMuonPhotonCol, _navmcspfo, _info.po_cmuon);

	JPFO_MC_Cheating_ISR =analysePO_MC_Cheating_ISR (_PFOMuonCol, _MCsPhotonCol, _PFOWoMuonCol,       _navpfomcs, _info.po_cisr );

	Counter(JMC, JPFO, JPFO_MC_Cheating_Muon, JPFO_MC_Cheating_ISR, evt);

	Finish(evt);
}




void Extra_Scalar::Counter(bool JMC, bool JPFO, bool JPFO_MC_Cheating_Muon, bool JPFO_MC_Cheating_ISR, LCEvent* evt){
    if(JMC){
    	_global_counter.pass_MCs++;
    	_single_counter.pass_MCs++;
    }
    else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
    }
	
    if(JPFO){
    	_global_counter.pass_PFO++;
    	_single_counter.pass_PFO++;
    }
    else{
		ToolSet::ShowMessage(1,1,"in processEvent: not pass analysePFOParticle ");
    }

    if(JPFO_MC_Cheating_Muon){
    	_global_counter.pass_PFO_MC_Cheating_Muon++;
    	_single_counter.pass_PFO_MC_Cheating_Muon++;
    }
    else{
		ToolSet::ShowMessage(1,1,"in processEvent: not pass analysePFOParticle ");
    }

    if(JPFO_MC_Cheating_ISR){
    	_global_counter.pass_PFO_MC_Cheating_ISR++;
    	_single_counter.pass_PFO_MC_Cheating_ISR++;
    }
    else{
		ToolSet::ShowMessage(1,1,"in processEvent: not pass analysePFOParticle ");
    }

	if(JMC&&JPFO&&JPFO_MC_Cheating_Muon&&JPFO_MC_Cheating_ISR){
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

	try{
		_PFOWoOverlayCol = evt->getCollection( _inputPFOWoOverlayCollection);
	}
	catch(...){
		std::cout << "no PFOs without overlay in this event" << std::endl;
	}

	try{
		_MCsWoOverlayCol = evt->getCollection( _inputMCsWoOverlayCollection );
	}
	catch(...){
		std::cout << "no MCs without overlay in this event" << std::endl;
	}


	try{
		_PFOMuonCol = evt->getCollection( _inputPFOMuonCollection );
	}
	catch(...){
		std::cout << "no isolated leptons in this event" << std::endl;
	}

	try{
		_PFOWoMuonCol = evt->getCollection( _inputPFOWoMuonCollection );
	}
	catch(...){
		std::cout << "no pfos after isolated lepton tagging in this event" << std::endl;
	}


	try{
		_PFOPhotonCol= evt->getCollection( _inputPFOPhotonCollection);
	}
	catch(...){
		std::cout << "no Pandora isolated photon in this event" << std::endl;
	}

	try{
		_PFOWoMuonPhotonCol = evt->getCollection( _inputPFOWoMuonPhotonCollection );
	}
	catch(...){
		std::cout << "no pfos after Pandora isolated photon tagging in this event" << std::endl;
	}


	try{
		_MCsMuonCol = evt->getCollection( _inputMCsMuonCollection );
	}
	catch(...){
		std::cout << "no isolated leptons in this event" << std::endl;
	}

	try{
		_MCsWoMuonCol = evt->getCollection( _inputMCsWoMuonCollection );
	}
	catch(...){
		std::cout << "no pfos after isolated lepton tagging in this event" << std::endl;
	}

	try{
		_MCsPhotonCol= evt->getCollection( _inputMCsPhotonCollection);
	}
	catch(...){
		std::cout << "no MC photon pythia in this event" << std::endl;
	}


	try{
		_MCsWoMuonPhotonCol= evt->getCollection( _inputMCsWoMuonPhotonCollection );
	}
	catch(...){
		std::cout << "no MCs without photon pythia in this event" << std::endl;
	}


	try{
		_MCsPhotonConversionCol = evt->getCollection( _inputMCsPhotonConversionCollection );
	}
	catch(...){
		std::cout << "no MC conversion photon in this event" << std::endl;
	}


	try{
		_MCsWoPhotonConversionCol = evt->getCollection( _inputMCsWoPhotonConversionCollection );
	}
	catch(...){
		std::cout << "no MCs without photon conversion in this event" << std::endl;
	}


	try{
		_MCsPFOWoPhotonCol = evt->getCollection( _inputMCsPFOWoPhotonCollection );
	}
	catch(...){
		std::cout << "no PFOs without Photon conversion in this event" << std::endl;
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

