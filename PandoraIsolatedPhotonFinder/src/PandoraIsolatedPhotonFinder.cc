#include "PandoraIsolatedPhotonFinder.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <cmath>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <IMPL/LCCollectionVec.h>

// ----- include for verbosity dependend logging ---------
#include <marlin/VerbosityLevels.h>

#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include "TMVA/Reader.h"

using namespace lcio ;
using namespace marlin ;
using namespace std;
using namespace TMVA;

PandoraIsolatedPhotonFinder aPandoraIsolatedPhotonFinder ;

PandoraIsolatedPhotonFinder::PandoraIsolatedPhotonFinder()
	: Processor("PandoraIsolatedPhotonFinder") {

		// Processor description
		_description = "Isolated Photon Finder Processor" ;

		// register steering parameters: name, description, class-variable, default value
		registerInputCollection( LCIO::MCPARTICLE,
				"InputMCCollection" ,
				"Input collection of MCParticle",
				_inputMCsCollection,
				std::string("MCParticle"));

		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"InputPFOCollection" ,
				"Input collection of ReconstructedParticles",
				_inputPFOsCollection,
				std::string("PandoraPFOs"));

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

		registerProcessorParameter( "MVACut",
				"MVA cut for ISO photon",
				_mvaCut,
				float(0.8) );

		registerProcessorParameter("DirOfWeights",
				"Directory of Weights for the Isolated photon MVA Classification"  ,
				_mva_weights ,
				std::string("isolated_photon_weights") ) ;

		//Output Collection 
		registerProcessorParameter( "SwitchOutputCollection",
				"whether to write a Marlin collection for further Marlin",
				_output_switch_collection,
				bool(true) );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputCollectionIsolatedPhoton",
				"Output collection of isolated photon in non-forward region",
				_outputIsoPhotonCollection,
				std::string("PFO_IsoPhoton") );

		registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
				"OutputCollectionWoIsolatedPhoton",
				"Copy of input collection but without the isolated photon",
				_outputWoIsoPhotonCollection,
				std::string("PFO_WoIsoPhoton") );

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
				float(30));

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

		registerProcessorParameter( "MaximalPollarAngle",
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
				float(30));

		registerProcessorParameter( "MaximalForwardEnergyCut",
				"The maximal energy for a isolated photon in the forward region",
				_maxForwardEnergyCut,
				float(-1));

		registerProcessorParameter( "UseForwardAngle",
				"Use forward angle cut",
				_useForwardPolarAngle,
				bool(true));

		registerProcessorParameter( "MinimalForwardPollarAngle",
				"The minimal cosine angle to define a forward region",
				_minForwardCosTheta,
				float(0.95));

		registerProcessorParameter( "MaximalForwardPollarAngle",
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
				float(0.98));

		registerProcessorParameter( "MaximalCosConeAngle",
				"The maximal cone size",
				_maxCosConeAngle,
				float(0.95));

		registerProcessorParameter( "ConeEnergyRatio",
				"The maximal cone size",
				_ConeEnergyRatio,
				float(0.95));

	}


