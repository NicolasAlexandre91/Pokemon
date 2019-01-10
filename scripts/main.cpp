#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "Attaque.h"
#include "Pokemon.h"
#include "Dresseur.h"
#include "Tile.h"
#include "Input.h"
#include "Map.h"
#include "Carte.h"
#include "Combat.h"
#include "Menu.h"
#include "Jeu.h"

#define LARGEUR_FENETRE 160
#define HAUTEUR_FENETRE 144

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

using namespace std;

void UpdateEvents(Input* in)
{
	SDL_Event event;
	in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
	in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
            in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
				in->mousebuttons[event.button.button]=0;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}

void RecupererVecteur(Input* in,int* vx,int* vy)
{
	int vitesse = 8;
	*vx = *vy = 0;
	if (in->key[SDLK_UP])
		*vy = -vitesse;
	if (in->key[SDLK_DOWN])
		*vy = vitesse;
	if (in->key[SDLK_LEFT])
		*vx = -vitesse;
	if (in->key[SDLK_RIGHT])
		*vx = vitesse;
}

int EssaiDeplacement(Map* carte,SDL_Rect* perso,int vx,int vy)
{
	SDL_Rect test;
	test = *perso;
	test.x+=vx;
	test.y+=vy;
	if (CollisionDecor(carte,&test)==0)
	{
		*perso = test;
		return 1;
	}
	return 0;
}

