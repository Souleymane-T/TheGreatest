#ifndef DEF_OBSTACLE
#define DEF_OBSTACLE

/*#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>*/
#include <iostream>
#include "Joueur.hh"
class Joueur;
class Obstacle
{
	/*Caracteristiques necessaires pour l'affichage
	Textûre pour l'image
	Rectangle pour les contours reels de l'objet
	sprite qui permet de mettre la texture sur la fenetre avec d'autres caracteristiques comme
	la couleur ou la position*/
	protected:
		sf::FloatRect o_rect;
		sf::Texture o_text;
		sf::Sprite o_sprite;
		int _x, _y;

	public:
		Obstacle(){};
		Obstacle(int x, int y);
		sf::Sprite& getSprite(){return o_sprite;};
		sf::FloatRect& getRect(){return o_rect;};
        void updateORect(){o_rect = o_sprite.getGlobalBounds();};//Met a jour la position de l'obstacle

		virtual ~Obstacle(){};
		virtual void collision(Joueur&, int&) = 0;//Classe virtuelle qui gere la collision avec le joueur
};
#endif //DEF_OBSTACLE


