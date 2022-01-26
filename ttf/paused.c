#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int paused(int score,int p,SDL_Window *window,int chkoukou)
{   int o=0;
    int t[4]={0,1,2,3};
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

    // Create a SDL window
    SDL_Window *windowmenu = SDL_CreateWindow("Pause", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200,900, SDL_WINDOW_MOUSE_FOCUS);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(windowmenu, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface *menu=SDL_LoadBMP("PAUSE.bmp");
    SDL_Texture *txt=SDL_CreateTextureFromSurface(renderer,menu);
    SDL_RenderCopy(renderer, txt, NULL, NULL);
    char result[50];

    bool running = true;
    SDL_Event event;

    while(running==true  )
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            int x1,y1;

            x1=event.motion.x;
            y1=event.motion.y;

            if(event.type == SDL_MOUSEBUTTONUP &&(event.motion.state & SDL_BUTTON_LEFT))
            {
              printf("%d %d \n",x1,y1);
            }
            if(event.type== SDL_MOUSEBUTTONUP && x1<=558 && x1>=441 && y1<=484 && y1>=410){
                printf("reume");
                  SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_ShowWindow(window);
                return 2;


            }
             if(event.type== SDL_MOUSEBUTTONUP && x1<=761 && x1>=641 && y1<=549 && y1>=410){
                SDL_DestroyWindow(windowmenu);
                SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_Quit();
                return 1;
            }
             if(event.type== SDL_MOUSEBUTTONUP && x1<=761 && x1>=441 && y1<=650 && y1>=523){
                SDL_DestroyWindow(windowmenu);
                SDL_DestroyTexture(txt);
                SDL_FreeSurface(menu);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(windowmenu);
                SDL_Quit();
                return 0;
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


}
