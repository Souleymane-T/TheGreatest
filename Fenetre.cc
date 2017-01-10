#include "Fenetre.hh"

Fenetre::Fenetre()
{
    window.create(sf::VideoMode(500, 500), "The Greatest");
    window.setPosition(sf::Vector2i(300, 50));
    window.setFramerateLimit(90);

    MenuText.setSmooth(true);
    MenuText.loadFromFile("img/title1.png");
    Menu_sprite.setTexture(MenuText);

    /////// TEXTE ZONE DIALOGUE ///////
    textarea.loadFromFile("img/textarea.png");
    textarea.setSmooth(true);
    textarea_sprite.setTexture(textarea);
    textarea_sprite.setPosition(sf::Vector2f(20,380));
    i = 0;
    j = 0;
    sontexte = true;
    DefilText = true;

    mfont.loadFromFile("font/FSEX300.ttf"); // Police de caractère 
    mtext.setFont(mfont);
    mtext.setCharacterSize(16);
    mtext.setColor(sf::Color::Black);
    mtext.setPosition(sf::Vector2f(45,400));
    ///////////////////

    sol.loadFromFile("img/sol.png");
    sol.setSmooth(true);
    sol_sprite.setTexture(sol);
    sol_sprite.setPosition(sf::Vector2f(0,0));

    mnom.setFont(mfont);
    mPV.setFont(mfont);
    mtemps.setFont(mfont);

    mnom.setString("Trump");
    mPV.setString("PV");
    mtemps.setString("Time");

    mnom.setCharacterSize(19);
    mPV.setCharacterSize(19);
    mtemps.setCharacterSize(19);

    mnom.setColor(sf::Color::White);
    mPV.setColor(sf::Color::White);
    mtemps.setColor(sf::Color::White);

    mnom.setPosition(sf::Vector2f(50,10));
    mPV.setPosition(sf::Vector2f(200,10));
    mtemps.setPosition(sf::Vector2f(400,10));
    ///////////////////

    //////// INFO DYNAMIQUE (points, barre de vie, temps en sec) /////
    PVbar.setFillColor(sf::Color::Green);
    PVbar.setSize(sf::Vector2f(100,5));
    PVbar.setPosition(sf::Vector2f(200,52));

    mscore.setFont(mfont);
    mtempsd.setFont(mfont);
    mPVnum.setFont(mfont);

    mscore.setString("0");
    mtempsd.setString("   ");
    mPVnum.setString("   ");

    mscore.setCharacterSize(19);
    mtempsd.setCharacterSize(19);
    mPVnum.setCharacterSize(19);

    mscore.setColor(sf::Color::White);
    mtempsd.setColor(sf::Color::White);
    mPVnum.setColor(sf::Color::White);

    mscore.setPosition(sf::Vector2f(50,40));
    mtempsd.setPosition(sf::Vector2f(400,40));
    mPVnum.setPosition(sf::Vector2f(220, 10));
    /////////////////

    //////// INFO POUR STATISTIQUE DU JOUEUR  ////////
    /*Nombre de bulletin, malus, bonus obtenus */
    mstat_malus.setFont(mfont);
    mstat_bonus.setFont(mfont);
    mstat_bull.setFont(mfont);

    mstat_malus.setCharacterSize(15);
    mstat_bonus.setCharacterSize(15);
    mstat_bull.setCharacterSize(15);

    mstat_malus.setColor(sf::Color::Black);
    mstat_bonus.setColor(sf::Color::Black);
    mstat_bull.setColor(sf::Color::Black);

    mstat_malus.setPosition(sf::Vector2f(30,390));
    mstat_bonus.setPosition(sf::Vector2f(30,420));
    mstat_bull.setPosition(sf::Vector2f(30,450));
    /////////////////
}
/*Affiche une image en arrière plan*/
void Fenetre::afficheImage(std::string nomImage)
{
    MenuText.loadFromFile(nomImage);
    Menu_sprite.setTexture(MenuText);
    window.draw(Menu_sprite);
    window.display();
    window.clear();
}
/* Image pour le menu avec "press enter" clignotant */
void Fenetre::menu(bool update)
{
    if(update)
        afficheImage("img/title1.png");
    else
        afficheImage("img/title2.png");
}
/*Image niveau de difficulté*/
void Fenetre::mode()
{
    afficheImage("img/niveau.png");
}
/*Affichage de fin récapitulatif*/
void Fenetre::fin(bool victoire)
{
    if(victoire) // On affiche d'abord le fond d'écran
        MenuText.loadFromFile("img/victoire.jpg");
    else
        MenuText.loadFromFile("img/defaite.png");
    Menu_sprite.setTexture(MenuText);
    window.draw(Menu_sprite);
    /* Puis on affiche par dessus les statistiques du joueur */
    window.draw(mstat_malus);
    window.draw(mstat_bonus);
    window.draw(mstat_bull);
    window.display();
    window.clear();
}
/*Bulle de dialogue*/
bool Fenetre::dialogue(std::vector<std::string> phrase_split,sf::Sound& vocal)
{
    if(DefilText == false)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // On appuie sur Entrer pour faire avancer le texte
        {
            i++;
            // Permet d'éviter qu'un appui soit compter plusieurs fois
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)); 
            if(i >= (signed)phrase_split.size()){ // Si il n'y a plus de texte
                i = 0; j = 0; sontexte = true; DefilText = true; // Réinitialisation des variables
                return false;
            }
            else
            {
                DefilText = true;
            }
        }
    }
    else
    {
        if(j != phrase_split[i].size()) // On parcout le string lettre par lettre
        {
            sstext << phrase_split[i].at(j);
            mtext.setString(sstext.str());
            if(sontexte) // On joue le son de bip
            {
                vocal.play();
                vocal.setLoop(true);
                sontexte = !sontexte;
            }
            j++;
        }
        else // le string est parcouru, on coupe le son et on efface ce qu'il y avait dans sstext
        {
            vocal.stop();
            sstext.str("");
            sstext.clear();
            sontexte = !sontexte;
            j = 0;
            DefilText = false;
        }
    }
    window.draw(textarea_sprite); // rectangle pour la zone de texte
    window.draw(mtext); // Affiche du texte par dessus
    return true;
}

