#ifndef COMBAT_H
#define COMBAT_H

#include "Input.h"

#include<SDL/SDL_ttf.h>

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        std::swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void BlackScreen(SDL_Surface *ecran)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    SDL_Flip(ecran);
}

void IntroCombat(std::string file)
{
    int i;
    SDL_Surface *barre_combat = NULL, *Ennemi = NULL, *GoldCombat = NULL;
    SDL_Surface *ecranCombat = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Rect positionBarreCombat;
    SDL_Rect positionGold, positionEnnemi;
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    GoldCombat = SDL_LoadBMP("gold_combat.bmp");
    Ennemi = SDL_LoadBMP(file.data());

    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;
    positionEnnemi.y = 0;
    positionGold.y = 40;

    for (i=0; i<96;i++)
    {
        positionEnnemi.x = i;
        positionGold.x = 104 - i;
        SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));

        SDL_BlitSurface(barre_combat, NULL, ecranCombat, &positionBarreCombat);
        SDL_BlitSurface(GoldCombat, NULL, ecranCombat, &positionGold);
        SDL_SetColorKey(Ennemi,SDL_SRCCOLORKEY,SDL_MapRGB(Ennemi->format,0,0,255));
        SDL_BlitSurface(Ennemi, NULL, ecranCombat, &positionEnnemi);

        SDL_Flip(ecranCombat);
        SDL_Delay(10);
    }

    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(GoldCombat);
    SDL_FreeSurface(Ennemi);
}

void AfficherGold(SDL_Surface *ecranCombat)
{
    SDL_Surface *barre_combat = NULL, *GoldCombat = NULL;
    SDL_Rect positionBarreCombat, positionGold;
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    GoldCombat = SDL_LoadBMP("gold_combat.bmp");

    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;
    positionGold.y = 40;
    positionGold.x = 8;

    SDL_BlitSurface(barre_combat, NULL, ecranCombat, &positionBarreCombat);
    SDL_BlitSurface(GoldCombat, NULL, ecranCombat, &positionGold);

    SDL_Flip(ecranCombat);

    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(GoldCombat);
}

void AfficherJoueur(SDL_Surface *ecranCombat,Dresseur Joueur)
{
    int i;
    int n = Joueur.get_team().size();
    SDL_Surface *barre_combat = NULL, *GoldCombat = NULL, *barre_ball, *ball, *ball_vide;
    SDL_Rect positionGold, positionBarreCombat, positionBarreBall, positionBall, positionBallVide;
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    barre_ball = SDL_LoadBMP("combat_image/barre_vie.bmp");
    ball = SDL_LoadBMP("combat_image/pokeball.bmp");
    ball_vide = SDL_LoadBMP("combat_image/pokeball_vide.bmp");
    GoldCombat = SDL_LoadBMP(Joueur.get_image().data());

    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;
    positionBarreBall.x = 72;
    positionBarreBall.y = 80;

    positionGold.x = 8;
    positionGold.y = 40;

    SDL_BlitSurface(barre_combat, NULL, ecranCombat, &positionBarreCombat);
    SDL_BlitSurface(GoldCombat, NULL, ecranCombat, &positionGold);
    SDL_BlitSurface(barre_ball,NULL, ecranCombat, &positionBarreBall);

    // Afficher les pokeball des joueurs
    for (i=0;i<n;i++)
    {
        positionBall.y = 80;
        positionBall.x = 88 + i*8;
        SDL_BlitSurface(ball,NULL, ecranCombat, &positionBall);
    }
    for (i=n;i<6;i++)
    {
        positionBallVide.y = 80;
        positionBallVide.x = 88 + i*8;
        SDL_BlitSurface(ball_vide,NULL, ecranCombat, &positionBallVide);
    }

    SDL_Flip(ecranCombat);

    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(GoldCombat);
    SDL_FreeSurface(barre_ball);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(ball_vide);
}

void AfficherDresseur(SDL_Surface *ecranCombat, Dresseur Ennemi)
{
    int i;
    int m = Ennemi.get_team().size();
    SDL_Surface *DresseurEnnemi = NULL, *barre_ball_ennemi, *ball, *ball_vide;
    SDL_Rect  positionEnnemi, positionBarreBallEnnemi, positionBall, positionBallVide;
    barre_ball_ennemi = SDL_LoadBMP("combat_image/barre_inverse.bmp");
    ball = SDL_LoadBMP("combat_image/pokeball.bmp");
    ball_vide = SDL_LoadBMP("combat_image/pokeball_vide.bmp");
    DresseurEnnemi = SDL_LoadBMP(Ennemi.get_image().data());

    positionBarreBallEnnemi.x = 8;
    positionBarreBallEnnemi.y = 16;

    positionEnnemi.x =96;
    positionEnnemi.y = 0;

    SDL_SetColorKey(DresseurEnnemi,SDL_SRCCOLORKEY,SDL_MapRGB(DresseurEnnemi->format,0,0,255));
    SDL_BlitSurface(DresseurEnnemi, NULL, ecranCombat, &positionEnnemi);
    SDL_BlitSurface(barre_ball_ennemi,NULL,ecranCombat, &positionBarreBallEnnemi);

    // Afficher les pokeball des joueurs
    for (i=0;i<6-m;i++)
    {
        positionBallVide.y = 16;
        positionBallVide.x = 24 + i*8;
        SDL_BlitSurface(ball_vide,NULL, ecranCombat, &positionBallVide);
    }
    for (i=6-m;i<6;i++)
    {
        positionBall.y = 16;
        positionBall.x = 24 + i*8;
        SDL_BlitSurface(ball,NULL, ecranCombat, &positionBall);
    }

    SDL_Flip(ecranCombat);

    SDL_FreeSurface(DresseurEnnemi);
    SDL_FreeSurface(barre_ball_ennemi);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(ball_vide);
}

