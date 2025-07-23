#include <GL/freeglut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4f, 0.4f, 0.4f); // Gray color

    glLineWidth(3.0f);

    glBegin(GL_LINES);
    // Base
    glVertex2f(-0.6f, -0.8f); glVertex2f(0.6f, -0.8f);

    // Legs
    glVertex2f(-0.6f, -0.8f); glVertex2f(0.0f, 0.8f);
    glVertex2f(0.6f, -0.8f); glVertex2f(0.0f, 0.8f);

    // Cross bars
    glVertex2f(-0.4f, -0.4f); glVertex2f(0.4f, -0.4f);
    glVertex2f(-0.25f, 0.0f); glVertex2f(0.25f, 0.0f);
    glVertex2f(-0.1f, 0.4f); glVertex2f(0.1f, 0.4f);

    // Inner diagonals
    glVertex2f(-0.6f, -0.8f); glVertex2f(0.6f, -0.4f);
    glVertex2f(0.6f, -0.8f); glVertex2f(-0.6f, -0.4f);

    glVertex2f(-0.4f, -0.4f); glVertex2f(0.4f, 0.0f);
    glVertex2f(0.4f, -0.4f); glVertex2f(-0.4f, 0.0f);

    glVertex2f(-0.25f, 0.0f); glVertex2f(0.25f, 0.4f);
    glVertex2f(0.25f, 0.0f); glVertex2f(-0.25f, 0.4f);

    // Antenna
    glVertex2f(0.0f, 0.8f); glVertex2f(0.0f, 1.0f);

    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glColor3f(0.0f, 0.0f, 0.0f);         // Drawing color

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // 2D coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple 2D Eiffel Tower");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
