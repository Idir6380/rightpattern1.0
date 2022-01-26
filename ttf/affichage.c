#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_ttf.h>
void affichevecteur(int k[]){
  for(int i = 0;i<36;i++){
        printf("%d \t",k[i]);
    }
     printf("\n");
}
void affichmat(int mat[7][7]){
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            printf("%d",mat[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}
