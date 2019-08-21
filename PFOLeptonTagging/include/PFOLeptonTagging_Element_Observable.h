#ifndef PFOLeptonTagging_ELEMENT_DATATYPE_H
#define PFOLeptonTagging_ELEMENT_DATATYPE_H  
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
#include "CVertex.h"

#include <IMPL/LCCollectionVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>

using ToolSet::operator<<;
using ToolSet::operator+;
using ToolSet::operator-;
using ToolSet::operator+=;

class PFOLeptonTagging_Global_Counter{
	private:
		bool _switch_root;
	public:
		//***********
		//event number
		//***********
		float nevt        ;
		float nrun        ;
		float gweight     ;
		float pass_PFO    ;
		float pass_all    ;

		void Init(bool switch_root){
			_switch_root = switch_root;
			if(_switch_root){
				nevt          = 0;
				nrun          = 0;
				gweight       = 0;
				pass_PFO      = 0;
				pass_all      = 0;
			}
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events and within " << nrun <<" runs " << " the global scale weight is " << gweight << std::endl; 
			std::cout << "There are " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "  totally " << pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};

class PFOLeptonTagging_Single_Counter{
	private:
		bool _switch_root;
	public:
		//***********
		//event number
		//***********
		float evt        ;
		float weight     ;
		float run        ;
		float pass_PFO   ;
		float pass_all   ;

		void Init(bool switch_root){
			_switch_root = switch_root;
			if(_switch_root){
				evt         = 0;
				run         = 0;
				weight      = 0;
				pass_PFO    = 0;
				pass_all    = 0;
			}
		}

		void Print(){
			std::cout << "In the Single Event Counter, this is the " << evt << "th event, in the " << run << "th run." << std::endl;
			std::cout << " and " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);

};

class PFOLeptonTagging_Function_Counter   {
	public:
		float pass_all    ;

		void Init(){
			pass_all    = 0;
		}

		void Fill_Data(TTree* tree, std::string prefix);
};



class PFOLeptonTagging_Counter{
	private:
		bool _switch_root;
	public:
		PFOLeptonTagging_Function_Counter PFO;

		void Init(bool switch_root){
			_switch_root = switch_root;
			if(_switch_root){
				PFO.Init();
			}
		}

		void Fill_Data(TTree* tree){
			if(_switch_root){
				PFO.Fill_Data(tree,"counter_PFO");
			}
		}
};


class PFOLeptonTagging_Observable{
	public:
		//************************
		//inserted by process file
		//************************
		float  combined_inm                ;
		float  sigma_inm                   ;
		float  combined_pt                 ;
		float  recoil_mass                 ;
		float  sigma_recoil                ;

		float  lepton_pair_costheta;
		float  lepton_pair_costheta_pair;
		float  lepton_pair_azimuth;
		float  lepton_pair_azimuth_pair;


		float vtx;
		float vty;
		float vtz;
		float chi2;        

		void Init(){
			combined_inm             =-10000.1;
			sigma_inm                =-10000.1;
			combined_pt              =-10000.1;
			recoil_mass              =-10000.1;
			sigma_recoil             =-10000.1;

			lepton_pair_costheta     =-10000.1;
			lepton_pair_costheta_pair=-10000.1;
			lepton_pair_azimuth      =-10000.1;
			lepton_pair_azimuth_pair =-10000.1;

			vtx  = -10000.1;
			vty  = -10000.1;
			vtz  = -10000.1;
			chi2 = -10000.1;        
		}

		void Get_MCParticles_Information( std::vector<MCParticle*> input) ;
		void Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) ;
		void Get_Vertex_Information( VertexInfo& vv) ;
		void Fill_Data(TTree* tree, std::string prefix);
};


//Stored data 
class PFOLeptonTagging_Variable{
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

class PFOLeptonTagging_Variable_Vec{
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

class PFOLeptonTagging_Number{
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



class PFOLeptonTagging_Information_Single{
	public:
		PFOLeptonTagging_Observable                      obv;
		PFOLeptonTagging_Variable_Vec                    particle;
		PFOLeptonTagging_Variable  p1;
		PFOLeptonTagging_Variable  p2;
		PFOLeptonTagging_Number                          num;


		void Init(){
			obv         .Init();
			particle    .Init();
			p1          .Init();
			p2          .Init();
			num.Init();
		}


		void Get_MCsParticles ( std::vector<MCParticle*> input) ;
		void Get_PFOParticles( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);

}; 

class PFOLeptonTagging_Information{
	private:
		bool _switch_root;
	public:
		PFOLeptonTagging_Information_Single pfo_input_lepton;
		PFOLeptonTagging_Information_Single mcs_input_lepton;
		PFOLeptonTagging_Information_Single pfo_input_other;
		PFOLeptonTagging_Information_Single pfo_output_lepton;
		PFOLeptonTagging_Information_Single pfo_output_other;

		void Init(){
			_switch_root=false;
		}

		void Init(bool switch_root){
			_switch_root=switch_root;
			if(_switch_root){
				pfo_input_lepton     .Init();
				mcs_input_lepton     .Init();
				pfo_input_other      .Init();
				pfo_output_lepton    .Init();
				pfo_output_other     .Init();
			}
		}

		void Set_Switch(bool open){
			_switch_root=open;
		}


		void Fill_Data(TTree* tree){
			if(_switch_root){
				pfo_input_lepton     .Fill_Data(tree,"pfo_input_lepton");
				mcs_input_lepton     .Fill_Data(tree,"mcs_input_lepton");
				pfo_input_other      .Fill_Data(tree,"pfo_input_other");
				pfo_output_lepton    .Fill_Data(tree,"pfo_output_lepton");
				pfo_output_other     .Fill_Data(tree,"pfo_output_other");
			}
		}

}; 

class PFOLeptonTagging_Output_Collection{
	private:
		bool             Jopen;
	public:
		std::string      name;
		LCCollectionVec* col;

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
