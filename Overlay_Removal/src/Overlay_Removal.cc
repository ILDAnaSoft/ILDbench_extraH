#include "Overlay_Removal.h"

Overlay_Removal aOverlay_Removal ;

Overlay_Removal::Overlay_Removal()
	: Processor("Overlay_Removal") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCParticleCollection", 
				"Name of the MC particle collection",
				_inputMCsCollection,
				std::string("MCParticle") );

	    registerInputCollection( LCIO::LCRELATION,
	    		"InputMCRecoTruthLink",
	    		"Relation between MC and PFO particles",
	    		_input_mcpfoRelation,
	    		std::string("MCTruthRecoLink"));

		registerInputCollection( 
				LCIO::RECONSTRUCTEDPARTICLE,         
				"PFOsFromClusteredJets",                     
				"The collection name for PFOs from clustered jets",   
				_inputJetPOsCollection,                 
				std::string("PFOsFromFastJet") );        

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputIsolepsCollection",
				"Name of the isolated lepton collection",
				_inputIsolepsCollection,
				std::string("Isoleps") );

		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOwoOverlayCollection",
				"The output after removing the overlay",
				_outputPFOWoOverlayCollection,
				std::string("PFOwoOverlay") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputMCwoOverlayCollection",
				"The output after removing the overlay",
				_outputMCsWoOverlayCollection,
				std::string("MCwoOverlay") );

		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );


	}


void Overlay_Removal::init() { 
	std::cout << "   init Overlay_Removal " << std::endl ;
	printParameters();

	_nRun = 0;
	_nEvt = 0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputPFOWoOverlayCol.Set_Switch(_output_switch_collection);
	_outputPFOWoOverlayCol.Set_Name(_outputPFOWoOverlayCollection);
	_outputMCsWoOverlayCol.Set_Switch(_output_switch_collection);
	_outputMCsWoOverlayCol.Set_Name(_outputMCsWoOverlayCollection);

	if(_output_switch_root){
		makeNTuple();
	}

}

void Overlay_Removal::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Overlay_Removal::processEvent( LCEvent * evt ) { 

	//init
	Init(evt);

	std::vector<MCParticle*> MCwoOverlay=analyseMCParticle(_in_mcCol, _info.mcs);

	std::vector<ReconstructedParticle*> JetPFOwoOverlay=analyseJet(_in_islCol, _in_jetpoCol, _info.jet);

	_outputMCsWoOverlayCol.Add_Element_MCParticle(MCwoOverlay);
	_outputPFOWoOverlayCol.Add_Element_RCParticle(JetPFOwoOverlay);

	bool JMC=true;
	Counter(JMC, evt);

	Finish(evt);
}

void Overlay_Removal::Counter(bool JMC, LCEvent* evt){
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


void Overlay_Removal::Init(LCEvent* evt) { 
	_nEvt ++;
	_global_counter.nevt=_nEvt;
	_global_counter.nrun=_nRun;
	_global_counter.gweight=1;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

	_info.Init();
	_counter.Init();
	_single_counter.Init();

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run   =evt->getRunNumber();

	_outputPFOWoOverlayCol.Set_Collection_MCParticle();
	_outputMCsWoOverlayCol.Set_Collection_MCParticle();

	// PFO loop
	_in_mcCol   = evt->getCollection( _inputMCsCollection   ) ;

	_in_jetpoCol= evt->getCollection( _inputJetPOsCollection) ;

	_in_islCol  = evt->getCollection( _inputIsolepsCollection);

    _nav_MC_to_PFO = new LCRelationNavigator( evt->getCollection( _input_mcpfoRelation ) );

	ToolSet::CMC::Set_Nav_From_MC_To_RC(_nav_MC_to_PFO);
}

void Overlay_Removal::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFOWoOverlayCol.Add_Collection(evt);
	_outputMCsWoOverlayCol.Add_Collection(evt);

	ToolSet::CMC::Clear();
	ToolSet::CRC::Clear();
	streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
		<< "   in run:  " << evt->getRunNumber() 
		<< std::endl ;
}



void Overlay_Removal::check( LCEvent * evt ) { 
}

void Overlay_Removal::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
}




void Overlay_Removal::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_counter       .Fill_Data(_datatrain);
	_info          .Fill_Data(_datatrain);
	return;

}











