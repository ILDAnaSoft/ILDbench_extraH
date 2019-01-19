#include "PFOLeptonTagging.h"

PFOLeptonTagging aPFOLeptonTagging ;

PFOLeptonTagging::PFOLeptonTagging()
	: Processor("PFOLeptonTagging") {

		// Processor description
		_description = "Isolated Lepton Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCsLeptonCollection", 
				"Name of the MC lepton collection",
				_inputMCsLeptonCollection,
				std::string("MCPS_Lepton") );

		//output collection
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOLeptonCollection",
				"The output for New corrected PFO LeptonCollection",
				_outputPFOLeptonCollection,
				std::string("PFOIsoLeptonConversion") );

		//output root
		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );

	}


void PFOLeptonTagging::init() { 
	std::cout << "   init PFOLeptonTagging " << std::endl ;

	// usually a good idea to
	printParameters();

	_nEvt = 0;
	_nRun = 0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputPFOLeptonCol           .Set_Switch(_output_switch_collection);

	_outputPFOLeptonCol           .Set_Name(_outputPFOLeptonCollection);

	// make Ntuple
	if(_output_switch_root){
		makeNTuple();
	}

}

void PFOLeptonTagging::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void PFOLeptonTagging::processEvent( LCEvent * evt ) { 

	Init(evt);

	int JMC1 =analyseMCParticle(_mcsLeptonCol, _outputPFOLeptonCol,_info, _counter.MCs1);

	Counter(JMC1,  evt);

	Finish(evt);
}

void PFOLeptonTagging::Counter(int JMC1, LCEvent* evt){
	if(JMC1>=0){
		_global_counter.pass_MCs1++;
		_single_counter.pass_MCs1++;
	}
	else{
		//	ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}

	if(JMC1){
		_global_counter.pass_all++;
		_single_counter.pass_all++;
	}
}


void PFOLeptonTagging::Init(LCEvent* evt) { 
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
	_mcsLeptonCol   = evt->getCollection( _inputMCsLeptonCollection  ) ;

	_outputPFOLeptonCol           .Set_Collection_RCParticle();


}

void PFOLeptonTagging::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFOLeptonCol           .Add_Collection(evt);
	// delete

}


void PFOLeptonTagging::check( LCEvent * evt ) { 
}

void PFOLeptonTagging::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain->Write();
		_outfile->Close();
	}
	_global_counter.Print();
}




void PFOLeptonTagging::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain= new TTree( "datatrain" , "events" );

	//Define root tree
	_global_counter.Fill_Data(_datatrain);
	_single_counter.Fill_Data(_datatrain);
	_info          .Fill_Data(_datatrain);
	_counter       .Fill_Data(_datatrain);
	return;

}











