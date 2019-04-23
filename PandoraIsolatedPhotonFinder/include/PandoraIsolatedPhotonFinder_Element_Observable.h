#ifndef PandoraIsolatedPhotonFinder_ELEMENT_DATATYPE_H
#define MCPhotonFPhoton_ELEMENT_DATATYPE_H  
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <utility>
#include <cmath>


#include "TTree.h"
#include "TFile.h"
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>

class TFile;
class TTree;

//header in the ToolSet
#include "CMC.h"
#include "CRC.h"
#include "CPrint.h"
#include "CFormat.h"
#include "CVector.h"
#include "CChain.h"

#include <IMPL/LCCollectionVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>

using ToolSet::operator<<;
using ToolSet::operator+;
using ToolSet::operator-;
using ToolSet::operator+=;

class PandoraIsolatedPhotonFinder_Global_Counter{
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float nrun        ;
		float gweight     ;
		float pass_PFO    ;
		float pass_all    ;

		void Init(){
			nevt          = 0;
			nrun          = 0;
			gweight       = 0;
			pass_PFO      = 0;
			pass_all      = 0;
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events and within " << nrun <<" runs " << " the global scale weight is " << gweight << std::endl; 
			std::cout << "There are " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "  totally " << pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class PandoraIsolatedPhotonFinder_Single_Counter{
	public:
		//***********
		//event number
		//***********
		float evt        ;
		float weight     ;
		float run        ;
		float pass_PFO   ;
		float pass_all   ;

		void Init(){
			evt         = 0;
			run         = 0;
			weight      = 0;
			pass_PFO    = 0;
			pass_all    = 0;
		}

		void Print(){
			std::cout << "In the Single Event Counter, this is the " << evt << "th event, in the " << run << "th run." << std::endl;
			std::cout << " and " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);

};

class PandoraIsolatedPhotonFinder_Function_Counter   {
	public:
		float pass_all    ;

		void Init(){
			pass_all    = 0;
		}

		void Fill_Data(TTree* tree, std::string prefix);
};



class PandoraIsolatedPhotonFinder_Counter{
	public:
		PandoraIsolatedPhotonFinder_Function_Counter PFO;

		void Init(){
			PFO.Init();
		}

		void Fill_Data(TTree* tree){
			PFO.Fill_Data(tree,"PFO");
		}
};

class PandoraIsolatedPhotonFinder_Observable{
	public:
		//************************
		//inserted by process file
		//************************

		std::vector<float> num_incone_total   ;
		std::vector<float> num_incone_charge  ;
		std::vector<float> num_incone_neutral ;
		std::vector<float> num_incone_photon  ;
		std::vector<float> num_incone_lepton  ;
		std::vector<float> num_incone_hadron  ;

		std::vector<float> input_energy;
		std::vector<float> cone_energy_total;
		std::vector<float> cone_energy_charge;
		std::vector<float> cone_energy_neutral;
		std::vector<float> cone_energy_photon;
		std::vector<float> cone_energy_lepton;
		std::vector<float> cone_energy_hadron;

		std::vector<float> cone_energy_ratio_total;
		std::vector<float> cone_energy_ratio_charge;
		std::vector<float> cone_energy_ratio_neutral;
		std::vector<float> cone_energy_ratio_photon;
		std::vector<float> cone_energy_ratio_lepton;
		std::vector<float> cone_energy_ratio_hadron;
		std::vector<float> cone_costheta;
		std::vector<float> mva_output;

		void Init(){
			num_incone_total         .clear();
			num_incone_charge        .clear();
			num_incone_neutral       .clear();
			num_incone_photon        .clear();
			num_incone_lepton        .clear();
			num_incone_hadron        .clear();

			input_energy             .clear();
			cone_energy_total        .clear();
			cone_energy_charge       .clear();
			cone_energy_neutral      .clear();
			cone_energy_photon       .clear();
			cone_energy_lepton       .clear();
			cone_energy_hadron       .clear();

			cone_energy_ratio_total  .clear();
			cone_energy_ratio_charge .clear();
			cone_energy_ratio_neutral.clear();
			cone_energy_ratio_photon .clear();
			cone_energy_ratio_lepton .clear();
			cone_energy_ratio_hadron .clear();
			cone_costheta            .clear();
			mva_output               .clear();
		}

		void Fill_Data(TTree* tree, std::string prefix);
};


//Stored data 
class PandoraIsolatedPhotonFinder_Variable{
	public:
		//************************
		//inserted by process file
		//************************
		float pdg                  ;        
		float p                    ;        
		float pt                   ;        
		float costheta             ;        
		float phi                  ;        
		float e                    ;        
		float mass                 ;        

		void Init(){
			pdg              =-10000.1;        
			p                =-10000.1;        
			pt               =-10000.1;        
			costheta         =-10000.1;        
			phi              =-10000.1;        
			e                =-10000.1;        
			mass             =-10000.1;        
		}

		void Get_MCParticle_Information( MCParticle* input) ;
		void Get_PFOParticle_Information( ReconstructedParticle* input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};

class PandoraIsolatedPhotonFinder_Variable_Vec{
	public:
		//************************
		//inserted by process file
		//************************
		std::vector<float> pdg                  ;        
		std::vector<float> p                    ;        
		std::vector<float> pt                   ;        
		std::vector<float> costheta             ;        
		std::vector<float> phi                  ;        
		std::vector<float> e                    ;        
		std::vector<float> mass                 ;        
		std::vector<float> endpointx            ;        
		std::vector<float> endpointy            ;        
		std::vector<float> endpointz            ;        
		std::vector<float> endpointr            ;        
		std::vector<float> vertexx              ;        
		std::vector<float> vertexy              ;        
		std::vector<float> vertexz              ;        
		std::vector<float> vertexr              ;        

		void Init(){
			pdg              .clear();        
			p                .clear();        
			pt               .clear();        
			costheta         .clear();        
			phi              .clear();        
			e                .clear();        
			mass             .clear();        
			endpointx        .clear();
			endpointy        .clear();
			endpointz        .clear();
			endpointr        .clear();
			vertexx          .clear();
			vertexy          .clear();
			vertexz          .clear();
			vertexr          .clear();
		}

		void Get_MCParticles_Information( std::vector<MCParticle*> input) ;
		void Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};

class PandoraIsolatedPhotonFinder_Number{
	public:
		float num                ;
		float num_plus           ;
		float num_minus          ;
		float num_neutral        ;
		float num_central        ;
		float num_forward        ;

		void Init(){
			num                = 0;
			num_plus           = 0;
			num_minus          = 0;
			num_neutral        = 0;
			num_central        = 0;
			num_forward        = 0;
		}

		void Get_MCParticles_Number ( std::vector<MCParticle*> input) ;
		void Get_PFOParticles_Number( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};

class PandoraIsolatedPhotonFinder_Information_Single{
	public:
		PandoraIsolatedPhotonFinder_Observable                      obv_small;
		PandoraIsolatedPhotonFinder_Observable                      obv_large;
		PandoraIsolatedPhotonFinder_Variable_Vec                    particle;
		PandoraIsolatedPhotonFinder_Number                          num;


		void Init(){
			obv_small  .Init();
			obv_large  .Init();
			particle   .Init();
			num        .Init();
		}


		void Get_MCParticles ( std::vector<MCParticle*> input) ;
		void Get_PFOParticles( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);

}; 

class PandoraIsolatedPhotonFinder_Information{
	public:
		PandoraIsolatedPhotonFinder_Information_Single isophoton;
		PandoraIsolatedPhotonFinder_Information_Single wophoton;

		void Init(){
			isophoton.Init();
			wophoton.Init();
		}


		void Fill_Data(TTree* tree){
			isophoton.Fill_Data(tree,"isophoton");
			wophoton.Fill_Data(tree,"wophoton");
		}

}; 

class PandoraIsolatedPhotonFinder_Output_Collection{
	public:
		std::string      name;
		LCCollectionVec* col;
		bool             Jopen;

		void Init(){
			Jopen=false;
		}

		void Set_Switch(bool open){
			Jopen=open;
		}

		void Set_Name(std::string in_name){
			name=in_name;
		}

		void Set_Collection_MCParticle(){
			if(Jopen){
				col= new LCCollectionVec( LCIO::MCPARTICLE ) ;
				col->setSubset(true) ;
			}
		}

		void Set_Collection_RCParticle(){
			if(Jopen){
				col= new LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE) ;
				col->setSubset(true) ;
			}
		}

		void Add_Collection(LCEvent* evt){
			if(Jopen){
				evt->addCollection(col, name.c_str() );
			}
		}

		void Add_Element_MCParticle(std::vector<MCParticle*> input){
			if(Jopen){
				for (int i = 0; i < input.size(); i++ ) {
					if(input[i]!=NULL){
						col->addElement(input[i]);
					}
				}
			}
		}

		void Add_Element_RCParticle(std::vector<ReconstructedParticle*> input){
			if(Jopen){
				for (int i = 0; i < input.size(); i++ ) {
					if(input[i]!=NULL){
						col->addElement(input[i]);
					}
				}
			}
		}
};
#endif
