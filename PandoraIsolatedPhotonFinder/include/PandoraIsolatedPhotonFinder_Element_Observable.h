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
		float pass_all    ;

		void Init(){
			nevt          =0;
			pass_all      =0;
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events, and " <<pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class PandoraIsolatedPhotonFinder_Single_Counter{
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float weight      ;
		float nrun        ;
		float pass_all    ;

		void Init(){
			nevt          =0;
			nrun          =0;
			weight        =0;
			pass_all      =0;
		}

		void Print(){
			std::cout << "in the Single Event Counter, this is  the " << nevt << "th event and the " << nrun <<" run " << " the weight is " << weight << std::endl; 
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);

};

class PandoraIsolatedPhotonFinder_Observable{
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

class PandoraIsolatedPhotonFinder_Information{
	public:
		PandoraIsolatedPhotonFinder_Variable                        data_variable;
		PandoraIsolatedPhotonFinder_Variable_Vec                    data_variable_vec;
		PandoraIsolatedPhotonFinder_Observable                      data_observable;


		PandoraIsolatedPhotonFinder_Information(){
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

		~PandoraIsolatedPhotonFinder_Information(){
		}
}; 

#endif
