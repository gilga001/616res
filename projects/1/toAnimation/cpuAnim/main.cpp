// Brian Malloy, Object Technology with C++
// Example of a simple animation with SDL

#include <SDL.h>
#include <iostream>
#include <string>
#include "generateFrames.h"

const unsigned int WIDTH = 854;
const int unsigned HEIGHT = 480;

const float START_X = 40.0;
const float START_Y = 350.0;
const float INCR_X = 0.3;

void init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
  }
  atexit(SDL_Quit);
}

SDL_Surface* getImage(const std::string& filename, bool setColorKey=true) {
  SDL_Surface *temp = SDL_LoadBMP(filename.c_str());
  if (temp == NULL) {
    throw std::string("Unable to load bitmap.")+SDL_GetError();
  }
  if ( setColorKey ) {
    Uint32 colorkey = SDL_MapRGB(temp->format, 255, 0, 255);
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  SDL_Surface *image = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return image;
}

void draw(SDL_Surface* image, SDL_Surface* screen, 
          float x = 0.0, float y = 0.0) {
  Uint16 w = image->w;
  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(x);
  Sint16 yCoord = static_cast<Sint16>(y);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  SDL_BlitSurface(image, &src, screen, &dest);
}

int main() {
  try {
   init();
   SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_DOUBLEBUF);
   if (screen == NULL) {
     throw std::string("Unable to set video mode: ")+SDL_GetError();
   }

  SDL_Surface *sky = getImage("images/sky.bmp");
  SDL_Surface *star = getImage("images/greenball.bmp", true);

  float x = START_X;
  float y = START_Y;
  SDL_Event event;
  bool makeVideo = false;
  bool done = false;
  GenerateFrames genFrames(screen);
  while ( !done) {
    while ( SDL_PollEvent(&event) ) {
      if (event.type == SDL_QUIT) done = true;
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        if (event.key.keysym.sym == SDLK_F4) {
          makeVideo = true;
          std::cout << "Generating frames for video" << std::endl;
        }
      }
    }
    if (makeVideo && genFrames.getFrameCount()<genFrames.getMaxFrames()) {
      genFrames.makeFrame();
    }
    else if (makeVideo ) {
      std::cout << genFrames.getMaxFrames() 
                << " have been generated." 
                << std::endl;
      makeVideo = false;
    }
    if ( x <= 600.0 ) {
      x += INCR_X;
    }
    else {
      makeVideo = false;
    }
    draw(sky, screen);
    draw(star, screen, x, y);
    SDL_Flip(screen);
  }
  SDL_FreeSurface(sky);
  SDL_FreeSurface(star);
  }
  catch(const std::string& msg) { std::cout << msg << std::endl;  }
  catch(...) { std::cout << "oops" << std::endl;  }
  return 0;
}