#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

struct Point {
    GLint x, y;
};

struct Color {
    GLfloat r, g, b;
};

// Global
Point p1 = {100, 100}, p2 = {300, 100}, p3 = {300, 300}, p4 = {100, 300};

// Function to draw line using DDA
void draw_dda(Point p1, Point p2, Color color) {
    GLfloat dx = p2.x - p1.x;
    GLfloat dy = p2.y - p1.y;
    GLfloat steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    GLfloat xInc = dx / steps;
    GLfloat yInc = dy / steps;
    GLfloat x = p1.x, y = p1.y;
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(1.0,1.0,1.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

// Get color of pixel
Color getPixelColor(GLint x, GLint y) {
    Color color;
    GLfloat pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);
    color.r = pixel[0];
    color.g = pixel[1];
    color.b = pixel[2];
    return color;
}

// Set color of pixel
void setPixelColor(GLint x, GLint y, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

// Flood Fill (4-Connectivity)
void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
    Color color = getPixelColor(x,y);
    if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b) {
        setPixelColor(x,y,newColor);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        floodFill(x+1,y,oldColor,newColor);
        floodFill(x-1,y,oldColor,newColor);
        floodFill(x,y+1,oldColor,newColor);
        floodFill(x,y-1,oldColor,newColor);
    }
}

// Boundary Fill (8-Connectivity)
void boundaryFill8(GLint x, GLint y, Color fillColor, Color boundaryColor1, Color boundaryColor2) {
    Color color = getPixelColor(x,y);
    if (!(color.r == boundaryColor1.r && color.g == boundaryColor1.g && color.b == boundaryColor1.b) &&
        !(color.r == boundaryColor2.r && color.g == boundaryColor2.g && color.b == boundaryColor2.b) &&
        !(color.r == fillColor.r && color.g == fillColor.g && color.b == fillColor.b)) {

        setPixelColor(x,y,fillColor);
        boundaryFill8(x+1,y,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x-1,y,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x,y+1,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x,y-1,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x+1,y+1,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x-1,y-1,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x+1,y-1,fillColor,boundaryColor1,boundaryColor2);
        boundaryFill8(x-1,y+1,fillColor,boundaryColor1,boundaryColor2);
    }
}

// Display Function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Color black = {0.0f,0.0f,0.0f}; 
    Color blue = {1.0f,1.0f,0.0f}; 

    draw_dda(p1,p2,black);
    draw_dda(p2,p3,blue);
    draw_dda(p3,p4,black);
    draw_dda(p4,p1,blue);

    glFlush();
}

// Menu choice
int fillChoice = 0;

// Mouse click event
void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Color oldColor = {1.0f,1.0f,1.0f}; // White
        Color newColor = {1.0f,0.0f,1.0f}; // Purple
        
        Color newColor1 = {0.0f,0.0f,1.0f};

        Color boundaryColor1 = {0.0f,0.0f,0.0f}; // Black
        Color boundaryColor2 = {1.0f,1.0f,0.0f}; // Blue

        if(fillChoice == 1) { 
            floodFill(x,480-y,oldColor,newColor1);
        }
        else if(fillChoice == 2) {
            boundaryFill8(x,480-y,newColor,boundaryColor1,boundaryColor2);
        }
    }
}

// Menu function
void menu(int option) {
    fillChoice = option;
}

// Main
int main(int argc, char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Flood Fill and Boundary Fill Combined");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    // Create Menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Flood Fill",1);
    glutAddMenuEntry("Boundary Fill",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

