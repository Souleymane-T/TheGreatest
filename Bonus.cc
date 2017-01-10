#include "Bonus.hh"

void Bonus::addStat(Joueur& J1){
		J1.addPV(_givePV);
		J1.addSpeed(_giveSpeed);
		J1.addRecap("Bonus");
	
}
