#ifndef DRESSEUR_H
#define DRESSEUR_H

#include "Pokemon.h"

class Dresseur
{
private:
    std::string nom;
    std::string image;
    std::vector<Pokemon> team;
    bool defeat;

public:
    //Dresseur(std::string nom, std::string image);
    void set_dresseur(std::string new_name, std::string new_image);
    void give_team(std::vector<Pokemon> new_team);
    std::vector<Pokemon> get_team();
    std::string get_nom();
    std::string get_image();
    void defeated();
    bool isdefeat();
};




#endif // DRESSEUR_H
