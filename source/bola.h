#include <iostream>
#include "pair.h"
#include "objeto.h"

using namespace std;

class Bola : Objeto
{
private:
  Pair<float> *vect;

public:
  Bola(int x, int y, int w, int h)
  {
    Objeto(new Pair<> {x,y}, new Pair<> {w,h});
    vect->x = 1.0;
    vect->y = -1.0;
  };
  ~Bola()
  {
    delete vect;
  };
  bool colision();
};

bool Bola::colision()
{
  return true;
};