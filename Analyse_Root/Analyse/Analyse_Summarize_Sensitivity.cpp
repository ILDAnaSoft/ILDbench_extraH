#include "Analyse_Summarize_Sensitivity.h"


void Analyse_Summarize_Sensitivity_Pre(CDraw &para){

	std::vector<std::string> sig_name;
	for(int i=0;i<para.signal_scan.property_num;i++){
		std::string signal_property=para.signal_scan.properties[i];
		std::string combined_file= para.default_path.output_file+"/"+signal_property+"/data_combine_"+signal_property+".dat";
		if(Is_File_Exist(combined_file)){
			sig_name.push_back(combined_file);
		}
    }

  	Analyse_Summarize_Sensitivity(para,sig_name);
	Analyse_Get_Exclusion_Limits(para);
}


void Analyse_Summarize_Sensitivity(CDraw& para,std::vector<std::string> &sig_name){

	ShowMessage(2,"Summarize sensitivity");
	std::vector<float> sen_vec;
	std::ofstream out_file;
	std::string out_file_path=para.path.output_file+"/combined_sensitivity.dat";
	ShowMessage(2,"output combined sensitivity file is ",out_file_path);
	out_file.open(out_file_path);
	out_file <<   "summarized_sensitivity :" << std::endl;
	for(unsigned int i=0;i<sig_name.size();i++){
		std::ifstream myfile;
		myfile.open(sig_name[i]);
		ShowMessage(2,"open file",sig_name[i]);
		TextQuery tq(myfile);
		QueryResult qr=tq.query("Lambda");
		std::vector<std::string> input_line=qr.Get_Lines_Content();
//  	for(unsigned int j=0;j<input_line.size();j++){
//  		int pos=input_line[j].find("Lambda out");
//  		std::string output_line=input_line[j].replace(pos,pos+10,Float_to_String(para.mass_scan.mass[i]));
//  		out_file <<   "    " << output_line << std::endl;
//  	}
    		int pos=input_line[input_line.size()-1].find("Lambda out");
    		std::string output_line=input_line[input_line.size()-1].replace(pos,pos+13,para.signal_scan.properties[i]+" :");
    		out_file <<   "    " << output_line << std::endl;
		myfile.close();
	}
	out_file.close();
	ShowMessage(2,"finished sumarize sensitivity");
}


void Analyse_Get_Exclusion_Limits(CDraw& para){
	ShowMessage(3, "read  Summarize sensitivity");
	std::string in_file_path=para.path.output_file+"/combined_sensitivity.dat";
	YAML::Node node = YAML::LoadFile(in_file_path);
	std::vector<float> input_exclusion_mass;
	for(int i=0;i<para.signal_scan.property_num;i++){
		std::string label=para.signal_scan.properties[i];
		input_exclusion_mass.push_back(0);
		RW_element(label  ,node["summarized_sensitivity"],input_exclusion_mass[i]);
		input_exclusion_mass[i]=std::pow(91.2/input_exclusion_mass[i],2);
	}
	std::ofstream out_file;
	std::string out_file_path=para.path.output_file+"/combined_exclusion_limits.dat";
	ShowMessage(2,"output exclusion limits file is ",out_file_path);
	out_file.open(out_file_path);
	for(int i=0;i<para.signal_scan.property_num;i++){
		out_file << "xILC["<<i<<"]= "<<para.signal_scan.properties[i] << " ;\n" ;
		out_file << "yILC["<<i<<"]= "<<input_exclusion_mass[i] << " ;\n" ;
	}
	out_file.close();
}
