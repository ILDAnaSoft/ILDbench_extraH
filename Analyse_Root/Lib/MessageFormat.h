#pragma once
#ifndef MESSAGEFORMAT_H
#define MESSAGEFORMAT_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string> 
#include <iomanip> 

#include "TH1.h"
#include "TMath.h"
#include "TLine.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "Function/Fvector.h"

std::ostream& Choose_Print_File(bool IsRecord, std::string file_name);

void RecordMessage(std::ofstream &file_name, int level);


template <typename TMess1> 
void RecordMessage(std::ofstream &file_name, int level, TMess1 mess){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;
	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

	file_name << fill << mess  << "\n";
	std::cout << fill << mess  << std::endl;
}


template <typename TMess1, typename TMess2> 
void RecordMessage(std::ofstream &file_name, int level, TMess1 mess, TMess2 ddata){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;
	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

	file_name << fill << std::left << std::setw(66-fillnum) << mess  << std::setfill(' ') << ":    " << ddata << "\n";
	std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << std::endl;
}




template <typename TMess1, typename TMess2,typename TMess3> 
void RecordMessage(std::ofstream &file_name, int level, TMess1 mess, TMess2 ddata, TMess3 ddata3){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;
	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

	file_name << fill << std::left << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata3 <<  "\n";
	std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata3 <<  std::endl;
}




template <typename TMess1, typename TMess2,typename TMess3, typename TMess4> 
void RecordMessage(std::ofstream &file_name, int level, TMess1 mess, TMess2 ddata, TMess3 ddata3, TMess4 ddata4){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;
	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

	file_name << fill << std::left << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata3 << ", " << ddata4 <<  "\n";
	std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata3 << ", " << ddata4 <<  std::endl;
}




template <typename TMess1, typename TMess2,typename TMess3, typename TMess4, typename TMess5> 
void RecordMessage(std::ofstream &file_name, int level, TMess1 mess, TMess2 ddata, TMess3 ddata3, TMess4 ddata4, TMess5 ddata5){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;
	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

	file_name << fill << std::left << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata3 << ", " << ddata4 << ", " << ddata5 << "\n";
	std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata3 << ", " << ddata4 << ", " << ddata5 << std::endl;
}










	template <class TMess_single>
		void ShowMessage_single(TMess_single t){
			std::cout << t << " "; 
		}	

	template <typename TMess1, typename... TMess2> 
		void ShowMessage(Int_t level, TMess1 mess, TMess2... ddata){
			std::cout.setf(std::ios::left);
			std::string fill_inc="     ";
			std::string fill="";

			int  fillnum_inc=5;
			int  fillnum=0;
			for(int i=0;i<level;i++){
				fill+=fill_inc;
				fillnum+=fillnum_inc;
			}

			std::cout << fill << std::setw(65-fillnum) << std::setfill(' ') << mess  << ":    " ;
			int arr[]={(ShowMessage_single(ddata),0)...};
			(void)arr;
			std::cout << std::endl;
		}



/*
template <typename TMess1, typename TMess2,typename TMess3, typename TMess4, typename TMess5> 
void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata, TMess3 ddata_comm, TMess4 ddata4, TMess5 ddata5){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;

	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

		std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata_comm << ", " << ddata4 << ", " << ddata5 << std::endl;
}



template <typename TMess1, typename TMess2,typename TMess3, typename TMess4> 
void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata, TMess3 ddata_comm, TMess4 ddata4){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;

	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

		std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata_comm << ", " << ddata4 << std::endl;
}




template <typename TMess1, typename TMess2,typename TMess3> 
void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata, TMess3 ddata_comm){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;

	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

		std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << ", " << ddata_comm << std::endl;
}


template <typename TMess1, typename TMess2> 
void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata){
	std::cout.setf(std::ios::left);
	std::string fill1="";
	std::string fill2="      ";
	std::string fill3="            ";
	std::string fill4="                  ";
	std::string fill5="                        ";
	std::string fill6="                              ";
	std::string fill;

	int  fillnum1=0;
	int  fillnum2=6;
	int  fillnum3=12;
	int  fillnum4=18;
	int  fillnum5=24;
	int  fillnum6=30;
	int  fillnum;

	switch(level){
		case 1:fill=fill1;fillnum=fillnum1;break;
		case 2:fill=fill2;fillnum=fillnum2;break;
		case 3:fill=fill3;fillnum=fillnum3;break;
		case 4:fill=fill4;fillnum=fillnum4;break;
		case 5:fill=fill5;fillnum=fillnum5;break;
		case 6:fill=fill6;fillnum=fillnum6;break;
		default:fill=fill1;
	}

		std::cout << fill << std::setw(66-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << std::endl;
}

*/



void ShowMessage (Int_t level, std::string mess);
void ShowMessage (Int_t level);
void ShowMessage ();

#endif