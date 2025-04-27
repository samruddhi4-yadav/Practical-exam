#include<GL/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

int p1=100;
int p2=100;
int p3=400;
int p4=400;

int choice=1;


void plotPoint(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void bresenhamLine(int style)
{
	int x=p1;
	int y=p2;
	
	int dx=abs(p3-p1);
	int dy=abs(p4-p2);
	int p=2*dy-dx;
	
	int xinc=(p3 > p1) ? 1:-1;
	int yinc=(p4 > p2) ? 1:-1;
	
	int count=0;
	
	if(dx>dy)
	{
		for(int i=0;i<dx;i++)
		{
			switch(style)
			{
				case 1:
				plotPoint(x,y);//simple line
				break;
				case 2:
				if(count%10==0)
				plotPoint(x,y);//doted line
				break;
				case 3:
				if(count%10<5)
				plotPoint(x,y);//dashed line
				break;
			}
			
			count++;
			
			x+=xinc;
			
			if(p<0)
				p +=2*dy;
			else
			{
				y+=yinc;
				p +=2*(dy-dx);
			}
		}
	}
	else
	{
		p=2*dx-dy;
		for(int i=0;i<dy;i++)
		{
		switch(style)
			{
				case 1:
				plotPoint(x,y);//simple line
				break;
				case 2:
				if(count%10==0)
				plotPoint(x,y);//doted line
				break;
				case 3:
				if(count%10<5)
				plotPoint(x,y);//dashed line
				break;
			}
			count++;
			y+=yinc;
			
			if(p<0)
				p +=2*dx;
			else
			{
				x+=xinc;
				p +=2*(dx-dy);
			}
		}
	}
	
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	bresenhamLine(choice);
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

int main(int argc, char** argv)
{
 	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Bresenham Line drawing algorith");
	init();
	CreateMenu();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
