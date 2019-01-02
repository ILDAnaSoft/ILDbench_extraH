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

		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOwoOverlayCollection",
				"The output after removing the overlay",
				_outputPFOwoOverlayCollection,
				std::string("PFOwoOverlay") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputMCwoOverlayCollection",
				"The output after removing the overlay",
				_outputMCwoOverlayCollection,
				std::string("MCwoOverlay") );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );


	}


void Overlay_Removal::init() { 
	std::cout << "   init Overlay_Removal " << std::endl ;
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

void Overlay_Removal::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Overlay_Removal::processEvent( LCEvent * evt ) { 

	//init
	Init(evt);

	std::vector<MCParticle*> MCwoOverlay=analyseMCParticle(_in_mcCol, _mc_info);

	std::vector<ReconstructedParticle*> JetPFOwoOverlay=analyseJet(_in_islCol, _in_jetpoCol, _jet_info);

	if(_output_switch_collection){
		for(unsigned int i=0;i<MCwoOverlay.size();i++){
			_ot_MCwoOverlay->addElement( MCwoOverlay[i]);
		}
		
		for(unsigned int i=0;i<JetPFOwoOverlay.size();i++){
			_ot_PFOwoOverlay->addElement( JetPFOwoOverlay[i]);
		}
	}

	Finish(evt);
}

void Overlay_Removal::Init(LCEvent* evt) { 
	_nEvt ++;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;
	_mc_info.Init();
	_jet_info.Init();

	// Output PFOs removed isolated photon 
	if(_output_switch_collection){
		_ot_MCwoOverlay = new LCCollectionVec( LCIO::MCPARTICLE) ;
		_ot_MCwoOverlay ->setSubset(true) ;
		_ot_PFOwoOverlay= new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE ) ;
		_ot_PFOwoOverlay->setSubset(true) ;
	}


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

	if(_output_switch_collection){
		evt->addCollection( _ot_PFOwoOverlay, _outputPFOwoOverlayCollection.c_str() );
	    evt->addCollection( _ot_MCwoOverlay , _outputMCwoOverlayCollection.c_str() );
	}

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
		_otfile->cd();
		_datatrain->Write();
		_otfile->Close();
	}
	_global_counter.Print();
	std::cout << "Overlay_Removal::end()  " << std::endl;
}




void Overlay_Removal::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_otfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	_mc_info .Fill_Data(_datatrain,"mc");
	_jet_info.Fill_Data(_datatrain,"jet");
	return;

}











