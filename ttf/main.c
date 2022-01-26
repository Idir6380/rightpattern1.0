#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "game.h"
#include "cpu.h"
#include "pvsc.h"
#include "saveppart.h"
#include "save2.h"
void partie(){
  switch (menu()){
  case 1 :game();
  break;
  case 2:save();
  break;
  case 3:cpu();
  break;
  case 4:pvsc();
  break;
  case 5:save2();
  break;
  case 6:Score();
  break;
  }
}
int main(int argc, char *argv[]){

    partie();

return 0;
}
