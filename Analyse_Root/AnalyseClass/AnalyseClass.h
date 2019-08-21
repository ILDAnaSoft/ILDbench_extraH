#pragma once
#ifndef ANALYSE_CLASS
#define ANALYSE_CLASS
#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitter.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TH3.h"
#include "THStack.h"
#include "TImage.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TMath.h"
#include "TMatrix.h"
#include "TMatrixT.h"


#include "AnalyseClass/Variable.h"
#include "AnalyseClass/Cut.h"
#include "AnalyseClass/File.h"
#include "AnalyseClass/Plot.h"
#include "Analyse/Abasic.h"
#include "Function/Fbasic.h"
class Analyse_Figure{
	private:
		bool        _plot_switch;
	public:
		TH1F*       hvariable_origin;
		TH1F*       hvariable_before;
		TH1F*       hvariable_after ;
		TH1F*       hvariable_final ;

		double      pass            ;

		~Analyse_Figure(){
			Clear();
		}

		void Init(Avariable &info, std::string name);

		void Init();

		void Clear();

		void Plot(float &variable, TH1F* &hvariable,double weight);
		void Plot_Origin(float &variable, double weight);
		void Plot_Before(float &variable, double weight);
		void Plot_After(float &variable, double weight);
		void Plot_Final(float &variable, double weight);
		void Set_Pass(double weight);
		void Add_Pass(double weight);
};



class Analyse_Single_File{
	private:
	float               	     _lumi      ;
	int							 _var_num   ; 
	std::vector<float>           _rootvar   ; 


	int							 _tree_num  ; 
	std::vector<TTree*>          _tree      ; 

	double                        _out_weight; 
	double                        _extra_weight ; 

	int							 _figure_num; 

	bool                         _record_switch;
	bool                         _plot_switch  ;
	std::string                  _plot_object;

	public:
	std::string                  _name      ;
	TFile*                       _root_file ; 

		std::vector<Analyse_Figure>  _figure ; 
		double                        in_weight ; 


		Analyse_Single_File()               ; 

		~Analyse_Single_File()              ; 

		void Init             (AVariable &var, TFile *plot_file, double extra_weight, bool record_switch, bool plot_switch,std::string plot_object, std::string figure_name, std::string file_name, std::vector<std::string> tree_name);

		void Clear()                        ;

		void Root_Init();
		void Root_Init_Var      (); 
		void Root_Endow_Weight  (); 
		void Root_Endow_Var     (AVariable &var); 
		void Root_Endow_Var     (std::vector<float> input_rootvar); 
		void Root_Endow_Unused_Var(AVariable &var, ACut &cut); 
		void Root_Fill          (int rootnum); 
		void Root_Close_Tree    (int rootnum); 
		void Root_Close_File    (); 

		void Plot_Origin        ( AVariable &var) ;
		void Plot_Final         ( AVariable &var) ;

		void Add_Pass_NoCut     ( ) ;
		void Add_Pass_AllCut    ( ) ;

		bool Get_Cut            ( AVariable &var,ACut &cut                                                      ) ;
		bool Use_Cut            ( Avariable &var, AVariable &Var, double weight, Analyse_Figure &figure                          ) ;
		bool Loop_Cut           ( AVariable &var, std::vector<Analyse_Figure> & figure, double weight, ACut &cut ) ;

		void Record_Information ( std::ofstream &myfile, AVariable& var, ACut &cut, std::string sample_name     ) ;




		/*****************************************************************************************
		 * private vairable 
		 *****************************************************************************************/
		std::vector<float> RootVar(){
			return(_rootvar);
		}
};


class Analyse_Multi_File : public APlot{
	private:
		int									   _var_num         ;

		int									   _file_num        ;

		TFile*								   _root_file       ; 
		TList*                                 _list;

		bool                                   _record_switch   ;
		bool                                   _plot_switch     ;
		std::string                            _plot_object     ;

		ACut                                   _cut             ;

		double                                  _extra_weight    ; 

		Analyse_Single_File*                   _which_sort      ;
		void                                   _Find_Which_Sort (CDraw &para, AFile &file_name, int filenum ) ;

		bool                                   _Has_Drawn       ;
	public:
		AVariable                              var              ;
		std::vector<Analyse_Single_File>       file             ;
		std::vector< std::pair<std::string,std::vector<Analyse_Single_File > > > sort;


		int Var_Num();


		Analyse_Multi_File(CDraw &para, AFile &file_name){
			Init(para,file_name);
		}

		~Analyse_Multi_File(){
			Clear();
		}


		void Init_Color();
		void Init                   ( CDraw &para, AFile &file_name                              ) ;
		void Clear                  ();
		void Root_Init              ( CDraw &para, AFile &file_name, int filenum);
		void Root_Init_Var          ( int filenum); 
		void Root_Endow_Var         ( int filenum);
		void Root_Endow_Weight      ( int filenum);
		void Root_Fill              ( int filenum                                                ) ;
		void Root_Close             ( int filenum                                                ) ;
		void Root_Close_Last        ( CDraw &para) ;

		void Plot_Origin            ( int filenum) ;
		void Plot_Final             ( int filenum) ;

		void Add_Pass_NoCut         ( int filenum) ;
		void Add_Pass_AllCut        ( int filenum) ;
		void Add_Tot_Pass           ( int filenum                                                ) ;

		bool Get_Cut                ( int filenum) ;

		void Record_Information     ( int filenum,std::ofstream &myfile, std::string sample_name ) ;
		void Record_Tot_Information ( std::ofstream &myfile, std::string sample_name             ) ;

		void Draw_Origin            ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_Before            ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_After             ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_Final             ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_Sort_Origin       ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_Sort_Before       ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_Sort_After        ( CDraw& para,AFile& file_name                                           ) ;
		void Draw_Sort_Final        ( CDraw& para,AFile& file_name                                           ) ;

		void Fill_Figure            ( );

		void Draw_Figure            ( CDraw& para,AFile& file_name                               ) ;
};
#endif
