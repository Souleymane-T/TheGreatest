#pragma once
#include "Objet.hh"

class Bonus: public Objet{
private:
	int _givePV;
	float _giveSpeed;
public:
	Bonus(int x, int y, int givePV, float giveSpeed)
	:Objet(x,y),_givePV(givePV),_giveSpeed(giveSpeed){};
	void addStat(Joueur& J1);//Ajoute les stats au joueur
};