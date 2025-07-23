#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

GLfloat triangle[3][2] = {
    {0.5, 0.0},
    {1.5, 0.0},
    {1.0, 0.5},

};

void drawTriangle(GLfloat triangle[3][2])
{
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < 3; i++)
    {
        glVertex2f(triangle[i][0], triangle[i][1]);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    drawTriangle(triangle);

    // GLfloat reflected_triangle_x[3][2];

    // for(int i = 0; i < 3; i++) {
    //     reflected_triangle_x[i][0] = triangle[i][0];
    //     reflected_triangle_x[i][1] = -triangle[i][1];
    // }

    // glColor3f(1.0, 0.0, 0.0);

    // drawTriangle(reflected_triangle_x);

    GLfloat reflected_triangle_y[3][2];

    // for (auto &i : triangle)
    // {
    //     for (auto &j : i)
    //         cout << j << ' ';
    //     cout << endl;
    // }

    for (int i = 0; i < 3; i++)
    {
        reflected_triangle_y[i][0] = -triangle[i][0];
        reflected_triangle_y[i][1] = triangle[i][1];
    }

    //     for (auto &i : reflected_triangle_y)
    // {
    //     for (auto &j : i)
    //         cout << j << ' ';
    //     cout << endl;
    // }

    glColor3f(1.0, 1.0, 0.0); // Takbir Hasan owned the idea. Dujoy implemented the code.

    drawTriangle(reflected_triangle_y);

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Reflection - FreeGLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}