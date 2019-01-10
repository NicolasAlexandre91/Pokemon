#ifndef POKEMON_H
#define POKEMON_H

#include <vector>
#include "Attaque.h"
#include<iostream>
#include <math.h>

class Pokemon
{
	protected:
		std::string nom;
		std::string image_back;
		std::string image_front;
		std::string cri;
		int niveau;
		int vie;
		int new_vie, max_vie;
		int degat;
		int pv, att, def, attspe, defspe, vit;
		int xpKO,gainXP,courbeXP, xp, xp_max,xp_maxpre;
		int type;
		int atq;
		int nivStat;
		int nivPrec;
		std::vector<float> ChangeStat;
		std::vector<float> Change_Prec;
		int attaque, defense, attaquespe, defensespe, vitesse;
		float precision;
		std::vector<Attaque> attq;
		std::vector<Attaque> AtkLearn;
		std::vector<int> niveauAtkLearn;

	public:
		//Pokemon(std::string nom, std::string image_back, std::string image_front, std::string cri, int niveau, int pv, int att, int def, int attspe, int defspe, int vit, int xpKO, int courbeXP, int type);
		void set_pokemon(std::string _nom, std::string _image_back, std::string _image_front, std::string _cri, int _niveau, int _pv, int _att, int _def, int _attspe, int _defspe, int _vit, int _xpKO, int _courbeXP, int _type);
		void change_vie(int new_vie);
		int get_vie();
		int get_viemax();
		int calcul_degat(Attaque atk, int defense);
		void degat_recu(int degat);
		void give_attaque(std::vector<Attaque> new_att);
		void give_xp(int gain);
		void level_up();
		void change_stat(int stat,int bonus);
		void reset_stats();
		void change_precision(int bonus);
		int get_def(Attaque atk);
		int get_type();
		int get_niveau();
		int get_vitesse();
		int get_xpKO();
		int get_xp();
		int get_xpmax();
		int get_xpmaxpre();
		float get_precision();
		std::vector<Attaque> get_attaque();
		std::string get_nom();
		std::string get_imagefront();
		std::string get_imageback();
		std::string get_cry();
};



#endif
