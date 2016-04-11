#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "structures.h"
#ifdef __MINGW32__
#undef main
#endif

using namespace std;

void affichage_joueur(SDL_Surface *ecran, Personnage joueur,taille *tai)
{
    SDL_Rect tiles;
    tiles.x=joueur.anim.i*(tai->x);
    tiles.y=(tai->y)*joueur.anim.o;
    tiles.w=tai->x;
    tiles.h=tai->y;
    SDL_BlitSurface(joueur.image,&tiles,ecran,&joueur.position);
}

void animation(Animation *anim)
{
    anim->tmp+=1;
    if(anim->tmp > anim->c)
    {
        anim->i+=1;
        anim->tmp=0;
    }
    if(anim->i >= anim->n[anim->o])
        anim->i=0;

}

void affichage_anim(SDL_Surface *ecran, Personnage joueur,taille *tai,Animation *anim)
{
    bool finanim;
    SDL_Rect tiles;

    while(finanim)
    {
        tiles.x=anim->i*(tai->x);
        tiles.y=(tai->y)*0;
        tiles.w=tai->x;
        tiles.h=tai->y;
        SDL_BlitSurface(joueur.image,&tiles,ecran,&joueur.position);

        SDL_Flip(ecran);

        anim->tmp+=1;
        if(anim->tmp > anim->c)
        {
            anim->i+=1;
            anim->tmp=0;
        }
        if(anim->i >= anim->n[anim->o])
        {
            finanim=false;
            anim->i=0;
        }


        SDL_Delay(33);
    }
}

void initAnim (Animation *anim)
{
    anim->i=0;
    anim->tmp=0;
    anim->tmpo=0;
    anim->o=0;

}
void camera(SDL_Rect *position,Evenement key, Personnage *joueur1, taille *tai)
{
        if(key.touche[SDLK_RIGHT]==1)
        {
            /*tai->x=50;
            tai->y=105;*/
            joueur1->anim.o=1;

        }
        if(key.touche[SDLK_DOWN]==1)
        {
            /*tai->x=50;
            tai->y=105;*/
            joueur1->anim.o=1;

        }
        if(key.touche[SDLK_UP]==1)
        {
            /*tai->x=50;
            tai->y=105;*/
            joueur1->anim.o=2;

        }
        if(key.touche[SDLK_LEFT]==1)
        {
            /*tai->x=50;
            tai->y=105;*/
            joueur1->anim.o=3;

        }
        /*if(key.touche[SDLK_SPACE]==1)
        {
            /*tai->x=60;
            tai->y=150;
            joueur1->anim.o=4;
        }*/

}
