#include "ListObstacle.hh"
const int ListObstacle::X[] = {157,219,281};
const int ListObstacle::Y[] = {156,220,284};

const int ListObstacle::nbMur = 3;

ListObstacle::~ListObstacle()
{
    unsigned int i;
    for(i = 0; i < _ListObstacle.size(); i++)
    {
        delete(_ListObstacle[i]);
    }
}

void ListObstacle::addObj(int nbBonus, int nbMalus)
{
    for(int i = 0; i < nbBonus; i++ )
        _ListObstacle.push_back(new Bonus(rand()%2000+1000,rand()%2000+1000,5,0.1)); //Coordonnnes au hasard en dehors de l'ecran

    for(int i = 0; i < nbMalus; i++ )
        _ListObstacle.push_back(new Malus(rand()%2000+1000,rand()%2000+1000,5,0.1)); //Coordonnnes au hasard en dehors de l'ecran
}

/*Créations des murs pour le boss*/
void ListObstacle::addMur()
{
    int modulo = 0;
    /*Création du carré enfermant le joueur*/
    for(int i = 0; i < nbMur; i++)
    {
        for(int j = 0; j < nbMur; j++)
        {
            if((j == 1) && (i == 1))
            {
                modulo++;
            }
            else
            {
                if(modulo % 2 == 0) // l'ajout des murs en bois ou bétons est alterné
                {
                    _ListObstacle.push_back(new Mur(X[j],Y[i],62,64));
                }
                else
                {
                    _ListObstacle.push_back(new Bois(X[j],Y[i],62,64,3));
                }
                modulo++;
            }
        }
    }
    /*Création des couronnes de murs*/
    addGdCour(50,418,92,5);
    addGdCour(104,364,130,3);
    /*Création de murs supplémentaires pour rendre le boss plus difficile*/
    addCroix();
}

void ListObstacle::addCroix(){
    _ListObstacle.push_back(new Mur(0,234,31,32));
    _ListObstacle.push_back(new Mur(468,234,31,32));
    _ListObstacle.push_back(new Bois(234,0,31,32,3));
    _ListObstacle.push_back(new Bois(234,468,31,32,3));
}

void ListObstacle::addGdCour(int refhaut, int refbass,int somme, int nb){
    int modulo = 0;
    int temp1 = refhaut;
    for(int i = 0; i < nb; i++)
    {
        if(modulo % 2 == 0) // l'ajout des murs en bois ou bétons est alterné
        {
            _ListObstacle.push_back(new Mur(temp1,refhaut,31,32));
            _ListObstacle.push_back(new Mur(refhaut,temp1,31,32));
            _ListObstacle.push_back(new Mur(temp1,refbass,31,32));
            _ListObstacle.push_back(new Mur(refbass,temp1,31,32));
        }
        else
        {
            _ListObstacle.push_back(new Bois(temp1,refhaut,31,32,3));
            _ListObstacle.push_back(new Bois(refhaut,temp1,31,32,3));
            _ListObstacle.push_back(new Bois(temp1,refbass,31,32,3));
            _ListObstacle.push_back(new Bois(refbass,temp1,31,32,3));
        }
        temp1 += somme;
        modulo++;
    }
}

ListObstacle::ListObstacle(Difficulte niveau):_niveau(niveau)
{
    switch(niveau)
    {
    case FACILE:
        _ListObstacle.push_back(new Bulletin (300,100,5));
        addObj(5,1);
        break;

    case NORMAL:
        _ListObstacle.push_back(new Bulletin(300,100,5));
        addObj(3,3);
        break;

    default:
        _ListObstacle.push_back(new Bulletin (300,100,5));
        addObj(2,5);
        break;
    }
}



void ListObstacle::update(Joueur& J1, int& special)
{
    size_t i,j;
    int tmp = 0;
    for(i = 0; i < _ListObstacle.size(); i++)
    {
        if(J1.getRect().intersects(_ListObstacle[i]->getRect()))
        {
            _ListObstacle[i]->collision(J1,tmp);//Pour faire l'addStat, tmp = 0
            if(special != 0)
            {
                for(j = 0; j <_ListObstacle.size(); j++)
                    _ListObstacle[j]->collision(J1,special); //Pour mettre tous les bonus sur le terrain ou en dehors
                if(special == 1)
                    special++;
                else
                {
                    special = 0;
                    return;
                }

                for(j = 0; j <_ListObstacle.size(); j++) //Si l'obstacle a bouge c'est un objet, on verifie qu'il n'ecrase pas un autre objet
                {
                    if(i==j)
                        continue;
                    else
                    {
                        while(_ListObstacle[i]->getRect().intersects(_ListObstacle[j]->getRect() ) //S'il intersect un autre objet ou le joueur
                                || _ListObstacle[i]->getRect().intersects(J1.getRect())
                             )
                            _ListObstacle[i]->collision(J1,special);
                    }
                }
            }
        }
    }
}
/*Test des collisions lors de la phase avec le boss*/
void ListObstacle::updateBoss(Joueur& J1, int& anim)
{

    for(unsigned int k = 0; k < _ListObstacle.size(); k++)
        _ListObstacle[k]->collision(J1,anim); // Entre les murs et le joueur
}

ListObstacle& ListObstacle::operator=(const Difficulte& niveau)
{
    if(_ListObstacle.size()!=0)//Si la liste est deja existante, la supprimer
    {
        unsigned int i;
        for(i = 0; i < _ListObstacle.size(); i++)
        {
            delete(_ListObstacle[i]);
        }
        _ListObstacle.clear();
    }
    this -> _niveau = niveau;
    switch(niveau)
    {
    case FACILE:
        _ListObstacle.push_back(new Bulletin (300,100,5));
        addObj(5,1);
        break;

    case NORMAL:
        _ListObstacle.push_back(new Bulletin(300,100,5));
        addObj(3,3);
        break;

    case DIFFICILE:
        _ListObstacle.push_back(new Bulletin (300,100,5));
        addObj(2,5);
        break;
    case BOSS:
        addMur();
        break;
    }
    return *this;
}
