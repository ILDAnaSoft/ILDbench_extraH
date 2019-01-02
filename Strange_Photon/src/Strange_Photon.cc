#include "Strange_Photon.h"

Strange_Photon aStrange_Photon ;

Strange_Photon::Strange_Photon()
	: Processor("Strange_Photon") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCParticleCollection", 
				"Name of the MC particle collection",
				_inputMCsCollection,
				std::string("MCParticle") );

		registerInputCollection( LCIO::MCPARTICLE,
				"InputCentralIsoMCPhotonCollection", 
				"Name of the MC central photon collection",
				_input,
				std::string("MCParticle") );

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPOParticleCollection" ,
				"Input collection of ReconstructedParticles",
				_inputPFOsCollection,
				std::string("PandoraPFOs"));

	    registerInputCollection( LCIO::LCRELATION,
	    		"InputMCRecoTruthLink",
	    		"Relation between MC and PFO particles",
	    		_mcpfoRelation,
	    		std::string("MCTruthRecoLink"));

	    registerInputCollection( LCIO::LCRELATION,
	    		"InputRecoMCTruthLink",
	    		"Relation between MC and PFO particles",
	    		_pfomcRelation,
	    		std::string("RecoMCTruthLink"));

		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );

		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOCollection",
				"The output for PFO Type Collection",
				_outputPFOCollection,
				std::string("outputPFO") );

	}


void Strange_Photon::init() { 
	std::cout << "   init Strange_Photon " << std::endl ;
	std::cout << "the output root file is " << _rootfilename << std::endl; 

	// usually a good idea to
	printParameters();

	// make Ntuple
	if(_output_switch_root){
		makeNTuple();
	}

	_nRun = 0;
	_nEvt = 0;
	_global_counter.Init();
}

void Strange_Photon::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Strange_Photon::processEvent( LCEvent * evt ) { 

	Init(evt);

    int JMC =analyseMCParticle(_mcCol, _navmcpfo, _mc_info,_mc2_info, _mc_counter);


    int JPFO=analysePFOParticle(_pfoCol, _navpfomc, _pfo_info, _pfo_counter);

	Counter(JMC, JPFO, evt);

	Finish(evt);
}

void Strange_Photon::Counter(int JMC, int JPFO,LCEvent* evt){
    if(JMC==1){
    	_global_counter.pass_mc++;
    	_single_counter.pass_mc++;
    }
	else if(JMC==0){
    	_global_counter.pass_mc++;
    	_single_counter.pass_mc++;
    }
    else{
	//	ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
    }
	
    if(JPFO){
    	_global_counter.pass_pfo++;
    	_single_counter.pass_pfo++;
    }
    else{
		ToolSet::ShowMessage(1,1,"in processEvent: not pass analysePFOParticle ");
    }

	if(JMC&&JPFO){
		_global_counter.pass_all++;
    	_single_counter.pass_all++;
	}
}


void Strange_Photon::Init(LCEvent* evt) { 
	//init
	_nEvt ++;
	_global_counter.nevt=_nEvt;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

    _mc_info.Init();
    _mc2_info.Init();
    _pfo_info.Init();
    _mc_counter.Init();
    _pfo_counter.Init();
	_single_counter.Init();


	_single_counter.nevt=evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.nrun=evt->getRunNumber();


	if(_output_switch_collection){
		_outPFOCol= new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE ) ;
		_outPFOCol->setSubset(true) ;
		// Output pfos after removed isolated photon from mc 
		_otpfosRemovedIsoPhotonCol = new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE) ;
		_otpfosRemovedIsoPhotonCol->setSubset(true) ;
		
		// Output mcs of isolated photon 
		_otIsoPhotonCol = new LCCollectionVec( LCIO::MCPARTICLE );
		_otIsoPhotonCol->setSubset(true);
		
		// Output mcs of isolated photon 
		_otIsoPhotonConversionCol = new LCCollectionVec( LCIO::MCPARTICLE );
		_otIsoPhotonConversionCol->setSubset(true);
		
		// Output mcs removed isolated photon 
		_otmcsRemovedIsoPhotonConversionCol = new LCCollectionVec( LCIO::MCPARTICLE ) ;
		_otmcsRemovedIsoPhotonConversionCol->setSubset(true) ;
	}


	// PFO loop
    _mcCol = evt->getCollection( _inputMCsCollection  ) ;
	_pfoCol = evt->getCollection( _inputPFOsCollection ) ;
    _navmcpfo = new LCRelationNavigator( evt->getCollection( _mcpfoRelation ) );
    _navpfomc = new LCRelationNavigator( evt->getCollection( _pfomcRelation ) );

}

void Strange_Photon::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	if(_output_switch_collection){
		  evt->addCollection(_otpfosRemovedIsoPhotonCol, _outputPFOsRemovedIsoPhotonCollection.c_str() );
		  evt->addCollection(_otIsoPhotonConversionCol , _outputIsoPhotonConversionCollection.c_str()        );
		  evt->addCollection(_otmcsRemovedIsoPhotonConversionCol, _outputMCsRemovedIsoPhotonConversionCollection.c_str() );
	}
	// delete
    delete _navmcpfo;
    delete _navpfomc;

	streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		<< "   in run:  " << evt->getRunNumber() 
		<< std::endl ;
}


void Strange_Photon::check( LCEvent * evt ) { 
}

void Strange_Photon::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
	std::cout << "Strange_Photon::end()  " << std::endl;
}




void Strange_Photon::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	//Define root tree
	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_mc_info .Fill_Data(_datatrain,"mc");
	_mc2_info .Fill_Data(_datatrain,"mc2");
	_pfo_info.Fill_Data(_datatrain,"po");
	return;

}











