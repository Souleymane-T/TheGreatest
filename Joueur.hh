#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include "Obstacle.hh"
class Obstacle;
class Joueur{

private:
    sf::Texture Trump;
	sf::Sprite Trump_sprite;
	sf::FloatRect Trump_rect;
	int _PV;
	float _Speed;
	int _Score;
	static const int _MaxPDV;
	static const float _MaxSpeed;
	static const int _width;
	static const int _height;
	std::map<std::string,int> Recap;//Map permettant d'avoir le recapitulatif du score: nb de bulletins, bonus, malus

public:
	Joueur();

	float getSpeed()const{return _Speed;};
	int getPV()const{return _PV;};
	int getScore()const{return _Score;};

	void setSpeed(float speed){_Speed = speed;};

	void addSpeed(float speed);
	void addScore(int score){_Score += score;};
	void addPV(int PV);
	void addRecap(std::string s){Recap[s]++;};//Incremente les nombres bulletins/bonus/malus
	sf::FloatRect& getRect(){return Trump_rect;};
	sf::Sprite& getSprite(){return Trump_sprite;};

	void updateORect(){Trump_rect = Trump_sprite.getGlobalBounds();};

	std::map<std::string,int> getResult()const{return Recap;};
	int getWidth()const{return _width;};
	int getHeight()const{return _height;};
};
