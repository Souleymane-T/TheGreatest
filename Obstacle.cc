#include "Obstacle.hh"

Obstacle::Obstacle(int x, int y){
	_x = x; _y = y;
	if(!o_text.loadFromFile("img/carre.png")){
		std::cout << "Probleme de chargement" << std::endl;
	}
	o_text.setSmooth(true);
	o_sprite.setTexture(o_text);
	o_sprite.setPosition(sf::Vector2f(_x,_y));
	o_rect = o_sprite.getGlobalBounds();
}