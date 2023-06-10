#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>

//GLOBAL VARIABLES
int x, y, xline1, xline2, trackLength,speed, readhighscore=0;
long int score;
char msg[100];
struct enemycarPosition{
	int x1, x2, y1, y2;
} e;
struct mycarPosition{
	int x1, x2, y1, y2;
} m;
struct enemycarPosition1{
	int x1, x2, y1, y2;
} e1;
struct highsc{
	char name[20];
	long int hscore;
}h[5];
struct colors{
	int bgcolor;
	int textcolor;
	int ingame_bgcolor1;
	int ingame_bgcolor2;
	int ingame_textcolor;
}c;
int carShape;  int enemycarShape;
struct previous_player{
	char name[20];
	int len;
}pp;
//USER DEFINED FUNCTIONS
void setgraphics();                           //set the graphics
void startgame();                             //start game
void loadingscreen();                         //show laoding screen
void mainmenu();                              //show main menu
void draw(long int);                          //draw path, display score and speed
void mycar(int );                             //spawn player car accord to car position
void enemycar(int *);                         //spawn and move enemy car 1
void enemycar1(int *);                        //spawn and move enemy car 2
int collisionDetection(struct mycarPosition mc, struct enemycarPosition ec);//check collision of enemy car 1 with player car
int collisionDetection1(struct mycarPosition mc, struct enemycarPosition1 ec);//check collision of enemy car 2 with player car
int scoreincrease(long int, int);             //increase player car speed accord to score
void pause();                                 //show paused screen
void gameover(long int);                      //show game-over screen
void displayControls();                       //display player controls
void showHighscores();                        //display high scores
void readHighscore();                         //read highscores from file
void showCredits();                           //show credits screen
void takeuserdetails(long int);               //take users details
int updateHighscore();                        //update the highscores in file
int checkifscoredHigh(long int);              //check if player scored high
int readgamedata();                           //read current game data
void defaultColor();                          //set default color
void colorSelect(int, int);                   //set color
int updategamedata();                         //update current game data
void customize();                             //show customize screen
void customizeCar();                          //show customize car screen
void customizeEnemyCar();                     //show customize enemy car screen
void customizeTheme();                        //show customize theme screen
void resetsettings();                         //reset all settings to default
void resetgamedata();                         //reset game data to default
void resetHighscore();		              //reset highscore to 0

int main(){
	setgraphics();
	x=getmaxx();
	y=getmaxy();
	if (readgamedata()==0){
	resetgamedata();
	}else
	defaultColor();
	loadingscreen();
	showCredits();

	delay(3000);
	cleardevice();
	mainmenu();
	closegraph();
	return 0;
}
void defaultColor(){
	setbkcolor(7);
	setcolor(c.textcolor);
}
void colorSelect(int a, int b){
	setbkcolor(a);
	setcolor(b);
}
void setgraphics(){
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
}
void loadingscreen(){
	int i=0;
	cleardevice();
	colorSelect(c.textcolor,c.bgcolor);
	settextstyle(7,0,5);
	outtextxy(x/2-165,y/4,"Forza Horizon 6");
	delay(1000);
	settextstyle(7,0,1);
	outtextxy(x/2-45 ,y-120,"LOADING....") ;
	while (i!=200){                   	//loading symbol
		rectangle(x/2-90,y-85,x/2-100+i,y-75);
		rectangle(x/2-90 ,y-85,x/2+100,y-75);
		i++;
		delay(10);
	}
}
void mainmenu(){
	int selection=0;
	cleardevice();
	defaultColor();

	while(1){
	cleardevice();
	score=0;
	speed=1;
	settextstyle(4,0,4);
	outtextxy(x/2-150,20,"FORZA HORIZON 6");
	settextstyle(8,0,4 );
	outtextxy(x/2-250,90,"CONTROLS");
	settextstyle(8,0,2);
	outtextxy(x/2-250,150,"W=UPWARD");
	outtextxy(x/2-250,175,"S=DOWNWARD");
	outtextxy(x/2-250,200,"A=LEFTWARD");
	outtextxy(x/2-250,225,"D=RIGHTWARD");
	outtextxy(x/2-250,250,"P=PAUSE / RESUME");
	outtextxy(x/2-250,275,"X=EXIT");
	settextstyle(8,0,2);
	outtextxy(x/2-210,425,"PRESS M TO RETURN TO MAIN MENU");
	if (selection==0)
	{
	settextstyle(7,0,4);
	outtextxy(x/2+90,100,"PLAY");
	}
	else
	{
	settextstyle(7,0,3);
	outtextxy(x/2+90,100,"PLAY");
	}
	if (selection==1)
	{
	settextstyle(7,0,4);
	outtextxy(x/2+90,150,"HIGH SCORES");
	}
	else
	{
	settextstyle(7,0,3);
	outtextxy(x/2+90,150,"HIGH SCORES");
	}
	if (selection==2)
	{
	settextstyle(7,0,4);
	outtextxy(x/2+90,200,"CUSTOMIZE");
	}
	else
	{
	settextstyle(7,0,3);
	outtextxy(x/2+90,200,"CUSTOMIZE");
	}
	if (selection==3)
	{
	settextstyle(7,0,4);
	outtextxy(x/2+90,250,"EXIT");
	}
	else
	{
	settextstyle(7,0,3);
	outtextxy(x/2+90,250,"EXIT");
	}
	circle(x/2+80,115,5);
	circle(x/2+80 ,165,5);
	circle(x/2+80 ,215,5);
	circle(x/2+80 ,265,5);
	setfillstyle(SOLID_FILL,c.textcolor);
	floodfill(x/2+80 ,115+50*selection,c.textcolor);
	switch(getch()){
		case 'W':
		case 'w':
			if (selection==0)
				selection=3;
			else
				selection--;
			break;
		case 's':
		case 'S':
			if (selection==3)
				selection=0;
			else
				selection++;
			break;
		case 13:
			if (selection==0){
				startgame();
			}
			else if (selection==1){
				showHighscores();
			}
			else if (selection==2){
				customize();
			}
			else if (selection==3){
				exit(0);
			}
			else if (selection==4){
				showCredits();
			}
			else {
				exit(0);
			}
			break;
		default:
			break;
		}
	}
}

