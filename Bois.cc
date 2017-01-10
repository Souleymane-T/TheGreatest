#include "Bois.hh"

Bois::Bois(int x, int y,int size_w, int size_h , int resistance)
:Mur(x,y,size_w,size_h), _resistance(resistance){
    if(!o_text.loadFromFile("img/wood.png")){
        std::cout << "Probleme de chargement" << std::endl;
    }
    o_text.setSmooth(true);
    o_sprite.setTexture(o_text);
    o_sprite.setPosition(sf::Vector2f(_x,_y));
    o_sprite.setTextureRect(sf::IntRect(0,0,_width,_height));
    o_rect = o_sprite.getGlobalBounds();
}

void Bois::collision(Joueur& J1, int& anim){
    if(J1.getRect().intersects(o_rect)){
        switch (anim){
            case 0://Collision par le bord haut du mur
                J1.getSprite().setPosition(
                    sf::Vector2f(J1.getSprite().getPosition().x,_y - 46));
                break;
            case 1://Collision par le bord droit
                J1.getSprite().setPosition(
                    sf::Vector2f(_x + _width,J1.getSprite().getPosition().y));
                break;
            case 2://Collision par le bord gauche
                J1.getSprite().setPosition(
                    sf::Vector2f(_x - 33,J1.getSprite().getPosition().y));
                break;
            default://Collision par le bord droit
                J1.getSprite().setPosition(
                    sf::Vector2f(J1.getSprite().getPosition().x,_y + _height));
                break;
        }
        //Si on appuie sur espace en avancant sur le mur en bois, on baisse la resistance
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            _resistance--;
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
            if(_resistance == 0){
                o_sprite.setPosition(sf::Vector2f(-1000,-1000));//On fait disparaitre le mur hors champ
                updateORect();
            }
        }
        J1.updateORect();


    }
}
