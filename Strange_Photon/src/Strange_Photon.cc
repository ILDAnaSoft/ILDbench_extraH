#include "Strange_Photon.h"

Strange_Photon aStrange_Photon ;

Strange_Photon::Strange_Photon()
	: Processor("Strange_Photon") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCsPhotonCollection", 
				"Name of the MC photon collection",
				_inputMCsPhotonCollection,
				std::string("MCPS_Photon") );

		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCsWoPhotonCollection", 
				"Name of the MC particle Wo photon collection",
				_inputMCsWoPhotonCollection,
				std::string("MCPS_WoPhoton") );

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPFOPhotonCollection" ,
				"Input collection of Reconstructed Photon",
				_inputPFOPhotonCollection,
				std::string("PFO_Photon"));

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPFOWoPhotonCollection" ,
				"Input collection of ReconstructedParticles Wo Photon",
				_inputPFOWoPhotonCollection,
				std::string("PFO_WoPhoton"));

		registerInputCollection( LCIO::LCRELATION,
				"InputMCTruthRecoLink",
				"Relation between MC and PFO particles",
				_mcpfoRelation,
				std::string("MCTruthRecoLink"));

		registerInputCollection( LCIO::LCRELATION,
				"InputRecoMCTruthLink",
				"Relation between MC and PFO particles",
				_pfomcRelation,
				std::string("RecoMCTruthLink"));



		//output collection
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOPhoton_ConversionCollection",
				"The output for New corrected PFO PhotonCollection",
				_outputPFOPhoton_ConversionCollection,
				std::string("PFOIsoPhotonConversion") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOWoPhoton_ConversionCollection",
				"The output for PFO Type Collection",
				_outputPFOWoPhoton_ConversionCollection,
				std::string("PFORemovedIsoPhotonConversion") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOLostEnergyPhoton_CombinedCollection",
				"The output for PFOs which lost energy and contain all particles coming from mc photon Collection",
				_outputPFOLostEnergyPhoton_CombinedCollection,
				std::string("PFOLostEnergyPhoton_CombinedConversion") );




		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOPhoton_OnlyCollection",
				"The output for New corrected PFO PhotonCollection",
				_outputPFOPhoton_OnlyCollection,
				std::string("PFOIsoPhotonOnly") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOWoPhoton_OnlyCollection",
				"The output for PFO Type Collection",
				_outputPFOWoPhoton_OnlyCollection,
				std::string("PFORemovedIsoPhotonOnly") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOLostEnergyPhoton_RCOnlyCollection",
				"The output for PFOs which lost energy and contain all particles coming from mc photon Collection",
				_outputPFOLostEnergyPhoton_RCOnlyCollection,
				std::string("PFOLostEnergyPhoton_RCOnly") );




		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputPFOLostEnergyPhotonCollection",
				"The output for PFO which lost energy and is a photon Collection",
				_outputPFOLostEnergyPhotonCollection,
				std::string("PFOLostEnergyPhotonConversion") );

		registerOutputCollection( LCIO::MCPARTICLE,
				"OutputMCsLostEnergyPhotonCollection",
				"The output for MCs PDG Collection",
				_outputMCsLostEnergyPhotonCollection,
				std::string("MCsLostEnergyPhotonConversion") );

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
		registerProcessorParameter( "MinEnergyDifferenceRario",
				"min energy difference between mc photon and reconstructed constituents",
				_minEnergyDifferenceRatio,
				float(0.05) );

	}


