#ifndef MCPhotonFPhoton_ELEMENT_DATATYPE_H 
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
#include "CLorentzVector.h"

using ToolSet::operator<<;
using ToolSet::operator+;
using ToolSet::operator-;
using ToolSet::operator+=;

class MCLevelClassify_Global_Counter{
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float nrun        ;
		float gweight     ;
		float pass_MCs    ;
		float pass_all    ;

		void Init(){
			nevt          = 0;
			nrun          = 0;
			gweight       = 0;
	        pass_MCs      = 0;
			pass_all      = 0;
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events and within " << nrun <<" runs " << " the global scale weight is " << gweight << std::endl; 
			std::cout << "There are " << pass_MCs << " events pass MCs;" << std::endl;
			std::cout << "  totally " << pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class MCLevelClassify_Single_Counter{
	public:
		//***********
		//event number
		//***********
		float evt        ;
		float weight     ;
		float run        ;
		float pass_MCs   ;
		float pass_all   ;

		void Init(){
			evt          =0;
			run          =0;
			weight        =0;
	        pass_MCs      = 0;
			pass_all      =0;
		}

		void Print(){
			std::cout << "In the Single Event Counter, this is the " << evt << "th event, in the " << run << "th run." << std::endl;
			std::cout << " and " << pass_MCs << " events pass MC;" << std::endl;
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);

};

class MCLevelClassify_Function_Counter   {
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



class MCLevelClassify_Counter{
	public:
		MCLevelClassify_Function_Counter MCs;

		void Init(){
	        MCs.Init();
		}

		void Fill_Data(TTree* tree){
			MCs                 .Fill_Data(tree,"MCs");
		}
};


class MCLevelClassify_Observable{
	public:
		//************************
		//inserted by process file
		//************************
		float visible_energy   ;        

		void Init(){
		    visible_energy =-10000.1;        
		}

		void Fill_Data(TTree* tree, std::string prefix);
};


//Stored data 
class MCLevelClassify_Variable{
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

class MCLevelClassify_Variable_Vec{
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

		void Init(){
		    pdg              .clear();        
		    p                .clear();        
		    pt               .clear();        
		    costheta         .clear();        
		    phi              .clear();        
		    e                .clear();        
		    mass             .clear();        
		}

		void Get_MCParticles_Information( std::vector<MCParticle*> input) ;
		void Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};

class MCLevelClassify_Number{
	public:
		float num                        ;
		float num_plus                   ;
		float num_minus                  ;
		float num_neutral                ;
		float num_central                ;
		float num_forward                ;

		void Init(){
		    num                = -10000.1;
		    num_plus           = -10000.1;
		    num_minus          = -10000.1;
			num_neutral        = -10000.1;
			num_central        = -10000.1;
			num_forward        = -10000.1;
		}

		void Fill_Data(TTree* tree, std::string prefix);
};



class MCLevelClassify_Information_Single{
	public:
		MCLevelClassify_Observable                      obv;
		MCLevelClassify_Variable_Vec                    leps;
		MCLevelClassify_Number                          num_muon;
		MCLevelClassify_Number                          num_MCs;


		void Init(){
			obv        .Init();
			leps       .Init();
			num_muon   .Init();
			num_MCs    .Init();
		}


		void Fill_Data(TTree* tree, std::string prefix){
			obv              .Fill_Data(tree,prefix+"_obv");
			leps             .Fill_Data(tree,prefix+"_leps");
			num_muon         .Fill_Data(tree,prefix+"_num_muon");
			num_MCs          .Fill_Data(tree,prefix+"_num_MCs" );
		}

}; 

class MCLevelClassify_Information{
	public:
		MCLevelClassify_Information_Single isolep;

		void Init(){
			isolep           .Init();
		}


		void Fill_Data(TTree* tree){
			isolep           .Fill_Data(tree,"isolep"           );
		}

}; 



#endif
