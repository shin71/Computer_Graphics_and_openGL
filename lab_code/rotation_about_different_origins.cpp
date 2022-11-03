#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
vector<vector<float>> points = {{-100,100,0},{-100,-100,100},{1,1,1}};
float windowWidth = 700.0;
float windowHeight = 700.0;
void myInit()
{
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glPointSize(2.0);
    glutCreateWindow("rotation_about_different_origins");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1*windowWidth/2,windowWidth/2,-1*windowHeight/2,windowHeight/2,1.0,-1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void mul_matrix(vector<vector<float>> &trans_matrix)
{
    auto [r1, c1] = make_pair(trans_matrix.size(),trans_matrix[0].size());
    auto [r2, c2] = make_pair(points.size(), points[0].size());
    vector<vector<float>> temp(r1, vector<float>(c2, 0));
    for (int i=0;i<r1;i++)
    {
        for (int j=0;j<c2;j++)
        {
            for (int k=0;k<c1;k++)
            {
                temp[i][j]+=trans_matrix[i][k] * points[k][j];
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
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < points[0].size(); j++)
    {
        float x = points[0][j];
        float y = points[1][j];
        glVertex2f(x,y);
    }
    glEnd();
    glFlush();
}
void Display()
{
    plot_points();
    float theta,tx=0,ty=0;
    cout<<"do you want to rotate about origin"<<endl;
    cout << "press 1 for yes or 0 for no" << endl;
    int choice; cin >> choice;
    if (choice == 0)
    { cout << "enter x y coordinates of new origin" << endl;
        cin >> tx >> ty;
    }
    vector<vector<float>> t ={{1,0,-tx},{0,1,-ty},{0,0,1}};
    mul_matrix(t);
    cout << "enter angle of rotation" << endl;
    cin >> theta;
    theta = (3.14 * theta) / 180.0;
    float s = sin(theta), c = cos(theta);
    vector<vector<float>>r = { {c,-s,0},{s,c,0},{0,0,1} };
    mul_matrix(r);
    t = { {1,0,tx},{0,1,ty},{0,0,1} };
    mul_matrix(t);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char* argv[]){
    cout << "that white square is the origin" << endl;
    glutInit(&argc, argv);
    myInit();
    glutDisplayFunc(Display);
    glutMainLoop();
}
