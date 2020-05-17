#include "mbed.h"
#include "tsi_sensor.h"

/* This defines will be replaced by PinNames soon */
#if defined(TARGET_KL25Z) || defined(TARGET_KL46Z)
#define ELEC0 9
#define ELEC1 10
#elif defined(TARGET_KL05Z)
#define ELEC0 9
#define ELEC1 8
#else
#error TARGET NOT DEFINED
#endif

#include <math.h>
#include "globals.h"
#include "source/bola.h"
#include "source/pala.h"

//DigitalOut myled(LED_GREEN);
Serial pc(USBTX, USBRX);

// character of the snake body
int score[] = {0, 0}; // score izq. , derecha

int main(int argc, const char **argv)
{
    int touch = 0;
    // pala width, height
    int pw = 15;
    int ph = 100;
    int sp = 10; // separacion de los limites laterales
    int b_speed = 10;

    // configurar el UART
    pc.baud(9600);
    pc.format(8, Serial::None, 2);

    TSIAnalogSlider tsi(ELEC0, ELEC1, 40);

    // inicializar los elementos

    // (x,y,w,h)
    Bola *bola = new Bola(100, 50, 10, 10, b_speed);
    Pala *pala_left = new Pala(sp, (MAP_HEIGHT / 2) - ph / 2, pw, ph, b_speed);
    Pala *pala_right = new Pala(MAP_WIDTH - pw - sp, (MAP_HEIGHT / 2) - ph / 2, pw, ph, b_speed);

    // enviar la comanda para el inicio
    pc.printf("init\n");

    // dimensiones => (w,h)
    pc.printf("tablero %i %i\n", MAP_WIDTH, MAP_HEIGHT);

    // dimensiones => (x,y,w,h)
    pc.printf("bola %d %i %i\n", bola->x, bola->y, bola->w / 2); // enviar radio
    pc.printf("palal %i %i %i %i\n", pala_left->x, pala_left->y, pala_left->w, pala_left->h);
    pc.printf("palar %i %i %i %i\n", pala_right->x, pala_right->y, pala_right->w, pala_right->h);
    pc.printf("done\n");

    // esperar hasta recibir respuesta desdel host
    while (pc.getc() != '1')
    {
        ;
    };

    // enviar la comanda para empezar
    pc.printf("started\n");

    while (true)
    {

        //myled = !myled;

        bola->checkPalaLeft(pala_left);
        bola->checkPalaRight(pala_right);

        touch = tsi.readDistance();
        if (touch > 0 && touch < 20)
        {
            pala_right->moveDown();
            pala_left->moveDown();
        }
        else if (touch > 20)
        {
            pala_right->moveUp();
            pala_left->moveUp();
        }

        bola->update();
        bola->bordes(score);

        pc.printf("d %i %i %i %i %i %i\n", bola->x, bola->y, score[0], score[1], pala_left->y, pala_right->y);

        wait(0.01f);
    }
    return 0;
}