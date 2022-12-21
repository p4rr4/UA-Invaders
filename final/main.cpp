#include <iostream>
#include "gfx.h"
#include <unistd.h>
#include <fstream>
#include <cstring>

using namespace std;

struct database { //Struct for saving scores
	int punt;
	char nam[4];
};

struct DatosEnemigos{    //hitbox
	int x;
	int y;
	int ancho;
	int alto;
	int f;
	int c;
	int contador;
};

struct DatosBalas{
	int x;				//coordenada x
	int y;				//coordenada y
	int ancho;			//hitbox x
	int alto;			//hitbox y
	int type;			//0 no hay bala, 1 para balas jugador y 2 para balas del enemigo
	int color[3];		//color de la bala
};

struct DatosJugador{
	int x;      //X de la nave
	int y;      //Y de la nave
	int yH;    //hitbox
	int ancho;  //dimension de la nave
	int alto;   //dimension de la nave
	int altoh; //hitbox
	int skin;   //aspecto de la nave
	int vida;   //vidas de la nave
};

/*
ANIMATION MODULES
These modules are all for printing characters in the terminal, so there is no explanation for them.
However, it is important to know that we use the ANSI colour codes for C++ to change the colour of the font.
We also use usleep() to make the animation effect.
*/
void introAnim();
void initialAnimation(char &answer);
void mainMenu(char name[4],int &opt,DatosJugador &jugador, int &cantE, bool &win, int &b,database data);
void menuJugar(char name[4],int &opt,DatosJugador &jugador, int &cantE, bool &win, int &b,database data);
void printLetter();
void credits(char name[4],int &opt,DatosJugador &jugador, int &cantE, bool &win, int &b,database data);
void instructions(char &ans, char name[4]);
void victoryAnim(char ans,char name[4],int score,DatosJugador jugador, int b);
void gameOverAnim(char ans,char name[4],int score,DatosJugador jugador,int cantE, int b);
void saveScore(database data,int level, char name[4], int score, char &ans); //This module uses the fstream library to save the scores to each text file
void EPSanimation();

void clearbuffer(); // Clears the keyboard buffer

void DefEne(int x, int y, int ancho, int alto, int f, int c, int e, DatosEnemigos enemigo[]);

// Modules that draw things
void DibEne1(int x, int y, int alto, int pixDim);  // draws enemy blue martian
void DibEne2(int x, int y, int alto, int pixDim); // draws enemy space invaders classic mini
void DibEne3(int x, int y, int alto, int pixDim); // draws enemy eye
void DibEne4(int x, int y, int alto, int pixDim); // draws enemy UFO
void DibEne3_1(int x, int y, int alto, int pixDim); // draws second life version of enemy eye
void dibExp(int x, int y, int alto, int pixDim); // draws the enemies' explosion
void DibP(int x, int y,int alto, int pixDim, int &hitJ, DatosJugador jugador); // draws the player's ship
void dibCorazon(int x, int y); // draws hearts (players' lifes)



