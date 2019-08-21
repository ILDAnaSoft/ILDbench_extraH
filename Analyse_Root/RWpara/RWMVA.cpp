#include "Class/MVA.h"
void CMVA:: Read_MVA(CPath &path, CFlow &flow){
	ShowMessage(3, "read MVA");
	YAML::Node MVA_node = YAML::LoadFile(path.MVA_file);
	ShowMessage(1);

	YAML::Node nodes = MVA_node["MVA"];
	for(YAML::const_iterator it=nodes.begin(); it != nodes.end(); ++it){
		ShowMessage(3, "MVA methods",it->first.as<std::string>());
		this->mva.push_back(it->second.as<CMVA_Basic>());
	}

	this->default_mva= this->mva[0];
};

