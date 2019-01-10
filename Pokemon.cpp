#include "Pokemon.h"


// Constructeur
/*Pokemon::Pokemon(std::string nom, std::string image_back, std::string image_front, std::string cri, int niveau, int pv, int att, int def, int attspe, int defspe, int vit, int xpKO, int courbeXP, int type):nom(nom), image_back(image_back), image_front(image_front), cri(cri), niveau(niveau), pv(pv), att(att), def(def), attspe(attspe), defspe(defspe), vit(vit), xpKO(xpKO), courbeXP(courbeXP), type(type)
{
    vie = (int) (2*pv*niveau/100+niveau+10);
    attaque = (int) (2*att*niveau/100+5);
    defense = (int) (2*def*niveau/100+5);
    attaquespe = (int) (2*attspe*niveau/100+5);
    defensespe = (int) (2*defspe*niveau/100+5);
    vitesse = (int) (2*vit*niveau/100+5);
    max_vie = vie;
    if (courbeXP == 0)
    {
        xp_max = (int) 0.8*pow(niveau,3);
        xp_maxpre = (int) 0.8*pow(niveau-1,3);
    }
    else if (courbeXP == 1)
    {
        xp_max = (int) pow(niveau,3);
        xp_maxpre = (int) pow(niveau-1,3);
    }
    else if (courbeXP == 2)
    {
        xp_max = (int) (1.2*pow(niveau,3) - 15*pow(niveau,2) + 100*niveau - 140);
        xp_maxpre = (int) (1.2*pow(niveau-1,3) - 15*pow(niveau-1,2) + 100*(niveau-1) - 140);
    }
    else
    {
        xp_max = (int) 1.25*pow(niveau,3);
        xp_maxpre = (int) 1.25*pow(niveau-1,3);

    }
    xp = xp_maxpre;
    gainXP = (int) xpKO*niveau/7;
    precision = 100;
}*/

void Pokemon::set_pokemon(std::string _nom, std::string _image_back, std::string _image_front, std::string _cri, int _niveau, int _pv, int _att, int _def, int _attspe, int _defspe, int _vit, int _xpKO, int _courbeXP, int _type)
{
    nom = _nom;
    image_back = _image_back;
    image_front = _image_front;
    cri = _cri;
    niveau = _niveau;
    pv = _pv;
    att = _att;
    def = _def;
    attspe = _attspe;
    defspe = _defspe;
    vit = _vit;
    xpKO = _xpKO;
    courbeXP = _courbeXP;
    type = _type;

    vie = (int) (2*pv*niveau/100+niveau+10);
    attaque = (int) (2*att*niveau/100+5);
    defense = (int) (2*def*niveau/100+5);
    attaquespe = (int) (2*attspe*niveau/100+5);
    defensespe = (int) (2*defspe*niveau/100+5);
    vitesse = (int) (2*vit*niveau/100+5);
    max_vie = vie;
    if (courbeXP == 0)
    {
        xp_max = (int) 0.8*pow(niveau,3);
        xp_maxpre = (int) 0.8*pow(niveau-1,3);
    }
    else if (courbeXP == 1)
    {
        xp_max = (int) pow(niveau,3);
        xp_maxpre = (int) pow(niveau-1,3);
    }
    else if (courbeXP == 2)
    {
        xp_max = (int) (1.2*pow(niveau,3) - 15*pow(niveau,2) + 100*niveau - 140);
        xp_maxpre = (int) (1.2*pow(niveau-1,3) - 15*pow(niveau-1,2) + 100*(niveau-1) - 140);
    }
    else
    {
        xp_max = (int) 1.25*pow(niveau,3);
        xp_maxpre = (int) 1.25*pow(niveau-1,3);

    }
    xp = xp_maxpre;
    gainXP = (int) xpKO*niveau/7;
    precision = 100;

    nivStat = 6;
    nivPrec = 6;
    precision = 1;

    ChangeStat.push_back(0.25);
    ChangeStat.push_back(0.28);
    ChangeStat.push_back(0.33);
    ChangeStat.push_back(0.4);
    ChangeStat.push_back(0.5);
    ChangeStat.push_back(0.66);
    ChangeStat.push_back(1);
    ChangeStat.push_back(1.5);
    ChangeStat.push_back(2);
    ChangeStat.push_back(2.5);
    ChangeStat.push_back(3);
    ChangeStat.push_back(3.5);
    ChangeStat.push_back(4);

    Change_Prec.push_back(0.333);
    Change_Prec.push_back(0.375);
    Change_Prec.push_back(0.429);
    Change_Prec.push_back(0.5);
    Change_Prec.push_back(0.6);
    Change_Prec.push_back(0.75);
    Change_Prec.push_back(1);
    Change_Prec.push_back(1.33);
    Change_Prec.push_back(1.667);
    Change_Prec.push_back(2);
    Change_Prec.push_back(2.333);
    Change_Prec.push_back(2.667);
    Change_Prec.push_back(3);
}

// Methodes

std::string Pokemon::get_nom()
{
    return nom;
}

