#include<GL/glut.h>
#include<cmath>

GLfloat triangle[3][2] = {
    {0.0, 0.5},
    {-0.5, -0.5},
    {0.5, -0.5}
};

GLfloat angle = 45.0;


void drawTriangle(GLfloat triangle[3][2]) {
    glBegin(GL_TRIANGLES);

    for(int i = 0; i < 3; i++) {
        glVertex2f(triangle[i][0], triangle[i][1]);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    drawTriangle(triangle);

    GLfloat rad_angle = (angle * M_PI) / 180.0;

    GLfloat rotated_angle[3][2];

    for(int i = 0; i < 3; i++) {
        rotated_angle[i][0] = triangle[i][0] * cos(rad_angle) - triangle[i][1] * sin(rad_angle);
        rotated_angle[i][1] = triangle[i][0] * sin(rad_angle) + triangle[i][1] * cos(rad_angle);
    }

    glColor3f(1.0, 0.0, 0.0);

    drawTriangle(rotated_angle);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Rotation - FreeGLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}