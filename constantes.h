/*
Nicolas ALEXANDRE
constantes.h
Défini des constantes pour tout le programme
*/
#include "Dresseur.h"
#include "Attaque.h"
#include "Tile.h"


#ifndef CONSTANTES_H
#define CONSTANTES_H

    #define TAILLE_BLOC 16 //taille d'un bloc carré en pixel
    #define TAILLE_BARRE_VIE 48
    #define TAILLE_BARRE_XP 64
    #define NB_BLOC_LARGEUR_ROUTE1 23
    #define NB_BLOC_HAUTEUR_ROUTE1 45
    #define NB_BLOC_LARGEUR_ROUTE2 31
    #define NB_BLOC_HAUTEUR_ROUTE2 64
    #define NB_BLOC_LARGEUR_ROUTE22 40
    #define NB_BLOC_HAUTEUR_ROUTE22 24
    #define NB_BLOC_LARGEUR_BOURGPALETTE 30
    #define NB_BLOC_HAUTEUR_BOURGPALETTE 30
    #define NB_BLOC_LARGEUR_MAISONCHEN 21
    #define NB_BLOC_HAUTEUR_MAISONCHEN 22
    #define NB_BLOC_LARGEUR_MAISON 19
    #define NB_BLOC_HAUTEUR_MAISON 18
    #define NB_BLOC_LARGEUR_CENTREPOKEMON 21
    #define NB_BLOC_HAUTEUR_CENTREPOKEMON 18
    #define NB_BLOC_LARGEUR_JADIELLE 47
    #define NB_BLOC_HAUTEUR_JADIELLE 48
    #define NB_BLOC_HAUTEUR_ARGENTA 43
    #define NB_BLOC_LARGEUR_ARGENTA 41
    #define LARGEUR_FENETRE_ROUTE1 TAILLE_BLOC * NB_BLOC_LARGEUR_ROUTE1
    #define HAUTEUR_FENETRE_ROUTE1 TAILLE_BLOC * NB_BLOC_HAUTEUR_ROUTE1
    #define LARGEUR_FENETRE_BOURGPALETTE TAILLE_BLOC * NB_BLOC_LARGEUR_BOURGPALETTE
    #define HAUTEUR_FENETRE_BOURGPALETTE TAILLE_BLOC * NB_BLOC_HAUTEUR_BOURGPALETTE
    #define LARGEUR_FENETRE_MAISONCHEN TAILLE_BLOC * NB_BLOC_LARGEUR_MAISONCHEN
    #define HAUTEUR_FENETRE_MAISONCHEN TAILLE_BLOC * NB_BLOC_HAUTEUR_MAISONCHEN
    #define LARGEUR_FENETRE_MAISON TAILLE_BLOC * NB_BLOC_LARGEUR_MAISON
    #define HAUTEUR_FENETRE_MAISON TAILLE_BLOC * NB_BLOC_LARGEUR_MAISON
    #define LARGEUR_FENETRE_COMBAT 160
    #define HAUTEUR_FENETRE_COMBAT 144

    // 4 Directions que peut prendre le personnage
    // Les directions MI_DIRECTION correspondent au personnage en mouvement
    enum {HAUT, BAS, GAUCHE, DROITE, MI_HAUT, MI_BAS, MI_GAUCHE, MI_DROITE};
    // Types de Tiles
    enum {OBSTACLE, TXT, PNJ, SOIN, BALL, UNIDIR, CHANGEMAP, PASSAGE, COMBATPKM, COMBATPNJ};
    // Numéro des Cartes
    enum {REDBAS,REDHAUT,BLUE,PALETTE,CHEN,CENTREPOKEMON,ROUTE1,ROUTE2,ROUTE22,JADIELLE,ARGENTA};
    // Type de courbe d'expérience
    enum {RAPIDE, MOYENNE, PARABOLIQUE, LENTE};
    // Type du Pokemon
    enum {NORMAL, COMBAT, VOL, POISON, SOL, ROCHE, INSECTE, SPECTRE, ACIER, PLANTE, FEU, EAU, ELECTRIK, PSY, GLACE, DRAGON, TENEBRES};
    // Stat
    enum {ATT,DEF,ATTSPE,DEFSPE,VIT,PREC};

    // Création des Attaques

    Attaque Eclair("ECLAIR",40,ELECTRIK,100,false);
    Attaque ViveAttaque("VIVE-ATTAQUE",40,NORMAL,100,false);
    Attaque Charge("CHARGE",50,NORMAL,100,false);
    Attaque Griffe("GRIFFE",40,NORMAL,100,false);
    Attaque Tornade("TORNADE",40,VOL,100,false);
    Attaque Picpic("PICPIC",35,VOL,100,false);
    Attaque Aeropique("AEROPIQUE",60,VOL,301,false);
    Attaque Morsure("MORSURE",60,TENEBRES,100,false);
    Attaque Blizzard("BLIZZARD",110,GLACE,70,false);
    Attaque Meteore("METEORE",60,NORMAL,301,false);
    Attaque FouetLianes("FOUET LIANES",45,PLANTE,100,false);
    Attaque Flammeche("FLAMMECHE",40,FEU,100,false);
    Attaque PistoletaO("PISTOLET A O",40,EAU,100,false);
    Attaque Souplesse("SOUPLESSE",80,NORMAL,75,false);
    Attaque Poursuite("POURSUITE",40,TENEBRES,100,false);
    Attaque TranchHerbe("TRANCH'HERBE",55,PLANTE,95,false);
    Attaque Belier("BELIER",90,NORMAL,85,false);
    Attaque LanceSoleil("LANCE-SOLEIL",120,PLANTE,100,false);
    Attaque Damocles("DAMOCLES",120,NORMAL,100,false);
    Attaque Dracosouffle("DRACOSOUFFLE",60,DRAGON,100,false);
    Attaque LanceFlamme("LANCE-FLAMME",90,FEU,100,false);
    Attaque Deflagration("DEFLAGRATION",110,FEU,85,false);
    Attaque Tranche("TRANCHE",70,NORMAL,100,false);
    Attaque CoudKrane("COUD'KRANE",130,NORMAL,100,false);
    Attaque Hydrocanon("HYDROCANON",110,EAU,80,false);
    Attaque Surf("SURF",90,EAU,100,false);
    Attaque ChocMental("CHOC MENTAL",50,PSY,100,false);
    Attaque DardVenin("DARD-VENIN",15,POISON,100,false);

    Attaque MimiQueue("MIMI-QUEUE",0,NORMAL,100,true);
    Attaque Rugissement("RUGISSEMENT",0,NORMAL,100,true);
    Attaque Grozyeux("GROZ'YEUX",0,NORMAL,100,true);
    Attaque Grimace("GRIMACE",0,NORMAL,90,true);
    Attaque Secretion("SECRETION",0,INSECTE,100,true);
    Attaque Armure("ARMURE",0,NORMAL,100,true);
    Attaque Repli("REPLI",0,EAU,100,true);
    Attaque JetDeSable("JET DE SABLE",0,SOL,100,true);

    // Création des Pokemons

    Pokemon Bulbizarre;// = Pokemon("BULBIZARRE", "pokemon_back/bulbizarre_back.bmp", "pokemon_front/bulbizarre_front.bmp", "cris/001Cry.wav", 7,45,49,49,65,65,45,64,PARABOLIQUE,PLANTE);
    std::vector<Attaque> ATKBulbizarre;

    Pokemon Herbizarre;// = Pokemon("HERBIZARRE", "pokemon_back/herbizarre_back.bmp", "pokemon_front/herbizarre_front.bmp", "cris/002Cry.wav", 16,60,62,63,80,80,60,141,PARABOLIQUE,PLANTE);
    std::vector<Attaque> ATKHerbizarre;

    Pokemon Florizarre;// = Pokemon("FLORIZARRE", "pokemon_back/florizarre_back.bmp", "pokemon_front/florizarre_front.bmp", "cris/003Cry.wav", 32,80,82,83,100,100,80,208,PARABOLIQUE,PLANTE);
    std::vector<Attaque> ATKFlorizarre;

    Pokemon Salameche;// = Pokemon("SALAMECHE", "pokemon_back/salameche_back.bmp", "pokemon_front/salameche_front.bmp", "cris/004Cry.wav", 7,39,52,43,60,50,65,65,PARABOLIQUE,FEU);
    std::vector<Attaque> ATKSalameche;

    Pokemon Reptincel;// = Pokemon("REPTINCEL", "pokemon_back/reptincel_back.bmp", "pokemon_front/reptincel_front.bmp","cris/005Cry.wav", 16,58,64,58,80,65,80,142,PARABOLIQUE,FEU);
    std::vector<Attaque> ATKReptincel;

    Pokemon Dracaufeu;// = Pokemon("DRACAUFEU", "pokemon_back/dracaufeu_back.bmp", "pokemon_front/dracaufeu_front.bmp","cris/006Cry.wav", 36,78,84,78,109,85,100,209,PARABOLIQUE,FEU);
    std::vector<Attaque> ATKDracaufeu;

    Pokemon Carapuce;// = Pokemon("CARAPUCE", "pokemon_back/carapuce_back.bmp", "pokemon_front/carapuce_front.bmp", "cris/007Cry.wav", 7,44,48,65,50,64,43,66,PARABOLIQUE,EAU);
    std::vector<Attaque> ATKCarapuce;

    Pokemon Carabaffe;// = Pokemon("CARABAFFE", "pokemon_back/carabaffe_back.bmp", "pokemon_front/carabaffe_front.bmp", "cris/008Cry.wav", 16,59,63,80,65,80,58,143,PARABOLIQUE,EAU);
    std::vector<Attaque> ATKCarabaffe;

    Pokemon Tortank;// = Pokemon("TORTANK", "pokemon_back/tortank_back.bmp", "pokemon_front/tortank_front.bmp", "cris/009Cry.wav", 36,79,83,100,85,105,78,210,PARABOLIQUE,EAU);
    std::vector<Attaque> ATKTortank;

    Pokemon Chenipan;
    std::vector<Attaque> ATKChenipan;

    Pokemon Chrysacier;
    std::vector<Attaque> ATKChrysacier;

    Pokemon Papilusion;
    std::vector<Attaque> ATKPapilusion;

    Pokemon Aspicot;
    std::vector<Attaque> ATKAspicot;

    Pokemon Coconfort;
    std::vector<Attaque> ATKCoconfort;

    Pokemon Dardargnan;
    std::vector<Attaque> ATKDardargnan;

    Pokemon Roucool;// = Pokemon("ROUCOOL","pokemon_back/roucool_back.bmp", "pokemon_front/roucool_front.bmp","cris/016Cry.wav", 3,40,45,40,35,35,56,55,PARABOLIQUE,VOL);
    std::vector<Attaque> ATKRoucool;

    Pokemon Roucoups;
    std::vector<Attaque> ATKRoucoups;

    Pokemon Roucarnage;
    std::vector<Attaque> ATKRoucarnage;

    Pokemon Rattata;// = Pokemon("RATTATA","pokemon_back/rattata_back.bmp", "pokemon_front/rattata_front.bmp","cris/019Cry.wav", 3,30,56,35,25,35,72,57,MOYENNE,NORMAL);
    std::vector<Attaque> ATKRattata;

    Pokemon Piafabec;// = Pokemon("PIAFABEC","pokemon_back/piafabec_back.bmp","pokemon_front/piafabec_front.bmp","cris/021Cry.wav", 4,40,60,30,31,31,70,58,MOYENNE,VOL);
    std::vector<Attaque> ATKPiafabec;

    Pokemon Rapasdepic;// = Pokemon("RAPASDEPIC","pokemon_back/rapasdepic_back.bmp","pokemon_front/rapasdepic_front.bmp","cris/022Cry.wav", 7,65,90,65,61,61,100,162,MOYENNE,VOL);
    std::vector<Attaque> ATKRapasdepic;

    Pokemon Pikachu;// = Pokemon("PIKACHU", "pokemon_back/pikachu_back.bmp", "pokemon_front/pikachu_front.bmp","cris/025Cry.wav", 7,35,55,40,50,50,90,82,MOYENNE,ELECTRIK);
    std::vector<Attaque> ATKPikachu;

    Pokemon Ponyta;// = Pokemon("PONYTA","pokemon_back/ponyta_back.bmp", "pokemon_front/ponyta_front.bmp","cris/077Cry.wav", 6,50,85,55,65,65,90,152,MOYENNE,FEU);
    std::vector<Attaque> ATKPonyta;

    Pokemon Doduo;// = Pokemon("DODUO","pokemon_back/doduo_back.bmp", "pokemon_front/doduo_front.bmp","cris/084Cry.wav", 4,35,85,45,35,35,75,96,MOYENNE,VOL);
    std::vector<Attaque> ATKDoduo;

    Pokemon Evoli;// = Pokemon("EVOLI","pokemon_back/evoli_back.bmp", "pokemon_front/evoli_front.bmp","cris/133Cry.wav", 5,55,55,50,45,65,55,92,MOYENNE,NORMAL);
    std::vector<Attaque> ATKEvoli;

    Pokemon Fouinette;// = Pokemon("FOUINETTE","pokemon_back/fouinette_back.bmp", "pokemon_front/fouinette_front.bmp","cris/161Cry.wav", 3,35,46,34,35,45,20,57,MOYENNE,NORMAL);
    std::vector<Attaque> ATKFouinette;

    Pokemon Fouinar;// = Pokemon("FOUINAR","pokemon_back/fouinar_back.bmp", "pokemon_front/fouinar_front.bmp","cris/162Cry.wav", 5,85,76,64,45,55,90,116,MOYENNE,NORMAL);
    std::vector<Attaque> ATKFouinar;

    Pokemon Coxy;
    std::vector<Attaque> ATKCoxy;

    Pokemon Suicune;// = Pokemon("SUICUNE","pokemon_back/suicune_back.bmp", "pokemon_front/suicune_front.bmp","cris/245Cry.wav",40,100,75,115,90,115,85,216,LENTE,EAU);
    std::vector<Attaque> ATKSuicune;


    // Création des dresseurs
    Dresseur Gold;// = Dresseur("GOLD", "gold_combat.bmp");

    std::vector<Pokemon> TeamGold;

    Dresseur Silver;// = Dresseur("SILVER", "silver_combat.bmp");
    std::vector<Pokemon> TeamSilver;

    // Création des tiles
    // Propriété : 0=obstacle, 1=emplacement dresseur, 2=passage unidirectionnel vers le bas, 3=changement de carte, 4=passage, 5=combat aléatoire, 6=combat dresseur,

    Tile ArbreCoupe;
    Tile ArgentaToRoute2G;
    Tile ArgentaToRoute2D;
    Tile CombatSilver;
    Tile BarriereChemin;
    Tile BarriereHerbe;
    Tile BarriereVille;
    Tile BiblioBlueHaut;
    Tile BiblioBlueBas;
    Tile BiblioBlueHaut2;
    Tile BiblioBlueBas2;
    Tile BiblioChenBas;
    Tile BiblioChenHaut;
    Tile BiblioRedBas;
    Tile BiblioRedHaut;
    Tile BiblioRedBas2;
    Tile BiblioRedHaut2;
    Tile Bloc;
    Tile BlueSister;
    Tile ClavierSoin;
    Tile Chen;
    Tile Comptoir;
    Tile ComptoirHaut;
    Tile ComptoirBas;
    Tile ComptoirSoin;
    Tile Console;
    Tile DiplomeChen;
    Tile PNJDresseur;
    Tile Eau;
    Tile EauDroite;
    Tile EauGauche;
    Tile EauHaut;
    Tile EauCoinDroite;
    Tile EauCoinGauche;
    Tile EcranOrdi;
    Tile EscalierRedBas;
    Tile EscalierRedHaut;
    Tile FauteuilCentre;
    Tile FenetreBlue;
    Tile FenetreChen;
    Tile FenetreRed;
    Tile Fillette;
    Tile FleurDroite;
    Tile FleurGauche;
    Tile GrandToitVertGauche;
    Tile GrandToitVertDroite;
    Tile GrandToitVertHautGauche;
    Tile GrandToitVertHautDroite;
    Tile GrandToitVertBasGauche;
    Tile GrandToitVertBasDroite;
    Tile GrandToitVertBasDroitebis;
    Tile GrandToitVertBasGauchebis;
    Tile GrandToitVertGauchebis;
    Tile GrandToitVertDroitebis;
    Tile GrandToitVertBas;
    Tile Gros;
    Tile GrotteRoute2;
    Tile HauteHerbe;
    Tile HautesHerbes;
    Tile HautesHerbesRoute1;
    Tile HautesHerbesRoute1b;
    Tile HautesHerbesPalette;
    Tile HautesHerbesPaletteb;
    Tile HautesHerbesBloc;
    Tile Herbe;
    Tile HerbeBloc;
    Tile HerbeRoute22;
    Tile HerbeRoute22b;
    Tile HerbeJadielle;
    Tile HerbeJadielleb;
    Tile Infirmiere;
    Tile JadielleToRoute2D;
    Tile JadielleToRoute2G;
    Tile JadielleToRoute2;
    Tile LitBas;
    Tile LitHaut;
    Tile MaisonBas;
    Tile MaisonBasBis;
    Tile MaisonBasDroite;
    Tile MaisonBasGauche;
    Tile MaisonBasGaucheFenetre;
    Tile MaisonBasDroiteFentre;
    Tile MaisonHautDroite;
    Tile MaisonHautFenetre1;
    Tile MaisonHautFenetre2;
    Tile MaisonHauteFenetre2;
    Tile MaisonHautGauche;
    Tile MaisonBriqueBas;
    Tile MaisonBriqueBasDroite;
    Tile MaisonBriqueBasGauche;
    Tile MaisonBriqueFenetre1;
    Tile MaisonBriqueFenetre1bis;
    Tile MaisonBriqueFenetre2;
    Tile MaisonBriqueFenetre2bis;
    Tile MaisonBriqueHautDroite;
    Tile MaisonBriqueHautGauche;
    Tile MaisonToitBasGauche;
    Tile MaisonToitBasDroite;
    Tile MaisonPoke;
    Tile MaisonMart;
    Tile MaisonGymGauche;
    Tile MaisonGymDroite;
    Tile MeubleRed;
    Tile Montagne;
    Tile MontagneBas;
    Tile MontagneCoinBasDroite;
    Tile MontagneCoinHautDroite;
    Tile MontagneDroite;
    Tile MontagneHaut;
    Tile MontagneGauche;
    Tile MontagneCoinBasGauche;
    Tile MontagneCoinHautGauche;
    Tile MontagneCreuxDroite;
    Tile MontagneCreuxGauche;
    Tile MurBlue;
    Tile MurBlueCarte;
    Tile MurChen;
    Tile MurCentre;
    Tile MurCentreComptoir;
    Tile MurRed;
    Tile Noir;
    Tile OrdiCentreHaut;
    Tile OrdiSoin;
    Tile OrdiRedBas;
    Tile OrdiRedHaut;
    Tile Palier;
    Tile PalierBlue;
    Tile PalierChen;
    Tile PalierRed;
    Tile PalierCentre;
    Tile PanneauRoute1;
    Tile PanneauBlue;
    Tile PanneauChen;
    Tile PanneauPalette;
    Tile PanneauJadielle1;
    Tile PanneauJadielle2;
    Tile PanneauJadielle3;
    Tile PanneauJadielle4;
    Tile PanneauArgenta1;
    Tile PanneauArgenta2;
    Tile PanneauArgenta3;
    Tile PanneauArgenta4;
    Tile PanneauArgenta5;
    Tile PanneauRoute22;
    Tile PanneauRoute2Bas;
    Tile PanneauRoute2Haut;
    Tile PanneauRed;
    Tile Passage;
    Tile PassageRoute;
    Tile Pave;
    Tile PetiteTableGauche;
    Tile PetiteTableDrotie;
    Tile PlanteBas;
    Tile PlanteHaut;
    Tile PortePalette1;
    Tile PortePalette2;
    Tile PortePalette3;
    Tile PorteJadielle1;
    Tile PorteJadielle2;
    Tile PorteJadielle3;
    Tile PorteJadielle4;
    Tile PorteJadielle5;
    Tile PorteArgenta1;
    Tile PorteArgenta2;
    Tile PorteArgenta3;
    Tile PorteArgenta4;
    Tile PorteArgenta5;
    Tile PorteRoute22;
    Tile PorteRoute2Maison;
    Tile PorteRoute2Batiment;
    Tile Poubelle;
    Tile RadioBlueHaut;
    Tile RadioBlueBas;
    Tile Roche;
    Tile RouteGravier;
    Tile Route;
    Tile RouteMiGravier;
    Tile RouteMiGravierBloc;
    Tile RouteGravierBloc;
    Tile RouteBloc;
    Tile RouteRoute1;
    Tile RouteRoute1b;
    Tile RouteRoute2;
    Tile RouteRoute22;
    Tile RouteRoute22b;
    Tile RouteJadielle;
    Tile RouteJadielleb;
    Tile RouteJadielleEst;
    Tile RouteJadielleEstb;
    Tile Route2ToJadielleG;
    Tile Route2ToJadielle;
    Tile Route2ToJadielleD;
    Tile Route2ToArgentaG;
    Tile Route2ToArgentaD;
    Tile Saoul;
    Tile Scientifique;
    Tile SoinBasDroite;
    Tile SoinBasGauche;
    Tile SoinHautDroite;
    Tile SoinHautGauche;
    Tile SolBlue;
    Tile SolCentre;
    Tile SolCentreOmbre;
    Tile SolChen;
    Tile SolRed;
    Tile Sonnette;
    Tile SonnetteDouble;
    Tile SourisOrdi;
    Tile TableBasDroite;
    Tile TableBasGauche;
    Tile TableHaut;
    Tile TableHautBall;
    Tile TableHautDroite;
    Tile TableHautGauche;
    Tile TableBlueBasDroite;
    Tile TableBlueBasGauche;
    Tile TableBlueHautDroite;
    Tile TableBlueHautGauche;
    Tile TableChen;
    Tile TableChenDroite;
    Tile TableChenGauche;
    Tile TableRedDroite;
    Tile TableRedGauche;
    Tile TabouretBlue;
    Tile TabouretRed;
    Tile Tele;
    Tile TeleBlueBas;
    Tile TeleBlueHaut;
    Tile TeleRedBas;
    Tile TeleRedHaut;
    Tile Toit;
    Tile ToitDroite;
    Tile ToitGauche;
    Tile ToitGrisBas;
    Tile ToitGrisBasDroite;
    Tile ToitGrisBasGauche;
    Tile ToitGrisHaut;
    Tile ToitGrisHautDroite;
    Tile ToitGrisHautGauche;
    Tile ToitVert;
    Tile ToitVertBas;
    Tile ToitVertHaut;


    std::vector<Tile> BourgPaletteTiles;
    std::vector<Tile> Route1Tiles;
    std::vector<Tile> Route2Tiles;
    std::vector<Tile> Route22Tiles;
    std::vector<Tile> MaisonChenTiles;
    std::vector<Tile> MaisonBlueTiles;
    std::vector<Tile> MaisonRedTiles;
    std::vector<Tile> CentrePokemonTiles;
    std::vector<Tile> JadielleTiles;
    std::vector<Tile> ArgentaTiles;


#endif // CONSTANTES_H
