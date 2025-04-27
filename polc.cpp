#include <GL/glut.h>
#include <iostream>
#include <vector>

struct Point {
    float x, y;
};

std::vector<Point> vertices; // Original polygon vertices
std::vector<Point> clipped;  // Temporary array for clipped vertices
Point p1, p2; // Clipping window corners (bottom-left and top-right)

void leftClip() {
    clipped.clear();
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        Point curr = vertices[i];
        Point next = vertices[(i + 1) % n];

        if (curr.x < p1.x && next.x >= p1.x) { // Outside to inside
            float y = (next.y - curr.y) / (next.x - curr.x) * (p1.x - curr.x) + curr.y;
            clipped.push_back({p1.x, y});
            clipped.push_back(next);
        }
        else if (curr.x >= p1.x && next.x >= p1.x) { // Inside to inside
            clipped.push_back(next);
        }
        else if (curr.x >= p1.x && next.x < p1.x) { // Inside to outside
            float y = (next.y - curr.y) / (next.x - curr.x) * (p1.x - curr.x) + curr.y;
            clipped.push_back({p1.x, y});
        }
    }
    vertices = clipped;
}

void rightClip() {
    clipped.clear();
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        Point curr = vertices[i];
        Point next = vertices[(i + 1) % n];

        if (curr.x > p2.x && next.x <= p2.x) { // Outside to inside
            float y = (next.y - curr.y) / (next.x - curr.x) * (p2.x - curr.x) + curr.y;
            clipped.push_back({p2.x, y});
            clipped.push_back(next);
        }
        else if (curr.x <= p2.x && next.x <= p2.x) { // Inside to inside
            clipped.push_back(next);
        }
        else if (curr.x <= p2.x && next.x > p2.x) { // Inside to outside
            float y = (next.y - curr.y) / (next.x - curr.x) * (p2.x - curr.x) + curr.y;
            clipped.push_back({p2.x, y});
        }
    }
    vertices = clipped;
}

void topClip() {
    clipped.clear();
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        Point curr = vertices[i];
        Point next = vertices[(i + 1) % n];

        if (curr.y > p2.y && next.y <= p2.y) { // Outside to inside
            float x = (next.x - curr.x) / (next.y - curr.y) * (p2.y - curr.y) + curr.x;
            clipped.push_back({x, p2.y});
            clipped.push_back(next);
        }
        else if (curr.y <= p2.y && next.y <= p2.y) { // Inside to inside
            clipped.push_back(next);
        }
        else if (curr.y <= p2.y && next.y > p2.y) { // Inside to outside
            float x = (next.x - curr.x) / (next.y - curr.y) * (p2.y - curr.y) + curr.x;
            clipped.push_back({x, p2.y});
        }
    }
    vertices = clipped;
}

void bottomClip() {
    clipped.clear();
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        Point curr = vertices[i];
        Point next = vertices[(i + 1) % n];

        if (curr.y < p1.y && next.y >= p1.y) { // Outside to inside
            float x = (next.x - curr.x) / (next.y - curr.y) * (p1.y - curr.y) + curr.x;
            clipped.push_back({x, p1.y});
            clipped.push_back(next);
        }
        else if (curr.y >= p1.y && next.y >= p1.y) { // Inside to inside
            clipped.push_back(next);
        }
        else if (curr.y >= p1.y && next.y < p1.y) { // Inside to outside
            float x = (next.x - curr.x) / (next.y - curr.y) * (p1.y - curr.y) + curr.x;
            clipped.push_back({x, p1.y});
        }
    }
    vertices = clipped;
}

void drawPolygon() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (const auto& pt : vertices) {
        glVertex2f(pt.x, pt.y);
    }
    glEnd();
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw clipping rectangle
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p1.x, p2.y);
        glEnd();

        // Perform clipping
        leftClip();
        rightClip();
        topClip();
        bottomClip();

        // Draw clipped polygon
        drawPolygon();
        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping rectangle
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glVertex2f(p1.x, p2.y);
    glEnd();

    // Draw original polygon
    drawPolygon();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    std::cout << "Enter Window Coordinates (bottom-left and top-right):\n";
    std::cout << "Enter P1 (x y): ";
    std::cin >> p1.x >> p1.y;
    std::cout << "Enter P2 (x y): ";
    std::cin >> p2.x >> p2.y;

    int n;
    std::cout << "Enter number of vertices: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        Point temp;
        std::cout << "Enter vertex " << i + 1 << " (x y): ";
        std::cin >> temp.x >> temp.y;
        vertices.push_back(temp);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping (C++)");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutMainLoop();

    return 0;
}

