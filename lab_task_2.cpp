#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

struct input
{
    float x, y;
};

vector<input> CP;
vector<input> BC;
int points = 200;

int binomialCoeff(int n, int k)
{
    if (k > n)
        return 0;
    if (k == 0 || k == n)
        return 1;
    int res = 1;
    for (int i = 1; i <= k; i++)
    {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}

input computeBP(float t)
{
    input p = {0.0f, 0.0f};
    int n = CP.size() - 1;
    for (int i = 0; i <= n; i++)
    {
        int coeff = binomialCoeff(n, i);
        float blend = coeff * pow(t, i) * pow(1 - t, n - i);
        p.x += blend * CP[i].x;
        p.y += blend * CP[i].y;
    }
    return p;
}

void computeBC()
{
    BC.clear();
    for (int i = 0; i <= points; i++)
    {
        float t = (float)i / points;
        BC.push_back(computeBP(t));
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(12.0);
    glColor3f(0.0, 0.9, 0.9);
    glBegin(GL_POINTS);
    for (const auto &pt : CP)
        glVertex2f(pt.x, pt.y);
    glEnd();

    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(2.0);
    glColor3f(0.8, 0.6, 0.9);
    glBegin(GL_LINE_STRIP);
    for (const auto &pt : CP)
        glVertex2f(pt.x, pt.y);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glLineWidth(4.0);
    glColor3f(1.0, 0.2, 0.7);
    glBegin(GL_LINE_STRIP);
    for (const auto &pt : BC)
        glVertex2f(pt.x, pt.y);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.1, 0.1, 0.15, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char **argv)
{
    CP = {
        {100, 100},
        {200, 500},
        {500, 500},
        {700, 100}};

    computeBC();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab Task - 2");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
