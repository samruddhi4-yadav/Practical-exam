#include<GL/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

int x_start=100;
int y_start=100;
int x_end=400;
int y_end=400;

int choice=1;

void plotpoint(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
	

void ddaLine(int style)
{
	int dx=x_end-x_start;
	int dy=y_end-y_start;
	
	int count=0;
	
	int steps=abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	float xInc=dx/ (float) steps;
	float yInc=dy/(float) steps;
	
	float x=x_start;
	float y=y_start;
	
	for(int i=0;i<=steps;i++)
	{
			switch(choice)
			{
				case 1:
				plotpoint(round(x),round(y));//simple line
				break;
				case 2:
				if(count%10==0)
				plotpoint(round(x),round(y));//doted line
				break;
				case 3:
				if(count%10<5)
				plotpoint(round(x),round(y));//dashed line
				break;
	               }
		count++;
		x+=xInc;
		y+=yInc;
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ddaLine(choice);
	
	glFlush();
}

void menu(int option)
{
	choice=option;
	glutPostRedisplay();
}

void CreateMenu()
{
	glutCreateMenu(menu);
	glutAddMenuEntry("Simple line",1);
	glutAddMenuEntry("Doted Line",2);
	glutAddMenuEntry("Dashed Line",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init()
{
	 glClearColor(0.0,0.0,0.0,0.0);
	 glColor3f(1.0,1.0,1.0);
	 gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
	 glutInit(&argc,argv);
	 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	 glutInitWindowSize(500,500);
	 glutInitWindowPosition(100,100);
	 
	 glutCreateWindow("DDA line drawing algorithm");
	 init();
	 CreateMenu();
	 glutDisplayFunc(display);
	 glutMainLoop();
	 
	 return 0;
}
