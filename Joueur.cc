#include "Joueur.hh"


const int Joueur::_MaxPDV = 150;
const float Joueur::_MaxSpeed = 3.0;
/*Taille du sprite du joueur*/
const int Joueur::_width = 33;
const int Joueur::_height = 46;

Joueur::Joueur(){

	if(!Trump.loadFromFile("img/Trump.png")){
		std::cout << "Probleme de chargement" << std::endl;
	}
	Trump.setSmooth(true);
	Trump_sprite.setTexture(Trump);
	Trump_sprite.setPosition(sf::Vector2f(210,200));
	Trump_rect = Trump_sprite.getGlobalBounds();

	_PV =100; _Speed = 1.5; _Score = 0;
}

void Joueur::addPV(int PV){
	_PV += PV;
	if(_PV > _MaxPDV)
		_PV = _MaxPDV;
	else if(_PV < 0){
		_PV = 0;
	}
}

void Joueur::addSpeed(float speed){
	_Speed += speed;
	if(_Speed > _MaxSpeed)
		_Speed = _MaxSpeed;
};



