#include<GL/glut.h>
#include<cmath>

GLfloat triangle[3][2] = {
    {0.0, 0.5},
    {-0.5, -0.5},
    {0.5, -0.5}
};

GLfloat sx = 1.5, sy = 0.5;


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

    GLfloat scaled_triangle[3][2];

    for(int i = 0; i < 3; i++) {
        scaled_triangle[i][0] = triangle[i][0] * sx;
        scaled_triangle[i][1] = triangle[i][1] * sy;
    }

    glColor3f(1.0, 0.0, 0.0);

    drawTriangle(scaled_triangle);

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
    glutCreateWindow("2D Scaling - FreeGLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}