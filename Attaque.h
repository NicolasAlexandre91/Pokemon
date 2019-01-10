#ifndef ATTAQUE_H
#define ATTAQUE_H

#include<iostream>
#include<vector>

class Attaque
{
	protected:
		std::string nom;
		int force, type, precision;
		int _stats;
		int _bonus;
		bool effect;


	public:
		Attaque(std::string nom, int force, int type, int precision, bool effect);
		std::string get_nom();
		int get_force();
		int get_type();
		int get_precision();
		void give_effect(int stat, int bonus);
		int get_stat();
		int get_bonus();
		bool is_effect();
};

#endif // ATTAQUE_H
