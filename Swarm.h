// Swarm class for managing collections of particles.

#ifndef SWARM_H_
#define SWARM_H_

#include <iostream>
#include <math.h>
#include <stdlib.h>

class Swarm {

private:
  int np; // Number of particles to initialize in swarm.

  float* px;
  float* py;

  float* polarAngle;
  float* radialSpeed;

  float speedDampFactor = 0.1;
  float rotationSpeed = 0.02;

  
  void initPolarCoords(int i) {
    // Randomly initialize particle's polar angle + radial speed. 

    polarAngle[i] = 2.0*M_PI*rand() / RAND_MAX;
      
    radialSpeed[i] = speedDampFactor*rand() / RAND_MAX;
    radialSpeed[i] *= radialSpeed[i];
  }

  
public:
  const int getNumParticles() { return np; }
  
  const float* get_Xcoords() { return px; }
  const float* get_Ycoords() { return py; }

  
  Swarm(int np):np(np) {

    
    px = new float[np]; memset(px, 0.0, np*4);
    py = new float[np]; memset(py, 0.0, np*4);

    polarAngle = new float[np];
    radialSpeed = new float[np];

    for(int i=0; i<np; i++) { initPolarCoords(i); }
  }


  void moveAllParticles() {

    float dx,dy;

    for(int i=0; i<np; i++) {

      polarAngle[i] += rotationSpeed;

      dx = radialSpeed[i]*cos(polarAngle[i]);
      dy = radialSpeed[i]*sin(polarAngle[i]);

      px[i] += dx;
      py[i] += dy;

      
      // Prevent rendering of edge pixels + reset to center. 
      if(px[i] < -1.0 || px[i] > 1.0 || py[i] < -1.0 || py[i] > 1.0) {

	px[i] = 0.0;
	py[i] = 0.0;
	
	initPolarCoords(i);
      }

      else if(rand()*1.0 < RAND_MAX*1.0 / 100000) {

	initPolarCoords(i);
      }
    }
  }

  
  ~Swarm() {

    delete [] px;
    delete [] py;

    delete [] polarAngle;
    delete [] radialSpeed;
  }
};

#endif
