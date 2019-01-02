#ifndef Strange_Photon_ELEMENT_DATATYPE_H
#define Strange_Photon_ELEMENT_DATATYPE_H  
#include <iostream>
#include <string>
#include <map>


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
		float weight      ;
		float pass_all    ;

		void Init(){
			nevt          =0;
			nrun          =0;
			weight        =0;
			pass_all      =0;
		}

		void Print(){
			std::cout << "in the Global Event Counter, this is  the " << nevt << "th event and the " << nrun <<" run " << " the weight is " << weight << std::endl; 
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class Strange_Photon_Single_Counter{
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float pass_mc     ;
		float pass_pfo    ;
		float pass_all    ;

		void Init(){
			nevt          =0;
			pass_mc       =0;
			pass_pfo      =0;
			pass_all      =0;
		}

		void Print(){
			std::cout << "In the Single Event Counter, Till now, there are totally " << nevt << " events, and " << pass_mc << " events pass MC, and " << pass_pfo << " events pass PFO, and " <<pass_all << " events pass all criterion." << std::endl; 

		}

		void Fill_Data(TTree* tree);
};

class Strange_Photon_Counter{
	public:
		//***********
		//event number
		//***********
		float pass_all    ;

		void Init(){
			pass_all      =0;
		}

		void Print(){
			std::cout << "in the Process Counter, in this process " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree, std::string prefix);

};

class Strange_Photon_Observable{
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

class Strange_Photon_Information{
	public:
		Strange_Photon_Variable                        data_variable;
		Strange_Photon_Variable_Vec                    data_variable_vec;
		Strange_Photon_Observable                      data_observable;


		Strange_Photon_Information(){
		}


		void Init(){
			data_variable.Init();
			data_variable_vec.Init();
			data_observable.Init();
		}


		void Fill_Data(TTree* tree, std::string prefix){
			data_observable  .Fill_Data(tree,prefix+"_observable");
			data_variable    .Fill_Data(tree,prefix+"_variable");
			data_variable_vec.Fill_Data(tree,prefix+"_variable_vec");
		}

		~Strange_Photon_Information(){
		}
}; 

#endif
