#ifndef Strange_Photon_ELEMENT_DATATYPE_H
#define Strange_Photon_ELEMENT_DATATYPE_H  
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

class Strange_Photon_Global_Counter{
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float nrun        ;
		float gweight     ;
		float pass_MCs1   ;
		float pass_MCs2   ;
		float pass_all    ;

		void Init(){
			nevt          = 0;
			nrun          = 0;
			gweight       = 0;
	        pass_MCs1     = 0;
	        pass_MCs2     = 0;
			pass_all      = 0;
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events and within " << nrun <<" runs " << " the global scale weight is " << gweight << std::endl; 
			std::cout << "There are " << pass_MCs1 << " events pass MCs1;" << std::endl;
			std::cout << "There are " << pass_MCs2 << " events pass MCs2;" << std::endl;
			std::cout << "  totally " << pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class Strange_Photon_Single_Counter{
	public:
		//***********
		//event number
		//***********
		float evt        ;
		float weight     ;
		float run        ;
		float pass_MCs1   ;
		float pass_MCs2   ;
		float pass_all   ;

		void Init(){
			evt         = 0;
			run         = 0;
			weight      = 0;
	        pass_MCs1     = 0;
	        pass_MCs2     = 0;
			pass_all    = 0;
		}

		void Print(){
			std::cout << "In the Single Event Counter, this is the " << evt << "th event, in the " << run << "th run." << std::endl;
			std::cout << " and " << pass_MCs1 << " events pass MCs1;" << std::endl;
			std::cout << " and " << pass_MCs2 << " events pass MCs2;" << std::endl;
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);

};

class Strange_Photon_Function_Counter   {
	public:
		float pass_all    ;

		void Init(){
	        pass_all    = 0;
		}

		void Fill_Data(TTree* tree, std::string prefix);
};



class Strange_Photon_Counter{
	public:
		Strange_Photon_Function_Counter MCs1;
		Strange_Photon_Function_Counter MCs2;

		void Init(){
	        MCs1.Init();
	        MCs2.Init();
		}

		void Fill_Data(TTree* tree){
			MCs1                .Fill_Data(tree,"MCs1");
			MCs2                .Fill_Data(tree,"MCs2");
		}
};


class Strange_Photon_Observable{
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
class Strange_Photon_Variable{
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

class Strange_Photon_Variable_Vec{
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

class Strange_Photon_Number{
	public:
		float num                        ;
		float num_plus                   ;
		float num_minus                  ;
		float num_neutral                ;
		float num_central                ;
		float num_forward                ;

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



class Strange_Photon_Information_Single{
	public:
		Strange_Photon_Observable                      obv;
		Strange_Photon_Variable_Vec                    particle;
		Strange_Photon_Number                          num;


		void Init(){
			obv         .Init();
			particle    .Init();
			num.Init();
		}


		void Get_MCParticles ( std::vector<MCParticle*> input) ;
		void Get_PFOParticles( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);

}; 

class Strange_Photon_Information{
	public:
		Strange_Photon_Information_Single mcs_lostenergy_photon;
		Strange_Photon_Information_Single pfo_lostenergy_photon;

		Strange_Photon_Information_Single pfo_photon_conversion;
		Strange_Photon_Information_Single pfo_wophoton_conversion;
		Strange_Photon_Information_Single pfo_lostenergy_photon_combined;

		Strange_Photon_Information_Single pfo_photon_only;
		Strange_Photon_Information_Single pfo_wophoton_only;
		Strange_Photon_Information_Single pfo_lostenergy_photon_rconly;

		void Init(){
			mcs_lostenergy_photon.Init();
			pfo_lostenergy_photon.Init();

			pfo_photon_conversion.Init();
			pfo_wophoton_conversion.Init();
			pfo_lostenergy_photon_combined.Init();

			pfo_photon_only      .Init();
			pfo_wophoton_only    .Init();
			pfo_lostenergy_photon_rconly.Init();
		}


		void Fill_Data(TTree* tree){
			mcs_lostenergy_photon  .Fill_Data(tree,"mcs_lostenergy_photon");
			pfo_lostenergy_photon  .Fill_Data(tree,"pfo_lostenergy_photon");

			pfo_photon_conversion  .Fill_Data(tree,"pfo_photon_conversion");
			pfo_wophoton_conversion.Fill_Data(tree,"pfo_wophoton_conversion");
			pfo_lostenergy_photon_combined.Fill_Data(tree,"pfo_lostenergy_photon_combined");

			pfo_photon_only        .Fill_Data(tree,"pfo_photon_only");
			pfo_wophoton_only      .Fill_Data(tree,"pfo_wophoton_only");
			pfo_lostenergy_photon_rconly.Fill_Data(tree,"pfo_lostenergy_photon_rconly");
		}

}; 

class Strange_Photon_Output_Collection{
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
