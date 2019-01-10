#include "Tile.h"

//Tile::Tile(std::string file, int prop):file(file), prop(prop){};

void Tile::set_tile(std::string new_file, int new_prop)
{
    file = new_file;
    prop = new_prop;
}

std::string Tile::get_file()
{
    return file;
}

int Tile::get_prop()
{
    return prop;
}

void Tile::change_prop(int new_prop)
{
    prop = new_prop;
}

void Tile::give_carte(int new_carte)
{
    carte = new_carte;
}

int Tile::get_carte()
{
    return carte;
}

void Tile::give_position(SDL_Rect new_entree)
{
    entree_map = new_entree;
}

SDL_Rect Tile::get_position()
{
    return entree_map;
}

void Tile::give_txt(std::vector<std::string> new_txt)
{
    txt = new_txt;
}

std::vector<std::string> Tile::get_txt()
{
    return txt;
}

void Tile::give_nbPNJ(int new_PNJ)
{
    nb_PNJ = new_PNJ;
}

int Tile::get_nbPNJ()
{
    return nb_PNJ;
}

void Tile::give_dresseur(Dresseur new_dresseur)
{
    dresseur = new_dresseur;
}

Dresseur Tile::get_dresseur()
{
    return dresseur;
}

