#include<GL/glut.h>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
GLint x0, y0, xEnd, yEnd;
inline GLint round(const GLfloat a){return GLint(a + 0.5);}
void myInit()
{
    glPointSize(1.5);
    gluOrtho2D(0.0, 320.0, 0.0, 240.0);
}
void setPixel(GLint xcoordinate, GLint ycoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate, ycoordinate);
    glEnd();
    glFlush();
}
void lineDDA(GLint x0, GLint y0, GLint xEnd, GLint yEnd)
{
    GLint dx = abs(xEnd - x0);
    GLint dy = abs(yEnd - y0);
    GLint steps, k;
    GLfloat xIncrement, yIncrement, x = x0, y = y0;

    steps = dx > dy ? dx : dy;

    xIncrement = GLfloat(dx) / GLfloat(steps);
    yIncrement = GLfloat(dy) / GLfloat(steps);
    setPixel(round(x), round(y));
    for (k = 1; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x), round(y));
    }
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    lineDDA(x0, y0, xEnd, yEnd);
}

int main(int argc, char* argv[])
{
    x0 = y0 = 9.0;
    xEnd = yEnd = 180.0;
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DDA Line Algorithim");

    glutDisplayFunc(Display);
    myInit();
    glutMainLoop();
}

