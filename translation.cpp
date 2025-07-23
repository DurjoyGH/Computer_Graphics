#include<GL/glut.h>
#include<cmath>

GLfloat triangle[3][2] = {
    {0.0, 0.5},
    {-0.5, -0.5},
    {0.5, -0.5}
};

GLfloat tx = 0.5, ty = 0.5;


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

    GLfloat translated_triangle[3][2];

    for(int i = 0; i < 3; i++) {
        translated_triangle[i][0] = triangle[i][0] + tx;
        translated_triangle[i][1] = triangle[i][1] + ty;
    }

    glColor3f(1.0, 0.0, 0.0);

    drawTriangle(translated_triangle);

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
    glutCreateWindow("2D Translation - FreeGLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}