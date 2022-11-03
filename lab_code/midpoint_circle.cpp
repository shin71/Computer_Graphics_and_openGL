#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
int x_center, y_center;
float radius;
void myInit()
{
    glPointSize(2.0);
    gluOrtho2D(0.0, 320.0, 0.0, 240.0);
}
void setPixel(int xcoordinate, int ycoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(x_center + xcoordinate,y_center + ycoordinate);
    glEnd();
    glFlush();
}
void plot(int x, int y)
{
    setPixel(x, y);
    setPixel(x, -y);
    setPixel(-x, y);
    setPixel(-x, -y);
    setPixel(y, x);
    setPixel(-y, x);
    setPixel(y, -x);
    setPixel(-y, -x);
}
void make_circle(float r)
{
    int x = 0, y = r;
    float p = (5.0 / 4.0) - r;
    if (r == int(r))
    {
        p = 1 - r;
    }
    
    while (y >= x)
    {
        plot(x, y);
        x++;
        p < 0.0 ? y = y : y -= 1;
        p < 0.0 ? p += (2 * x) + 1 : p += (2 * x) + 1 - (2 * y);
    }
}
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    make_circle(radius);}
int main(int argc, char* argv[])
{
    cin >> x_center >> y_center;
    cin >> radius;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("midpoint circle Algorithim");

    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
}

