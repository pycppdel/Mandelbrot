#include "mandelbrot_classes.h"

#define width 800
#define height 800
#define window_x 100
#define window_y 100
#define precision 50

Field FIELD(width, height, precision);

void redraw(struct Display*);

ColorReg colorreg;

int main(int argc, char** argv){

  //making screen
  SDL_Rect windowrect = {window_x, window_y, width, height};
  SDL_MANAGER manager = SDL_MANAGER(&windowrect);

  FIELD.setxscale(-2, 2);
  FIELD.setyscale(-2, 2);

  std::cout << FIELD.xscale.first << "\n";


  manager.init("mandelbrot");
  manager.setDrawMethod(redraw);

  for(int i=0;i<height;i++){
    for(int g = 0;g<width;g++){
      FIELD.setColor(i, g, new Color(255, 0, 0));
    }
  }

  int *m_x, *m_y;



  //starting loop

  bool quit = false;
  SDL_Event e;
  struct Display* display = manager.getDisplay();

  std::cout << "E";

  FIELD.calculateColors(&colorreg);

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
  FIELD.draw(r);
  SDL_RenderPresent(r);

}
