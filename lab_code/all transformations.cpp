#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
vector<vector<float>> points = { {0,100,100,0},{0,0,100,100},{1,1,1,1} };
float windowWidth = 700.0;
float windowHeight = 700.0;
void myInit()
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glPointSize(2.0);
    glutCreateWindow("Transformation");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1 * windowWidth / 2, windowWidth / 2, -1 * windowHeight / 2, windowHeight / 2, 1.0, -1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void mul_matrix(vector<vector<float>>& trans_matrix)
{
    auto [r1, c1] = make_pair(trans_matrix.size(), trans_matrix[0].size());
    auto [r2, c2] = make_pair(points.size(), points[0].size());
    vector<vector<float>> temp(r1, vector<float>(c2, 0));
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                temp[i][j] += trans_matrix[i][k] * points[k][j];
            }
        }
    }
    points = temp;
}
void plot_points()
{
    glColor3f(1, 1, 1);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2i(0, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < points[0].size(); j++)
    {
        float x = points[0][j];
        float y = points[1][j];
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}
void Display()
{
    plot_points();
    int trans;
    cout << "press 0 for translation,1 for scaling,2 for rotation";
    cout << ",3 for sheering,4 for reflection about a line";
    cout << endl;
    cin >> trans;
    if (trans == 0)
    {
        float tx, ty;
        cout << "enter transalion terms" << endl;
        cin >> tx >> ty;
        vector<vector<float>> t = { {1,0,tx},{0,1,ty},{0,0,1} };
        mul_matrix(t);
    }
    if (trans == 1)
    {
        float sx, sy;
        cout << "enter scaling terms" << endl;
        cin >> sx >> sy;
        vector<vector<float>>s = { {sx,0,0},{0,sy,0},{0,0,1} };
        mul_matrix(s);
    }
    if (trans == 2)
    {
        float theta;
        cout << "enter angle of rotation" << endl;
        cin >> theta;
        theta = (3.14 * theta) / 180.0;
        float s = sin(theta), c = cos(theta);
        vector<vector<float>>r = { {c,-s,0},{s,c,0},{0,0,1} };
        mul_matrix(r);
    }
    if (trans == 3)
    {
        int fac, axis;
        float sx = 0, sy = 0;
        cout << "enter sheering factor" << endl;
        cin >> fac; sx = fac;
        cout << "enter axis for sheering 1 for x or 0 for y" << endl;
        cin >> axis;
        if (!axis) { swap(sx, sy); }
        vector<vector<float>> sheer = { {1,sy,0},{sx,1,0},{0,0,1} };
        mul_matrix(sheer);
    }
    if (trans == 4)
    {
        float m, c;
        cout << "enter slope and intercept of line" << endl;
        cin >> m >> c;
        vector<vector<float>> ref = {
              {(1 - (m * m)) / (1 + (m * m)),(2 * m) / (1 + (m * m)),(2 * m * -c) / (1 + (m * m))},
              {(2 * m) / (1 + (m * m)) ,((m * m) - 1) / (1 + (m * m)),(2 * c) / (1 + (m * m)) },
              {0,0,1}
        };
        mul_matrix(ref);

    }
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char* argv[]) {
    cout << "that white square is the origin" << endl;
    glutInit(&argc, argv);
    myInit();
    glutDisplayFunc(Display);
    glutMainLoop();
}
