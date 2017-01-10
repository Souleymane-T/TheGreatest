#pragma once
#include "Obstacle.hh"
#include "Joueur.hh"

class Mur: public Obstacle{
protected:
	int _width;
	int _height;
public:
	Mur(int x, int y, int size_w, int size_h);
	void collision(Joueur& J1, int& anim); /*Empêche le joueur de traverser le mur*/
	int getWidth()const{return _width;};
	int getHeight()const{return _height;};
};

