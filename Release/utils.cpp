#include "utils.h"



//LTexture

LTexture::LTexture(){

texture = NULL;
clip = NULL;
position = NULL;

}

LTexture::LTexture(std::string path, SDL_Renderer* render){

  renderer = render;
  setupTexture(path);
  clip = NULL;
  position = NULL;

}

LTexture::LTexture(std::string path, SDL_Renderer* render, SDL_Rect* clip){

  renderer = render;
  setupTexture(path);

  this->clip = clip;
  position = NULL;

}

LTexture::LTexture(std::string path, SDL_Renderer* render, SDL_Rect* clip, SDL_Rect* position){

  renderer = render;
  setupTexture(path);

  this->clip = clip;
  this->position = position;

}

void LTexture::setupTexture(std::string path){

  //loading with a cast
  SDL_Surface* trash = IMG_Load(const_cast<char*>(path.data()));

  //creating surface and destroying
  texture = SDL_CreateTextureFromSurface(renderer, trash);
  SDL_FreeSurface(trash);


}

SDL_Texture* LTexture::getTexture(){

  return texture;

}

void LTexture::changeClip(SDL_Rect* clip){

  this->clip = clip;


}

void LTexture::changePosition(SDL_Rect* position){

  this->position = position;

}


LTexture::~LTexture(){

SDL_DestroyTexture(texture);

}

//SDL_Manager
SDL_MANAGER::SDL_MANAGER(){

//does nothing
windowSize = NULL;
texturecount = 0;

}

SDL_MANAGER::SDL_MANAGER(SDL_Rect* pos){

  windowSize = pos;
  //does nothing
  texturecount = 0;

}

SDL_MANAGER::~SDL_MANAGER(){


}

bool SDL_MANAGER::init(){

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  display.window = SDL_CreateWindow("", windowSize->x, windowSize->y, windowSize->w, windowSize->h, SDL_WINDOW_SHOWN);


  display.renderer = SDL_CreateRenderer(display.window, -1, SDL_RENDERER_ACCELERATED);
  display.screen = SDL_GetWindowSurface(display.window);



  return true;
}

bool SDL_MANAGER::init(std::string name){

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  display.window = SDL_CreateWindow(const_cast<char*>(name.data()), windowSize->x, windowSize->y, windowSize->w, windowSize->h, SDL_WINDOW_SHOWN);


  display.renderer = SDL_CreateRenderer(display.window, -1, SDL_RENDERER_ACCELERATED);
  display.screen = SDL_GetWindowSurface(display.window);



  return true;
}

bool SDL_MANAGER::deinit(){


  std::list<LTexture>::iterator destroyer;

  destroyer = textures.begin();

  while(destroyer != textures.end()){

    (*destroyer).~LTexture();
    destroyer++;
  }



  SDL_DestroyRenderer(display.renderer);
  SDL_FreeSurface(display.screen);

  //delete windowSize;
  SDL_DestroyWindow(display.window);

  //quittinh
  SDL_Quit();
  IMG_Quit();
  return true;
}

void SDL_MANAGER::setDrawMethod(void (*method)(Display*)){

  this->drawmethod = method;

}

void SDL_MANAGER::draw(){

drawmethod(&display);

}

void addTexture(LTexture* texture){

}

bool removeTexture(LTexture* texture){

return true;
}

Display* SDL_MANAGER::getDisplay(){

  return &display;

}

std::list<LTexture>* SDL_MANAGER::getTextures(){

  return &textures;
}
