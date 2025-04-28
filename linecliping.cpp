#include <GL/glut.h>
#include <iostream>
using namespace std;

// Define region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Clipping window boundaries
float xmin = 100, ymin = 100, xmax = 400, ymax = 400;

// Line endpoints
float x1 = 50, y_1 = 250, x2 = 450, y2 = 350;

// Function to compute region code
int computeCode(float x, float y) {
    int code = INSIDE;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

// Cohen-Sutherland algorithm
void cohenSutherlandLineClip(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        }
        else if (code1 & code2) {
            break;
        }
        else {
            int codeOut;
            float x, y;

            codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(1.0, 0.0, 0.0); // Red color for clipped line
        glBegin(GL_LINES);
        glVertex2f(x1, y_1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0.0, 1.0, 0.0); // Green color for window
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    // Draw original line (optional, for understanding)
    /*glColor3f(0.0, 0.0, 1.0); // Blue color for original line
    glBegin(GL_LINES);
        glVertex2f(50, 250);
        glVertex2f(450, 350);
    glEnd();*/

    // Perform clipping
    cohenSutherlandLineClip(x1, y_1, x2, y2);

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1); // Background black
    gluOrtho2D(0, 500, 0, 500); // Coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

