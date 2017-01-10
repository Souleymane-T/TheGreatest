#pragma once
#include "Obstacle.hh"

class Objet: public Obstacle{
public:
	Objet(int x, int y);
	void collision(Joueur& J1, int&);
	virtual void addStat(Joueur& J1) = 0;//Fonction virtuelle qui permettra d'ajouter/retirer de la vie/vitesse au joueur
};

