#include "SDL_ALL/utils.h"
#include <iostream>


void d(struct Display* g){

  SDL_Renderer* t = g->renderer;

  SDL_RenderClear(t);
  SDL_SetRenderDrawColor(t, 0xFF, 0x9, 0x8F, 0xFF);
  SDL_RenderPresent(t);

}

int main(){

  SDL_Rect t = {100, 100, 800, 800};
  SDL_MANAGER man(&t);

  man.init("Hallo");

  man.setDrawMethod(d);

  bool quit = false;
  SDL_Event e;

  while(!quit){

    SDL_PollEvent(&e);

    switch(e.type){

      case SDL_QUIT:

      quit = true;
      break;
    }

    man.draw();

  }



  man.deinit();


  return 0;
}
