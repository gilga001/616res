#include <iostream>
#include <sstream>
#include <iomanip>
#include "generateFrames.h"

void GenerateFrames::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << USERNAME << '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  SDL_SaveBMP(screen, filename.c_str());
}

