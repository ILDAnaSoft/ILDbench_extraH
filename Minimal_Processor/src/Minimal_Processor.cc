#include "Minimal_Processor.h"

Minimal_Processor aMinimal_Processor ;

Minimal_Processor::Minimal_Processor()
	: Processor("Minimal_Processor") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCParticleCollection", 
				"Name of the MC particle collection",
				_inputMCsCollection,
				std::string("MCParticlesSkimmed") );

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


void Minimal_Processor::init() { 
	std::cout << "   init Minimal_Processor " << std::endl ;
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

void Minimal_Processor::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Minimal_Processor::processEvent( LCEvent * evt ) { 

	Init(evt);

    bool JMC,JPFO;

    JMC =analyseMCParticle(_mcCol, _navmcpfo, _mc_info, _mc_counter);
    if(JMC){
    	_global_counter.pass_mc++;
    }
    else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
    }



    JPFO=analysePFOParticle(_pfoCol, _navpfomc, _pfo_info, _pfo_counter);
    if(JPFO){
    	_global_counter.pass_pfo++;
    }
    else{
		ToolSet::ShowMessage(1,1,"in processEvent: not pass analysePFOParticle ");
    }

	if(JMC&&JPFO){
		_global_counter.pass_all++;
	}
	if(_output_switch_collection){
	// choose a RECONSTRUCTEDPARTICLE vector to write into the collection 
////	for(unsigned int i=0;i<JetPFOwoOverlay.size();i++){
////		_otPFOCol->addElement( JetPFOwoOverlay[i]);
////	}
	}

	Finish(evt);
}

void Minimal_Processor::Init(LCEvent* evt) { 
	//init
	_nEvt ++;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;
    _mc_info.Init();
    _pfo_info.Init();
    _mc_counter.Init();
    _pfo_counter.Init();


	if(_output_switch_collection){
		_outPFOCol= new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE ) ;
		_outPFOCol->setSubset(true) ;
	}


	// PFO loop
    _mcCol = evt->getCollection( _inputMCsCollection  ) ;
	_pfoCol = evt->getCollection( _inputPFOsCollection ) ;
    _navmcpfo = new LCRelationNavigator( evt->getCollection( _mcpfoRelation ) );
    _navpfomc = new LCRelationNavigator( evt->getCollection( _pfomcRelation ) );

}

void Minimal_Processor::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	// delete
    delete _navmcpfo;
    delete _navpfomc;

	streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		<< "   in run:  " << evt->getRunNumber() 
		<< std::endl ;
}


void Minimal_Processor::check( LCEvent * evt ) { 
}

void Minimal_Processor::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
	std::cout << "Minimal_Processor::end()  " << std::endl;
}




void Minimal_Processor::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	//Define root tree
	_mc_info .Fill_Data(_datatrain,"mc");
	_pfo_info.Fill_Data(_datatrain,"po");
	return;

}











