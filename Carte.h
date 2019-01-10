#ifndef CARTE_H
#define CARTE_H

#include <vector>
#include <string>
#include <SDL/SDL_mixer.h>
#include "Tile.h"
#include "Pokemon.h"

class Carte
{
    protected:
        int LARGEUR_CARTE,HAUTEUR_CARTE;
        std::vector<int> Map;
        std::vector<Tile> tiles;
        std::vector<Pokemon> PokemonSauvage;
        std::vector<int> probaApparition;
        int nb;
        Mix_Music* Music;
        std::vector< std::vector<SDL_Surface*> > pnj;
        std::vector<int> direction;
        Pokemon PokeBall;
        Tile change_tile;
        int num_tile;

    public:
        Carte(int LARGEUR_CARTE,int HAUTEUR_CARTE, std::vector<int> Map, int nb);
        int get_width();
        int get_height();
        int get_nb();
        std::vector<int> get_direction();
        std::vector<int> get_proba();
        std::vector<int> get_map();
        std::vector<Tile> get_tiles();
        std::vector<Pokemon> get_sauvage();
        Pokemon get_pokeball();
        Tile get_tile();
        int get_numTile();
        void give_tiles(std::vector<Tile> new_tiles);
        void give_music(Mix_Music* new_Music);
        void give_pnj(std::vector< std::vector<SDL_Surface*> > new_pnj);
        void give_direction(std::vector<int> new_direction);
        void give_PokeSauvage(std::vector<Pokemon> new_sauvage);
        void give_ProbaApparition(std::vector<int> new_proba);
        void give_PokeBall(Pokemon Pokeball);
        void give_Tile(Tile new_tile);
        void give_numTile(int new_numTile);
        Mix_Music* get_music();
        std::vector< std::vector<SDL_Surface*> > get_pnj();
};

#endif // CARTE_H
