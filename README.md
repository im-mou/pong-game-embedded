![game.png]('images/game.png')
# Pong Game 

Implementación del juego del pong en c++ para el microcontrolador klz25

## Requerimientos

Se necesita el compilador gcc, g++ o clang.


## Método de uso
Para compilar y ejecutar la aplicación usa la siguiente comanda en el directorio base del proyecto:

```bash
make all
./game.out
```
Para limpiar el proyecto usa la siguiente comanda:
```bash
make clean
```
## Controles
```bash
Pala izquierda:
 ---------------       -----------------
|   Up  ·   w   |     |   Down  ·   s   |  
 ---------------       -----------------

Pala derecha:
 ---------------       -----------------
|   Up  ·   i   |     |   Down  ·   k   |  
 ---------------       -----------------
```

## Cosas por arreglar
- Detección de colisión de la bola contra las palas y los muros.
- Inicio aleatorio de la bola.
- Fijar velocidad de la bola.
- Fin del juego.
## Cosas por implementar
- Menú principal del juego.
- Implementación del código para la placa klz25.
- Implementación entrada por el sensor táctil.
- Interfaz python.