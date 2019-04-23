#include "Extra_Scalar.h"

bool Extra_Scalar::POCutMuon( std::vector<ReconstructedParticle*> &muon, Extra_Scalar_Number& num, Extra_Scalar_Variable& vari1, Extra_Scalar_Variable& vari2) {
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

	vari1.Get_PFOParticle_Information(muonplus[0]);
	vari2.Get_PFOParticle_Information(muonminus[0]);

	return(true);
}

void Extra_Scalar::POCutMuonPair( std::vector<ReconstructedParticle*> &muon, Extra_Scalar_Observable& obv) {
	EVENT::Track* lep1=0,  *lep2=0; 
	EVENT::TrackVec trkvec1 = muon[0]->getTracks();
	EVENT::TrackVec trkvec2 = muon[1]->getTracks();

	if((trkvec1.size()>0)&&(trkvec2.size()>0)){
		lep1=trkvec1[0];
		lep2=trkvec2[0];

		VertexInfo vv;
		vv.addTrack( lep1 );
		vv.addTrack( lep2 );
		//beam spot constraint
		float xyz[3] = { 150e-6, 5e-6, 0.2  }; //mm
		vv.setBeamSpotSize( xyz  );
		vv.useIPcon( true  );

		TVector3 vtxPos = vv.getVertexPosition();
		float vtx = vtxPos[0];
		float vty = vtxPos[1];
		float vtz = vtxPos[2];
		float chi2 = vv.getVertexChisq();
		obv.Get_Vertex_Information(vv);
	}
}


void Extra_Scalar::POCutPhoton(std::vector<ReconstructedParticle*> &photon, Extra_Scalar_Number &num, Extra_Scalar_Variable& vari_cen, Extra_Scalar_Variable& vari_for){
	std::vector<ReconstructedParticle*> photon_cen;
	std::vector<ReconstructedParticle*> photon_for;
	int pnum_cen=0;
	int pnum_for=0;
	std::stable_sort(photon.begin(),photon.end(),ToolSet::CRC::Compare_as_E);
	for(unsigned int i=0;i<photon.size();i++){
		float angle  = std::abs(ToolSet::CMC::Cal_CosTheta(photon[i]));
		if(angle<0.95){
			pnum_cen++;
			photon_cen.push_back(photon[i]);
		}
		else{
			pnum_for ++;
			photon_for.push_back(photon[i]);
		}
	}
	num.num_central= pnum_cen;
	num.num_forward= pnum_for;
	num.num        = pnum_cen+pnum_for;
	if(pnum_cen>0){
		vari_cen.Get_PFOParticle_Information(photon_cen[0]);
	}
	if(pnum_for>0){
		vari_for.Get_PFOParticle_Information(photon_for[0]);
	}
}
