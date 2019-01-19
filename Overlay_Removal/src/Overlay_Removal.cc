#include "Overlay_Removal.h"

Overlay_Removal aOverlay_Removal ;

Overlay_Removal::Overlay_Removal()
	: Processor("Overlay_Removal") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		registerInputCollection( 
				LCIO::RECONSTRUCTEDPARTICLE,         
				"InputPandoraPFOCollection",                     
				"The collection name for PFOs ",   
				_inputPFOCollection,                 
				std::string("PandoraPFOs") );        

		registerInputCollection( 
				LCIO::RECONSTRUCTEDPARTICLE,         
				"InputPFOFromClusteredJets",                     
				"The collection name for PFOs from clustered jets",   
				_inputJetPFOCollection,                 
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
				"OutputPFOOverlayCollection",
				"The output of the overlay",
				_outputPFOOverlayCollection,
				std::string("PFOOverlay") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOWoOverlayCollection",
				"The output after removing the overlay",
				_outputPFOWoOverlayCollection,
				std::string("PFOWoOverlay") );

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
	_outputPFOOverlayCol  .Set_Switch(_output_switch_collection);
	_outputPFOOverlayCol  .Set_Name(_outputPFOOverlayCollection);

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

	bool JPFO=analyseJet(_in_pfoCol, _in_islCol, _in_jetpoCol, _outputPFOWoOverlayCol,_outputPFOOverlayCol, _info.wooverlay, _info.overlay);

	Counter(JPFO, evt);

	Finish(evt);
}

void Overlay_Removal::Counter(bool JPFO, LCEvent* evt){
	if(JPFO){
		_global_counter.pass_PFO++;
		_global_counter.pass_all++;
		_single_counter.pass_PFO++;
		_single_counter.pass_all++;
	}
	else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analysePFOParticle ");
	}
}


void Overlay_Removal::Init(LCEvent* evt) { 
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

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run   =evt->getRunNumber();

	_outputPFOWoOverlayCol.Set_Collection_RCParticle();
	_outputPFOOverlayCol  .Set_Collection_RCParticle();

	// PFO loop
	_in_pfoCol= evt->getCollection( _inputPFOCollection) ;

	_in_jetpoCol= evt->getCollection( _inputJetPFOCollection) ;

	_in_islCol  = evt->getCollection( _inputIsolepsCollection);

}

void Overlay_Removal::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFOWoOverlayCol.Add_Collection(evt);
	_outputPFOOverlayCol  .Add_Collection(evt);

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