void PandoraIsolatedPhotonFinder::init() { 
	std::cout << "   init PandoraIsolatedPhotonFinder " << std::endl ;
	printParameters() ;

	_nEvt = 0;
	_nRun = 0;
	_pnum = 0;
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

	if(_output_switch_root&&!_output_switch_collection){
	}
	else{
		_reader = new TMVA::Reader( "Color:Silent" );    
		// add input variables
		_reader->AddVariable( "isophoton_obv_small_num_incone_total"  ,        &_info_isr.isophoton.obv_small.num_incone_total    );
		_reader->AddVariable( "isophoton_obv_small_num_incone_charge" ,        &_info_isr.isophoton.obv_small.num_incone_charge   );
		_reader->AddVariable( "isophoton_obv_small_num_incone_photon" ,        &_info_isr.isophoton.obv_small.num_incone_photon   );
		_reader->AddVariable( "isophoton_obv_small_num_incone_lepton" ,        &_info_isr.isophoton.obv_small.num_incone_lepton   );

////	_reader->AddVariable( "isophoton_obv_small_cone_energy_total"  ,       &_info_isr.isophoton.obv_small.cone_energy_total  );
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_charge" ,       &_info_isr.isophoton.obv_small.cone_energy_charge );
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_neutral",       &_info_isr.isophoton.obv_small.cone_energy_neutral);
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_photon" ,       &_info_isr.isophoton.obv_small.cone_energy_photon );
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_lepton" ,       &_info_isr.isophoton.obv_small.cone_energy_lepton );
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_hadron" ,       &_info_isr.isophoton.obv_small.cone_energy_hadron );

		_reader->AddVariable( "isophoton_obv_small_cone_energy_ratio_total"  , &_info_isr.isophoton.obv_small.cone_energy_ratio_total  );
		_reader->AddVariable( "isophoton_obv_small_cone_energy_ratio_charge" , &_info_isr.isophoton.obv_small.cone_energy_ratio_charge );
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_ratio_neutral", &_info_isr.isophoton.obv_small.cone_energy_ratio_neutral);
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_ratio_photon" , &_info_isr.isophoton.obv_small.cone_energy_ratio_photon );
////	_reader->AddVariable( "isophoton_obv_small_cone_energy_ratio_lepton" , &_info_isr.isophoton.obv_small.cone_energy_ratio_lepton );
		_reader->AddVariable( "isophoton_obv_small_cone_energy_ratio_hadron" , &_info_isr.isophoton.obv_small.cone_energy_ratio_hadron );
//		_reader->AddVariable( "isophoton_obv_small_cone_costheta"            , &_info_isr.isophoton.obv_small.cone_costheta            );

////	_reader->AddVariable( "isophoton_obv_large_num_incone_total"  ,        &_info_isr.isophoton.obv_large.num_incone_total    );
////	_reader->AddVariable( "isophoton_obv_large_num_incone_charge" ,        &_info_isr.isophoton.obv_large.num_incone_charge   );
////	_reader->AddVariable( "isophoton_obv_large_num_incone_neutral",        &_info_isr.isophoton.obv_large.num_incone_neutral  );
////	_reader->AddVariable( "isophoton_obv_large_num_incone_photon" ,        &_info_isr.isophoton.obv_large.num_incone_photon   );
////	_reader->AddVariable( "isophoton_obv_large_num_incone_lepton" ,        &_info_isr.isophoton.obv_large.num_incone_lepton   );
////	_reader->AddVariable( "isophoton_obv_large_num_incone_hadron" ,        &_info_isr.isophoton.obv_large.num_incone_hadron   );

////	_reader->AddVariable( "isophoton_obv_large_cone_energy_total"  ,       &_info_isr.isophoton.obv_large.cone_energy_total  );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_charge" ,       &_info_isr.isophoton.obv_large.cone_energy_charge );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_neutral",       &_info_isr.isophoton.obv_large.cone_energy_neutral);
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_photon" ,       &_info_isr.isophoton.obv_large.cone_energy_photon );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_lepton" ,       &_info_isr.isophoton.obv_large.cone_energy_lepton );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_hadron" ,       &_info_isr.isophoton.obv_large.cone_energy_hadron );

////	_reader->AddVariable( "isophoton_obv_large_cone_energy_ratio_total"  , &_info_isr.isophoton.obv_large.cone_energy_ratio_total  );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_ratio_charge" , &_info_isr.isophoton.obv_large.cone_energy_ratio_charge );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_ratio_neutral", &_info_isr.isophoton.obv_large.cone_energy_ratio_neutral);
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_ratio_photon" , &_info_isr.isophoton.obv_large.cone_energy_ratio_photon );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_ratio_lepton" , &_info_isr.isophoton.obv_large.cone_energy_ratio_lepton );
////	_reader->AddVariable( "isophoton_obv_large_cone_energy_ratio_hadron" , &_info_isr.isophoton.obv_large.cone_energy_ratio_hadron );
		_reader->AddVariable( "isophoton_obv_large_cone_costheta"            , &_info_isr.isophoton.obv_large.cone_costheta            );

		// book the reader (method, weights)
		TString dir    = _mva_weights;
		TString prefix = "TMVAClassification";
		TString methodName = "BDTGmethod";
		TString weightfile = dir + "/" + prefix + "_" + "BDTG.weights.xml";
		_reader->BookMVA( methodName, weightfile ); 
	}
}

