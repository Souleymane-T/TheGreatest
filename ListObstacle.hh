#pragma once
#include "Obstacle.hh"
#include "Bonus.hh"
#include "Malus.hh"
#include "Bois.hh"
#include "Mur.hh"
#include "Bulletin.hh"
#include <vector>
enum Difficulte{FACILE,NORMAL,DIFFICILE, BOSS};

class ListObstacle{

private:
	std::vector<Obstacle*> _ListObstacle;
	Difficulte _niveau;
	static const int X[];
	static const int Y[];
	static const int nbMur;

public:
	ListObstacle(Difficulte);
	ListObstacle(){};
	~ListObstacle();
	void update(Joueur&, int&);
	void updateBoss(Joueur&, int&);
    Difficulte getDifficulte()const{return _niveau;};
    ListObstacle& operator=(const Difficulte& niveau);
    std::vector<Obstacle*>& getListObstacle(){return _ListObstacle;};
    Obstacle& operator[](int k){return *_ListObstacle[k];};
private:
	void addObj(int nbBonus, int nbMalus);
	void addMur();
	void addCroix();
	void addGdCour(int refhaut, int refbass,int somme, int nb);
};


