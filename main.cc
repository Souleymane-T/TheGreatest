#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <fstream>

#include "utility.hh"
#include "Joueur.hh"
#include "Hillary.hh"
#include "Obstacle.hh"
#include "Objet.hh"
#include "Bonus.hh"
#include "Malus.hh"
#include "Bulletin.hh"
#include "ListObstacle.hh"
#include "Mur.hh"
#include "Bois.hh"
#include "Fenetre.hh"

// Joue une musique
void audio(bool& jouer, const std::string titre);
// Découpe un fichier texte et met dans un vect de string
void update_texte(const std::string texte); 

/////////////////
void FenDisclai(); // Disclaimer
bool disclaib = true; 
sf::Clock mclock; // Egalemnt pour changement image du joueur
/////////////////
void FenMenu(); // Menu
sf::Music music1;
sf::Clock clkmenu; // clock pour faire clignoter "Press enter"
// pour éviter de faire un music1.play tout le temps ce qui bloquerait la musique
bool son = true; 
bool menub_fin = true; // savoir si on a passé tout le menu
bool menub_img_up = true; // mettre a jour l'image du menu
bool modeb = true; // savoir si on a fait "entrer" pour passer la première image
bool finDuJeu = false;
bool victoire;
/////////////////
void FenDial(); // Affichage du dialogue
sf::SoundBuffer buffer; // Un buffer permet la superposition de sons
sf::Sound vocal; // Pour le son du bip 
std::vector<std::string> phrase_split; // vecteur dans update_texte
bool dialb = true; // 1er dialogue
bool dialhillary = true; // dialogue d'hillary
bool theme = true; // même utilité sur bool son;
/////////////////
void FenAffi(); /*** AFFICHAGE DU JEU ***/
/////////////////
void FenUpInfo(); /***  MISE A JOUR DES INFOS ***/ // Pour gérer l'avancement dans le jeu
int temps = 25;
const int ScoreMax = 40;
const int tempsBoss = 50;
int tempsSpecial = 5;
int special = 0; // Ternaire: 0 -> bulletin seul; 1 -> ajout bonus&malus; 2 -> retire bonus&malus
sf::Clock mclockt; // Clock pour mettre a jour le temps restant au joueur
/////////////////
void bord(); // test collision bord écran
void deplacement(); // déplacement du joueur
void animation(); // mise à jour de la texture du joueur
bool updateFPS; // savoir si on découpe pas en dehors du png de Trump
sf::Vector2i anim(1,0); // Image de Trump en ligne X et colonne Y de Trump.png
/////////////////

bool dialVictoire = true; // dialogue fin du jeu
bool dialtran = false; // Pour afficher le dialogue par dessus tous les autres objets

sf::Clock HillaryClock, HillaryCollision;

ListObstacle L1;
Joueur J1;
Hillary Clinton;
Fenetre F1;