void PokemonJoueur(SDL_Surface *ecranCombat, Pokemon Joueur)
{
    int i = 0, barreVieJoueur = 0, vie = 0, vieMaxJoueur = 0,niveauJoueur, xpJoueur, xpMax, xpMaxPre, barreXP;
    TTF_Font *police = NULL, *policeVie = NULL;
    const char* NameJoueur = Joueur.get_nom().data();

    SDL_Surface *barre_combat = NULL, *barre_vie = NULL, *barre_joueur = NULL, *textevieJoueur = NULL, *textevieMax = NULL, *texteniveauJoueur, *NomJoueur = NULL,  *PV_actuel = NULL, *PV = NULL, *PV_moyen = NULL, *PV_faible = NULL, *XP;
    SDL_Surface *PokemonEquipe = NULL;
    SDL_Rect positionBarreCombat, positionBarreJoueur, positionTexteVie, positionTexteVieMax, positionNiveauJoueur, positionNomJoueur,  positionPokemon,  positionPV, positionXP;

    // Chargement des polices
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    policeVie = TTF_OpenFont("ttf/Pokemon_GB.ttf", 8);
    SDL_Color couleurNoire = {0,0,0};

    vie = Joueur.get_vie();
    vieMaxJoueur = Joueur.get_viemax();
    niveauJoueur = Joueur.get_niveau();
    xpJoueur = Joueur.get_xp();
    xpMax = Joueur.get_xpmax();
    xpMaxPre = Joueur.get_xpmaxpre();
    xpMax -= xpMaxPre;
    xpJoueur -= xpMaxPre;

    // Conversion de l'entier vie en caractère (int to char) pour l'afficher en tant que texte
    char buffer [20];
    char buffer2 [20];
    char buffer3 [20];
    const char* textvieJoueur = itoa(vie,buffer,10);
    const char* textvieMax = itoa(vieMaxJoueur,buffer2,10);
    const char* textniveauJoueur = itoa(niveauJoueur,buffer3,10);

    textevieJoueur = TTF_RenderText_Blended(policeVie, textvieJoueur, couleurNoire);
    textevieMax = TTF_RenderText_Blended(policeVie, textvieMax, couleurNoire);
    NomJoueur = TTF_RenderText_Blended(police, NameJoueur, couleurNoire);
    texteniveauJoueur = TTF_RenderText_Blended(policeVie, textniveauJoueur, couleurNoire);

    PokemonEquipe = SDL_LoadBMP(Joueur.get_imageback().data());

    // Définit toutes les positions des images
    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;

    positionBarreJoueur.x = 72;
    positionBarreJoueur.y = 56;

    positionTexteVie.x = 96;
    positionTexteVie.y = 81;
    if (vie > 99)
    {
        positionTexteVie.x = 88;
    }

    positionTexteVieMax.x = 128;
    positionTexteVieMax.y = 81;
    if (vieMaxJoueur > 99)
    {
        positionTexteVieMax.x = 120;
    }

    positionNiveauJoueur.x = 120;
    positionNiveauJoueur.y = 66;

    positionNomJoueur.x = 80;
    positionNomJoueur.y = 52;

    positionPokemon.x = 8;
    positionPokemon.y = 40;

    positionPV.x = 96;
    int PVx = positionPV.x;
    positionPV.y = 75;

    positionXP.x = 143;
    int XPx = positionXP.x;
    positionXP.y = 91;

    // Chargement des images
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    barre_vie = SDL_LoadBMP("combat_image/barre_vie.bmp");
    barre_joueur = SDL_LoadBMP("combat_image/barre_joueur.bmp");
    PV = SDL_LoadBMP("combat_image/vie.bmp");
    PV_moyen = SDL_LoadBMP("combat_image/vie_moyenne.bmp");
    PV_faible = SDL_LoadBMP("combat_image/vie_critique.bmp");
    XP = SDL_LoadBMP("combat_image/xp.bmp");

    SDL_BlitSurface(barre_combat, NULL, ecranCombat, &positionBarreCombat);
    SDL_BlitSurface(barre_joueur, NULL, ecranCombat, &positionBarreJoueur);
    SDL_BlitSurface(texteniveauJoueur,NULL,ecranCombat, &positionNiveauJoueur);
    SDL_SetColorKey(PokemonEquipe,SDL_SRCCOLORKEY,SDL_MapRGB(PokemonEquipe->format,0,0,255));
    SDL_BlitSurface(PokemonEquipe, NULL, ecranCombat, &positionPokemon);
    SDL_BlitSurface(NomJoueur, NULL, ecranCombat, &positionNomJoueur);
    SDL_BlitSurface(textevieJoueur, NULL, ecranCombat, &positionTexteVie);
    SDL_BlitSurface(textevieMax, NULL, ecranCombat, &positionTexteVieMax);

    // Mise à jour de la longueur de la barre de vie en fonction de la vie actuelle
    // Calcul via le produit en croix vie/vieMax = barreDeVie/barreDeVieMax
    barreVieJoueur = (int) floor(vie*TAILLE_BARRE_VIE/vieMaxJoueur);

    if (barreVieJoueur > 24)
    {
        PV_actuel = PV;
    }
    else if (barreVieJoueur < 8)
    {
        PV_actuel = PV_faible;
    }
    else
    {
        PV_actuel = PV_moyen;
    }

    for (i=0; i<barreVieJoueur;i++)
    {
        positionPV.x = PVx+i;
        SDL_BlitSurface(PV_actuel, NULL, ecranCombat, &positionPV);
    }

    barreXP = (int) floor(xpJoueur*TAILLE_BARRE_XP/xpMax);

    for (i=0; i<barreXP;i++)
    {
        positionXP.x = XPx-i;
        SDL_BlitSurface(XP, NULL, ecranCombat, &positionXP);
    }

    // Mise à jour de l'écran
    SDL_Flip(ecranCombat);
    // Libération des surfaces
    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(barre_vie);
    SDL_FreeSurface(barre_joueur);
    SDL_FreeSurface(NomJoueur);
    SDL_FreeSurface(PV);
    SDL_FreeSurface(PV_actuel);
    SDL_FreeSurface(PV_moyen);
    SDL_FreeSurface(PV_faible);
    SDL_FreeSurface(textevieJoueur);
    SDL_FreeSurface(textevieMax);
    SDL_FreeSurface(texteniveauJoueur);
    SDL_FreeSurface(XP);
}

