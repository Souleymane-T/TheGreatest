#pragma once
#include "Mur.hh"
#include <SFML/Window.hpp>
class Bois: public Mur{
private:
	int _resistance;
public:
	Bois(int x, int y, int size_w, int size_h , int resistance);
	void collision(Joueur& J1, int& anim);//Gestion des collisions avec le joueur
};
