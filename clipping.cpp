#include <GL/glut.h>
#include <iostream>

float Xmin, Xmax, Ymin, Ymax;
float x1, y1_, x2, y2_;
bool lineInside = false;
bool clipNeeded = false;
bool lineInvisible = false;

float clippedX1, clippedY1, clippedX2, clippedY2;

const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

int computeCode(float x, float y) {
    int code = INSIDE;
    if (x < Xmin) code |= LEFT;
    else if (x > Xmax) code |= RIGHT;
    if (y < Ymin) code |= BOTTOM;
    else if (y > Ymax) code |= TOP;
    return code;
}

bool cohenSutherlandClip(float &x1, float &y1, float &x2, float &y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 | code2) == 0) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            float x, y;
            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (Ymax - y1) / (y2 - y1);
                y = Ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (Ymin - y1) / (y2 - y1);
                y = Ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (Xmax - x1) / (x2 - x1);
                x = Xmax;
            } else {
                y = y1 + (y2 - y1) * (Xmin - x1) / (x2 - x1);
                x = Xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    return accept;
}

void setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawRectangle() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(Xmin, Ymin);
    glVertex2f(Xmax, Ymin);
    glVertex2f(Xmax, Ymax);
    glVertex2f(Xmin, Ymax);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (lineInside) {
        setViewport(0, 0, 400, 600);
        drawRectangle();

        setViewport(400, 0, 400, 600);
        drawRectangle();
        drawLine(x1, y1_, x2, y2_, 1, 1, 1); 
    } else if (clipNeeded) {
        setViewport(0, 0, 366, 700);
        drawRectangle();

        setViewport(366, 0, 366, 700);
        drawRectangle();
        drawLine(x1, y1_, x2, y2_, 1, 1, 1);

        setViewport(632, 0, 366, 700);
        drawRectangle();
        drawLine(clippedX1, clippedY1, clippedX2, clippedY2, 1, 1, 1);
    } else if (lineInvisible) {
        setViewport(0, 0, 800, 600);
        drawRectangle();
    }

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    std::cout << "Enter clipping rectangle (Xmin Ymin Xmax Ymax): ";
    std::cin >> Xmin >> Ymin >> Xmax >> Ymax;

    std::cout << "Enter line start point (x1 y1): ";
    std::cin >> x1 >> y1_;

    std::cout << "Enter line end point (x2 y2): ";
    std::cin >> x2 >> y2_;

    int code1 = computeCode(x1, y1_);
    int code2 = computeCode(x2, y2_);

    if ((code1 | code2) == 0) {
        lineInside = true;
    } else {
        float cx1 = x1, cy1 = y1_, cx2 = x2, cy2 = y2_;
        if (cohenSutherlandClip(cx1, cy1, cx2, cy2)) {
            clipNeeded = true;
            clippedX1 = cx1;
            clippedY1 = cy1;
            clippedX2 = cx2;
            clippedY2 = cy2;
        } else {
            std::cout << "Line is completely outside and not visible.\n";
            lineInvisible = true;
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Clipping Demonstration");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}



//Clipping needed

// Xmin Ymin Xmax Ymax: 100 100 400 300
// x1 y1: 50 150
// x2 y2: 450 250


//Outside

// Xmin Ymin Xmax Ymax: 100 100 400 300
// x1 y1: 50 350
// x2 y2: 80 320


//Inside

// Xmin Ymin Xmax Ymax: 100 100 400 300
// x1 y1: 150 150
// x2 y2: 350 250

