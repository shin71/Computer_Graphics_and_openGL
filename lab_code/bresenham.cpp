#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
vector<int> points;int lines;
void myInit()
{
    glPointSize(2.0);
    gluOrtho2D(0.0, 320.0, 0.0, 240.0);
}
void setPixel(int xcoordinate, int ycoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate, ycoordinate);
    glEnd();
    glFlush();
}
void Bresenham(int x0,int y0,int xEnd,int yEnd)
{
    int dx = abs(xEnd - x0);
    int dy = abs(yEnd - y0);
    bool con = false;
    if (dy > dx)
    {
        con = true;
        swap(dy, dx);swap(x0, y0);swap(xEnd, yEnd);
    }
    if (x0 > xEnd)
    {
        swap(x0, xEnd);
        swap(y0, yEnd);
    }
    int two_dy = 2 * dy;
    int two_dy_minus_dx = 2 * (dy - dx);
    int p = 2*dy - dx;
    con ? setPixel(y0,x0): setPixel(x0, y0);
    while (x0 < xEnd)
    {
        x0++;
        if (p < 0)
        {p += two_dy;}
        else
        {
            p += two_dy_minus_dx;
            y0++;
        }
        con ? setPixel(y0, x0) : setPixel(x0, y0);
    }

}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < lines; i++)
    {
        Bresenham(points[i * lines], points[i * lines + 1], points[i * lines + 2], points[i * lines + 3]);
    }
}

int main(int argc, char* argv[])
{
    cin >> lines;
    points = vector<int>(lines * 4);
    for (int i = 0; i < lines; i++)
    {
        cin >> points[i * lines] >> points[i * lines + 1] >> points[i * lines + 2] >> points[i * lines + 3];
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bresenham Line Algorithim");

    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
}

