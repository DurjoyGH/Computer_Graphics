#include <GL/glut.h>
#include <cmath>

GLfloat originalPentagon[5][2] = {
    {5.0, 0.0},
    {15.0, 0.0},
    {20.0, 10.0},
    {10.0, 20.0},
    {0.0, 10.0}
};

GLfloat rotatedPentagon[5][2];
float angle = 0.0;

void rotatePentagon(float angleDegrees)
{
    float angleRad = angleDegrees * M_PI / 180.0;

    for (int i = 0; i < 5; i++)
    {
        float x = originalPentagon[i][0];
        float y = originalPentagon[i][1];

        rotatedPentagon[i][0] = 10 + (x - 10) * cos(angleRad) - (y - 10) * sin(angleRad);
        rotatedPentagon[i][1] = 10 + (x - 10) * sin(angleRad) + (y - 10) * cos(angleRad);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    rotatePentagon(angle);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++)
    {
        glVertex2f(rotatedPentagon[i][0], rotatedPentagon[i][1]);
    }
    glEnd();

    glPointSize(6.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(10.0, 10.0);
    glEnd();

    glFlush();
}

void update(int value)
{
    angle += 1.0;
    if (angle >= 360.0)
        angle -= 360.0;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-30.0, 30.0, -30.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pentagon Rotation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
