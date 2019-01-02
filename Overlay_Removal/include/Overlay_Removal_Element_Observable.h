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

using namespace lcio ;
using namespace marlin ;
using namespace std;
using ToolSet::operator<<;
using ToolSet::operator-;
using ToolSet::operator+;

class Overlay_Removal_Global_Counter{
	public:
		//***********
		//event number
		//***********
		float evt         ;
		float pass_mc     ;
		float pass_po     ;
		float pass_jet    ;
		float pass_all    ;

		void Init(){
			evt           =0;
			pass_all      =0;
			pass_mc       =0;
			pass_po       =0;
			pass_jet      =0;
		}

		void Print(){
			std::cout << "in the Global counter, there are " << pass_mc << " pass MC, and " << pass_po << " pass PO, and " <<pass_all << " pass all criterion." << std::endl; 
		}
};

class Overlay_Removal_Counter{
	public:
		//***********
		//event number
		//***********
		float evt         ;
		float pass_all    ;

		void Init(){
			evt           =0;
			pass_all      =0;
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

class Overlay_Removal_Information{
	public:
		Overlay_Removal_Variable_Vec                    data_wo_overlay;

		Overlay_Removal_Observable                      data_observable_wo_overlay;


		Overlay_Removal_Information(){
		}


		void Init(){
			data_wo_overlay.Init();

			data_observable_wo_overlay.Init();
		}


		void Fill_Data(TTree* tree, std::string prefix){
			data_wo_overlay           .Fill_Data(tree,prefix+"_wo_overlay");

			data_observable_wo_overlay.Fill_Data(tree,prefix+"_observable_wo_overlay");
		}

		~Overlay_Removal_Information(){
		}
}; 

#endif
