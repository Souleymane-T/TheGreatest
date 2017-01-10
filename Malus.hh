#pragma once
#include "Objet.hh"

class Malus: public Objet{
private:
	int _givePV;
	float _giveSpeed;
public:
	Malus(int x, int y, int givePV, float giveSpeed)
	:Objet(x,y),_givePV(givePV),_giveSpeed(giveSpeed){};
	void addStat(Joueur& J1);//Ajoute des malus au joueur
};