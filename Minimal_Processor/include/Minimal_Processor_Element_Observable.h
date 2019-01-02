#ifndef Minimal_Processor_ELEMENT_DATATYPE_H
#define Minimal_Processor_ELEMENT_DATATYPE_H  
#include "TTree.h"
#include <string>
#include <iostream>
#include <marlin/Processor.h>
#include <lcio.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/MCParticle.h>
#include <UTIL/LCRelationNavigator.h>
#include "CMC.h"
#include "CRC.h"

using namespace lcio ;
using namespace marlin ;
class Minimal_Processor_Global_Counter{
	public:
		//***********
		//event number
		//***********
		float evt         ;
		float pass_mc     ;
		float pass_pfo    ;
		float pass_all    ;

		void Init(){
			evt           =0;
			pass_all      =0;
			pass_mc       =0;
			pass_pfo      =0;
		}

		void Print(){
			std::cout << "in the Global counter, there are " << pass_mc << " pass MC, and " << pass_pfo << " pass PFO, and " <<pass_all << " pass all criterion." << std::endl; 
		}
};

class Minimal_Processor_Counter{
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

class Minimal_Processor_Observable{
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
class Minimal_Processor_Variable{
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

class Minimal_Processor_Variable_Vec{
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

class Minimal_Processor_Information{
	public:
		Minimal_Processor_Variable                        data_variable;
		Minimal_Processor_Variable_Vec                    data_variable_vec;
		Minimal_Processor_Observable                      data_observable;


		Minimal_Processor_Information(){
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

		~Minimal_Processor_Information(){
		}
}; 

#endif
