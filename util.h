// Helper functions for better encapsulation.

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <SDL.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Swarm.h"
#include "Screen.h"

using namespace std;


int startSDL() {

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {

    cout << "Failed to initialize SDL. Exiting program..." << endl;
    return -1;
  }

  
  srand(time(NULL)); // Seed the RNG.
  return 0;
}


bool endProgram() {

  SDL_Event event;
  
  while(SDL_PollEvent(&event)) {

    if(event.type == SDL_QUIT) { return true; }
  }

  return false;
}


void modifyPixelColor(Uint8& r, Uint8& g, Uint8& b, int t0) {
  // Updates color of particles in swarm.

  float df = 0.0003; // Dampening term.

  r = (sin(1*t0*df) + 1)*128;
  b = (sin(2*t0*df) + 1)*128;
  g = (sin(3*t0*df) + 1)*128;
}


void switchToPixelSpace(int& i, int& x, int& y, Screen& window, Swarm& swarm) {
  // Converts coords of Particle space to SDL pixel screen coords. 

  x = (swarm.get_Xcoords()[i] + 1)*window.getScreenWidth() / 2;
      
  y = (swarm.get_Ycoords()[i] + 1)*window.getScreenWidth() / 2;
  y -= window.getScreenWidth() / 2; y += window.getScreenHeight() / 2;
}


#endif