void startgame()
{
	int i , mycarLocation,collision=0,activateEnemy1=0;
	int *enemycarPos,*enemycarPos1;

	cleardevice();
	randomize();
	defaultColor();

	for(i=3;i!=0;i--)
	{
		cleardevice();
		settextstyle(7,0,3);
		sprintf(msg,"Starting in %d...",i);
		outtextxy(x/2-100,100,msg);
		delay(500);
	}

	colorSelect(7,1);
	settextstyle(7,0,1);
	xline1=x/2-75;
	xline2=x/2+75;
	trackLength=xline2-xline1;
	mycarLocation=0;
	*enemycarPos=0;
	*enemycarPos1=0;

	while(1)
	{
		cleardevice();
		draw(score);
		enemycar(enemycarPos); colorSelect(1,2);
		if(activateEnemy1==1)
		{
			enemycar1(enemycarPos1);
			*enemycarPos1+=speed+1;
			collision=collisionDetection(m,e)+collisionDetection1(m,e1);
		}
		else
		{
			collision=collisionDetection(m,e);
		}

		mycar(mycarLocation);

		if(collision==1)
		{
			gameover(score);
		}

		if(kbhit())
		{
			switch(getch())
			{
				case 'A':
				case 'a':
					if(mycarLocation!=-2)
					mycarLocation--;
					break;
				case 'd':
				case 'D':
					if(mycarLocation!=1)
					mycarLocation++;
					break;
				case 'p':
				case 'P':
					pause();
					break;
				case 'X':
				case 'x':
					exit(0);
					break;
				default:
					break;
			}

		}

		*enemycarPos=*enemycarPos+speed+1;
		score+=speed*1;
		if(*enemycarPos>y/2 )
		activateEnemy1=1;
		speed=speedincrease(score,speed);
		delay(5);
	}
}
void mycar(int carLocation)
{
		m.x1=xline1+(trackLength/3*carLocation)+75;
		m.x2=xline2+(trackLength/3*(carLocation+1))-75;
		m.y1=y-3;
		m.y2=y-50;
	if(carShape==0) //normal
	{    	setfillstyle(SOLID_FILL,7);
		bar(m.x1,m.y1-35,m.x2,m.y1);//part of car
		rectangle(m.x1,m.y1-35,m.x2,m.y1);//outline of the part
		setfillstyle(SOLID_FILL,RED);
		bar(m.x1+10,m.y1-35,m.x2-10,m.y1);
		rectangle(m.x1+10,m.y2+13,m.x2-10,m.y1);
		setfillstyle(SOLID_FILL,7);
		bar(m.x1+5,m.y2,m.x2-5,m.y2+13);
		rectangle(m.x1+5,m.y2,m.x2-5,m.y2+13);
		setfillstyle(SOLID_FILL,c.ingame_textcolor);
		bar(m.x1+3,m.y2+3,m.x1+5,m.y2+13);
		bar(m.x2-3,m.y2+3,m.x2-5,m.y2+13);

	}
	else if (carShape==1)   //rectangle
	{            setcolor(RED);
		     setfillstyle(9,WHITE);
		     rectangle(m.x1,m.y1,m.x2,m.y2);
		     floodfill((m.x1+m.x2)/2,(m.y1+m.y2)/2,RED);
	}
	else if(carShape==2)
		     //AUTO
	{  setcolor(RED);
	   setfillstyle(SOLID_FILL,YELLOW);
	   line((m.x1+m.x2)/2,m.y2,m.x1+10,m.y1-5);//we used three lines to make the triangle
	   line(m.x2-10,m.y1-5,m.x1+10,m.y1-5);
	   line((m.x1+m.x2)/2,m.y2,m.x2-10,m.y1-5);
	   floodfill((m.x1+m.x2)/2,m.y2+3,RED);
	   setcolor(RED);
	   setfillstyle(SOLID_FILL,WHITE);

	   rectangle(m.x2,m.y1-5,m.x2-10,m.y1+5); //wheels
	   floodfill(m.x2-5,m.y1,RED);
	   setcolor(RED);
	   setfillstyle(SOLID_FILL,WHITE);
	   rectangle(m.x1,m.y1-5,m.x1+10,m.y1+5);
	   floodfill(m.x1+5,m.y1,RED);
	   setcolor(RED);
	   setfillstyle(SOLID_FILL,WHITE);

	   rectangle((m.x1+m.x2)/2+5,m.y2-10,(m.x1+m.x2)/2-5,m.y2) ;
	   floodfill((m.x1+m.x2)/2,m.y2-5,RED);

	}
	else if(carShape==3)               //Spyder
	{              setcolor(14);                                                    setcolor(14); setfillstyle(SOLID_FILL,RED);
		ellipse((m.x1+m.x2)/2,(m.y1+m.y2)/2,0,360,(m.x2-m.x1)/2,(m.y1-m.y2)/2); line(m.x1,(m.y1+m.y2)/2  ,(m.x1)-10,(m.y1+m.y2)/2); line(m.x1-10,(m.y1+m.y2)/2,m.x1-20,(m.y1+m.y2)/2-10);//center of the SPYDER
		line(m.x2,(m.y1+m.y2)/2  ,(m.x2)+10,(m.y1+m.y2)/2); line(m.x2+10,(m.y1+m.y2)/2,m.x2+20,(m.y1+m.y2)/2-10);
		line(m.x1+5,(m.y1+m.y2)/2-10,m.x1-10,(m.y1+m.y2)/2-30); line(m.x2-5,(m.y1+m.y2)/2-10,m.x2+10,(m.y1+m.y2)/2-30);
		line(m.x1+5,(m.y1+m.y2)/2+10,m.x1-10,(m.y1+m.y2)/2+30); line(m.x2-5,(m.y1+m.y2)/2+10,m.x2+10,(m.y1+m.y2)/2+30); floodfill((m.x1+m.x2)/2,(m.y1+m.y2)/2 , 14);
	}
	else if(carShape==4)  //F1 car
	{
		setcolor(14);
		 setfillstyle(SOLID_FILL,YELLOW);
		 line((m.x1+m.x2)/2,m.y2+5,m.x2-5,m.y1); //similar to AUTO
		 line((m.x1+m.x2)/2,m.y2+5,m.x1+5,m.y1);
		 line(m.x2-5,m.y1,m.x1+5,m.y1);
		 floodfill((m.x1+m.x2)/2,m.y1-2,14);
		 setcolor(14);
		 setfillstyle(SOLID_FILL,LIGHTGRAY);
		 rectangle(m.x2,m.y1-5,m.x2-5,m.y1+5);
		 floodfill(m.x2-3,m.y1,14);
		 setcolor(14);
		 setfillstyle(SOLID_FILL,LIGHTGRAY);
		 rectangle(m.x1,m.y1+5,m.x1-5,m.y1-5);
		 floodfill(m.x1-3,m.y1,14);
		 setfillstyle(SOLID_FILL,RED);
		 bar(m.x2-5,m.y2+3,m.x1+5,m.y2+8);
		 setcolor(14);
		 setfillstyle(SOLID_FILL,LIGHTGRAY);
		 rectangle(m.x2,m.y2,m.x2-5,m.y2+10);
		 floodfill(m.x2-3,m.y2+5,14);
		 setcolor(14);
		 setfillstyle(SOLID_FILL,LIGHTGRAY);
		 rectangle(m.x1,m.y2,m.x1+5,m.y2+10);
		 floodfill(m.x1+3,m.y2+5,14);
	}
	else
	{
			setfillstyle(SOLID_FILL,7);
			bar(m.x1,m.y1-35,m.x2,m.y1);
			rectangle(m.x1,m.y1-35,m.x2,m.y1);
			setfillstyle(SOLID_FILL,RED);
			bar(m.x1+10,m.y1-35,m.x2-10,m.y1);
			rectangle(m.x1+10,m.y2+13,m.x2-10,m.y1);
			setfillstyle(SOLID_FILL,7);
		bar(m.x1+5,m.y2,m.x2-5,m.y2+13);
		rectangle(m.x1+5,m.y2,m.x2-5,m.y2+13);
		setfillstyle(SOLID_FILL,c.ingame_textcolor);
		bar(m.x1+3,m.y2+3,m.x1+5,m.y2+13);
		bar(m.x2-3,m.y2+3,m.x2-5,m.y2+13);
	}

}
  void enemycar(int *i)
{
	static int enemycarLoc;
	if(*i==0)
	{
		enemycarLoc=random(100)%3; //generates enemy car on random position
		e.x1=xline1+3+(trackLength/3)*enemycarLoc;
		e.x2=xline1+(trackLength/3*(enemycarLoc+1))-3;

	}
	e.y1=*i+3;
	e.y2=*i+48;
	if(enemycarShape==0)
	{
		setcolor(12);
		rectangle(e.x1,e.y1,e.x2,e.y1+33);
		rectangle(e.x1+5,e.y1+33,e.x2-5,e.y2);
		setfillstyle(SOLID_FILL,c.ingame_textcolor);
		bar(e.x1+3,e.y1+33,e.x1+5,e.y2-3);
		bar(e.x2-5,e.y1+33,e.x2-3,e.y2-3);
	}
	else if(enemycarShape==1){
		setcolor(12);
		setfillstyle(9,WHITE);
		rectangle(e.x1,e.y1,e.x2,e.y2);
		floodfill(e.x1+3,e.y1+3,12);
	}
	else if(enemycarShape==2)
	{                   setcolor(12);
		setfillstyle(7,3);
		rectangle(e.x1,e.y1,e.x2,e.y2);
		floodfill(e.x1+3,e.y1+3,12);
	}
	else if(enemycarShape==3)
	{
		setcolor(14); setfillstyle(SOLID_FILL,RED);
		circle((e.x1+e.x2)/2,(e.y1+e.y2)/2,15);
		floodfill((e.x1+e.x2)/2,(e.y1+e.y2)/2,14);
		line(e.x1,(e.y1+e.y2)/2  ,(e.x1)-10,(e.y1+e.y2)/2); line(e.x1-10,(e.y1+e.y2)/2,e.x1-20,(e.y1+e.y2)/2+10);
		line(e.x2,(e.y1+e.y2)/2  ,(e.x2)+10,(e.y1+e.y2)/2); line(e.x2+10,(e.y1+e.y2)/2,e.x2+20,(e.y1+e.y2)/2+10);
		line(e.x1+5,(e.y1+e.y2)/2-10,e.x1-10,(e.y1+e.y2)/2-30); line(e.x2-5,(e.y1+e.y2)/2-10,e.x2+10,(e.y1+e.y2)/2-30);
		line(e.x1+5,(e.y1+e.y2)/2+10,e.x1-10,(e.y1+e.y2)/2+30); line(e.x2-5,(e.y1+e.y2)/2+10,e.x2+10,(e.y1+e.y2)/2+30);
	}


	else if(enemycarShape==4)
	{
		setcolor(14);
	setfillstyle(SOLID_FILL,RED);
	line(e.x1-5,e.y1,(e.x1+e.x2)/2,e.y2-5);
	line((e.x1+e.x2)/2,e.y2-5,e.x2-5,e.y1);
	line(e.x2-5,e.y1,e.x1-5,e.y1);
	floodfill((e.x1+e.x2)/2,e.y2-10,14);
		setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e.x1-10,e.y1-5,e.x1-5,e.y1+5);
	floodfill(e.x1-8,e.y1,14);
		setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e.x2-5,e.y1-5,e.x2,e.y1+5);
	floodfill(e.x2-3,e.y1,14);
	bar(e.x1-5,e.y2-15,e.x2-5,e.y2-10);
		setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e.x1-10,e.y2-15,e.x1-5,e.y2-5);
	floodfill(e.x1-8,e.y2-10,14);
		setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e.x2-5,e.y2-15,e.x2,e.y2-5);
	floodfill(e.x2-3,e.y2-10,14);
	}

	else
	{       setcolor(12);
		rectangle(e.x1,e.y1,e.x2,e.y1+33);
		rectangle(e.x1+5,e.y1+33,e.x2-5,e.y2);
		setfillstyle(SOLID_FILL,c.ingame_textcolor);
		bar(e.x1+3,e.y1+33,e.x1+5,e.y2-3);
		bar(e.x2-5,e.y1+33,e.x2-3,e.y2-3);
	}

	if(e.y1>y)
	*i=-speed-1;
}

