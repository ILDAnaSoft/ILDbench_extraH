#include "PFOLeptonTagging.h"

PFOLeptonTagging aPFOLeptonTagging ;

PFOLeptonTagging::PFOLeptonTagging()
	: Processor("PFOLeptonTagging") {

		// Processor description
		_description = "Isolated Lepton Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPFOLeptonCollection", 
				"Name of the PFO lepton collection",
				_inputPFOLeptonCollection,
				std::string("PFO_Lepton") );

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPFOWoLeptonCollection", 
				"Name of the PFO wo lepton collection",
				_inputPFOWoLeptonCollection,
				std::string("PFO_Wo_Lepton") );

		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCsLeptonCollection", 
				"Name of the MCs lepton collection",
				_inputMCsLeptonCollection,
				std::string("MCParticles") );

		//output collection
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOLeptonCollection",
				"The output for New corrected PFO LeptonCollection",
				_outputPFOLeptonCollection,
				std::string("PFO_IsoLeptonRecovery") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOWoLeptonCollection",
				"The output for New corrected PFO LeptonCollection",
				_outputPFOWoLeptonCollection,
				std::string("PFO_Wo_IsoLeptonRecovery") );

		//output root
		registerProcessorParameter( "SwitchOutputRoot",
				"whether to write a root tree for observables",
				_output_switch_root,
				bool(true) );

		registerProcessorParameter( "RootFileName",
				"Name of Root file (default: output.root)",
				_rootfilename, 
				std::string("../result/output.root") );

		//Input parameters 
		registerProcessorParameter( "hmass",
				"hmass",
				_hmass,
				float(125) );

    	registerProcessorParameter( "cms",
    			"cms", 
    			_center_energy,
    			float(500));

	}


void PFOLeptonTagging::init() { 
	std::cout << "   init PFOLeptonTagging " << std::endl ;

	// usually a good idea to
	printParameters();

	_nEvt = 0;
	_nRun = 0;
	_global_counter.Init(_output_switch_root);
	_single_counter.Init(_output_switch_root);
	_counter.Init(_output_switch_root);
	_info.Init(_output_switch_root);

	_outputPFOLeptonCol           .Set_Switch(_output_switch_collection);
	_outputPFOLeptonCol           .Set_Name(_outputPFOLeptonCollection);
	_outputPFOWoLeptonCol         .Set_Switch(_output_switch_collection);
	_outputPFOWoLeptonCol         .Set_Name(_outputPFOWoLeptonCollection);

	// make Ntuple
	if(_output_switch_root){
		makeNTuple();
	}

	ToolSet::CMC::Set_Collider_Energy(_center_energy);

	lepnum=0;
}

void PFOLeptonTagging::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void PFOLeptonTagging::processEvent( LCEvent * evt ) { 

	Init(evt);

	int JPFO=analysePOParticle(_PFOLeptonCol,_PFOWoLeptonCol,_MCsLeptonCol,_outputPFOLeptonCol,_outputPFOWoLeptonCol,_info, _counter.PFO);

	Counter(JPFO,  evt);

	Finish(evt);
}

void PFOLeptonTagging::Counter(int JPFO, LCEvent* evt){
	if(JPFO>0){
		_global_counter.pass_PFO++;
		_single_counter.pass_PFO++;
	}
	else{
		//	ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}

	if(JPFO>0){
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

	_info.Init(_output_switch_root);
	_counter.Init(_output_switch_root);
	_single_counter.Init(_output_switch_root);

	_single_counter.evt=evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run=evt->getRunNumber();


	// PFO loop
	_PFOLeptonCol   = evt->getCollection( _inputPFOLeptonCollection  ) ;
	_PFOWoLeptonCol = evt->getCollection( _inputPFOWoLeptonCollection) ;
	_MCsLeptonCol   = evt->getCollection( _inputMCsLeptonCollection) ;

	_outputPFOLeptonCol  .Set_Collection_RCParticle();
	_outputPFOWoLeptonCol.Set_Collection_RCParticle();


}

void PFOLeptonTagging::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFOLeptonCol  .Add_Collection(evt);
	_outputPFOWoLeptonCol.Add_Collection(evt);
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
	std::cout << "tot lepnum is " <<lepnum << std::endl;
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











