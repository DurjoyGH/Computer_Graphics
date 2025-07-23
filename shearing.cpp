#include <GL/glut.h>

GLfloat triangle[3][2] = {
    {0.0, 0.5},
    {-0.5, -0.5},
    {0.5, -0.5}
};

GLfloat shx = 0.5;
GLfloat shy = 0.5;

void drawTriangle(GLfloat tri[3][2]) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i][0], tri[i][1]);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    drawTriangle(triangle);

    // Shear in X-direction
    GLfloat shearX[3][2];
    for (int i = 0; i < 3; i++) {
        shearX[i][0] = triangle[i][0] + shx * triangle[i][1];
        shearX[i][1] = triangle[i][1];
    }

    glColor3f(0.0, 1.0, 1.0);
    drawTriangle(shearX);

    // Shear in Y-direction
    GLfloat shearY[3][2];
    for (int i = 0; i < 3; i++) {
        shearY[i][0] = triangle[i][0];
        shearY[i][1] = triangle[i][1] + shy * triangle[i][0];
    }

    glColor3f(1.0, 1.0, 0.0); 
    drawTriangle(shearY);

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
    glutCreateWindow("2D Shearing - FreeGLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
