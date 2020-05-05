#include <iostream>
#include "source/pala.h"

using namespace std;

int main(int argc, const char **argv)
{

  Pala *ai = new Pala(2, 4, 3, 5);

  printf("pala AI\n");
  printf("x:%d\n", ai->getPos()->x);
  printf("y:%d\n", ai->getPos()->y);
  printf("w:%d\n", ai->getDim()->x);
  printf("h:%d\n", ai->getDim()->y);

  return 0;
}