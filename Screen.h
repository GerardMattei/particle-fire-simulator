// Screen class for rendering particle fire animation.

#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <SDL.h>

using namespace std;


class Screen {

private:
  int SCREEN_WIDTH;
  int SCREEN_HEIGHT;

  Uint32* displayBuffer;
  Uint32* boxBlurBuffer;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;

  
public:
  const int getScreenWidth() { return SCREEN_WIDTH; }
  const int getScreenHeight() { return SCREEN_HEIGHT; }

  
  Screen(int w, int h):SCREEN_WIDTH(w),SCREEN_HEIGHT(h) {

    
    // Initialize buffers containing pixel values.
    displayBuffer = new Uint32[w*h]; memset(displayBuffer, 0, w*h*4);
    boxBlurBuffer = new Uint32[w*h]; memset(boxBlurBuffer, 0, w*h*4);

    
    // Initialize SDL window, renderer, and texture. 
    window = SDL_CreateWindow("Particle Fire Simulator",
			      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, w, h);
  }


  void updateScreen() {

    
    SDL_UpdateTexture(texture, NULL, displayBuffer, SCREEN_WIDTH*4);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    boxBlur();
  }


  void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {

    
    if(x >= 0 && x<SCREEN_WIDTH && y >= 0 && y<SCREEN_HEIGHT) {

      Uint32 color = 0;

      color += r; color <<= 8;
      color += g; color <<= 8;
      color += b; color <<= 8;

      color += 0xFF;
      displayBuffer[x + SCREEN_WIDTH*y] = color;
    }
  }


  void boxBlur() {
    // Box blur algorithm to blur previously rendered screen + use
    // as canvas for drawing subsequent frame. 

    Uint32* tempBuffer = displayBuffer;
    displayBuffer = boxBlurBuffer;
    boxBlurBuffer = tempBuffer;

    
    int new_x,new_y;

    Uint8 r,g,b;
    Uint32 color;

    int redTotal,greenTotal,blueTotal;
    
    for(int y=0; y<SCREEN_HEIGHT; y++) {
      for(int x=0; x<SCREEN_WIDTH; x++) {

	redTotal = 0;
	greenTotal = 0;
	blueTotal = 0;
	
	for(int row=-1; row<=1; row++) {
	  for(int col=-1; col<=1; col++) {

	    new_x = x + col;
	    new_y = y + row;

	    if(new_x >= 0 && new_x<SCREEN_WIDTH && new_y >= 0 && new_y<SCREEN_HEIGHT) {

	      color = boxBlurBuffer[new_x + SCREEN_WIDTH*new_y];

	      r = color >> 24; redTotal += r;
	      g = color >> 16; greenTotal += g;
	      b = color >> 8; blueTotal += b;
	    }
	  }
	}

	r = redTotal / 9;
	g = greenTotal / 9;
	b = blueTotal / 9;

	setPixel(x,y,r,g,b);
      }
    }
  }
  
  
  ~Screen() {

    delete [] displayBuffer;
    delete [] boxBlurBuffer;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
  }
};


#endif
