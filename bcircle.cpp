#include<GL/glut.h>
#include <iostream>
using namespace std;

int xc,yc;
int r;

void plotPoint(int a,int b)
{
	glBegin(GL_POINTS);
	glVertex2i(xc+a,yc+b);
	glVertex2i(xc-a,yc+b);
	glVertex2i(xc+a,yc-b);
	glVertex2i(xc-a,yc-b);
	
	glVertex2i(xc+b,yc+a);
	glVertex2i(xc-b,yc+a);
	glVertex2i(xc+b,yc-a);
	glVertex2i(xc-b,yc-a);
	
	glEnd();
}

void bresenhamCircle()
{
	int a=0,b=r;
	int d=3-2*r;
	
	while(a<=b)
	{
		plotPoint(a,b);
		if(d<0)
			d+=4*a+6;
		else
		{
			d+=4*(a-b)+10;
			b--;
		}
		a++;
	}
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	bresenhamCircle();
}

void init()
{
	 glClearColor(0.0,0.0,0.0,0.0);
	 glColor3f(1.0,1.0,1.0);
	 gluOrtho2D(0,500,0,500);
}

int main(int argc,char**argv)
{
	cout<<"Enter the center point(xc,yc)";
	cin>>xc >>yc;
	
	cout<<"Enter the radius==";
	cin>> r;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Breasenham Circle drawing algorithm");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
		
