import arcade
import sys
import serial

# Size of the screen pr defecto
SCREEN_WIDTH = None
SCREEN_HEIGHT = None
SCREEN_TITLE = "Juego del pong"

class Bola:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.r = 0

class Pala:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.w = 0
        self.h = 0

class MyGame(arcade.Window):
    """ Main application class. """

    def __init__(self, width, height, title):
        """
        Initializer
        """
        self.gameOver = False
        self.bola = None
        self.pl = None
        self.pr = None
        self.sw = None
        self.sh = None
        self.score = ["0","0"]

        # escuchar al puerto
        self.ser = serial.Serial('/dev/tty.usbmodem642', 9600, timeout=1)

    def init_game(self):

        #crear objetos
        self.bola = Bola()
        self.pl = Pala()
        self.pr = Pala()

        # esperar hasta recibir la señal de inicio
        while self.ser.readline().decode("utf-8").rstrip('\n') != "\x00init":
            print("Reinicia para empezar")

        # leer los datos para la inicializacion
        line = ''
        while True:
            line = self.ser.readline().decode("utf-8").rstrip('\n').split()
            if len(line) > 0:
                if line[0] == "tablero":
                    self.sw = int(line[1])
                    self.sh = int(line[2])
                    super().__init__(self.sw, self.sh, "title")
                elif line[0] == "bola":
                    self.bola.x = int(line[1])
                    self.bola.y = int(line[2])
                    self.bola.r = int(line[3])
                elif line[0] == "palal":
                    self.pl.x = int(line[1])
                    self.pl.y = int(line[2])
                    self.pl.w = int(line[3])
                    self.pl.h = int(line[4])
                elif line[0] == "palar":
                    self.pr.x = int(line[1])
                    self.pr.y = int(line[2])
                    self.pr.w = int(line[3])
                    self.pr.h = int(line[4])
                elif line[0] == "done":
                    self.gameOver = False
                    break
            print(line)

        # Set the background color
        arcade.set_background_color(arcade.color.BLACK)
        

    def on_draw(self):
        """
        Render the screen.
        """

        # This command is necessary before drawing
        arcade.start_render()

        #linea separadora
        x = (self.sw/2) -1 
        arcade.draw_lrtb_rectangle_filled(x,x+2,self.sh,0,arcade.color.GRAY)

        #muros
        arcade.draw_lrtb_rectangle_filled(0,self.sw,10,0,arcade.color.WHITE)
        arcade.draw_lrtb_rectangle_filled(0,self.sw,self.sh,self.sh-10,arcade.color.WHITE)

        #puntuaciones
        arcade.draw_text(self.score[0], (self.sw/2)-35, self.sh-50, arcade.color.WHITE, 18, align="center")
        arcade.draw_text(self.score[1], (self.sw/2)+23, self.sh-50, arcade.color.WHITE, 18, align="center")

        # bola
        arcade.draw_circle_filled(self.bola.x, self.bola.y, self.bola.r, arcade.color.WHITE)

        #pala left
        arcade.draw_lrtb_rectangle_filled(self.pl.x, self.pl.x+self.pl.w, self.pl.y+self.pl.h, self.pl.y, arcade.color.WHITE)

        #pala right
        arcade.draw_lrtb_rectangle_filled(self.pr.x, self.pr.x+self.pr.w, self.pr.y+self.pr.h, self.pr.y, arcade.color.WHITE)


    def on_update(self, delta_time):
        """
        All the logic to move, and the game logic goes here.
        """
        if not self.gameOver:
            line = self.ser.readline().decode("utf-8").rstrip('\n').split()
            if len(line) > 0:
                # data = "d bola(x,y) score(l,r) pala_left(y) pala_right(y)"
                if line[0] == "d": #bola position
                    # print(line)
                    self.bola.x = int(line[1])
                    self.bola.y = int(line[2])
                    #puntuacion
                    self.score[0] = line[3] # puntuacion izq.
                    self.score[1] = line[4] # puntuacion derec.
                    #auto left
                    self.pl.y = int(line[5])
                    #auto right
                    self.pr.y = int(line[6])


def main():
    window = MyGame(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    window.init_game()
    #emitir estado ready
    window.ser.write('1'.encode('utf-8'))
    arcade.run()

if __name__ == "__main__":
    main()