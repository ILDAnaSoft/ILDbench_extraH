#ifndef Overlay_Removal_ELEMENT_DATATYPE_H
#define Overlay_Removal_ELEMENT_DATATYPE_H  
#include <string>
#include <iostream>
#include <map>

#include <marlin/Processor.h>
#include <lcio.h>

#include <EVENT/ReconstructedParticle.h>
#include <EVENT/MCParticle.h>
#include <UTIL/LCRelationNavigator.h>
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <marlin/VerbosityLevels.h>

#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include "TTree.h"
#include "TFile.h"


#include "CMC.h"
#include "CRC.h"
#include "CPrint.h"
#include "CFormat.h"
#include "CVector.h"

#include <IMPL/LCCollectionVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>

using ToolSet::operator<<;
using ToolSet::operator-;
using ToolSet::operator+;
using ToolSet::operator+=;

class Overlay_Removal_Global_Counter{
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float nrun        ;
		float gweight     ;
		float pass_MCs    ;
		float pass_PFO    ;
		float pass_jet    ;
		float pass_all    ;

		void Init(){
			nevt          = 0;
			nrun          = 0;
			gweight       = 0;
			pass_MCs      = 0;
			pass_PFO      = 0;
			pass_jet      = 0;
			pass_all      = 0;
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events and within " << nrun <<" runs " << " the global scale weight is " << gweight << std::endl; 
			std::cout << "There are " << pass_MCs << " events pass MCs;" << std::endl;
			std::cout << "There are " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "There are " << pass_jet << " events pass jet;" << std::endl;
			std::cout << "  totally " << pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class Overlay_Removal_Single_Counter{
	public:
		//***********
		//event number
		//***********
		float evt        ;
		float weight     ;
		float run        ;
		float pass_MCs   ;
		float pass_PFO   ;
		float pass_jet   ;
		float pass_all   ;

		void Init(){
			evt          = 0;
			run          = 0;
			weight       = 0;
	        pass_MCs     = 0;
	        pass_PFO     = 0;
	        pass_jet     = 0;
			pass_all     = 0;
		}

		void Print(){
			std::cout << "In the Single Event Counter, this is the " << evt << "th event, in the " << run << "th run." << std::endl;
			std::cout << " and " << pass_MCs << " events pass MCs;" << std::endl;
			std::cout << " and " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << " and " << pass_jet << " events pass jet;" << std::endl;
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);

};

class Overlay_Removal_Function_Counter   {
	public:
		float pass_all    ;

		float pass_num    ;

		float pass_energy ;


		void Init(){
	        pass_all    = 0;
	        pass_num    = 0;
	        pass_energy = 0;
		}

		void Fill_Data(TTree* tree, std::string prefix);
};



class Overlay_Removal_Counter{
	public:
		Overlay_Removal_Function_Counter MCs;
		Overlay_Removal_Function_Counter PFO;
		Overlay_Removal_Function_Counter jet;

		void Init(){
	        MCs.Init();
	        PFO.Init();
	        jet.Init();
		}

		void Fill_Data(TTree* tree){
			MCs                 .Fill_Data(tree,"MCs");
			PFO                 .Fill_Data(tree,"PFO");
			jet                 .Fill_Data(tree,"jet");
		}
};



class Overlay_Removal_Observable{
	public:
		//************************
		//inserted by process file
		//************************
		float visible_energy   ;        
		float invisible_energy   ;        

		void Init(){
		    visible_energy =-10000.1;        
		    invisible_energy =-10000.1;        
		}

		void Get_MCParticles_Information( std::vector<MCParticle*> input) ;
		void Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};


//Stored data 
class Overlay_Removal_Variable{
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

class Overlay_Removal_Variable_Vec{
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

class Overlay_Removal_Number{
	public:
		float num                ;
		float num_plus                   ;
		float num_minus                  ;
		float num_neutral                ;
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


class Overlay_Removal_Information_Single{
	public:
		Overlay_Removal_Observable                      obv;
		Overlay_Removal_Variable_Vec                    wo_overlay;
		Overlay_Removal_Number                          num_wo_overlay;


		void Init(){
			obv           .Init();
			wo_overlay    .Init();
			num_wo_overlay.Init();
		}


		void Get_MCParticles ( std::vector<MCParticle*> input) ;
		void Get_PFOParticles( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);

}; 


class Overlay_Removal_Information{
	public:
		Overlay_Removal_Information_Single mcs;
		Overlay_Removal_Information_Single jet;

		void Init(){
			mcs.Init();
			jet.Init();
		}


		void Fill_Data(TTree* tree){
			mcs.Fill_Data(tree,"_mcs");
			jet.Fill_Data(tree,"_jet");
		}

}; 

class Overlay_Removal_Output_Collection{
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
			    	col->addElement(input[i]);
			    }
			}
		}

		void Add_Element_RCParticle(std::vector<ReconstructedParticle*> input){
			if(Jopen){
			    for (int i = 0; i < input.size(); i++ ) {
			    	col->addElement(input[i]);
			    }
			}
		}
};
#endif
