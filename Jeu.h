#ifndef JEU_H
#define JEU_H

#include "Map.h"
#include "Carte.h"
#include "Combat.h"
#include "Menu.h"
#include<SDL/SDL_ttf.h>

#define CACHE_SIZE 5000

// La fonction deplacerJoueur change la position du personnage en fonction de la direction prise et de la case d'arrivée
void deplacerJoueur(Carte Map, SDL_Rect *pos, int direction, bool &obstacle)
{
    int p;
    switch(direction)
    {
    case HAUT:
        p = (pos->x) + (pos->y-1)*Map.get_width();
        // Si le joueur sort de la carte, pas de changement de position et déclaration d'un obstacle
        if (pos -> y-1 < 0)
        {
            obstacle=true;
            break;
        }
        // Si le joueur rencontre une case obstacle, pas de changement de position et déclaration d'un obstacle
        if (Map.get_tiles()[Map.get_map()[p]].get_prop() <= UNIDIR)
        {
            obstacle=true;
            break;
        }
        // Sinon la position change
        obstacle = false;
        pos->y--;
        break;

    case BAS:
        p = (pos->x) + (pos->y+1)*Map.get_width();

        if (pos->y+1 >= Map.get_height())
        {
            obstacle = true;
            break;
        }
        // Seul le cas bas autorise le joueur à franchir les cases BARRIERES identifées par 3 et 4
        if (Map.get_tiles()[Map.get_map()[p]].get_prop() < UNIDIR)
        {
            obstacle = true;
            break;
        }
        if (Map.get_tiles()[Map.get_map()[p]].get_prop()==UNIDIR)
        {
            pos->y++;
            pos->y++;
            break;
        }
        obstacle = false;
        pos->y++;
        break;

    case GAUCHE:
        p = (pos->x-1) + (pos->y)*Map.get_width();

        if (pos->x-1 < 0)
        {
            obstacle = true;
            break;
        }

        if (Map.get_tiles()[Map.get_map()[p]].get_prop() <= UNIDIR)
        {
            obstacle = true;
            break;
        }
        obstacle = false;
        pos->x--;
        break;

    case DROITE:
        p = (pos->x+1) + (pos->y)*Map.get_width();

        if (pos->x+1 >= Map.get_width())
        {
            obstacle = true;
            break;
        }
        if (Map.get_tiles()[Map.get_map()[p]].get_prop() <= UNIDIR)
        {
            obstacle = true;
            break;
        }
        obstacle = false;
        pos->x++;
        break;
    }
}

// La fonction donne la caractéristique de la case en face du joueur et permet une action si on presse barre d'espace (afficher du texte, soigner Pokemon, faire que le PNJ se retourne vers le joueur etc.)
void get_tileprop(Carte Map, SDL_Rect *pos, int direction, bool &txt, bool &pnj, bool &soin, bool &ball, std::vector<std::string> &tiletext)
{
    int p;
    switch(direction)
    {
    case HAUT:
        p = (pos->x) + (pos->y-1)*Map.get_width();
        if (Map.get_tiles()[Map.get_map()[p]].get_prop()>=TXT and Map.get_tiles()[Map.get_map()[p]].get_prop()<=SOIN)
        {
            txt = true;
            tiletext = Map.get_tiles()[Map.get_map()[p]].get_txt();
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                pnj = true;
            }
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==SOIN)
            {
                soin = true;
            }
            break;
        }
        else if (Map.get_tiles()[Map.get_map()[p]].get_prop()==BALL)
        {
            ball = true;
            break;
        }
        // Sinon la position change
        txt = false;
        soin = false;
        pnj = false;
        ball = false;
        break;

    case BAS:
        p = (pos->x) + (pos->y+1)*Map.get_width();
        if (Map.get_tiles()[Map.get_map()[p]].get_prop()>=TXT and Map.get_tiles()[Map.get_map()[p]].get_prop()<=SOIN)
        {
            txt = true;
            tiletext = Map.get_tiles()[Map.get_map()[p]].get_txt();
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                pnj = true;
            }
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==SOIN)
            {
                soin = true;
            }
            break;
        }
        else if (Map.get_tiles()[Map.get_map()[p]].get_prop()==BALL)
        {
            ball = true;
            break;
        }
        txt = false;
        soin = false;
        pnj = false;
        ball = false;
        break;

    case GAUCHE:
        p = (pos->x-1) + (pos->y)*Map.get_width();
        if (Map.get_tiles()[Map.get_map()[p]].get_prop()>=TXT and Map.get_tiles()[Map.get_map()[p]].get_prop()<=SOIN)
        {
            txt = true;
            tiletext = Map.get_tiles()[Map.get_map()[p]].get_txt();
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                pnj = true;
            }
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==SOIN)
            {
                soin = true;
            }
            break;
        }
        else if (Map.get_tiles()[Map.get_map()[p]].get_prop()==BALL)
        {
            ball = true;
            break;
        }
        txt = false;
        soin = false;
        pnj = false;
        ball = false;
        break;

    case DROITE:
        p = (pos->x+1) + (pos->y)*Map.get_width();
        if (Map.get_tiles()[Map.get_map()[p]].get_prop()>=TXT and Map.get_tiles()[Map.get_map()[p]].get_prop()<=SOIN)
        {
            txt = true;
            tiletext = Map.get_tiles()[Map.get_map()[p]].get_txt();
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                pnj = true;
            }
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==SOIN)
            {
                soin = true;
            }
            break;
        }
        else if (Map.get_tiles()[Map.get_map()[p]].get_prop()==BALL)
        {
            ball = true;
            break;
        }
        txt = false;
        soin = false;
        pnj = false;
        ball = false;
        break;
    }
}

SDL_Surface* LoadImage32(const char* fichier_image)
{
	SDL_Surface* image_result;
	SDL_Surface* image_ram = SDL_LoadBMP(fichier_image);	// charge l'image dans image_ram en RAM
	if (image_ram==NULL)
	{
		printf("Image %s introuvable !! \n",fichier_image);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	image_result = SDL_DisplayFormat(image_ram);
	SDL_FreeSurface(image_ram);
	return image_result;
}

void ChargerMap_tileset(FILE* F,Map* m)
{
	int numtile,i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	char buf2[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #tileset
	fscanf(F,"%s",buf); // nom du fichier
	m->tileset = LoadImage32(buf);
	fscanf(F,"%d %d",&m->nbtilesX,&m->nbtilesY);
	m->LARGEUR_TILE = m->tileset->w/m->nbtilesX;
	m->HAUTEUR_TILE = m->tileset->h/m->nbtilesY;
	m->props = (TileProp*) malloc(m->nbtilesX*m->nbtilesY*sizeof(TileProp));
	for(j=0,numtile=0;j<m->nbtilesY;j++)
	{
		for(i=0;i<m->nbtilesX;i++,numtile++)
		{
			m->props[numtile].R.w = m->LARGEUR_TILE;
			m->props[numtile].R.h = m->HAUTEUR_TILE;
			m->props[numtile].R.x = i*m->LARGEUR_TILE;
			m->props[numtile].R.y = j*m->HAUTEUR_TILE;
			fscanf(F,"%s %s",buf,buf2);
			m->props[numtile].OBSTACLE = 0;
			if (strcmp(buf2,"OBSTACLE")==0)
				m->props[numtile].OBSTACLE = 1;
		}
	}
}

void ChargerMap_level(FILE* F,Map* m)
{
	int i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #level
	fscanf(F,"%d %d",&m->nbtiles_largeur_monde,&m->nbtiles_hauteur_monde);
	m->schema = (Uint16**) malloc(m->nbtiles_largeur_monde*sizeof(Uint16*));
	for(i=0;i<m->nbtiles_largeur_monde;i++)
		m->schema[i] = (Uint16*) malloc(m->nbtiles_hauteur_monde*sizeof(Uint16));
	for(j=0;j<m->nbtiles_hauteur_monde;j++)
	{
		for(i=0;i<m->nbtiles_largeur_monde;i++)
		{
			int tmp;
			fscanf(F,"%d",&tmp);
			if (tmp>=m->nbtilesX*m->nbtilesY)
			{
				printf("level tile hors limite\n");
				SDL_Quit();
				system("pause");
				exit(-1);
			}
			m->schema[i][j] = tmp;
		}
	}
}

Map* ChargerMap(const char* level,int largeur_fenetre,int hauteur_fenetre)
{
	FILE* F;
	Map* m;
	F = fopen(level,"r");
	if (!F)
	{
		printf("fichier %s introuvable !! \n",level);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	m = (Map*) malloc(sizeof(Map));
	ChargerMap_tileset(F,m);
	ChargerMap_level(F,m);
	m->largeur_fenetre = largeur_fenetre;
	m->hauteur_fenetre = hauteur_fenetre;
	m->xscroll = 0;
	m->yscroll = 0;
	fclose(F);
	return m;
}

int AfficherMap(Map* m,SDL_Surface* screen)
{
	int i,j;
	SDL_Rect Rect_dest;
	int numero_tile;
	int minx,maxx,miny,maxy;
	minx = m->xscroll / m->LARGEUR_TILE;
	miny = m->yscroll / m->HAUTEUR_TILE;
	maxx = (m->xscroll + m->largeur_fenetre)/m->LARGEUR_TILE;
	maxy = (m->yscroll + m->hauteur_fenetre)/m->HAUTEUR_TILE;
	for(i=minx;i<=maxx;i++)
	{
		for(j=miny;j<=maxy;j++)
		{
			Rect_dest.x = i*m->LARGEUR_TILE - m->xscroll;
			Rect_dest.y = j*m->HAUTEUR_TILE - m->yscroll;
			if (i<0 || i>=m->nbtiles_largeur_monde || j<0 || j>=m->nbtiles_hauteur_monde)
				numero_tile = 0;
			else
				numero_tile = m->schema[i][j];
			SDL_BlitSurface(m->tileset,&(m->props[numero_tile].R),screen,&Rect_dest);
		}
	}
	return 0;
}

int LibererMap(Map* m)
{
	int i;
	SDL_FreeSurface(m->tileset);
	for(i=0;i<m->nbtiles_hauteur_monde;i++)
		free(m->schema[i]);
	free(m->schema);
	free(m->props);
	free(m);
	return 0;
}

int CollisionDecor(Map* carte,SDL_Rect* perso)
{
	int xmin,xmax,ymin,ymax,i,j,indicetile;
	xmin = perso->x / carte->LARGEUR_TILE;
	ymin = perso->y / carte->HAUTEUR_TILE;
	xmax = (perso->x + perso->w -1) / carte->LARGEUR_TILE;
	ymax = (perso->y + perso->h -1) / carte->HAUTEUR_TILE;
	if (xmin<0 || ymin<0 || xmax>=carte->nbtiles_largeur_monde || ymax>=carte->nbtiles_hauteur_monde)
		return 1;
	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			indicetile = carte->schema[i][j];
			if (carte->props[indicetile].OBSTACLE)
				return 1;
		}
	}
	return 0;
}

void ClampScroll(Map* m)
{
	if (m->xscroll<0)
		m->xscroll=0;
	if (m->yscroll<0)
		m->yscroll=0;
	if (m->xscroll>m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1)
		m->xscroll=m->nbtiles_largeur_monde*m->LARGEUR_TILE-m->largeur_fenetre-1;
	if (m->yscroll>m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1)
		m->yscroll=m->nbtiles_hauteur_monde*m->HAUTEUR_TILE-m->hauteur_fenetre-1;
}

int FocusScrollCenter(Map* carte,SDL_Rect* perso)
{
	carte->xscroll = perso->x + perso->w - carte->largeur_fenetre/2;
	carte->yscroll = perso->y + perso->h/2 - carte->hauteur_fenetre/2;
	ClampScroll(carte);
	return 0;
}

void LoadMap(std::vector<SDL_Surface*> &tiles, Carte Map)
{
    int const n = Map.get_tiles().size();
    tiles.resize(n);

    for (int i=0;i<n;i++)
    {
        //tiles[i] = SDL_LoadBMP(Map.get_tiles()[i].get_file().data());
        tiles[i] = LoadImage32(Map.get_tiles()[i].get_file().data());
        //tiles[i] = SDL_DisplayFormat(SDL_LoadBMP(Map.get_tiles()[i].get_file().data()));
    }
}

void FreeMap(std::vector<SDL_Surface*> &tiles)
{
    int const n = tiles.size();
    for (int i=0;i<n;i++)
    {
        SDL_FreeSurface(tiles[i]);
    }
    tiles.clear();
}

void AfficherCarte(SDL_Surface* ecran, SDL_Surface* joueur, SDL_Rect *pos, Carte Map, SDL_Rect *offset, std::vector<SDL_Surface*> tiles)
{
    //SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_Surface *ball = NULL;
    ball = SDL_LoadBMP("tiles/pokeball.bmp");
    int i = 0, j = 0, p=0,x,y;
    //int const n = Map.get_tiles().size();
    //Déclaration des surfaces du terrain
    /*std::vector<SDL_Surface*> tiles(n);
    for (i=0;i<n;i++)
    {
        tiles[i] = SDL_LoadBMP(Map.get_tiles()[i].get_file().data());
    }*/

    SDL_Rect position, positionPNJ, positionJoueur;
    //SDL_Rect positionRondoudou, positionNidorino;

    positionJoueur.x = 4*TAILLE_BLOC;
    positionJoueur.y = 4*TAILLE_BLOC-4;
    x=pos->x;
    y=pos->y;

    // Placement des cases
    for (i=(x/TAILLE_BLOC)-5; i<(x/TAILLE_BLOC)+7;i++)
    {
        for (j=(y/TAILLE_BLOC)-5; j<(y/TAILLE_BLOC)+6;j++)
        {
            position.x = (i-(x/TAILLE_BLOC-4))*TAILLE_BLOC + offset->x;
            position.y = (j-(y/TAILLE_BLOC-4))*TAILLE_BLOC + offset->y;
            p = i+j*Map.get_width();

            SDL_BlitSurface(tiles[Map.get_map()[p]],NULL,ecran,&position);
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                positionPNJ.x = (i-(x/TAILLE_BLOC-4))*TAILLE_BLOC + offset->x;
                positionPNJ.y = (j-(y/TAILLE_BLOC-4))*TAILLE_BLOC + offset->y -4;
                SDL_SetColorKey(Map.get_pnj()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()][Map.get_direction()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()]],SDL_SRCCOLORKEY,SDL_MapRGB(Map.get_pnj()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()][Map.get_direction()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()]]->format,0,0,255));
                SDL_BlitSurface(Map.get_pnj()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()][Map.get_direction()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()]], NULL, ecran, &positionPNJ);
            }
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==BALL)
            {
                position.x = (i-(x/TAILLE_BLOC-4))*TAILLE_BLOC + offset->x;
                position.y = (j-(y/TAILLE_BLOC-4))*TAILLE_BLOC + offset->y;
                SDL_SetColorKey(ball,SDL_SRCCOLORKEY,SDL_MapRGB(ball->format,255,255,255));
                SDL_BlitSurface(ball, NULL, ecran, &position);
            }
        }
    }

    // On place le joueur
    SDL_SetColorKey(joueur,SDL_SRCCOLORKEY,SDL_MapRGB(joueur->format,255,255,255));
    SDL_BlitSurface(joueur, NULL, ecran, &positionJoueur);

    SDL_Flip(ecran);

    // Liberation des surfaces
    /*for (i=0;i<n;i++)
    {
        SDL_FreeSurface(tiles[i]);
    }*/
    SDL_FreeSurface(ball);
}

