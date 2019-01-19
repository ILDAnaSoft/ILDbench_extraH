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
				std::string("../results/output.root") );

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

	// usually a good idea to
	printParameters();

	_nEvt = 0;
	_nRun = 0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputPFOCol       .Set_Switch(_output_switch_collection);
	_outputPFOCol       .Set_Name(_outputPFOCollection);

	// make Ntuple
	if(_output_switch_root){
		makeNTuple();
	}

}

void Minimal_Processor::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Minimal_Processor::processEvent( LCEvent * evt ) { 

	Init(evt);

    bool JMC =analyseMCParticle(_mcCol, _navmcpfo, _info.MCs, _counter.MCs);

    bool JPFO=analysePFOParticle(_pfoCol, _outputPFOCol, _navpfomc, _info.PFO, _counter.PFO);

	Counter(JMC, JPFO, evt);

	Finish(evt);
}




void Minimal_Processor::Counter(bool JMC, bool JPFO, LCEvent* evt){
	if(JMC){
		_global_counter.pass_MCs++;
		_single_counter.pass_MCs++;
	}
    else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ", evt->getEventNumber());
    }


    if(JPFO){
    	_global_counter.pass_PFO++;
    	_single_counter.pass_PFO++;
    }
    else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analysePFOParticle ",evt->getEventNumber());
    }

	if(JMC&&JPFO){
		_global_counter.pass_all++;
    	_single_counter.pass_all++;
	}
    else{
		ToolSet::ShowMessage(1,"in processEvent: not pass all",evt->getEventNumber());
    }
}






void Minimal_Processor::Init(LCEvent* evt) { 
	//init
	_nEvt ++;
	_global_counter.nevt=_nEvt;
	_global_counter.nrun=_nRun;
	_global_counter.gweight=1;
	if( _nEvt % 50 == 0 ){
		if(_output_switch_collection&&!_output_switch_root){
		}
		else{
			ToolSet::ShowMessage(1,"processing event",_nEvt);
		}
	} 

	_info.Init();
	_counter.Init();
	_single_counter.Init();

	_single_counter.evt=evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run=evt->getRunNumber();


	// PFO loop
    _mcCol = evt->getCollection( _inputMCsCollection  ) ;
	_pfoCol = evt->getCollection( _inputPFOsCollection ) ;
    _navmcpfo = new LCRelationNavigator( evt->getCollection( _mcpfoRelation ) );
    _navpfomc = new LCRelationNavigator( evt->getCollection( _pfomcRelation ) );

	_outputPFOCol.Set_Collection_RCParticle();
}

void Minimal_Processor::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFOCol       .Add_Collection(evt);

	// delete
    delete _navmcpfo;
    delete _navpfomc;

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
}




void Minimal_Processor::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_info          .Fill_Data(_datatrain);
	_counter       .Fill_Data(_datatrain);
	return;

}