int main()
{
    srand(time(NULL));
    update_texte("text/texte.txt");
    buffer.loadFromFile("audio/vocal.ogg");
    vocal.setBuffer(buffer);
    J1.getSprite().setPosition(sf::Vector2f(250,250));
    J1.getSprite().setTextureRect(
        sf::IntRect(anim.x * 48 + 7, anim.y * 48 + 2, J1.getWidth(), J1.getHeight()));
    while(F1.getWindow().isOpen())
    {
        sf::Event event;
        while (F1.getWindow().pollEvent(event)) //Quitte en appuyant sur la croix ou sur Echap
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                F1.getWindow().close();
        }

        if(disclaib) // Disclaimer
        {
            FenDisclai();
        }
        else if(menub_fin) // Menu avec selection difficulté
        {
            FenMenu();
            audio(son, "audio/opening.ogg");
        }
        else
        {
            if(!finDuJeu) // phase de jeu
            {
                if(dialb) // dialogue d'intro
                {
                    F1.affi_sol();
                    audio(theme, "audio/IFIC.ogg");
                    FenDial();
                    F1.getWindow().display();
                    F1.getWindow().clear();
                }
                else
                {
                    F1.affi_sol();
                    deplacement();
                    FenUpInfo();
                    FenAffi();
                }
            }
            else
            {
                J1.getSprite().setPosition(sf::Vector2f(270-J1.getWidth(),270-J1.getHeight()));
                Clinton.getSprite().setPosition(sf::Vector2f(270,290));
                if(victoire) // Victoire
                {
                    if(dialVictoire)
                    {
                        if(F1.geti() == 5){
                            Clinton.setSprite("img/endH.png");
                            audio(son,"audio/death.ogg");
                            music1.setLoop(false);
                        }
                        F1.affi_sol();
                        update_texte("text/goodend.txt");
                        FenDial();
                        FenAffi();

                    }
                    else
                    {
                        audio(theme,"audio/victoire.ogg");
                        F1.affi_stat(J1);
                        F1.fin(victoire);
                    }
                }
                else // Défaite
                {
                    if(dialVictoire)
                    {
                        update_texte("text/badend.txt");
                        F1.affi_sol();
                        FenDial();
                        FenAffi();
                    }
                    else
                    {
                        audio(theme,"audio/defaite.ogg");
                        F1.affi_stat(J1);
                        F1.fin(victoire);
                    }
                }
            }

        }
    }
    return 0;
}

/*** AFFICHAGE DU DISCLAIMER ***/
void FenDisclai()
{
    if(mclock.getElapsedTime().asMilliseconds() >= 5000) // 5 sec d'attente
        disclaib = false;
    F1.afficheImage("img/avertissement.png");
}

/*** AFFICHAGE DU MENU ***/
void FenMenu()
{
    if(modeb)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            modeb = false;
        
        if(clkmenu.getElapsedTime().asMilliseconds() >= 500)
        {
            F1.menu(menub_img_up);
            menub_img_up = !menub_img_up;
            clkmenu.restart();
        }
    }
    else  // Choix du niveau de difficulte
    {
        F1.mode();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            L1 = FACILE;
            menub_fin = false;
            music1.stop();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            L1 = NORMAL;
            menub_fin = false;
            music1.stop();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            L1 = DIFFICILE;
            tempsSpecial = 7;
            menub_fin = false;
            music1.stop();
        }
    }
}

/*** AFFICHAGE DES DIALOGUES ***/
void FenDial()
{
    if(F1.dialogue(phrase_split,vocal) == false)
    {
        phrase_split.clear();
        dialb = false;
        dialhillary = !dialhillary;
        dialVictoire = false;
    }
    dialtran = true;
}

/*** AFFICHAGE DU JEU ***/
void FenAffi()
{
    unsigned int k;
    for(k = 0; k < L1.getListObstacle().size(); k++) // Obstacle
        F1.getWindow().draw(L1[k].getSprite());
    F1.getWindow().draw(J1.getSprite()); // Trump
    F1.getWindow().draw(Clinton.getSprite());
    if(dialtran){
        F1.affi_text();
        dialtran = false;
    }
    F1.affi_jeu();
}

