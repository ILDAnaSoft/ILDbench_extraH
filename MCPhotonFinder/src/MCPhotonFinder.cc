#include "MCPhotonFinder.h"

MCPhotonFinder aMCPhotonFinder ;

MCPhotonFinder::MCPhotonFinder()
	: Processor("MCPhotonFinder") {

		// Processor description
		_description = "Isolated Photon Finder Processor: output is Photon at the MC Pythia level" ;

		// register steering parameters: name, description, class-variable, default value
    	registerInputCollection( LCIO::MCPARTICLE,
    			"InputMCCollection" ,
    			"Input collection of MCParticles",
    			_inputMCsCollection,
    			std::string("MCParticle"));

		//Output Collection 
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

    	registerOutputCollection( LCIO::MCPARTICLE,
    			"OutputCollectionIsolatedPhoton",
    			"Output collection of isolated photon in non-forward region",
    			_outputIsoPhotonCollection,
    			std::string("MCsIsoPhoton") );

    	registerOutputCollection( LCIO::MCPARTICLE,
    			"OutputCollectionWoIsolatedPhoton",
    			"Copy of input collection but without the isolated photon",
    			_outputWoIsoPhotonCollection,
    			std::string("MCsWoIsoPhoton") );

		//Output root 
		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );

		//Input parameters 
    	registerProcessorParameter( "UseEnergy",
    			"Use energy cut",
    			_useEnergy,
    			bool(true));

    	registerProcessorParameter( "MinimalEnergyCut",
    			"The minimal energy for a isolated photon",
    			_minEnergyCut,
    			float(0));

    	registerProcessorParameter( "MaximalEnergyCut",
    			"The maximal energy for a isolated photon",
    			_maxEnergyCut,
    			float(-1));

    	registerProcessorParameter( "UsePolarAngle",
    			"Use cosine polar angle cut",
    			_usePolarAngle,
    			bool(true));

    	registerProcessorParameter( "MinimalPolarAngle",
    			"The minimal cosine polar angle for a isolated photon",
    			_minCosTheta,
    			float(0.0));

    	registerProcessorParameter( "MaximalPolarAngle",
    			"The maximal cosine polar angle for a isolated photon",
    			_maxCosTheta,
    			float(0.95));

    	registerProcessorParameter( "UseForwardEnergy",
    			"Use energy cut in the forward region",
    			_useForwardEnergy,
    			bool(true));

    	registerProcessorParameter( "MinimalForwardEnergyCut",
    			"The minimal energy for a isolated photon in the forward region",
    			_minForwardEnergyCut,
    			float(0));

    	registerProcessorParameter( "MaximalForwardEnergyCut",
    			"The maximal energy for a isolated photon in the forward region",
    			_maxForwardEnergyCut,
    			float(-1));

    	registerProcessorParameter( "UseForwardAngle",
    			"Use forward angle cut",
    			_useForwardPolarAngle,
    			bool(true));

    	registerProcessorParameter( "MinimalForwardPolarAngle",
    			"The minimal cosine angle to define a forward region",
    			_minForwardCosTheta,
    			float(0.95));

    	registerProcessorParameter( "MaximalForwardPolarAngle",
    			"The maximal cosine angle to define a forward region",
    			_maxForwardCosTheta,
    			float(0.98));

    	registerProcessorParameter( "UseIsolationCone",
    			"Define a cone using the photon as the axis, the other particle can not lie in the cone",
    			_useIsolationCone,
    			bool(false));

    	registerProcessorParameter( "MinimalCosConeAngle",
    			"The minimal cone size",
    			_minCosConeAngle,
    			float(-1));

    	registerProcessorParameter( "MaximalCosConeAngle",
    			"The maximal cone size",
    			_maxCosConeAngle,
    			float(0.9));

    	registerProcessorParameter( "ConeEnergyRatio",
    			"The maximal cone size",
    			_ConeEnergyRatio,
    			float(0.95));

	}


void MCPhotonFinder::init() { 
    streamlog_out(DEBUG) << "   init MCPhotonFinder " << std::endl ;
    printParameters() ;

	_nEvt = 0;
	_nRun = 0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputWoIsoPhotonCol.Set_Switch(_output_switch_collection);
	_outputWoIsoPhotonCol.Set_Name(_outputWoIsoPhotonCollection);
	_outputIsoPhotonCol.Set_Switch(_output_switch_collection);
	_outputIsoPhotonCol.Set_Name(_outputIsoPhotonCollection);

	if(_output_switch_root){
		makeNTuple();
	}
}

void MCPhotonFinder::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void MCPhotonFinder::processEvent( LCEvent * evt ) { 
	Init(evt);

	bool JMC=analyseMCParticle( _MCsCol, _outputIsoPhotonCol, _outputWoIsoPhotonCol, _info.isophoton, _info.wophoton,_counter.MCs) ;

	Counter(JMC, evt);

	Finish(evt);
}

void MCPhotonFinder::Counter(bool JMC, LCEvent* evt){
	if(JMC){
		_global_counter.pass_MCs++;
		_global_counter.pass_all++;
		_single_counter.pass_MCs++;
		_single_counter.pass_all++;
	}
	else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}
}


void MCPhotonFinder::Init(LCEvent* evt) { 
	_nEvt++;
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

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run   =evt->getRunNumber();


	try{
		_MCsCol= evt->getCollection( _inputMCsCollection) ;
	}
	catch(...){
		std::cout << "no MCs without overlay in this event" << std::endl;
	}


	_outputWoIsoPhotonCol .Set_Collection_MCParticle();
	_outputIsoPhotonCol.Set_Collection_MCParticle();
}


void MCPhotonFinder::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}
// Add mcs to new collection
	_outputWoIsoPhotonCol.Add_Collection(evt);
	_outputIsoPhotonCol.Add_Collection(evt);

}


void MCPhotonFinder::check( LCEvent * evt ) { 
}

void MCPhotonFinder::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
}


void MCPhotonFinder::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	//Define root tree
	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_counter       .Fill_Data(_datatrain);
	_info          .Fill_Data(_datatrain);
	return;

}






































