#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>

void Start(SDL_Surface *ecran)
{
    SDL_Surface *menu = NULL;
    SDL_Rect posMenu;

    menu = SDL_LoadBMP("menu/start.bmp");

    posMenu.x = 0;
    posMenu.y = 0;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    SDL_BlitSurface(menu, NULL, ecran, &posMenu);

    SDL_Flip(ecran);

    SDL_FreeSurface(menu);
}

void AfficherMenuPokemon(SDL_Surface *ecran, int posPointeur, int posPointeurSelect, bool change, std::vector<Pokemon> team)
{
    TTF_Font *police = NULL;
    police = TTF_OpenFont("ttf/pkmnemn.ttf", 16);
    SDL_Color couleurNoire = {0,0,0};
    SDL_Surface *pointeur = NULL, *pointeur_select = NULL, *texteRetour = NULL, *textePoke, *texteNiveau, *barrePV, *PV, *PV_actuel, *PV_moyen, *PV_faible, *level;
    const char* retour = "RETOUR";
    int barreVie, niveauPoke;
    int teamSize = team.size();
    char buffer [20];

    texteRetour = TTF_RenderText_Blended(police, retour, couleurNoire);

    SDL_Rect positionPointeur, positionPointeurSelect, positionTexteRetour, positionBarrePV, positionTextePoke, positionPV, positionLevel, positionNiveau;

    positionPointeur.x = 0;
    positionPointeur.y = 8 + posPointeur*16;

    positionPointeurSelect.x = 0;
    positionPointeurSelect.y = 8 + posPointeurSelect*16;

    positionTexteRetour.x = 8;
    positionTexteRetour.y = 100;

    positionBarrePV.x = 88;

    positionLevel.x = 64;

    positionNiveau.x = 72;

    positionTextePoke.x = 8;

    pointeur = SDL_LoadBMP("combat_image/pointeur.bmp");
    pointeur_select = SDL_LoadBMP("combat_image/pointeur_select.bmp");
    barrePV = SDL_LoadBMP("combat_image/barre_pv.bmp");
    PV = SDL_LoadBMP("combat_image/vie.bmp");
    PV_moyen = SDL_LoadBMP("combat_image/vie_moyenne.bmp");
    PV_faible = SDL_LoadBMP("combat_image/vie_critique.bmp");
    level = SDL_LoadBMP("combat_image/niveau.bmp");

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    if (change == true)
    {
        SDL_BlitSurface(pointeur_select, NULL, ecran, &positionPointeurSelect);
    }

    SDL_BlitSurface(pointeur, NULL, ecran, &positionPointeur);
    SDL_BlitSurface(texteRetour, NULL, ecran, &positionTexteRetour);

    for (int i=0;i<teamSize;i++)
    {
        positionTextePoke.y = 4 + i*16;
        positionBarrePV.y = 16 + i*16;
        positionPV.x = 104;
        positionPV.y = 19 + i*16;
        positionLevel.y = 16 + i*16;
        positionNiveau.y = 12 + i*16;
        textePoke = TTF_RenderText_Blended(police, team[i].get_nom().data(), couleurNoire);
        niveauPoke = team[i].get_niveau();
        const char* texteNiveauPoke = itoa(niveauPoke,buffer,10);
        texteNiveau = TTF_RenderText_Blended(police, texteNiveauPoke, couleurNoire);
        SDL_BlitSurface(textePoke, NULL, ecran, &positionTextePoke);
        SDL_BlitSurface(barrePV, NULL, ecran, &positionBarrePV);
        SDL_BlitSurface(level, NULL, ecran, &positionLevel);
        SDL_BlitSurface(texteNiveau, NULL, ecran, &positionNiveau);

        barreVie = (int) floor(team[i].get_vie()*TAILLE_BARRE_VIE/team[i].get_viemax());
        if (barreVie > 24)
        {
            PV_actuel = PV;
        }
        else if (barreVie < 8)
        {
            PV_actuel = PV_faible;
        }
        else
        {
            PV_actuel = PV_moyen;
        }

        int PVx = positionPV.x;
        for (int j=0; j<barreVie;j++)
        {
            positionPV.x = PVx+j;
            SDL_BlitSurface(PV_actuel, NULL, ecran, &positionPV);
        }
    }

    SDL_Flip(ecran);

    SDL_FreeSurface(pointeur);
    SDL_FreeSurface(pointeur_select);
    SDL_FreeSurface(barrePV);
    SDL_FreeSurface(PV);
    SDL_FreeSurface(PV_moyen);
    SDL_FreeSurface(PV_faible);
    SDL_FreeSurface(PV_actuel);
    SDL_FreeSurface(level);
    SDL_FreeSurface(texteRetour);
    SDL_FreeSurface(textePoke);
}

void PokemonChoice(SDL_Surface *ecran, std::vector<Pokemon> &team)
{
    Mix_Chunk *Choose;
    Mix_AllocateChannels(1);
    Choose = Mix_LoadWAV("chunk/choose.wav");

    Pokemon Poke1, Poke2;
    SDL_Event event;
    int posPointeur = 0, posPointeurSelect = 0, continuer = 1, teamSize = team.size();
    bool change = false;
    AfficherMenuPokemon(ecran,posPointeur,posPointeurSelect,change,team);
    SDL_EnableKeyRepeat(0,0);
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_DOWN:
                        if (posPointeur == 6)
                        {
                            posPointeur = 0;
                        }
                        else if (posPointeur == teamSize-1)
                        {
                            posPointeur = 6;
                        }
                        else
                        {
                            posPointeur += 1;
                        }
                        Mix_PlayChannel(0, Choose, 0);
                        AfficherMenuPokemon(ecran,posPointeur,posPointeurSelect,change,team);

                    break;
                    case SDLK_UP:
                        if (posPointeur == 0)
                        {
                            posPointeur = 6;
                        }
                        else if (posPointeur == 6)
                        {
                            posPointeur = teamSize-1;
                        }
                        else
                        {
                            posPointeur -= 1;
                        }
                        Mix_PlayChannel(0, Choose, 0);
                        AfficherMenuPokemon(ecran,posPointeur,posPointeurSelect,change,team);

                    break;
                    case SDLK_SPACE:
                        if (posPointeur == 6)
                        {
                            continuer = 0;
                        }
                        else
                        {
                            if (change == false)
                            {
                                change = true;
                                posPointeurSelect = posPointeur;
                            }
                            else
                            {
                                change = false;
                                Poke1 = team[posPointeurSelect];
                                Poke2 = team[posPointeur];
                                team[posPointeurSelect] = Poke2;
                                team[posPointeur] = Poke1;
                            }
                        }
                        Mix_PlayChannel(0, Choose, 0);
                        AfficherMenuPokemon(ecran,posPointeur,posPointeurSelect,change,team);

                    break;
                    case SDLK_ESCAPE:
                        continuer = 0;
                    break;
                    default:;
                }
            break;
            default:;
        }
    }
    SDL_EnableKeyRepeat(2,50);

    Mix_FreeChunk(Choose);
}



#endif // MENU_H