void PokemonEnnemi(SDL_Surface *ecranCombat, Pokemon Ennemi)
{
    int i = 0, barreVieEnnemi = 0, vieEnnemi = 0, vieMaxEnnemi = 0, niveauEnnemi;
    TTF_Font *police = NULL, *policeVie = NULL;
    const char* NameEnnemi = Ennemi.get_nom().data();

    SDL_Surface *barre_combat = NULL, *barre_ennemi = NULL, *texteniveauEnnemi, *NomEnnemi = NULL, *PV_actuel = NULL, *PV = NULL, *PV_moyen = NULL, *PV_faible = NULL, *PokemonSauvage = NULL;
    SDL_Rect positionBarreCombat, positionBarreEnnemi, positionNiveauEnnemi, positionNomEnnemi, positionPokemonSauvage, positionPVEnnemi;

    // Chargement des polices
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    policeVie = TTF_OpenFont("ttf/Pokemon_GB.ttf", 8);
    SDL_Color couleurNoire = {0,0,0};

    vieEnnemi = Ennemi.get_vie();
    vieMaxEnnemi = Ennemi.get_viemax();
    niveauEnnemi = Ennemi.get_niveau();

    char buffer [20];
    const char* textniveauEnnemi = itoa(niveauEnnemi,buffer,10);

    NomEnnemi = TTF_RenderText_Blended(police, NameEnnemi, couleurNoire);
    texteniveauEnnemi = TTF_RenderText_Blended(policeVie, textniveauEnnemi, couleurNoire);

    PokemonSauvage = SDL_LoadBMP(Ennemi.get_imagefront().data());

    // Définit toutes les positions des images
    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;

    positionBarreEnnemi.x = 8;
    positionBarreEnnemi.y = 0;

    positionNiveauEnnemi.x = 56;
    positionNiveauEnnemi.y = 9;

    positionNomEnnemi.x = 9;
    positionNomEnnemi.y = -4;

    positionPokemonSauvage.x = 96;
    positionPokemonSauvage.y = 0;

    positionPVEnnemi.x = 32;
    int PVEnnemix = positionPVEnnemi.x;
    positionPVEnnemi.y = 19;

    // Chargement des images
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    barre_ennemi = SDL_LoadBMP("combat_image/barre_ennemi.bmp");
    PV = SDL_LoadBMP("combat_image/vie.bmp");
    PV_moyen = SDL_LoadBMP("combat_image/vie_moyenne.bmp");
    PV_faible = SDL_LoadBMP("combat_image/vie_critique.bmp");

    SDL_BlitSurface(barre_combat, NULL, ecranCombat, &positionBarreCombat);
    SDL_BlitSurface(barre_ennemi, NULL, ecranCombat, &positionBarreEnnemi);
    SDL_BlitSurface(texteniveauEnnemi, NULL, ecranCombat, &positionNiveauEnnemi);
    SDL_SetColorKey(PokemonSauvage,SDL_SRCCOLORKEY,SDL_MapRGB(PokemonSauvage->format,0,0,255));
    SDL_BlitSurface(PokemonSauvage, NULL, ecranCombat, &positionPokemonSauvage);
    SDL_BlitSurface(NomEnnemi, NULL, ecranCombat, &positionNomEnnemi);

    // Mise à jour de la longueur de la barre de vie en fonction de la vie actuelle
    // Calcul via le produit en croix vie/vieMax = barreDeVie/barreDeVieMax
    barreVieEnnemi = (int) floor(vieEnnemi*TAILLE_BARRE_VIE/vieMaxEnnemi);

    if (barreVieEnnemi > 24)
    {
        PV_actuel = PV;
    }
    else if (barreVieEnnemi < 8)
    {
        PV_actuel = PV_faible;
    }
    else
    {
        PV_actuel = PV_moyen;
    }

    for (i=0; i<barreVieEnnemi;i++)
    {
        positionPVEnnemi.x = PVEnnemix+i;
        SDL_BlitSurface(PV_actuel, NULL, ecranCombat, &positionPVEnnemi);
    }
    // Mise à jour de l'écran
    SDL_Flip(ecranCombat);
    // Libération des surfaces
    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(barre_ennemi);
    SDL_FreeSurface(NomEnnemi);
    SDL_FreeSurface(PV);
    SDL_FreeSurface(PV_actuel);
    SDL_FreeSurface(PV_moyen);
    SDL_FreeSurface(PV_faible);
    SDL_FreeSurface(texteniveauEnnemi);
}

