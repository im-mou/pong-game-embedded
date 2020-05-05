#include <iostream>
#include "pair.h"

using namespace std;

class Objeto
{
protected:
  Pair<> *m_dim;
  Pair<> *m_pos;

public:
  Objeto() = default;
  Objeto(Pair<> *pos, Pair<> *dim);
  ~Objeto();

  Pair<> *getPos();
  void setPos(int x, int y);
  Pair<> *getDim();
  void setDim(int w, int h);
};

Objeto::Objeto(Pair<> *pos, Pair<> *dim)
{
  m_dim = dim;
  m_pos = pos;
};

Objeto::~Objeto()
{
  delete m_pos;
  delete m_dim;
};

Pair<> *Objeto::getPos()
{
  return m_pos;
}

Pair<> *Objeto::getDim()
{
  return m_dim;
}

void Objeto::setPos(int x, int y)
{
  m_pos->x = x;
  m_pos->y = y;
}

void Objeto::setDim(int w, int h)
{
  m_pos->x = w;
  m_pos->y = h;
}