std::string Pokemon::get_imagefront()
{
    return image_front;
}

std::string Pokemon::get_imageback()
{
    return image_back;
}

std::string Pokemon::get_cry()
{
    return cri;
}

void Pokemon::change_vie(int new_vie)
{
	if (new_vie>0)
	{
		vie=new_vie;
	}
	else
	{
		vie = 0;
	}
}

void Pokemon::level_up()
{
    niveau +=1;
    xp_maxpre = xp_max;
    if (courbeXP == 0)
    {
        xp_max = (int) 0.8*pow(niveau,3);
    }
    else if (courbeXP == 1)
    {
        xp_max = (int) pow(niveau,3);
    }
    else if (courbeXP == 2)
    {
        xp_max = (int) (1.2*pow(niveau,3) - 15*pow(niveau,2) + 100*niveau - 140);
    }
    else
    {
        xp_max = (int) 1.25*pow(niveau,3);
    }
    new_vie = (int) (2*pv*niveau/100+niveau+10);
    vie = vie + new_vie - max_vie;
    attaque = (int) (2*att*niveau/100+5);
    defense = (int) (2*def*niveau/100+5);
    attaquespe = (int) (2*attspe*niveau/100+5);
    defensespe = (int) (2*defspe*niveau/100+5);
    vitesse = (int) (2*vit*niveau/100+5);
    max_vie = new_vie;

    for (int i=0; i<niveauAtkLearn.size(); i++)
    {
        if (niveau == niveauAtkLearn[i])
        {
            //AtkLearn[i] Choose new attack
        }
    }
}

void Pokemon::give_xp(int gain)
{
    xp += gain;
    if (xp >= xp_max)
    {
        level_up();
    }
}

int Pokemon::get_vie()
{
	return vie;
}

int Pokemon::get_viemax()
{
    return max_vie;
}

int Pokemon::get_def(Attaque atk)
{
    if (atk.get_type()<9)
    {
        return defense;
    }
    else
    {
        return defensespe;
    }
}

int Pokemon::get_type()
{
    return type;
}

int Pokemon::get_niveau()
{
    return niveau;
}

int Pokemon::get_vitesse()
{
    return vitesse;
}

int Pokemon::get_xpKO()
{
    return gainXP;
}

int Pokemon::get_xp()
{
    return xp;
}

int Pokemon::get_xpmax()
{
    return xp_max;
}

int Pokemon::get_xpmaxpre()
{
    return xp_maxpre;
}

std::vector<Attaque> Pokemon::get_attaque()
{
	return attq;
}

int Pokemon::calcul_degat(Attaque atk,int defense)
{
    if (atk.get_type()<9)
    {
        atq = attaque;
    }
    else
    {
        atq = attaquespe;
    }

    degat = (((niveau*0.4+2)*atq*atk.get_force())/(defense*50)+2);
    return degat;
}

void Pokemon::degat_recu(int degat)
{
	vie-=degat;
	if (vie<0)
	{
		vie=0;
	}
}

void Pokemon::give_attaque(std::vector<Attaque> new_att)
{
	attq = new_att;
}

float Pokemon::get_precision()
{
    return precision;
}

void Pokemon::change_precision(int bonus)
{
    if ((nivPrec == 0 and bonus <0) or (nivPrec == 12 and bonus >0))
    {

    }
    else
    {
        nivPrec += bonus;
        precision = Change_Prec[nivPrec];
    }
}

void Pokemon::change_stat(int stat, int bonus)
{
    //defense = (int) ((2*def*niveau/100+5)*ChangeStat[0]);
    if ((nivStat == 0 and bonus <0) or (nivStat == 12 and bonus >0))
    {

    }
    else
    {
        nivStat += bonus;
        if (stat == 0)
        {
            attaque = (int) ((2*att*niveau/100+5)*ChangeStat[nivStat]);
        }

        else if (stat == 1)
        {
            defense = (int) ((2*def*niveau/100+5)*ChangeStat[nivStat]);
        }

        else if (stat == 2)
        {
            attaquespe = (int) ((2*attspe*niveau/100+5)*ChangeStat[nivStat]);
        }

        else if (stat == 3)
        {
            defensespe = (int) ((2*defspe*niveau/100+5)*ChangeStat[nivStat]);
        }

        else if (stat == 4)
        {
            vitesse = (int) ((2*vit*niveau/100+5)*ChangeStat[nivStat]);
        }
    }
}

void Pokemon::reset_stats()
{
    nivStat = 6;
    attaque = (int) ((2*att*niveau/100+5)*ChangeStat[nivStat]);
    defense = (int) ((2*def*niveau/100+5)*ChangeStat[nivStat]);
    attaquespe = (int) ((2*attspe*niveau/100+5)*ChangeStat[nivStat]);
    defensespe = (int) ((2*defspe*niveau/100+5)*ChangeStat[nivStat]);
    vitesse = (int) ((2*vit*niveau/100+5)*ChangeStat[nivStat]);
    precision = 1;
}