void enemycar1(int *j)
{
	static int enemycarLoc1;
	if(*j==0)
	{
		enemycarLoc1=random(100)%3;
		e1.x1=xline1+3+(trackLength/3)*enemycarLoc1;
		e1.x2=xline1+(trackLength/3*(enemycarLoc1+1))-3;
	}
	e1.y1=*j+3;
	e1.y2=*j+48;
	if(enemycarShape==0)
	{       setcolor(5);
		rectangle(e1.x1,e1.y1,e1.x2,e1.y1+33);
		rectangle(e1.x1+5,e1.y1+33,e1.x2-5,e1.y2);
		setfillstyle(SOLID_FILL,c.ingame_textcolor);
		bar(e1.x1+3,e1.y1+33,e1.x1+5,e1.y2-3);
		bar(e1.x2-5,e1.y1+33,e1.x2-3,e1.y2-3);

	}
	else if(enemycarShape==1)
	{       setcolor(5);
		rectangle(e1.x1,e1.y1,e1.x2,e1.y2);
	}
	else if (enemycarShape==2) {
		setcolor(12);
		setfillstyle(7,3);
		rectangle(e1.x1,e1.y1,e1.x2,e1.y2);
		floodfill(e1.x1+3,e1.y1+3,12);
	}
	else if(enemycarShape==3)
	{
		setcolor(14);
		setfillstyle(SOLID_FILL,RED);
		circle((e1.x1+e1.x2)/2,(e1.y1+e1.y2)/2,15);
		floodfill((e1.x1+e1.x2)/2,(e1.y1+e1.y2)/2,14);
		line(e1.x1,(e1.y1+e1.y2)/2  ,(e1.x1)-10,(e1.y1+e1.y2)/2); line(e1.x1-10,(e1.y1+e1.y2)/2,e1.x1-20,(e1.y1+e1.y2)/2+10);
		line(e1.x2,(e1.y1+e1.y2)/2  ,(e1.x2)+10,(e1.y1+e1.y2)/2); line(e1.x2+10,(e1.y1+e1.y2)/2,e1.x2+20,(e1.y1+e1.y2)/2+10);
		line(e1.x1+5,(e1.y1+e1.y2)/2-10,e1.x1,(e1.y1+e1.y2)/2-20); line(e1.x2-5,(e1.y1+e1.y2)/2-10,e1.x2+5,(e1.y1+e1.y2)/2-20);
		line(e1.x1+5,(e1.y1+e1.y2)/2+10,e1.x1-10,(e1.y1+e1.y2)/2+30); line(e1.x2-5,(e1.y1+e1.y2)/2+10,e1.x2+10,(e1.y1+e1.y2)/2+30);

	}
	else if(enemycarShape==4)
	{
	setcolor(14);
	setfillstyle(SOLID_FILL,RED);
	line(e1.x1-5,e1.y1,(e1.x1+e1.x2)/2,e1.y2-5);
	line((e1.x1+e1.x2)/2,e1.y2-5,e1.x2-5,e1.y1);
	line(e1.x2-5,e1.y1,e1.x1-5,e1.y1);
	floodfill((e1.x1+e1.x2)/2,e1.y2-10,14);
	setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e1.x1-10,e1.y1-5,e1.x1-5,e1.y1+5);
	floodfill(e1.x1-8,e1.y1,14);
	setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e1.x2-5,e1.y1-5,e1.x2,e1.y1+5);
	floodfill(e1.x2-3,e1.y1,14);
	bar(e1.x1-5,e1.y2-15,e1.x2-5,e1.y2-10);
	setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e1.x1-10,e1.y2-15,e1.x1-5,e1.y2-5);
	floodfill(e1.x1-8,e1.y2-10,14);
	setcolor(14);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(e1.x2-5,e1.y2-15,e1.x2,e1.y2-5);
	floodfill(e1.x2-3,e1.y2-10,14);
	}

	else
	{
	setcolor(5);
	rectangle(e1.x1,e1.y1,e1.x2,e1.y1+33);
	rectangle(e1.x1+5,e1.y1+33,e1.x2-5,e1.y2);
	setfillstyle(SOLID_FILL,c.ingame_textcolor);
	bar(e1.x1+3,e1.y1+33,e1.x1+5,e1.y2-3);
	bar(e1.x2-5,e1.y1+33,e1.x2-3,e1.y2-3);
	}
	if(e1.y1>y){
	*j=-speed-1;}
}
int collisionDetection(struct mycarPosition mc,struct enemycarPosition ec){
	if(ec.x1>mc.x2){
			return 0;
		       }
	else{
			if(ec.x2<mc.x1)
			return 0;
			else{
				if(ec.y1>mc.y1) return 0;
				else{
					if(ec.y2<mc.y2) return 0;
					else  return 1 ;
				     }
			    }
	   }
}
int collisionDetection1( struct mycarPosition mc , struct enemycarPosition1 ec ){
	if(ec.x1>mc.x2)
	return 0;

	else{
	       if(ec.x2<mc.x1)
	       return 0;
	       else{
			if(ec.y1>mc.y1)
			return 0;

			else{
			       if(ec.y2<mc.y2)
			       return 0;
			       else
			       return 1;
			}
	       }
	}
}
void draw(long int sc) {
	     setcolor(4);
	     line(xline1-30,0,xline1-30,y);
	     line(xline2+30,0,xline2+30,y);
	     sprintf(msg,"Score : %ld",sc);
	     outtextxy(xline2+99,y/2,msg);
}
int speedincrease(long int sc,int sp){
	switch(sp){
		case 1:
		if(sc>1000)
			sp++;
		  break;
		case 2:
		if(sc>2000)
			sp++;
		  break;
		case 3:
		if(sc>4000)
			sp++;
		  break;
		case 4:
		if(sc>8000)
			sp++;
		  break;
		case 5:
		if(sc>16000)
			sp++;
		  break;
		case 6:
		if(sc>32000)
			sp++;
		  break;
		case 7:
		if(sc>64000)
			sp++;
		  break;
		case 8:
		if(sc>120000)
			sp++;
		  break;
		case 9:
		if(sc>240000)
			sp++;
		  break;
		default:
			break;
	}
	return sp;
}
void pause(){
	int the_end=0;
	setfillstyle(SOLID_FILL,3);
	bar(xline1, y/2 -210, xline2, y/2 - 180);
	//Pause symbol
	line(xline1+50,y/2-200,xline1+50,y/2-190); //straight line
	line(xline1+50,y/2-200,xline1+60,y/2-195); //back slash line
	line(xline1+50,y/2-190,xline1+60,y/2-195); //front slash line

	outtextxy(xline1+70,y/2-207,"Paused");
	while(!the_end){
		switch(getch()){
		case 'p':
		case 'P':
			the_end=1;
			break;
		case 'm':
		case 'M':
			mainmenu();
			break;
		case 'x':
		case 'X':
			exit(0);
			break;
		default:
			break;
		}
	}
}
void gameover(long int sc){
	setfillstyle(SOLID_FILL,c.ingame_bgcolor2);
	bar(xline1,y/2-210,xline2,y/2-180);
	outtextxy(xline1+30,y/2-210,"Game Over");
	delay(10);
	getch();
	cleardevice();
	sprintf(msg,"Score: %ld",score);
	outtextxy(99,100,msg);
	if(checkifscoreHigh(sc)==1){
		outtextxy(99,130,"Congrats! You made your way to the highscore Table.");
		outtextxy(99,150,"Press any key to continue.");
		getch();
		takeuserdetails(score);
	}
	else{

	outtextxy(10,130,"Sorry! You could'nt make your way to the highscore table.");
	outtextxy(10,150,"Press any key to return to the mainmenu");
	getch();
	}
	mainmenu();
}



