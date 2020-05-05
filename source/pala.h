#include <iostream>
#include "objeto.h"

using namespace std;

class Pala: public Objeto
{
public:
  Pala() = default;
  Pala(int x, int y, int w, int h): Objeto(new Pair<> {x,y}, new Pair<> {w,h}){};
  ~Pala();
};
