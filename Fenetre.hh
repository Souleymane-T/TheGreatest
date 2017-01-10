#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>

#include "Joueur.hh"
#include "ListObstacle.hh"

#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
#include <fstream>

class Fenetre
{
private:
    sf::RenderWindow window;

    //// MENU ////
    sf::Texture MenuText; 
    sf::Sprite Menu_sprite;
    /////////////

    //// SOL ///
    sf::Texture sol;
    sf::Sprite sol_sprite;
    /////////////

    sf::Font mfont;

    ///// ZONE DE DIALOGUE /////
    sf::Texture textarea;
    sf::Sprite textarea_sprite;
    sf::Text mtext;
    std::stringstream sstext;
    bool sontexte;
    bool DefilText;
    int i;
    unsigned int j;
    /////////////

    /////// INFO STATIQUE ///////
    sf:: Text mnom, mPV, mtemps;
    //////// INFO DYNAMIQUE (points, nombre pts vie, barre de vie, temps) /////
    sf:: Text mscore, mtempsd, mPVnum;
    sf::RectangleShape PVbar;
    /////////////

    //////// INFO POUR STATISTIQUE DU JOUEUR  ////////
    sf:: Text mstat_malus, mstat_bonus, mstat_bull;
    ////////////

public:
    Fenetre();
    void menu(bool update);
    void mode();
    bool dialogue(std::vector<std::string> phrase_split, sf::Sound& vocal);
    void affi_jeu();
    void affi_text();
    void affi_sol(){window.draw(sol_sprite);}
    void update_info(Joueur& J1, int temps);
    void fin(bool);
    void affi_stat(Joueur& J1);
    void afficheImage(std::string nomImage);
    sf::RenderWindow& getWindow(){return window;};
    int geti(){return i;};

};
