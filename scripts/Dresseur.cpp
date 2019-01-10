#include "Dresseur.h"

//Dresseur::Dresseur(std::string nom, std::string image): nom(nom), image(image)
//{
//    defeat = false;
//}

void Dresseur::set_dresseur(std::string new_name, std::string new_image)
{
    nom = new_name;
    image = new_image;
    defeat = false;
}

std::string Dresseur::get_nom()
{
    return nom;
}

std::string Dresseur::get_image()
{
    return image;
}

void Dresseur::give_team(std::vector<Pokemon> new_team)
{
    team = new_team;
}

std::vector<Pokemon> Dresseur::get_team()
{
    return team;
}

void Dresseur::defeated()
{
    defeat = true;
}

bool Dresseur::isdefeat()
{
    return defeat;
}
