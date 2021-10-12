#include "mandelbrot_classes.h"

#define width 800
#define height 800
#define window_x 100
#define window_y 100

void redraw(struct Display*);

int main(){

  //making screen
  SDL_Rect windowrect = {window_x, window_y, width, height};
  SDL_MANAGER manager = SDL_MANAGER(&windowrect);


  manager.init("mandelbrot");
  manager.setDrawMethod(redraw);

  //starting loop

  bool quit = false;
  SDL_Event e;
  struct Display* display = manager.getDisplay();

  while(!quit){

    SDL_PollEvent(&e);

    switch(e.type){

      case  SDL_QUIT:
                    quit = true;
                    break;
    }

    manager.draw();
  }

  manager.deinit();

  return 0;
}

void redraw(struct Display* display){

  SDL_Renderer* r = display->renderer;
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderPresent(r);

}