void AfficherCombat(SDL_Surface *ecranCombat, Pokemon Joueur, Pokemon Ennemi)
{
    int i = 0, barreVieJoueur = 0, barreVieEnnemi = 0, barreXP;
    int vie = 0, vieEnnemi = 0, vieMaxJoueur = 0, vieMaxEnnemi = 0, niveauJoueur, niveauEnnemi, xpJoueur, xpMax, xpMaxPre;
    TTF_Font *police = NULL, *policeVie = NULL;
    const char* NameJoueur = Joueur.get_nom().data();
    const char* NameEnnemi = Ennemi.get_nom().data();

    SDL_Surface *barre_combat = NULL, *barre_vie = NULL, *barre_ennemi = NULL, *barre_joueur = NULL, *textevieJoueur = NULL, *textevieMax = NULL, *texteniveauJoueur, *texteniveauEnnemi, *NomJoueur = NULL, *NomEnnemi = NULL, *PV_actuel = NULL, *PV = NULL, *PV_moyen = NULL, *PV_faible = NULL, *XP;
    SDL_Surface *PokemonEquipe = NULL, *PokemonSauvage = NULL;
    SDL_Rect positionBarreCombat, positionBarreEnnemi, positionBarreJoueur, positionTexteVie, positionTexteVieMax, positionNiveauJoueur, positionNiveauEnnemi, positionNomJoueur, positionNomEnnemi, positionPokemon, positionPokemonSauvage, positionPV, positionPVEnnemi, positionXP;

    // Chargement des polices
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    policeVie = TTF_OpenFont("ttf/Pokemon_GB.ttf", 8);
    SDL_Color couleurNoire = {0,0,0};

    vie = Joueur.get_vie();
    vieEnnemi = Ennemi.get_vie();
    vieMaxJoueur = Joueur.get_viemax();
    vieMaxEnnemi = Ennemi.get_viemax();
    niveauJoueur = Joueur.get_niveau();
    niveauEnnemi = Ennemi.get_niveau();
    xpJoueur = Joueur.get_xp();
    xpMax = Joueur.get_xpmax();
    xpMaxPre = Joueur.get_xpmaxpre();
    xpMax -= xpMaxPre;
    xpJoueur -= xpMaxPre;

    // Conversion de l'entier vie en caractère (int to char) pour l'afficher en tant que texte
    char buffer [20];
    char buffer2 [20];
    char buffer3 [20];
    char buffer4 [20];
    const char* textvieJoueur = itoa(vie,buffer,10);
    const char* textvieMax = itoa(vieMaxJoueur,buffer2,10);
    const char* textniveauJoueur = itoa(niveauJoueur,buffer3,10);
    const char* textniveauEnnemi = itoa(niveauEnnemi,buffer4,10);

    textevieJoueur = TTF_RenderText_Blended(policeVie, textvieJoueur, couleurNoire);
    textevieMax = TTF_RenderText_Blended(policeVie, textvieMax, couleurNoire);
    NomJoueur = TTF_RenderText_Blended(police, NameJoueur, couleurNoire);
    NomEnnemi = TTF_RenderText_Blended(police, NameEnnemi, couleurNoire);
    texteniveauJoueur = TTF_RenderText_Blended(policeVie, textniveauJoueur, couleurNoire);
    texteniveauEnnemi = TTF_RenderText_Blended(policeVie, textniveauEnnemi, couleurNoire);

    PokemonEquipe = SDL_LoadBMP(Joueur.get_imageback().data());
    PokemonSauvage = SDL_LoadBMP(Ennemi.get_imagefront().data());

    // Définit toutes les positions des images
    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;

    positionBarreEnnemi.x = 8;
    positionBarreEnnemi.y = 0;

    positionBarreJoueur.x = 72;
    positionBarreJoueur.y = 56;


    positionTexteVie.x = 96;
    positionTexteVie.y = 81;
    if (vie > 99)
    {
        positionTexteVie.x = 88;
    }

    positionTexteVieMax.x = 128;
    positionTexteVieMax.y = 81;
    if (vieMaxJoueur > 99)
    {
        positionTexteVieMax.x = 120;
    }

    positionNiveauJoueur.x = 120;
    positionNiveauJoueur.y = 66;

    positionNiveauEnnemi.x = 56;
    positionNiveauEnnemi.y = 9;

    positionNomJoueur.x = 80;
    positionNomJoueur.y = 52;

    positionNomEnnemi.x = 9;
    positionNomEnnemi.y = -4;

    positionPokemon.x = 8;
    positionPokemon.y = 40;

    positionPokemonSauvage.x = 96;
    positionPokemonSauvage.y = 0;

    positionXP.x = 143;
    int XPx = positionXP.x;
    positionXP.y = 91;

    positionPV.x = 96;
    int PVx = positionPV.x;
    positionPV.y = 75;

    positionPVEnnemi.x = 32;
    int PVEnnemix = positionPVEnnemi.x;
    positionPVEnnemi.y = 19;

    // Chargement des images
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    barre_vie = SDL_LoadBMP("combat_image/barre_vie.bmp");
    barre_joueur = SDL_LoadBMP("combat_image/barre_joueur.bmp");
    barre_ennemi = SDL_LoadBMP("combat_image/barre_ennemi.bmp");
    PV = SDL_LoadBMP("combat_image/vie.bmp");
    PV_moyen = SDL_LoadBMP("combat_image/vie_moyenne.bmp");
    PV_faible = SDL_LoadBMP("combat_image/vie_critique.bmp");
    XP = SDL_LoadBMP("combat_image/xp.bmp");

    // On efface l'écran
    SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));

    SDL_BlitSurface(barre_combat, NULL, ecranCombat, &positionBarreCombat);
    SDL_BlitSurface(barre_joueur, NULL, ecranCombat, &positionBarreJoueur);
    SDL_BlitSurface(barre_ennemi, NULL, ecranCombat, &positionBarreEnnemi);
    SDL_BlitSurface(texteniveauJoueur,NULL,ecranCombat, &positionNiveauJoueur);
    SDL_BlitSurface(texteniveauEnnemi,NULL,ecranCombat, &positionNiveauEnnemi);
    SDL_SetColorKey(PokemonEquipe,SDL_SRCCOLORKEY,SDL_MapRGB(PokemonEquipe->format,0,0,255));
    SDL_BlitSurface(PokemonEquipe, NULL, ecranCombat, &positionPokemon);
    SDL_SetColorKey(PokemonSauvage,SDL_SRCCOLORKEY,SDL_MapRGB(PokemonSauvage->format,0,0,255));
    SDL_BlitSurface(PokemonSauvage, NULL, ecranCombat, &positionPokemonSauvage);
    SDL_BlitSurface(NomJoueur, NULL, ecranCombat, &positionNomJoueur);
    SDL_BlitSurface(NomEnnemi, NULL, ecranCombat, &positionNomEnnemi);
    SDL_BlitSurface(textevieJoueur, NULL, ecranCombat, &positionTexteVie);
    SDL_BlitSurface(textevieMax, NULL, ecranCombat, &positionTexteVieMax);

    // Mise à jour de la longueur de la barre de vie en fonction de la vie actuelle
    // Calcul via le produit en croix vie/vieMax = barreDeVie/barreDeVieMax
    barreVieJoueur = (int) floor(vie*TAILLE_BARRE_VIE/vieMaxJoueur);

    if (barreVieJoueur > 24)
    {
        PV_actuel = PV;
    }
    else if (barreVieJoueur < 8)
    {
        PV_actuel = PV_faible;
    }
    else
    {
        PV_actuel = PV_moyen;
    }

    for (i=0; i<barreVieJoueur;i++)
    {
        positionPV.x = PVx+i;
        SDL_BlitSurface(PV_actuel, NULL, ecranCombat, &positionPV);
    }

    barreVieEnnemi = (int) floor(vieEnnemi*TAILLE_BARRE_VIE/vieMaxEnnemi);

    if (barreVieEnnemi > 24)
    {
        PV_actuel = PV;
    }
    else if (barreVieEnnemi < 8)
    {
        PV_actuel = PV_faible;
    }
    else
    {
        PV_actuel = PV_moyen;
    }

    for (i=0; i<barreVieEnnemi;i++)
    {
        positionPVEnnemi.x = PVEnnemix+i;
        SDL_BlitSurface(PV_actuel, NULL, ecranCombat, &positionPVEnnemi);
    }

    barreXP = (int) floor(xpJoueur*TAILLE_BARRE_XP/xpMax);

    for (i=0; i<barreXP;i++)
    {
        positionXP.x = XPx-i;
        SDL_BlitSurface(XP, NULL, ecranCombat, &positionXP);
    }

    // Mise à jour de l'écran
    SDL_Flip(ecranCombat);
    // Libération des surfaces
    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(barre_vie);
    SDL_FreeSurface(barre_ennemi);
    SDL_FreeSurface(barre_joueur);
    SDL_FreeSurface(NomJoueur);
    SDL_FreeSurface(NomEnnemi);
    SDL_FreeSurface(PV);
    SDL_FreeSurface(PV_actuel);
    SDL_FreeSurface(PV_moyen);
    SDL_FreeSurface(PV_faible);
    SDL_FreeSurface(textevieJoueur);
    SDL_FreeSurface(textevieMax);
    SDL_FreeSurface(texteniveauJoueur);
    SDL_FreeSurface(texteniveauEnnemi);
    SDL_FreeSurface(XP);
}

