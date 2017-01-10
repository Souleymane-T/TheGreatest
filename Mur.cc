#include "Mur.hh"



Mur::Mur(int x, int y, int size_w, int size_h)
:Obstacle(x,y),_width(size_w),_height(size_h){
    if(!o_text.loadFromFile("img/wall.png")){
        std::cout << "Probleme de chargement" << std::endl;
    }
    o_text.setSmooth(true);
    o_sprite.setTexture(o_text);
    o_sprite.setPosition(sf::Vector2f(_x,_y));
    o_sprite.setTextureRect(sf::IntRect(0,0,size_w,size_h));
    o_rect = o_sprite.getGlobalBounds();
}
/*Empêche le joueur de traverser le mur*/
void Mur::collision(Joueur& J1, int& anim){
    if(J1.getRect().intersects(o_rect)){
        switch (anim){
            case 0:
                J1.getSprite().setPosition(
                    sf::Vector2f(J1.getSprite().getPosition().x, _y - J1.getHeight() ));
                break;
            case 1:
                J1.getSprite().setPosition(
                    sf::Vector2f(_x + _width,J1.getSprite().getPosition().y));
                break;
            case 2:
                J1.getSprite().setPosition(
                    sf::Vector2f(_x - J1.getWidth(),J1.getSprite().getPosition().y));
                break;
            default:
                J1.getSprite().setPosition(
                    sf::Vector2f(J1.getSprite().getPosition().x,_y + _height));
                break;
        }
        J1.updateORect();
    }
}
