#include "Attaque.h"
#include<iostream>

//Constructeur
Attaque::Attaque(std::string nom, int force, int type, int precision, bool effect):nom(nom), force(force), type(type), precision(precision), effect(effect){}

// Methodes
std::string Attaque::get_nom()
{
	return nom;
}

int Attaque::get_force()
{
	return force;
}

int Attaque::get_type()
{
    return type;
}

int Attaque::get_precision()
{
    return precision;
}

void Attaque::give_effect(int stat, int bonus)
{
    _stats = stat;
    _bonus = bonus;
}

int Attaque::get_stat()
{
    return _stats;
}

int Attaque::get_bonus()
{
    return _bonus;
}

bool Attaque::is_effect()
 {
     return effect;
 }
