#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
int x_center, y_center;
float a, b;
void myInit()
{
    glPointSize(2.0);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}
void setPixel(int xcoordinate, int ycoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(x_center + xcoordinate, y_center + ycoordinate);
    glEnd();
    glFlush();
}
void plot(int x, int y)
{
    setPixel(x, y);
    setPixel(x, -y);
    setPixel(-x, y);
    setPixel(-x, -y);
}
void make_ellipse(float rx,float ry)
{
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;
    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) +
        (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy)
    {

        // Print points based on 4-way symmetry
        plot(x, y);
        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
        ((rx * rx) * ((y - 1) * (y - 1))) -
        (rx * rx * ry * ry);

    // Plotting points of region 2
    while (y >= 0)
    {

        // Print points based on 4-way symmetry
        plot(x, y);

        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}




void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    make_ellipse(a, b);
}

int main(int argc, char* argv[])
{
    cout << "enter center\n";
    cin >> x_center >> y_center;
    cout << "enter a and b i.e major and minor axis length resp\n";
    cin >> a >> b;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("midpoint ellipse Algorithim");

    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
}