/*Affichage des infos statiques et dynamiques*/
void Fenetre::affi_jeu()
{
    window.draw(mnom);
    window.draw(mPV);
    window.draw(mtemps);

    window.draw(mscore);
    window.draw(PVbar);
    window.draw(mtempsd);
    window.draw(mPVnum);
    window.display();
    window.clear();
}

void Fenetre::affi_text(){
    window.draw(textarea_sprite);
    window.draw(mtext);
}

/*Mise à jour de l'affichage des données du joueur et du temps écoulé*/
void Fenetre::update_info(Joueur& J1, int temps)
{
    std::stringstream sstemps, ssscore, ssmPVnum;
    sstemps << temps;
    mtempsd.setString(sstemps.str());

    ssscore << J1.getScore();
    ssmPVnum << J1.getPV();
    PVbar.setSize(sf::Vector2f(J1.getPV(),5));

    mscore.setString(ssscore.str());
    mPVnum.setString(ssmPVnum.str());
}
/*Affichage des statistiques en fin de jeu*/
void Fenetre::affi_stat(Joueur& J1)
{
	std::stringstream ssbonus, ssmalus, ssbull;
	ssbonus << " Bonus : " << J1.getResult()["Bonus"];
	ssmalus << " Malus : " << J1.getResult()["Malus"];
	ssbull << " Ballot(s) : " << J1.getResult()["Bulletin"];
	mstat_malus.setString(ssbonus.str());
    mstat_bonus.setString(ssmalus.str());
    mstat_bull.setString(ssbull.str());
}
