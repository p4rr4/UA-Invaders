#include <iostream>
#include "gfx.h"
#include <unistd.h>
using namespace std;

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
	int x;
	int y;
	int yH;    //hitbox
	int ancho;
	int alto; 
	int altoh; //hitbox
	int skin;
	int vida;
};

void introAnim();
void initialAnimation(char &answer);
void mainMenu(int &opt, int &instr);
void printLetter();
void credits(int &opt, int &instr);
void clearbuffer();
void menuJugar(int &opt, int &instr,DatosJugador &jugador, int &cantE, bool &win, int &b, char &input);

void DefEne(int x, int y, int ancho, int alto, int f, int c, int e, DatosEnemigos enemigo[]);
void DibEne1(int x, int y, int alto, int pixDim);
void DibEne2(int x, int y, int alto, int pixDim);
void DibEne3(int x, int y, int alto, int pixDim);
void DibEne4(int x, int y, int alto, int pixDim);
void dibExp(int x, int y, int alto, int pixDim);
void DibEne3_1(int x, int y, int alto, int pixDim);

void DibP(int x, int y,int alto, int pixDim, int &hitJ, DatosJugador jugador);
char DetInput(char input);
void accion(char input, int windowX, DatosJugador &jugador);

void movBalas(int nb, int windowY, DatosBalas bala[], DatosEnemigos enemigo[], DatosJugador jugador);
void DibTodasBalas(int nb, DatosBalas bala[]);
void dibBala(int b, DatosBalas bala[]);
void DefBala(int b, int type, int pixDim, int e, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador jugador);

void dibCorazon(int x, int y);
void interfaz(int wX,int wY, DatosJugador jugador);
void matriz(int x0, int y0,int ancho, int alto, int sep,int enemigos[][10], int f, int c, int pixDim, DatosEnemigos enemigo[]);

void killing(int nb, int enemigos[][10],int f, int c, int &hitJ, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador &jugador, int &lastEne);
bool GameOver(int f, int c, DatosEnemigos enemigo[], DatosJugador jugador);
bool countE(int enemigos[][10],int f, int c, int &cant);

void animDrch(DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c);
void animIzq(DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c);
void animMatriz(DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c);

void stats(DatosJugador jugador,int cantE, bool win, int b);

// Levels
void lvl1(DatosJugador &jugador, int &cantE, bool &win, int &b, char &input);
void lvl2(DatosJugador &jugador, int &cantE, bool &win, int &b, char &input);
void lvl3(DatosJugador &jugador, int &cantE, bool &win, int &b, char &input);


int main()
{
	int nvl;
	DatosJugador jugador;
	bool win=0;
	int cantE;
	int b=0; //identificador de las balas
	char ans;
	int option,instr;
	char name[4];
	char input;
	instr = 0;

	initialAnimation(ans);
	printLetter();

	cout << "\n\n\t\t\t\t\t\t\u001b[34mEɳƚҽɾ ყσυɾ ɳαɱҽ (3 ʅҽƚƚҽɾʂ): ";
	cin >> name;
	mainMenu(option, instr);
	
	menuJugar(option, instr,jugador,cantE,win,b,input);
	
	return 0;
}

void lvl1(DatosJugador &jugador, int &cantE, bool &win, int &b, char &input){
	int windowX=1200;//X of the window
	int windowY=900;//Y of the window
	int x=70;//initial x of enemies
	int y=20;//initial y of enemies
	int sep=24;//separation between enemies
	const int F=8;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=10;//distancia de cada movimiento
	int pixDim=4;//dimension de los píxeles
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int ticks=50;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=250;
	int balasEnemigas4=400;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala [500];
	DatosEnemigos enemigo [F*C];

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


	int enemigos [F][C]=
	{{0,0,0,0,0,0,0,0,0,0},
	{0,1,2,2,1,0,0,1,2,0},
	{0,2,0,0,2,0,1,0,2,0},
	{0,2,0,0,2,0,0,0,2,0},
	{0,2,2,2,2,0,0,0,2,0},
	{0,2,0,0,0,0,0,0,2,0},
	{0,2,0,0,0,0,0,2,2,1},
	{0,0,0,0,0,0,0,0,0,0}};
	
	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,F,C);
}

void lvl2(DatosJugador &jugador, int &cantE, bool &win, int &b, char &input){
	int windowX=1200;//X of the window
	int windowY=900;//Y of the window
	int x=20;//initial x of enemies
	int y=20;//initial y of enemies
	int sep=10;//separation between enemies
	const int F=8;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=28;//distancia de cada movimiento
	int pixDim=4;//dimension de los píxeles
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int ticks=50;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=100;
	int balasEnemigas4=400;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala [500];
	DatosEnemigos enemigo [F*C];

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


	int enemigos [F][C]=
	{{1,0,2,2,2,0,1,0,1,1},
	{0,0,2,2,2,0,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0},
	{0,0,0,2,0,2,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0},
	{0,2,0,2,0,0,0,0,0,0},
	{0,0,2,2,2,0,3,3,0,0},
	{0,0,0,0,2,0,3,3,0,0}};
	
	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,F,C);
}

