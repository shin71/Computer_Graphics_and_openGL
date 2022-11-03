#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
void myInit()
{
    glPointSize(2.0);
    gluOrtho2D(0.0, 600.0, 0.0, 400.0);
}
void boundaryfill(int x,int y,vector<float>&fillColor,vector<float>&BoundaryColor)
{
    float currColor[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,currColor);
    vector<float> currColor1(currColor, currColor + 3);
    if ((currColor1 != fillColor)&&(currColor1!=BoundaryColor)) {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();

        boundaryfill(x - 1, y, fillColor, BoundaryColor);
        boundaryfill(x, y + 1, fillColor, BoundaryColor);
        boundaryfill(x + 1, y, fillColor, BoundaryColor);
        boundaryfill(x, y - 1, fillColor, BoundaryColor);
        boundaryfill(x - 1, y - 1, fillColor, BoundaryColor);
        boundaryfill(x + 1, y + 1, fillColor, BoundaryColor);
        boundaryfill(x + 1, y - 1, fillColor, BoundaryColor);
        boundaryfill(x - 1, y + 1, fillColor, BoundaryColor);
    }
}
void Display()
{
    glLineWidth(2);
    glPointSize(1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(200, 200);
    glVertex2f(200, 250);
    glVertex2f(250, 250);
    glVertex2f(250, 200);
    glEnd();
    vector<float> boundaryColor = { 1.0,1.0,1.0 };
    vector<float> fillColor = { 1.0,1.0,0.0 };
    boundaryfill(201,201,fillColor,boundaryColor);
    glFlush();

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("Boundary filling algorithm");

    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
}

