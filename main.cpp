#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "structures.h"
#ifdef __MINGW32__
#undef main
#endif

Evenement Event();
void affichage_joueur(SDL_Surface *ecran, Personnage joueur, taille *tai);
void animation(Animation *anim);
void initAnim (Animation *anim);
void camera(SDL_Rect *position,Evenement key, Personnage *joueur1, taille* tai);
void affichage_anim(SDL_Surface *ecran, Personnage joueur,taille *tai,Animation *anim);

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Surface *background = IMG_Load("0000100000.pcx");
    SDL_Surface *heu = IMG_Load("0000100001.pcx");
    SDL_Rect position;
    Evenement key;
    Personnage joueur1, joueur2;
    taille tai, tai2;
    int test=0;
    key.quit=0;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_WM_SetCaption("VanPri", NULL);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_Music *musique=Mix_LoadMUS("AcademyGrounds.ogg");
    Mix_PlayMusic(musique, -1);

    ecran = SDL_SetVideoMode(640, 480, 24,  SDL_DOUBLEBUF);

    joueur1.image= IMG_Load("anim.png");
    joueur2.image= IMG_Load("anim");
    joueur1.position.x=50;
    joueur1.position.y=190;
    joueur2.position.x=NULL;
    joueur2.position.y=NULL;

    initAnim(&joueur1.anim);
    initAnim(&joueur2.anim);
    joueur2.anim.n[0]=25;
    joueur2.anim.c=1;
    joueur1.anim.n[0]=12;
    joueur1.anim.c=2;

    tai2.x=640;
    tai2.y=480;
    tai.x=216;
    tai.y=278;

    SDL_Rect p,v,front1;

    position.x=-300;
    position.y=-480;
    v.y=487-267;
    v.x=position.x;

    SDL_SetColorKey(heu, SDL_SRCCOLORKEY, SDL_MapRGB(heu->format,255,0,0));

    while(key.quit==0)
    {
        key=Event();
        joueur1.anim.o=0;
        joueur1.anim.o=0;

        if(key.touche[SDLK_ESCAPE]==1)
            key.quit=1;
        camera(&position,key,&joueur1,&tai);

        //remise en positif des RECT
        p=position;
        front1=v;

        //mise des images dans l'ordre des calques
        SDL_BlitSurface(background,NULL,ecran,&p);

        //affichage du personnage
        affichage_joueur(ecran,joueur1, &tai);

        //front surface
        SDL_BlitSurface(heu,NULL,ecran,&front1);

        if(key.touche[SDLK_SPACE]==1)
            affichage_anim(ecran,joueur2, &tai2,&joueur2.anim);

        SDL_Flip(ecran);
        animation(&joueur1.anim);

        SDL_Delay(33);
    }
    return 0;
}
