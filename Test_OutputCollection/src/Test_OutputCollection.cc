#include "Test_OutputCollection.h"

Test_OutputCollection aTest_OutputCollection ;

Test_OutputCollection::Test_OutputCollection()
	: Processor("Test_OutputCollection") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCParticleCollection1", 
				"Name of the MC particle collection",
				_inputMCsCollection1,
				std::string("MCParticle") );

		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCParticleCollection2", 
				"Name of the MC particle collection",
				_inputMCsCollection2,
				std::string("MCParticle") );

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPOParticleCollection1" ,
				"Input collection of ReconstructedParticles",
				_inputPFOCollection1,
				std::string("PandoraPFOs"));

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPOParticleCollection2" ,
				"Input collection of ReconstructedParticles",
				_inputPFOCollection2,
				std::string("PandoraPFOs"));

		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../results/output.root") );

	}


void Test_OutputCollection::init() { 
	std::cout << "   init Test_OutputCollection " << std::endl ;

	// usually a good idea to
	printParameters();

	_nEvt = 0;
	_nRun = 0;
    _global_counter.Init();
    _single_counter.Init();
    _counter.Init();

	// make Ntuple
	if(_output_switch_root){
		makeNTuple();
	}

}

void Test_OutputCollection::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Test_OutputCollection::processEvent( LCEvent * evt ) { 

	Init(evt);

    bool JMC =analyseMCParticle(_mcCol1, _mcCol2, _info.MCs1, _info.MCs2, _counter.MCs1,_counter.MCs2);

    bool JPFO=analysePFOParticle(_pfoCol1, _pfoCol2, _info.PFO1, _info.PFO2,  _counter.PFO1,_counter.PFO2);

    Counter(JMC, JPFO, evt);

	Finish(evt);
}



void Test_OutputCollection::Counter(bool JMC, bool JPFO, LCEvent* evt){
	if(JMC){
		_global_counter.pass_MCs++;
		_single_counter.pass_MCs++;
	}
    else{
		ToolSet::ShowMessage(2,"in processEvent: not pass analyseMCParticle ", evt->getEventNumber());
    }


    if(JPFO){
    	_global_counter.pass_PFO++;
    	_single_counter.pass_PFO++;
    }
    else{
		ToolSet::ShowMessage(2,"in processEvent: not pass analysePFOParticle ",evt->getEventNumber());
    }

	if(JMC&&JPFO){
		_global_counter.pass_all++;
    	_single_counter.pass_all++;
	}
    else{
		ToolSet::ShowMessage(2,"in processEvent: not pass all",evt->getEventNumber());
    }
}





void Test_OutputCollection::Init(LCEvent* evt) { 
	//init
	_nEvt ++;
    _global_counter.nevt=_nEvt;
    _global_counter.nrun=_nRun;
    _global_counter.gweight=1;
	if( _nEvt % 50 == 0 ){
		ToolSet::ShowMessage(1,"processing event",_nEvt);
	} 

    _info.Init();
    _counter.Init();
    _single_counter.Init();

    _single_counter.evt=evt->getEventNumber();
    _single_counter.weight=evt->getWeight();
    _single_counter.run=evt->getRunNumber();


	_mcCol1=0;
	try{
		_mcCol1 = evt->getCollection( _inputMCsCollection1  ) ;
	}
	catch(...){
		ToolSet::ShowMessage(2,"no MCs collection 1 in this event");
	}
	_mcCol2=0;
	try{
		_mcCol2 = evt->getCollection( _inputMCsCollection2  ) ;
	}
	catch(...){
		ToolSet::ShowMessage(2,"no MCs collection 2 in this event");
	}
	_pfoCol1=0;
	try{
		_pfoCol1 = evt->getCollection( _inputPFOCollection1 ) ;
	}
	catch(...){
		ToolSet::ShowMessage(2,"no PFO collection 1 in this event");
	}
	_pfoCol2=0;
	try{
		_pfoCol2 = evt->getCollection( _inputPFOCollection2 ) ;
	}
	catch(...){
		ToolSet::ShowMessage(2,"no PFO collection 2 in this event");
	}

}

void Test_OutputCollection::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

}


void Test_OutputCollection::check( LCEvent * evt ) { 
}

void Test_OutputCollection::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
}




void Test_OutputCollection::makeNTuple() {

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











