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
				"OutputPFOsRemovedIsoPhotonCollection",
				"The output for PFO Type Collection",
				_outputPFOsRemovedIsoPhotonCollection,
				std::string("outputPFOsRemovedIsoPhotonCollection") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputIsoPhotonConversionCollection",
				"The output for PFO Type Collection",
				_outputIsoPhotonConversionCollection,
				std::string("outputIsoPhotonConversionCollection") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputMCsRemovedIsoPhotonConversionCollection",
				"The output for PFO Type Collection",
				_outputMCsRemovedIsoPhotonConversionCollection,
				std::string("outputMCsRemovedIsoPhotonConversionCollection") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputIsoPhotonCollection",
				"The output for PFO Type Collection",
				_outputIsoPhotonCollection,
				std::string("outputIsoPhotonCollection") );

		//Input parameters 
		registerProcessorParameter( "ConeEnergyRatio",
				"cone energy ratio cut",
				_ConeEnergyRatio,
				float(0.95) );

		registerProcessorParameter( "MaxCosConeAngle",
				"max cone angle",
				_maxCosConeAngle,
				float(0.95) );

	}


void Strange_Photon::init() { 
	std::cout << "   init Strange_Photon " << std::endl ;

	// usually a good idea to
	printParameters();

	_nEvt = 0;
	_nRun = 0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputPFORemovedIsoPhotonCol          .Set_Switch(_output_switch_collection);
	_outputIsoPhotonCol                    .Set_Switch(_output_switch_collection);
	_outputIsoPhotonConversionCol          .Set_Switch(_output_switch_collection);
	_outputMCsRemovedIsoPhotonConversionCol.Set_Switch(_output_switch_collection);
	_outputPFORemovedIsoPhotonCol          .Set_Name(_outputPFOsRemovedIsoPhotonCollection);
	_outputIsoPhotonCol                    .Set_Name(_outputIsoPhotonCollection);
	_outputIsoPhotonConversionCol          .Set_Name(_outputIsoPhotonConversionCollection);
	_outputMCsRemovedIsoPhotonConversionCol.Set_Name(_outputMCsRemovedIsoPhotonConversionCollection);
	// make Ntuple
	if(_output_switch_root){
		makeNTuple();
	}

}

void Strange_Photon::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 

void Strange_Photon::processEvent( LCEvent * evt ) { 

	Init(evt);

	int JMC =analyseMCParticle(_mcCol, _navmcpfo, _info.mc,_info.mc2, _info.pfo, _counter.MCs);

	int JPFO=analysePFOParticle(_pfoCol, _navpfomc, _info.pfo, _counter.PFO);

	Counter(JMC, JPFO, evt);

	Finish(evt);
}

void Strange_Photon::Counter(int JMC, int JPFO,LCEvent* evt){
	if(JMC==1){
		_global_counter.pass_MCs++;
		_single_counter.pass_MCs++;
	}
	else if(JMC==0){
		_global_counter.pass_MCs++;
		_single_counter.pass_MCs++;
	}
	else{
		//	ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}

	if(JPFO){
		_global_counter.pass_PFO++;
		_single_counter.pass_PFO++;
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
	_global_counter.nrun=_nRun;
	_global_counter.gweight=1;
	if( _nEvt % 50 == 0 ) std::cout << "processing event "<< _nEvt << std::endl;

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

	_outputPFORemovedIsoPhotonCol          .Set_Collection_RCParticle();
	_outputIsoPhotonCol                    .Set_Collection_MCParticle();
	_outputIsoPhotonConversionCol          .Set_Collection_MCParticle();
	_outputMCsRemovedIsoPhotonConversionCol.Set_Collection_MCParticle();


}

void Strange_Photon::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFORemovedIsoPhotonCol          .Add_Collection(evt);
	_outputIsoPhotonCol                    .Add_Collection(evt);
	_outputIsoPhotonConversionCol          .Add_Collection(evt);
	_outputMCsRemovedIsoPhotonConversionCol.Add_Collection(evt);

	// delete
	delete _navmcpfo;
	delete _navpfomc;

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
}




void Strange_Photon::makeNTuple() {

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