void AfficherChoixAttaque(SDL_Surface *ecranCombat, Pokemon Joueur, Pokemon Ennemi, int posPointeur)
{
    TTF_Font *police = NULL;
    const char* text1 = Joueur.get_attaque()[0].get_nom().data();
    SDL_Surface *barre_attaque = NULL, *texte = NULL, *texte2 = NULL, *texte3 = NULL, *texte4 = NULL, *pointeur = NULL;
    SDL_Rect positionBarreAttaque, positionTexte, positionTexte2, positionTexte3, positionTexte4, positionPointeur;

    // Chargement des polices
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    SDL_Color couleurNoire = {0,0,0};

    texte = TTF_RenderText_Blended(police, text1, couleurNoire);


    // Définit toutes les positions des images

    positionBarreAttaque.x = 32;
    positionBarreAttaque.y = 96;

    positionTexte.x = 48;
    positionTexte.y = 100;

    positionTexte2.x = 48;
    positionTexte2.y = 108;

    positionTexte3.x = 48;
    positionTexte3.y = 116;

    positionTexte4.x = 48;
    positionTexte4.y = 124;

    barre_attaque = SDL_LoadBMP("combat_image/barre_attaque.bmp");
    pointeur = SDL_LoadBMP("combat_image/pointeur.bmp");

    AfficherCombat(ecranCombat,Joueur, Ennemi);

    SDL_BlitSurface(barre_attaque, NULL, ecranCombat, &positionBarreAttaque);
    SDL_BlitSurface(texte, NULL, ecranCombat, &positionTexte);

    if (Joueur.get_attaque().size()>1)
    {
        const char* text2 = Joueur.get_attaque()[1].get_nom().data();
        texte2 = TTF_RenderText_Blended(police, text2, couleurNoire);
        SDL_BlitSurface(texte2, NULL, ecranCombat, &positionTexte2);
    }
    if (Joueur.get_attaque().size()>2)
    {
        const char* text3 = Joueur.get_attaque()[2].get_nom().data();
        texte3 = TTF_RenderText_Blended(police, text3, couleurNoire);
        SDL_BlitSurface(texte3, NULL, ecranCombat, &positionTexte3);
    }
    if (Joueur.get_attaque().size()>3)
    {
        const char* text4 = Joueur.get_attaque()[3].get_nom().data();
        texte4 = TTF_RenderText_Blended(police, text4, couleurNoire);
        SDL_BlitSurface(texte4, NULL, ecranCombat, &positionTexte4);
    }

    positionPointeur.x = 40;
    if (posPointeur == 0)
    {
        positionPointeur.y = 104;
        SDL_BlitSurface(pointeur, NULL, ecranCombat, &positionPointeur);
    }
    else if (posPointeur == 1)
    {
        positionPointeur.y = 112;
        SDL_BlitSurface(pointeur, NULL, ecranCombat, &positionPointeur);
    }
    else if (posPointeur == 2)
    {
        positionPointeur.y = 120;
        SDL_BlitSurface(pointeur, NULL, ecranCombat, &positionPointeur);
    }
    else if (posPointeur == 3)
    {
        positionPointeur.y = 128;
        SDL_BlitSurface(pointeur, NULL, ecranCombat, &positionPointeur);
    }

    // Mise à jour de l'écran
    SDL_Flip(ecranCombat);
    // Libération des surfaces
    SDL_FreeSurface(barre_attaque);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    SDL_FreeSurface(texte3);
    SDL_FreeSurface(texte4);
    SDL_FreeSurface(pointeur);
}

void Texte(SDL_Surface *ecranCombat, const char* texte1, const char* texte2)
{
    TTF_Font *police = NULL;
    SDL_Surface *txt1, *txt2, *barre_combat;
    SDL_Rect positionTexte1, positionTexte2, positionBarreCombat;

    positionTexte1.x = 8;
    positionTexte1.y = 108;
    positionTexte2.x = 8;
    positionTexte2.y = 124;
    positionBarreCombat.x = 0;
    positionBarreCombat.y = 96;

    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");

    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    SDL_Color couleurNoire = {0,0,0};

    txt1 = TTF_RenderText_Blended(police, texte1, couleurNoire);
    txt2 = TTF_RenderText_Blended(police, texte2, couleurNoire);

    SDL_BlitSurface(barre_combat,NULL,ecranCombat,&positionBarreCombat);
    SDL_BlitSurface(txt1,NULL,ecranCombat,&positionTexte1);
    SDL_BlitSurface(txt2,NULL,ecranCombat,&positionTexte2);
    SDL_Flip(ecranCombat);

    SDL_FreeSurface(txt1);
    SDL_FreeSurface(txt2);
    SDL_FreeSurface(barre_combat);
}

void Curseur(SDL_Surface *ecranCombat)
{
    SDL_Surface *curseur;
    SDL_Rect positionCurseur;
    curseur = SDL_LoadBMP("curseur_suite.bmp");
    positionCurseur.x = 144;
    positionCurseur.y = 136;
    SDL_BlitSurface(curseur, NULL, ecranCombat, &positionCurseur);
    SDL_Flip(ecranCombat);
    SDL_FreeSurface(curseur);
}