void AfficherCarteRival(SDL_Surface* ecran, SDL_Surface* joueur, SDL_Surface* rival, SDL_Rect *posJoueur, SDL_Rect *posRival, Carte Map, int isTexte, bool &isCurseur)
{
    int i = 0, j = 0, p,x,y;
    int const n = Map.get_tiles().size();
    //SDL_Surface *ecran = NULL;
//    carte[2][7] = HERBE;
    const char* textRival = "T'es sur mon chemin!";
    //Déclaration des surfaces du terrain
    SDL_Surface  *barre_combat, *texteRival, *curseur;

    std::vector<SDL_Surface*> tiles(n);
    for (i=0;i<n;i++)
    {
        tiles[i] = SDL_LoadBMP(Map.get_tiles()[i].get_file().data());
    }

    SDL_Rect position, positionBarre, positionTexte, positioncurseur, positionJoueur;
    TTF_Font *police = NULL;
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    SDL_Color couleurNoire = {0,0,0};
    texteRival = TTF_RenderText_Blended(police, textRival, couleurNoire);

    positionJoueur.x = 4*TAILLE_BLOC;
    positionJoueur.y = 4*TAILLE_BLOC-4;
    x=posJoueur->x;
    y=posJoueur->y;

    //ecran = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //ecran = SDL_SetVideoMode(160, 144, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    curseur = SDL_LoadBMP("combat_image/curseur_suite.bmp");

    // On efface l'écran
    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    // Placement des cases
    for (i=(x/TAILLE_BLOC)-5; i<(x/TAILLE_BLOC)+7;i++)
    {
        for (j=(y/TAILLE_BLOC)-5; j<(y/TAILLE_BLOC)+6;j++)
        {
            position.x = (i-(x/TAILLE_BLOC-4))*TAILLE_BLOC;
            position.y = (j-(y/TAILLE_BLOC-4))*TAILLE_BLOC;
            p = i+j*Map.get_width();

            SDL_BlitSurface(tiles[Map.get_map()[p]],NULL,ecran,&position);
        }
    }
    // On place le rival
    SDL_SetColorKey(rival,SDL_SRCCOLORKEY,SDL_MapRGB(rival->format,0,0,255));
    SDL_BlitSurface(rival, NULL, ecran, posRival);
    // On place le joueur
    SDL_SetColorKey(joueur,SDL_SRCCOLORKEY,SDL_MapRGB(joueur->format,255,255,255));
    SDL_BlitSurface(joueur, NULL, ecran, &positionJoueur);

    if (isTexte == 1)
    {
        positionBarre.x = 0;
        positionBarre.y = 96;
        positionTexte.x = positionBarre.x + 8;
        positionTexte.y = positionBarre.y + 12;
        SDL_BlitSurface(barre_combat, NULL, ecran, &positionBarre);
        SDL_BlitSurface(texteRival, NULL, ecran, &positionTexte);
        positioncurseur.x = positionBarre.x + 144;
        positioncurseur.y = positionBarre.y + 40;
        if (isCurseur == true)
        {
            SDL_BlitSurface(curseur, NULL, ecran, &positioncurseur);
        }
    }

    SDL_Flip(ecran);

    // Liberation des surfaces
    for (i=0;i<n;i++)
    {
        SDL_FreeSurface(tiles[i]);
    }
    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(texteRival);
    SDL_FreeSurface(curseur);
}

void DistanceJoueur(SDL_Rect *posJoueur,SDL_Rect *posRivalEcran,Carte Map)
{
    int i = 0, j = 0, p,x,y;
    int const n = Map.get_tiles().size();
    std::vector<SDL_Surface*> tiles(n);
    for (i=0;i<n;i++)
    {
        tiles[i] = SDL_LoadBMP(Map.get_tiles()[i].get_file().data());
    }
    SDL_Rect position;

    x=posJoueur->x;
    y=posJoueur->y;

    for (i=(x/TAILLE_BLOC)-5; i<(x/TAILLE_BLOC)+7;i++)
    {
        for (j=(y/TAILLE_BLOC)-5; j<(y/TAILLE_BLOC)+6;j++)
        {
            position.x = (i-(x/TAILLE_BLOC-4))*TAILLE_BLOC;
            position.y = (j-(y/TAILLE_BLOC-4))*TAILLE_BLOC;
            p = i+j*Map.get_width();

            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                posRivalEcran->x = position.x;
                posRivalEcran->y = position.y-4;
            }
        }
    }
}

void AfficherTxt(SDL_Surface* ecran, SDL_Surface* joueur, SDL_Rect *pos, Carte Map, std::vector<std::string> tiletext)
{
    int i = 0, j = 0, p=0,x,y;
    int const n = Map.get_tiles().size();
    //SDL_Surface *ecran = NULL;
    //Déclaration des surfaces du terrain
    std::vector<SDL_Surface*> tiles(n);
    for (i=0;i<n;i++)
    {
        tiles[i] = SDL_LoadBMP(Map.get_tiles()[i].get_file().data());
    }

    SDL_Surface  *barre_combat, *texte1, *texte2, *texte3, *texte4, *ball;
    SDL_Rect position, positionPNJ, positionBarre, positionJoueur, positionTexte1, positionTexte2;
    TTF_Font *police = NULL;
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    SDL_Color couleurNoire = {0,0,0};
    texte1 = TTF_RenderText_Blended(police, tiletext[0].data(), couleurNoire);
    if (tiletext.size()>1)
    {
        texte2 = TTF_RenderText_Blended(police, tiletext[1].data(), couleurNoire);
    }
    if (tiletext.size()>2)
    {
        texte3 = TTF_RenderText_Blended(police, tiletext[2].data(), couleurNoire);
    }
    if (tiletext.size()>3)
    {
        texte4 = TTF_RenderText_Blended(police, tiletext[3].data(), couleurNoire);
    }
    barre_combat = SDL_LoadBMP("combat_image/barre_combat.bmp");
    ball = SDL_LoadBMP("tiles/pokeball.bmp");

    positionJoueur.x = 4*TAILLE_BLOC;
    positionJoueur.y = 4*TAILLE_BLOC-4;
    x=pos->x;
    y=pos->y;

    //ecran = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // On efface l'écran
    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    // Placement des cases
    for (i=(x/TAILLE_BLOC)-4; i<(x/TAILLE_BLOC)+6;i++)
    {
        for (j=(y/TAILLE_BLOC)-4; j<(y/TAILLE_BLOC)+5;j++)
        {
            position.x = (i-(x/TAILLE_BLOC-4))*TAILLE_BLOC;
            position.y = (j-(y/TAILLE_BLOC-4))*TAILLE_BLOC;
            p = i+j*Map.get_width();

            SDL_BlitSurface(tiles[Map.get_map()[p]],NULL,ecran,&position);
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==PNJ)
            {
                positionPNJ.x = position.x;
                positionPNJ.y = position.y -4;
                SDL_SetColorKey(Map.get_pnj()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()][Map.get_direction()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()]],SDL_SRCCOLORKEY,SDL_MapRGB(Map.get_pnj()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()][Map.get_direction()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()]]->format,0,0,255));
                SDL_BlitSurface(Map.get_pnj()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()][Map.get_direction()[Map.get_tiles()[Map.get_map()[p]].get_nbPNJ()]], NULL, ecran, &positionPNJ);
            }
            if (Map.get_tiles()[Map.get_map()[p]].get_prop()==BALL)
            {
                SDL_SetColorKey(ball,SDL_SRCCOLORKEY,SDL_MapRGB(ball->format,255,255,255));
                SDL_BlitSurface(ball, NULL, ecran, &position);
            }
        }
    }
        // On place le joueur
    SDL_SetColorKey(joueur,SDL_SRCCOLORKEY,SDL_MapRGB(joueur->format,255,255,255));
    SDL_BlitSurface(joueur, NULL, ecran, &positionJoueur);

    //positionBarre.x = (Map.get_width()/2-5)*TAILLE_BLOC;
    //positionBarre.y = (Map.get_height()-3)*TAILLE_BLOC;
    positionBarre.x = 0;
    positionBarre.y = 96;
    positionTexte1.x = positionBarre.x + 8;
    positionTexte1.y = positionBarre.y + 12;
    positionTexte2.x = positionBarre.x + 8;
    positionTexte2.y = positionBarre.y + 28;
    SDL_BlitSurface(barre_combat, NULL, ecran, &positionBarre);
    SDL_BlitSurface(texte1, NULL, ecran, &positionTexte1);
    if (tiletext.size()>1)
    {
        SDL_BlitSurface(texte2, NULL, ecran, &positionTexte2);
    }

    SDL_Flip(ecran);

    if (tiletext.size()>2)
    {
        Input in;
        while (!in.key[SDLK_SPACE])
        {
            if (!in.key[SDLK_SPACE])
            {
                Curseur(ecran);
                SDL_Delay(250);
            }
            in.UpdateEvent();
            if (!in.key[SDLK_SPACE])
            {
                SDL_BlitSurface(barre_combat, NULL, ecran, &positionBarre);
                SDL_BlitSurface(texte1, NULL, ecran, &positionTexte1);
                SDL_BlitSurface(texte2, NULL, ecran, &positionTexte2);
                SDL_Flip(ecran);
                SDL_Delay(250);
            }
        }

        SDL_BlitSurface(barre_combat, NULL, ecran, &positionBarre);
        SDL_BlitSurface(texte3, NULL, ecran, &positionTexte1);
        if (tiletext.size()>3)
        {
            SDL_BlitSurface(texte4, NULL, ecran, &positionTexte2);
        }
        SDL_Flip(ecran);

    }

    // Liberation des surfaces
    for (i=0;i<n;i++)
    {
        SDL_FreeSurface(tiles[i]);
    }
    SDL_FreeSurface(barre_combat);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(texte1);
    if (tiletext.size()>1)
    {
        SDL_FreeSurface(texte2);
    }
    if (tiletext.size()>2)
    {
        SDL_FreeSurface(texte3);
    }
    if (tiletext.size()>3)
    {
        SDL_FreeSurface(texte4);
    }
}

