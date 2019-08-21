#pragma once
#ifndef AFILE_H
#define AFILE_H
#include <string> 
#include <vector> 
#include <iostream>
#include "Class/DrawClass.h"
#include "Function/Ffile.h"
#include "Analyse/Make_Table.h"
class AFile_Name{
	private:
	public:
		std::string                 name      ;
		std::string                 latex     ;

		std::vector<std::string>	basic_file;
		std::vector<float>          xection   ;

		std::string             	Unpol_file;
		std::string             	MVA_file  ;
		std::string                 CUT_file  ;
		std::string                 ana_data  ;
		std::string                 ana_Unpol ;

		void Clear(){
			name      = ""    ;
			latex     = ""    ;
			basic_file.clear();
			xection   .clear();
			MVA_file  = ""    ;
			CUT_file  = ""    ;
			ana_data  = ""    ;
		}

		int Num(){
			return(basic_file.size());
		}
};

class AFile{
	private:
		std::string _property;
	public:
		std::vector<AFile_Name>  input       ;
		ASort_List               input_sort  ;
		std::vector<AFile_Name>  output      ;
		ASort_List               output_sort ;
		AFile_Name               output_total;
		std::vector<std::string> folder      ;
		//folder order
        //The data_folder:"             
        //The plot_folder_name:"        
        //The plot_combine_folder_name:"
        //The event_Unpol_folder:"      
        //The event_MVA_folder:"        
        //The event_CUT_folder:"        
        //The plot_summary horizontaly:"        
        //The plot_in_sensitivity:"        
		std::string              significance   ;
		std::string              output_table   ;
		std::string              efficiency_plot;
		std::string              reweight_table ;
		std::string              sensitivity    ;
		std::string              output_MVA     ;
		std::string              dataset_MVA    ;

		void Set_Property(std::string input_property);

		int Input_Num(){
			return(input.size());
		}

		int Output_Num(){
			return(output.size());
		}

		std::string  Get_Output_Unpol_File(std::string input_file_name);
		std::vector<std::string> Get_Output_Unpol_Files(std::vector<std::string> input_file_name);
		std::vector<std::string> Get_Output_Unpol_Files();
		/**
		 * @brief Get_Output_MVA_File 
		 *
		 * @param input_file_name : file short name
		 *
		 * @return 
		 */
		std::string  Get_Output_MVA_File(std::string input_file_name);
		std::vector<std::string> Get_Output_MVA_Files(std::vector<std::string> input_file_name);
		std::vector<std::string> Get_Output_MVA_Files();

		void Clear();
};


std::ostream & operator<<(std::ostream & ostr, AFile &file_name);

std::string change_name(std::string arg_string);
void get_file_name(CDraw &para, AFile &file_name);
#endif