void TourAttaque(SDL_Surface *ecranCombat,Pokemon &Attaquant1, Pokemon &Attaquant2, int Attack1, int Attack2)
{
    const char* vide = "";
    const char* critique = "Coup Critique !";
    const char* efficace = "C'est super efficace!";
    const char* rate = "rate son attaque";
    const char* inefficace1 = "Ce n'est pas";
    const char* inefficace2 = "très efficace...";

    float coeffType[17*17] =
    //                                                 E               T
    //                         I   S                   L               E
    // N   C       P           N   P       P           E           D   N
    // O   O       O       R   S   E   A   L           C       G   R   E
    // R   M       I       O   E   C   C   A           T       L   A   B
    // M   B   V   S   S   C   C   T   I   N   F   E   R   P   A   G   R
    // A   A   O   O   O   H   T   R   E   T   E   A   I   S   C   O   E
    // L   T   L   N   L   E   E   E   R   E   U   U   K   Y   E   N   S
    {  1,  2,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,   //NORMAL
	   1,  1,  2,  1,  1,0.5,0.5,  1,  1,  1,  1,  1,  1,  2,  1,  1,0.5,   //COMBAT
	   1,0.5,  1,  1,  0,  2,0.5,  1,  1,0.5,  1,  1,  2,  1,  2,  1,  1,   //VOL
	   1,0.5,  1,0.5,  2,  1,0.5,  1,  1,0.5,  1,  1,  1,  2,  1,  1,  1,   //POISON
       1,  1,  1,0.5,  1,0.5,  1,  1,  1,  2,  1,  2,  0,  1,  2,  1,  1,   //SOL
     0.5,  2,0.5,0.5,  2,  1,  1,  1,  2,  2,0.5,  2,  1,  1,  1,  1,  1,   //ROCHE
       1,0.5,  2,  1,0.5,  2,  1,  1,  1,0.5,  2,  1,  1,  1,  1,  1,  1,   //INSECTE
       0,  0,  1,0.5,  1,  1,0.5,  2,  1,  1,  1,  1,  1,  1,  1,  1,  2,   //SPECTRE
     0.5,  2,0.5,  0,  2,0.5,0.5,  1,0.5,0.5,  2,  1,  1,0.5,0.5,  1,  1,   //ACIER
       1,  1,  2,  2,0.5,  1,  2,  1,  1,0.5,  2,0.5,0.5,  1,  2,  1,  1,   //PLANTE
       1,  1,  1,  1,  2,  2,0.5,  1,0.5,0.5,0.5,  2,  1,  1,0.5,  1,  1,   //FEU
       1,  1,  1,  1,  1,  1,  1,  1,0.5,  2,0.5,0.5,  2,  1,0.5,  1,  1,   //EAU
       1,  1,0.5,  1,  2,  1,  1,  1,0.5,  1,  1,  1,0.5,  1,  1,  1,  1,   //ELECTRIK
       1,0.5,  1,  1,  1,  1,  2,  2,  1,  1,  1,  1,  1,0.5,  1,  1,  2,   //PSY
       1,  2,  1,  1,  1,  2,  1,  1,  2,  1,  2,  1,  1,  1,0.5,  1,  1,   //GLACE
       1,  1,  1,  1,  1,  1,  1,  1,  1,0.5,0.5,0.5,0.5,  1,  2,  2,  1,   //DRAGON
       1,  2,  1,  1,  1,  1,  2,0.5,  1,  1,  1,  1,  1,  0,  1,  1,0.5};  //TENEBRES

    // Coefficient d'atténuation de l'attaque
    float coeffAttaque, coeffTypePoke, randPrecision;
    int Critique, randCritique;

    if (Attaquant1.get_attaque()[Attack1].get_type()==Attaquant1.get_type())
    {
        coeffTypePoke = 1.5;
    }
    else
    {
        coeffTypePoke = 1;
    }

    // Le coefficient atténue l'attaque entre 0.85 et 1
    coeffAttaque = (float)(rand()% 38 + 217)/255;

    randCritique = rand()% 10000 + 1;
    randPrecision = (float) (rand()% 100 + 1);
    if (randCritique < 626)
    {
        Critique = 2;
    }
    else
    {
        Critique = 1;
    }

    if ((randPrecision <= Attaquant1.get_attaque()[Attack1].get_precision()*Attaquant1.get_precision()) and (Attaquant1.get_attaque()[Attack1].is_effect()==false))
    {
        Attaquant2.degat_recu((int)Attaquant1.calcul_degat(Attaquant1.get_attaque()[Attack1],Attaquant2.get_def(Attaquant1.get_attaque()[Attack1]))*coeffAttaque*coeffType[Attaquant1.get_attaque()[Attack1].get_type()+Attaquant2.get_type()*17]*coeffTypePoke*Critique);
        if (Critique == 2)
        {
            Texte(ecranCombat,critique,vide);
            SDL_Delay(500);
        }
        if (coeffType[Attaquant1.get_attaque()[Attack1].get_type()+Attaquant2.get_type()*17]>1)
        {
            Texte(ecranCombat,efficace,vide);
            SDL_Delay(500);
        }
        else if (coeffType[Attaquant1.get_attaque()[Attack1].get_type()+Attaquant2.get_type()*17]<1)
        {
            Texte(ecranCombat,inefficace1,inefficace2);
            SDL_Delay(500);
        }
    }
    else if (randPrecision >= Attaquant1.get_attaque()[Attack1].get_precision()*Attaquant1.get_precision())
    {
        Texte(ecranCombat,rate,vide);
        SDL_Delay(500);
    }

    if (Attaquant1.get_attaque()[Attack1].is_effect()==true)
    {
        if (Attaquant1.get_attaque()[Attack1].get_bonus()<0)
        {
            if (Attaquant1.get_attaque()[Attack1].get_stat()==PREC)
            {
                Attaquant2.change_precision(Attaquant1.get_attaque()[Attack1].get_bonus());
            }
            else
            {
                Attaquant2.change_stat(Attaquant1.get_attaque()[Attack1].get_stat(),Attaquant1.get_attaque()[Attack1].get_bonus());
            }
        }
        else
        {
            if (Attaquant1.get_attaque()[Attack1].get_stat()==PREC)
            {
                Attaquant1.change_precision(Attaquant1.get_attaque()[Attack1].get_bonus());
            }
            else
            {
                Attaquant1.change_stat(Attaquant1.get_attaque()[Attack1].get_stat(),Attaquant1.get_attaque()[Attack1].get_bonus());
            }
        }
    }
}

