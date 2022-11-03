#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
void myInit()
{
    glPointSize(2.0);
    gluOrtho2D(0.0, 600.0, 0.0, 400.0);
}
void Display()
{
    glLineWidth(2);
    glPointSize(1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(200, 200);
    glVertex2f(220, 200);
    glVertex2f(220, 240);
    glVertex2f(200, 240);
    glEnd();
    glFlush();

}
void floodfill(int x, int y, float* fc, float* ic) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] == ic[0] && color[1] == ic[1] && color[2] == ic[2])) {
        glColor3f(fc[0], fc[1], fc[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        floodfill(x + 1, y, fc, ic);
        floodfill(x - 1, y, fc, ic);
        floodfill(x, y + 1, fc, ic);
        floodfill(x, y - 1, fc, ic);
        floodfill(x + 1, y + 1, fc, ic);
        floodfill(x - 1, y - 1, fc, ic);
        floodfill(x - 1, y + 1, fc, ic);
        floodfill(x + 1, y - 1, fc, ic);
    }
}



void mouse(int btn, int state, int x, int y) {
    y = 400 - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            float ic[] = { 0,0,0 };
            float fc[] = { 1,0,1 };
            floodfill(x, y, fc, ic);
        }
    }
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("Flood filling algorithm");

    glutDisplayFunc(Display);
    glutMouseFunc(mouse);
    myInit();
    glutMainLoop();
}

