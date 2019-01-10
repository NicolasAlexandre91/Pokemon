#ifndef TILE_H
#define TILE_H

#include <string>
#include <SDL/SDL.h>
#include "Dresseur.h"

class Tile
{
    protected:
        std::string file;
        int prop;
        // Pour les Tiles CHANGEMAP
        int carte;
        SDL_Rect entree_map;
        // Pour les Tiles TXT et PNJ : texte du PNJ ou de l'objet
        std::vector<std::string> txt;
        // Pour les Tiles PNJ : numero du PNJ
        int nb_PNJ;
        Dresseur dresseur;

    public:
        //Tile(std::string file, int prop);
        void set_tile(std::string file, int prop);
        std::string get_file();
        int get_prop();
        void change_prop(int new_prop);
        void give_carte(int new_carte);
        int get_carte();
        void give_position(SDL_Rect new_entree);
        SDL_Rect get_position();
        void give_txt(std::vector<std::string> new_txt);
        std::vector<std::string> get_txt();
        void give_nbPNJ(int new_PNJ);
        int get_nbPNJ();
        void give_dresseur(Dresseur new_dresseur);
        Dresseur get_dresseur();

};

#endif // TILE_H