void showCredits(){
	cleardevice();
	settextstyle(7, 0, 4);
	outtextxy(x/2 - 50 , 50 , "CREDITS");
	settextstyle(7, 0, 3);
	outtextxy(200, 150, "This game is developed by:");
	outtextxy(200,200,"-Chaitanya Bhardwaj");
	outtextxy(200, 250, "-Rachit Jain");
	outtextxy(200, 300, "-Shrey Jain");
	outtextxy(200, 350, "-Het Sarsava");
	delay(3000);
	mainmenu();

}

void showHighscores(){
	int i;
	cleardevice();

	if (readhighscore == 0)
		readHighscore();

	settextstyle(7, 0, 4);
	outtextxy(x/2 -100, 100, "HighScore");

	settextstyle(7, 0, 3);

	for (i = 0; i<5; i++){
	       sprintf(msg, "%d. %s", i+1, h[i].name);
	       outtextxy(100, 150 + i*25, msg);
	       sprintf(msg, "%ld", h[i].hscore);
	       outtextxy(400, 150 + i*25, msg);
	}

	outtextxy(100, 150 + i*25 + 100, "Press any key to return to main menu:");
	getch();

}

void readHighscore(){

	size_t elements_read;
	FILE *fp;
	fp = fopen("highscore.bin", "rb");
	if (fp == NULL){
		resetHighscore();
	}
	else{
		elements_read = fread(&h, sizeof(struct highsc), 5, fp);
		fclose(fp);
		if (elements_read == 0){
			outtextxy(x/2 - 50, y/2, "Error");
			getch();
			mainmenu();
		}
		readhighscore = 1;
	    }
}