void ChangeTeam(Pokemon &Poke1, Pokemon &Poke2)
{
    Pokemon PokeIntermediaire = Poke2;
    Poke2 = Poke1;
    Poke1 = PokeIntermediaire;
}

// Fonction principale du jeu dans laquelle le personnage peut se déplacer, entrer en combat
void jouer()
{
    SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR_FENETRE_COMBAT, HAUTEUR_FENETRE_COMBAT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    Pokemon Poke1, Poke2, Poke3, Poke4, Poke5, Poke6;

    std::vector<Pokemon> update_team;
    std::vector<Tile> update_tiles;
    std::vector<int> update_direction;

    int v, teamSize;

    std::vector<SDL_Surface*> tiles;

    // Déclaration des images du personnages (en mouvement et statique dans les 4 directions)
    SDL_Surface *gold[8] = {NULL};
    //SDL_Surface *silver[9] = {NULL};
    std::vector<SDL_Surface*> silver;
    std::vector<SDL_Surface*> scientifique;
    std::vector<SDL_Surface*> gros;
    std::vector<SDL_Surface*> infirmiere;
    std::vector<SDL_Surface*> fillette;
    std::vector<SDL_Surface*> saoul;
    std::vector<SDL_Surface*> chen, bluesister;
    //SDL_Surface *scientifique[9] = {NULL};
    // Déclaration des images variables suivant la direction prise
    SDL_Surface *gold_mouv = NULL, *gold_static = NULL, *silver_mouv = NULL, *silver_static = NULL;
    // Chargement des sprites
    gold[HAUT] = SDL_LoadBMP("tiles_perso/gold_haut.bmp");
    gold[BAS] = SDL_LoadBMP("tiles_perso/gold_bas.bmp");
    gold[DROITE] = SDL_LoadBMP("tiles_perso/gold_right.bmp");
    gold[GAUCHE] = SDL_LoadBMP("tiles_perso/gold_left.bmp");
    gold[MI_HAUT] = SDL_LoadBMP("tiles_perso/gold_haut_mouv.bmp");
    gold[MI_BAS] = SDL_LoadBMP("tiles_perso/gold_bas_mouv.bmp");
    gold[MI_DROITE] = SDL_LoadBMP("tiles_perso/gold_right_mouv.bmp");
    gold[MI_GAUCHE] = SDL_LoadBMP("tiles_perso/gold_left_mouv.bmp");

    gold_mouv = gold[MI_BAS];
    gold_static = gold[BAS];

    SDL_Surface *silverBAS = SDL_LoadBMP("tiles_perso/silver_haut.bmp");
    SDL_Surface *silverHAUT = SDL_LoadBMP("tiles_perso/silver_bas.bmp");
    SDL_Surface *silverGAUCHE= SDL_LoadBMP("tiles_perso/silver_droite.bmp");
    SDL_Surface *silverDROITE = SDL_LoadBMP("tiles_perso/silver_gauche.bmp");
    //SDL_Surface *silverMI_HAUT = SDL_LoadBMP("tiles_perso/silver_haut_mouv.bmp");
    //SDL_Surface *silverMI_BAS = SDL_LoadBMP("tiles_perso/silver_bas_mouv.bmp");
    SDL_Surface *silverMI_DROITE = SDL_LoadBMP("tiles_perso/silver_droite_mouv.bmp");
    //SDL_Surface *silverMI_GAUCHE = SDL_LoadBMP("tiles_perso/silver_gauche_mouv.bmp");
    SDL_Surface *silver8 = SDL_LoadBMP("tiles_perso/silver_droite_combat.bmp");

    //std::vector<SDL_Surface*[9]> silverImages;
    silver.push_back(silverHAUT);
    silver.push_back(silverBAS);
    silver.push_back(silverGAUCHE);
    silver.push_back(silverDROITE);
    //silver.push_back(silverMI_HAUT);
    //silver.push_back(silverMI_BAS);
    //silver.push_back(silverMI_DROITE);
    //silver.push_back(silverMI_GAUCHE);
    //silver.push_back(silver8);

    silver_mouv = silverMI_DROITE;
    silver_static = silverGAUCHE;

    // On inverse BAS avec HAUT et GAUCHE avec DROITE pour que le PNJ parle en face du joueur
    SDL_Surface *scientifiqueBAS = SDL_LoadBMP("tiles_perso/scientifique_haut.bmp");
    SDL_Surface *scientifiqueHAUT = SDL_LoadBMP("tiles_perso/scientifique_bas.bmp");
    SDL_Surface *scientifiqueGAUCHE = SDL_LoadBMP("tiles_perso/scientifique_droite.bmp");
    SDL_Surface *scientifiqueDROITE = SDL_LoadBMP("tiles_perso/scientifique_gauche.bmp");
    //std::vector<SDL_Surface*[9]> scientifiqueImages;
    scientifique.push_back(scientifiqueHAUT);
    scientifique.push_back(scientifiqueBAS);
    scientifique.push_back(scientifiqueGAUCHE);
    scientifique.push_back(scientifiqueDROITE);

    SDL_Surface *grosBAS = SDL_LoadBMP("tiles_perso/gros_haut.bmp");
    SDL_Surface *grosHAUT = SDL_LoadBMP("tiles_perso/gros_bas.bmp");
    SDL_Surface *grosGAUCHE = SDL_LoadBMP("tiles_perso/gros_droite.bmp");
    SDL_Surface *grosDROITE = SDL_LoadBMP("tiles_perso/gros_gauche.bmp");

    gros.push_back(grosHAUT);
    gros.push_back(grosBAS);
    gros.push_back(grosGAUCHE);
    gros.push_back(grosDROITE);

    SDL_Surface *chenBAS = SDL_LoadBMP("tiles_perso/chen_haut.bmp");
    SDL_Surface *chenHAUT = SDL_LoadBMP("tiles_perso/chen_bas.bmp");
    SDL_Surface *chenGAUCHE = SDL_LoadBMP("tiles_perso/chen_droite.bmp");
    SDL_Surface *chenDROITE = SDL_LoadBMP("tiles_perso/chen_gauche.bmp");

    chen.push_back(chenHAUT);
    chen.push_back(chenBAS);
    chen.push_back(chenGAUCHE);
    chen.push_back(chenDROITE);

    SDL_Surface *infirmiereBAS = SDL_LoadBMP("tiles_perso/infirmiere_bas.bmp");

    infirmiere.push_back(infirmiereBAS);
    infirmiere.push_back(infirmiereBAS);
    infirmiere.push_back(infirmiereBAS);
    infirmiere.push_back(infirmiereBAS);

    SDL_Surface *filletteGAUCHE = SDL_LoadBMP("tiles_perso/fillette_gauche.bmp");

    fillette.push_back(filletteGAUCHE);
    fillette.push_back(filletteGAUCHE);
    fillette.push_back(filletteGAUCHE);
    fillette.push_back(filletteGAUCHE);

    SDL_Surface *saoul1 = SDL_LoadBMP("tiles_perso/saoul.bmp");

    saoul.push_back(saoul1);
    saoul.push_back(saoul1);
    saoul.push_back(saoul1);
    saoul.push_back(saoul1);

    SDL_Surface *bluesisterBAS = SDL_LoadBMP("tiles_perso/bluesister_haut.bmp");
    SDL_Surface *bluesisterHAUT = SDL_LoadBMP("tiles_perso/bluesister_bas.bmp");
    SDL_Surface *bluesisterGAUCHE = SDL_LoadBMP("tiles_perso/bluesister_droite.bmp");
    SDL_Surface *bluesisterDROITE = SDL_LoadBMP("tiles_perso/bluesister_gauche.bmp");

    bluesister.push_back(bluesisterHAUT);
    bluesister.push_back(bluesisterBAS);
    bluesister.push_back(bluesisterGAUCHE);
    bluesister.push_back(bluesisterDROITE);

    // Déclaration des positions du joueur sur la carte
    SDL_Rect position, positionJoueur, positionIntermediaire, positionRival, positionRivalIntermediaire, postmp, offset;
    SDL_Event event;

    // Déclaration de la position du joueur, positionJoueur raisonne en terme de cases tandis que position et positionIntermediaire en terme de pixels
    positionJoueur.x = 10;
    positionJoueur.y = 14;
    // Correspond à la position du joueur en mouvement
    positionIntermediaire.x = positionJoueur.x*TAILLE_BLOC;
    positionIntermediaire.y = positionJoueur.y*TAILLE_BLOC;
    // Correspond à la position du joueur statique
    position.x = positionJoueur.x*TAILLE_BLOC;
    position.y = positionJoueur.y*TAILLE_BLOC;

    positionRival.x = 2*TAILLE_BLOC;
    positionRival.y = 4*TAILLE_BLOC-4;

    positionRivalIntermediaire.x = 2*TAILLE_BLOC;
    positionRivalIntermediaire.y = 4*TAILLE_BLOC-4;

    offset.x = 0;
    offset.y = 0;

    int continuer = 1, i = 0, combatAlea = 0, pokeAlea = 0, direction = GAUCHE;
    bool obstacle = false, txt=false, pnj=false, soin = false, ball = false, isCurseur = false;
    std::vector<std::string> tiletext;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////     MUSIQUES     /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Mix_Music *MusicRoute1, *MusicRoute10, *MusicPalette, *MusicJadielle, *MusicLabo, *MusicCentre, *MusicCombat, *MusicLegendary, *MusicRival, *MusicCombatRival, *MusicForetJade;
    MusicRoute1 = Mix_LoadMUS("music/PkmRB_Route1.mid");
    MusicRoute10 = Mix_LoadMUS("music/PkmRB_Route10.mid");
    MusicPalette = Mix_LoadMUS("music/PkmRB_Pallet.mid");
    MusicJadielle = Mix_LoadMUS("music/PkmRB_Jadielle.mid");
    MusicLabo = Mix_LoadMUS("music/PkmRB_Lab.mid");
    MusicForetJade = Mix_LoadMUS("music/PkmRB_Forest.mid");
    MusicCentre = Mix_LoadMUS("music/PkmRB_Center.mid");
    MusicCombat = Mix_LoadMUS("music/PkmRB_Battle2.mid");
    MusicCombatRival = Mix_LoadMUS("music/PkmRB_Battle3.mid");
    MusicLegendary = Mix_LoadMUS("music/PkmRB_Battle4.mid");
    MusicRival = Mix_LoadMUS("music/PkmRB_Rival.mid");
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);

    Mix_Chunk *Bump;
    Mix_AllocateChannels(1);
    Bump = Mix_LoadWAV("chunk/bump.wav");


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////     Pokemon Sauvages     /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Pokemon> SauvageRoute1;
    SauvageRoute1.push_back(Roucool);
    SauvageRoute1.push_back(Rattata);
    SauvageRoute1.push_back(Fouinette);
    SauvageRoute1.push_back(Fouinar);
    SauvageRoute1.push_back(Suicune);

    std::vector<Pokemon> SauvageRoute2;
    SauvageRoute2.push_back(Chenipan);
    SauvageRoute2.push_back(Chrysacier);
    SauvageRoute2.push_back(Coconfort);
    SauvageRoute2.push_back(Suicune);

    std::vector<Pokemon> SauvageRoute22;
    SauvageRoute22.push_back(Rattata);
    SauvageRoute22.push_back(Piafabec);
    SauvageRoute22.push_back(Doduo);
    SauvageRoute22.push_back(Ponyta);
    SauvageRoute22.push_back(Rapasdepic);
    SauvageRoute22.push_back(Suicune);

    std::vector<int> ProbaRoute1;
    ProbaRoute1.push_back(449);
    ProbaRoute1.push_back(749);
    ProbaRoute1.push_back(949);
    ProbaRoute1.push_back(999);
    ProbaRoute1.push_back(1000);

    std::vector<int> ProbaRoute2;
    ProbaRoute2.push_back(333);
    ProbaRoute2.push_back(666);
    ProbaRoute2.push_back(999);
    ProbaRoute2.push_back(1000);

    std::vector<int> ProbaRoute22;
    ProbaRoute22.push_back(300);
    ProbaRoute22.push_back(799);
    ProbaRoute22.push_back(899);
    ProbaRoute22.push_back(949);
    ProbaRoute22.push_back(999);
    ProbaRoute22.push_back(1000);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////     MATRICE CARTE     //////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int Route1Matrix[NB_BLOC_LARGEUR_ROUTE1*NB_BLOC_HAUTEUR_ROUTE1] =
    {8, 8, 8, 2, 8, 8, 8, 8, 8, 2,20,21, 2, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     8, 8, 8, 2, 8, 8, 8, 8, 8, 2,21,20, 2, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     8, 8, 8, 2, 8, 8, 8, 8, 8, 2,20,21, 2, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     8, 8, 8, 2, 8, 8, 8, 8, 8, 2,21,20, 2, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     8, 8, 8, 2, 8, 8, 8, 8, 8, 2,18,19, 2, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8, 8, 2,16,15, 2, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 2, 2, 2, 2, 2, 2, 9, 9, 2, 2, 2, 2, 2, 2, 2, 8, 8, 8, 1,
     1, 1, 8, 2,11,11,11,11, 8, 8, 9, 9, 8, 8, 8, 8,11,11, 2, 8, 8, 8, 1,
     1, 1, 8, 2,10,10,10,10, 8, 8, 9, 9, 8, 8, 8, 8,10,10, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8, 8, 1, 9, 9, 9, 9, 9, 9, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 4, 4, 4, 4, 4, 1, 5, 5, 5, 5, 9, 9, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 1,12,12,12,12,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 3, 6, 6, 6, 6, 1,12,12,12,12,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 1,12,12,12,12,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 4, 4, 4, 4, 4, 1,12,12,12,12,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8,11,11,11,11, 8, 8, 9, 9, 9, 9, 9, 9, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8,10,10,10,10, 8, 8, 9, 9, 9, 9, 9, 9, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8,11,11,11,11, 9, 9,12,12,12,12, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8,10,10,10,10, 9, 9,12,12,12,12, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,11,11,11,11, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,10,10,10,10, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 4, 7, 5, 5, 4, 7, 4, 4, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8, 8, 8, 8, 8,12,12,12,12, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 1, 1, 1, 1, 1, 1, 1, 1,12,12,12,12, 5, 5, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8,11,11,11,11,12,12,12,12, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 8, 8, 8, 8,10,10,10,10,12,12,12,12, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 8, 8, 8, 1,
     1, 1, 8, 2, 5, 5, 9, 9, 9, 0, 5, 5, 5, 5, 5 ,5 ,5 ,5, 2, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8,12,12,12,12, 9, 9, 8, 8,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8,12,12,12,12, 9, 9, 8, 8,12,12,12,12, 1, 8, 8, 8, 1,
     1, 1, 8, 1,12,12,12,12,11,11, 9, 9,12,12,12,12,11,11, 1, 8, 8, 8, 1,
     1, 1, 8, 1,12,12,12,12,10,10, 9, 9,12,12,12,12,10,10, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 2, 2, 2, 2, 2, 2,12,12, 2, 2, 2, 2, 2, 2, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 2,12,12, 2, 8, 8, 8, 8, 8, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 2,14,13, 2, 8, 8, 8, 8, 8, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 2,17,17, 2, 8, 8, 8, 8, 8, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 8, 8, 8, 8, 8, 2,12,12, 2, 8, 8, 8, 8, 8, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 2, 2, 2, 2, 2, 2,12,12, 2, 2, 2, 2, 2, 2, 1, 8, 8, 8, 1,
     1, 1, 8, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 1,
     1, 1, 8, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 1};

    int Route2Matrix[NB_BLOC_LARGEUR_ROUTE2*NB_BLOC_HAUTEUR_ROUTE2] =
    { 0, 0, 0, 0, 0, 0, 0, 2,53, 2,53, 2,53, 2,53, 2,53, 2,53, 2,53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0,53, 2,53, 2,53, 2,53, 2,53, 2,53, 2,53, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 2,53, 2,53, 2,53, 2,53, 2,53, 2,53, 2,53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,53, 2, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 2,53, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,55,56, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2,53, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,12,12,12,12,12,12,12,12,53, 2,14, 2, 3, 3, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,12,12,12,12,12,12,12,12, 2,53,14, 2, 3, 3, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,12,12,12,12,12,12,12,12,53, 2,45,40,40,40,40,40,40,46, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,12,12,12,12,12,12,12,12, 2,53,41,38,38,38,38,38,38,42, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,41,38,38,38,38,38,38,42, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,43,39,37,39,39,39,39,44, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 5, 5,13, 5, 5, 5, 5, 3, 3, 3, 3,11,11,11,11, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0, 3,47, 3, 3,10,10,10,10, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 0, 0, 5, 5, 5, 5, 5, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 5, 5, 0, 5, 5, 5, 0, 0, 0, 0, 5, 5,21,19,19,20, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 5, 5,15,18,17,16, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 0, 0, 0, 5, 5, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 5,13, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 5, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 5, 0, 5, 0, 5, 5, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 5, 0, 5, 0, 5, 0, 5, 5, 0, 5, 0, 5, 5, 6, 6, 6, 8, 6, 6, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 5, 5, 0, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 0, 5, 5, 0, 5, 0, 5, 5, 6, 6, 6, 8, 6, 6, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 5, 5, 5, 0, 4,53, 2, 4, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 5, 0, 0, 5, 0, 5, 5, 5, 5, 4, 4,29,29, 4, 4, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5,32,34,34,34,34,33, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5,30,35,35,35,35,31, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,25,28,28,27,28,26, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,22,29,24,24,24,23, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 8, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3,53, 2, 0, 5, 0, 0, 0, 0,11,11,11,11, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 2,53, 0, 5, 0, 0, 0, 0,10,10,10,10, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,11,11,53, 2,12,12,12,12,12,12, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,10,10, 2,53,12,12,12,12,12,12, 0, 5, 6, 6, 6, 8, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,11,11,53, 2,12,12,12,12, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,10,10, 2,53,12,12,12,12, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,11,11,53, 2,11,11, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,10,10, 2,53,10,10, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,11,11,53, 2,53, 2,53, 2,53, 2, 5, 5, 5, 0,11,11, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5,10,10, 2,53, 2,53, 2,53, 2,53, 0, 0, 5, 0,10,10, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 8, 7, 7, 6, 6, 5, 5, 6, 8, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0,11,11,11,11, 3, 3, 0, 0, 5, 0,11,11,11,11, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0,10,10,10,10, 3, 3, 0, 0, 5, 0,10,10,10,10, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 3, 3,53, 2, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 3,48, 2,53, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,14, 2,53, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,14,51,54,52, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,14, 2, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,14,49,50,48, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,14, 2,53, 2, 5, 5, 5, 5, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,14, 2, 2,53, 5, 5, 5, 5, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5,
      0, 0, 0, 0, 0, 0, 0, 0, 0,13, 0,53, 2,53, 2, 5, 5, 5, 5, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5};

    int Route22Matrix[NB_BLOC_LARGEUR_ROUTE22*NB_BLOC_HAUTEUR_ROUTE22] =
    {18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,28,19,19,19,19,27,18,18,18,18,18,18,18,18,18,18,18,18,28,19,19,19,19,19,19,27,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,21,37,35,35,39,22,18,18,18,18,18,18,18,18,18,18,18,18,21, 0, 0, 0, 0, 0, 0,22,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,21,38,36,36,40,25,19,19,19,19,19,19,19,19,19,19,19,19,23, 5, 5, 5, 7, 5, 5,22,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,21,32,34,34,33, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,22,18,18,18,18,18,18,18,18,21,21,
     18,18,18,18,21,29, 9,31,30, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,25,19,19,19,19,19,19,19,19,23,23,
     18,18,18,18,21, 3, 3, 3, 3, 4, 4, 0, 0, 0, 0,17,13,13,15,26,20,20,24, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0,44,45, 0, 0, 0, 0, 0,
     18,18,18,18,21, 3, 3, 3,10, 4, 4, 5, 5, 5, 5,16,12,12,14,22,18,18,21, 5, 7, 5, 5, 4, 0, 0, 0, 0, 0,43,45, 0, 0, 0, 0, 0,
     18,18,18,18,21, 3, 3, 3, 3, 4, 4,11,11,11,11,16,12,12,14,22,18,18,21,11,11,11,11, 4, 0,47, 2,47, 2,42,46,47, 2,47, 2, 0,
     18,18,18,18,21, 6, 6, 8, 6, 4, 4,11,11,11,11,16,12,12,14,22,18,18,21,11,11,11,11, 4, 0, 2,47, 2,47,41,46, 2,47, 2,47, 2,
     18,18,18,18,21, 3, 3, 3, 3, 4, 4,11,11,11,11, 1, 1, 1, 1,22,18,18,21,11,11,11,11, 4, 0,47, 2,26,20,20,20,20,24,47, 2,47,
     18,18,18,18,21, 3, 3, 3, 3, 4, 4,11,11,11,11, 1, 1, 1, 1,22,18,18,21,11,11,11,11, 4, 0, 2,47,22,18,18,18,18,21, 2,47, 2,
     18,18,18,18,21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22,18,18,21, 0, 0, 0, 0, 0, 0, 0, 0,22,18,18,18,18,21,47, 2,47,
     18,18,18,18,21, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5,25,19,19,23, 5, 5, 5, 7, 5, 5, 5, 5,22,18,18,18,18,21, 4, 4, 4,
     18,18,18,18,18,20,20,20,20,20,24, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,22,18,18,18,18,21,47, 2,47,
     18,18,18,18,18,18,18,18,18,18,21, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,22,18,18,18,18,21, 2,47, 2,
     18,18,18,18,18,18,18,18,18,18,18,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,18,18,18,18,18,21,47, 2,47,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21, 2, 3, 2,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21,47, 2,47,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21, 2,47, 2,
     18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,21,47, 2,47};

    int BourgPaletteMatrix[NB_BLOC_LARGEUR_BOURGPALETTE*NB_BLOC_HAUTEUR_BOURGPALETTE] =
    {50,50,50,50,50,37,37,34,34,34,34,39,39,35,35,34,34,34,34,39,39,37,37,37,37,50,50,50,50,50,
     50,50,50,50,50,37,37,34,34,34,34,39,39,35,35,34,34,34,34,39,39,37,37,37,37,50,50,50,50,50,
     50,50,50,50,50,37,37,34,34,34,34,38,38,35,35,34,34,34,34,38,38,37,37,37,37,50,50,50,50,50,
     50,50,50,50,50,37,37,37, 2, 2, 2, 2, 2,34,34, 2, 2, 2, 2, 2, 2, 2, 2,37,37,50,50,50,50,50,
     50,50,50,50,50,37,37,37,37,37,37,37, 2,49,49, 2,37,37,37,37,37,37,37,37,37,50,50,50,50,50,
     50,50,50,50,50,37,50,37,37,37,37,37, 2,48,43, 2,37,37,37,37,37,50,37,37,37,50,50,50,50,50,
     50,50,50,50,50,37,50,37,37,37,37,37, 2,34,34, 2,37,37,37,37,37,50,37,37,37,50,50,50,50,50,
     50,50,50,50,50,37,37,37, 2,37,37,37, 2,34,34, 2,37,37,37,37,37,37,37, 2,37,50,50,50,50,50,
     50,50,50,50,50, 2, 2, 2, 2, 2, 2, 2, 2,34,34, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,51,36,51,36,51,36,51,36,51,36,51,36,51,36,51,36,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,36,51,17,16,16,18,36,51,36,51,17,16,16,18,36,51,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,35,35,12,14,15,13,51,36,35,35,12,14,15,13,51,36,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,35,44,10,40, 9,11,36,51,35,45,10,41, 9,11,36,51,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,51,36,51,36,51,36,51,36,51,36,51,36,51,36,51,36,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,36,51,36,51,36,51,36,51,36,51,36,51,36,51,36,51,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,51,36,35,35,35,35,51,36,32,31,31,31,31,33,51,36,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,36,51, 1, 1, 1, 0,36,51,29,28,28,28,28,30,36,51,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,51,36,39,39,39,39,51,36,22,26,24,25,27,23,51,36,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,36,51,38,38,38,38,36,51,20,19,42, 9,19,21,36,51,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,51,36,51,36,51,36,51,36,35,35,35,35,35,35,35,35,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,36,51,36,51,36,51,36,51, 1, 1, 1,46, 1, 1,35,35,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,37,37, 7, 6, 6, 8,35,35,39,39,39,39,37,37,35,35,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,37,37, 4, 3, 3, 5,35,35,38,38,38,38,47,37,35,35,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2,37,37,37, 4, 3, 3, 5,35,35,35,35,35,35,35,35,35,35,37, 2,50,50,50,50,50,
     50,50,50,50,50, 2, 2,37,37, 4, 3, 3, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,50,50,50,50,50,
     50,50,50,50,50, 2, 2, 2, 2, 4, 3, 3, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,50,50,50,50,50,
     50,50,50,50,50,37,37,37, 2, 4, 3, 3, 5,37,37,37,37,37,37, 2,37,37,37,37,37,50,50,50,50,50,
     50,50,50,50,50,39,39,37, 2, 4, 3, 3, 5,34,34,34,34,34,34, 2,37,39,39,37,37,50,50,50,50,50,
     50,50,50,50,50,38,38,37, 2, 4, 3, 3, 5,34,34,34,34,34,34, 2,37,38,38,37,37,50,50,50,50,50,
     50,50,50,50,50,38,38,37, 2, 4, 3, 3, 5,34,34,34,34,34,34, 2,37,38,38,37,37,50,50,50,50,50};

    int MaisonChenMatrix[NB_BLOC_LARGEUR_MAISONCHEN*NB_BLOC_HAUTEUR_MAISONCHEN] =
    {17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17, 1, 1, 2, 2, 0, 0, 5, 5, 5, 5,17,17,17,17,17,17,
     17,17,17,17,17, 6, 7,15,15,15,15, 4, 4, 4, 4,17,17,17,17,17,17,
     17,17,17,17,17, 9,10,15,15,18,15,15,15,15,15,17,17,17,17,17,17,
     17,17,17,17,17,15,15,15,15,15,15,11,13,12, 3,17,17,17,17,17,17,
     17,17,17,17,17,15,15,15,15,15,15, 9, 8,10,15,17,17,17,17,17,17,
     17,17,17,17,17,15,15,15,15,15,15,15,15,15,15,17,17,17,17,17,17,
     17,17,17,17,17, 5, 5, 5, 5,15,15, 5, 5, 5, 5,17,17,17,17,17,17,
     17,17,17,17,17, 4, 4, 4, 4,15,15, 4, 4, 4, 4,17,17,17,17,17,17,
     17,17,17,17,17,15,15,15,15,15,15,15,15,15,15,17,17,17,17,17,17,
     17,17,17,17,17,15,16,15,15,15,15,15,15,15,15,17,17,17,17,17,17,
     17,17,17,17,17,15,15,15,15,15,15,15,15,15,15,17,17,17,17,17,17,
     17,17,17,17,17,15,15,15,15,14,14,15,15,15,15,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
     17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17};

     int MaisonBlueMatrix[NB_BLOC_LARGEUR_MAISON*NB_BLOC_HAUTEUR_MAISON] =
     {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20, 7, 9, 3, 0, 1, 2, 1, 5,20,20,20,20,20,20,
      20,20,20,20,20, 8,10, 4,18,18,18,18, 6,20,20,20,20,20,20,
      20,20,20,20,20,18,18,18,18,18,18,18,18,20,20,20,20,20,20,
      20,20,20,20,20,18,18,17,13,14,17,18,18,20,20,20,20,20,20,
      20,20,20,20,20,18,18,21,15,16,17,18,18,20,20,20,20,20,20,
      20,20,20,20,20,18,18,18,18,18,18,18,18,20,20,20,20,20,20,
      20,20,20,20,20,12,18,18,18,18,18,18,12,20,20,20,20,20,20,
      20,20,20,20,20,11,18,19,19,18,18,18,11,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
      20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};

    int MaisonRedBasMatrix[NB_BLOC_LARGEUR_MAISON*NB_BLOC_HAUTEUR_MAISON] =
    {28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28, 7, 9, 2, 0, 1, 0, 0,24,28,28,28,28,28,28,
     28,28,28,28,28, 8,10, 3, 6,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,22,22,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,17,11,12,17,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,17,13,14,17,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,22,15,16,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,22,22,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,23,23,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28};

    int MaisonRedHautMatrix[NB_BLOC_LARGEUR_MAISON*NB_BLOC_HAUTEUR_MAISON] =
    {28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,20, 0, 0, 0, 7, 9, 0,25,28,28,28,28,28,28,
     28,28,28,28,28,21,22,26,27, 8,10,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,15,16,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,22,22,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,22, 4,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,22,22,22, 5,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,18,22,22,22,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,19,22,22,22,22,22,22,22,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
     28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28};

     int CentrePokemonMatrix[NB_BLOC_LARGEUR_CENTREPOKEMON*NB_BLOC_HAUTEUR_CENTREPOKEMON] =
     {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,10,11,14, 3, 3, 4, 3, 3, 3,16,19,19,19,19,19,19,
      19,19,19,19,19,12,13,15,21, 1, 7, 1, 1, 1,17,19,19,19,19,19,19,
      19,19,19,19,19, 5, 5, 9,20, 8, 6, 0, 0, 0, 1,19,19,19,19,19,19,
      19,19,19,19,19, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,19,19,19,19,19,19,
      19,19,19,19,19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,19,19,19,19,19,
      19,19,19,19,19, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0,19,19,19,19,19,19,
      19,19,19,19,19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,19,19,19,19,19,19,
      19,19,19,19,19, 0, 0, 0,18,18, 0, 0, 2, 2, 0,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
      19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19};

     int JadielleMatrix[NB_BLOC_LARGEUR_JADIELLE*NB_BLOC_HAUTEUR_JADIELLE] =
     { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 0, 0, 6, 6, 6, 6, 2, 2, 0, 0, 4, 0, 6, 6, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 0, 0, 5, 5, 5, 5, 2, 2, 0, 0, 4, 0, 5, 5, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 2, 2,84, 1, 0, 0,14, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 2,62, 1,84, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7,80,81,80, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7,82,86,83, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 2,62, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1,84, 1, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 1,84, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 0, 0, 0, 0, 0, 0, 0,14, 0,84,71,72, 1,27,29,29,28, 2, 2, 2, 2,36,35,35,35,35,39, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 0, 3, 3, 3, 3, 3, 3, 4, 4, 1,84, 1,84,25,30,24,26, 2, 2, 2, 2,37,34,34,34,34,40, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1,84, 1,84, 1, 2, 2, 2, 2, 2, 2,38,31,42,43,31,41, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 1,84, 1,84, 2, 2, 2, 2, 2,61,32,24,24,24,67,33, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1,84, 1,27,29,29,28, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 1,84,25,66,24,26,15,15,15,15,16,16,16,16,16,16,15,15, 4, 4, 4, 4, 4, 4,
      73,73, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1, 2, 2, 4, 4, 4, 4, 4, 4,
      73,73, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 2, 2, 4, 4, 4, 4, 4, 4,
      73,73, 8, 8, 8, 8, 8, 8, 8, 8,10, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1,84, 1,84, 1,55,54,54,54,54,57,84, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4,
      74,74, 9, 9, 9, 9, 9, 9, 9, 9,12, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 1,84, 1,84,56,53,53,53,53,58, 1,84, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4,
       0, 0, 0, 0,79,78, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1,84, 1, 2, 2,51,48,48,47,48,52,84, 1,84, 1, 2, 1,84, 1, 4, 4, 4, 4, 4, 4,
       0, 0, 0, 0,79,77, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 4, 4, 4, 4, 4, 7, 1, 1,84, 2,60,49,65,46,46,46,50, 1,84, 1,84, 1,84, 1,84, 4, 4, 4, 4, 4, 4,
       1,84, 1,84,80,76, 2,84, 1,84, 1, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2,84, 1,84, 1,84, 1,84, 1,84, 1,55,54,54,57, 0, 0,84, 1, 4, 4, 4, 4, 4, 4,
      84, 1,84, 1,81,70, 2, 1,84, 1,84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,59, 1,84, 1,84, 1,84, 1,84, 1,84,56,53,53,58, 0, 0, 1,84, 4, 4, 4, 4, 4, 4,
       1,84, 1,75,11,11,11,11,13,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1, 6, 6, 0, 0, 0, 0,51,48,47,52, 0, 0,84, 1, 4, 4, 4, 4, 4, 4,
      84, 1,84,73, 8, 8, 8, 8,10, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 5, 5, 0, 0, 0, 0,49,64,45,50, 0, 0, 1,84, 4, 4, 4, 4, 4, 4,
       0, 0, 0,73, 8, 8, 8, 8,10,84, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1, 4, 4, 4, 4, 4, 4,
      16,16,16,73, 8, 8, 8, 8,10, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 1,84, 4, 4, 4, 4, 4, 4,
       0, 0, 0,73, 8, 8, 8, 8,10,84, 1, 0, 0,14, 0, 6, 6, 6, 6, 0, 0,84, 1,84, 1,84, 1,55,54,54,57,84, 1, 6, 6, 0, 0, 0, 0,84, 1, 4, 4, 4, 4, 4, 4,
       0, 0, 0,73, 8, 8, 8, 8,10, 1,84, 0, 0, 4, 4, 5, 5, 5, 5, 0, 0, 1,84, 6, 6, 1,84,56,53,53,58, 1,84, 5, 5, 0, 0, 0, 0, 1,84, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10,84, 1, 0, 0,22,21,21,21,21,23, 0, 0,84, 1, 5, 5,84, 1,51,48,47,52,84, 1, 0, 0, 0, 0, 6, 6,84, 1, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10, 1,84, 0, 0,19,18,18,18,18,20, 0, 0, 1,84, 0, 0, 1,84,49,63,44,50, 1,84, 0, 0, 0, 0, 5, 5, 1,84, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10, 2, 2, 0, 0,19,18,18,18,18,20, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10,15,15,16,16,19,18,18,18,18,20,16,17,15,15,16,17,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10,84, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0,84, 1, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6,84, 1, 6, 6, 6, 6,84, 1, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10, 1,84, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1,84, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 1,84, 5, 5, 5, 5, 1,84, 4, 4, 4, 4, 4, 4,
       8, 8, 8, 8, 8, 8, 8, 8,10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,84, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4,
       9, 9, 9, 9, 9, 9, 9, 9,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1,84, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,84, 1, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1,84, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,84, 1, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1,84, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3,69,68, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3,85,85, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 2, 2, 0, 0, 0, 0, 6, 6, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 2, 2, 0, 0, 0, 0, 5, 5, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, 0, 0, 4,
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, 0, 0, 4};

       int ArgentaMatrix[NB_BLOC_LARGEUR_ARGENTA * NB_BLOC_HAUTEUR_ARGENTA] =
       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
         0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        19,19,19,19,24, 2, 1, 7, 7, 7, 7,39,43,43,43,43,43,43,40,54,58,58,58,58,55, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
        17,17,17,17,20, 1, 2, 6, 6, 6, 6,41,44,44,44,44,44,44,42,56,59,59,59,59,57, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,
        17,17,17,17,20, 2, 1, 7, 7, 7, 7,60,64,64,64,64,64,64,61,52,50,51,50,51,53, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 0, 5, 5, 5, 5, 5,
        17,17,17,17,20, 1, 2, 6, 6, 6, 6,62,65,65,65,65,65,65,63,49,47,47,47,47,48, 6, 6, 0, 0, 0, 0, 6, 6, 6, 6, 0, 5, 5, 5, 5, 5,
        17,17,17,17,20, 3, 3, 0, 0, 0, 0,52,50,51,50,51,50,51,53, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
        17,17,17,17,20,10,10, 9,11, 9, 9,49,47,47,47,47,47,47,48,10,10, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,11, 9, 9, 9, 5, 5, 5, 5, 5,
        17,17,17,17,20, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 3, 2, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
        17,17,17,17,20, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3,16, 1, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
        17,17,17,17,20, 2, 1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,25,19,19,19,19,19,
        17,17,17,17,20, 1, 2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2,21,17,17,17,17,17,
        17,17,17,17,20, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0,30,29,29,31, 2, 1,21,17,17,17,17,17,
        17,17,17,17,20, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1 ,2, 0, 0, 0, 0, 0, 0, 0, 0,27,72,26,28, 1, 2,21,17,17,17,17,17,
        17,17,17,17,20, 2, 1, 0, 0, 0, 0, 2, 1,39,43,43,43,43,40, 2, 1, 2, 1,54,58,58,55, 2, 1, 2, 1, 2, 1, 2, 1,21,17,17,17,17,17,
        17,17,17,17,20, 1, 2, 0, 0, 0, 0, 1, 2,41,44,44,44,44,42, 1, 2, 1, 2,56,59,59,57, 1, 2, 1, 2, 1, 2, 1, 2,23,18,18,18,18,18,
        17,17,17,17,20, 2, 1, 0, 0, 0, 0, 3, 3,37,34,35,36,34,38, 2, 1, 0, 0,52,51,50,53, 0, 0, 0, 0, 0, 0, 2, 1, 8, 1, 2, 1, 2, 1,
        17,17,17,17,20, 1, 2, 0, 0, 0, 0, 3,15,32,26,26,26,71,33, 1, 2, 0, 0,49,70,45,48, 0, 0, 0, 0, 0, 0, 1, 2, 8, 2, 1, 2, 1, 2,
        17,17,17,17,20, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 8, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 3, 3, 8, 1, 2, 1, 2, 1,
        17,17,17,17,20, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 8, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3,14, 8, 2, 1, 2, 1, 2,
        17,17,17,17,20, 2, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1,25,19,19,19,19,19,
        17,17,17,17,20, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2,21,17,17,17,17,17,
        17,17,17,17,20, 2, 1, 2, 1, 2, 1, 2, 1,54,58,58,55, 2, 1, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1,21,17,17,17,17,17,
        17,17,17,17,20, 1, 2, 1, 2, 1, 2, 1, 2,56,59,59,57, 1, 2, 1, 2, 3, 3, 8, 8, 8,13, 8, 8, 8, 8, 3, 3, 1, 2,21,17,17,17,17,17,
        17,17,17,17,20, 2, 1, 0, 0, 0, 0, 0, 0,52,51,50,53, 7, 7, 2, 1, 0, 5, 7, 7, 7, 7, 7, 7, 7, 7, 5, 0, 2, 1,21,17,17,17,17,17,
        17,17,17,17,20, 1, 2, 0, 0, 0, 0, 0, 0,49,69,46,48, 6, 6, 1, 2, 0, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 0, 1, 2,23,18,18,18,18,18,
        17,17,17,17,20, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 5, 7, 7, 7, 7, 7, 7, 7, 7, 5, 0, 2, 1, 0, 4, 0, 0, 0, 0,
        17,17,17,17,20, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 0, 1, 2, 0, 4, 0, 0, 0, 0,
        17,17,17,17,20, 2, 1,30,29,29,31, 7, 7, 0, 0, 0, 0, 0, 0, 3, 3, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 2, 1, 0, 4, 0, 0, 0, 0,
        17,17,73,18,22, 1, 2,27,68,26,28, 6, 6, 0, 0, 0, 0, 0, 0, 3,12, 0, 5, 9, 9, 9,11, 9, 9, 9, 9, 5, 0, 1, 2, 0, 4, 0, 0, 0, 0,
        17,17,20, 4, 4, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 4, 0, 0, 0, 0,
        17,17,20, 4, 4, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 4, 0, 0, 0, 0,
        17,17,20, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 2, 1, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0,
        18,18,22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 1, 2, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5,75,76, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 1, 2, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,74,74,74,74,74,74, 2, 1, 8, 1, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,74,74,74,74,74,74, 1, 2, 8, 1, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,74,74,74,74,74,74, 2, 1,25,19,19,19,19,19,19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Création des vecteurs Cartes à partir des tableaux
    std::vector<int> Route1Map;
    for (v=0;v<NB_BLOC_LARGEUR_ROUTE1*NB_BLOC_HAUTEUR_ROUTE1;v++)
    {
        Route1Map.push_back(Route1Matrix[v]);
    }

    std::vector<int> Route2Map;
    for (v=0;v<NB_BLOC_LARGEUR_ROUTE2*NB_BLOC_HAUTEUR_ROUTE2;v++)
    {
        Route2Map.push_back(Route2Matrix[v]);
    }

    std::vector<int> Route22Map;
    for (v=0;v<NB_BLOC_LARGEUR_ROUTE22*NB_BLOC_HAUTEUR_ROUTE22;v++)
    {
        Route22Map.push_back(Route22Matrix[v]);
    }

    std::vector<int> BourgPaletteMap;
    for (v=0;v<NB_BLOC_LARGEUR_BOURGPALETTE*NB_BLOC_HAUTEUR_BOURGPALETTE;v++)
    {
        BourgPaletteMap.push_back(BourgPaletteMatrix[v]);
    }

    std::vector<int> MaisonChenMap;
    for (v=0;v<NB_BLOC_LARGEUR_MAISONCHEN*NB_BLOC_HAUTEUR_MAISONCHEN;v++)
    {
        MaisonChenMap.push_back(MaisonChenMatrix[v]);
    }

    std::vector<int> MaisonBlueMap;
    for (v=0;v<NB_BLOC_LARGEUR_MAISON*NB_BLOC_HAUTEUR_MAISON;v++)
    {
        MaisonBlueMap.push_back(MaisonBlueMatrix[v]);
    }

    std::vector<int> MaisonRedBasMap;
    for (v=0;v<NB_BLOC_LARGEUR_MAISON*NB_BLOC_HAUTEUR_MAISON;v++)
    {
        MaisonRedBasMap.push_back(MaisonRedBasMatrix[v]);
    }

    std::vector<int> MaisonRedHautMap;
    for (v=0;v<NB_BLOC_LARGEUR_MAISON*NB_BLOC_HAUTEUR_MAISON;v++)
    {
        MaisonRedHautMap.push_back(MaisonRedHautMatrix[v]);
    }

    std::vector<int> CentrePokemonMap;
    for (v=0;v<NB_BLOC_LARGEUR_CENTREPOKEMON*NB_BLOC_HAUTEUR_CENTREPOKEMON;v++)
    {
        CentrePokemonMap.push_back(CentrePokemonMatrix[v]);
    }

    std::vector<int> JadielleMap;
    for (v=0;v<NB_BLOC_LARGEUR_JADIELLE*NB_BLOC_HAUTEUR_JADIELLE;v++)
    {
        JadielleMap.push_back(JadielleMatrix[v]);
    }

    std::vector<int> ArgentaMap;
    for (v=0;v<NB_BLOC_LARGEUR_ARGENTA*NB_BLOC_HAUTEUR_ARGENTA;v++)
    {
        ArgentaMap.push_back(ArgentaMatrix[v]);
    }

    // Création des Classes Carte
    Carte Route1(NB_BLOC_LARGEUR_ROUTE1,NB_BLOC_HAUTEUR_ROUTE1,Route1Map,ROUTE1);
    Carte Route2(NB_BLOC_LARGEUR_ROUTE2,NB_BLOC_HAUTEUR_ROUTE2,Route2Map,ROUTE2);
    Carte Route22(NB_BLOC_LARGEUR_ROUTE22,NB_BLOC_HAUTEUR_ROUTE22,Route22Map,ROUTE22);
    Carte Palette(NB_BLOC_LARGEUR_BOURGPALETTE,NB_BLOC_HAUTEUR_BOURGPALETTE,BourgPaletteMap,PALETTE);
    Carte MaisonChen(NB_BLOC_LARGEUR_MAISONCHEN,NB_BLOC_HAUTEUR_MAISONCHEN,MaisonChenMap,CHEN);
    Carte MaisonBlue(NB_BLOC_LARGEUR_MAISON,NB_BLOC_HAUTEUR_MAISON,MaisonBlueMap,BLUE);
    Carte MaisonRedBas(NB_BLOC_LARGEUR_MAISON,NB_BLOC_HAUTEUR_MAISON,MaisonRedBasMap,REDBAS);
    Carte MaisonRedHaut(NB_BLOC_LARGEUR_MAISON,NB_BLOC_HAUTEUR_MAISON,MaisonRedHautMap,REDHAUT);
    Carte CentrePokemon(NB_BLOC_LARGEUR_CENTREPOKEMON,NB_BLOC_HAUTEUR_CENTREPOKEMON,CentrePokemonMap,CENTREPOKEMON);
    Carte Jadielle(NB_BLOC_LARGEUR_JADIELLE,NB_BLOC_HAUTEUR_JADIELLE,JadielleMap,JADIELLE);
    Carte Argenta(NB_BLOC_LARGEUR_ARGENTA,NB_BLOC_HAUTEUR_ARGENTA,ArgentaMap,ARGENTA);

    Route1.give_tiles(Route1Tiles);
    Route2.give_tiles(Route2Tiles);
    Route22.give_tiles(Route22Tiles);
    Palette.give_tiles(BourgPaletteTiles);
    MaisonChen.give_tiles(MaisonChenTiles);
    MaisonBlue.give_tiles(MaisonBlueTiles);
    MaisonRedBas.give_tiles(MaisonRedTiles);
    MaisonRedHaut.give_tiles(MaisonRedTiles);
    CentrePokemon.give_tiles(CentrePokemonTiles);
    Jadielle.give_tiles(JadielleTiles);
    Argenta.give_tiles(ArgentaTiles);

    Route1.give_music(MusicRoute1);
    Route2.give_music(MusicForetJade);
    Route22.give_music(MusicRoute10);
    Palette.give_music(MusicPalette);
    MaisonBlue.give_music(MusicPalette);
    MaisonRedBas.give_music(MusicPalette);
    MaisonRedHaut.give_music(MusicPalette);
    CentrePokemon.give_music(MusicCentre);
    MaisonChen.give_music(MusicLabo);
    Jadielle.give_music(MusicJadielle);
    Argenta.give_music(MusicJadielle);

    std::vector< std::vector<SDL_Surface*> > PNJRoute1;
    PNJRoute1.push_back(silver);
    std::vector< std::vector<SDL_Surface*> > PNJMaisonChen;
    PNJMaisonChen.push_back(scientifique);
    PNJMaisonChen.push_back(chen);
    std::vector< std::vector<SDL_Surface*> > PNJPalette;
    PNJPalette.push_back(gros);
    std::vector< std::vector<SDL_Surface*> > PNJCentrePokemon;
    PNJCentrePokemon.push_back(infirmiere);
    std::vector< std::vector<SDL_Surface*> > PNJJadielle;
    PNJJadielle.push_back(saoul);
    PNJJadielle.push_back(fillette);
    std::vector< std::vector<SDL_Surface*> > PNJMaisonBlue;
    PNJMaisonBlue.push_back(bluesister);

    std::vector<int> dirRoute1;
    dirRoute1.push_back(GAUCHE);
    std::vector<int> dirMaisonChen;
    dirMaisonChen.push_back(GAUCHE);
    dirMaisonChen.push_back(HAUT);
    std::vector<int> dirPalette;
    dirPalette.push_back(DROITE);
    std::vector<int> dirJadielle;
    dirJadielle.push_back(GAUCHE);
    dirJadielle.push_back(GAUCHE);
    std::vector<int> dirMaisonBlue;
    dirMaisonBlue.push_back(GAUCHE);
    std::vector<int> dirCentrePokemon;
    dirCentrePokemon.push_back(BAS);

    Route1.give_pnj(PNJRoute1);
    MaisonChen.give_pnj(PNJMaisonChen);
    Route1.give_direction(dirRoute1);
    MaisonChen.give_direction(dirMaisonChen);
    Palette.give_pnj(PNJPalette);
    Palette.give_direction(dirPalette);
    CentrePokemon.give_pnj(PNJCentrePokemon);
    CentrePokemon.give_direction(dirCentrePokemon);
    Jadielle.give_direction(dirJadielle);
    Jadielle.give_pnj(PNJJadielle);
    MaisonBlue.give_direction(dirMaisonBlue);
    MaisonBlue.give_pnj(PNJMaisonBlue);

    Route1.give_PokeSauvage(SauvageRoute1);
    Route1.give_ProbaApparition(ProbaRoute1);
    Route2.give_PokeSauvage(SauvageRoute2);
    Route2.give_ProbaApparition(ProbaRoute2);
    Route22.give_PokeSauvage(SauvageRoute22);
    Route22.give_ProbaApparition(ProbaRoute22);

    MaisonChen.give_PokeBall(Pikachu);
    MaisonChen.give_Tile(TableHaut);
    MaisonChen.give_numTile(13);

    std::vector<Carte> World;
    World.push_back(MaisonRedBas);
    World.push_back(MaisonRedHaut);
    World.push_back(MaisonBlue);
    World.push_back(Palette);
    World.push_back(MaisonChen);
    World.push_back(CentrePokemon);
    World.push_back(Route1);
    World.push_back(Route2);
    World.push_back(Route22);
    World.push_back(Jadielle);
    World.push_back(Argenta);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////     CARTE      //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Carte Carte_Actuelle = Palette;
    Carte update_carte = Carte_Actuelle;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // activation de la répétition des touches
    SDL_EnableKeyRepeat(2,50);
    LoadMap(tiles,Carte_Actuelle);
    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
    // Jouer la musique indéfiniment
    Mix_PlayMusic(Carte_Actuelle.get_music(),-1);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
           switch(event.key.keysym.sym)
            {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////     HAUT       //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDLK_UP:
                // Chargement des personnages en mouvement et statique dans la direction indiquée
                gold_mouv = gold[MI_HAUT];
                gold_static = gold[HAUT];
                // Appel de la fonction deplacerJoueur pour mettre à jour la position du joueur en fonction de son environnement
                direction = HAUT;
                deplacerJoueur(Carte_Actuelle, &positionJoueur, direction, obstacle);

                // Ajustement des positions à l'échelle de la carte (par tranche de TAILLE_BLOC pixels)
                position.x = positionJoueur.x * TAILLE_BLOC;
                position.y = positionJoueur.y * TAILLE_BLOC;
                // positionIntermediaire
                positionIntermediaire.x = positionJoueur.x*TAILLE_BLOC;
                positionIntermediaire.y = positionJoueur.y*TAILLE_BLOC+ TAILLE_BLOC;
                // Si la case du haut est un obstacle, le personnage fait du sur place
                if (obstacle == true)
                {
                    Mix_PlayChannel(0, Bump, 0);
                    AfficherCarte(ecran, gold_mouv, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(120);
                    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(30);
                }
                else if (obstacle == false)
                {
                    for (i=0;i<4;i++)
                    {
                        offset.y = 2*i;
                        AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    for (i=4;i<8;i++)
                    {
                        offset.y = 2*i;
                        AfficherCarte(ecran, gold_mouv, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    offset.y = 16;
                    AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                    offset.y = 0;
                }
                get_tileprop(Carte_Actuelle,&positionJoueur,direction,txt,pnj,soin,ball,tiletext);
                break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////     BAS      //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Les cas suivants (Bas, Gauche, Droite) sont identiques au cas Haut
            case SDLK_DOWN:
                gold_mouv = gold[MI_BAS];
                gold_static = gold[BAS];

                direction = BAS;
                deplacerJoueur(Carte_Actuelle, &positionJoueur, direction, obstacle);

                positionIntermediaire.x = positionJoueur.x*TAILLE_BLOC;
                positionIntermediaire.y = positionJoueur.y*TAILLE_BLOC-TAILLE_BLOC;
                position.x = positionJoueur.x * TAILLE_BLOC;
                position.y = positionJoueur.y * TAILLE_BLOC;
                if (obstacle == true)
                {
                    Mix_PlayChannel(0, Bump, 0);
                    AfficherCarte(ecran, gold_mouv, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(120);
                    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(30);
                }
                else if (obstacle == false)
                {
                    for (i=0;i<4;i++)
                    {
                        offset.y = -2*i;
                        AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    for (i=4;i<8;i++)
                    {
                        offset.y = -2*i;
                        AfficherCarte(ecran, gold_mouv, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    offset.y = -16;
                    AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                    offset.y = 0;
                }
                get_tileprop(Carte_Actuelle,&positionJoueur,direction,txt,pnj,soin,ball,tiletext);
                break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////     GAUCHE       /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDLK_LEFT:
                gold_mouv = gold[MI_GAUCHE];
                gold_static = gold[GAUCHE];

                direction = GAUCHE;
                deplacerJoueur(Carte_Actuelle, &positionJoueur, direction, obstacle);

                positionIntermediaire.x = positionJoueur.x*TAILLE_BLOC + TAILLE_BLOC;
                positionIntermediaire.y = positionJoueur.y*TAILLE_BLOC;
                position.x = positionJoueur.x * TAILLE_BLOC;
                position.y = positionJoueur.y * TAILLE_BLOC;
                if (obstacle == true)
                {
                    Mix_PlayChannel(0, Bump, 0);
                    AfficherCarte(ecran, gold_mouv, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(120);
                    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(30);
                }
                else if (obstacle == false)
                {
                    for (i=0;i<4;i++)
                    {
                        offset.x = 2*i;
                        AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    for (i=4;i<8;i++)
                    {
                        offset.x = 2*i;
                        AfficherCarte(ecran, gold_mouv, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    offset.x = 16;
                    AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                    offset.x = 0;
                }

                get_tileprop(Carte_Actuelle,&positionJoueur,direction,txt,pnj,soin,ball,tiletext);
                break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////     DROITE       /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDLK_RIGHT:
                gold_mouv = gold[MI_DROITE];
                gold_static = gold[DROITE];

                direction = DROITE;
                deplacerJoueur(Carte_Actuelle, &positionJoueur, direction, obstacle);

                positionIntermediaire.x = positionJoueur.x*TAILLE_BLOC - TAILLE_BLOC;
                positionIntermediaire.y = positionJoueur.y*TAILLE_BLOC;
                position.x = positionJoueur.x * TAILLE_BLOC;
                position.y = positionJoueur.y * TAILLE_BLOC;
                if (obstacle == true)
                {
                    Mix_PlayChannel(0, Bump, 0);
                    AfficherCarte(ecran, gold_mouv, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(120);
                    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                    SDL_Delay(30);
                }
                else if (obstacle == false)
                {
                    for (i=0;i<4;i++)
                    {
                        offset.x = -2*i;
                        AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    for (i=4;i<8;i++)
                    {
                        offset.x = -2*i;
                        AfficherCarte(ecran, gold_mouv, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                        SDL_Delay(1);
                    }
                    offset.x = -16;
                    AfficherCarte(ecran, gold_static, &positionIntermediaire, Carte_Actuelle, &offset,tiles);
                    offset.x = 0;
                }
                get_tileprop(Carte_Actuelle,&positionJoueur,direction,txt,pnj,soin,ball,tiletext);
                break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////    ACTION     ///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            case SDLK_SPACE:
                if (pnj==true)
                {
                    int p;
                    if (direction == HAUT)
                    {
                        p = positionJoueur.x + (positionJoueur.y-1)*Carte_Actuelle.get_width();
                    }
                    else if (direction == BAS)
                    {
                        p = positionJoueur.x + (positionJoueur.y+1)*Carte_Actuelle.get_width();
                    }
                    else if (direction == GAUCHE)
                    {
                        p = positionJoueur.x-1 + positionJoueur.y*Carte_Actuelle.get_width();
                    }
                    else if (direction == DROITE)
                    {
                        p = positionJoueur.x+1 + positionJoueur.y*Carte_Actuelle.get_width();
                    }

                    update_direction = Carte_Actuelle.get_direction();
                    update_direction[Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[p]].get_nbPNJ()] = direction;
                    Carte_Actuelle.give_direction(update_direction);
                    update_direction.clear();
                }
                if (txt==true)
                {
                    AfficherTxt(ecran, gold_static, &position,Carte_Actuelle,tiletext);
                    SDL_Delay(500);
                }
                if (soin==true)
                {
                    teamSize = Gold.get_team().size();
                    for (i=0;i<teamSize;i++)
                    {
                        Poke1 = Gold.get_team()[i];
                        Poke1.change_vie(Poke1.get_viemax());
                        update_team.push_back(Poke1);
                    }
                    Gold.give_team(update_team);
                    update_team.clear();
                }
                if (ball==true)
                {
                    teamSize = Gold.get_team().size();
                    if (teamSize<6)
                    {
                        for (i=0;i<teamSize;i++)
                        {
                            update_team.push_back(Gold.get_team()[i]);
                        }
                        update_team.push_back(Carte_Actuelle.get_pokeball());
                        Gold.give_team(update_team);
                        update_team.clear();
                    }
                    update_tiles = Carte_Actuelle.get_tiles();
                    update_carte = Carte_Actuelle;
                    update_tiles[Carte_Actuelle.get_numTile()] = Carte_Actuelle.get_tile();
                    update_carte.give_tiles(update_tiles);
                    World[Carte_Actuelle.get_nb()] = update_carte;
                    Carte_Actuelle = World[Carte_Actuelle.get_nb()];
                    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                }
                break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////     Change Ordre Equipe       ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDLK_LSHIFT:
                teamSize = Gold.get_team().size();
                for (i=0;i<teamSize;i++)
                {
                    update_team.push_back(Gold.get_team()[i]);
                }
                update_team[1] = Tortank;
                Gold.give_team(update_team);
                update_team.clear();

                break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////    START // QUIT      ///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDLK_BACKSPACE:
                //Start(ecran);
                update_team = Gold.get_team();
                PokemonChoice(ecran, update_team);
                Gold.give_team(update_team);
                update_team.clear();
                AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                break;

            case SDLK_ESCAPE:
                continuer = 0;
                break;

            default:;
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////     COMBAT Pokemon Sauvage       /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // Si la case d'arrivée est une case HAUTES_HERBES, 1 chance sur 10 d'apparition d'un Pokemon sauvage
            if (Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[positionJoueur.x+positionJoueur.y*Carte_Actuelle.get_width()]].get_prop()==COMBATPKM)
            {
                Poke1 = Gold.get_team()[0];
                combatAlea = rand()%100+1;
                    if (combatAlea<10)
                    {
                        pokeAlea = rand()%1000+1;
                        int p = 0, sauvageNumber = Carte_Actuelle.get_sauvage().size();
                        while (Carte_Actuelle.get_proba()[p]<pokeAlea and p<sauvageNumber)
                        {
                            p+=1;
                        }
                        Mix_PlayMusic(MusicCombat,-1);
                        i = 0;
                        while (i<4)
                        {
                            BlackScreen(ecran);
                            SDL_Delay(200);
                            AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                            SDL_Delay(200);
                            i++;
                        }

                        //SDL_Delay(2000);

                        IntroCombat(Carte_Actuelle.get_sauvage()[p].get_imagefront());
                        combatPokemon(Poke1,Carte_Actuelle.get_sauvage()[p]);
                        Mix_PlayMusic(Carte_Actuelle.get_music(),-1);
                        AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                        update_team.push_back(Poke1);
                        teamSize = Gold.get_team().size();
                        for (i=1;i<teamSize;i++)
                        {
                            update_team.push_back(Gold.get_team()[i]);
                        }
                        Gold.give_team(update_team);
                        update_team.clear();
                    }
                }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////     COMBAT Dresseur      /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //Déclencher un combat de dresseurs
                if (Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[positionJoueur.x+positionJoueur.y*Carte_Actuelle.get_width()]].get_prop()==COMBATPNJ)
                {
                    Dresseur Dresseur_Actuel = Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[positionJoueur.x+positionJoueur.y*Carte_Actuelle.get_width()]].get_dresseur();
                    Pokemon PokeEnnemi = Dresseur_Actuel.get_team()[0];
                    if (Silver.isdefeat()==false)
                    {
                        int isTexte = 0;
                        Mix_PlayMusic(MusicRival,-1);
                        DistanceJoueur(&position,&positionRival,Carte_Actuelle);
                        positionRival.y -= TAILLE_BLOC;
                        AfficherCarteRival(ecran, gold_static,silver8, &position, &positionRival, Carte_Actuelle, isTexte, isCurseur);
                        SDL_Delay(500);
                        positionRival.y += TAILLE_BLOC;
                        int posRivalx = positionRival.x;
                        for (i=1;i<(positionJoueur.x - positionRival.x/TAILLE_BLOC-1);i++)
                        {
                            positionRival.x = posRivalx + i*TAILLE_BLOC;
                            positionRivalIntermediaire.x = positionRival.x - 0.5*TAILLE_BLOC;
                            AfficherCarteRival(ecran, gold_static,silver_mouv, &position, &positionRivalIntermediaire, Carte_Actuelle, isTexte, isCurseur);
                            SDL_Delay(200);
                            AfficherCarteRival(ecran, gold_static, silver_static, &position, &positionRival, Carte_Actuelle, isTexte, isCurseur);
                            SDL_Delay(200);
                        }
                        isTexte = 1;
                        AfficherCarteRival(ecran, gold_static, silver_static, &position, &positionRival, Carte_Actuelle, isTexte, isCurseur);
                        SDL_Delay(700);

                        Input inRival;
                        while (!inRival.key[SDLK_SPACE])
                        {
                            if (!inRival.key[SDLK_SPACE])
                            {
                                isCurseur = true;
                                AfficherCarteRival(ecran, gold_static, silver_static, &position, &positionRival, Carte_Actuelle, isTexte, isCurseur);
                                SDL_Delay(250);
                            }
                            inRival.UpdateEvent();
                            if (!inRival.key[SDLK_SPACE])
                            {
                                isCurseur = false;
                                AfficherCarteRival(ecran, gold_static, silver_static, &position, &positionRival, Carte_Actuelle, isTexte, isCurseur);
                                SDL_Delay(250);
                            }
                            inRival.UpdateEvent();
                        }
                        isCurseur = false;
                        isTexte = 0;
                        AfficherCarteRival(ecran, gold_static, silver_static, &position, &positionRival, Carte_Actuelle, isTexte, isCurseur);
                        Mix_PlayMusic(MusicCombatRival,-1);
                        SDL_Delay(1500);

                        Poke1 = Gold.get_team()[0];
                        Poke2 = Gold.get_team()[1];
                        IntroCombat(Dresseur_Actuel.get_image());
                        combatDresseur(Gold,Dresseur_Actuel);
                        combat(Poke1,PokeEnnemi);
                        if (Gold.get_team().size()>1 and Poke1.get_vie()==0)
                        {
                            combat(Poke2,PokeEnnemi);
                        }
                        update_team.push_back(Poke1);
                        teamSize = Gold.get_team().size();
                        for (i=1;i<teamSize;i++)
                        {
                            update_team.push_back(Gold.get_team()[i]);
                        }
                        Gold.give_team(update_team);
                        update_team.clear();

                        positionRival.x = 2*TAILLE_BLOC;
                        positionRival.y = 4*TAILLE_BLOC-4;
                        Mix_PlayMusic(Carte_Actuelle.get_music(),-1);
                        AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                        Silver.defeated();
                    }
                }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////     Changement de carte      ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                if (Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[positionJoueur.x+positionJoueur.y*Carte_Actuelle.get_width()]].get_prop()==CHANGEMAP)
                {
                    FreeMap(tiles);
                    //Récupére le numéro de l'ancienne carte
                    int lastMap = Carte_Actuelle.get_nb();
                    postmp = Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[positionJoueur.x+positionJoueur.y*Carte_Actuelle.get_width()]].get_position();

                    Carte_Actuelle = World[Carte_Actuelle.get_tiles()[Carte_Actuelle.get_map()[positionJoueur.x+positionJoueur.y*Carte_Actuelle.get_width()]].get_carte()];
                    if (Carte_Actuelle.get_nb()>=PALETTE and lastMap>=PALETTE)
                    {
                        Mix_PlayMusic(Carte_Actuelle.get_music(),-1);
                    }
                    positionJoueur = postmp;
                    position.x = positionJoueur.x * TAILLE_BLOC;
                    position.y = positionJoueur.y * TAILLE_BLOC;
                    LoadMap(tiles,Carte_Actuelle);
                    AfficherCarte(ecran, gold_static, &position, Carte_Actuelle, &offset,tiles);
                }
            break;
            default:;
        }
    }
    // Désactivation de la répétition des touches
    SDL_EnableKeyRepeat(0,0);

    // Libération des surfaces chargées et des musiques
    for (i=0;i<8;i++)
        SDL_FreeSurface(gold[i]);

    for (i=0;i<4;i++)
    {
        SDL_FreeSurface(silver[i]);
        SDL_FreeSurface(scientifique[i]);
        SDL_FreeSurface(gros[i]);
        SDL_FreeSurface(chen[i]);
        SDL_FreeSurface(bluesister[i]);
    }

    SDL_FreeSurface(silver8);
    SDL_FreeSurface(filletteGAUCHE);
    SDL_FreeSurface(infirmiereBAS);
    SDL_FreeSurface(saoul1);

    Mix_FreeMusic(MusicRoute1);
    Mix_FreeMusic(MusicRoute10);
    Mix_FreeMusic(MusicPalette);
    Mix_FreeMusic(MusicJadielle);
    Mix_FreeMusic(MusicLabo);
    Mix_FreeMusic(MusicCentre);
    Mix_FreeMusic(MusicCombat);
    Mix_FreeMusic(MusicLegendary);
    Mix_FreeMusic(MusicRival);
    Mix_FreeMusic(MusicCombatRival);
    Mix_FreeChunk(Bump);
}

#endif // JEU_H
