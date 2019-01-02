#ifndef EXTRA_SCALAR_LEPTON_CLASS_H
#define EXTRA_SCALAR_LEPTON_CLASS_H  
class CLEPTON_CUT{
	public:
		float electronMinEnergyDepositByMomentum;
		float electronMaxEnergyDepositByMomentum;
		float electronMinEcalToHcalFraction;
		float electronMaxEcalToHcalFraction;
		float electronMinTrackEnergy;
		float electronMaxTrackEnergy;

		float electronMinD0;
		float electronMaxD0;
		float electronMinZ0;
		float electronMaxZ0;
		float electronMinR0;
		float electronMaxR0;
		float electronMinD0Sig;
		float electronMaxD0Sig;
		float electronMinZ0Sig;
		float electronMaxZ0Sig;
		float electronMinR0Sig;
		float electronMaxR0Sig;

		float electroncosConeAngle;


		float muonMinEnergyDepositByMomentum;
		float muonMaxEnergyDepositByMomentum;
		float muonMinEcalToHcalFraction;
		float muonMaxEcalToHcalFraction;
		float muonMinTrackEnergy;
		float muonMaxTrackEnergy;
		float muonMinEyoke;
		float muonMaxEyoke;

		float muonMinD0;
		float muonMaxD0;
		float muonMinZ0;
		float muonMaxZ0;
		float muonMinR0;
		float muonMaxR0;
		float muonMinD0Sig;
		float muonMaxD0Sig;
		float muonMinZ0Sig;
		float muonMaxZ0Sig;
		float muonMinR0Sig;
		float muonMaxR0Sig;

		float cosConeAngle;

		void Read_Cut(){
			this->electronMinTrackEnergy=5.0;
			this->electronMaxTrackEnergy=100000.0;
			this->electronMinEnergyDepositByMomentum=0.5;
			this->electronMaxEnergyDepositByMomentum=1.3;
			this->electronMinEcalToHcalFraction=0.9;
			this->electronMaxEcalToHcalFraction=100000.0;

			this->muonMinTrackEnergy=5.0;
			this->muonMaxTrackEnergy=100000.0;   
			this->muonMinEnergyDepositByMomentum=0.0;
			this->muonMaxEnergyDepositByMomentum=0.3;
			this->muonMinEcalToHcalFraction=0.0;
			this->muonMaxEcalToHcalFraction=100000.0;
			this->muonMinEyoke=1.2;
			this->muonMaxEyoke=100000.0;

			this->electronMinD0=0.0;
			this->electronMaxD0=100000.0;
			this->electronMinZ0=0.0;
			this->electronMaxZ0=100000.0;
			this->electronMinR0=0.0;
			this->electronMaxR0=100000.0;
			this->electronMinD0Sig=0.0;
			this->electronMaxD0Sig=50.0;
			this->electronMinZ0Sig=0.0;
			this->electronMaxZ0Sig=5.0;
			this->electronMinR0Sig=0.0;
			this->electronMaxR0Sig=100000.0;

			this->muonMinD0=0.0;
			this->muonMaxD0=100000.0;
			this->muonMinZ0=0.0;
			this->muonMaxZ0=100000.0;
			this->muonMinR0=0.0;
			this->muonMaxR0=100000.0;
			this->muonMinD0Sig=0.0;
			this->muonMaxD0Sig=5.0;
			this->muonMinZ0Sig=0.0;
			this->muonMaxZ0Sig=5.0;
			this->muonMinR0Sig=0.0;
			this->muonMaxR0Sig=100000.0;

			this->cosConeAngle=0.98;
		}

		CLEPTON_CUT(){
			Read_Cut();
		}
};




#endif