void combat(Pokemon &Joueur, Pokemon &Ennemi)
{
    SDL_Surface *ecranCombat = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    int attaqueAlea = 0, posPointeur = 0, fuite = 1, AttaqueSize = Joueur.get_attaque().size();
    SDL_Event event;

    //SDL_Rect positionGold, positionEnnemi;

    Mix_Music *MusicVictory;
    MusicVictory = Mix_LoadMUS("music/PkmRS_Victory.mid");

    Mix_AllocateChannels(2);
    Mix_Chunk *criJoueur, *criEnnemi;
    Mix_Volume(1,MIX_MAX_VOLUME/2);
    Mix_Volume(0,MIX_MAX_VOLUME/2);

    criJoueur = Mix_LoadWAV(Joueur.get_cry().data());
    criEnnemi = Mix_LoadWAV(Ennemi.get_cry().data());

    std::vector<const char*> AttackNameJoueur;
    std::vector<const char*> AttackNameEnnemi;
    // Déclaration des string
    std::string NomJoueur = Joueur.get_nom();
    std::string NomEnnemi = Ennemi.get_nom();
    NomEnnemi.append(" ennemi");

    std::string start = "Un ";
    std::string GO;
    std::string ATKJ1;
    std::string ATKJ2;
    std::string ATKJ3;
    std::string ATKJ4;
    std::string ATKE1;
    std::string ATKE2;
    std::string ATKE3;
    std::string ATKE4;
    // Ajout du nom du Pokemon au string
    start.append(NomEnnemi);
    GO.append(NomJoueur);
    ATKE1.append("lance ");
    ATKE2.append("lance ");
    ATKE3.append("lance ");
    ATKE4.append("lance ");
    ATKJ1.append("lance ");
    ATKJ2.append("lance ");
    ATKJ3.append("lance ");
    ATKJ4.append("lance ");

    // Conversion des string en const char avec la fonction data()
    const char* vide = "";
    // Noms des attaques
    const char* ATKJoueur1 = (ATKJ1.append(Joueur.get_attaque()[0].get_nom())).data();
    AttackNameJoueur.push_back(ATKJoueur1);
    const char* ATKEnnemi1 = (ATKE1.append(Ennemi.get_attaque()[0].get_nom())).data();
    AttackNameEnnemi.push_back(ATKEnnemi1);

    if (Joueur.get_attaque().size()>1)
    {
        const char* ATKJoueur2 = (ATKJ2.append(Joueur.get_attaque()[1].get_nom())).data();
        AttackNameJoueur.push_back(ATKJoueur2);
    }
    if (Joueur.get_attaque().size()>2)
    {
        const char* ATKJoueur3 = (ATKJ3.append(Joueur.get_attaque()[2].get_nom())).data();
        AttackNameJoueur.push_back(ATKJoueur3);
    }
    if (Joueur.get_attaque().size()>3)
    {
        const char* ATKJoueur4 = (ATKJ4.append(Joueur.get_attaque()[3].get_nom())).data();
        AttackNameJoueur.push_back(ATKJoueur4);
    }
    if (Ennemi.get_attaque().size()>1)
    {
        const char* ATKEnnemi2 = (ATKE2.append(Ennemi.get_attaque()[1].get_nom())).data();
        AttackNameEnnemi.push_back(ATKEnnemi2);
    }
    if (Ennemi.get_attaque().size()>2)
    {
        const char* ATKEnnemi3 = (ATKE3.append(Ennemi.get_attaque()[2].get_nom())).data();
        AttackNameEnnemi.push_back(ATKEnnemi3);
    }
    if (Ennemi.get_attaque().size()>3)
    {
        const char* ATKEnnemi4 = (ATKE4.append(Ennemi.get_attaque()[3].get_nom())).data();
        AttackNameEnnemi.push_back(ATKEnnemi4);
    }

    // "Pokemon est KO"
    const char* KO = "est KO!";
    // "En avant Pokemon"
    const char* JoueurGO = (GO.append("! Go!").data());

    const char* Fuite1 = "Vous prenez la";
    const char* Fuite2 = "fuite !";

    // Affiche la fenetre de combat avec la pharse "En avant -Nom du Pokemon du joueur- !"
    AfficherCombat(ecranCombat,Joueur, Ennemi);
    Texte(ecranCombat,JoueurGO,vide);
    SDL_Delay(500);
    Mix_PlayChannel(1, criJoueur, 0);
    SDL_Delay(500);

    Input inCombat;
    // Le combat dure jusqu'à ce qu'un des Pokemon n'ait plus de points de vie
    // Chaque Pokemon possède 2 attaques, le joueur peut les lancer via les touches 1 et 2
	while ((Joueur.get_vie()>0 and Ennemi.get_vie()>0) and (fuite))
	{
	    AfficherChoixAttaque(ecranCombat,Joueur, Ennemi, posPointeur);
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_BACKSPACE:
                        fuite = 0;
                    break;
                    case SDLK_DOWN:
                        if (posPointeur == AttaqueSize-1)
                        {
                            posPointeur = 0;
                        }
                        else
                        {
                            posPointeur += 1;
                        }
                        AfficherChoixAttaque(ecranCombat,Joueur, Ennemi, posPointeur);
                    break;
                    case SDLK_UP:
                        if (posPointeur == 0)
                        {
                            posPointeur = AttaqueSize-1;
                        }
                        else
                        {
                            posPointeur -= 1;
                        }
                        AfficherChoixAttaque(ecranCombat,Joueur, Ennemi, posPointeur);
                    break;
                    case SDLK_SPACE:
                        // Nombre aléatoire sur l'attaque de l'ennemi
                        attaqueAlea = rand()%Ennemi.get_attaque().size();
                        if (Joueur.get_vitesse()<Ennemi.get_vitesse())
                        {
                            // Affiche l'attaque lancée par le premier attaquant
                            AfficherCombat(ecranCombat,Joueur, Ennemi);
                            Texte(ecranCombat,NomEnnemi.data(), AttackNameEnnemi[attaqueAlea]);
                            SDL_Delay(500);
                            TourAttaque(ecranCombat,Ennemi,Joueur,attaqueAlea,posPointeur);
                            AfficherCombat(ecranCombat,Joueur, Ennemi);
                            Texte(ecranCombat,NomEnnemi.data(), AttackNameEnnemi[attaqueAlea]);
                            SDL_Delay(500);
                            if (Joueur.get_vie()>0)
                            {
                                // Affiche l'attaque lancée par le second attaquant
                                AfficherCombat(ecranCombat,Joueur, Ennemi);
                                Texte(ecranCombat,NomJoueur.data(), AttackNameJoueur[posPointeur]);
                                SDL_Delay(500);
                                TourAttaque(ecranCombat,Joueur,Ennemi,posPointeur,attaqueAlea);
                                AfficherCombat(ecranCombat,Joueur, Ennemi);
                                Texte(ecranCombat,NomJoueur.data(), AttackNameJoueur[posPointeur]);
                                SDL_Delay(500);
                            }
                        }
                        else
                        {
                            // Affiche l'attaque lancée par le premier attaquant
                            AfficherCombat(ecranCombat,Joueur, Ennemi);
                            Texte(ecranCombat,NomJoueur.data(), AttackNameJoueur[posPointeur]);
                            SDL_Delay(500);
                            TourAttaque(ecranCombat,Joueur,Ennemi,posPointeur,attaqueAlea);
                            AfficherCombat(ecranCombat,Joueur, Ennemi);
                            Texte(ecranCombat,NomJoueur.data(), AttackNameJoueur[posPointeur]);
                            SDL_Delay(500);
                            if (Ennemi.get_vie()>0)
                            {
                                // Affiche l'attaque lancée par le second attaquant
                                AfficherCombat(ecranCombat,Joueur, Ennemi);
                                Texte(ecranCombat,NomEnnemi.data(), AttackNameEnnemi[attaqueAlea]);
                                SDL_Delay(500);
                                TourAttaque(ecranCombat,Ennemi,Joueur,attaqueAlea,posPointeur);
                                AfficherCombat(ecranCombat,Joueur, Ennemi);
                                Texte(ecranCombat,NomEnnemi.data(), AttackNameEnnemi[attaqueAlea]);
                                SDL_Delay(500);
                            }
                        }
                    break;
                    default:;
                    }
                break;
                default:;
        }
	}
	Input in1;
	// Si l'ennemi est KO
	if (Ennemi.get_vie()==0)
    {
        Mix_PlayChannel(0, criEnnemi, 0);
        SDL_Delay(1000);
        // Mise à jour des points de vie pour l'affichage
        Mix_PlayMusic(MusicVictory,-1);
        SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
        PokemonJoueur(ecranCombat,Joueur);
        Texte(ecranCombat,NomEnnemi.data(), KO);

        Joueur.give_xp(Ennemi.get_xpKO());

        while (!in1.key[SDLK_SPACE])
        {
            if (!in1.key[SDLK_SPACE])
            {
                SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
                PokemonJoueur(ecranCombat,Joueur);
                Texte(ecranCombat,NomEnnemi.data(), KO);
                Curseur(ecranCombat);
                SDL_Delay(250);
            }
            in1.UpdateEvent();
            if (!in1.key[SDLK_SPACE])
            {
                SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
                PokemonJoueur(ecranCombat,Joueur);
                Texte(ecranCombat,NomEnnemi.data(), KO);
                SDL_Delay(250);
            }
            in1.UpdateEvent();
        }
    }
    // Si le Pokemon du dresseur est KO, message de défaite
    else if (Joueur.get_vie()==0)
    {
        Mix_PlayChannel(1, criJoueur, 0);
        SDL_Delay(1000);
        SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
        PokemonEnnemi(ecranCombat, Ennemi);
        Texte(ecranCombat,NomJoueur.data(), KO);
        while (!in1.key[SDLK_SPACE])
        {
            if (!in1.key[SDLK_SPACE])
            {
                SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
                PokemonEnnemi(ecranCombat, Ennemi);
                Texte(ecranCombat,NomJoueur.data(), KO);
                Curseur(ecranCombat);
                SDL_Delay(250);
            }
            in1.UpdateEvent();
            if (!in1.key[SDLK_SPACE])
            {
                SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
                PokemonEnnemi(ecranCombat, Ennemi);
                Texte(ecranCombat,NomJoueur.data(), KO);
                SDL_Delay(250);
            }
            in1.UpdateEvent();
        }
    }
    else
    {
        AfficherCombat(ecranCombat,Joueur, Ennemi);
        Texte(ecranCombat,Fuite1,Fuite2);
        SDL_Delay(1000);
    }

    Joueur.reset_stats();
    Ennemi.reset_stats();

    Mix_FreeChunk(criJoueur);
    Mix_FreeChunk(criEnnemi);
    Mix_FreeMusic(MusicVictory);
}

