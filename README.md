# UA-Invaders
#### Programming 1 Project 2022 by Adrián Tendero García, Alejandro Benito Marcos and Jesús Parra García
#### Computer engineering 1st year at University of Alicante (ARA Group)

## The game


   UA Invaders is a recreation of the classic game, Space Invaders, but in this case you will have to defend the University of Alicante from the enemies.
The game is programmed to run in Ubuntu OS with the X11 library installed and a full-screen terminal zoomed in 3 times.
Note that if the resolution of the screen or the hardware of the computer is not enough, the game will not run correctly.
To compile the game, you must have all the files of the main/ folder in the same directory where you compile it.
You can find more about how to play the game in its instructions once you are in the main menu.
The game has been programmed in C++ language using the gfx library, cstring, unistd.h and fstream.


##### To compile, use:
```
g++ -o main main.cpp gfx.c -lX11
chmod +x main
./main
```

## How does it work?
  The game basically works using a matrix of enemies that draws the enemies thanks to a system to draw them in a box of 19x13 pixels of a constant dimension.
  The program file has 4 main structs that track the position of the enemies, the bullets and the ship to later on check whether the bullet has hit or not.
  To make that, we have designed hitboxes for all of the enemies and the ship.
  To save the scores, we have used fstream and text files that will store the score and the name of the players between executions. 
  You can have a look at the source code to find further information.