// Levels
void lvl1_1(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl1_2(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl1_3(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl2_1(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl2_2(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl2_3(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl3_1(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl3_2(DatosJugador &jugador, int &cantE, bool &win, int &b);
void lvl3_3(DatosJugador &jugador, int &cantE, bool &win, int &b);


// Bullet components
void DefBala(int b, int type, int pixDim, int e, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador jugador);
void movBalas(int nb, int windowY, DatosBalas bala[], DatosEnemigos enemigo[], DatosJugador jugador);
void dibBala(int b, DatosBalas bala[]);
void DibTodasBalas(int nb, DatosBalas bala[]);


char DetInput(char input);
void accion(char input, int windowX, DatosJugador &jugador);


void interfaz(int wX,int wY, DatosJugador jugador);
void matriz(int x0, int y0,int ancho, int alto, int sep,int enemigos[][10], int f, int c, int pixDim, DatosEnemigos enemigo[]);

void killing(int &score,int nb, int enemigos[][10],int f, int c, int &hitJ, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador &jugador, int &lastEne);
bool GameOver(int f, int c, DatosEnemigos enemigo[], DatosJugador jugador);
bool countE(int enemigos[][10],int f, int c, int &cant);

void animDrch(int &score,DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c);
void animIzq(int &score,DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c);
void animMatriz(int &score,DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,int f,int c);

void stats(int score,char name[4],DatosJugador jugador,int cantE, bool win, int b, int level,database data, char &ans);

int sumScore(int enemigos[][10], int f, int c, int &score);

void resetEne(int ne, DatosEnemigos enemigo[], int f, int c);

int main()
{
	DatosJugador jugador;
	database data;
	bool win=0;
	int cantE=0;
	int b=0; //identificador de las balas
	char ans;
	int option;
	char name[4];
	char input;

	initialAnimation(ans);
	printLetter();

	cout << "\n\n\t\t\t\t\t\t\u001b[34mEɳƚҽɾ ყσυɾ ɳαɱҽ (3 ʅҽƚƚҽɾʂ): ";
	cin >> name;

	mainMenu(name,option,jugador,cantE,win,b,data);
	
	return 0;
}
int sumScore(int enemigos[][10], int f, int c, int &score){
	switch(enemigos[f][c]){
		case 1:
			score+=30;
		break;
		case 2:
			score+=20;
		break;
		case 4:
			score+=35;
		break;
		case 5:
			score+=40;
		break;
	}
	return score;
}
void resetEne(int ne, DatosEnemigos enemigo[], int f, int c){
	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			enemigo[j+i*c].x=0;
			enemigo[j+i*c].y=0;
			enemigo[j+i*c].ancho=0;
			enemigo[j+i*c].alto=0;
			enemigo[j+i*c].f=i;
			enemigo[j+i*c].c=j;
			enemigo[j+i*c].contador=-1;
		}
	}

}
void lvl1_1(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){

	score=0;
	b=0;

	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=200;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=4;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=10;//distancia de cada movimiento
	int ticks=50;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=1000;
	int balasEnemigas4=1000;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala11 [500];
	DatosEnemigos enemigo11 [F*C];

	resetEne(cantE,enemigo11,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=1;
	jugador.vida=3;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador

	int enemigos11 [F][C]=
	{{0,0,0,2,0,0,2,0,0,0},
	{0,0,0,0,2,2,0,0,0,0},
	{0,0,0,0,2,2,0,0,0,0},
	{0,0,0,2,0,0,2,0,0,0}};
	
	win=countE(enemigos11,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");
	animMatriz(score,jugador,enemigo11,bala11,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos11,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}

void lvl1_2(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	
	score=0;
	b=0;
	
	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=5;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=10;//distancia de cada movimiento
	int ticks=50;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=1000;
	int balasEnemigas4=1000;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala12 [500];
	DatosEnemigos enemigo12 [F*C];

	resetEne(cantE,enemigo12,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=1;
	jugador.vida=3;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador


	int enemigos12 [F][C]=
	{{0,2,0,0,2,2,0,0,2,0},
	{0,0,2,0,2,2,0,2,0,0},
	{0,0,3,2,0,0,2,3,0,0},
	{0,0,0,0,2,2,0,0,0,0},
	{0,0,0,0,3,3,0,0,0,0}};
	
	win=countE(enemigos12,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");
	animMatriz(score, jugador,enemigo12,bala12,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos12,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}

void lvl1_3(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;
	
	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=6;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=10;//distancia de cada movimiento
	int ticks=50;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=1000;
	int balasEnemigas4=1000;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala13 [500];
	DatosEnemigos enemigo13 [F*C];

	resetEne(cantE,enemigo13,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=1;
	jugador.vida=3;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador


	int enemigos13 [F][C]=
	{{2,0,0,2,0,0,2,0,0,2},
	{0,3,3,0,3,3,0,3,3,0},
	{0,3,3,0,3,3,0,3,3,0},
	{2,0,0,2,0,0,2,0,0,2},
	{3,0,0,3,0,0,3,0,0,3},
	{0,2,2,0,2,2,0,2,2,0}};
	
	win=countE(enemigos13,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score,jugador,enemigo13,bala13,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos13,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}

void lvl2_1(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;
	
	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=8;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=15;//distancia de cada movimiento
	int ticks=40;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=50;
	int balasEnemigas1=200;
	int balasEnemigas4=1000;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala21 [500];
	DatosEnemigos enemigo21 [F*C];

	resetEne(cantE,enemigo21,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=2;
	jugador.vida=4;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador


	int enemigos21 [F][C]=
	{{1,0,0,0,1,1,0,0,0,1},
	{0,2,0,3,0,0,3,0,2,0},
	{2,0,2,0,3,3,0,2,0,2},
	{2,0,2,0,3,3,0,2,0,2},
	{0,0,0,3,0,0,3,0,0,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,2,2,0,0,0,0,2,2,0}};
	
	win=countE(enemigos21,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score, jugador,enemigo21,bala21,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos21,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}

void lvl2_2(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;
	
	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=7;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=15;//distancia de cada movimiento
	int ticks=40;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=50;
	int balasEnemigas1=200;
	int balasEnemigas4=1000;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala22 [500];
	DatosEnemigos enemigo22 [F*C];

	resetEne(cantE,enemigo22,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=2;
	jugador.vida=4;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador


	int enemigos22 [F][C]=
	{{0,3,0,1,0,0,1,0,3,0},
	{3,0,3,0,2,2,0,3,0,3},
	{0,5,0,0,2,2,0,0,5,0},
	{5,1,5,5,1,1,5,5,1,5},
	{0,5,0,5,0,0,5,0,5,0},
	{0,0,2,0,3,3,0,2,0,0},
	{1,0,0,3,0,0,3,0,0,1}};
	
	win=countE(enemigos22,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score,jugador,enemigo22,bala22,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos22,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);

}
void lvl2_3(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;
	
	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=9;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=15;//distancia de cada movimiento
	int ticks=40;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=200;
	int balasEnemigas4=400;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala23 [500];
	DatosEnemigos enemigo23 [F*C];

	resetEne(cantE,enemigo23,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=2;
	jugador.vida=4;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador

	int enemigos23 [F][C]=
	{{3,0,0,2,0,0,2,0,0,3},
	{0,0,1,0,0,0,0,1,0,0},
	{0,0,2,2,0,0,2,2,0,0},
	{0,0,4,2,2,2,2,4,0,0},
	{0,3,0,0,2,2,0,0,3,0},
	{4,0,0,0,0,0,0,0,0,4},
	{0,0,4,0,1,1,0,4,0,0},
	{0,4,0,0,0,0,0,0,4,0},
	{0,2,0,0,2,2,0,0,2,0}};
	
	win=countE(enemigos23,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score,jugador,enemigo23,bala23,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos23,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);

}
void lvl3_1(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;
	
	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=8;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=15;//distancia de cada movimiento
	int ticks=40;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=100;
	int balasEnemigas4=300;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala31 [500];
	DatosEnemigos enemigo31 [F*C];

	resetEne(cantE,enemigo31,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=3;
	jugador.vida=4;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador

	int enemigos31 [F][C]=
	{{2,4,2,0,2,2,0,2,4,2},
	{4,2,0,2,0,0,2,0,2,4},
	{5,3,0,0,5,5,0,0,3,5},
	{2,1,3,0,4,4,0,3,1,2},
	{0,2,0,3,0,0,3,0,2,0},
	{3,0,3,5,0,0,5,3,0,3},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,2,0,0,0,0,2,0,0}};
	
	win=countE(enemigos31,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score,jugador,enemigo31,bala31,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos31,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}
void lvl3_2(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;

	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=9;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=15;//distancia de cada movimiento
	int ticks=40;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=100;
	int balasEnemigas4=200;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala32 [500];
	DatosEnemigos enemigo32 [F*C];

	resetEne(cantE,enemigo32,F,C);

	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=3;
	jugador.vida=4;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador

	int enemigos32 [F][C]=
	{{4,5,5,0,0,0,0,5,5,4},
	{0,5,5,0,1,1,0,5,5,0},
	{2,1,0,4,0,0,4,0,1,2},
	{3,2,0,0,0,0,0,0,2,3},
	{4,3,2,1,0,0,1,2,3,4},
	{0,0,3,2,0,0,2,3,0,0},
	{0,2,0,3,2,2,3,0,2,0},
	{0,0,0,0,5,5,0,0,0,0},
	{0,2,0,2,0,0,2,0,2,0}};
	
	win=countE(enemigos32,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score,jugador,enemigo32,bala32,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos32,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}
void lvl3_3(int &score, DatosJugador &jugador, int &cantE, bool &win, int &b){
	score=0;
	b=0;

	int pixDim=4;//dimension de los píxeles
	int windowX=1200;//X de la ventana
	int windowY=900;//Y de la ventana
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int x=20;//esquina inicial de los enemigos
	int y=20;//esquina inicial de los enemigos
	int sep=12;//separacion entre enemigos
	const int F=11;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=15;//distancia de cada movimiento
	int ticks=40;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=100;
	int balasEnemigas4=200;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala33 [500];
	DatosEnemigos enemigo33 [F*C];
	resetEne(cantE,enemigo33,F,C);
	jugador.ancho= 25*pixDim;
	jugador.alto= 17*pixDim;
	jugador.altoh = 10*pixDim;
	jugador.x=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	jugador.y=windowY-60-jugador.alto;//posicion inicial del jugador
	jugador.yH=jugador.y+8*pixDim;
	jugador.skin=3;
	jugador.vida=6;


	int k=(windowX-(C*ancho)-(C*sep)-x)/dist;//número de movimientos de la animacion
	int xd=x;//x de dibujado
	int yd=y;//y de dibujado
	int xP=(windowX-jugador.ancho)/2;//posicion inicial del jugador
	int yP=windowY-20-jugador.alto;//posicion inicial del jugador

	int enemigos33 [F][C]=
	{{0,5,0,5,0,0,5,0,5,0},
	{0,0,5,0,0,0,0,5,0,0},
	{3,1,0,2,0,0,2,0,1,3},
	{0,0,2,0,2,2,0,2,0,0},
	{3,0,3,3,0,0,3,3,0,3},
	{1,3,4,1,3,3,1,4,3,1},
	{3,0,3,3,0,0,3,3,0,3},
	{0,0,0,0,0,0,0,0,0,0},
	{2,0,0,0,0,0,0,0,0,2},
	{0,0,2,0,0,0,0,2,0,0},
	{0,5,0,0,2,2,0,0,5,0}};
	
	win=countE(enemigos33,F,C,cantE);

	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(score,jugador,enemigo33,bala33,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos33,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,F,C);
}
int lastE(int enemigos[][10],int f, int c){

	int ene=0;

	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if(enemigos[i][j]!=0){
				ene=j+i*c;
			}
		}
	}

	return ene;
}
void stats(int score,char name[4],DatosJugador jugador,int cantE, bool win, int b, int level,database data, char &ans){
	char res;
	if (win==1)
	{
		gfx_close();
		victoryAnim(res,name,score,jugador,b);
		saveScore(data,level,name,score,ans);
	}else{
		gfx_close();
		gameOverAnim(res,name,score,jugador,cantE,b);
		saveScore(data,level,name,score,ans);
	}
}
void animMatriz(int &score,DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,int f,int c){

	char input;

	while(input!='q' && lost==0 && win==0){

		animDrch(score,jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,f,c);
		yd=yd+alto;
		animIzq(score,jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,f,c);
		yd=yd+alto;
	}
}
void animDrch(int &score,DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c){
	int r=0;

	lastEne=lastE(enemigos,f,c);

	while(r<k*ticks && input!='q' && lost==0 && win==0)
	{
		win=countE(enemigos, f,c, cantE);
		input=DetInput(input);
		accion(input,windowX, jugador);

		if(r%velBalas==0)movBalas(b,windowY,bala,enemigo, jugador);
		if(r%ticksBala==0){
			DefBala(b,1,pixDim,0, enemigo, bala, jugador);
			b++;
		}
		if(r%balasEnemigas1==0 && r!=0){
			for (int i = 0; i < f; ++i)
			{
				for (int j = 0; j < c; ++j)
				{
					if (enemigos[i][j]==1)
					{
						DefBala(b,2,pixDim,j+i*c, enemigo, bala, jugador);
						b++;
					}
				}
			}
		}
		if(r%balasEnemigas4==0 && r!=0){
			for (int i = 0; i < f; ++i)
			{
				for (int j = 0; j < c; ++j)
				{
					if (enemigos[i][j]==4)
					{
						DefBala(b,3,pixDim,j+i*c, enemigo, bala, jugador);
						b++;
					}
					
				}
			}
		}
		if(r%ticks==0)xd=x+dist*r/ticks;

		killing(score,b,enemigos,f,c,hitJ, enemigo, bala, jugador,lastEne);
		lost=GameOver(f,c, enemigo, jugador);

		if ((enemigo[lastEne].y+enemigo[lastEne].alto) > (windowY-40))
		{
			lost=1;
		}

		if (jugador.vida<=0)
		{
			lost=1;
		}

		gfx_clear();
		

		interfaz(windowX,windowY, jugador);
		DibTodasBalas(b, bala);
		DibP(jugador.x, jugador.y, jugador.alto, pixDim, hitJ, jugador);
		matriz(xd,yd,ancho,alto,sep,enemigos,f,c, pixDim, enemigo);


		gfx_flush();
		usleep(t/ticks);

		++r;
	}
	return;
}
void animIzq(int &score,DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c){
	int l=(k-1)*ticks;

	lastEne=lastE(enemigos,f,c);

	while(l >= 0 && input!='q'&& lost==0 && win==0)
	{
		win=countE(enemigos, f,c, cantE);
		input=DetInput(input);
		accion(input,windowX, jugador);
		if(l%velBalas==0)movBalas(b,windowY, bala, enemigo,jugador);
		if (l!=0)
		{
			if(l%ticksBala==0){
				DefBala(b,1,pixDim,0, enemigo, bala, jugador);
				b++;
			}
		}
		if (l!=0){
			if(l%balasEnemigas1==0){
				for (int i = 0; i < f; ++i)
				{
					for (int j = 0; j < c; ++j)
					{
						if (enemigos[i][j]==1)
						{
							DefBala(b,2,pixDim,j+i*c, enemigo, bala, jugador);
							b++;
						}
						
					}
				}
			}
		}
		if(l%balasEnemigas4==0){
			for (int i = 0; i < f; ++i)
			{
				for (int j = 0; j < c; ++j)
				{
					if (enemigos[i][j]==4)
					{
						DefBala(b,3,pixDim,j+i*c, enemigo, bala, jugador);
						b++;
					}
					
				}
			}
		}
		if(l%ticks==0)xd=x+dist*l/ticks;

		killing(score,b,enemigos,f,c,hitJ, enemigo, bala, jugador,lastEne);
		lost=GameOver(f,c, enemigo, jugador);

		if ((enemigo[lastEne].y+enemigo[lastEne].alto) > (windowY-40))
		{
			lost=1;
		}

		if (jugador.vida<=0)
		{
			lost=1;
		}

		gfx_clear();

		interfaz(windowX,windowY, jugador);
		DibTodasBalas(b, bala);
		DibP(jugador.x, jugador.y, jugador.alto, pixDim, hitJ, jugador);
		matriz(xd,yd,ancho,alto,sep,enemigos,f,c, pixDim, enemigo);

		gfx_flush();
		usleep(t/ticks);

		--l;
	}
	return;
}
void dibExp(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo

	gfx_color(255,0,0);

	for (int i = 0; i < alto; ++i)
	{

		if (i==3)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

		if (i==4)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

		if (i==5)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

		if (i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

		if (i==8)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

		if (i==9)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 }
		}

	}
}
void dibCorazon(int x, int y){
	int pixDim=2;
	int alto=13;
	int arre=pixDim-1;//arreglo

	gfx_color(255,0,0);

	for (int i = 0; i < alto; ++i)
	{
		if (i==2)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==3)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+3*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==4)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==5)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			 }
		}

		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+3*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==8)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==9)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==10)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			}
		}
	}
}
bool countE(int enemigos[][10],int f, int c, int &cant){
	bool win;
	cant=0;

	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (enemigos[i][j]!=0)
			{
				cant++;
			}
		}
	}
	if (cant==0)
	{
		win=1;
	}else{
		win=0;
	}

	return win;
}
bool GameOver(int f, int c, DatosEnemigos enemigo[], DatosJugador jugador){
	bool lost;

	for (int i = 0; i < f; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				if (enemigo[j+i*c].y + enemigo[j+i*c].alto > jugador.y && enemigo[j+i*c].x + enemigo[j+i*c].ancho > jugador.x && enemigo[j+i*c].y < jugador.y + jugador.alto && enemigo[j+i*c].x < jugador.x + jugador.ancho)
				{
					lost=1;
				}
			}
		}
	return lost;
}
void DefEne(int x, int y, int ancho, int alto, int f, int c, int e, DatosEnemigos enemigo[]){
	enemigo[e].x=x;
	enemigo[e].y=y;
	enemigo[e].ancho=ancho;
	enemigo[e].alto=alto;
	enemigo[e].f=f;
	enemigo[e].c=c;
}
void matriz(int x0, int y0,int ancho, int alto, int sep,int enemigos [][10],int f, int c, int pixDim, DatosEnemigos enemigo[]){

	int e=0;

	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (enemigos [i][j]==1)
			{
				DibEne1(x0+j*(ancho+sep), y0+i*(alto+sep),alto,pixDim);
				DefEne((x0+j*(ancho+sep))+4*pixDim, (y0+i*(alto+sep))+4*pixDim, (11*pixDim)-1, (9*pixDim)-1,i,j,e, enemigo);
			}

			if (enemigos [i][j]==2)
			{
				DibEne2(x0+j*(ancho+sep), y0+i*(alto+sep),alto, pixDim);
				DefEne((x0+j*(ancho+sep))+4*pixDim,(y0+i*(alto+sep))+7*pixDim,(11*pixDim)-1,(3*pixDim)-1,i,j,e, enemigo);
			}

			if (enemigos [i][j]==3)
			{
				DibEne3(x0+j*(ancho+sep), y0+i*(alto+sep),alto, pixDim);
				DefEne((x0+j*(ancho+sep))+4*pixDim, (y0+i*(alto+sep))+0*pixDim, (11*pixDim)-1, (12*pixDim)-1,i,j,e, enemigo);
			}

			if (enemigos [i][j]==4)
			{
				DibEne4(x0+j*(ancho+sep), y0+i*(alto+sep),alto, pixDim);
				DefEne((x0+j*(ancho+sep))+1*pixDim, (y0+i*(alto+sep))+3*pixDim, (17*pixDim)-1, (8*pixDim)-1,i,j,e, enemigo);
			}

			if (enemigos [i][j]==5)
			{
				DibEne3_1(x0+j*(ancho+sep), y0+i*(alto+sep),alto, pixDim);
				DefEne((x0+j*(ancho+sep))+1*pixDim, (y0+i*(alto+sep))+3*pixDim, (17*pixDim)-1, (8*pixDim)-1,i,j,e, enemigo);
			}

			if (enemigos [i][j]==0)
			{
				if (enemigo[j+i*c].contador==-1)
				{
				}else if(enemigo[j+i*c].contador>0){
					dibExp(x0+j*(ancho+sep), y0+i*(alto+sep),alto, pixDim);
					enemigo[j+i*c].contador-=1;
					DefEne(0,0,0,0,i,j,e, enemigo);
				}else{
					DefEne(0,0,0,0,i,j,e, enemigo);
				}
			}

			e++;
		}
	}
}
void killing(int &score,int nb, int enemigos[][10],int f, int c, int &hitJ, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador &jugador, int &lastEne){

	for (int b = 0; b < nb; ++b)
	{
		if (bala[b].type==1)
		{
			for (int i = 0; i < f; ++i)
			{
				for (int j = 0; j < c; ++j)
				{
					if(enemigos[i][j]!=0){
						if (enemigo[j+i*c].y + enemigo[j+i*c].alto > bala[b].y && enemigo[j+i*c].x + enemigo[j+i*c].ancho > bala[b].x && enemigo[j+i*c].y < bala[b].y + bala[b].alto && enemigo[j+i*c].x < bala[b].x + bala[b].ancho)
						{
							if (enemigos[i][j]==3)//enemigo que tiene dos vidas
							{
								enemigos[i][j]=5;
								lastEne=lastE(enemigos,f,c);
							}else{
								score=sumScore(enemigos,i,j,score);
								enemigos[i][j]=0;
								enemigo[j+i*c].contador=30;
								lastEne=lastE(enemigos,f,c);
							}

							DefBala(b,0,0,0, enemigo, bala, jugador);

						}
					}
				}
			}
		}	
		if (bala[b].type==2) //bala enemigo 1 resta 1 de vida
		{
			if (jugador.yH + jugador.altoh > bala[b].y && jugador.x + jugador.ancho > bala[b].x && jugador.yH < bala[b].y + bala[b].alto && jugador.x < bala[b].x + bala[b].ancho)
			{
				jugador.vida-=1;
				DefBala(b,0,0,0, enemigo, bala, jugador);
				hitJ=30;//dura menos tiempo el efecto de daño(contador)
			}
		}
		if (bala[b].type==3) ////bala enemigo 4 resta 2 de vida
		{
			if (jugador.yH + jugador.altoh > bala[b].y && jugador.x + jugador.ancho > bala[b].x && jugador.yH < bala[b].y + bala[b].alto && jugador.x < bala[b].x + bala[b].ancho)
			{
				jugador.vida-=2;
				DefBala(b,0,0,0, enemigo, bala, jugador);
				hitJ=60; //dura mas tiempo el efecto de daño(contador)
			}
		}	
	}
}
void movBalas(int nb, int windowY, DatosBalas bala[], DatosEnemigos enemigo[], DatosJugador jugador){
	for (int b = 0; b < nb; ++b)
	{	
		if (bala[b].type==1)
		{
			bala[b].y-=10;
			if (bala[b].y<12)
			{
				DefBala(b,0,0,0, enemigo, bala, jugador);
			}
		}
		if (bala[b].type==2)
		{
			bala[b].y+=10;
			if (bala[b].y>windowY-60)
			{
				DefBala(b,0,0,0, enemigo, bala, jugador);
			}
		}
		if (bala[b].type==3)
		{
			bala[b].y+=5;
			if (bala[b].y>windowY-60)
			{
				DefBala(b,0,0,0, enemigo, bala, jugador);
			}
		}
	}
}
void DefBala(int b, int type, int pixDim, int e, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador jugador){

	switch(type){
		case 0:
			bala[b].x=0;
			bala[b].y=0;
			bala[b].ancho=0;
			bala[b].alto=0;
		break;
		case 1:            //balas del jugador
			bala[b].type=type;
			bala[b].ancho=1*pixDim;;
			bala[b].alto=3*pixDim;;
			bala[b].x=jugador.x+(jugador.ancho-(bala[b].ancho))/2;
			bala[b].y=jugador.y-1*pixDim;
			bala[b].color[0]=200;
			bala[b].color[1]=100;
			bala[b].color[2]=50;
		break;
		case 2:    //balas enemigo 1
			bala[b].type=type;
			bala[b].ancho=1*pixDim;;
			bala[b].alto=1*pixDim;;        
			bala[b].x=enemigo[e].x + (enemigo[e].ancho-(bala[b].ancho))/2;
			bala[b].y=enemigo[e].y + enemigo[e].alto;
			bala[b].color[0]=50;
			bala[b].color[1]=200;
			bala[b].color[2]=10;
		break;
		case 3:    //balas enemigo 4
			bala[b].type=type;
			bala[b].ancho=3*pixDim;;
			bala[b].alto=3*pixDim;;        
			bala[b].x=enemigo[e].x + (enemigo[e].ancho-(bala[b].ancho))/2;
			bala[b].y=enemigo[e].y + enemigo[e].alto;
			bala[b].color[0]=255;
			bala[b].color[1]=10;
			bala[b].color[2]=10;
		break;
	}
}
void dibBala(int b, DatosBalas bala[]){
	
	gfx_color(bala[b].color[0] , bala[b].color[1] , bala[b].color[2]);
	for (int i = 0; i < bala[b].alto; ++i)
	{
		gfx_line( bala[b].x , bala[b].y+i , bala[b].x+bala[b].ancho-1 , bala[b].y+i);
	}
}
void accion(char input, int windowX, DatosJugador &jugador){
	if (input=='Q')
	{
		jugador.x-=10;
		if (jugador.x<=20)
		{
			jugador.x=20;
		}
	}

	if (input=='S')
	{
		jugador.x+=10;
		if (jugador.x>=windowX-20-jugador.ancho)
		{
			jugador.x=windowX-20-jugador.ancho;
		}
	}
}
char DetInput(char input){

	if (gfx_event_waiting()==1){
		input=gfx_wait();	
	} else{
		input=' ';
	}
	return input;
}
void DibTodasBalas(int nb,DatosBalas bala[]){
	for (int b = 0; b < nb; ++b)
	{
		dibBala(b, bala);
	}
}
void interfaz(int wX,int wY, DatosJugador jugador){
	int up=10;
	int down=wX-10;
	int left=10;
	int right=wY-10;
	int xc=20;//corazon
	int yc=wY-40;//corazon
	gfx_color(0,150,30);

	for (int i = 0; i < 6; ++i)
	{

		if (i==0 || i==1){
			gfx_line(down-i,right-i,down-i,left+i);
			gfx_line(up+i,left+i,up+i,right-i);
			gfx_line(up+i,right-i,down-i,right-i);
			gfx_line(down-i,left+i,up+i,left+i);
		}
		if (i==4 || i==5){
			gfx_line(down-i,right-i-30,down-i,left+i);
			gfx_line(up+i,left+i,up+i,right-i-30);
			gfx_line(up+i,right-i-30,down-i,right-i-30);
			gfx_line(down-i,left+i,up+i,left+i);
		}
	}


	for (int i = 0; i < jugador.vida; ++i)
	{
		dibCorazon(xc,yc);
		xc+=24;
	}
}
void DibEne1(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo

	for (int i = 0; i < alto; ++i)
	{
		if (i==0)
		{
			for (int d = 0; d < pixDim; ++d)
			{	// Naranja claro
				gfx_color(252, 196, 85);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
			}
		}

		if (i==1)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}			 

		if (i==2)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Cian
			 	gfx_color(50, 200, 253);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			}
		}	

		if (i==3)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);


			}
		}	

		if (i==4)
		{
			for (int d = 0; d < pixDim; ++d)
			{

			 	// Cian
			 	gfx_color(50, 200, 253);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==5)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco ojos
			 	gfx_color(253, 237, 169);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);


			}
		}


		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco ojos
			 	gfx_color(253, 237, 169);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro ojos
			 	gfx_color(59, 51, 33);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);




			}
		}


		if (i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul oscuro
				gfx_color(0, 118, 213);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

			 	// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			 	// Cian
			 	gfx_color(50, 200, 253);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);


			}
		}


		if (i==8)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul oscuro
				gfx_color(0, 118, 213);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);


			 	// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);


			}
		}


		if (i==9)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul oscuro
				gfx_color(0, 118, 213);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);


			 	// Azul base
			 	gfx_color(2, 143, 244);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);


			 	// Azul mas oscuro
			 	gfx_color(0, 104, 187);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			}
		}


		if (i==10)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul oscuro
				gfx_color(0, 118, 213);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);


			 	// Azul mas oscuro
			 	gfx_color(0, 104, 187);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}


		if (i==11)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul oscuro
				gfx_color(0, 118, 213);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);



			 	// Azul mas oscuro
			 	gfx_color(0, 104, 187);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==12)
		{
			for (int d = 0; d < pixDim; ++d)
			{

				// Azul oscuro
				gfx_color(0, 118, 213);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);




			 	// Azul mas oscuro
			 	gfx_color(0, 104, 187);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);


			}
		}


	}
}
void DibEne2(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo


	for (int i = 0; i < alto; ++i)
	{
		if (i==3)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde antena
				gfx_color(8, 160, 75);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);



			}
		}

		if (i==4)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde muy oscuro
				gfx_color(19, 43, 30);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	
			 	// Verde antena
				gfx_color(8, 160, 75);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			}
		}
	

		if (i==5)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde medio
				gfx_color(5, 208, 91);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 	
			 	// Verde muy oscuro -
				gfx_color(17, 66, 37);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			 	// Verde muy oscuro --
				gfx_color(20, 96, 53);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(0, 255, 111);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);



			}
		}

		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			{	

				// Verde medio
				gfx_color(5, 208, 91);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde muy oscuro --
				gfx_color(20, 96, 53);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);


				// Verde intermedio -
				gfx_color(6, 185, 83);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	
			 	// Verde muy oscuro -
				gfx_color(17, 66, 37);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(0, 255, 111);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro ojos
			 	gfx_color(21, 21, 21);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde intermedio +
			 	gfx_color(11, 137, 64);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde muy oscuro --
				gfx_color(20, 96, 53);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);


			 	// Verde intermedio +
			 	gfx_color(11, 137, 64);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);


			 	// Verde muy oscuro -
				gfx_color(17, 66, 37);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);

				// Verde medio
				gfx_color(5, 208, 91);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

				// Verde antena
				gfx_color(8, 160, 75);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

				// Verde intermedio -
				gfx_color(6, 185, 83);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(0, 255, 111);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
				

			}
		}

		if (i==8)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde muy oscuro --
				gfx_color(20, 96, 53);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);

				// Verde antena
				gfx_color(8, 160, 75);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


				// Verde intermedio -
				gfx_color(6, 185, 83);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde intermedio +
			 	gfx_color(11, 137, 64);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde muy oscuro --
				gfx_color(20, 96, 53);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

		

			}
		}

		if (i==9)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde antena
				gfx_color(8, 160, 75);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);


				// Verde claro
				gfx_color(0, 255, 111);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde muy oscuro -
				gfx_color(17, 66, 37);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

			

			}
		}

		if (i==10)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Verde antena
				gfx_color(8, 160, 75);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde intermedio +
			 	gfx_color(11, 137, 64);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 
				// Verde medio
				gfx_color(5, 208, 91);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

				// Verde muy oscuro --
				gfx_color(20, 96, 53);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
		

			}
		}


	}
}
void DibEne3(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo


	for (int i = 0; i < alto; ++i)
	{
		gfx_color(0,200,0);
		
		
		if (i==0){
			for (int d = 0; d < pixDim; ++d){
				// Amarillo
				gfx_color(252, 215, 3);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==1){
			for (int d = 0; d < pixDim; ++d){
				// Amarillo
				gfx_color(252, 215, 3);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

				// Verde claro
				gfx_color(149, 238, 69);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==2){
			for (int d = 0; d < pixDim; ++d){
				// Amarillo
				gfx_color(252, 215, 3);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

				// Verde claro
				gfx_color(149, 238, 69);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(141, 204, 0);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==3){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(141, 204, 0);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==4){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(149, 238, 69);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 }
		}
		if (i==5){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(150, 158, 28);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==6){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(149, 238, 69);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==7){
			for (int d = 0; d < pixDim; ++d){
			 	// Verde claro
				gfx_color(149, 238, 69);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==8){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(150, 158, 28);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro
			 	gfx_color(57, 51, 32);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}		


		if (i==9){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro
			 	gfx_color(57, 51, 32);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==10){
			for (int d = 0; d < pixDim; ++d){

				// Verde pistacho
				gfx_color(150, 158, 28);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro
			 	gfx_color(57, 51, 32);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);



			}
		}
		if (i==11){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(150, 158, 28);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(141, 204, 0);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==12){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(150, 158, 28);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}

	}
}
void DibEne3_1(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo


	for (int i = 0; i < alto; ++i)
	{
				
		if (i==0){
			for (int d = 0; d < pixDim; ++d){
				// Amarillo
				gfx_color(247, 52, 43);
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			
				gfx_color(247, 104, 6);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==1){
			for (int d = 0; d < pixDim; ++d){
				// Amarillo
				gfx_color(247, 104, 6);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

				// Verde claro
				gfx_color(124, 124, 124);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==2){
			for (int d = 0; d < pixDim; ++d){
				// Amarillo
				gfx_color(247, 52, 43);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

				// Verde claro
				gfx_color(124, 124, 124);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(79, 79, 79);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==3){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(79, 79, 79);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==4){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(79, 79, 79);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(124, 124, 124);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 }
		}
		if (i==5){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(50, 50, 50);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(79, 79, 79);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==6){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(79, 79, 79);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			 	// Verde claro
				gfx_color(124, 124, 124);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==7){
			for (int d = 0; d < pixDim; ++d){
			 	// Verde claro
				gfx_color(124, 124, 124);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(79, 79, 79);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==8){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(50, 50, 50);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(247, 52, 43);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(247, 52, 43);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(79, 79, 79);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro
			 	gfx_color(57, 51, 32);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);


			}
		}		


		if (i==9){
			for (int d = 0; d < pixDim; ++d){
				// Verde oscuro
				gfx_color(50, 50, 50);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro
			 	gfx_color(57, 51, 32);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==10){
			for (int d = 0; d < pixDim; ++d){

				// Verde pistacho
				gfx_color(40, 40, 40);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(50, 50, 50);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(79, 79, 79);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

			 	// Negro
			 	gfx_color(57, 51, 32);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);



			}
		}
		if (i==11){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho
				gfx_color(50, 50, 50);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);

				// Verde oscuro
				gfx_color(79, 79, 79);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			 	// Blanco
			 	gfx_color(253, 246, 213);			 	
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);


			}
		}
		if (i==12){
			for (int d = 0; d < pixDim; ++d){
				// Verde pistacho

				gfx_color(247, 52, 43);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(40, 40, 40);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			}
		}

	}
}
void DibEne4(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo


	for (int i = 0; i < alto; ++i){

	gfx_color(0, 0, 255);


		if (i==0)
		{
			for (int d = 0; d < pixDim; ++d)
			{	// Naranja
				gfx_color(246, 149, 60);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==1)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Rosa claro
				gfx_color(232, 205, 251);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

				// Azul oscuro
				gfx_color(94, 51, 251);			 	
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			}
		}

		if (i==2)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Azul oscuro
				gfx_color(94, 51, 251);			 	
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
				// Azul morado
				gfx_color(139, 95, 252);			 	
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
				// Rosa claro
				gfx_color(232, 205, 251);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
				// Morado oscuro
				gfx_color(108, 71, 169);			 	
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
				// Rosa claro
				gfx_color(232, 205, 251);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==3)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Azul morado
				gfx_color(139, 95, 252);			 	
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
				// Rosa claro
				gfx_color(232, 205, 251);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				// Morado oscuro
				gfx_color(108, 71, 169);			 	
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
				// Rosa claro
				gfx_color(232, 205, 251);			 	
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
				// Azul oscuro
				gfx_color(94, 51, 251);			 	
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==4)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Azul oscuro
				gfx_color(94, 51, 251);			 	
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				// Azul morado
				gfx_color(139, 95, 252);			 	
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==5)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Rosa claro
				gfx_color(232, 205, 251);			 	
			 	gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+16*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Azul claro
				gfx_color(179, 195, 235);
			 	gfx_line(x+1*pixDim,y+(i*pixDim)+d,x+1*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+3*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+17*pixDim,y+(i*pixDim)+d,x+17*pixDim+arre,y+(i*pixDim)+d);


			 	// Azul un poco oscuro
			 	gfx_color(98, 133, 205);
			 	gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+2*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+16*pixDim,y+(i*pixDim)+d,x+16*pixDim+arre,y+(i*pixDim)+d);




			}
		}

		if (i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Naranja
				gfx_color(246, 149, 60);
			 	gfx_line(x+1*pixDim,y+(i*pixDim)+d,x+1*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+17*pixDim,y+(i*pixDim)+d,x+17*pixDim+arre,y+(i*pixDim)+d);


			 	// Morado oscuro
			 	gfx_color(64, 51, 138);
			 	gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+16*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==8)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Naranja
				gfx_color(246, 149, 60);
			 	gfx_line(x+3*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+7*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+13*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);

			 	// Morado oscuro
			 	gfx_color(64, 51, 138);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);


			}
		}

		if (i==9)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Morado oscuro
			 	gfx_color(64, 51, 138);
			 	gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);

			}
		}

		if (i==10)
		{
			for (int d = 0; d < pixDim; ++d)
			{	

				// Morado oscuro abajo
			 	gfx_color(109, 72, 168);
			 	gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+11*pixDim+arre,y+(i*pixDim)+d);
			 	
			 	// Morado oscuro
			 	gfx_color(64, 51, 138);
			 	gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);



			}
		}

		if (i==11)
		{
			for (int d = 0; d < pixDim; ++d)
			{	
				// Morado oscuro
			 	gfx_color(64, 51, 138);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
			 	gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);

			 	// Morado oscuro abajo
			 	gfx_color(109, 72, 168);
			 	gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);


			}
		}
	}
}
void DibP(int x, int y, int alto, int pixDim,int &hitJ, DatosJugador jugador){

	int arre=pixDim-1;//arreglo

	int color[3];      //blanco
	int color1[3];	   //gris
	int color2[3];	   //negro
	int color3[3];	   //azul oscuro
	int color4[3];	   //azul medio
	int color5[3];	   //azul claro
	int color6[3];	   //rojo

	switch(jugador.skin) //seleccionador de skin
	{
		case 1:
			if (hitJ>0)
			{
				color[0]=255;//color daño
				color[1]=150;
				color[2]=150;
				hitJ--;
			}else{
				color[0]=255;//color blanco
				color[1]=255;
				color[2]=255;
			}

			color1[0]=150;//color gris
			color1[1]=150;
			color1[2]=150;

			color2[0]=75;//color negro
			color2[1]=75;
			color2[2]=75;

			color3[0]=75;//color azul oscuro
			color3[1]=75;
			color3[2]=200;

			color4[0]=100;//color azul medio
			color4[1]=100;
			color4[2]=255;

			color5[0]=150;//color azul claro
			color5[1]=150;
			color5[2]=255;

			color6[0]=255;//color rojo
			color6[1]=0;
			color6[2]=0;
		break;
		case 2:
			if (hitJ>0)
			{
				color[0]=200;//color daño
				color[1]=50;
				color[2]=50;
				hitJ--;
			}else{
				color[0]=0;//color blanco
				color[1]=100;
				color[2]=0;
			}

			color1[0]=175;//color gris
			color1[1]=175;
			color1[2]=175;

			color2[0]=75;//color negro
			color2[1]=75;
			color2[2]=75;

			color3[0]=75;//color azul oscuro
			color3[1]=75;
			color3[2]=200;

			color4[0]=100;//color azul medio
			color4[1]=100;
			color4[2]=255;

			color5[0]=150;//color azul claro
			color5[1]=150;
			color5[2]=255;

			color6[0]=150;//color rojo
			color6[1]=0;
			color6[2]=150;
		break;
		case 3:
			if (hitJ>0)
			{
				color[0]=100;//color daño
				color[1]=100;
				color[2]=255;
				hitJ--;
			}else{
				color[0]=125;//color blanco
				color[1]=15;
				color[2]=15;
			}

			color1[0]=75;//color gris
			color1[1]=75;
			color1[2]=100;

			color2[0]=50;//color negro
			color2[1]=50;
			color2[2]=50;

			color3[0]=50;//color azul oscuro
			color3[1]=50;
			color3[2]=150;

			color4[0]=75;//color azul medio
			color4[1]=75;
			color4[2]=200;

			color5[0]=125;//color azul claro
			color5[1]=125;
			color5[2]=200;

			color6[0]=100;//color rojo
			color6[1]=50;
			color6[2]=0;
		break;
	}

	for (int i = 0; i < alto; ++i)
	{
		if (i==0)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color6[0], color6[1], color6[2]);
				gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			}
		}		
		if (i==1)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==2)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color5[0], color5[1], color5[2]);
				gfx_line(x+12*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
			}
		}

		if (i==3)
		{
			for (int d = 0; d < 4*pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color5[0], color5[1], color5[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==4)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color4[0], color4[1], color4[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==5)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color3[0], color3[1], color3[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color6[0], color6[1], color6[2]);
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+18*pixDim,y+(i*pixDim)+d,x+18*pixDim+arre,y+(i*pixDim)+d);

			}
		}
		if (i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+18*pixDim,y+(i*pixDim)+d,x+18*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==8)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
			 	gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+16*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+6*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+18*pixDim,y+(i*pixDim)+d,x+18*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color5[0], color5[1], color5[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}

		if (i==9)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+19*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+8*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+16*pixDim,y+(i*pixDim)+d,x+16*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color6[0], color6[1], color6[2]);
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+2*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+22*pixDim,y+(i*pixDim)+d,x+22*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color4[0], color4[1], color4[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==10)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+4*pixDim,y+(i*pixDim)+d,x+20*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+2*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+7*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+16*pixDim,y+(i*pixDim)+d,x+17*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+22*pixDim,y+(i*pixDim)+d,x+22*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+15*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color3[0], color3[1], color3[2]);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==11)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+1*pixDim,y+(i*pixDim)+d,x+23*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+15*pixDim,y+(i*pixDim)+d,x+19*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+2*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+22*pixDim,y+(i*pixDim)+d,x+22*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==12)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+1*pixDim,y+(i*pixDim)+d,x+23*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+19*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+11*pixDim,y+(i*pixDim)+d,x+13*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+21*pixDim,y+(i*pixDim)+d,x+22*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==13)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+0*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+20*pixDim,y+(i*pixDim)+d,x+24*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+19*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+1*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+21*pixDim,y+(i*pixDim)+d,x+23*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==14)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+0*pixDim,y+(i*pixDim)+d,x+4*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+20*pixDim,y+(i*pixDim)+d,x+24*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color2[0], color2[1], color2[2]);
				gfx_line(x+5*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+19*pixDim,y+(i*pixDim)+d,x+19*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+1*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+8*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+16*pixDim,y+(i*pixDim)+d,x+18*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+21*pixDim,y+(i*pixDim)+d,x+23*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==15)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color[0], color[1], color[2]);
				gfx_line(x+0*pixDim,y+(i*pixDim)+d,x+5*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+19*pixDim,y+(i*pixDim)+d,x+24*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color6[0], color6[1], color6[2]);
				gfx_line(x+10*pixDim,y+(i*pixDim)+d,x+10*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+14*pixDim,y+(i*pixDim)+d,x+14*pixDim+arre,y+(i*pixDim)+d);
				gfx_color(color1[0], color1[1], color1[2]);
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+21*pixDim,y+(i*pixDim)+d,x+22*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==16)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_color(color6[0], color6[1], color6[2]);
				gfx_line(x+2*pixDim,y+(i*pixDim)+d,x+3*pixDim+arre,y+(i*pixDim)+d);
				gfx_line(x+21*pixDim,y+(i*pixDim)+d,x+22*pixDim+arre,y+(i*pixDim)+d);
			}
		}
	}
}
void initialAnimation(char &answer) {

	system("clear");
	cout << "\n\n\n";
	usleep(100000);
	cout << "\t\t\033[0;32m █    ██  ▄▄▄          ██▓ ███▄    █ ██▒   █▓ ▄▄▄      ▓█████▄ ▓█████  ██▀███    ██████ \n";
	usleep(100000);
	cout << "\t\t\033[0;32m ██  ▓██▒▒████▄       ▓██▒ ██ ▀█   █▓██░   █▒▒████▄    ▒██▀ ██▌▓█   ▀ ▓██ ▒ ██▒▒██    ▒ \n";
	usleep(100000);
	cout << "\t\t\033[0;32m▓██  ▒██░▒██  ▀█▄     ▒██▒▓██  ▀█ ██▒▓██  █▒░▒██  ▀█▄  ░██   █▌▒███   ▓██ ░▄█ ▒░ ▓██▄   \n";
	usleep(100000);
	cout << "\t\t\033[0;32m▓▓█  ░██░░██▄▄▄▄██    ░██░▓██▒  ▐▌██▒ ▒██ █░░░██▄▄▄▄██ ░▓█▄   ▌▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n";
	usleep(100000);
	cout << "\t\t\033[0;32m▒▒█████▓  ▓█   ▓██▒   ░██░▒██░   ▓██░  ▒▀█░   ▓█   ▓██▒░▒████▓ ░▒████▒░██▓ ▒██▒▒██████▒▒\n";
	usleep(500000);
	cout << "\t\t\033[0;32m░▒▓▒ ▒ ▒  ▒▒   ▓▒█░   ░▓  ░ ▒░   ▒ ▒   ░ ▐░   ▒▒   ▓▒█░ ▒▒▓  ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n";
	usleep(500000);
	cout << "\t\t\033[0;32m░░▒░ ░ ░   ▒   ▒▒ ░    ▒ ░░ ░░   ░ ▒░  ░ ░░    ▒   ▒▒ ░ ░ ▒  ▒  ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n";
	usleep(500000);
	cout << "\t\t\033[0;32m ░░░ ░ ░   ░   ▒       ▒ ░   ░   ░ ░     ░░    ░   ▒    ░ ░  ░    ░     ░░   ░ ░  ░  ░  \n";
	usleep(500000);
	cout << "\t\t\033[0;32m   ░           ░  ░    ░           ░      ░        ░  ░   ░       ░  ░   ░           ░  \n";
	usleep(500000);
	cout << "\t\t\033[0;32m                                         ░              ░                               \n";
	usleep(500000);
	
	cout << "\n\n\t\t\t\t\t\t\u001b[34mPɾҽʂʂ ENTER ƚσ ƈσɳƚιɳυҽ...";
	cin.get();
}
void mainMenu(char name[4],int &opt,DatosJugador &jugador, int &cantE, bool &win, int &b,database data) {
	char ans;

	opt = 1;


	do {
		printLetter();
		clearbuffer();
		cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Pʅαყ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Iɳʂƚɾυƈƚισɳʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Cɾҽԃιƚʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Qυιƚ";
		if (!(opt<=4 & opt>=1)) {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ";
		}
		cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
		cin>>opt;
	}while (!(opt<=4 & opt>=1));
	switch (opt) {
	case 1:
		menuJugar(name,opt,jugador,cantE,win,b,data);
	break;
	case 2:
		instructions(ans,name);
		mainMenu(name,opt,jugador,cantE,win,b,data);
	break;
	case 3:
		credits(name,opt,jugador,cantE,win,b,data);
	break;
	case 4:
		cout << "\n\n\t\t\t\t\t\t\u001b[34mᎶᎧᎧᎴᏰᎩᏋ\n";
		exit(0);
	default:
	break;
	}
}
void printLetter(){
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\033[0;32m █    ██  ▄▄▄          ██▓ ███▄    █ ██▒   █▓ ▄▄▄      ▓█████▄ ▓█████  ██▀███    ██████ \n";
	cout << "\t\t\033[0;32m ██  ▓██▒▒████▄       ▓██▒ ██ ▀█   █▓██░   █▒▒████▄    ▒██▀ ██▌▓█   ▀ ▓██ ▒ ██▒▒██    ▒ \n";
	cout << "\t\t\033[0;32m▓██  ▒██░▒██  ▀█▄     ▒██▒▓██  ▀█ ██▒▓██  █▒░▒██  ▀█▄  ░██   █▌▒███   ▓██ ░▄█ ▒░ ▓██▄   \n";
	cout << "\t\t\033[0;32m▓▓█  ░██░░██▄▄▄▄██    ░██░▓██▒  ▐▌██▒ ▒██ █░░░██▄▄▄▄██ ░▓█▄   ▌▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n";
	cout << "\t\t\033[0;32m▒▒█████▓  ▓█   ▓██▒   ░██░▒██░   ▓██░  ▒▀█░   ▓█   ▓██▒░▒████▓ ░▒████▒░██▓ ▒██▒▒██████▒▒\n";
	cout << "\t\t\033[0;32m░▒▓▒ ▒ ▒  ▒▒   ▓▒█░   ░▓  ░ ▒░   ▒ ▒   ░ ▐░   ▒▒   ▓▒█░ ▒▒▓  ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n";
	cout << "\t\t\033[0;32m░░▒░ ░ ░   ▒   ▒▒ ░    ▒ ░░ ░░   ░ ▒░  ░ ░░    ▒   ▒▒ ░ ░ ▒  ▒  ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n";
	cout << "\t\t\033[0;32m ░░░ ░ ░   ░   ▒       ▒ ░   ░   ░ ░     ░░    ░   ▒    ░ ░  ░    ░     ░░   ░ ░  ░  ░  \n";
	cout << "\t\t\033[0;32m   ░           ░  ░    ░           ░      ░        ░  ░   ░       ░  ░   ░           ░  \n";
	cout << "\t\t\033[0;32m                                         ░              ░                               \n";
}
void credits(char name[4],int &opt,DatosJugador &jugador, int &cantE, bool &win, int &b,database data) {
	char ans1;
	do {
		printLetter();
		cout << "\n\n\t\t\t\t\t\t\u001b[34mAԃɾιáɳ Tҽɳԃҽɾσ Gαɾƈíα";
		cout << "\n\n\t\t\t\t\t\t\u001b[34mAʅҽʝαɳԃɾσ Bҽɳιƚσ Mαɾƈσʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34mJҽʂúʂ Pαɾɾα Gαɾƈíα";
		if (ans1!='e') {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
		}
		cout << "\n\n\t\t\t\t\t\t\u001b[34mExιƚ (e): ";
		cin >> ans1;
	}while(ans1!='e');
	mainMenu(name,opt,jugador,cantE,win,b,data);
}
void clearbuffer() {    
	char c;
	do {
		c = getchar();
	}while (c != '\n' && c != EOF);
}
void menuJugar(char name[4],int &opt, DatosJugador &jugador, int &cantE, bool &win, int &b,database data) {
	int score=0;
	opt = 1;
	int level=0;
	char ans;
	do{
	do {
		printLetter();
		cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Pԋαʂҽ 1";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Pԋαʂҽ 2";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Pԋαʂҽ 3";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
		if (!(opt<=4 & opt>=1)) {
			cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ";
		}
		cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
		cin>>opt;
	} while (!(opt<=4 & opt>=1));
	switch (opt){
		case 1:
			do {
				printLetter();
				cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Lҽʋҽʅ 1";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Lҽʋҽʅ 2";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Lҽʋҽʅ 3";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
				if (!(opt<=4 & opt>=1)) {
					cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ";
				}
				cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
				cin>>opt;
			} while (!(opt<=4 & opt>=1));

			switch (opt) {
			case 1:
				level = 11;
				introAnim();
				lvl1_1(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
			break;
			case 2:
				level = 12;
				introAnim();
				lvl1_2(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 3:
				level = 13;
				introAnim();
				lvl1_3(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 4:

				menuJugar(name,opt,jugador,cantE,win,b,data);
			break;
			default:
			break;
			}
		break;
		case 2:
			do {
				printLetter();
				cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Lҽʋҽʅ 1";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Lҽʋҽʅ 2";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Lҽʋҽʅ 3";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
				if (!(opt<=4 & opt>=1)) {
					cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ";
				}
				cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
				cin>>opt;
			} while (!(opt<=4 & opt>=1));

			switch (opt) {
			case 1:
				level = 21;
				introAnim();
				lvl2_1(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 2:
				level = 22;
				introAnim();
				lvl2_2(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 3:
				level = 23;
				introAnim();
				lvl2_3(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 4:
				menuJugar(name,opt,jugador,cantE,win,b,data);
			break;
			default:
			break;
			}
		break;
		case 3:
			do {
				printLetter();
				cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Lҽʋҽʅ 1";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Lҽʋҽʅ 2";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Lҽʋҽʅ 3";
				cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
				if (!(opt<=4 & opt>=1)) {
					cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ";
				}
				cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
				cin>>opt;
			} while (!(opt<=4 & opt>=1));

			switch (opt) {
			case 1:
				level = 31;
				introAnim();
				lvl3_1(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 2:
				level = 32;
				introAnim();
				lvl3_2(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 3:
				level = 33;
				introAnim();
				lvl3_3(score,jugador,cantE,win,b);
				stats(score,name,jugador,cantE,win,b,level,data,ans);
				
			break;
			case 4:
				menuJugar(name,opt,jugador,cantE,win,b,data);
			break;
			default:
			break;
			}
		break;
		case 4:
			mainMenu(name,opt,jugador,cantE,win,b,data);
		break;
		default:
		break;
	}
	}while(ans=='y');
}
void introAnim() {
	system("clear");
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\u001b[33m 333333333333333   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m3:::::::::::::::33 "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m3::::::33333::::::3"<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m3333333     3:::::3"<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m            3:::::3"<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m            3:::::3"<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m    33333333:::::3 "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m    3:::::::::::3  "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m    33333333:::::3 "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m            3:::::3"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m            3:::::3"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m3333333     3:::::3"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m3::::::33333::::::3"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m3:::::::::::::::33 "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m 333333333333333   "<< endl;

	usleep(1000000);
	system("clear");
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\u001b[33m 222222222222222    "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m2:::::::::::::::22  "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m2::::::222222:::::2 "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m2222222     2:::::2 "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m            2:::::2 "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m         2222::::2  "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m    22222::::::22   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m  22::::::::222     "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m 2:::::22222        "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m2:::::2             "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m2:::::2             "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m2:::::2       222222"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m2::::::2222222:::::2"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m2::::::::::::::::::2"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m22222222222222222222"<< endl;

	usleep(1000000);
	system("clear");
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\u001b[33m      1111111   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m     1::::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m    1:::::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m    111:::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m       1::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m       1::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m       1::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\u001b[33m       1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m       1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m       1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m       1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m       1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m    111::::::111"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m    1::::::::::1"<< endl;
	cout << "\t\t\t\t\t\t\u001b[33m    111111111111"<< endl;
	usleep(1000000);
}

void instructions(char &ans, char name[4]) {
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Welcome to UA Invaders, "<<name<<"!                      |"<< endl;
	cout << "\t\t\t\t\u001b[36m| I am going to explain to you how the game works.  |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Firstly, there are 3 different phases each        |"<< endl;
	cout << "\t\t\t\t\u001b[36m| phase with 3 levels of 3 different difficulties.  |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| I suggest you play the easy ones first,           |"<< endl;
	cout << "\t\t\t\t\u001b[36m| just to get in touch with the controls            |"<< endl;
	cout << "\t\t\t\t\u001b[36m| of the game.                                      |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| The program must be displayed with the terminal   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| in full screen and zooming in 3 times, so that    |"<< endl;
	cout << "\t\t\t\t\u001b[36m| the text and the menu are centered properly.      |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| The controls are simple:                          |"<< endl;
	cout << "\t\t\t\t\u001b[36m|  [<-][->]Use right and left arrow keys to move.   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|  Press the [Q] key to exit the game, be careful   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|  because you will lose the game automatically     |"<< endl;
	cout << "\t\t\t\t\u001b[36m|  without the possibility to come back.            |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| During the game, you will ride a ship and you     |"<< endl;
	cout << "\t\t\t\t\u001b[36m| will have to fight and kill the aliens that are   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| trying to invade the University of Alicante.      |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Your ship will have 3 lifes initially, although   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| this number of lifes will increase as the game    |"<< endl;
	cout << "\t\t\t\t\u001b[36m| becomes more and more difficult.                  |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Your ship will shoot bullets automatically in     |"<< endl;
	cout << "\t\t\t\t\u001b[36m| the direction of the enemies.                     |"<< endl;
	cout << "\t\t\t\t\u001b[36m| As you change from phase to phase, your ship will |"<< endl;
	cout << "\t\t\t\t\u001b[36m| I am going to explain to you how the game works.  |"<< endl;
	cout << "\t\t\t\t\u001b[36m| change its appearance.                            |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Now we will go through the enemies. At the        |"<< endl;
	cout << "\t\t\t\t\u001b[36m| beginning, the enemies will be simple and melee,  |"<< endl;
	cout << "\t\t\t\t\u001b[36m| but as you advance through the levels you will    |"<< endl;
	cout << "\t\t\t\t\u001b[36m| discover new enemies that can shoot you, or       |"<< endl;
	cout << "\t\t\t\t\u001b[36m| enemies that are more tough to kill.              |"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Simple and shooter enemies will die with 1 shot,  |"<< endl;
	cout << "\t\t\t\t\u001b[36m| but tank enemies will die with 2 shots and they   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| will change their appearance.                     |"<< endl;
	cout << "\t\t\t\t\u001b[36m| Also, as the difficulty increases, enemies may    |"<< endl;
	cout << "\t\t\t\t\u001b[36m| move faster or slower and a bigger amount of      |"<< endl;
	cout << "\t\t\t\t\u001b[36m| enemies may appear.                               |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| There are 2 different of bullets, small bullets   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| will substract 1 life and big bullets will        |"<< endl;
	cout << "\t\t\t\t\u001b[36m| substract 2 lifes.                                |"<< endl;
	cout << "\t\t\t\t\u001b[36m| You lose the game if you run out of lifes         |"<< endl;
	cout << "\t\t\t\t\u001b[36m| and you will be instakilled is an enemy reaches   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| your ship movement line.                          |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
	do {
	system("clear");
	cout << "\n\n\n";
	cout << "\t\t\t\t\u001b[36m                       .-----."<< endl;
	cout << "\t\t\t\t\u001b[36m                      | .===. |"<< endl;
	cout << "\t\t\t\t\u001b[36m                      |- 6 6 -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      ( <___> )"<< endl;
	cout << "\t\t\t\t\u001b[36m _________________ooo__|_____|______________________"<< endl;
	cout << "\t\t\t\t\u001b[36m|                                                   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| You win the game if you manage to kill all the    |"<< endl;
	cout << "\t\t\t\t\u001b[36m| enemies. Each enemy is assigned a determined      |"<< endl;
	cout << "\t\t\t\t\u001b[36m| amount of score, depending on the type of enemy   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| and at what level it appears. Also, every extra   |"<< endl;
	cout << "\t\t\t\t\u001b[36m| life that you finish the level with will sum      |"<< endl;
	cout << "\t\t\t\t\u001b[36m| 25 points to your score. Good luck, Have fun!     |"<< endl;
	cout << "\t\t\t\t\u001b[36m|______________________________ooo__________________|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |_ | _|"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |  |  |"<< endl;
	cout << "\t\t\t\t\u001b[36m                       |__|__|  "<< endl;
	cout << "\t\t\t\t\u001b[36m                       |- Y -|"<< endl;
	cout << "\t\t\t\t\u001b[36m                      (__| |__)"<< endl;
	usleep(1000000);
	cout << "\n\t\t\t\t\t\t\t\u001b[36mNext(n):";
	cin >> ans;
	if (ans!='n') {
		cout << "\t\t\t\t\t\t\u001b[36mINVALID OPTION";
	}
	}while(!(ans=='n'));
}
void gameOverAnim(char ans,char name[4],int score,DatosJugador jugador,int cantE, int b){
	system("clear");
	if (jugador.vida<0) {
		jugador.vida = 0;
	}
	cout << "\n\n";
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██████   █████  ███    ███ ███████ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██       ██   ██ ████  ████ ██      "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██   ███ ███████ ██ ████ ██ █████   "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██    ██ ██   ██ ██  ██  ██ ██      "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m ██████  ██   ██ ██      ██ ██████ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m                                       "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m ██████  ██    ██ ███████ ██████  "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██    ██ ██    ██ ██      ██   ██ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██    ██ ██    ██ █████   ██████  "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m██    ██  ██  ██  ██      ██   ██ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\u001b[31m ██████    ████   ███████ ██   ██ "<< endl << endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[31m    Name: "<< name << endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[31m    Score: "<< score << endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[31m    Lifes left: "<< jugador.vida << endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[31m    Enemies left: "<< cantE << endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[31m    Total bullets: "<< b << endl << endl;
	usleep(1000000);
	do {
	cout << "\n\t\t\t\t\t\t\u001b[31m      Next(n): ";
	cin >> ans;
	if (ans!='n'){
		cout << "\n\t\t\t\t\t\t\u001b[31m      Invalid option";
	}
	}while (ans!='n');
}
void victoryAnim(char ans,char name[4],int score,DatosJugador jugador, int b) {
	system("clear");
	if (jugador.vida<0) {
		jugador.vida = 0;
	}
	cout << "\n\n\n\n";

	cout << "\t\t\t\t\u001b[33m██    ██  ██████  ██    ██     ██     ██ ██ ███    ██ ██ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\u001b[33m ██  ██  ██    ██ ██    ██     ██     ██ ██ ████   ██ ██ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\u001b[33m  ████   ██    ██ ██    ██     ██  █  ██ ██ ██ ██  ██ ██ "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\u001b[33m   ██    ██    ██ ██    ██     ██ ███ ██ ██ ██  ██ ██    "<< endl;
	usleep(100000);
	cout << "\t\t\t\t\u001b[33m   ██     ██████   ██████       ███ ███  ██ ██   ████ ██ "<< endl << endl;
	usleep(100000);
	cout << "\t\t\t\t\t\t\u001b[33m      Name: "<<name<< endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[33m      Score: "<<score<< endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[33m      Lifes left: "<< jugador.vida << endl;
	usleep(1000000);
	cout << "\t\t\t\t\t\t\u001b[33m      Total bullets: "<< b << endl;
	usleep(1000000);
	do {
	cout << "\n\t\t\t\t\t\t\u001b[33m      Next(n): ";
	cin >> ans;
	if (ans!='n'){
		cout << "\n\t\t\t\t\t\t\u001b[33m      Invalid option";
	}
	}while (ans!='n');
	

}
void saveScore(database data,int level, char name[4], int score,char &ans){
	char arch[30];
	char ch;
	int count=0;
	int i;
	switch (level){
	case 11:
		strcpy(arch, "level1_1.txt");
		break;
	case 12:
		strcpy(arch, "level1_2.txt");
		break;
	case 13:
		strcpy(arch, "level1_3.txt");
		break;
	case 21:
		strcpy(arch, "level2_1.txt");
		break;
	case 22:
		strcpy(arch, "level2_2.txt");
		break;
	case 23:
		strcpy(arch, "level2_3.txt");
		break;
	case 31:
		strcpy(arch, "level3_1.txt");
		break;
	case 32:
		strcpy(arch, "level3_2.txt");
		break;
	case 33:
		strcpy(arch, "level3_3.txt");
		break;
	default:
		break;
	}

	ofstream file;
	file.open(arch, ios::app);

	file << name << " " << score << endl;
	file.close();

	ifstream infile;
	infile.open(arch);

	infile.get(ch);

	while (infile) {
		if (ch=='\n'){
			count++;
		}
		infile.get(ch);
	}
	infile.close();

	ifstream datain;
	datain.open(arch, ios::in);
	system("clear");
	cout << "\n\n\n";
	usleep(100000);
	cout << "\t\t\t\t\t\t\u001b[32m╦  ╔═╗╔═╗╔╦╗  ╔═╗╔═╗╔═╗╦═╗╔═╗╔═╗"<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\t\u001b[32m║  ╠═╣╚═╗ ║   ╚═╗║  ║ ║╠╦╝║╣ ╚═╗"<< endl;
	usleep(100000);
	cout << "\t\t\t\t\t\t\u001b[32m╩═╝╩ ╩╚═╝ ╩   ╚═╝╚═╝╚═╝╩╚═╚═╝╚═╝"<< endl;
	usleep(100000);


	for (i=0; i<count;i++){
		usleep(100000);
		datain >> data.nam >> data.punt;
		cout << "\n\t\t\t\t\t\t\t\u001b[34m"<<data.nam <<" "<< data.punt << endl;
	}
	do {
		cout << "\n\n\t\t\t\t\t\t\u001b[34mDo you want to play again? (y/n)";
		cin >> ans;
		if (ans!='y' && ans!='n'){
			cout << "\n\t\t\t\t\t\t\t\u001b[34mInvalid option";
		}

	}while (ans!='y' && ans!='n');
	if (ans=='n') {
		EPSanimation();
	}

}
void EPSanimation() {
	system("clear");
	cout << "\n\n\n\n";
	usleep(100000);
	cout << "\t\t\t\u001b[36m                                             .                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                                           ...                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                                         .....                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                  THANKS               .......                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                   FOR               ,,,,,,,,,                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                  PLAYING           ,,,,,,,,,,                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                                  ,,,,,,,,,,,,                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                                ,,,,,,,,,,,,,,                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                              .,,,,,,,,,,,,,,,                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                             *****************                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                           *******************                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                 *((**/  *********************                                  "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                 ##//  ******************%%%%%%%%%%%%%%/                        "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                ##(  .************#&&&&&&&&&&,  /#(((((((((((#/.                "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m                #/  ********&&&&&&% *%%%%%%%%(.                                 "<< endl;
	usleep(100000);
	cout << "\t\t\t\u001b[36m               #  ***%&&%#%%#,                                                  "<< endl;
	usleep(100000);
	exit(0);

}