# include "iGraphics.h"

#define speed 3;
bool f = true;
void collision();
void bFcollision();
void setSnakeColour();
int snakeSpeed = 8;
int moveTimer = 0,fruitTime=0;
bool up=false,down=false,left=false,right=true;
int fruitPosX,fruitPosY;
int bfruitTime=0;
int bfruitPosX,bfruitPosY;
int snakeBuilder=3;
int screen = 0;
bool BFruit=false;
int markPosX,markPosY;
bool snakeMark=false;
bool gameover=false;
int score=0;
char scores[10];
int r,g,b;
bool key1=true;
void menu();
void startGame();
void gameOver();
void instructions();
//void highscore();
void credits();
//void setdim();

FILE *from;
int sscores[5];
char show[6][6];
void High_scores()
{
	iClear();

	if((from = fopen( "HIGHSCORE.txt" , "r" )) == NULL)
	{
		from = fopen( "HIGHSCORE.txt" , "w" );
		for (int i=0; i<5; i++)
		{
			sscores[i]=0;
			fprintf( from,"%d\n", sscores[i] );
		}
		fclose(from);
	}

	from = fopen( "HIGHSCORE.txt" , "r" );
	int i=0;
	while (!feof(from))
	{
		fgets(show[i],5,from);
		i++;
	}
	fclose(from);

	iShowBMP(0,0,"highscore.bmp");
	
	iSetColor(0,0,0);

	iText(80,400,"1.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(80,340,"2.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(80,280,"3.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(80,220,"4.",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(80,160,"5.",GLUT_BITMAP_TIMES_ROMAN_24);

	for (int i=0; i<5; i++)	
		iText(110,400-i*60,show[i],GLUT_BITMAP_TIMES_ROMAN_24);
}


void GameOver(){

	if ((from = fopen( "HIGHSCORE.txt" , "r")) == NULL)
	{
		from = fopen( "HIGHSCORE.txt" , "w" );
		for (int i=0; i<5; i++)
		{
			sscores[i]=0;
			fprintf( from, "%d\n", sscores[i] );
		}
		fclose(from);
	}

	from = fopen( "HIGHSCORE.txt" , "r" );
	int i=0;
	while (!feof(from))
	{
		fscanf(from,"%d",&sscores[i]);
		i++;
	}
	fclose(from);
	
	for (i=0; i<5; i++){
		if (score>sscores[i])
		{
			for (int j=4; j>i; j--)
				sscores[j]=sscores[j-1];

			sscores[i]=score;
			break;
		}
	}

	from = fopen( "HIGHSCORE.txt" , "w" );
	for (int i=0; i<5; i++)
		fprintf( from, "%d\n", sscores[i] );

	fclose(from);
}


struct snakes
{
	int x;
	int y;
	bool show;

}snake[100];


void iDraw()
{
	iClear();
	if(screen==0) 
		menu();
	if(screen==1){ 
		startGame();
	}
	if(screen==2) 
		instructions();
	if(screen==3) 
		High_scores();
	if(screen==4) 
		credits();
	if(screen == 6)
		//GameOver();
		gameOver();
	//printf("%d",score);
	collision();
	bFcollision();
	setSnakeColour();
	iSetColor(0,0,255);
	sprintf(scores,"SCORE: %d",score);
	
}

void startGame(){
	
	iSetColor(255,255,102);
	iFilledRectangle(0,0,800,500);
	if(score!=0&&score%31==0){
		iSetColor(r,g,b);
	iFilledRectangle(0,0,800,500);

	}
	iSetColor(255,255,0);
	iText(350,550,scores,GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0,0,0);
	if(screen ==1){
		for(int i=0; i<100;i++){
			if(snake[i].show)
				iFilledCircle(snake[i].x,snake[i].y,10);
		}
	}
	if(score!=0&&score%20==0){
		iSetColor(r,g,b);
	for(int i=0; i<100;i++){
		if(snake[i].show)
			iFilledCircle(snake[i].x,snake[i].y,10);
	}

	}
	iSetColor(255,0,0);
	iFilledCircle(fruitPosX,fruitPosY,10);
	if(score>=5&&score%5==0&&BFruit==true){
	iSetColor(76,153,0);
	iFilledCircle(bfruitPosX,bfruitPosY,10);
	
	}
}
void menu(){
	iShowBMP(0,0,"Menu.bmp");
	//startGame();
}
void gameOver(){
	iShowBMP(0,0,"gameover.bmp");
	iSetColor(255, 255, 255);
	iText(590,45,"Back",GLUT_BITMAP_TIMES_ROMAN_24);
}
void instructions(){
	iShowBMP(0,0,"instruction.bmp");
}
/*void highscore(){
	iShowBMP(0,0,"highscore.bmp");
}*/
void credits(){
	iShowBMP(0,0,"credits.bmp");
}
/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	printf("%d %d\n", mx, my);	
	
	if(screen ==0)
	{
	
	   if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=0 && mx<=270 && my>=320 && my<=370)
		{
			printf("%d %d\n",mx,my);
			screen=1;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=0 && mx<=270 && my>=277 && my<=318)
		{
			screen = 2;
			printf("%d %d\n",mx,my);
            
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=0 && mx<=270 && my>=225 && my<=275)
		{
			screen = 3;
			printf("%d %d\n",mx,my);
			
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=0 && mx<=268 && my>=176 && my<=215)
		{
			
			screen = 4 ;
			printf("%d %d\n",mx,my);
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=0 && mx<=268 && my>=129 && my<=169)
		{
			exit(0);
			printf("%d %d\n",mx,my);
		}	
		
	}

	if(screen == 2)
	{
		
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=41 && mx<=777 && my>=282 && my<=3166)
		{
			screen = 0;
			printf("%d %d\n",mx,my);
		}
	}

	if(screen == 3)
	{
		
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=16 && mx<=151 && my>=9 && my<=52)
		{
			screen = 0;
			printf("%d %d\n",mx,my);
		}

	}

	if(screen ==4)
	{
		//printf("%d %d\n",mx,my);
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=684 && mx<=785 && my>=13 && my<=64)
		{
			screen = 0;
			printf("%d %d\n",mx,my);
		}
	}
	

	if(screen ==6)
	{
		//printf("%d %d\n",mx,my);
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=587 && mx<=637 && my>=42 && my<=66)
		{
			screen = 0;
			printf("%d %d\n",mx,my);
		}
	}
}


