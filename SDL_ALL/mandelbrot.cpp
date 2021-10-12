#include "mandelbrot_classes.h"

#define width 800
#define height 800
#define window_x 100
#define window_y 100

Field FIELD(width, height, 10);

void redraw(struct Display*);

ColorReg colorreg;

int main(int argc, char** argv){

  //making screen
  SDL_Rect windowrect = {window_x, window_y, width, height};
  SDL_MANAGER manager = SDL_MANAGER(&windowrect);

  int xb, xe, yb, ye;

  xb = (int)argv[1][0] - 48;
  xe = (int)argv[2][0] - 48;
  yb = (int)argv[3][0] - 48;
  ye = (int)argv[4][0] - 48;

  FIELD.xscale.first = (long double)xb;
  std::cout << FIELD.xscale.first << "\n";

  std::cout << xb << "\n";

  manager.init("mandelbrot");
  manager.setDrawMethod(redraw);

  for(int i=0;i<height;i++){
    for(int g = 0;g<width;g++){
      FIELD.setColor(i, g, new Color(255, 0, 0));
    }
  }

  std::cout << (*FIELD.get(1, 3)->first);


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
    FIELD.calculateColors(&colorreg);
  }

  manager.deinit();

  return 0;
}

void redraw(struct Display* display){

  SDL_Renderer* r = display->renderer;
  SDL_RenderClear(r);
  FIELD.draw(r);
  SDL_RenderPresent(r);

}
