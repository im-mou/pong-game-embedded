import socket
import sys
#import arcade

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(('0.0.0.0', 50000))
for x in range(0, 10000):
    print("sent")
    print(s.send("Hola"))

    print("recived")
    print(str(s.recv(1000)))
    print(x)
s.close()

# # Set constants for the screen size
# SCREEN_WIDTH = 800
# SCREEN_HEIGHT = 500

# # Open the window. Set the window title and dimensions (width and height)
# arcade.open_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Juego del pong")

# # Set the background color to white.
# # For a list of named colors see:
# # http://arcade.academy/arcade.color.html
# # Colors can also be specified in (red, green, blue) format and
# # (red, green, blue, alpha) format.
# arcade.set_background_color(arcade.color.BLACK)

# # Start the render process. This must be done before any drawing commands.
# arcade.start_render()

# #palas
# h = 100
# w = 15
# y = (SCREEN_HEIGHT/2)-h/2 

# #bola
# radius = 10
# arcade.draw_circle_filled(100, 300, radius, arcade.color.WHITE)

# #pala left
# x = 10
# arcade.draw_lrtb_rectangle_filled(x, x+w, y+h, y, arcade.color.WHITE)

# #pala right
# x = SCREEN_WIDTH - w - x
# arcade.draw_lrtb_rectangle_filled(x, x+w, y+h, y, arcade.color.WHITE)

# #linea separadora
# x = (SCREEN_WIDTH/2) -1 
# arcade.draw_lrtb_rectangle_filled(x,x+2,SCREEN_HEIGHT,0,arcade.color.GRAY)

# #muros
# arcade.draw_lrtb_rectangle_filled(0,SCREEN_WIDTH,10,0,arcade.color.WHITE)
# arcade.draw_lrtb_rectangle_filled(0,SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_HEIGHT-10,arcade.color.WHITE)

# #puntuaciones
# arcade.draw_text("0", (SCREEN_WIDTH/2)-35, SCREEN_HEIGHT-50, arcade.color.WHITE, 18, align="center")
# arcade.draw_text("0", (SCREEN_WIDTH/2)+23, SCREEN_HEIGHT-50, arcade.color.WHITE, 18, align="center")

# # Finish drawing and display the result
# arcade.finish_render()

# # Keep the window open until the user hits the 'close' button
# arcade.run()

