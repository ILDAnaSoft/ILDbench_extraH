#include "TFile.h"


void test_corrupted_file(std::vector<std::string> input_file){

	int num=input_file.size();
	for(int i=0;i<num;i++){
	    TFile myfile(input_file[i].c_str());
	    if (myfile.IsZombie()) {
	    	//something very wrong, cannot use this file, exit
	    	std::cout << "The file is wrong: " << input_file[i] << std::endl;
			if(myfile.TestBit(TFile::kRecovered)) {
				//the Recover procedure has been run when opening the file
				//    //and the Recover was successful
				//std::cout << "     The file is recovered: " << input_file[i] << std::endl;
			} 
			else {
				std::cout << "     The file can't be recovered: " << input_file[i] << std::endl;
			}
	    }
	}
}