/*iPassiveMouseMove is called to detect and use 
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/
 
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == 'q')
	{
		//do something with 'q'
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	else if(key ==GLUT_KEY_LEFT)
		{
		right = false;
		left=true;
		up=false;
		down=false;
	}
	else if(key ==GLUT_KEY_RIGHT)
	{
		right = true;
		left=false;
		up=false;
		down=false;
	}
	else if(key ==GLUT_KEY_UP)
	{
		right = false;
		left=false;
		up=true;
		down=false;

	}
	else if(key ==GLUT_KEY_DOWN)
	{
		right = false;
		left=false;
		up=false;
		down=true;
	}
}


void setdim()
{
	int sum = 400;
		for(int i=0; i<100;i++){
			snake[i].y=250;
			snake[i].x=sum;
			sum -= 10;
			if(i ==0 || i==1 || i==2)
				snake[i].show = true;
			else
				snake[i].show = false;
		}
}

void timer()
{

	for (int i = snakeBuilder; i >0; i--) {
            snake[i].x = snake[(i - 1)].x;
            snake[i].y = snake[(i - 1)].y;
        }
	if(screen==1){

        if (left) {
			snake[0].x -= snakeSpeed;
			if(	snake[0].x>800||snake[0].x<0){
				GameOver();
				gameover=true;
				screen = 6;
			}
        }

        if (right) {
			snake[0].x += snakeSpeed;
			if(	snake[0].x>800||snake[0].x<0){
				GameOver();
				gameover=true;
				screen = 6;
			}
        }

        if (up) {
			snake[0].y += snakeSpeed;
			if(	snake[0].y>500||snake[0].y<0){
				GameOver();
				gameover=true;
				screen = 6;
			}
        }

        if (down) {
			snake[0].y -=snakeSpeed;
			if(	snake[0].y>500||snake[0].y<0){
				GameOver();
				gameover=true;
				screen = 6;
			}
        }
	}
}
void setSnakeColour(){
	r=rand()%255;
	g=rand()%255;
	b=rand()%255;
}
void setFruit(){
	fruitPosX = 20 + rand()%770;
	fruitPosY = 20 + rand()%470;
}
void setBfruit(){
	if(score>=5&&score%5==0&&f==true){
	bfruitPosX = 30+ rand()%770;
	bfruitPosY = 30+rand()%470;
	}
}
void bfruitTimer(){
	bfruitTime++;
	if(bfruitTime > 150){
		bfruitPosX = 20 + rand()%770;
		bfruitPosY = 20 + rand()%470;
		bfruitTime=0;
	}

}
void collision(){
	if (BFruit==false)
	{
	if(snake[0].x >= fruitPosX-10 && snake[0].x <= fruitPosX+10 && snake[0].y >= fruitPosY -10 && snake[0].y <= fruitPosY+10){
		fruitPosX = 20 + rand()%770;
		fruitPosY = 20 + rand()%470;
		snake[snakeBuilder].show = true;
		snakeBuilder++;
		score++;
		printf("%d",snake[0].x);
		if(score%5==0&&score>=5)
			BFruit=true;
	}
	}
}

void bFcollision(){

	if(BFruit==true){
	
			if(snake[0].x >= bfruitPosX-10 && snake[0].x <= bfruitPosX+10 && snake[0].y >= bfruitPosY-10  && snake[0].y <= bfruitPosY+10){
			
	bfruitPosX = 20+ rand()%770;
	bfruitPosY = 20+rand()%470;
	bfruitTime=0;
	snake[snakeBuilder].show = true;
	score+=10;
	BFruit=false;
	f=false;
			}		
	}
	
}

int main()
{ 
	if(!gameover){	
	setdim();
	setFruit();
	setBfruit();
	iSetTimer(25,timer);
	setSnakeColour();
	iSetTimer(25,bfruitTimer);
	}
	//PlaySound("ss", NULL, SND_LOOP | SND_ASYNC);
	iInitialize(800,600, "Snake");
	

	return 0;
}