void Strange_Photon::init() { 
	std::cout << "   init Strange_Photon " << std::endl ;

	// usually a good idea to
	printParameters();

	_nEvt = 0;
	_nRun = 0;
	_pnum =0;
	_global_counter.Init();
	_single_counter.Init();
	_counter.Init();

	_outputPFOPhoton_ConversionCol           .Set_Switch(_output_switch_collection);
	_outputPFOWoPhoton_ConversionCol         .Set_Switch(_output_switch_collection);
	_outputPFOLostEnergyPhoton_CombinedCol   .Set_Switch(_output_switch_collection);
	_outputPFOPhoton_OnlyCol                 .Set_Switch(_output_switch_collection);
	_outputPFOWoPhoton_OnlyCol               .Set_Switch(_output_switch_collection);
	_outputPFOLostEnergyPhoton_RCOnlyCol     .Set_Switch(_output_switch_collection);
	_outputPFOLostEnergyPhotonCol            .Set_Switch(_output_switch_collection);
	_outputMCsLostEnergyPhotonCol            .Set_Switch(_output_switch_collection);

	_outputPFOPhoton_ConversionCol           .Set_Name(_outputPFOPhoton_ConversionCollection);
	_outputPFOWoPhoton_ConversionCol         .Set_Name(_outputPFOWoPhoton_ConversionCollection);
	_outputPFOLostEnergyPhoton_CombinedCol   .Set_Name(_outputPFOLostEnergyPhoton_CombinedCollection);
	_outputPFOPhoton_OnlyCol                 .Set_Name(_outputPFOPhoton_OnlyCollection);
	_outputPFOWoPhoton_OnlyCol               .Set_Name(_outputPFOWoPhoton_OnlyCollection);
	_outputPFOLostEnergyPhoton_RCOnlyCol     .Set_Name(_outputPFOLostEnergyPhoton_RCOnlyCollection);
	_outputPFOLostEnergyPhotonCol            .Set_Name(_outputPFOLostEnergyPhotonCollection);
	_outputMCsLostEnergyPhotonCol            .Set_Name(_outputMCsLostEnergyPhotonCollection);

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

//	int JMC1 =analyseMCParticle_Conversion(_mcsPhotonCol, _mcsWoPhotonCol, _pfoPhotonCol, _pfoWoPhotonCol, _outputPFOLostEnergyPhotonCol, _outputPFOLostEnergyPhoton_CombinedCol, _outputMCsLostEnergyPhotonCol, _outputPFOPhoton_ConversionCol, _outputPFOWoPhoton_ConversionCol, _navmcpfo, _navpfomc,_info, _counter.MCs1);

//	int JMC2 =analyseMCParticle_OnlyPhoton(_mcsPhotonCol, _mcsWoPhotonCol, _pfoPhotonCol, _pfoWoPhotonCol, _outputPFOLostEnergyPhoton_RCOnlyCol, _outputPFOPhoton_OnlyCol, _outputPFOWoPhoton_OnlyCol, _navmcpfo, _navpfomc,_info, _counter.MCs2);

	int JMC1=0, JMC2=0;
  	int JMC3 =analyseMCParticle_Check(_mcsPhotonCol, _mcsWoPhotonCol, _pfoPhotonCol, _pfoWoPhotonCol, _navmcpfo, _navpfomc,_info, _counter.MCs1);

	Counter(JMC1, JMC2,  evt);

	Finish(evt);
}

void Strange_Photon::Counter(int JMC1, int JMC2, LCEvent* evt){
	if(JMC1>=0){
		_global_counter.pass_MCs1++;
		_single_counter.pass_MCs1++;
	}
	else{
		//	ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}

	if(JMC2>=0){
		_global_counter.pass_MCs2++;
		_single_counter.pass_MCs2++;
	}
	else{
		//	ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}

	if(JMC1&&JMC2){
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
	_mcsPhotonCol   = evt->getCollection( _inputMCsPhotonCollection  ) ;
	_mcsWoPhotonCol = evt->getCollection( _inputMCsWoPhotonCollection) ;
	_pfoPhotonCol   = evt->getCollection( _inputPFOPhotonCollection  ) ;
	_pfoWoPhotonCol = evt->getCollection( _inputPFOWoPhotonCollection) ;

	_navmcpfo = new LCRelationNavigator( evt->getCollection( _mcpfoRelation ) );
	_navpfomc = new LCRelationNavigator( evt->getCollection( _pfomcRelation ) );
	ToolSet::CMC::Set_Nav_From_MC_To_RC(_navmcpfo);

	_outputPFOPhoton_ConversionCol           .Set_Collection_RCParticle();
	_outputPFOWoPhoton_ConversionCol         .Set_Collection_RCParticle();
	_outputPFOLostEnergyPhoton_CombinedCol   .Set_Collection_RCParticle();
	_outputPFOPhoton_OnlyCol                 .Set_Collection_RCParticle();
	_outputPFOWoPhoton_OnlyCol               .Set_Collection_RCParticle();
	_outputPFOLostEnergyPhoton_RCOnlyCol     .Set_Collection_RCParticle();
	_outputPFOLostEnergyPhotonCol            .Set_Collection_RCParticle();
	_outputMCsLostEnergyPhotonCol            .Set_Collection_MCParticle();


}

void Strange_Photon::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain->Fill();
	}

	_outputPFOPhoton_ConversionCol           .Add_Collection(evt);
	_outputPFOWoPhoton_ConversionCol         .Add_Collection(evt);
	_outputPFOLostEnergyPhoton_CombinedCol   .Add_Collection(evt);
	_outputPFOPhoton_OnlyCol                 .Add_Collection(evt);
	_outputPFOWoPhoton_OnlyCol               .Add_Collection(evt);
	_outputPFOLostEnergyPhoton_RCOnlyCol     .Add_Collection(evt);
	_outputPFOLostEnergyPhotonCol            .Add_Collection(evt);
	_outputMCsLostEnergyPhotonCol            .Add_Collection(evt);
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
	std::cout << "total photon number " << _pnum << std::endl;
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











