#include "Extra_Scalar.h"

bool Extra_Scalar::POCutMuon( std::vector<ReconstructedParticle*> &muon, Extra_Scalar_Number& num, Extra_Scalar_Variable_Vec& vari) {
	std::vector<ReconstructedParticle*> muonplus =ToolSet::CRC::Get_POParticleType(muon, 13);
	std::vector<ReconstructedParticle*> muonminus=ToolSet::CRC::Get_POParticleType(muon,-13);
	int numt = muon.size();
	int nump = muonplus .size();
	int numm = muonminus.size();
	num.num       =numt;
	num.num_plus  =nump;
	num.num_minus =numm;
	if(numt<2) {
		return(false);
	}
	if(nump<1) {
		return(false);
	}
	if(numm<1) {
		return(false);
	}
	return(true);
}

void Extra_Scalar::POCutPhoton(std::vector<ReconstructedParticle*> &photon, Extra_Scalar_Number &num, Extra_Scalar_Variable_Vec& vari){
	vari.Get_PFOParticles_Information(photon);
	int pnum_cen=0;
	int pnum_for=0;
	std::stable_sort(photon.begin(),photon.end(),ToolSet::CRC::Compare_as_E);
	vari.Get_PFOParticles_Information(photon);
	for(unsigned int i=0;i<photon.size();i++){
		float angle  = std::abs(ToolSet::CMC::Cal_CosTheta(photon[i]));
		if(angle<0.95){
			pnum_cen++;
		}
		else{
			pnum_for ++;
		}
	}
	num.num_central= pnum_cen;
	num.num_forward= pnum_for;
	num.num        = pnum_cen+pnum_for;
}
