#ifndef PALA_H_
#define PALA_H_

#include <iostream>
#include "../globals.h"

using namespace std;

class Pala
{
public:
  int x, y, w, h, speed;
  Pala(int x, int y, int w, int h, int speed) : x(x), y(y), w(w), h(h), speed(speed)
  {
    reset();
  };
  ~Pala();
  void reset();
  void moveUp();
  void moveDown();
  void moveAuto(int bolapos);
};

void Pala::reset()
{
  y = (MAP_HEIGHT / 2) - h / 2;
}

void Pala::moveDown()
{
  if (y > 1)
    y -= speed;
};
void Pala::moveUp()
{
  if (y + h < MAP_HEIGHT)
    y += speed;
};

#endif