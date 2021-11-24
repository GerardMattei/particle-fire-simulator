// Particle fire simulator program.
// Compile command:
// g++ *.cpp $(pkg-config --cflags --libs sdl2) -o particle-fire-sim && ./particle-fire-sim

#include <iostream>
#include <SDL.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "Screen.h"
#include "Swarm.h"
#include "util.h"

using namespace std;

  // Update color schema.


int main() {


  startSDL();
  int t0 = SDL_GetTicks();

  Swarm swarm(7500);
  Screen window(800,600);

  int x,y;
  
  Uint8 r = 255.0*rand() / RAND_MAX;
  Uint8 g = 255.0*rand() / RAND_MAX;
  Uint8 b = 255.0*rand() / RAND_MAX;
  

  // Main event loop.
  bool quit = false;
  
  while(!quit) {
    
    t0 = SDL_GetTicks();

    modifyPixelColor(r,g,b,t0);
    swarm.moveAllParticles();

    
    for(int i=0; i<swarm.getNumParticles(); i++) {

      switchToPixelSpace(i,x,y, window, swarm);  
      window.setPixel(x,y,r,g,b);
    }

    window.updateScreen();

    quit = endProgram();
  }
  

  SDL_Quit();
  return 0;
}

