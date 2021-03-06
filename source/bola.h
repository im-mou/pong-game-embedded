#ifndef BOLA_H_
#define BOLA_H_

#include <iostream>
#include <math.h>
#include "../globals.h"
#include "pala.h"

using namespace std;

class Bola
{
public:
  int x, y, w, h;
  float dirx, diry;
  Bola(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
  {
    reset();
  };
  ~Bola(){};
  void update();
  void bordes(int *score);
  void reset();
  void checkPalaLeft(Pala *p);
  void checkPalaRight(Pala *p);
};

void Bola::update()
{
  x += dirx;
  y += diry;
}

void Bola::bordes(int *score)
{
  // condicion para el borde superior y el inferior
  if (y < 1 || y > MAP_HEIGHT - 1)
  {
    diry *= -1;
  }

  // condicion para el borde derecho
  if (x > MAP_WIDTH -1 )
  {
    score[0]++;
    reset();
  }

  // condicion para el borde izquierdo
  if (x < 1)
  {
    score[1]++;
    reset();
  }
}

void Bola::reset()
{
  float r = fmod(rand(), (3.14159 / 4));
  float angulo = ((rand() % 2) + 1) > 1 ? r : -r;
  //float angulo = fmod(rand(), (3.14159 / 4) + (-3.14159 / 4));
  x = MAP_WIDTH / 2;
  y = MAP_HEIGHT / 2;

  //angle = 0;
  dirx = 1 * cos(angulo);
  diry = 1 * sin(angulo);

  // hace que 50% de veces vaya a la der. o a la izq.
  if (((rand() % 2) + 1) > 1)
  {
    dirx *= -1;
  }
}

void Bola::checkPalaLeft(Pala *p)
{
  if (
      y < p->y + p->h &&
      y > p->y - p->h &&
      x < p->x + p->w)
  {
    if (x > p->x)
    {
      float diff = y - (p->y - p->h);
      float rad = 45 * M_PI / 180;
      //float angle = map(diff, 0, p->h, -rad, rad);
      float angle = -rad + (rad - (-rad)) * (diff / p->h);

      dirx = 3 * cos(angle);
      diry = 3 * sin(angle);
      x = p->x + p->w;
      //xspeed *= -1;
    }
  }
}

void Bola::checkPalaRight(Pala *p)
{
  float xpi = M_PI / 180;
  if (y < p->y + p->h &&
      y > p->y - p->h &&
      x > p->x - p->w)
  {
    if (x < p->x)
    {
      //xspeed *= -1;
      float diff = y - (p->y - p->h);
      //float angle = map(diff, 0, p->h, 255 * M_PI / 180, 135 * M_PI / 180);
      float angle = (225 * xpi) + ((135 * xpi) - (225 * xpi)) * (diff / p->h);

      dirx = 3 * cos(angle);
      diry = 3 * sin(angle);
      x = p->x - p->w;
    }
  }
}

#endif