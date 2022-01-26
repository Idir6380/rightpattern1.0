#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>
int notfound()
{
    SDL_Window *window = NULL;     // window
    SDL_Renderer *renderer = NULL; // rendere
    SDL_Texture *titre = NULL; //texture
    //rect titre
    SDL_Rect recttitre = {300, 350, 600, 80};
    // Lancement SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    // Création fenêtre et render

    if (SDL_CreateWindowAndRenderer(1200, 900, SDL_WINDOW_RESIZABLE, &window, &renderer) != 0)
    {
        SDL_ExitWithError("Impossible de créer la fenetre");
    }
    SDL_SetWindowTitle(window, "NOT FOUND");

    if (SDL_SetRenderDrawColor(renderer, 4,21,98, SDL_ALPHA_OPAQUE) != 0)
    {
        SDL_ExitWithError("impossible de de changer la couleur du rendu");
    }
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

  //init sdl_ttf
    if(TTF_Init()==-1)
{

    exit(2);
}

     titre = loadttf("PART NOT FOUND", renderer, 100, 218, 18, 18);
     SDL_RenderCopy(renderer,titre, NULL, &recttitre);
     SDL_RenderPresent(renderer);
 bool running=true;
 SDL_Event event;
 while(running==true  )
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
                  TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(titre);

    SDL_Quit();
                partie();
            }

        }
        // Show what was drawn
        SDL_RenderPresent(renderer);
    }
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(titre);

    SDL_Quit();

    return EXIT_SUCCESS;
}