/***  MISE A JOUR DES INFOS ***/ // Pour gérer l'avancement dans le jeu
void FenUpInfo()
{
    if(temps > 0)  // Mise a jour du temps
    {
        if(mclockt.getElapsedTime().asMilliseconds() >= 1000)
        {
            temps--;
            if(temps%tempsSpecial==0 && !special)
            {
                special++;
            }
            mclockt.restart();
        }
        if(J1.getPV() == 0)
        {
            finDuJeu = true;
            victoire = false;
        }
    }
    else
    {
        if(J1.getScore() < ScoreMax) // défaite score insuffisant
        {
            finDuJeu = true;
            victoire = false;
        }
        else
        {
            if(L1.getDifficulte() == BOSS)
            {
                finDuJeu = true;
                victoire = true;
            }
            else
            {
                L1 = BOSS;
                music1.stop();
                son = true;
                temps = tempsBoss;
                J1.getSprite().setPosition(sf::Vector2f(270-J1.getWidth(),270-J1.getHeight()));
            }
        }
    }
    if(L1.getDifficulte() != BOSS)  //Si on est pas dans le mode du boss
    {
        L1.update(J1, special);
    }
    else // On entre dans le mode du boss
    {
        if(dialhillary == false) // Dialogue d'intro de Hillary
        {
            temps = tempsBoss;
            F1.affi_sol();
            update_texte("text/texthillary.txt");
            FenDial();
            J1.getSprite().setPosition(sf::Vector2f(270-J1.getWidth(),270-J1.getHeight()));
            J1.updateORect();

        }
        else // Fin du dialogue
        {
            audio(son, "audio/Fusion.ogg");
            special = 1;
            L1.updateBoss(J1,anim.y);// Si on est dans le mode du Boss
            Clinton.updateImage(HillaryClock);
            // Test de collision Hillary-Trump toutes les sec 
            if(HillaryCollision.getElapsedTime().asMilliseconds() >= 1000) 
            {
                Clinton.collision(J1,anim.y);
                HillaryCollision.restart();
            }
            Clinton.deplacement(J1);
        }
    }
    F1.update_info(J1, temps); // Mise a jour info du joueur
    // Si fin du jeu, arrêt du son et préparation pour dialogue et musique de fin
    if(finDuJeu) 
    {
        dialVictoire = true;
        son = true;
        theme = true;
        music1.stop();
    }
}


/***  DECOUPE UN TEXTE POUR LES DIALOGUES */
void update_texte(const std::string texte)
{
    std::ifstream file(texte);
    std::stringstream ss;
    std::string s;
    while (getline(file,s))
    {
        ss << s ;
    }
    s = ss.str();
    file.close();
    phrase_split = split(s, "-");
}

/*** MUSIQUE DE FOND ***/
void audio(bool& jouer,const std::string titre)
{
    if(jouer)
    {
        music1.openFromFile(titre);
        music1.play();
        music1.setLoop(true);
        jouer = !jouer;
    }
}



/***************************************/
/****** DEPLACEMENT DU PERSONNAGE ******/

/*** CHANGEMENT DE L'IMAGE DU JOUEUR ***/
void animation()
{
    if(mclock.getElapsedTime().asMilliseconds() >= 100)
    {
        if(updateFPS)
        {
            anim.x++;
            if(anim.x == 2)
            {
                updateFPS = false;
            }
        }
        else
        {
            anim.x--;
            if(anim.x == 0)
            {
                updateFPS = true;
            }
        }
        mclock.restart();
    }
}
/*** TEST DE COLLISION AVEC LE BORD ***/
void bord()
{
    if(J1.getSprite().getPosition().x <= 0)
        J1.getSprite().setPosition(sf::Vector2f(0,J1.getSprite().getPosition().y));
    if(J1.getSprite().getPosition().x >= 450)
        J1.getSprite().setPosition(sf::Vector2f(450,J1.getSprite().getPosition().y));
    if(J1.getSprite().getPosition().y <= 0)
        J1.getSprite().setPosition(sf::Vector2f(J1.getSprite().getPosition().x,0));
    if(J1.getSprite().getPosition().y >= 450)
        J1.getSprite().setPosition(sf::Vector2f(J1.getSprite().getPosition().x,450));
    J1.updateORect();
}
/*** DEPLACEMENNT DU JOUEUR ***/
void deplacement()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        J1.getSprite().move(0,-J1.getSpeed());
        animation();
        anim.y = 3;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        J1.getSprite().move(0,J1.getSpeed());
        animation();
        anim.y = 0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        J1.getSprite().move(-J1.getSpeed(),0);
        animation();
        anim.y = 1;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        J1.getSprite().move(J1.getSpeed(),0);
        animation();
        anim.y = 2;
    }
    J1.getSprite().setTextureRect( // on change l'image en fontion de la direction
        sf::IntRect(anim.x * 48 + 7, anim.y * 48 + 2, J1.getWidth(), J1.getHeight()));
    bord();

}
