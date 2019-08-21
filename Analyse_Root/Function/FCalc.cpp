#include "FCalc.h"
float Get_Significance(float sig, float bkg){
	float significance =sig/std::sqrt(sig+bkg);
	return(significance);
}

float Get_Efficiency(float current, float origin){
	float effi=current/(current+origin);
	return(effi);
}
