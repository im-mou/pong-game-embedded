#ifndef PALA_H_
#define PALA_H_

#include <iostream>
#include "../globals.h"

using namespace std;

class Pala
{
public:
  int x,y,w,h;
  Pala(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
  {
    reset();
  };
  ~Pala();
  void reset();
  void moveUp();
  void moveDown();
};

void Pala::reset()
{
  y = (MAP_HEIGHT / 2) - h/2;
}

void Pala::moveUp(){
  if(y > 1)
    y -= 1; 
};
void Pala::moveDown(){
  if(y + h < MAP_HEIGHT)
    y += 1; 
};

#endif