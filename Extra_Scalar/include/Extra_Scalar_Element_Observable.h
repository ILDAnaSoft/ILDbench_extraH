#ifndef Extra_Scalar_ELEMENT_DATATYPE_H
#define Extra_Scalar_ELEMENT_DATATYPE_H  
#include "Extra_Scalar_Lepton_Class.h"
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

#include <IMPL/LCCollectionVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>

using ToolSet::operator<<;
using ToolSet::operator+;
using ToolSet::operator-;
using ToolSet::operator+=;


class Extra_Scalar_Global_Counter{
	// init once,  record global information for all events
	public:
		float nevt                     ;
		float nrun                     ;
		float gweight                  ;
		float pass_MCs                 ;
		float pass_PFO                 ;
		float pass_PFO_MC_Cheating_Muon;
		float pass_PFO_MC_Cheating_ISR ;
		float pass_all                 ;

		void Init(){
			nevt                       = 0;
			nrun                       = 0;
			gweight                    = 0;
	        pass_MCs                   = 0;
	        pass_PFO                   = 0;
	        pass_PFO_MC_Cheating_Muon  = 0;
	        pass_PFO_MC_Cheating_ISR   = 0;
	        pass_all                   = 0;
		}

		void Print(){
			std::cout << "In the Global Event Counter, Till now, there are totally " << nevt << " events and within " << nrun <<" runs " << " the global scale weight is " << gweight << std::endl; 
			std::cout << "There are " << pass_MCs << " events pass MCs;" << std::endl;
			std::cout << "      and " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "      and " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << "      and " << pass_PFO_MC_Cheating_Muon << " events pass PFO with cheated muon;" << std::endl;
			std::cout << "      and " << pass_PFO_MC_Cheating_ISR  << " events pass PFO with cheated ISR ;" << std::endl;
			std::cout << "  totally " << pass_all << " events pass all criterion." << std::endl; 
		}


		void Fill_Data(TTree* tree);
};



class Extra_Scalar_Single_Counter{
	// init and record information for each event
	public:
		float evt                      ;
		float run                      ;
		float weight                   ;
		float pass_MCs                 ;
		float pass_PFO                 ;
		float pass_PFO_MC_Cheating_Muon;
		float pass_PFO_MC_Cheating_ISR ;
		float pass_all                 ;

		void Init(){
			evt                        = 0;
			run                        = 0;
			weight                     = 0;
	        pass_MCs                   = 0;
	        pass_PFO                   = 0;
	        pass_PFO_MC_Cheating_Muon  = 0;
	        pass_PFO_MC_Cheating_ISR   = 0;
			pass_all                   = 0;
		}

		void Print(){
			std::cout << "In the Single Event Counter, this is the " << evt << "th event, in the " << run << "th run." << std::endl;
			std::cout << " and " << pass_MCs << " events pass MC; " << std::endl;
			std::cout << " and " << pass_PFO << " events pass PFO;" << std::endl;
			std::cout << " and " << pass_PFO_MC_Cheating_Muon << " events pass_PFO_MC_Cheating_Muon;" << std::endl;
		    std::cout << " and " << pass_PFO_MC_Cheating_ISR  << " events pass_PFO_MC_Cheating_ISR; " << std::endl;
			std::cout << "in this event it has " << pass_all << " pass all criterion." << std::endl; 
		}

		void Fill_Data(TTree* tree);
};



class Extra_Scalar_Function_Counter{
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

class Extra_Scalar_Counter{
	public:
		Extra_Scalar_Function_Counter MCs;
		Extra_Scalar_Function_Counter PFO;
		Extra_Scalar_Function_Counter PFO_MC_Cheating_Muon;
		Extra_Scalar_Function_Counter PFO_MC_Cheating_ISR;

		void Init(){
	        MCs.Init();
	        PFO.Init();
	        PFO_MC_Cheating_Muon.Init();
	        PFO_MC_Cheating_ISR.Init();
		}

		void Fill_Data(TTree* tree){
			MCs                 .Fill_Data(tree,"MCs");
			PFO                 .Fill_Data(tree,"PFO");
			PFO_MC_Cheating_Muon.Fill_Data(tree,"PFO_MC_Cheating_Muon");
			PFO_MC_Cheating_ISR .Fill_Data(tree,"PFO_MC_Cheating_ISR");
		}
};


class Extra_Scalar_Observable{
	public:
		//************************
		//inserted by process file
		//************************
		float  kcut_zmass                 ;
		float  kcut_zpt                   ;
		float  kcut_invis_costheta        ;
		float  kcut_invis_e               ;
		float  kcut_recoil_mass           ;
		float  kcut_vis_e                 ;
		float  kcut_vis_all_e             ;

		float  lep_pair_costheta          ;
		float  lep_pair_costheta_pair     ;
		float  lep_pair_azimuth           ;
		float  lep_pair_azimuth_pair      ;

