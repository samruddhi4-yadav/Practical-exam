#include <bits/stdc++.h>
#include <GL/glut.h>
#include <cmath> 
#include <iostream>
class Point
{
public:
    int x, y;
    void setxy(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};
 
static int POINTSNUM = 0;
static Point points[4];
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0); 
    glColor3f(1.0, 1.0, 1.0); 
    glPointSize(4.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluOrtho2D(0.0, 600.0, 0.0, 480.0); 
 }

void setPoint(Point p)
{
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
}

void setline(Point p1, Point p2)
{
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y); // Set vertex coordinates
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush(); // Empty the buffer
}

Point setBezier(Point p1, Point p2, Point p3, Point p4, double u)
 
{
    Point p;
    double a1 = pow((1 - u), 3);          // (1 - u)^3
    double a2 = pow((1 - u), 2) * 3 * u;  // (1 - u)^2 * 3 * u
 
    double a3 = 3 * u * u * (1 - u);      // 3 * u^2 * (1 - u)
 
    double a4 = u * u * u;                // u^3
    p.x = a1 * p1.x + a2 * p2.x + a3 * p3.x + a4 * p4.x; // Compute the x-coordinate

 
    p.y = a1 * p1.y + a2 * p2.y + a3 * p3.y + a4 * p4.y; // Compute the y-coordinate
 
    return p;
}

// Mouse event

void mymouseFunction(int button, int state, int x, int y)
 
 
{
 
    if (state == GLUT_DOWN) 
 
    {
        points[POINTSNUM].setxy(x, 480 - y); 
        glColor3f(0.0, 0.0, 1.0); 
        setPoint(points[POINTSNUM]);
        glColor3f(1.0, 0.0, 0.0); 
        if (POINTSNUM > 0)
            setline(points[POINTSNUM - 1], points[POINTSNUM]);
        if (POINTSNUM == 3)
        {
            glColor3f(1.0, 1.0, 0.0); // Set the color of the Bezier curve
            Point p_current = points[0]; // Set as starting point
            for (double u = 0.0; u <= 1.0; u += 0.01) // Increase u increment to make smoother curve
            {
                Point P = setBezier(points[0], points[1], points[2], points[3], u); // Use 'u' here instead of 't'
                setline(p_current, P);
                p_current = P;
            }
            POINTSNUM = 0; // Reset after drawing the curve
 
        }
        else
        {
 
            POINTSNUM++; // Increment the point counter
        }
    }
}
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   
    glutInitWindowSize(600, 480);   
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier curve");
    init(); 
    glutMouseFunc(mymouseFunction); 
    glutMainLoop(); 
    return 0;
 
}

 

