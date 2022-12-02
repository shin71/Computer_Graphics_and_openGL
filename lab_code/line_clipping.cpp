#include<GL/glut.h>
#include<iostream>
using namespace std;
const float windowHeight = 700.0,windowWidth = 700.0;
float xmin = -150,ymin = -150,xmax = 150,ymax = 150;
float xd1=INT_MIN,yd1,xd2=INT_MIN,yd2;
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2i(0, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();
    if (xd1 != INT_MIN && xd2 != INT_MIN) {
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(xd1, yd1);
        glVertex2i(xd2, yd2);
        glEnd();
    }
    glFlush();
}
void init() {
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Clipping");
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, 300, 1.0, -
        1.0);
}
int getRegionCode(float x, float y) {
    int c = 0;
    if (y > ymax) c = 8;
    if (y < ymin) c = 4;
    if (x > xmax) c = 2;
    if (x < xmin) c = 1;
    return c;
}
void cohen_Line(float x1, float y1, float x2, float y2) {
    int c1 = getRegionCode(x1, y1);
    int c2 = getRegionCode(x2, y2);
    float m = (y2 - y1) / (x2 - x1);
    while ((c1 | c2) > 0) {
        if ((c1 & c2) > 0) break;
        float xi = x1;
        float yi = y1;
        int c = c1;
        if (c == 0) {
            c = c2;
            xi = x2;
            yi = y2;
        }
        float x, y;
        if ((c & 8) > 0) {
            y = ymax;
            x = xi + 1.0 / m * (ymax - yi);
        }
        if ((c & 4) > 0) {
            y = ymin;
            x = xi + 1.0 / m * (ymin - yi);
        }
        if ((c & 2) > 0) {
            x = xmax;
            y = yi + m * (xmax -
                xi);
        }
        if ((c & 1) > 0) {
            x = xmin;
            y = yi + m * (xmin - xi);
        }
        if (c == c1) {
            xd1 = x;
            yd1 = y;
            c1 = getRegionCode(xd1, yd1);
        }
        if (c == c2) {
            xd2 = x;
            yd2 = y;
            c2 = getRegionCode(xd2, yd2);
        }
    }
    display();
}
void mykey(unsigned char key, int x, int y) {
    if (key == 'c') {
        cohen_Line(xd1, yd1, xd2, yd2);
        glFlush();
    }
}


int main(int argc, char** argv) {
    cout << "the middle white point is the origin" << endl;
    glutInit(&argc, argv);
    init();
    cout << "Enter the x, y co-ordinate of the line" << endl;
    cin >> xd1 >> yd1;
    cout << "Enter the x, y co-ordinate of the other end point for the line" << endl;
    cin >> xd2 >> yd2;
    glutDisplayFunc(display);
    cout << "press 'c' key to clip line" << endl;
    glutKeyboardFunc(mykey);
    glutMainLoop();
    return 0;
}
