#include "Carte.h"

Carte::Carte(int LARGEUR_CARTE,int HAUTEUR_CARTE, std::vector<int> Map, int nb): LARGEUR_CARTE(LARGEUR_CARTE), HAUTEUR_CARTE(HAUTEUR_CARTE), Map(Map), nb(nb){}

int Carte::get_width()
{
    return LARGEUR_CARTE;
}

int Carte::get_height()
{
    return HAUTEUR_CARTE;
}

int Carte::get_nb()
{
    return nb;
}

std::vector<int> Carte::get_map()
{
    return Map;
}

std::vector<Tile> Carte::get_tiles()
{
    return tiles;
}

void Carte::give_tiles(std::vector<Tile> new_tiles)
{
    tiles = new_tiles;
}

Pokemon Carte::get_pokeball()
{
    return PokeBall;
}

void Carte::give_PokeBall(Pokemon Pokeball)
{
    PokeBall = Pokeball;
}

void Carte::give_Tile(Tile new_tile)
{
    change_tile = new_tile;
}

Tile Carte::get_tile()
{
    return change_tile;
}

int Carte::get_numTile()
{
    return num_tile;
}

void Carte::give_numTile(int new_numTile)
{
    num_tile = new_numTile;
}

void Carte::give_music(Mix_Music* new_music)
{
    Music = new_music;
}

Mix_Music* Carte::get_music()
{
    return Music;
}

void Carte::give_pnj(std::vector< std::vector<SDL_Surface*> > new_pnj)
{
    pnj = new_pnj;
}

std::vector< std::vector<SDL_Surface*> > Carte::get_pnj()
{
    return pnj;
}

void Carte::give_direction(std::vector<int> new_direction)
{
    direction = new_direction;
}

std::vector<int> Carte::get_direction()
{
    return direction;
}

void Carte::give_PokeSauvage(std::vector<Pokemon> new_Sauvage)
{
    PokemonSauvage = new_Sauvage;
}

std::vector<Pokemon> Carte::get_sauvage()
{
    return PokemonSauvage;
}

void Carte::give_ProbaApparition(std::vector<int> new_proba)
{
    probaApparition = new_proba;
}

std::vector<int> Carte::get_proba()
{
    return probaApparition;
}
