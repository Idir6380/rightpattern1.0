#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int Lost(int score,int p)
{   int o=0;
    int t[4]={0,1,2,3};
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
   SDL_Surface *menu=NULL;
    // Create a SDL window
    SDL_Window *windowmenu = SDL_CreateWindow("LOOSE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200,900, SDL_WINDOW_MOUSE_FOCUS);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(windowmenu, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(p==1){
    menu=SDL_LoadBMP("CPULost.bmp");
    }else{
    menu=SDL_LoadBMP("Youlost.bmp");
    }

    SDL_Texture *txt=SDL_CreateTextureFromSurface(renderer,menu);
    SDL_RenderCopy(renderer, txt, NULL, NULL);
    char result[50];
    int button= 0;
    bool running = true;
    SDL_Event event;
     SDL_Rect winrect={447,277,300,100};
     sprintf(result,"score:%d",score);
     txt=loadttf(result,renderer,100,255, 255, 255);
      SDL_RenderCopy(renderer,txt,NULL,&winrect);
      SDL_RenderPresent(renderer);
    while(running==true && button == 0 )
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            int x1,y1;

            x1=event.motion.x;
            y1=event.motion.y;


            if(event.type == SDL_QUIT)
            {
                running = false;
                SDL_DestroyWindow(windowmenu);
                SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_Quit();
                partie();
            }
            if(event.type == SDL_MOUSEBUTTONUP &&(event.motion.state & SDL_BUTTON_LEFT))
            {
              printf("%d %d \n",x1,y1);
            }
            if(event.type== SDL_MOUSEBUTTONUP && x1<=558 && x1>=441 && y1<=545 && y1>=465){
                printf("score");
                    SDL_DestroyWindow(windowmenu);
                SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_Quit();
                Score();
            }
               if(event.type== SDL_MOUSEBUTTONUP && x1<=761 && x1>=641 && y1<=549 && y1>=469){
                SDL_DestroyWindow(windowmenu);
                SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_Quit();
                switch(p){
                case 0: game();
                break;
                case 1: cpu();
                break;
                case 2: pvsc();
                break;
                }

            }
             if(event.type== SDL_MOUSEBUTTONUP && x1<=761 && x1>=441 && y1<=650 && y1>=582){
                SDL_DestroyWindow(windowmenu);
                SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_Quit();
                partie();
            }

        }
        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    /* On copie tmp sur
texture */
   SDL_DestroyTexture(txt);
    SDL_FreeSurface(menu);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(windowmenu);
    SDL_Quit();
    return button;
}