		float  opal_lep_isolation1        ;        
		float  opal_lep_isolation2        ;        
		float  opal_zmass                 ;        
		float  opal_lep_pair_pz           ;        
		float  opal_invis_momentum        ;        
		float  opal_invis_costheta        ;        
		float  opal_lep_pair_acoplanarity ;        

		void Init(){
			kcut_zmass                =-10000.1;
			kcut_zpt                  =-10000.1;
			kcut_invis_costheta       =-10000.1;
			kcut_invis_e              =-10000.1;
			kcut_recoil_mass          =-10000.1;
			kcut_vis_e                =-10000.1;
			kcut_vis_all_e            =-10000.1;

			lep_pair_costheta         =-10000.1;
			lep_pair_costheta_pair    =-10000.1;
			lep_pair_azimuth          =-10000.1;
			lep_pair_azimuth_pair     =-10000.1;

		    opal_lep_isolation1       =-10000.1;       
		    opal_lep_isolation2       =-10000.1;       
		    opal_zmass                =-10000.1;       
		    opal_lep_pair_pz          =-10000.1;       
		    opal_invis_momentum       =-10000.1;       
		    opal_invis_costheta       =-10000.1;       
		    opal_lep_pair_acoplanarity=-10000.1;       
		}

		void Fill_Data(TTree* tree, std::string prefix);
};


//Stored data 
class Extra_Scalar_Variable{
	public:
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

		void Get_MCsParticle_Information( MCParticle* input) ;
		void Get_PFOParticle_Information( ReconstructedParticle* input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};

class Extra_Scalar_Variable_Vec{
	public:
		//************************
		//inserted by process file
		//************************
		std::vector<float> pdg       ;        
		std::vector<float> p         ;        
		std::vector<float> pt        ;        
		std::vector<float> costheta  ;       
		std::vector<float> phi       ;        
		std::vector<float> e         ;        
		std::vector<float> mass      ;        
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

		void Get_MCsParticles_Information( std::vector<MCParticle*> input) ;
		void Get_PFOParticles_Information( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix);
};


class Extra_Scalar_Number{
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

		void Fill_Data(TTree* tree, std::string prefix);
};


class Extra_Scalar_Information_Single{
	public:
		Extra_Scalar_Observable                      obv;

		Extra_Scalar_Variable                        vari_muon_plus;

		Extra_Scalar_Variable                        vari_muon_minus;

		Extra_Scalar_Variable                        vari_photon_central;

		Extra_Scalar_Variable                        vari_photon_forward;

		Extra_Scalar_Number                          num_muon  ;

		Extra_Scalar_Number                          num_photon;

		Extra_Scalar_Number                          num_PFO   ;

		Extra_Scalar_Number                          num_MCs   ;

		void Init(){
			obv        .Init();
			vari_muon_plus .Init();
			vari_muon_minus.Init();
			vari_photon_central.Init();
			vari_photon_forward.Init();
			num_muon   .Init();
			num_photon .Init();
			num_PFO    .Init();
			num_MCs    .Init();
		}

		void Get_MCParticles ( std::vector<MCParticle*> input) ;
		void Get_PFOParticles( std::vector<ReconstructedParticle*> input) ;
		void Fill_Data(TTree* tree, std::string prefix){
			obv        .Fill_Data(tree,prefix+"_obv"        );
			vari_muon_plus  .Fill_Data(tree,prefix+"_vari_muon_plus"  );
			vari_muon_minus .Fill_Data(tree,prefix+"_vari_muon_minus"  );
			vari_photon_central.Fill_Data(tree,prefix+"_vari_photon_central");
			vari_photon_forward.Fill_Data(tree,prefix+"_vari_photon_forward");
			num_muon   .Fill_Data(tree,prefix+"_num_muon"   );
			num_photon .Fill_Data(tree,prefix+"_num_photon" );
			num_PFO    .Fill_Data(tree,prefix+"_num_PFO"    );
			num_MCs    .Fill_Data(tree,prefix+"_num_MCs"    );
		} 

}; 

class Extra_Scalar_Information{
	public:
		Extra_Scalar_Information_Single               hs;
		Extra_Scalar_Information_Single               py;
		Extra_Scalar_Information_Single               de;
		Extra_Scalar_Information_Single               po;
		Extra_Scalar_Information_Single               po_wo_overlay;
		Extra_Scalar_Information_Single               po_cmuon;
		Extra_Scalar_Information_Single               po_cisr;

		void Init(){
			hs           .Init();
			py           .Init();
			de           .Init();
			po           .Init();
			po_wo_overlay.Init();
			po_cmuon     .Init();
			po_cisr      .Init();
		}


		void Fill_Data(TTree* tree){
			hs           .Fill_Data(tree,"hs"           );
			py           .Fill_Data(tree,"py"           );
			de           .Fill_Data(tree,"de"           );
			po           .Fill_Data(tree,"po"           );
			po_wo_overlay.Fill_Data(tree,"po_wo_overlay");
			po_cmuon     .Fill_Data(tree,"po_cmuon"     );
			po_cisr      .Fill_Data(tree,"po_isr"       );
		}

}; 

class Extra_Scalar_Output_Collection{
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