void takeuserdetails(long int sc){
	char inputbuf[20];
	int input_pos=pp.len;
	char c;
	int the_end=0;
	strcpy(inputbuf,pp.name);
	do {
		cleardevice();
		outtextxy(10,140,"Enter your name:");bar(10,160,300,200); outtextxy(15,175,inputbuf);
		c=getch();
		switch(c)
		{
			case 8:  //backspace
			if (input_pos)
			{
				input_pos--;
				inputbuf[input_pos]=0;
			}
			break;
			case 13: //return
			the_end=1;
			break;
			case 27: //escape = abort
			inputbuf[0]=0;
			the_end=1;
			break;
			default:
			if (input_pos<20-1&&c>=' '&&c<='~')
			{
				inputbuf[input_pos]=c;
				input_pos++;
				inputbuf[input_pos]=0;
			}
		}
	}
	while(!the_end);
	strcpy(pp.name,inputbuf);
	updategamedata();
	h[4].hscore=sc;
	strcpy(h[4].name,inputbuf);
	if (updateHighscore()==0){
		outtextxy(10,220,"Unable to update Highscore.");
		outtextxy(10,240,"Press any key to return to mainmenu.");
	}else{
		outtextxy(10,220,"Highscore succesfully updated.");
		outtextxy(10,240,"Press any key to return to mainmenu.");
	}
	getch();
}
int updateHighscore(){
	char ch[20];
	int i,j=4;
	long int k;
	size_t elements_written;
	FILE *fp;
	for (i=3;i>0,j>0;i--){
		if (h[j].hscore>h[i].hscore){
			k=h[j].hscore;
			h[j].hscore=h[i].hscore;
			h[i].hscore=k;
			strcpy(ch,h[j].name);
			strcpy(h[j].name,h[i].name);
			strcpy(h[i].name,ch);
			j=i;
		}
		else{
			break;
		}
	}
	fp=fopen("highscore.bin","wb");
	if (fp==NULL){
		return 0;
	}
	else{
		elements_written=fwrite(&h,sizeof(struct highsc),5,fp);
		fclose(fp);
		if(elements_written==0){
			return 0;
		}
		else{
			return 1;
		}
	}
}
int checkifscoreHigh(long int sc){
	if (readhighscore==0)
		readHighscore();
	if (sc>h[4].hscore)
		return 1;
	else
		return 0;
}
int readgamedata(){
	size_t elements_written;
	int n=0;
	FILE *fp;
	fp=fopen("gamedata.bin","rb");
	if (fp==NULL){
		return 0;
	}
	else{
		elements_written=fread(&c,sizeof(struct colors),1,fp);
		if (elements_written==0){
			return 0;
		}
		else{
		n++;
		}

		elements_written=fread(&carShape,sizeof(int),1,fp);
		if(elements_written==0){
			return 0;
		}
		else{
			n++;
		}

		elements_written=fread(&pp,sizeof(struct previous_player),1,fp);
		if (elements_written==0){
			return 0;
		}
		else{
			n++;
		}
		elements_written=fread(&enemycarShape,sizeof(int),1,fp);
		if(elements_written==0)
	       {	return 0 ; }
		else {
		n++;  }

		if (n==4){
			return 1;
		}
		else{
			return 0;
		}
	}
}
int updategamedata(){
	FILE *fp;
	fp=fopen("gamedata.bin","wb");
	if (fp==NULL){
		return 0;
	}else{
		fwrite(&c,sizeof(struct colors),1,fp);
		fwrite(&carShape,sizeof(int),1,fp);
		fwrite(&pp,sizeof(struct previous_player),1,fp);
		fwrite(&enemycarShape,sizeof(int),1,fp);
		return 1;
	}
}

