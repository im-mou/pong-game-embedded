#include <iostream> // std::cout, std::endl
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds
#include <math.h>
#include "globals.h"
#include "source/bola.h"
#include "source/pala.h"

#include "input.cpp"

using namespace std;

// character of the snake body
int score[] = {0, 0};

bool is_map_border(int x, int y)
{
  return y == 0 || x == 0 || x == MAP_WIDTH || y == MAP_HEIGHT;
}
// checks if the coordinates match the coordinates of food
bool is_bola(Bola *bola, int x, int y)
{
  return bola->x == x && bola->y == y;
}
bool is_pala(Pala *pala, int x, int y)
{
  for (int k = 0; k < pala->h; k++)
  {
    if ((pala->y + k) == y && pala->x == x)
    {
      return true;
    }
  }
  return false;
}


// draws a map and snake
void draw(Bola *bola, Pala *pala_left, Pala *pala_right)
{
  system("clear");

  // draws the map
  for (int i = 0; i <= MAP_HEIGHT; i++)
  {
    for (int j = 0; j <= MAP_WIDTH; j++)
    {

      if (is_map_border(j, i)) // print tablero
      {
        cout << '#' << flush;
      }
      else if (is_bola(bola, j, i)) // print bola
      {
        cout << "O" << flush;
      }
      else if (is_pala(pala_left, j, i) || is_pala(pala_right, j, i)) // print palas
      {
        cout << "|" << flush;
      }
      else if (i == 2) // print scores
      {
        if (j == MAP_WIDTH / 2 - 2)
        {
          cout << score[0];
        }
        else if (j == MAP_WIDTH / 2 + 2)
        {
          cout << score[1];
        } else {
          cout << " ";
        }
        cout << flush;
      }
      else if (j == MAP_WIDTH / 2) // print separador
      {
        cout << "." << flush;
      }
      else
      {
        cout << ' ' << flush;
      }
    }
    cout << "\n";
  }
}

// will be called on 'Esc'
void exit()
{
  input_off();
  printf("\n\n###### GAMEOVER ######\n\n");
}

int main(int argc, const char **argv)
{

  Bola *bola = new Bola(0, 0, 1, 1);
  Pala *pala_left = new Pala(2, 0, 2, 5);
  Pala *pala_right = new Pala(MAP_WIDTH - 2, 0, 2, 5);

  fd_set rfds;
  timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  input_on();

  while (true)
  {
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    // there is some data in the thread
    if (select(1, &rfds, NULL, NULL, &timeout) > 0 && FD_ISSET(STDIN_FILENO, &rfds))
    {
      switch (getchar())
      {

      case 73:
      case 105:
        pala_right->moveUp();
        break;

      case 75:
      case 107:
        pala_right->moveDown();
        break;

      case 87:
      case 119:
        pala_left->moveUp();
        break;

      case 83:
      case 115:
        pala_left->moveDown();
        break;

      case 27:
        //exit();
        //return 0;
      default:
        break;
      }
    }

    bola->checkPalaLeft(pala_left);
    bola->checkPalaRight(pala_right);

    draw(bola, pala_left, pala_right);
    bola->update();
    bola->bordes(score);
    this_thread::sleep_for(chrono::milliseconds(200));
  }

  input_off();
  return 0;
}