void PandoraIsolatedPhotonFinder::processRunHeader( LCRunHeader* run) { 
	_nRun++;
} 












void PandoraIsolatedPhotonFinder::processEvent( LCEvent * evt ) { 
	Init(evt);

	bool JPFO=analysePFOParticle(_MCsCol, _PFOCol, _outputIsoPhotonCol, _outputWoIsoPhotonCol,_info_isr,_info_normal,_counter.PFO) ;

	Counter(JPFO, evt);

	Finish(evt);
}




void PandoraIsolatedPhotonFinder::Counter(bool JPFO, LCEvent* evt){
	if(JPFO){
		_global_counter.pass_PFO++;
		_global_counter.pass_all++;
		_single_counter.pass_PFO++;
		_single_counter.pass_all++;
	}
	else{
		ToolSet::ShowMessage(1,"in processEvent: not pass analyseMCParticle ");
	}
}






void PandoraIsolatedPhotonFinder::Init(LCEvent* evt) { 
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

	_info_isr.Init();
	_info_normal.Init();
	_counter.Init();
	_single_counter.Init();

	_single_counter.evt   =evt->getEventNumber();
	_single_counter.weight=evt->getWeight();
	_single_counter.run   =evt->getRunNumber();

	try{
		_PFOCol = evt->getCollection( _inputPFOsCollection ) ;
	}
	catch(...){
		std::cout << "no PFO without overlay in this event" << std::endl;
	}

	_MCsCol= evt->getCollection( _inputMCsCollection  ) ;
	_navmcpfo = new LCRelationNavigator( evt->getCollection( _mcpfoRelation ) );
	_navpfomc = new LCRelationNavigator( evt->getCollection( _pfomcRelation ) );



	_outputWoIsoPhotonCol.Set_Collection_RCParticle();
	_outputIsoPhotonCol  .Set_Collection_RCParticle();

}


void PandoraIsolatedPhotonFinder::Finish(LCEvent* evt) { 
	if(_output_switch_root){
		_datatrain_sig->Fill();
		_datatrain_bkg->Fill();
	}
// Add mcs to new collection
	_outputWoIsoPhotonCol.Add_Collection(evt);
	_outputIsoPhotonCol  .Add_Collection(evt);
}

void PandoraIsolatedPhotonFinder::check( LCEvent * evt ) { 
}

void PandoraIsolatedPhotonFinder::end() { 
	if(_output_switch_root){
		_outfile->cd();
		_datatrain_sig->Write();
		_datatrain_bkg->Write();
		_outfile->Close();
	}

	if(_output_switch_root&&!_output_switch_collection){
	}
	else{
		delete _reader;
	}
	std::cout << "total photon number " << _pnum << std::endl;
	_global_counter.Print();

}




void PandoraIsolatedPhotonFinder::makeNTuple() {

	//Output root file
	std::cout << _rootfilename << std::endl;
	_outfile = new TFile( _rootfilename.c_str() , "RECREATE" );
	_datatrain_sig= new TTree( "datatrain_sig" , "events" );
	_datatrain_bkg= new TTree( "datatrain_bkg" , "events" );

	//Define root tree
	_global_counter.Fill_Data(_datatrain_sig);
	_single_counter.Fill_Data(_datatrain_sig);
	_counter       .Fill_Data(_datatrain_sig);

	_info_isr.Fill_Data(_datatrain_sig);
	_info_normal.Fill_Data(_datatrain_bkg);
	return;

}


















