void customize()
{
       int i = 0 ;
       while(1)
       {
       defaultColor();
       cleardevice();
       settextstyle(8,0,5);
       outtextxy(x/2-50,100,"Customize");
       if(i==0)
       {
       settextstyle(7,0,4);
       outtextxy(125,150,"Theme");
       }
       else
       {
       settextstyle(7,0,3);
       outtextxy(125,150,"Theme");
       }
       if(i==1)
       {
       settextstyle(7,0,4);
       outtextxy(125,200,"Car Shape");
       }
       else
       {
       settextstyle(7,0,3);
       outtextxy(125,200,"Car Shape");
       }
       if(i==2)
       {
       settextstyle(7,0,4);
       outtextxy(125,250,"Enemy Car Shape");
       }
       else
       {
       settextstyle(7,0,3);
       outtextxy(125,250,"Enemy Car Shape");
       }
       if(i==3)
       {
       settextstyle(7,0,4);
       outtextxy(125,300,"Reset all settings");
       }
       else
       {
       settextstyle(7,0,3);
       outtextxy(125,300,"Reset all settings");
       }
       if(i==4)
       {
       settextstyle(7,0,4);
       outtextxy(125,350,"Return");
       }
       else
       {
       settextstyle(7,0,3);
       outtextxy(125,350,"Return");
       }
	circle(100,165,3);
	circle(100,215,3);
	circle(100,265,3);
	circle(100,315,3);
	circle(100,365,3);
	setfillstyle(SOLID_FILL,c.textcolor);
	floodfill(100,165+i*50,c.textcolor);

	switch(getch())
	{
		case'w':
		case'W':if (i==0)
			i=4;
			else
			i--;
			break;
		case's':
		case'S':if(i==4)
			i=0;
			else
			i++;
			break;
		case'm':
		case'M':
			mainmenu();
			break;
		case 13:
			if(i==0)
			customizeTheme();
			else if(i==1)
			customizeCar();
			else if(i==2)
			customizeEnemyCar();
			else if(i==3)
			resetsettings();
			else
			mainmenu();
			break;
		default:
			break;
		}
	}
}
void customizeTheme()
{
	struct colors c1;
	int i = 0 , j;
	c1=c;
	while(1)
	{    cleardevice();
	     defaultColor();
	     settextstyle(7,0,4);
	     outtextxy(x/2-50,100,"THEME");

      if(i==0)
      {
       settextstyle(7,0,3);
       outtextxy(125,150,"Dark Ocean");
       }
       else
       {
       settextstyle(7,0,2);
       outtextxy(125,150,"Dark Ocean");
       }
       if (i==1)
       {
       settextstyle(7,0,3);
       outtextxy(125,200,"Gray Mountain");
       }
       else
       {
       settextstyle(7,0,2);
       outtextxy(125,200,"Gray Mountain");
       }
       if (i==2)
       {
       settextstyle(7,0,3);
       outtextxy(125,250,"Return");
       }
       else
       {
       settextstyle(7,0,2);
       outtextxy(125,250,"Return");
       }

       circle(100,165,3);
       circle(100,215,3);
       circle(100,265,3);

       setfillstyle(SOLID_FILL,c.textcolor);
       floodfill(100,165+i*50,c.textcolor);

	if(c.bgcolor==1)
	{
	       outtextxy(400,150,"(Current Theme)");
	       }else
	{
		outtextxy(400,200,"(Current Theme)");
	}
	switch(getch())
	{
		case'W':
		case'w':if (i==0)
			i = 2;
			else
			i--;
			break;
		case's':
		case'S':if(i==2)
			i=0;
			else
			i++;
			break;
		case'm':
		case'M':
			mainmenu();
			break;
		case 13:
			if(i==2)
			{
				customize();
			}
			else
			{
				outtextxy(100,400,"Updating");
				for(j=0; j<3 ; j++)
				{
					outtextxy(300+j*10,400,".");
					delay(1000);
				}
				if(i==0)
				{
					c.bgcolor=1;           //blue
					c.textcolor=15;        //white
					c.ingame_bgcolor1=0;   //black
					c.ingame_bgcolor2=8;   //darkgray
					c.ingame_textcolor=15; //white
				}
				else if(i==1)
				{
					c.bgcolor=15;           //white
					c.textcolor=1;          //blue
					c.ingame_bgcolor1=7;    //lightgray
					c.ingame_bgcolor2=8;    //darkgray
					c.ingame_textcolor=15;  //white
				}
				if(updategamedata()==0)
				{
					setcolor(RED);
					outtextxy(100,425,"Error try again");
					c=c1;
				}
				else
				{
				       outtextxy(100,425,"Successfully updated. Press any key");
				}
				getch();
			break;
		default:
			break;
		}
	}
   }
}

