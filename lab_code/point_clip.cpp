#include<GL/glut.h>
#include<iostream>
using namespace std;
const float windowHeight = 700.0,windowWidth = 700.0;
float xmin = -150,ymin = -150,xmax = 150,ymax = 150;
float px, py,draw=1;
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
void plot_points() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    if (draw == 1)
    {
        glColor3f(1.0, 1.0, 0.0);
        glVertex2i(px, py);
    }
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(0, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmin, ymax);
    glVertex2i(xmax, ymax);
    glVertex2i(xmax, ymin);
    glEnd();
    glFlush();
}
void display()
{
    plot_points();
    cout << "enter 1 to clip the points" << endl;
    cin >> draw;
    draw = ((px >= xmin) && (px <= xmax) && (py <= ymax) && (py >= ymin));
}

int main(int argc, char** argv) {
    cout << "the middle white point is the origin" << endl;
    glutInit(&argc, argv);
    init();
    cout << "Enter the x, y co-ordinate of point to clip" << endl;
    cin >> px >> py;
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
