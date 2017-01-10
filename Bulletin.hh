#pragma once
#include "Objet.hh"

class Bulletin: public Objet{
private:
	int _giveScore;
public:
	Bulletin(int x, int y, int giveScore);
	void addStat(Joueur& J1);//Ajoute des points au joueur
	void collision(Joueur& J1, int& special);

};
