#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SDL/SDL.h>

typedef struct
{
	SDL_Rect R;
	int mur,OBSTACLE;
	// tout ce que vous voulez...
} TileProp;

class Map
{
    private:

    public:

    int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY;
	SDL_Surface* tileset;
	TileProp* props;
	Uint16** schema;
	int nbtiles_largeur_monde,nbtiles_hauteur_monde;
	int xscroll,yscroll;
	int largeur_fenetre,hauteur_fenetre;
	Map* ChargerMap(const char* fic,int largeur_fenetre,int hauteur_fenetre);

};


#endif // MAP_H_INCLUDED