void lvl3(DatosJugador &jugador, int &cantE, bool &win, int &b, char &input){
	int windowX=1200;//X of the window
	int windowY=900;//Y of the window
	int x=220;//initial x of enemies
	int y=20;//initial y of enemies
	int sep=0;//separation between enemies
	const int F=15;//filas matriz enemigos
	const int C=10;//columnas matriz enemigos
	int dist=5;//distancia de cada movimiento
	int pixDim=4;//dimension de los píxeles
	int ancho=19*pixDim;//de cada enemigo unico (no tocar)
	int alto=13*pixDim;//de cada enemigo unico (no tocar)
	int ticks=50;//cantidad de ticks por cada movimiento del enemigo(no tocar)
	int t=300000;//tiempo
	int ticksBala=75;
	int balasEnemigas1=100;
	int balasEnemigas4=400;
	int velBalas=3;
	int lost=0;
	int hitJ;
	int lastEne;

	DatosBalas bala [500];
	DatosEnemigos enemigo [F*C];

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


	int enemigos [F][C]=
	{{4,0,0,1,0,1,0,0,0,4},
	{0,0,0,0,0,0,0,0,0,0},
	{0,2,0,2,0,0,2,0,2,0},
	{0,0,2,0,0,0,0,2,0,0},
	{0,0,0,2,0,0,2,0,0,0},
	{4,0,2,0,3,3,0,2,0,4},
	{0,0,0,3,3,3,3,0,0,0},
	{0,0,3,3,3,3,3,3,0,0},
	{0,0,0,3,3,3,3,0,0,0},
	{0,0,0,0,3,3,0,0,0,0},
	{0,4,0,0,0,0,0,0,4,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}};
	
	gfx_open(windowX, windowY, "UA invaders");

	animMatriz(jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,F,C);
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
void stats(DatosJugador jugador,int cantE, bool win, int b){
	if (win==1)
	{
		cout<<"YOU WIN"<<endl;
		cout<<jugador.vida<<" vidas restantes."<<endl;
	}else{
		cout<<"GAME OVER"<<endl;
		cout<<cantE<<" enemigos han quedado con vida."<<endl;
		cout<<jugador.vida<<" vidas restantes."<<endl;
	}
	cout<<"numero de balas totales: "<<b<<endl;
}
void animMatriz(DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c){

	while(input!='q' && lost==0 && win==0){

		animDrch(jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,f,c);
		yd=yd+alto;
		animIzq(jugador,enemigo,bala,lastEne,dist,hitJ,ancho,alto,sep,t,xd,yd,x,windowX,windowY,cantE,velBalas,ticksBala,b,pixDim,enemigos,balasEnemigas1,balasEnemigas4,k,ticks,lost,win,input,f,c);
		yd=yd+alto;
	}
}
void animDrch(DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c){
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

		killing(b,enemigos,f,c,hitJ, enemigo, bala, jugador,lastEne);
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
}
void animIzq(DatosJugador &jugador,DatosEnemigos enemigo[],DatosBalas bala[],int lastEne,int dist,int &hitJ,int ancho, int alto, int sep, int t,int &xd, int &yd,int &x,int windowX,int windowY,int &cantE,int velBalas,int ticksBala,int &b,int pixDim,int enemigos[][10],int balasEnemigas1,int balasEnemigas4,int k,int ticks,int &lost,bool &win,char &input,int f,int c){
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

		killing(b,enemigos,f,c,hitJ, enemigo, bala, jugador,lastEne);
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
}
void dibExp(int x, int y, int alto, int pixDim){
	int arre=pixDim-1;//arreglo

	gfx_color(255,0,0);

	for (int i = 0; i < alto; ++i)
	{
		
		if (i==5 || i==7)
		{
			for (int d = 0; d < pixDim; ++d)
			{
				gfx_line(x+9*pixDim,y+(i*pixDim)+d,x+9*pixDim+arre,y+(i*pixDim)+d);
			}
		}
		if (i==6)
		{
			for (int d = 0; d < pixDim; ++d)
			 {
			 	gfx_line(x+6*pixDim,y+(i*pixDim)+d,x+12*pixDim+arre,y+(i*pixDim)+d);
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
			if (enemigo[j+i*c].contador>0)
			{
				dibExp(x0+j*(ancho+sep), y0+i*(alto+sep),alto, pixDim);
				enemigo[j+i*c].contador-=1;
				DefEne(0,0,0,0,i,j,e, enemigo);
			}else{
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
					DefEne(0,0,0,0,i,j,e, enemigo);
				}
			}

			e++;
		}
	}
}
void killing(int nb, int enemigos[][10],int f, int c, int &hitJ, DatosEnemigos enemigo[], DatosBalas bala[], DatosJugador &jugador, int &lastEne){

	for (int b = 0; b < nb; ++b)
	{
		if (bala[b].type==1)
		{
			for (int i = 0; i < f; ++i)
			{
				for (int j = 0; j < c; ++j)
				{
					if (enemigo[j+i*c].y + enemigo[j+i*c].alto > bala[b].y && enemigo[j+i*c].x + enemigo[j+i*c].ancho > bala[b].x && enemigo[j+i*c].y < bala[b].y + bala[b].alto && enemigo[j+i*c].x < bala[b].x + bala[b].ancho)
					{
						if (enemigos[i][j]==3)//enemigo que tiene dos vidas
						{
							enemigos[i][j]=5;
							lastEne=lastE(enemigos,f,c);
						}else{
							enemigos[i][j]=0;
							enemigo[j+i*c].contador=30;
							lastEne=lastE(enemigos,f,c);
						}

						DefBala(b,0,0,0, enemigo, bala, jugador);

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
			case 3:
				if (hitJ>0)
				{
					color[0]=255;//color daño
					color[1]=150;
					color[2]=150;
					hitJ--;
				}else{
					color[0]=255;//color base
					color[1]=255;
					color[2]=255;
				}
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

void mainMenu(int &opt, int &instr) {
	
	printLetter();

	opt = 0;
	instr = 0;

	do {
		clearbuffer();
		cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Pʅαყ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Iɳʂƚɾυƈƚισɳʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Cɾҽԃιƚʂ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Qυιƚ";
		cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
		cin>>opt;
		if (!(opt<=4 & opt>=1)) {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
		}
	}while (!(opt<=4 & opt>=1));
	switch (opt) {
	case 1:
		instr = 1;
		break;
	case 2:
		//Instrucciones
		break;
	case 3:
		credits(opt, instr);
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

void credits(int &opt, int &instr) {
	char ans1;
	printLetter();
	cout << "\n\n\t\t\t\t\t\t\u001b[34mAԃɾιáɳ Tҽɳԃҽɾσ Gαɾƈíα";
	cout << "\n\n\t\t\t\t\t\t\u001b[34mAʅҽʝαɳԃɾσ Bҽɳιƚσ Mαɾƈσʂ";
	cout << "\n\n\t\t\t\t\t\t\u001b[34mJҽʂúʂ Pαɾɾα Gαɾƈíα";
	do {
		cout << "\n\n\t\t\t\t\t\t\u001b[34mExιƚ (e): ";
		cin >> ans1;
		if (ans1!='e') {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
		}
	}while(ans1!='e');
	mainMenu(opt, instr);



}

void clearbuffer() {    
	char c;
	do {
		c = getchar();
	}while (c != '\n' && c != EOF);
}

void menuJugar(int &opt, int &instr,DatosJugador &jugador, int &cantE, bool &win, int &b, char &input) {
	opt = 0;
	instr = 1;
	printLetter();
		do {
			cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Pԋαʂҽ 1";
			cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Pԋαʂҽ 2";
			cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Pԋαʂҽ 3";
			cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
			cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
			cin>>opt;
			if (!(opt<=4 & opt>=1)) {
				cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
			}
		} while (!(opt<=4 & opt>=1));
		switch (opt){
			case 1:
				printLetter();
				do {
					cout << "\n\n\t\t\t\t\t\t\u001b[34m1. Lҽʋҽʅ 1";
					cout << "\n\n\t\t\t\t\t\t\u001b[34m2. Lҽʋҽʅ 2";
					cout << "\n\n\t\t\t\t\t\t\u001b[34m3. Lҽʋҽʅ 3";
					cout << "\n\n\t\t\t\t\t\t\u001b[34m4. Bαƈƙ";
					cout << "\n\n\t\t\t\t\t\t\u001b[34mOρƚισɳ: ";
					cin>>opt;
					if (!(opt<=4 & opt>=1)) {
						cout << "\n\n\t\t\t\t\t\t\u001b[34mIɳʋαʅιԃ Oρƚισɳ\n";
					}
				} while (!(opt<=4 & opt>=1));
				switch (opt) {
				case 1:
					introAnim();
					lvl1(jugador,cantE,win,b,input);
					stats(jugador,cantE,win,b);
					break;
				case 2:
					introAnim();
					lvl2(jugador,cantE,win,b,input);
					stats(jugador,cantE,win,b);
					break;
				case 3:
					introAnim();
					lvl3(jugador,cantE,win,b,input);
					stats(jugador,cantE,win,b);
					break;
				case 4:
					menuJugar(opt,instr,jugador,cantE,win,b,input);
					break;
				default:
					break;
				}
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				mainMenu(opt, instr);
				break;
			default:
				break;
			}
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
	cout << "\t\t\t\t\t\t\t\u001b[33m  1111111   "<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m 1::::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\t\u001b[33m1:::::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\t\u001b[33m111:::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::1   "<< endl;  
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m   1::::l   "<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m111::::::111"<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m1::::::::::1"<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m1::::::::::1"<< endl;
	cout << "\t\t\t\t\t\t\t\u001b[33m111111111111"<< endl;

}