void customizeCar()
{
	int carshape;
	int i = 0 , j;

	carshape=carShape;

	while(1)
	{
		cleardevice();
		defaultColor();
		settextstyle(7,0,4);
		outtextxy(x/2-80,50,"MY CAR SHAPE");

		if(i==0)
		{
		settextstyle(7,0,2);
		outtextxy(125,100,"Normal");
		}
		else
		{
		settextstyle(7,0,1);
		outtextxy(125,100,"Normal");
		}
		if (i==1)
		{
		settextstyle(7,0,2);
		outtextxy(125,140,"Box Car");
		}
		else
		{
		settextstyle(7,0,2);
		outtextxy(125,140,"Box Car");
		}
		if (i==2)
		{
		settextstyle(7,0,2);
		outtextxy(125,180,"Auto");
		}
		else
		{
		settextstyle(7,0,1);
		outtextxy(125,180,"Auto");
		}
		if (i==3)
		{
		settextstyle(7,0,2);
		outtextxy(125,220,"Spyder");
		}
		else
		{
		settextstyle(7,0,1);
		outtextxy(125,220,"Spyder");
		}
		if (i==4)
		{
		settextstyle(7,0,2);
		outtextxy(125,260,"F1 Car");
		}
		else
		{
		settextstyle(7,0,1);
		outtextxy(125,260,"F1 Car");
		}
		if(i==5)
		{
		settextstyle(7,0,2);
		outtextxy(125,300,"Return");
		}
		else
		{
		settextstyle(7,0,1);
		outtextxy(125,300,"Return");
		}
		circle(115,110,3);
		circle(115,150,3);
		circle(115,190,3);
		circle(115,230,3);
		circle(115,270,3);
		circle(115,310,3);

		setfillstyle(SOLID_FILL,c.textcolor);
		floodfill(115,110+i*40,c.textcolor);

		outtextxy(400,110+carShape*40,"(Current Shape)");

		switch(getch())
		{
			case'W':
			case'w':if(i==0) i=5;
				else
				i--;
				break;
			case's':
			case'S':if(i==5) i=0;
				else
				i++;
				break;
			case'm':
			case'M':
				mainmenu();
				break;
			case 13:
				if(i==5)
					customize();
				else
				{
					outtextxy(100,400,"Updating");
					for(j=0; j<5 ; j++)
					{
						outtextxy(300+j*10,400,".");
						delay(500);
					}
					carShape=i;
					if(updategamedata()==0)
					{
						setcolor(RED);
						outtextxy(100,425,"Error try again.");
						carShape=carshape;
					}
					else
					{
						outtextxy(100,425,"Successfully updated. Press any key.");
					}
					getch();
				}
				break;
			default:
				break;
		}
	}
}
void customizeEnemyCar()
{
	int enemycarshape;
	int i = 0 , j;

	enemycarshape=enemycarShape;

	while(1)
	{
		cleardevice();
		defaultColor();
		settextstyle(7,0,4);
		outtextxy(x/2-100,50,"ENEMY CAR SHAPE");

		if(i==0)
		{
		settextstyle(7,0,3);
		outtextxy(125,150,"Normal");
		}
		else
		{
		settextstyle(7,0,2);
		outtextxy(125,150,"Normal");
		}
		if (i==1)
		{
		settextstyle(7,0,3);
		outtextxy(125,200,"Rectangle");
		}
		else
		{
		settextstyle(7,0,2);
		outtextxy(125,200,"Rectangle");
		}
		if (i==2)
		{
		settextstyle(7,0,3);
		outtextxy(125,250,"Block");
		}
		else
		{
		settextstyle(7,0,2);
		outtextxy(125,250,"Block");
		}
		if (i==3)
		{
		settextstyle(7,0,3);
		outtextxy(125,300,"Spyder");
		}
		else
		{
		settextstyle(7,0,2);
		outtextxy(125,300,"Spyder");
		}
		if (i==4)
		{
		settextstyle(7,0,3);
		outtextxy(125,350,"Return");
		}
		else
		{
		settextstyle(7,0,2);
		outtextxy(125,350,"Return");
		}

		circle(115,155,3);
		circle(115,205,3);
		circle(115,255,3);
		circle(115,305,3);
		circle(115,355,3);

		setfillstyle(SOLID_FILL,c.textcolor);
		floodfill(115,155+i*50,c.textcolor);

		outtextxy(400,150+enemycarShape*50,"(Current Shape)");

		switch(getch())
		{
			case'W':
			case'w':if(i==0) i=4;
				else
				i--;
				break;
			case's':
			case'S':if(i==4) i=0;
				else
				i++;
				break;
			case'm':
			case'M':
				mainmenu();
				break;
			case 13:
				if(i==4)
					customize();
				else
				{
					outtextxy(100,400,"Updating");
					for(j=0; j<5 ; j++)
					{
						outtextxy(300+j*10,400,".");
						delay(1000);
					}
				   enemycarShape=i;
					if(updategamedata()==0)
					{
						setcolor(RED);
						outtextxy(100,425,"Error try again.");
						enemycarShape=enemycarshape;
					}
					else
					{
						outtextxy(100,425,"Successfully updated. Press any key.");
					}
					getch();
				}
				break;
			default:
				break;
		}
	}
}

void resetsettings()
{
	int i;
	cleardevice();
	defaultColor();
	outtextxy(100,100,"Resetting all settings.");
	for(i=0 ; i<5 ; i++)
	{
		outtextxy(350+i*25,100,".");
		delay(1000);
	}

	resetHighscore();
	resetgamedata();

	outtextxy(100,125,"Successfully updated. Press any key");
	getch();
}

void resetgamedata()
{
	c.bgcolor=1;          //blue
	c.textcolor=15;       //white
	c.ingame_bgcolor1=0;  //black
	c.ingame_bgcolor2=8;  //darkgray
	c.ingame_textcolor=15;//white

	carShape=0;           //normal
	enemycarShape=0;

	strcpy(pp.name,"Player");
	pp.len=6;

	updategamedata();
}

void resetHighscore()
{
	int i ;
	char name[20];
	FILE *fp;

	for(i=0; i<5 ; i++)
	{
		strcpy(h[i].name,"Player");
		h[i].hscore=0;
	}

	fp=fopen("highscore.bin","wb");
	if(fp!=NULL)
	{
		fwrite(&h,sizeof(struct highsc),5,fp);
		fclose(fp);
	}
}