void Deplace(Map* carte,SDL_Rect* perso,int vx,int vy,int LARGEUR_TILE,int HAUTEUR_TILE)
{
	int i;
	/*if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE)
	{
		//Deplace(carte,perso,vx/2,vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		//Deplace(carte,perso,vx-vx/2,vy-vy/2,LARGEUR_TILE,HAUTEUR_TILE);
		return;
	}*/
	if (EssaiDeplacement(carte,perso,vx,vy)==1)
		return;
// affine
	for(i=0;i<ABS(vx);i++)
	{
		if (EssaiDeplacement(carte,perso,SGN(vx),0)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (EssaiDeplacement(carte,perso,0,SGN(vy))==0)
			break;
	}
}

void Evolue(Input* in,Map* carte,SDL_Rect* perso,int LARGEUR_TILE,int HAUTEUR_TILE)
{
	int vx,vy;
	RecupererVecteur(in,&vx,&vy);
	Deplace(carte,perso,vx,vy,LARGEUR_TILE,HAUTEUR_TILE);
}

void AfficherPerso(SDL_Rect* perso,SDL_Surface* screen,int xscroll,int yscroll, SDL_Surface* gold)
{
	SDL_Rect positionsurecran = *perso;
	positionsurecran.x -= xscroll;
	positionsurecran.y -= yscroll;
	SDL_SetColorKey(gold,SDL_SRCCOLORKEY,SDL_MapRGB(gold->format,255,255,255));
    SDL_BlitSurface(gold, NULL, screen, &positionsurecran);
	//SDL_FillRect(screen,&positionsurecran,gold[0]);
}

int main(int argc, char *argv[])
{
    // initialise SDL video
    SDL_Init( SDL_INIT_VIDEO );

    // initialise SDL TTF
    TTF_Init();

    // initialise SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    // initialise rand
    srand(time(NULL));

    ArbreCoupe.set_tile("tiles/arbre_coupe.bmp",OBSTACLE);
    ArgentaToRoute2G.set_tile("tiles/route.bmp",CHANGEMAP);
    ArgentaToRoute2D.set_tile("tiles/routebis.bmp",CHANGEMAP);
    CombatSilver.set_tile("tiles/herbe.bmp",COMBATPNJ);
    BarriereChemin.set_tile("tiles/barriere_chemin.bmp",UNIDIR);
    BarriereHerbe.set_tile("tiles/barriere_herbe.bmp",UNIDIR);
    BarriereVille.set_tile("tiles/barriere_ville.bmp",OBSTACLE);
    BiblioBlueHaut.set_tile("tiles/biblioBlue_haut.bmp",OBSTACLE);
    BiblioBlueBas.set_tile("tiles/biblioBlue_bas.bmp",OBSTACLE);
    BiblioBlueHaut2.set_tile("tiles/biblioBlue_haut2.bmp",OBSTACLE);
    BiblioBlueBas2.set_tile("tiles/biblioBlue_bas2.bmp",OBSTACLE);
    BiblioChenBas.set_tile("tiles/biblioChen_bas.bmp",TXT);
    BiblioChenHaut.set_tile("tiles/biblioChen_haut.bmp",OBSTACLE);
    BiblioRedBas.set_tile("tiles/biblioRed_bas.bmp",OBSTACLE);
    BiblioRedHaut.set_tile("tiles/biblioRed_haut.bmp",OBSTACLE);
    BiblioRedBas2.set_tile("tiles/biblioRed_bas2.bmp",OBSTACLE);
    BiblioRedHaut2.set_tile("tiles/biblioRed_haut2.bmp",OBSTACLE);
    Bloc.set_tile("tiles/bloc.bmp",OBSTACLE);
    BlueSister.set_tile("tiles/tabouretBlue.bmp",PNJ);
    ClavierSoin.set_tile("tiles/clavierSoin.bmp",OBSTACLE);
    Chen.set_tile("tiles/solChen.bmp",PNJ);
    Comptoir.set_tile("tiles/comptoirCentre.bmp",OBSTACLE);
    ComptoirHaut.set_tile("tiles/comptoirCentre_haut.bmp",OBSTACLE);
    ComptoirBas.set_tile("tiles/comptoirCentre_bas.bmp",OBSTACLE);
    ComptoirSoin.set_tile("tiles/comptoirCentre.bmp",SOIN);
    Console.set_tile("tiles/console.bmp",TXT);
    DiplomeChen.set_tile("tiles/diplomeChen.bmp",OBSTACLE);
    PNJDresseur.set_tile("tiles/herbe.bmp",PNJ);
    Eau.set_tile("tiles/eau.bmp",OBSTACLE);
    EauDroite.set_tile("tiles/eau_bord_droite.bmp",OBSTACLE);
    EauGauche.set_tile("tiles/eau_bord_gauche.bmp",OBSTACLE);
    EauHaut.set_tile("tiles/eau_bord_haut.bmp",OBSTACLE);
    EauCoinDroite.set_tile("tiles/eau_coin_droite.bmp",OBSTACLE);
    EauCoinGauche.set_tile("tiles/eau_coin_gauche.bmp",OBSTACLE);
    EcranOrdi.set_tile("tiles/ecranOrdi.bmp",OBSTACLE);
    EscalierRedBas.set_tile("tiles/escalierRed_bas.bmp",CHANGEMAP);
    EscalierRedHaut.set_tile("tiles/escalierRed_haut.bmp",CHANGEMAP);
    FauteuilCentre.set_tile("tiles/fauteuilCentre.bmp",OBSTACLE);
    FenetreBlue.set_tile("tiles/fenetreBlue.bmp",OBSTACLE);
    FenetreChen.set_tile("tiles/fenetreChen.bmp",OBSTACLE);
    FenetreRed.set_tile("tiles/fenetreRed.bmp",OBSTACLE);
    Fillette.set_tile("tiles/route_gravier.bmp",PNJ);
    FleurDroite.set_tile("tiles/fleur_droite.bmp",PASSAGE);
    FleurGauche.set_tile("tiles/fleur_gauche.bmp",PASSAGE);
    GrandToitVertGauche.set_tile("tiles/grandtoitvert_gauche.bmp",OBSTACLE);
    GrandToitVertDroite.set_tile("tiles/grandtoitvert_droite.bmp",OBSTACLE);
    GrandToitVertHautGauche.set_tile("tiles/grandtoitvert_haut_gauche.bmp",OBSTACLE);
    GrandToitVertHautDroite.set_tile("tiles/grandtoitvert_haut_droite.bmp",OBSTACLE);
    GrandToitVertBasGauche.set_tile("tiles/grandtoitvert_bas_gauche.bmp",OBSTACLE);
    GrandToitVertBasDroite.set_tile("tiles/grandtoitvert_bas_droite.bmp",OBSTACLE);
    GrandToitVertBas.set_tile("tiles/grandtoitvertbas.bmp",OBSTACLE);
    GrandToitVertBasDroitebis.set_tile("tiles/grandtoitvertbasdroite.bmp",OBSTACLE);
    GrandToitVertBasGauchebis.set_tile("tiles/grandtoitvertbasgauche.bmp",OBSTACLE);
    GrandToitVertDroitebis.set_tile("tiles/grandtoitvertdroite.bmp",OBSTACLE);
    GrandToitVertGauchebis.set_tile("tiles/grandtoitvertgauche.bmp",OBSTACLE);
    Gros.set_tile("tiles/herbe.bmp",PNJ);
    GrotteRoute2.set_tile("tiles/grotte.bmp",OBSTACLE);
    HauteHerbe.set_tile("tiles/hautesherbes.bmp",PASSAGE);
    HautesHerbes.set_tile("tiles/hautesherbes.bmp",COMBATPKM);
    HautesHerbesRoute1.set_tile("tiles/hautesherbes.bmp",CHANGEMAP);
    HautesHerbesRoute1b.set_tile("tiles/hautesherbes.bmp",CHANGEMAP);
    HautesHerbesPalette.set_tile("tiles/hautesherbes.bmp",CHANGEMAP);
    HautesHerbesPaletteb.set_tile("tiles/hautesherbes.bmp",CHANGEMAP);
    HautesHerbesBloc.set_tile("tiles/hautesherbes.bmp",OBSTACLE);
    Herbe.set_tile("tiles/herbe.bmp",PASSAGE);
    HerbeBloc.set_tile("tiles/herbe.bmp",OBSTACLE);
    HerbeRoute22.set_tile("tiles/herbe.bmp",CHANGEMAP);
    HerbeRoute22b.set_tile("tiles/herbe.bmp",CHANGEMAP);
    HerbeJadielle.set_tile("tiles/herbe.bmp",CHANGEMAP);
    HerbeJadielleb.set_tile("tiles/herbe.bmp",CHANGEMAP);
    Infirmiere.set_tile("tiles/solCentre_ombre.bmp",PNJ);
    JadielleToRoute2D.set_tile("tiles/route.bmp",CHANGEMAP);
    JadielleToRoute2G.set_tile("tiles/routebis.bmp",CHANGEMAP);
    JadielleToRoute2.set_tile("tiles/routebis.bmp",CHANGEMAP);
    LitBas.set_tile("tiles/lit_bas.bmp",SOIN);
    LitHaut.set_tile("tiles/lit_haut.bmp",SOIN);
    MaisonBas.set_tile("tiles/maison_bas.bmp",OBSTACLE);
    MaisonBasBis.set_tile("tiles/maison_basbis.bmp",OBSTACLE);
    MaisonBasDroite.set_tile("tiles/maison_bas_droite.bmp",OBSTACLE);
    MaisonBasGauche.set_tile("tiles/maison_bas_gauche.bmp",OBSTACLE);
    MaisonBasGaucheFenetre.set_tile("tiles/maison_bas_gauche_fenetre.bmp",OBSTACLE);
    MaisonBasDroiteFentre.set_tile("tiles/maison_bas_droite_fenetre.bmp",OBSTACLE);
    MaisonHautDroite.set_tile("tiles/maison_haut_droite.bmp",OBSTACLE);
    MaisonHautFenetre1.set_tile("tiles/maison_haut_fenetre1.bmp",OBSTACLE);
    MaisonHautFenetre2.set_tile("tiles/maison_haut_fenetre2.bmp",OBSTACLE);
    MaisonHauteFenetre2.set_tile("tiles/maisonhaute_fenetre2.bmp",OBSTACLE);
    MaisonHautGauche.set_tile("tiles/maison_haut_gauche.bmp",OBSTACLE);
    MaisonBriqueBas.set_tile("tiles/maisonbrique_bas.bmp",OBSTACLE);
    MaisonBriqueBasDroite.set_tile("tiles/maisonbrique_bas_droite.bmp",OBSTACLE);
    MaisonBriqueBasGauche.set_tile("tiles/maisonbrique_bas_gauche.bmp",OBSTACLE);
    MaisonBriqueFenetre1.set_tile("tiles/maisonbrique_fenetre1.bmp",OBSTACLE);
    MaisonBriqueFenetre1bis.set_tile("tiles/maisonbrique_fenetre1bis.bmp",OBSTACLE);
    MaisonBriqueFenetre2.set_tile("tiles/maisonbrique_fenetre2.bmp",OBSTACLE);
    MaisonBriqueFenetre2bis.set_tile("tiles/maisonbrique_fenetre2bis.bmp",OBSTACLE);
    MaisonBriqueHautDroite.set_tile("tiles/maisonbrique_haut_droite.bmp",OBSTACLE);
    MaisonBriqueHautGauche.set_tile("tiles/maisonbrique_haut_gauche.bmp",OBSTACLE);
    MaisonToitBasGauche.set_tile("tiles/maison_toit_bas_gauche.bmp",OBSTACLE);
    MaisonToitBasDroite.set_tile("tiles/maison_toit_bas_droite.bmp",OBSTACLE);
    MaisonPoke.set_tile("tiles/maison_poke.bmp",OBSTACLE);
    MaisonMart.set_tile("tiles/maison_mart.bmp",OBSTACLE);
    MaisonGymGauche.set_tile("tiles/maison_gym_gauche.bmp",OBSTACLE);
    MaisonGymDroite.set_tile("tiles/maison_gym_droite.bmp",OBSTACLE);
    MeubleRed.set_tile("tiles/meubleRed.bmp",OBSTACLE);
    Montagne.set_tile("tiles/montagne.bmp",OBSTACLE);
    MontagneBas.set_tile("tiles/montagne_bas.bmp",OBSTACLE);
    MontagneCoinBasDroite.set_tile("tiles/montagne_coin_bas_droite.bmp",OBSTACLE);
    MontagneCoinHautDroite.set_tile("tiles/montagne_coin_haut_droite.bmp",OBSTACLE);
    MontagneDroite.set_tile("tiles/montagne_droite.bmp",OBSTACLE);
    MontagneHaut.set_tile("tiles/montagne_haut.bmp",OBSTACLE);
    MontagneGauche.set_tile("tiles/montagne_gauche.bmp",OBSTACLE);
    MontagneCoinBasGauche.set_tile("tiles/montagne_coin_bas_gauche.bmp",OBSTACLE);
    MontagneCoinHautGauche.set_tile("tiles/montagne_coin_haut_gauche.bmp",OBSTACLE);
    MontagneCreuxDroite.set_tile("tiles/montagne_creux_droite.bmp",OBSTACLE);
    MontagneCreuxGauche.set_tile("tiles/montagne_creux_gauche.bmp",OBSTACLE);
    MurBlue.set_tile("tiles/murBlue.bmp",OBSTACLE);
    MurBlueCarte.set_tile("tiles/murBlueCarte.bmp",OBSTACLE);
    MurChen.set_tile("tiles/murChen.bmp",OBSTACLE);
    MurCentre.set_tile("tiles/murCentre.bmp",OBSTACLE);
    MurCentreComptoir.set_tile("tiles/murCentreComptoir.bmp",OBSTACLE);
    MurRed.set_tile("tiles/murRed.bmp",OBSTACLE);
    Noir.set_tile("tiles/noir.bmp",OBSTACLE);
    OrdiCentreHaut.set_tile("tiles/ordiCentre_haut.bmp",OBSTACLE);
    OrdiSoin.set_tile("tiles/ordiSoin.bmp",OBSTACLE);
    OrdiRedBas.set_tile("tiles/ordiRed_bas.bmp",OBSTACLE);
    OrdiRedHaut.set_tile("tiles/ordiRed_haut.bmp",OBSTACLE);
    Palier.set_tile("tiles/palier.bmp",OBSTACLE);
    PalierBlue.set_tile("tiles/palierBlue.bmp",CHANGEMAP);
    PalierChen.set_tile("tiles/palierChen.bmp",CHANGEMAP);
    PalierRed.set_tile("tiles/palierRed.bmp",CHANGEMAP);
    PalierCentre.set_tile("tiles/palierChen.bmp",CHANGEMAP);
    PanneauRoute1.set_tile("tiles/panneau.bmp",TXT);
    PanneauBlue.set_tile("tiles/panneau.bmp",TXT);
    PanneauChen.set_tile("tiles/panneau.bmp",TXT);
    PanneauPalette.set_tile("tiles/panneau.bmp",TXT);
    PanneauJadielle1.set_tile("tiles/panneau.bmp",TXT);
    PanneauJadielle2.set_tile("tiles/panneau.bmp",TXT);
    PanneauJadielle3.set_tile("tiles/panneau.bmp",TXT);
    PanneauJadielle4.set_tile("tiles/panneau.bmp",TXT);
    PanneauArgenta1.set_tile("tiles/panneau.bmp",TXT);
    PanneauArgenta2.set_tile("tiles/panneau.bmp",TXT);
    PanneauArgenta3.set_tile("tiles/panneau.bmp",TXT);
    PanneauArgenta4.set_tile("tiles/panneau.bmp",TXT);
    PanneauArgenta5.set_tile("tiles/panneau.bmp",TXT);
    PanneauRoute22.set_tile("tiles/panneau.bmp",TXT);
    PanneauRed.set_tile("tiles/panneau.bmp",TXT);
    PanneauRoute2Bas.set_tile("tiles/panneau.bmp",TXT);
    PanneauRoute2Haut.set_tile("tiles/panneau.bmp",TXT);
    Passage.set_tile("tiles/passage.bmp",PASSAGE);
    PassageRoute.set_tile("tiles/passage_route.bmp",PASSAGE);
    Pave.set_tile("tiles/pave.bmp",PASSAGE);
    PetiteTableGauche.set_tile("tiles/petitetable_gauche.bmp",OBSTACLE);
    PetiteTableDrotie.set_tile("tiles/petitetable_droite.bmp",OBSTACLE);
    PlanteBas.set_tile("tiles/plante_bas.bmp",OBSTACLE);
    PlanteHaut.set_tile("tiles/plante_haut.bmp",OBSTACLE);
    PortePalette1.set_tile("tiles/porte.bmp",CHANGEMAP);
    PortePalette2.set_tile("tiles/porte.bmp",CHANGEMAP);
    PortePalette3.set_tile("tiles/porte.bmp",CHANGEMAP);
    PorteJadielle1.set_tile("tiles/porte.bmp",CHANGEMAP);
    PorteJadielle2.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteJadielle3.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteJadielle4.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteJadielle5.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteArgenta1.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteArgenta2.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteArgenta3.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteArgenta4.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteArgenta5.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteRoute22.set_tile("tiles/porte.bmp",TXT);
    PorteRoute2Maison.set_tile("tiles/porte.bmp",OBSTACLE);
    PorteRoute2Batiment.set_tile("tiles/porte.bmp",OBSTACLE);
    Poubelle.set_tile("tiles/poubelle.bmp",TXT);
    RadioBlueHaut.set_tile("tiles/radioBlue_haut.bmp",OBSTACLE);
    RadioBlueBas.set_tile("tiles/radioBlue_bas.bmp",OBSTACLE);
    Roche.set_tile("tiles/roche.bmp",OBSTACLE);
    RouteGravier.set_tile("tiles/route_gravier.bmp",PASSAGE);
    Route.set_tile("tiles/routebis.bmp",PASSAGE);
    RouteMiGravier.set_tile("tiles/route.bmp",PASSAGE);
    RouteMiGravierBloc.set_tile("tiles/route.bmp",OBSTACLE);
    RouteGravierBloc.set_tile("tiles/route_gravier.bmp",OBSTACLE);
    RouteBloc.set_tile("tiles/routebis.bmp",OBSTACLE);
    RouteRoute1.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteRoute1b.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteRoute2.set_tile("tiles/route_gravier.bmp",PASSAGE);
    RouteRoute22.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteRoute22b.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteJadielle.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteJadielleb.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteJadielleEst.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    RouteJadielleEstb.set_tile("tiles/route_gravier.bmp",CHANGEMAP);
    Route2ToJadielleD.set_tile("tiles/route.bmp",CHANGEMAP);
    Route2ToJadielleG.set_tile("tiles/routebis.bmp",CHANGEMAP);
    Route2ToJadielle.set_tile("tiles/routebis.bmp",CHANGEMAP);
    Route2ToArgentaG.set_tile("tiles/route.bmp",CHANGEMAP);
    Route2ToArgentaD.set_tile("tiles/routebis.bmp",CHANGEMAP);
    Saoul.set_tile("tiles/routebis.bmp",PNJ);
    Scientifique.set_tile("tiles/solChen.bmp",PNJ);
    SoinBasDroite.set_tile("tiles/soin_bas_droite.bmp",OBSTACLE);
    SoinBasGauche.set_tile("tiles/soin_bas_gauche.bmp",OBSTACLE);
    SoinHautDroite.set_tile("tiles/soin_haut_droite.bmp",OBSTACLE);
    SoinHautGauche.set_tile("tiles/soin_haut_gauche.bmp",OBSTACLE);
    SolBlue.set_tile("tiles/solBlue.bmp",PASSAGE);
    SolCentre.set_tile("tiles/solPokeCentre.bmp",PASSAGE);
    SolCentreOmbre.set_tile("tiles/solCentre_ombre.bmp",PASSAGE);
    SolChen.set_tile("tiles/solChen.bmp",PASSAGE);
    SolRed.set_tile("tiles/solRed.bmp",PASSAGE);
    Sonnette.set_tile("tiles/sonnette.bmp",OBSTACLE);
    SonnetteDouble.set_tile("tiles/sonnette_double.bmp",OBSTACLE);
    SourisOrdi.set_tile("tiles/sourisOrdi.bmp",OBSTACLE);
    TableBasDroite.set_tile("tiles/table_bas_droite.bmp",OBSTACLE);
    TableBasGauche.set_tile("tiles/table_bas_gauche.bmp",OBSTACLE);
    TableHaut.set_tile("tiles/table_haut.bmp",OBSTACLE);
    TableHautBall.set_tile("tiles/table_haut.bmp",BALL);
    TableHautDroite.set_tile("tiles/table_haut_droite.bmp",OBSTACLE);
    TableHautGauche.set_tile("tiles/table_haut_gauche.bmp",OBSTACLE);
    TableBlueBasDroite.set_tile("tiles/tableBlue_bas_droite.bmp",OBSTACLE);
    TableBlueBasGauche.set_tile("tiles/tableBlue_bas_gauche.bmp",OBSTACLE);
    TableBlueHautDroite.set_tile("tiles/tableBlue_haut_droite.bmp",OBSTACLE);
    TableBlueHautGauche.set_tile("tiles/tableBlue_haut_gauche.bmp",OBSTACLE);
    TableChen.set_tile("tiles/tableChen.bmp",PASSAGE);
    TableChenDroite.set_tile("tiles/tableChen_droite.bmp",PASSAGE);
    TableChenGauche.set_tile("tiles/tableChen_gauche.bmp",PASSAGE);
    TableRedDroite.set_tile("tiles/tableRed_droite.bmp",PASSAGE);
    TableRedGauche.set_tile("tiles/tableRed_gauche.bmp",PASSAGE);
    TabouretBlue.set_tile("tiles/tabouretBlue.bmp",PASSAGE);
    TabouretRed.set_tile("tiles/tabouretRed.bmp",PASSAGE);
    Tele.set_tile("tiles/tele.bmp",OBSTACLE);
    TeleBlueBas.set_tile("tiles/teleBlue_bas.bmp",OBSTACLE);
    TeleBlueHaut.set_tile("tiles/teleBlue_haut.bmp",OBSTACLE);
    TeleRedBas.set_tile("tiles/teleRed_bas.bmp",OBSTACLE);
    TeleRedHaut.set_tile("tiles/teleRed_haut.bmp",OBSTACLE);
    Toit.set_tile("tiles/toit.bmp",OBSTACLE);
    ToitDroite.set_tile("tiles/toit_droite.bmp",OBSTACLE);
    ToitGauche.set_tile("tiles/toit_gauche.bmp",OBSTACLE);
    ToitGrisBas.set_tile("tiles/toitgris_bas.bmp",OBSTACLE);
    ToitGrisBasDroite.set_tile("tiles/toitgris_bas_droite.bmp",OBSTACLE);
    ToitGrisBasGauche.set_tile("tiles/toitgris_bas_gauche.bmp",OBSTACLE);
    ToitGrisHaut.set_tile("tiles/toitgris_haut.bmp",OBSTACLE);
    ToitGrisHautDroite.set_tile("tiles/toitgris_haut_droite.bmp",OBSTACLE);
    ToitGrisHautGauche.set_tile("tiles/toitgris_haut_gauche.bmp",OBSTACLE);
    ToitVertBas.set_tile("tiles/toitvert_bas.bmp",OBSTACLE);
    ToitVertHaut.set_tile("tiles/toitvert_haut.bmp",OBSTACLE);
    ToitVert.set_tile("tiles/toitvert.bmp",OBSTACLE);

    Bulbizarre.set_pokemon("BULBIZARRE","pokemon_back/bulbizarre_back.bmp", "pokemon_front/bulbizarre_front.bmp", "cris/001Cry.wav", 7,45,49,49,65,65,45,64,PARABOLIQUE,PLANTE);
    Herbizarre.set_pokemon("HERBIZARRE","pokemon_back/herbizarre_back.bmp", "pokemon_front/herbizarre_front.bmp", "cris/002Cry.wav", 16,60,62,63,80,80,60,141,PARABOLIQUE,PLANTE);
    Florizarre.set_pokemon("FLORIZARRE","pokemon_back/florizarre_back.bmp", "pokemon_front/florizarre_front.bmp", "cris/003Cry.wav", 32,80,82,83,100,100,80,208,PARABOLIQUE,PLANTE);
    Salameche.set_pokemon("SALAMECHE","pokemon_back/salameche_back.bmp", "pokemon_front/salameche_front.bmp", "cris/004Cry.wav", 7,39,52,43,60,50,65,65,PARABOLIQUE,FEU);
    Reptincel.set_pokemon("REPTINCEL","pokemon_back/reptincel_back.bmp", "pokemon_front/reptincel_front.bmp","cris/005Cry.wav", 16,58,64,58,80,65,80,142,PARABOLIQUE,FEU);
    Dracaufeu.set_pokemon("DRACAUFEU","pokemon_back/dracaufeu_back.bmp", "pokemon_front/dracaufeu_front.bmp","cris/006Cry.wav", 36,78,84,78,109,85,100,209,PARABOLIQUE,FEU);
    Carapuce.set_pokemon("CARAPUCE","pokemon_back/carapuce_back.bmp", "pokemon_front/carapuce_front.bmp", "cris/007Cry.wav", 7,44,48,65,50,64,43,66,PARABOLIQUE,EAU);
    Carabaffe.set_pokemon("CARABAFFE","pokemon_back/carabaffe_back.bmp", "pokemon_front/carabaffe_front.bmp", "cris/008Cry.wav", 16,59,63,80,65,80,58,143,PARABOLIQUE,EAU);
    Tortank.set_pokemon("TORTANK","pokemon_back/tortank_back.bmp", "pokemon_front/tortank_front.bmp", "cris/009Cry.wav", 36,79,83,100,85,105,78,210,PARABOLIQUE,EAU);
    Chenipan.set_pokemon("CHENIPAN","pokemon_back/chenipan_back.bmp", "pokemon_front/chenipan_front.bmp", "cris/010Cry.wav", 3,45,30,35,20,20,45,53,MOYENNE,INSECTE);
    Chrysacier.set_pokemon("CHRYSACIER","pokemon_back/chrysacier_back.bmp", "pokemon_front/chrysacier_front.bmp", "cris/011Cry.wav", 7,50,20,55,25,25,30,72,MOYENNE,INSECTE);
    Papilusion.set_pokemon("PAPILUSION","pokemon_back/papilusion_back.bmp", "pokemon_front/papilusion_front.bmp", "cris/012Cry.wav",10,60,45,50,80,80,70,160,MOYENNE,INSECTE);
    Aspicot.set_pokemon("ASPICOT", "pokemon_back/aspicot_back.bmp", "pokemon_front/aspicot_front.bmp", "cris/013Cry.wav", 3,40,35,30,20,20,50,52,MOYENNE,INSECTE);
    Coconfort.set_pokemon("COCONFORT","pokemon_back/coconfort_back.bmp", "pokemon_front/coconfort_front.bmp", "cris/014Cry.wav", 7,45,25,50,25,25,35,71,MOYENNE,INSECTE);
    Dardargnan.set_pokemon("DARDARGNAN", "pokemon_back/dardargnan_back.bmp", "pokemon_front/dardargnan_front.bmp", "cris/015Cry.wav",10,65,80,40,45,80,75,159,MOYENNE,INSECTE);
    Roucool.set_pokemon("ROUCOOL","pokemon_back/roucool_back.bmp", "pokemon_front/roucool_front.bmp","cris/016Cry.wav", 3,40,45,40,35,35,56,55,PARABOLIQUE,VOL);
    Roucoups.set_pokemon("ROUCOUPS","pokemon_back/roucoups_back.bmp","pokemon_front/roucoups_front.bmp","cris/Cry017.wav", 7,63,60,55,50,50,71,113,PARABOLIQUE,VOL);
    Roucarnage.set_pokemon("ROUCARNAGE","pokemon_back/roucarnage_back.bmp","pokemon_front/roucarnage_front.bmp","cris/018Cry.wav",36,83,80,75,70,70,91,172,PARABOLIQUE,VOL);
    Rattata.set_pokemon("RATTATA","pokemon_back/rattata_back.bmp", "pokemon_front/rattata_front.bmp","cris/019Cry.wav", 3,30,56,35,25,35,72,57,MOYENNE,NORMAL);
    Piafabec.set_pokemon("PIAFABEC","pokemon_back/piafabec_back.bmp","pokemon_front/piafabec_front.bmp","cris/021Cry.wav", 4,40,60,30,31,31,70,58,MOYENNE,VOL);
    Rapasdepic.set_pokemon("RAPASDEPIC","pokemon_back/rapasdepic_back.bmp","pokemon_front/rapasdepic_front.bmp","cris/022Cry.wav", 7,65,90,65,61,61,100,162,MOYENNE,VOL);
    Pikachu.set_pokemon("PIKACHU","pokemon_back/pikachu_back.bmp", "pokemon_front/pikachu_front.bmp","cris/025Cry.wav", 7,35,55,40,50,50,90,82,MOYENNE,ELECTRIK);
    Ponyta.set_pokemon("PONYTA","pokemon_back/ponyta_back.bmp", "pokemon_front/ponyta_front.bmp","cris/077Cry.wav", 6,50,85,55,65,65,90,152,MOYENNE,FEU);
    Doduo.set_pokemon("DODUO","pokemon_back/doduo_back.bmp", "pokemon_front/doduo_front.bmp","cris/084Cry.wav", 4,35,85,45,35,35,75,96,MOYENNE,VOL);
    Evoli.set_pokemon("EVOLI","pokemon_back/evoli_back.bmp", "pokemon_front/evoli_front.bmp","cris/133Cry.wav", 5,55,55,50,45,65,55,92,MOYENNE,NORMAL);
    Fouinette.set_pokemon("FOUINETTE","pokemon_back/fouinette_back.bmp", "pokemon_front/fouinette_front.bmp","cris/161Cry.wav", 3,35,46,34,35,45,20,57,MOYENNE,NORMAL);
    Fouinar.set_pokemon("FOUINAR","pokemon_back/fouinar_back.bmp", "pokemon_front/fouinar_front.bmp","cris/162Cry.wav", 5,85,76,64,45,55,90,116,MOYENNE,NORMAL);
    Coxy.set_pokemon("COXY","pokemon_back/coxy_back.bmp","pokemon_front/coxy_front/bmp","cris/165Cry.wav", 3,40,20,30,40,80,55,54,RAPIDE,INSECTE);
    Suicune.set_pokemon("SUICUNE","pokemon_back/suicune_back.bmp", "pokemon_front/suicune_front.bmp","cris/245Cry.wav",40,100,75,115,90,115,85,216,LENTE,EAU);

    MimiQueue.give_effect(DEF,-1);
    Rugissement.give_effect(ATT,-1);
    Grozyeux.give_effect(DEF,-1);
    Grimace.give_effect(VIT,-2);
    Secretion.give_effect(VIT,-1);
    Armure.give_effect(DEF,1);
    Repli.give_effect(DEF,1);
    JetDeSable.give_effect(PREC,-1);

    ATKBulbizarre.push_back(Charge);
    ATKBulbizarre.push_back(Rugissement);
    ATKBulbizarre.push_back(FouetLianes);
    Bulbizarre.give_attaque(ATKBulbizarre);

    ATKHerbizarre.push_back(TranchHerbe);
    ATKHerbizarre.push_back(Belier);
    Herbizarre.give_attaque(ATKHerbizarre);

    ATKFlorizarre.push_back(LanceSoleil);
    ATKFlorizarre.push_back(Damocles);
    Florizarre.give_attaque(ATKFlorizarre);

    ATKSalameche.push_back(Griffe);
    ATKSalameche.push_back(Rugissement);
    ATKSalameche.push_back(Flammeche);
    ATKSalameche.push_back(Grimace);
    Salameche.give_attaque(ATKSalameche);

    ATKReptincel.push_back(Dracosouffle);
    ATKReptincel.push_back(LanceFlamme);
    Reptincel.give_attaque(ATKReptincel);

    ATKDracaufeu.push_back(Tranche);
    ATKDracaufeu.push_back(Deflagration);
    Dracaufeu.give_attaque(ATKDracaufeu);

    ATKCarapuce.push_back(Charge);
    ATKCarapuce.push_back(MimiQueue);
    ATKCarapuce.push_back(PistoletaO);
    Carapuce.give_attaque(ATKCarapuce);

    ATKCarabaffe.push_back(Surf);
    ATKCarabaffe.push_back(Belier);
    Carabaffe.give_attaque(ATKCarabaffe);

    ATKTortank.push_back(Hydrocanon);
    ATKTortank.push_back(CoudKrane);
    Tortank.give_attaque(ATKTortank);

    ATKChenipan.push_back(Charge);
    ATKChenipan.push_back(Secretion);
    Chenipan.give_attaque(ATKChenipan);

    ATKChrysacier.push_back(Armure);
    Chrysacier.give_attaque(ATKChrysacier);

    ATKPapilusion.push_back(ChocMental);
    Papilusion.give_attaque(ATKPapilusion);

    ATKAspicot.push_back(DardVenin);
    Aspicot.give_attaque(ATKAspicot);

    ATKCoconfort.push_back(Armure);
    Coconfort.give_attaque(ATKCoconfort);

    ATKRoucool.push_back(Charge);
    ATKRoucool.push_back(Tornade);
    ATKRoucool.push_back(JetDeSable);
    Roucool.give_attaque(ATKRoucool);

    ATKRattata.push_back(Charge);
    ATKRattata.push_back(MimiQueue);
    ATKRattata.push_back(ViveAttaque);
    Rattata.give_attaque(ATKRattata);

    ATKPiafabec.push_back(Picpic);
    ATKPiafabec.push_back(Rugissement);
    ATKPiafabec.push_back(Poursuite);
    ATKPiafabec.push_back(Grozyeux);
    Piafabec.give_attaque(ATKPiafabec);

    ATKRapasdepic.push_back(Poursuite);
    ATKRapasdepic.push_back(Aeropique);
    Rapasdepic.give_attaque(ATKRapasdepic);

    ATKPikachu.push_back(Eclair);
    ATKPikachu.push_back(Rugissement);
    ATKPikachu.push_back(MimiQueue);
    ATKPikachu.push_back(ViveAttaque);
    Pikachu.give_attaque(ATKPikachu);

    ATKPonyta.push_back(Charge);
    ATKPonyta.push_back(Rugissement);
    ATKPonyta.push_back(MimiQueue);
    ATKPonyta.push_back(Flammeche);
    Ponyta.give_attaque(ATKPonyta);

    ATKDoduo.push_back(Picpic);
    ATKDoduo.push_back(ViveAttaque);
    Doduo.give_attaque(ATKDoduo);

    ATKEvoli.push_back(Charge);
    //ATKEvoli.push_back(MimiQueue);
    ATKEvoli.push_back(Rugissement);
    //ATKEvoli.push_back(ViveAttaque);
    //ATKEvoli.push_back(Morsure);
    //ATKEvoli.push_back(Belier);
    ATKEvoli.push_back(Meteore);
    Evoli.give_attaque(ATKEvoli);

    ATKFouinette.push_back(Griffe);
    ATKFouinette.push_back(ViveAttaque);
    Fouinette.give_attaque(ATKFouinette);

    ATKFouinar.push_back(Griffe);
    ATKFouinar.push_back(Souplesse);
    Fouinar.give_attaque(ATKFouinar);

    ATKSuicune.push_back(Morsure);
    ATKSuicune.push_back(Blizzard);
    Suicune.give_attaque(ATKSuicune);

    Gold.set_dresseur("GOLD","combat_image/gold_combat.bmp");
    Silver.set_dresseur("SILVER","combat_image/silver_combat.bmp");

    // Team des dresseurs
    TeamGold.push_back(Roucool);
    //TeamGold.push_back(Bulbizarre);
    //TeamGold.push_back(Herbizarre);
    //TeamGold.push_back(Florizarre);
    //TeamGold.push_back(Salameche);
    //TeamGold.push_back(Reptincel);
    TeamGold.push_back(Dracaufeu);
    TeamGold.push_back(Carapuce);
    //TeamGold.push_back(Carabaffe);
    //TeamGold.push_back(Tortank);
    //TeamGold.push_back(Pikachu);
    //TeamGold.push_back(Suicune);
    Gold.give_team(TeamGold);

    TeamSilver.push_back(Evoli);
    Silver.give_team(TeamSilver);

    // Position des changements de Carte
    SDL_Rect posRedToPalette, posEscalierRed; //Venant de Maison Red
    SDL_Rect posBlueToPalette; // Venant de Maison Blue
    SDL_Rect posChenToPalette; // Venant de Labo Chen
    SDL_Rect posPokeToJadielle; // Venant de Centre Pokemon
    SDL_Rect posPaletteToRoute1D, posPaletteToRoute1G, posPaletteToMaison, posPaletteToChen; // Venant de Bourg Palette
    SDL_Rect posJadielleToRoute1D, posJadielleToRoute1G, posJadielleToRoute22B, posJadielleToRoute22H, posJadielleToRoute22HerbeB, posJadielleToRoute22HerbeH, posJadielleToCentrePokemon, posJadielleToRoute2, posJadielleToRoute2D, posJadielleToRoute2G; //Venant de Jadielle
    SDL_Rect posRoute22ToJadielleB, posRoute22ToJadielleH, posRoute22ToJadielleHerbeB, posRoute22ToJadielleHerbeH; // Venant de Route22
    SDL_Rect posRoute1ToPaletteD, posRoute1ToPaletteG, posRoute1ToJadielleD, posRoute1ToJadielleG; // Venant de Route 1
    SDL_Rect posRoute2ToJadielleD, posRoute2ToJadielleG, posRoute2ToJadielle, posRoute2ToArgentaG, posRoute2ToArgentaD; // Venant de Route2
    SDL_Rect posArgentaToRoute2G, posArgentaToRoute2D; // Venant de Argenta

    posPaletteToChen.x = 10;
    posPaletteToChen.y = 16;

    posPaletteToMaison.x = 8;
    posPaletteToMaison.y = 12;

    posEscalierRed.x = 12;
    posEscalierRed.y = 5;

    posJadielleToCentrePokemon.x = 9;
    posJadielleToCentrePokemon.y = 12;

    posChenToPalette.x = 17;
    posChenToPalette.y = 18;

    posBlueToPalette.x = 18;
    posBlueToPalette.y = 12;

    posRedToPalette.x = 10;
    posRedToPalette.y = 12;

    posRoute1ToPaletteD.x = 14;
    posRoute1ToPaletteD.y = 5;

    posRoute1ToPaletteG.x = 13;
    posRoute1ToPaletteG.y = 5;

    posPaletteToRoute1D.x = 11;
    posPaletteToRoute1D.y = 39;

    posPaletteToRoute1G.x = 10;
    posPaletteToRoute1G.y = 39;

    posJadielleToRoute22B.x = 33;
    posJadielleToRoute22B.y = 12;

    posJadielleToRoute22H.x = 33;
    posJadielleToRoute22H.y = 11;

    posJadielleToRoute22HerbeB.x = 33;
    posJadielleToRoute22HerbeB.y = 10;

    posJadielleToRoute22HerbeH.x = 33;
    posJadielleToRoute22HerbeH.y = 9;

    posJadielleToRoute1D.x = 11;
    posJadielleToRoute1D.y = 5;

    posJadielleToRoute1G.x = 10;
    posJadielleToRoute1G.y = 5;

    posJadielleToRoute2G.x = 12;
    posJadielleToRoute2G.y = 58;

    posJadielleToRoute2.x = 13;
    posJadielleToRoute2.y = 58;

    posJadielleToRoute2D.x = 14;
    posJadielleToRoute2D.y = 58;

    posRoute1ToJadielleD.x = 34;
    posRoute1ToJadielleD.y = 42;

    posRoute1ToJadielleG.x = 33;
    posRoute1ToJadielleG.y = 42;

    posPokeToJadielle.x = 28;
    posPokeToJadielle.y = 31;

    posRoute22ToJadielleB.x = 5;
    posRoute22ToJadielleB.y = 23;

    posRoute22ToJadielleH.x = 5;
    posRoute22ToJadielleH.y = 22;

    posRoute22ToJadielleHerbeB.x = 5;
    posRoute22ToJadielleHerbeB.y = 21;

    posRoute22ToJadielleHerbeH.x = 5;
    posRoute22ToJadielleHerbeH.y = 20;

    posRoute2ToJadielleG.x = 22;
    posRoute2ToJadielleG.y = 5;

    posRoute2ToJadielleD.x = 24;
    posRoute2ToJadielleD.y = 5;

    posRoute2ToJadielle.x = 23;
    posRoute2ToJadielle.y = 5;

    posRoute2ToArgentaG.x = 19;
    posRoute2ToArgentaG.y = 37;

    posRoute2ToArgentaD.x = 20;
    posRoute2ToArgentaD.y = 37;

    posArgentaToRoute2G.x = 13;
    posArgentaToRoute2G.y = 5;

    posArgentaToRoute2D.x = 14;
    posArgentaToRoute2D.y = 5;

    // Propriétés données aux tiles d'une carte

    // Propriétés Tiles Route1

    HautesHerbesPalette.give_carte(PALETTE);
    HautesHerbesPalette.give_position(posRoute1ToPaletteD);
    HautesHerbesPaletteb.give_carte(PALETTE);
    HautesHerbesPaletteb.give_position(posRoute1ToPaletteG);
    RouteJadielle.give_carte(JADIELLE);
    RouteJadielle.give_position(posRoute1ToJadielleD);
    RouteJadielleb.give_carte(JADIELLE);
    RouteJadielleb.give_position(posRoute1ToJadielleG);
    std::vector<std::string> TXTPanneauRoute1;
    TXTPanneauRoute1.push_back("ROUTE 1");
    TXTPanneauRoute1.push_back("");
    TXTPanneauRoute1.push_back("BOURG PALETTE -");
    TXTPanneauRoute1.push_back("JADIELLE");
    std::vector<std::string> TXTSilver;
    TXTSilver.push_back("Hmm... Je dois");
    TXTSilver.push_back("devenir plus fort !");
    PanneauRoute1.give_txt(TXTPanneauRoute1);
    PNJDresseur.give_txt(TXTSilver);
    PNJDresseur.give_nbPNJ(0);
    CombatSilver.give_dresseur(Silver);

    // Ajout des tiles au vecteur contenant les tiles d'une carte. L'ordre sera spécifique lors de la création de la carte

    // Vecteur Tiles Route1

    Route1Tiles.push_back(PanneauRoute1);       //0
    Route1Tiles.push_back(Roche);               //1
    Route1Tiles.push_back(Bloc);                //2
    Route1Tiles.push_back(PNJDresseur);         //3
    Route1Tiles.push_back(BarriereHerbe);       //4
    Route1Tiles.push_back(BarriereChemin);      //5
    Route1Tiles.push_back(CombatSilver);        //6
    Route1Tiles.push_back(Passage);             //7
    Route1Tiles.push_back(Herbe);               //8
    Route1Tiles.push_back(RouteGravier);        //9
    Route1Tiles.push_back(FleurGauche);         //10
    Route1Tiles.push_back(FleurDroite);         //11
    Route1Tiles.push_back(HautesHerbes);        //12
    Route1Tiles.push_back(HautesHerbesPalette); //13
    Route1Tiles.push_back(HautesHerbesPaletteb);//14
    Route1Tiles.push_back(RouteJadielle);       //15
    Route1Tiles.push_back(RouteJadielleb);      //16
    Route1Tiles.push_back(HautesHerbesBloc);    //17
    Route1Tiles.push_back(RouteBloc);           //18
    Route1Tiles.push_back(RouteMiGravierBloc);  //19
    Route1Tiles.push_back(Route);               //20
    Route1Tiles.push_back(RouteMiGravier);      //21

    // Propriétés Tiles Route2

    Route2ToJadielleD.give_carte(JADIELLE);
    Route2ToJadielleD.give_position(posRoute2ToJadielleD);
    Route2ToJadielleG.give_carte(JADIELLE);
    Route2ToJadielleG.give_position(posRoute2ToJadielleG);
    Route2ToJadielle.give_carte(JADIELLE);
    Route2ToJadielle.give_position(posRoute2ToJadielle);
    Route2ToArgentaG.give_carte(ARGENTA);
    Route2ToArgentaG.give_position(posRoute2ToArgentaG);
    Route2ToArgentaD.give_carte(ARGENTA);
    Route2ToArgentaD.give_position(posRoute2ToArgentaD);
    std::vector<std::string> TXTPanneauRoute2;
    TXTPanneauRoute2.push_back("ROUTE 2");
    TXTPanneauRoute2.push_back("");
    TXTPanneauRoute2.push_back("JADIELLE -");
    TXTPanneauRoute2.push_back("ARGENTA");
    PanneauRoute2Bas.give_txt(TXTPanneauRoute2);

    Route2Tiles.push_back(Herbe);                  //0
    Route2Tiles.push_back(Pave);                   //1
    Route2Tiles.push_back(Route);                  //2
    Route2Tiles.push_back(RouteGravier);           //3
    Route2Tiles.push_back(Bloc);                   //4
    Route2Tiles.push_back(Roche);                  //5
    Route2Tiles.push_back(BarriereHerbe);          //6
    Route2Tiles.push_back(BarriereChemin);         //7
    Route2Tiles.push_back(Passage);                //8
    Route2Tiles.push_back(PassageRoute);           //9
    Route2Tiles.push_back(FleurGauche);            //10
    Route2Tiles.push_back(FleurDroite);            //11
    Route2Tiles.push_back(HautesHerbes);           //12
    Route2Tiles.push_back(ArbreCoupe);             //13
    Route2Tiles.push_back(BarriereVille);          //14
    Route2Tiles.push_back(MaisonToitBasGauche);    //15
    Route2Tiles.push_back(MaisonToitBasDroite);    //16
    Route2Tiles.push_back(MaisonBas);              //17
    Route2Tiles.push_back(PorteRoute2Maison);      //18
    Route2Tiles.push_back(Toit);                   //19
    Route2Tiles.push_back(ToitDroite);             //20
    Route2Tiles.push_back(ToitGauche);             //21
    Route2Tiles.push_back(MaisonBriqueBasGauche);  //22
    Route2Tiles.push_back(MaisonBriqueBasDroite);  //23
    Route2Tiles.push_back(MaisonBriqueBas);        //24
    Route2Tiles.push_back(MaisonBriqueHautGauche); //25
    Route2Tiles.push_back(MaisonBriqueHautDroite); //26
    Route2Tiles.push_back(MaisonBriqueFenetre2);   //27
    Route2Tiles.push_back(MaisonBriqueFenetre2bis);//28
    Route2Tiles.push_back(PorteRoute2Batiment);    //29
    Route2Tiles.push_back(ToitGrisBasGauche);      //30
    Route2Tiles.push_back(ToitGrisBasDroite);      //31
    Route2Tiles.push_back(ToitGrisHautGauche);     //32
    Route2Tiles.push_back(ToitGrisHautDroite);     //33
    Route2Tiles.push_back(ToitGrisHaut);           //34
    Route2Tiles.push_back(ToitGrisBas);            //35
    Route2Tiles.push_back(Palier);                 //36
    Route2Tiles.push_back(GrotteRoute2);           //37
    Route2Tiles.push_back(Montagne);               //38
    Route2Tiles.push_back(MontagneBas);            //39
    Route2Tiles.push_back(MontagneHaut);           //40
    Route2Tiles.push_back(MontagneGauche);         //41
    Route2Tiles.push_back(MontagneDroite);         //42
    Route2Tiles.push_back(MontagneCoinBasGauche);  //43
    Route2Tiles.push_back(MontagneCoinBasDroite);  //44
    Route2Tiles.push_back(MontagneCoinHautGauche); //45
    Route2Tiles.push_back(MontagneCoinHautDroite); //46
    Route2Tiles.push_back(PanneauRoute2Haut);      //47
    Route2Tiles.push_back(PanneauRoute2Bas);       //48
    Route2Tiles.push_back(RouteBloc);              //49
    Route2Tiles.push_back(RouteGravierBloc);       //50
    Route2Tiles.push_back(Route2ToJadielleG);      //51
    Route2Tiles.push_back(Route2ToJadielleD);      //52
    Route2Tiles.push_back(RouteMiGravier);         //53
    Route2Tiles.push_back(Route2ToJadielle);       //54
    Route2Tiles.push_back(Route2ToArgentaG);       //55
    Route2Tiles.push_back(Route2ToArgentaD);       //56


    // Propriétés Tiles Route22

    RouteJadielleEst.give_carte(JADIELLE);
    RouteJadielleEst.give_position(posRoute22ToJadielleB);
    RouteJadielleEstb.give_carte(JADIELLE);
    RouteJadielleEstb.give_position(posRoute22ToJadielleH);
    HerbeJadielle.give_carte(JADIELLE);
    HerbeJadielle.give_position(posRoute22ToJadielleHerbeB);
    HerbeJadielleb.give_carte(JADIELLE);
    HerbeJadielleb.give_position(posRoute22ToJadielleHerbeH);
    std::vector<std::string> TXTPanneauRoute22;
    TXTPanneauRoute22.push_back("LIGUE POKéMON");
    TXTPanneauRoute22.push_back("");
    TXTPanneauRoute22.push_back("ENTREE de la");
    TXTPanneauRoute22.push_back("ROUTE VICTOIRE");
    std::vector<std::string> TXTPorteRoute22;
    TXTPorteRoute22.push_back("L'accès à la ligue est fermé");
    PorteRoute22.give_txt(TXTPorteRoute22);
    PanneauRoute22.give_txt(TXTPanneauRoute22);

    // Vecteur Tiles Route22

    Route22Tiles.push_back(Herbe);                  //0
    Route22Tiles.push_back(Pave);                   //1
    Route22Tiles.push_back(Route);                  //2
    Route22Tiles.push_back(RouteGravier);           //3
    Route22Tiles.push_back(Bloc);                   //4
    Route22Tiles.push_back(BarriereHerbe);          //5
    Route22Tiles.push_back(BarriereChemin);         //6
    Route22Tiles.push_back(Passage);                //7
    Route22Tiles.push_back(PassageRoute);           //8
    Route22Tiles.push_back(PorteRoute22);           //9
    Route22Tiles.push_back(PanneauRoute22);         //10
    Route22Tiles.push_back(HautesHerbes);           //11
    Route22Tiles.push_back(Eau);                    //12
    Route22Tiles.push_back(EauHaut);                //13
    Route22Tiles.push_back(EauDroite);              //14
    Route22Tiles.push_back(EauCoinDroite);          //15
    Route22Tiles.push_back(EauGauche);              //16
    Route22Tiles.push_back(EauCoinGauche);          //17
    Route22Tiles.push_back(Montagne);               //18
    Route22Tiles.push_back(MontagneBas);            //19
    Route22Tiles.push_back(MontagneHaut);           //20
    Route22Tiles.push_back(MontagneDroite);         //21
    Route22Tiles.push_back(MontagneGauche);         //22
    Route22Tiles.push_back(MontagneCoinBasDroite);  //23
    Route22Tiles.push_back(MontagneCoinHautDroite); //24
    Route22Tiles.push_back(MontagneCoinBasGauche);  //25
    Route22Tiles.push_back(MontagneCoinHautGauche); //26
    Route22Tiles.push_back(MontagneCreuxDroite);    //27
    Route22Tiles.push_back(MontagneCreuxGauche);    //28
    Route22Tiles.push_back(MaisonBriqueBasGauche);  //29
    Route22Tiles.push_back(MaisonBriqueBasDroite);  //30
    Route22Tiles.push_back(MaisonBriqueBas);        //31
    Route22Tiles.push_back(MaisonBriqueHautGauche); //32
    Route22Tiles.push_back(MaisonBriqueHautDroite); //33
    Route22Tiles.push_back(MaisonBriqueFenetre2bis);//34
    Route22Tiles.push_back(ToitGrisHaut);           //35
    Route22Tiles.push_back(ToitGrisBas);            //36
    Route22Tiles.push_back(ToitGrisHautGauche);     //37
    Route22Tiles.push_back(ToitGrisBasGauche);      //38
    Route22Tiles.push_back(ToitGrisHautDroite);     //39
    Route22Tiles.push_back(ToitGrisBasDroite);      //40
    Route22Tiles.push_back(RouteJadielleEst);       //41
    Route22Tiles.push_back(RouteJadielleEstb);      //42
    Route22Tiles.push_back(HerbeJadielle);          //43
    Route22Tiles.push_back(HerbeJadielleb);         //44
    Route22Tiles.push_back(HerbeBloc);              //45
    Route22Tiles.push_back(RouteGravierBloc);       //46
    Route22Tiles.push_back(RouteMiGravier);         //47

    // Propriétés Tiles Bourg Palette

    PortePalette1.give_carte(REDBAS);
    PortePalette1.give_position(posPaletteToMaison);
    PortePalette2.give_carte(BLUE);
    PortePalette2.give_position(posPaletteToMaison);
    PortePalette3.give_carte(CHEN);
    PortePalette3.give_position(posPaletteToChen);
    HautesHerbesRoute1.give_carte(ROUTE1);
    HautesHerbesRoute1.give_position(posPaletteToRoute1D);
    HautesHerbesRoute1b.give_carte(ROUTE1);
    HautesHerbesRoute1b.give_position(posPaletteToRoute1G);
    std::vector<std::string> TXTPanneauPalette;
    TXTPanneauPalette.push_back("BOURG PALETTE");
    TXTPanneauPalette.push_back("");
    TXTPanneauPalette.push_back("Calme, paix et");
    TXTPanneauPalette.push_back("pureté");
    std::vector<std::string> TXTPanneauRed;
    TXTPanneauRed.push_back("Maison de RED");
    std::vector<std::string> TXTPanneauBlue;
    TXTPanneauBlue.push_back("Maison de BLUE");
    std::vector<std::string> TXTPanneauChen;
    TXTPanneauChen.push_back("Labo du Prof. CHEN");
    std::vector<std::string> TXTGros;
    TXTGros.push_back("{} C++, c'est beau");
    TXTGros.push_back("le progrès!");

    PanneauPalette.give_txt(TXTPanneauPalette);
    PanneauRed.give_txt(TXTPanneauRed);
    PanneauBlue.give_txt(TXTPanneauBlue);
    PanneauChen.give_txt(TXTPanneauChen);
    Gros.give_nbPNJ(0);
    Gros.give_txt(TXTGros);

    // Vecteur Tiles Bourg Palette

    BourgPaletteTiles.push_back(PanneauPalette);          //0
    BourgPaletteTiles.push_back(BarriereVille);           //1
    BourgPaletteTiles.push_back(Bloc);                    //2
    BourgPaletteTiles.push_back(Eau);                     //3
    BourgPaletteTiles.push_back(EauGauche);               //4
    BourgPaletteTiles.push_back(EauDroite);               //5
    BourgPaletteTiles.push_back(EauHaut);                 //6
    BourgPaletteTiles.push_back(EauCoinGauche);           //7
    BourgPaletteTiles.push_back(EauCoinDroite);           //8
    BourgPaletteTiles.push_back(MaisonBas);               //9
    BourgPaletteTiles.push_back(MaisonBasGauche);         //10
    BourgPaletteTiles.push_back(MaisonBasDroite);         //11
    BourgPaletteTiles.push_back(MaisonHautGauche);        //12
    BourgPaletteTiles.push_back(MaisonHautDroite);        //13
    BourgPaletteTiles.push_back(MaisonHautFenetre1);      //14
    BourgPaletteTiles.push_back(MaisonHautFenetre2);      //15
    BourgPaletteTiles.push_back(Toit);                    //16
    BourgPaletteTiles.push_back(ToitGauche);              //17
    BourgPaletteTiles.push_back(ToitDroite);              //18
    BourgPaletteTiles.push_back(MaisonBriqueBas);         //19
    BourgPaletteTiles.push_back(MaisonBriqueBasGauche);   //20
    BourgPaletteTiles.push_back(MaisonBriqueBasDroite);   //21
    BourgPaletteTiles.push_back(MaisonBriqueHautGauche);  //22
    BourgPaletteTiles.push_back(MaisonBriqueHautDroite);  //23
    BourgPaletteTiles.push_back(MaisonBriqueFenetre1);    //24
    BourgPaletteTiles.push_back(MaisonBriqueFenetre1bis); //25
    BourgPaletteTiles.push_back(MaisonBriqueFenetre2);    //26
    BourgPaletteTiles.push_back(MaisonBriqueFenetre2bis); //27
    BourgPaletteTiles.push_back(ToitGrisBas);             //28
    BourgPaletteTiles.push_back(ToitGrisBasGauche);       //29
    BourgPaletteTiles.push_back(ToitGrisBasDroite);       //30
    BourgPaletteTiles.push_back(ToitGrisHaut);            //31
    BourgPaletteTiles.push_back(ToitGrisHautGauche);      //32
    BourgPaletteTiles.push_back(ToitGrisHautDroite);      //33
    BourgPaletteTiles.push_back(HauteHerbe);              //34
    BourgPaletteTiles.push_back(RouteGravier);            //35
    BourgPaletteTiles.push_back(Route);                   //36
    BourgPaletteTiles.push_back(Herbe);                   //37
    BourgPaletteTiles.push_back(FleurGauche);             //38
    BourgPaletteTiles.push_back(FleurDroite);             //39
    BourgPaletteTiles.push_back(PortePalette1);           //40
    BourgPaletteTiles.push_back(PortePalette2);           //41
    BourgPaletteTiles.push_back(PortePalette3);           //42
    BourgPaletteTiles.push_back(HautesHerbesRoute1);      //43
    BourgPaletteTiles.push_back(PanneauRed);              //44
    BourgPaletteTiles.push_back(PanneauBlue);             //45
    BourgPaletteTiles.push_back(PanneauChen);             //46
    BourgPaletteTiles.push_back(Gros);                    //47
    BourgPaletteTiles.push_back(HautesHerbesRoute1b);     //48
    BourgPaletteTiles.push_back(HautesHerbesBloc);        //49
    BourgPaletteTiles.push_back(Roche);                   //50
    BourgPaletteTiles.push_back(RouteMiGravier);          //51

    // Propriétés Tiles Labo Chen

    PalierChen.give_carte(PALETTE);
    PalierChen.give_position(posChenToPalette);
    std::vector<std::string> TXTScientifique;
    TXTScientifique.push_back("Combien as-tu de");
    TXTScientifique.push_back("Pokémon?");
    std::vector<std::string> TXTChen;
    TXTChen.push_back("Où en est ton");
    TXTChen.push_back("Pokédex?");
    std::vector<std::string> TXTPoubelle;
    TXTPoubelle.push_back("Hmm... Bon appétit!");
    std::vector<std::string> TXTBiblioChen;
    TXTBiblioChen.push_back("A-t-il vraiment");
    TXTBiblioChen.push_back("lu tout ça !?");
    Scientifique.give_txt(TXTScientifique);
    Scientifique.give_nbPNJ(0);
    Chen.give_nbPNJ(1);
    Chen.give_txt(TXTChen);
    Poubelle.give_txt(TXTPoubelle);
    BiblioChenBas.give_txt(TXTBiblioChen);

    // Vecteur Tiles Labo Chen

    MaisonChenTiles.push_back(DiplomeChen);     //0
    MaisonChenTiles.push_back(MurChen);         //1
    MaisonChenTiles.push_back(FenetreChen);     //2
    MaisonChenTiles.push_back(Poubelle);        //3
    MaisonChenTiles.push_back(BiblioChenBas);   //4
    MaisonChenTiles.push_back(BiblioChenHaut);  //5
    MaisonChenTiles.push_back(EcranOrdi);       //6
    MaisonChenTiles.push_back(SourisOrdi);      //7
    MaisonChenTiles.push_back(TableChen);       //8
    MaisonChenTiles.push_back(TableChenGauche); //9
    MaisonChenTiles.push_back(TableChenDroite); //10
    MaisonChenTiles.push_back(TableHautGauche); //11
    MaisonChenTiles.push_back(TableHautDroite); //12
    MaisonChenTiles.push_back(TableHautBall);   //13
    MaisonChenTiles.push_back(PalierChen);      //14
    MaisonChenTiles.push_back(SolChen);         //15
    MaisonChenTiles.push_back(Scientifique);    //16
    MaisonChenTiles.push_back(Noir);            //17
    MaisonChenTiles.push_back(Chen);            //18

    // Propriéts Tiles Maison Blue

    PalierBlue.give_carte(PALETTE);
    PalierBlue.give_position(posBlueToPalette);
    std::vector<std::string> TXTBlueSister;
    TXTBlueSister.push_back("Mais où est passé");
    TXTBlueSister.push_back("Blue ?");
    BlueSister.give_txt(TXTBlueSister);
    BlueSister.give_nbPNJ(0);

    // Vecteur Tiles Maison Blue

    MaisonBlueTiles.push_back(MurBlueCarte);        //0
    MaisonBlueTiles.push_back(MurBlue);             //1
    MaisonBlueTiles.push_back(FenetreBlue);         //2
    MaisonBlueTiles.push_back(TeleBlueHaut);        //3
    MaisonBlueTiles.push_back(TeleBlueBas);         //4
    MaisonBlueTiles.push_back(RadioBlueHaut);       //5
    MaisonBlueTiles.push_back(RadioBlueBas);        //6
    MaisonBlueTiles.push_back(BiblioBlueHaut);      //7
    MaisonBlueTiles.push_back(BiblioBlueBas);       //8
    MaisonBlueTiles.push_back(BiblioBlueHaut2);     //9
    MaisonBlueTiles.push_back(BiblioBlueBas2);      //10
    MaisonBlueTiles.push_back(PlanteBas);           //11
    MaisonBlueTiles.push_back(PlanteHaut);          //12
    MaisonBlueTiles.push_back(TableBlueHautGauche); //13
    MaisonBlueTiles.push_back(TableBlueHautDroite); //14
    MaisonBlueTiles.push_back(TableBlueBasGauche);  //15
    MaisonBlueTiles.push_back(TableBlueBasDroite);  //16
    MaisonBlueTiles.push_back(TabouretBlue);        //17
    MaisonBlueTiles.push_back(SolBlue);             //18
    MaisonBlueTiles.push_back(PalierBlue);          //19
    MaisonBlueTiles.push_back(Noir);                //20
    MaisonBlueTiles.push_back(BlueSister);          //21

    // Propriétés Tiles Maison Red

    PalierRed.give_carte(PALETTE);
    PalierRed.give_position(posRedToPalette);
    EscalierRedHaut.give_carte(REDHAUT);
    EscalierRedHaut.give_position(posEscalierRed);
    EscalierRedBas.give_carte(REDBAS);
    EscalierRedBas.give_position(posEscalierRed);
    std::vector<std::string> TXTConsole;
    TXTConsole.push_back("Ma Super Nintendo...");
    TXTConsole.push_back("*Nostalgie*");
    std::vector<std::string> TXTLit;
    TXTLit.push_back("Une petite sieste...");
    TXTLit.push_back("Plus tard!");
    Console.give_txt(TXTConsole);
    LitBas.give_txt(TXTLit);
    LitHaut.give_txt(TXTLit);

    // Vecteur Tiles Maison Red

    MaisonRedTiles.push_back(MurRed);            //0
    MaisonRedTiles.push_back(FenetreRed);        //1
    MaisonRedTiles.push_back(TeleRedHaut);       //2
    MaisonRedTiles.push_back(TeleRedBas);        //3
    MaisonRedTiles.push_back(Tele);              //4
    MaisonRedTiles.push_back(Console);           //5
    MaisonRedTiles.push_back(MeubleRed);         //6
    MaisonRedTiles.push_back(BiblioRedHaut);     //7
    MaisonRedTiles.push_back(BiblioRedBas);      //8
    MaisonRedTiles.push_back(BiblioRedHaut2);    //9
    MaisonRedTiles.push_back(BiblioRedBas2);     //10
    MaisonRedTiles.push_back(TableHautGauche);   //11
    MaisonRedTiles.push_back(TableHautDroite);   //12
    MaisonRedTiles.push_back(TableBasGauche);    //13
    MaisonRedTiles.push_back(TableBasDroite);    //14
    MaisonRedTiles.push_back(TableRedGauche);    //15
    MaisonRedTiles.push_back(TableRedDroite);    //16
    MaisonRedTiles.push_back(TabouretRed);       //17
    MaisonRedTiles.push_back(LitHaut);           //18
    MaisonRedTiles.push_back(LitBas);            //19
    MaisonRedTiles.push_back(OrdiRedHaut);       //20
    MaisonRedTiles.push_back(OrdiRedBas);        //21
    MaisonRedTiles.push_back(SolRed);            //22
    MaisonRedTiles.push_back(PalierRed);         //23
    MaisonRedTiles.push_back(EscalierRedHaut);   //24
    MaisonRedTiles.push_back(EscalierRedBas);    //25
    MaisonRedTiles.push_back(PetiteTableGauche); //26
    MaisonRedTiles.push_back(PetiteTableDrotie); //27
    MaisonRedTiles.push_back(Noir);              //28

    // Propriétés Tiles Centre Pokemon

    PalierCentre.give_carte(JADIELLE);
    PalierCentre.give_position(posPokeToJadielle);
    std::vector<std::string> TXTInfirmiere;
    TXTInfirmiere.push_back("Vos Pokémon sont en");
    TXTInfirmiere.push_back("super forme!");
    ComptoirSoin.give_txt(TXTInfirmiere);
    Infirmiere.give_nbPNJ(0);

    // Vecteur Tiles Centre Pokemon

    CentrePokemonTiles.push_back(SolCentre);           //0
    CentrePokemonTiles.push_back(SolCentreOmbre);      //1
    CentrePokemonTiles.push_back(FauteuilCentre);      //2
    CentrePokemonTiles.push_back(MurCentre);           //3
    CentrePokemonTiles.push_back(MurCentreComptoir);   //4
    CentrePokemonTiles.push_back(Comptoir);            //5
    CentrePokemonTiles.push_back(ComptoirBas);         //6
    CentrePokemonTiles.push_back(ComptoirHaut);        //7
    CentrePokemonTiles.push_back(Sonnette);            //8
    CentrePokemonTiles.push_back(SonnetteDouble);      //9
    CentrePokemonTiles.push_back(SoinHautGauche);      //10
    CentrePokemonTiles.push_back(SoinHautDroite);      //11
    CentrePokemonTiles.push_back(SoinBasGauche);       //12
    CentrePokemonTiles.push_back(SoinBasDroite);       //13
    CentrePokemonTiles.push_back(OrdiSoin);            //14
    CentrePokemonTiles.push_back(ClavierSoin);         //15
    CentrePokemonTiles.push_back(OrdiCentreHaut);      //16
    CentrePokemonTiles.push_back(OrdiRedBas);          //17
    CentrePokemonTiles.push_back(PalierCentre);        //18
    CentrePokemonTiles.push_back(Noir);                //19
    CentrePokemonTiles.push_back(ComptoirSoin);        //20
    CentrePokemonTiles.push_back(Infirmiere);          //21

    // Propriétés Tiles Jadielle

    RouteRoute1.give_carte(ROUTE1);
    RouteRoute1.give_position(posJadielleToRoute1D);
    RouteRoute1b.give_carte(ROUTE1);
    RouteRoute1b.give_position(posJadielleToRoute1G);
    RouteRoute22.give_carte(ROUTE22);
    RouteRoute22.give_position(posJadielleToRoute22B);
    RouteRoute22b.give_carte(ROUTE22);
    RouteRoute22b.give_position(posJadielleToRoute22H);
    HerbeRoute22.give_carte(ROUTE22);
    HerbeRoute22.give_position(posJadielleToRoute22HerbeB);
    HerbeRoute22b.give_carte(ROUTE22);
    HerbeRoute22b.give_position(posJadielleToRoute22HerbeH);
    PorteJadielle1.give_carte(CENTREPOKEMON);
    PorteJadielle1.give_position(posJadielleToCentrePokemon);
    JadielleToRoute2D.give_carte(ROUTE2);
    JadielleToRoute2D.give_position(posJadielleToRoute2D);
    JadielleToRoute2G.give_carte(ROUTE2);
    JadielleToRoute2G.give_position(posJadielleToRoute2G);
    JadielleToRoute2.give_carte(ROUTE2);
    JadielleToRoute2.give_position(posJadielleToRoute2);
    std::vector<std::string> TXTPanneauJadielle1;
    TXTPanneauJadielle1.push_back("JADIELLE");
    TXTPanneauJadielle1.push_back("");
    TXTPanneauJadielle1.push_back("Le paradis vert");
    TXTPanneauJadielle1.push_back("éternel");
    std::vector<std::string> TXTPanneauJadielle2;
    TXTPanneauJadielle2.push_back("CLUB des DRESSEURS");
    TXTPanneauJadielle2.push_back("");
    TXTPanneauJadielle2.push_back("réservé aux");
    TXTPanneauJadielle2.push_back("meilleurs");
    std::vector<std::string> TXTPanneauJadielle3;
    TXTPanneauJadielle3.push_back("Avis: Arène fermée");
    std::vector<std::string> TXTPanneauJadielle4;
    TXTPanneauJadielle4.push_back("Bienvenue à");
    TXTPanneauJadielle4.push_back("JADIELLE, la porte");
    TXTPanneauJadielle4.push_back("vers le PLATEAU");
    TXTPanneauJadielle4.push_back("INDIGO");
    std::vector<std::string> TXTSaoul;
    TXTSaoul.push_back("PASSAGE INTERDIT!");
    std::vector<std::string> TXTFillette;
    TXTFillette.push_back("Papy, tu as encore");
    TXTFillette.push_back("trop bu...");
    Saoul.give_nbPNJ(0);
    Fillette.give_nbPNJ(1);
    Saoul.give_txt(TXTSaoul);
    Fillette.give_txt(TXTFillette);
    PanneauJadielle1.give_txt(TXTPanneauJadielle1);
    PanneauJadielle2.give_txt(TXTPanneauJadielle2);
    PanneauJadielle3.give_txt(TXTPanneauJadielle3);
    PanneauJadielle4.give_txt(TXTPanneauJadielle4);

    // Vecteur Tiles Jadielle

    JadielleTiles.push_back(Herbe);                      //0
    JadielleTiles.push_back(Route);                      //1
    JadielleTiles.push_back(RouteGravier);               //2
    JadielleTiles.push_back(Bloc);                       //3
    JadielleTiles.push_back(Roche);                      //4
    JadielleTiles.push_back(FleurGauche);                //5
    JadielleTiles.push_back(FleurDroite);                //6
    JadielleTiles.push_back(BarriereVille);              //7
    JadielleTiles.push_back(Montagne);                   //8
    JadielleTiles.push_back(MontagneBas);                //9
    JadielleTiles.push_back(MontagneDroite);             //10
    JadielleTiles.push_back(MontagneHaut);               //11
    JadielleTiles.push_back(MontagneCoinBasDroite);      //12
    JadielleTiles.push_back(MontagneCoinHautDroite);     //13
    JadielleTiles.push_back(ArbreCoupe);                 //14
    JadielleTiles.push_back(BarriereChemin);             //15
    JadielleTiles.push_back(BarriereHerbe);              //16
    JadielleTiles.push_back(Passage);                    //17
    JadielleTiles.push_back(Eau);                        //18
    JadielleTiles.push_back(EauGauche);                  //19
    JadielleTiles.push_back(EauDroite);                  //20
    JadielleTiles.push_back(EauHaut);                    //21
    JadielleTiles.push_back(EauCoinGauche);              //22
    JadielleTiles.push_back(EauCoinDroite);              //23
    JadielleTiles.push_back(MaisonBas);                  //24
    JadielleTiles.push_back(MaisonToitBasGauche);        //25
    JadielleTiles.push_back(MaisonToitBasDroite);        //26
    JadielleTiles.push_back(ToitGauche);                 //27
    JadielleTiles.push_back(ToitDroite);                 //28
    JadielleTiles.push_back(Toit);                       //29
    JadielleTiles.push_back(MaisonBasBis);               //30
    JadielleTiles.push_back(MaisonHauteFenetre2);        //31
    JadielleTiles.push_back(MaisonBasGaucheFenetre);     //32
    JadielleTiles.push_back(MaisonBasDroiteFentre);      //33
    JadielleTiles.push_back(ToitVertBas);                //34
    JadielleTiles.push_back(ToitVertHaut);               //35
    JadielleTiles.push_back(GrandToitVertHautGauche);    //36
    JadielleTiles.push_back(GrandToitVertGauche);        //37
    JadielleTiles.push_back(GrandToitVertBasGauche);     //38
    JadielleTiles.push_back(GrandToitVertHautDroite);    //39
    JadielleTiles.push_back(GrandToitVertDroite);        //40
    JadielleTiles.push_back(GrandToitVertBasDroite);     //41
    JadielleTiles.push_back(MaisonGymGauche);            //42
    JadielleTiles.push_back(MaisonGymDroite);            //43
    JadielleTiles.push_back(MaisonPoke);                 //44
    JadielleTiles.push_back(MaisonMart);                 //45
    JadielleTiles.push_back(MaisonBriqueBas);            //46
    JadielleTiles.push_back(MaisonBriqueFenetre2);       //47
    JadielleTiles.push_back(MaisonBriqueFenetre2bis);    //48
    JadielleTiles.push_back(MaisonBriqueBasGauche);      //49
    JadielleTiles.push_back(MaisonBriqueBasDroite);      //50
    JadielleTiles.push_back(MaisonBriqueHautGauche);     //51
    JadielleTiles.push_back(MaisonBriqueHautDroite);     //52
    JadielleTiles.push_back(ToitGrisBas);                //53
    JadielleTiles.push_back(ToitGrisHaut);               //54
    JadielleTiles.push_back(ToitGrisHautGauche);         //55
    JadielleTiles.push_back(ToitGrisBasGauche);          //56
    JadielleTiles.push_back(ToitGrisHautDroite);         //57
    JadielleTiles.push_back(ToitGrisBasDroite);          //58
    JadielleTiles.push_back(PanneauJadielle1);           //59
    JadielleTiles.push_back(PanneauJadielle2);           //60
    JadielleTiles.push_back(PanneauJadielle3);           //61
    JadielleTiles.push_back(PanneauJadielle4);           //62
    JadielleTiles.push_back(PorteJadielle1);             //63
    JadielleTiles.push_back(PorteJadielle2);             //64
    JadielleTiles.push_back(PorteJadielle3);             //65
    JadielleTiles.push_back(PorteJadielle4);             //66
    JadielleTiles.push_back(PorteJadielle5);             //67
    JadielleTiles.push_back(RouteRoute1);                //68
    JadielleTiles.push_back(RouteRoute1b);               //69
    JadielleTiles.push_back(RouteRoute22);               //70
    JadielleTiles.push_back(Saoul);                      //71
    JadielleTiles.push_back(Fillette);                   //72
    JadielleTiles.push_back(MontagneGauche);             //73
    JadielleTiles.push_back(MontagneCoinBasGauche);      //74
    JadielleTiles.push_back(MontagneCoinHautGauche);     //75
    JadielleTiles.push_back(RouteRoute22b);              //76
    JadielleTiles.push_back(HerbeRoute22);               //77
    JadielleTiles.push_back(HerbeRoute22b);              //78
    JadielleTiles.push_back(HerbeBloc);                  //79
    JadielleTiles.push_back(RouteBloc);                  //80
    JadielleTiles.push_back(RouteMiGravierBloc);         //81
    JadielleTiles.push_back(JadielleToRoute2G);          //82
    JadielleTiles.push_back(JadielleToRoute2D);          //83
    JadielleTiles.push_back(RouteMiGravier);             //84
    JadielleTiles.push_back(RouteGravierBloc);           //85
    JadielleTiles.push_back(JadielleToRoute2);           //86

    // Propriétés Tiles Argenta

    ArgentaToRoute2G.give_carte(ROUTE2);
    ArgentaToRoute2G.give_position(posArgentaToRoute2G);
    ArgentaToRoute2D.give_carte(ROUTE2);
    ArgentaToRoute2D.give_position(posArgentaToRoute2D);
    std::vector<std::string> TXTPanneauArgenta1;
    TXTPanneauArgenta1.push_back("ARGENTA");
    TXTPanneauArgenta1.push_back("");
    TXTPanneauArgenta1.push_back("Le mat et le");
    TXTPanneauArgenta1.push_back("gris de la roche");
    std::vector<std::string> TXTPanneauArgenta2;
    TXTPanneauArgenta2.push_back("");
    std::vector<std::string> TXTPanneauArgenta3;
    TXTPanneauArgenta3.push_back("");
    std::vector<std::string> TXTPanneauArgenta4;
    TXTPanneauArgenta4.push_back("");
    std::vector<std::string> TXTPanneauArgenta5;
    TXTPanneauArgenta5.push_back("");
    PanneauArgenta1.give_txt(TXTPanneauArgenta1);
    PanneauArgenta2.give_txt(TXTPanneauArgenta2);
    PanneauArgenta3.give_txt(TXTPanneauArgenta3);
    PanneauArgenta4.give_txt(TXTPanneauArgenta4);
    PanneauArgenta5.give_txt(TXTPanneauArgenta5);

    // Vecteur Tiles Argenta

    ArgentaTiles.push_back(Herbe);                    //0
    ArgentaTiles.push_back(Route);                    //1
    ArgentaTiles.push_back(RouteMiGravier);           //2
    ArgentaTiles.push_back(RouteGravier);             //3
    ArgentaTiles.push_back(Bloc);                     //4
    ArgentaTiles.push_back(Roche);                    //5
    ArgentaTiles.push_back(FleurGauche);              //6
    ArgentaTiles.push_back(FleurDroite);              //7
    ArgentaTiles.push_back(BarriereVille);            //8
    ArgentaTiles.push_back(BarriereHerbe);            //9
    ArgentaTiles.push_back(BarriereChemin);           //10
    ArgentaTiles.push_back(Passage);                  //11
    ArgentaTiles.push_back(PanneauArgenta1);          //12
    ArgentaTiles.push_back(PanneauArgenta2);          //13
    ArgentaTiles.push_back(PanneauArgenta3);          //14
    ArgentaTiles.push_back(PanneauArgenta4);          //15
    ArgentaTiles.push_back(PanneauArgenta5);          //16
    ArgentaTiles.push_back(Montagne);                 //17
    ArgentaTiles.push_back(MontagneBas);              //18
    ArgentaTiles.push_back(MontagneHaut);             //19
    ArgentaTiles.push_back(MontagneDroite);           //20
    ArgentaTiles.push_back(MontagneGauche);           //21
    ArgentaTiles.push_back(MontagneCoinBasDroite);    //22
    ArgentaTiles.push_back(MontagneCoinBasGauche);    //23
    ArgentaTiles.push_back(MontagneCoinHautDroite);   //24
    ArgentaTiles.push_back(MontagneCoinHautGauche);   //25
    ArgentaTiles.push_back(MaisonBas);                //26
    ArgentaTiles.push_back(MaisonToitBasGauche);      //27
    ArgentaTiles.push_back(MaisonToitBasDroite);      //28
    ArgentaTiles.push_back(Toit);                     //29
    ArgentaTiles.push_back(ToitGauche);               //30
    ArgentaTiles.push_back(ToitDroite);               //31
    ArgentaTiles.push_back(MaisonBasGaucheFenetre);   //32
    ArgentaTiles.push_back(MaisonBasDroiteFentre);    //33
    ArgentaTiles.push_back(MaisonHauteFenetre2);      //34
    ArgentaTiles.push_back(MaisonGymGauche);          //35
    ArgentaTiles.push_back(MaisonGymDroite);          //36
    ArgentaTiles.push_back(GrandToitVertBasGauche);   //37
    ArgentaTiles.push_back(GrandToitVertBasDroite);   //38
    ArgentaTiles.push_back(GrandToitVertHautGauche);  //39
    ArgentaTiles.push_back(GrandToitVertHautDroite);  //40
    ArgentaTiles.push_back(GrandToitVertGauche);      //41
    ArgentaTiles.push_back(GrandToitVertDroite);      //42
    ArgentaTiles.push_back(ToitVertHaut);             //43
    ArgentaTiles.push_back(ToitVertBas);              //44
    ArgentaTiles.push_back(MaisonMart);               //45
    ArgentaTiles.push_back(MaisonPoke);               //46
    ArgentaTiles.push_back(MaisonBriqueBas);          //47
    ArgentaTiles.push_back(MaisonBriqueBasDroite);    //48
    ArgentaTiles.push_back(MaisonBriqueBasGauche);    //49
    ArgentaTiles.push_back(MaisonBriqueFenetre2);     //50
    ArgentaTiles.push_back(MaisonBriqueFenetre2bis);  //51
    ArgentaTiles.push_back(MaisonBriqueHautGauche);   //52
    ArgentaTiles.push_back(MaisonBriqueHautDroite);   //53
    ArgentaTiles.push_back(ToitGrisHautGauche);       //54
    ArgentaTiles.push_back(ToitGrisHautDroite);       //55
    ArgentaTiles.push_back(ToitGrisBasGauche);        //56
    ArgentaTiles.push_back(ToitGrisBasDroite);        //57
    ArgentaTiles.push_back(ToitGrisHaut);             //58
    ArgentaTiles.push_back(ToitGrisBas);              //59
    ArgentaTiles.push_back(GrandToitVertGauchebis);   //60
    ArgentaTiles.push_back(GrandToitVertDroitebis);   //61
    ArgentaTiles.push_back(GrandToitVertBasGauchebis);//62
    ArgentaTiles.push_back(GrandToitVertBasDroitebis);//63
    ArgentaTiles.push_back(ToitVert);                 //64
    ArgentaTiles.push_back(GrandToitVertBas);         //65
    ArgentaTiles.push_back(MaisonHautGauche);         //66 A remplacer
    ArgentaTiles.push_back(MaisonHautDroite);         //67 A remplacer
    ArgentaTiles.push_back(PorteArgenta1);            //68
    ArgentaTiles.push_back(PorteArgenta2);            //69
    ArgentaTiles.push_back(PorteArgenta3);            //70
    ArgentaTiles.push_back(PorteArgenta4);            //71
    ArgentaTiles.push_back(PorteArgenta5);            //72
    ArgentaTiles.push_back(MontagneCreuxGauche);      //73
    ArgentaTiles.push_back(HauteHerbe);               //74
    ArgentaTiles.push_back(ArgentaToRoute2G);         //75
    ArgentaTiles.push_back(ArgentaToRoute2D);         //76



    SDL_Rect perso;
    SDL_Surface *gold[8] = {NULL};
    gold[HAUT] = SDL_LoadBMP("tiles_perso/gold_haut.bmp");
    gold[BAS] = SDL_LoadBMP("tiles_perso/gold_bas.bmp");
    gold[DROITE] = SDL_LoadBMP("tiles_perso/gold_right.bmp");
    gold[GAUCHE] = SDL_LoadBMP("tiles_perso/gold_left.bmp");
    gold[MI_HAUT] = SDL_LoadBMP("tiles_perso/gold_haut_mouv.bmp");
    gold[MI_BAS] = SDL_LoadBMP("tiles_perso/gold_bas_mouv.bmp");
    gold[MI_DROITE] = SDL_LoadBMP("tiles_perso/gold_right_mouv.bmp");
    gold[MI_GAUCHE] = SDL_LoadBMP("tiles_perso/gold_left_mouv.bmp");

    SDL_Surface* screen;
    screen = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	Map* carte;
	Input in;
	int LARGEUR_TILE,HAUTEUR_TILE;
	LARGEUR_TILE = 16;
	HAUTEUR_TILE = 16;
	int i = 0;
	memset(&in,0,sizeof(in));

	//carte = ChargerMap("TilesRoute1.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
	perso.x = 272;
	perso.y = 160;
	perso.w = 16;
	perso.h = 16;

	/*while(!in.key[SDLK_ESCAPE])
	{
		UpdateEvents(&in);
        Evolue(&in,carte,&perso,LARGEUR_TILE,HAUTEUR_TILE);
        FocusScrollCenter(carte,&perso);
        AfficherMap(carte,screen);
        AfficherPerso(&perso,screen,carte->xscroll,carte->yscroll,gold[i]);
        SDL_Flip(screen);
        SDL_Delay(50);

	}*/
	jouer();

    return 0;
}
