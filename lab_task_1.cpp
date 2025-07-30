#include <bits/stdc++.h>
#include <GL/freeglut.h>

using namespace std;

struct input
{
    float a, b;
};

vector<input> points(4);

void drawText(float x, float y, const string &text);

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(8.0);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS);
     for (int i = 0; i < 4; i++)
    {
        float r = 0.5 + 0.5 * sin(i);
        float g = 0.5 + 0.5 * cos(i);
        float b = 0.5 + 0.5 * sin(i + 1);

        glColor3f(r, g, b);
        glVertex2f(points[i].a, points[i].b);
    }
    glEnd();

     for (int i = 0; i < 4; i++)
    {
        float x = points[i].a;
        float y = points[i].b;

        stringstream ss;
        ss << "(" << (int)x << ", " << (int)y << ")";
        
        glColor3f(1.0, 1.0, 1.0);
        drawText(x + 5, y + 5, ss.str()); 
    }

    glFlush();
}

void init()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
}

void drawText(float x, float y, const string &text)
{
    glRasterPos2f(x, y);
    for (char ch : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, ch);
    }
}


int main(int argc, char **argv)
{
    cout << "Enter 4 points (x, y) within 0 <= x <= 800 and 0 <= y << 600\n";

    for (int i = 0; i < 4; i++)
    {
        while (true)
        {
            cout << "Point " << i + 1 << ": ";
            cin >> points[i].a >> points[i].b;

            if (points[i].a >= 0 && points[i].a <= 800 &&
                points[i].b >= 0 && points[i].b <= 600)
            {
                break;
            }

            else
            {
                cout << "Invalid input! Please enter x in [0,800] and y in [0,600]. Try again.\n";
            }
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab Task - 1");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}