void combatPokemon(Pokemon &Joueur, Pokemon &Ennemi)
{
    SDL_Surface *ecranCombat = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    Mix_AllocateChannels(1);
    Mix_Chunk *criEnnemi;
    Mix_Volume(0,MIX_MAX_VOLUME/2);

    criEnnemi = Mix_LoadWAV(Ennemi.get_cry().data());

    std::string NomEnnemi = Ennemi.get_nom();

    std::string start = "Un ";

    // Ajout du nom du Pokemon au string
    start.append(NomEnnemi);

    // "Pokemon apparait"
    const char* apparait = "sauvage apparaît!";

    // Affiche la fenetre de combat avec la pharse "Un -Nom du Pokemon adverse- sauvage apparaît!"
    SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
    PokemonEnnemi(ecranCombat, Ennemi);
    AfficherGold(ecranCombat);
    Texte(ecranCombat,start.data(), apparait);
    SDL_Delay(500);
    Mix_PlayChannel(0, criEnnemi, 0);

    Input in;
    while (!in.key[SDLK_SPACE])
    {
        if (!in.key[SDLK_SPACE])
        {
            SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
            PokemonEnnemi(ecranCombat, Ennemi);
            AfficherGold(ecranCombat);
            Texte(ecranCombat,start.data(), apparait);
            Curseur(ecranCombat);
            SDL_Delay(250);
        }
        in.UpdateEvent();
        if (!in.key[SDLK_SPACE])
        {
            SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
            PokemonEnnemi(ecranCombat, Ennemi);
            AfficherGold(ecranCombat);
            Texte(ecranCombat,start.data(), apparait);
            SDL_Delay(250);
        }
        in.UpdateEvent();
    }

    combat(Joueur,Ennemi);

    Mix_FreeChunk(criEnnemi);
}

void combatDresseur(Dresseur &Joueur, Dresseur Ennemi)
{
    SDL_Surface *ecranCombat = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    Mix_AllocateChannels(1);
    Mix_Chunk *criEnnemi;
    Mix_Volume(0,MIX_MAX_VOLUME/2);

    criEnnemi = Mix_LoadWAV(Ennemi.get_team()[0].get_cry().data());

    std::string NomJoueur = Joueur.get_nom();
    std::string NomEnnemi = Ennemi.get_nom();

    // "Pokemon apparait"
    const char* fight = "veut se battre!";
    const char* envoie = "envoie";

    SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
    AfficherJoueur(ecranCombat,Joueur);
    AfficherDresseur(ecranCombat,Ennemi);
    Texte(ecranCombat,NomEnnemi.data(), fight);
    SDL_Delay(500);

    Input in;
    while (!in.key[SDLK_SPACE])
    {
        if (!in.key[SDLK_SPACE])
        {
            SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
            AfficherJoueur(ecranCombat,Joueur);
            AfficherDresseur(ecranCombat,Ennemi);
            Texte(ecranCombat,NomEnnemi.data(), fight);
            Curseur(ecranCombat);
            SDL_Delay(250);
        }
        in.UpdateEvent();
        if (!in.key[SDLK_SPACE])
        {
            SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
            AfficherJoueur(ecranCombat,Joueur);
            AfficherDresseur(ecranCombat,Ennemi);
            Texte(ecranCombat,NomEnnemi.data(), fight);
            SDL_Delay(250);
        }
        in.UpdateEvent();
    }

    SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
    AfficherGold(ecranCombat);

    Input in2;
    while (!in2.key[SDLK_SPACE])
    {
        if (!in2.key[SDLK_SPACE])
        {
            SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
            AfficherGold(ecranCombat);
            Texte(ecranCombat,NomEnnemi.data(), envoie);
            Curseur(ecranCombat);
            SDL_Delay(250);
        }
        in2.UpdateEvent();
        if (!in2.key[SDLK_SPACE])
        {
            SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
            AfficherGold(ecranCombat);
            Texte(ecranCombat,NomEnnemi.data(), envoie);
            SDL_Delay(250);
        }
        in2.UpdateEvent();
    }

    SDL_FillRect(ecranCombat, NULL, SDL_MapRGB(ecranCombat->format, 255, 255, 255));
    AfficherGold(ecranCombat);
    Texte(ecranCombat,envoie,Ennemi.get_team()[0].get_nom().data());
    SDL_Delay(200);
    PokemonEnnemi(ecranCombat,Ennemi.get_team()[0]);
    Texte(ecranCombat,envoie,Ennemi.get_team()[0].get_nom().data());
    SDL_Delay(500);
    Mix_PlayChannel(0, criEnnemi, 0);
    SDL_Delay(500);

    Mix_FreeChunk(criEnnemi);
}

#endif // COMBAT_H
