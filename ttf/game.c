#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>
#include "ttffonc.h"
#include "verifie.h"
#include "affichage.h"
#include "game.h"
#include "sauv.h"
int game()
{   FILE* F2;
    int p=0,temps=120,chkoukou=2,q;
    size_t x1,y1;
    int score=1000;
    int k[36]; //tableau de compteur
    srand(time(NULL));
    int num[7][7];
    char nom[50];
    saved player;
    //
    gets(nom);
    //boutton
 int km[36];
 //les numeros
 int v[49];
for (int i=0; i<49; i++){
       v[i]=0;
    }
 int c;
 for (int i=0;i<36;i++){
    km[i]=(rand()%2)+1;
    int j=i/6;
    if (km[i]==1){
       //represente les lignes
       c=j+i;
       v[c]++;
       c=i+j+8;
       v[c]++;
    }
    if(km[i]==2){
       //represente les lignes
       c=j+i+1;
       v[c]++;
       c=i+j+7;
       v[c]++;
    }
 }

int i=0;
    for (int m=0; m<7; m++){
        for(int l=0; l<7; l++){
            num[m][l]=v[i];
            i++;
        }
    }
//
F2=fopen("C:/mat.bin","wb");

    for (int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            fwrite(&num[i][j],sizeof(int),1,F2);
        }
    }
    fclose(F2);
    //
   unsigned int lastTime = 0, currentTime;
   SDL_Rect rectangle2;
   SDL_Texture* wintxt=NULL;
   SDL_Rect winrect={580,580,500,500};
    TTF_Init();
    //creer un rectangle pour GO
    SDL_Rect gorect={580,0,100,100};
    //creer un rectangle pour name
    SDL_Rect namrect={450,140,300,100};
    //creer un boutton pour save
    SDL_Rect saverect={0,0,80,80};
    //creer un rectangle pour pause
    SDL_Rect pausrect={100,0,100,100};
     //creer un rectangle pour mute
    SDL_Rect muterect={1000,0,100,100};
    //rectangle pour le timer
    SDL_Rect timerrect={450,0,300,120};
    //
    SDL_Window *window = NULL;
    SDL_Renderer *pRenderer = NULL;
    SDL_Texture* txt = NULL;//texture
    //Lancement SDL
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  //initialiser sdl mixer
  Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
  // charger le fichier audio
  Mix_Music *music= Mix_LoadMUS("play1.mp3");
  if(music==NULL){
    printf("eror");
  }
  //initialiser compteur
  for(int i=0;i<36;i++){
    k[i]=0;
  }
    affichevecteur(k);

    //Création fenêtre
    window = SDL_CreateWindow("PLAY",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, 0 );
    if(window == NULL)
        SDL_ExitWithError("Creation fenetre echouee");
    /*------------------------------------------------------------*/
   pRenderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
    if(pRenderer==NULL)
    {
        SDL_ExitWithError("creation echouee");
    }
    //afficher rendu----------------------------------------------
    SDL_SetRenderDrawColor(pRenderer, 40, 174, 204, 255);
    SDL_RenderClear(pRenderer);
    SDL_RenderPresent(pRenderer);
    //init sdl_ttf
    if(TTF_Init()==-1)
{
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
}

     txt=loadttf("GO!!",pRenderer,100,251, 255, 226);
      SDL_RenderCopy(pRenderer,txt,NULL,&gorect);
      SDL_RenderPresent(pRenderer);
      txt=loadttf("save",pRenderer,40,251, 255, 226);
      SDL_RenderCopy(pRenderer,txt,NULL,&saverect);
      SDL_RenderPresent(pRenderer);
      txt=loadttf("PAUSE",pRenderer,40,251, 255, 226);
      SDL_RenderCopy(pRenderer,txt,NULL,&pausrect);
      SDL_RenderPresent(pRenderer);
       txt=loadttf("mute",pRenderer,40,251, 255, 226);
      SDL_RenderCopy(pRenderer,txt,NULL,&muterect);
      SDL_RenderPresent(pRenderer);
    //dessinner la matrice pleine
                for(int i=290;i<891;i=i+103){
                    for(int j=250;j<851;j=j+103){
    //coordonees
    rectangle2.x = i;
    rectangle2.y = j;
    //largeur
    rectangle2.w=100;
    //hauteur
    rectangle2.h=100;

    if(SDL_SetRenderDrawColor(pRenderer,251, 255, 226,SDL_ALPHA_OPAQUE)!=0){
         SDL_ExitWithError("impossible de de changer la couleur du rendu");
    }
    if(SDL_RenderFillRect(pRenderer,&rectangle2)!=0){
        SDL_ExitWithError("impossible de dessiner un rectangle");
    }
    SDL_RenderPresent(pRenderer);
    }
    }
    /*------------------------------------------------------------*/
    int j=0;
      for (int n=240;n<941;n=n+103)
        {
         int i=0;
        for (int c=200;c<901;c=c+103)
        {
         int cx=n+33;
         int cy=c+37;
          SDL_SetRenderDrawColor(pRenderer,0,0,0,99);
          nbr(pRenderer,cx,cy,num[i][j],0,0,0,28,28);
         i++;
        }
         j++;
        }
        //---------afficher les ligne
    //
    SDL_Event event;
    bool quit = false;
    char result[50];
    SDL_Texture *tme;
    int mute=0;
    //jouer la music
    affichevecteur(k);
   Mix_PlayMusic(music,-1);
     while(quit==false &&p  == 0){

           currentTime = SDL_GetTicks();
      if ((currentTime > lastTime + 1000 && (currentTime/1000)%1 == 0) && chkoukou==2 &&verifie(num)!=true  ) {
         sprintf(result,"score:%d♠time:%03d",score,temps);
         SDL_SetRenderDrawColor(pRenderer,40, 174, 204, 255);
         SDL_RenderFillRect(pRenderer,&timerrect);
         tme=loadttf(result,pRenderer,40,251, 255, 226);
         SDL_RenderCopy(pRenderer,tme,NULL,&timerrect);
         SDL_RenderPresent(pRenderer);
         tme=NULL;
         temps--;
         score-=3;
         lastTime = currentTime;
      }

             while(SDL_PollEvent(&event))
        {

            switch(event.type){
              case SDL_QUIT:
                  Mix_CloseAudio();
                   SDL_DestroyWindow(window);
                  partie();
                quit = true;
                break;
             case SDL_MOUSEBUTTONUP:

                x1=event.motion.x;
                y1=event.motion.y;
             printf("%d %d \n",x1,y1);
             //pause
             if((x1>=0 && x1<=80)&&(y1>=0 && y1<=80)){
                F2=fopen("C:/vec.bin","wb");
            for(int i=0;i<36;i++){
            fwrite(&k[i],sizeof(int),1,F2);
        }
        fclose(F2);
        player.score=score;
        player.temps=temps;
        strcpy(player.nom,nom);
        F2=fopen("C:/player.bin","wb");
        fwrite(&player,sizeof(saved),1,F2);
        fclose(F2);
          TTF_Quit();
          Mix_FreeMusic(music);
          SDL_DestroyWindow(window);
          SDL_Quit();
          partie();
             }
               if((x1>=100 && x1<=200)&&(y1>=0 && y1<=100)){
               chkoukou=-1;
               Mix_PauseMusic();
                     SDL_HideWindow(window);
                     q=paused(score,p,window,chkoukou);
                     if(q==2){
                        chkoukou=2;
                        Mix_ResumeMusic();
                      }
                      if(q==1){

                        TTF_Quit();
                        Mix_FreeMusic(music);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        game();
                      }
                      if(q==0){
                       TTF_Quit();
                       Mix_FreeMusic(music);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        partie();
                      }
                     }
                     if(((x1>=1000&&x1<=1100)&&(y1>=0 && y1<=100))){
                                 if(mute%2==0){
                                    printf("%d",mute);
                                Mix_PauseMusic();
                                SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                                SDL_RenderDrawLine(pRenderer,1000,0,1100,100);
                                SDL_RenderDrawLine(pRenderer,1100,0,1000,100);
                                 }
                                  if(mute%2==1){
                                    printf("%d",mute);
                                Mix_ResumeMusic();
                                SDL_SetRenderDrawColor(pRenderer,40, 174, 204,225);
                                SDL_RenderDrawLine(pRenderer,1000,0,1100,100);
                                SDL_RenderDrawLine(pRenderer,1100,0,1000,100);
                                txt=loadttf("mute",pRenderer,40,251, 255, 226);
                                SDL_RenderCopy(pRenderer,txt,NULL,&muterect);
                                SDL_RenderPresent(pRenderer);
                            }
                            mute++;
                     }

             //premiere ligne
             //bouton 1 1
             if((x1>=290 && x1<=390)&&(y1>=250 && y1<=350)){
                if(k[0]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,290 , 100 + 250 ,100 + 290 , 250);
                      num[0][1]--;num[1][0]--;


                }
                if(k[0]%3==1)
            {
                SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,290 , 100 + 250 ,100 + 290 , 250);
                   num[0][1]++;num[1][0]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 290 , 250,100+ 290 ,100 + 250);
                    num[0][0]--;num[1][1]--;

            }
            if(k[0]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,290 , 250,100+ 290 ,100 + 250);
                    num[0][0]++;num[1][1]++;

            }
                   k[0]=k[0]+1;
                }
                //bouton 1 2----
                 if((x1>=393 && x1<=493)&&(y1>=250 && y1<=350)){
                if(k[1]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,393 , 100 + 250 ,100 + 393 , 250);
                      num[0][2]--;num[1][1]--;

                }
                if(k[1]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,393 , 100 + 250 ,100 + 393 , 250);
                   num[0][2]++;num[1][1]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 393 , 250,100+ 393 ,100 + 250);
                    num[0][1]--;num[1][2]--;

            }
            if(k[1]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,393 , 250,100+ 393 ,100 + 250);
                    num[0][1]++;num[1][2]++;


            }
                   k[1]=k[1]+1;
                }
                //boutton 1 3----
                if((x1>=496 && x1<=596)&&(y1>=250 && y1<=350)){
                if(k[2]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,496 , 100 + 250 ,100 + 496 , 250);
                      num[0][3]--;num[1][2]--;

                }
                if(k[2]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,496 , 100 + 250 ,100 + 496 , 250);
                   num[0][3]++;num[1][2]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 496 , 250,100+ 496 ,100 + 250);
                    num[0][2]--;num[1][3]--;

            }
            if(k[2]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,496 , 250,100+ 496 ,100 + 250);
                   num[0][2]++;num[1][3]++;

            }
                   k[2]=k[2]+1;
                }
                //boutton 1 4----
                if((x1>=599 && x1<=699)&&(y1>=250 && y1<=350)){
                if(k[3]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,599 , 100 + 250 ,100 + 599 , 250);
                      num[0][4]--;num[1][3]--;

                }
                if(k[3]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,599 , 100 + 250 ,100 + 599 , 250);
                   num[0][4]++;num[1][3]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 599 , 250,100+ 599 ,100 + 250);
                    num[0][3]--;num[1][4]--;


            }
            if(k[3]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,599 , 250,100+ 599 ,100 + 250);
                   num[0][3]++;num[1][4]++;

            }
                   k[3]=k[3]+1;
                }
                //bouton 1 5
                 if((x1>=702 && x1<=802)&&(y1>=250 && y1<=350)){
                if(k[4]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,702 , 100 + 250 ,100 + 702 , 250);
                      num[0][5]--;num[1][4]--;

                }
                if(k[4]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,702 , 100 + 250 ,100 + 702 , 250);
                   num[0][5]++;num[1][4]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 702 , 250,100+ 702 ,100 + 250);
                    num[0][4]--;num[1][5]--;

            }
            if(k[4]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,702 , 250,100+ 702 ,100 + 250);
                   num[0][4]++;num[1][5]++;

            }
                   k[4]=k[4]+1;
                }
                //boutton 1 6
                 if((x1>=805 && x1<=905)&&(y1>=250 && y1<=350)){
                if(k[5]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,805 , 100 + 250 ,100 + 805 , 250);
                      num[0][6]--;num[1][5]--;

                }
                if(k[5]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,805 , 100 + 250 ,100 + 805 , 250);
                   num[0][6]++;num[1][5]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 805 , 250,100+ 805 ,100 + 250);
                    num[0][5]--;num[1][6]--;

            }
            if(k[5]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,805 , 250,100+ 805 ,100 + 250);
                   num[0][5]++;num[1][6]++;

            }
                   k[5]=k[5]+1;
                }
                //---fin 1ere ligne
            //deuxieme ligne
            //boutton 2 1
               if((x1>=290 && x1<=390)&&(y1>=353 && y1<=453)){
                if(k[6]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,290 , 100 + 353 ,100 + 290 , 353);
                      num[1][1]--;num[2][0]--;

                }
                if(k[6]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,290 , 100 + 353 ,100 + 290, 353);
                   num[1][1]++;num[2][0]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 290 , 353,100+ 290 ,100 + 353);
                    num[1][0]--;num[2][1]--;

            }
            if(k[6]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,290 , 353,100+ 290 ,100 + 353);
                    num[1][0]++;num[2][1]++;

            }
                   k[6]=k[6]+1;
                }
                //boutton 2 2
                if((x1>=393 && x1<=493)&&(y1>=353 && y1<=453)){
                if(k[7]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,393 , 100 + 353 ,100 + 393 , 353);
                      num[1][2]--;num[2][1]--;

                }
                if(k[7]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,393 , 100 + 353 ,100 + 393, 353);
                   num[1][2]++;num[2][1]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 393 , 353,100+ 393 ,100 + 353);
                    num[1][1]--;num[2][2]--;

            }
            if(k[7]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,393 , 353,100+ 393 ,100 + 353);
                    num[1][1]++;num[2][2]++;

            }
                   k[7]=k[7]+1;
                }
                //boutton 2 3
                if((x1>=496 && x1<=596)&&(y1>=353 && y1<=453)){
                if(k[8]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,496 , 100 + 353 ,100 + 496 , 353);
                      num[1][3]--;num[2][2]--;

                }
                if(k[8]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,496 , 100 + 353 ,100 + 496, 353);
                   num[1][3]++;num[2][2]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 496 , 353,100+ 496 ,100 + 353);
                    num[1][2]--;num[2][3]--;

            }
            if(k[8]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,496 , 353,100+ 496 ,100 + 353);
                    num[1][2]++;num[2][3]++;

            }
                   k[8]=k[8]+1;
                }
               //boutton 2 4
                if((x1>=599 && x1<=699)&&(y1>=353 && y1<=453)){
                if(k[9]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,599 , 100 + 353 ,100 + 599 , 353);
                      num[1][4]--;num[2][3]--;

                }
                if(k[9]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,599 , 100 + 353 ,100 + 599, 353);
                   num[1][4]++;num[2][3]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 599 , 353,100+ 599 ,100 + 353);
                    num[1][3]--;num[2][4]--;

            }
            if(k[9]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,599 , 353,100+ 599 ,100 + 353);
                    num[1][3]++;num[2][4]++;

            }
                   k[9]=k[9]+1;
                }
                //boutton 2 5
                if((x1>=702 && x1<=802)&&(y1>=353 && y1<=453)){
                if(k[10]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,702 , 100 + 353 ,100 + 702 , 353);
                      num[1][5]--;num[2][4]--;

                }
                if(k[10]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,702 , 100 + 353 ,100 + 702, 353);
                   num[1][5]++;num[2][4]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 702 , 353,100+702 ,100 + 353);
                    num[1][4]--;num[2][5]--;

            }
            if(k[10]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,702 , 353,100+702 ,100 + 353);
                    num[1][4]++;num[2][5]++;

            }
                   k[10]=k[10]+1;
                }
                //boutton 2 6
                if((x1>=805 && x1<=905)&&(y1>=353 && y1<=453)){
                if(k[11]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,805 , 100 + 353 ,100 + 805 , 353);
                      num[1][6]--;num[2][5]--;

                }
                if(k[11]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,805 , 100 + 353 ,100 + 805, 353);
                   num[1][6]++;num[2][5]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 805 , 353,100+805 ,100 + 353);
                    num[1][5]--;num[2][6]--;

            }
            if(k[11]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,805 , 353,100+805 ,100 + 353);
                    num[1][5]++;num[2][6]++;

            }
                   k[11]=k[11]+1;
                }
                 //---fin 2eme ligne
                 //3eme ligne
                 //boutton 3 1
                 if((x1>=290 && x1<=390)&&(y1>=456 && y1<=556)){
                if(k[12]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,290 , 100 + 456 ,100 + 290 , 456);
                      num[2][1]--;num[3][0]--;

                }
                if(k[12]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,290 , 100 + 456 ,100 + 290, 456);
                   num[2][1]++;num[3][0]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 290 , 456,100+ 290 ,100 + 456);
                    num[2][0]--;num[3][1]--;

            }
            if(k[12]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,290 , 456,100+ 290 ,100 + 456);
                    num[2][0]++;num[3][1]++;

            }
                   k[12]=k[12]+1;
                }
                //boutton  3 2
                 if((x1>=393 && x1<=493)&&(y1>=456 && y1<=556)){
                if(k[13]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,393 , 100 + 456 ,100 + 393 , 456);
                      num[2][2]--;num[3][1]--;

                }
                if(k[13]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,393 , 100 + 456 ,100 + 393, 456);
                   num[2][2]++;num[3][1]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 393 , 456,100+ 393 ,100 + 456);
                    num[2][1]--;num[3][2]--;

            }
            if(k[13]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,393 , 456,100+393 ,100 + 456);
                    num[2][1]++;num[3][2]++;

            }
                   k[13]=k[13]+1;
                }
                //boutton  3 3
                 if((x1>=496 && x1<=596)&&(y1>=456 && y1<=556)){
                if(k[14]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,496 , 100 + 456 ,100 + 496 , 456);
                      num[2][3]--;num[3][2]--;

                }
                if(k[14]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,496 , 100 + 456 ,100 + 496, 456);
                   num[2][3]++;num[3][2]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 496 , 456,100+ 496 ,100 + 456);
                    num[2][2]--;num[3][3]--;

            }
            if(k[14]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,496, 456,100+496 ,100 + 456);
                    num[2][2]++;num[3][3]++;

            }
                   k[14]=k[14]+1;
                }
              //bouton 3 4
                 if((x1>=599 && x1<=699)&&(y1>=456 && y1<=556)){
                if(k[15]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,599 , 100 + 456 ,100 + 599 , 456);
                      num[2][4]--;num[3][3]--;

                }
                if(k[15]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,599 , 100 + 456 ,100 + 599, 456);
                   num[2][4]++;num[3][3]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 599 , 456,100+ 599 ,100 + 456);
                    num[2][3]--;num[3][4]--;

            }
            if(k[15]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,599 , 456,100+599 ,100 + 456);
                    num[2][3]++;num[3][4]++;

            }
                   k[15]=k[15]+1;
                }
              //bouton 3 5
                 if((x1>=702 && x1<=802)&&(y1>=456 && y1<=556)){
                if(k[16]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,702 , 100 + 456 ,100 + 702 , 456);
                      num[2][5]--;num[3][4]--;

                }
                if(k[16]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,702 , 100 + 456 ,100 + 702, 456);
                   num[2][5]++;num[3][4]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 702 , 456,100+ 702 ,100 + 456);
                    num[2][4]--;num[3][5]--;

            }
            if(k[16]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,702 , 456,100+702 ,100 + 456);
                    num[2][4]++;num[3][5]++;

            }
                   k[16]=k[16]+1;
                }
                //bouton 3 6
                 if((x1>=805 && x1<=905)&&(y1>=456 && y1<=556)){
                if(k[17]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,805 , 100 + 456 ,100 + 805 , 456);
                      num[2][6]--;num[3][5]--;

                }
                if(k[17]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,805 , 100 + 456 ,100 + 805, 456);
                   num[2][6]++;num[3][5]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 805 , 456,100+ 805 ,100 + 456);
                    num[2][5]--;num[3][6]--;

            }
            if(k[17]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,805 , 456,100+805 ,100 + 456);
                    num[2][5]++;num[3][6]++;

            }
                   k[17]=k[17]+1;
                }
                //fin de la  3em ligne
                //debut 4eme ligne
                //boutton 4 1
                        if((x1>=290 && x1<=390)&&(y1>=559 && y1<=659)){
                if(k[18]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,290 , 100 + 559 ,100 + 290 , 559);
                      num[3][1]--;num[4][0]--;

                }
                if(k[18]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,290 , 100 + 559 ,100 + 290, 559);
                   num[3][1]++;num[4][0]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 290 , 559,100+ 290 ,100 + 559);
                    num[3][0]--;num[4][1]--;

            }
            if(k[18]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,290 , 559,100+ 290 ,100 + 559);
                    num[3][0]++;num[4][1]++;


            }
                   k[18]=k[18]+1;
                }


                //boutton 4 2
                 if((x1>=393 && x1<=493)&&(y1>=559 && y1<=659)){
                if(k[19]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,393 , 100 + 559 ,100 + 393 , 559);
                      num[3][2]--;num[4][1]--;


                }
                if(k[19]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,393 , 100 + 559 ,100 + 393, 559);
                   num[3][2]++;num[4][1]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 393 , 559,100+ 393 ,100 + 559);
                    num[3][1]--;num[4][2]--;



            }
            if(k[19]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,393 , 559,100+ 393 ,100 + 559);
                    num[3][1]++;num[4][2]++;


            }
                   k[19]=k[19]+1;
                }
                //boutton 4 3
                if((x1>=496 && x1<=596)&&(y1>=559 && y1<=659)){
                if(k[20]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,496 , 100 + 559 ,100 + 496 , 559);
                      num[3][3]--;num[4][2]--;


                }
                if(k[20]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,496 , 100 + 559 ,100 + 496, 559);
                   num[3][3]++;num[4][2]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 496 , 559,100+ 496 ,100 + 559);
                    num[3][2]--;num[4][3]--;



            }
            if(k[20]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,496 , 559,100+ 496 ,100 + 559);
                    num[3][2]++;num[4][3]++;


            }
                   k[20]=k[20]+1;
                }
                //boutton 4 4
                if((x1>=599 && x1<=699)&&(y1>=559 && y1<=659)){
                if(k[21]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,599 , 100 + 559 ,100 + 599 , 559);
                      num[3][4]--;num[4][3]--;


                }
                if(k[21]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,599 , 100 + 559 ,100 + 599, 559);
                   num[3][4]++;num[4][3]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 599 , 559,100+ 599 ,100 + 559);
                    num[3][3]--;num[4][4]--;



            }
            if(k[21]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,599 , 559,100+ 599 ,100 + 559);
                    num[3][3]++;num[4][4]++;


            }
                   k[21]=k[21]+1;
                }
                //boutton 4 5
                if((x1>=702 && x1<=802)&&(y1>=559 && y1<=659)){
                if(k[22]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,702 , 100 + 559 ,100 + 702 , 559);
                      num[3][5]--;num[4][4]--;


                }
                if(k[22]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,702 , 100 + 559 ,100+702, 559);
                   num[3][5]++;num[4][4]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 702 , 559,100+702 ,100 + 559);
                    num[3][4]--;num[4][5]--;


            }
            if(k[22]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,702 , 559,100+702 ,100 + 559);
                    num[3][4]++;num[4][5]++;


            }
                   k[22]=k[22]+1;
                }
                //boutton 4 6
                 if((x1>=805 && x1<=905)&&(y1>=559 && y1<=659)){
                if(k[23]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,805 , 100 + 559 ,100 + 805 , 559);
                      num[3][6]--;num[4][5]--;


                }
                if(k[23]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,805 , 100 + 559 ,100+805, 559);
                   num[3][6]++;num[4][5]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 805 , 559,100+805 ,100 + 559);
                    num[3][5]--;num[4][6]--;



            }
            if(k[23]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,805 , 559,100+805 ,100 + 559);
                    num[3][5]++;num[4][6]++;


            }
                   k[23]=k[23]+1;
                }
               //---fin 4eme ligne
               //debut 5eme ligne
               //boutton 5 1
               if((x1>=290 && x1<=390)&&(y1>=662 && y1<=762)){
                if(k[24]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,290 , 100 + 662 ,100 + 290 , 662);
                      num[4][1]--;num[5][0]--;


                }
                if(k[24]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,290 , 100 + 662 ,100 + 290, 662);
                   num[4][1]++;num[5][0]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 290 , 662,100+ 290 ,100 + 662);
                    num[4][0]--;num[5][1]--;



            }
            if(k[24]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,290 , 662,100+ 290 ,100 + 662);
                    num[4][0]++;num[5][1]++;


            }
                   k[24]=k[24]+1;
                }
                //boutton 5 2
                if((x1>=393 && x1<=493)&&(y1>=662 && y1<=762)){
                if(k[25]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,393 , 100 + 662 ,100 + 393 , 662);
                      num[4][2]--;num[5][1]--;


                }
                if(k[25]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,393 , 100 + 662 ,100 + 393, 662);
                   num[4][2]++;num[5][1]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 393 , 662,100+ 393 ,100 + 662);
                    num[4][1]--;num[5][2]--;


            }
            if(k[25]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,393 , 662,100+ 393 ,100 + 662);
                    num[4][1]++;num[5][2]++;


            }
                   k[25]=k[25]+1;
                }
              //boutton 5 3
              if((x1>=496 && x1<=596)&&(y1>=662 && y1<=762)){
                if(k[26]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,496 , 100 + 662 ,100 + 496 , 662);
                      num[4][3]--;num[5][2]--;

                }
                if(k[26]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,496 , 100 + 662 ,100 + 496, 662);
                   num[4][3]++;num[5][2]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 496 , 662,100+ 496 ,100 + 662);
                    num[4][2]--;num[5][3]--;

            }
            if(k[26]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,496 , 662,100+ 496 ,100 + 662);
                    num[4][2]++;num[5][3]++;

            }
                   k[26]=k[26]+1;
                }
                //boutton 5 4
                if((x1>=599 && x1<=699)&&(y1>=662 && y1<=762)){
                if(k[27]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,599 , 100 + 662 ,100 + 599 , 662);
                      num[4][4]--;num[5][3]--;

                }
                if(k[27]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,599 , 100 + 662 ,100 + 599, 662);
                   num[4][4]++;num[5][3]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 599 , 662,100+ 599 ,100 + 662);
                    num[4][3]--;num[5][4]--;

            }
            if(k[27]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,599 , 662,100+ 599 ,100 + 662);
                    num[4][3]++;num[5][4]++;

            }
                   k[27]=k[27]+1;
                }
                //boutton  5 5
                if((x1>=702 && x1<=802)&&(y1>=662 && y1<=762)){
                if(k[28]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,702 , 100 + 662 ,100 + 702 , 662);
                      num[4][5]--;num[5][4]--;

                }
                if(k[28]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,702 , 100 + 662 ,100 + 702, 662);
                   num[4][5]++;num[5][4]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 702 , 662,100+ 702 ,100 + 662);
                    num[4][4]--;num[5][5]--;

            }
            if(k[28]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,702 , 662,100+ 702 ,100 + 662);
                    num[4][4]++;num[5][5]++;

            }
                   k[28]=k[28]+1;
                }
                //boutton 5 6
                if((x1>=805 && x1<=905)&&(y1>=662 && y1<=762)){
                if(k[29]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,805 , 100 + 662 ,100 + 805 , 662);
                      num[4][6]--;num[5][5]--;

                }
                if(k[29]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,805 , 100 + 662 ,100 + 805, 662);
                   num[4][6]++;num[5][5]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 805 , 662,100+ 805 ,100 + 662);
                    num[4][5]--;num[5][6]--;

            }
            if(k[29]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,805 , 662,100+ 805 ,100 + 662);
                    num[4][5]++;num[5][6]++;

            }
                   k[29]=k[29]+1;
                }
                //--fin ligne 5
                //---debut ligne 6
                //bouton 6 1
                if((x1>=290 && x1<=390)&&(y1>=765 && y1<=865)){
                if(k[30]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,290 , 100 + 765 ,100 + 290 , 765);
                      num[5][1]--;num[6][0]--;

                }
                if(k[30]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,290 , 100 + 765 ,100 + 290, 765);
                   num[5][1]++;num[6][0]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 290 , 765,100+ 290 ,100 + 765);
                    num[5][0]--;num[6][1]--;

            }
            if(k[30]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,290 , 765,100+ 290 ,100 + 765);
                    num[5][0]++;num[6][1]++;

            }
                   k[30]=k[30]+1;
                }
                //--fin boutton 6 1
                // bouton 6 2
                 if((x1>=393 && x1<=493)&&(y1>=765 && y1<=865)){
                if(k[31]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,393 , 100 + 765 ,100 + 393 , 765);
                      num[5][2]--;num[6][1]--;

                }
                if(k[31]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,393 , 100 + 765 ,100 + 393, 765);
                   num[5][2]++;num[6][1]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 393 , 765,100+ 393 ,100 + 765);
                    num[5][1]--;num[6][2]--;

            }
            if(k[31]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,393 , 765,100+ 393 ,100 + 765);
                    num[5][1]++;num[6][2]++;

            }
                   k[31]=k[31]+1;
                }
                //--fin boutton 6 2
                //--bouton 6 3
                if((x1>=496 && x1<=596)&&(y1>=765 && y1<=865)){
                if(k[32]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,496 , 100 + 765 ,100 + 496 , 765);
                      num[5][3]--;num[6][2]--;

                }
                if(k[32]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,496 , 100 + 765 ,100 + 496, 765);
                   num[5][3]++;num[6][2]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 496 , 765,100+ 496 ,100 + 765);
                    num[5][2]--;num[6][3]--;

            }
            if(k[32]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,496 , 765,100+ 496 ,100 + 765);
                    num[5][2]++;num[6][3]++;

            }
                   k[32]=k[32]+1;
                }
                //--fin boutton 6 3
                //boutton 6 4
                 if((x1>=599 && x1<=699)&&(y1>=765 && y1<=865)){
                if(k[33]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,599 , 100 + 765 ,100 + 599 , 765);
                      num[5][4]--;num[6][3]--;

                }
                if(k[33]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,599 , 100 + 765 ,100 + 599, 765);
                   num[5][4]++;num[6][3]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 599 , 765,100+ 599 ,100 + 765);
                    num[5][3]--;num[6][4]--;

            }
            if(k[33]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,599 , 765,100+ 599 ,100 + 765);
                    num[5][3]++;num[6][4]++;

            }
                   k[33]=k[33]+1;
                }
                //--fin boutton 6 4
                //boutton 6 5
                if((x1>=702 && x1<=802)&&(y1>=765 && y1<=865)){
                if(k[34]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,702,100 + 765,100 + 702 , 765);
                      num[5][5]--;num[6][4]--;

                }
                if(k[34]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,702 , 100 + 765 ,100 + 702, 765);
                   num[5][5]++;num[6][4]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 702 , 765,100+ 702 ,100 + 765);
                    num[5][4]--;num[6][5]--;

            }
            if(k[34]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,702 , 765,100+ 702 ,100 + 765);
                    num[5][4]++;num[6][5]++;

            }
                   k[34]=k[34]+1;
                }
                //--fin boutton 6 5
                //boutton 6 6
                if((x1>=805 && x1<=905)&&(y1>=765 && y1<=865)){
                if(k[35]%3==0){
                     SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                     SDL_RenderDrawLine(pRenderer,805 , 100 + 765 ,100 + 805 , 765);
                      num[5][6]--;num[6][5]--;

                }
                if(k[35]%3==1)
            {SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                   SDL_RenderDrawLine(pRenderer,805 , 100 + 765 ,100 + 805, 765);
                   num[5][6]++;num[6][5]++;
                   SDL_SetRenderDrawColor(pRenderer,0,0,0,225);
                 SDL_RenderDrawLine(pRenderer, 805 , 765,100+ 805 ,100 + 765);
                    num[5][5]--;num[6][6]--;

            }
            if(k[35]%3==2){
                    SDL_SetRenderDrawColor(pRenderer,251, 255, 226,225);
                    SDL_RenderDrawLine(pRenderer,805 , 765,100+ 805 ,100 + 765);
                    num[5][5]++;num[6][6]++;

            }
                   k[35]=k[35]+1;
                }
                SDL_RenderPresent(pRenderer);
                //fin ligne 6
                break;
            }
        }



       if(verifie(num)){
          wintxt=loadttf("GG!",pRenderer,200,0,0,0);
          SDL_RenderCopy(pRenderer,wintxt,NULL,&winrect);
          SDL_RenderPresent(pRenderer);
          SDL_Delay(300);
          TTF_Quit();
          fiche(nom,score,1);
          Mix_FreeMusic(music);
          SDL_DestroyWindow(window);
          SDL_Quit();
          int p=0;
          Win(score,0);


       }
       if(temps == 0 && verifie(num)==false ){
             wintxt=loadttf("U lost !",pRenderer,200,0,0,0);
          SDL_RenderCopy(pRenderer,wintxt,NULL,&winrect);
          SDL_RenderPresent(pRenderer);
        SDL_Delay(300);
        TTF_Quit();
         fiche(nom,score,1);
        Mix_FreeMusic(music);
        SDL_DestroyWindow(window);
        SDL_Quit();
        Lost(score,0);
       }
    }
     //-----------
    TTF_Quit();
    Mix_FreeMusic(music);
    SDL_DestroyWindow(window);

    return p;
}



