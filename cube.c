#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

GLfloat xmove = 0, ymove = 0;
int xspin = 0, yspin = 0;

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(xmove, ymove, 1);
    glRotatef(xspin, 1, 0, 0);
    glRotatef(yspin, 0, 1, 0);

    glBegin(GL_QUADS); // front
    glVertex3f(50, -50, -50);
    glColor3d(0.0, 1.0, 0.0);
    glVertex3f(50, 50, -50);
    glVertex3f(-50, 50, -50);
    glColor3d(1.0, 1.0, 0.0);
    glVertex3f(-50, -50, -50);
    glEnd();

    glBegin(GL_QUADS); //back
    glVertex3f(50, -50, 50);
    glColor3d(1.0, 0.5, 0.0);
    glVertex3f(50, 50, 50);
    glVertex3f(-50, 50, 50);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3f(-50, -50, 50);
    glEnd();

    glBegin(GL_QUADS); //right
    glVertex3f(50, -50, -50);
    glColor3d(1.0, 0.0, 1.0);
    glVertex3f(50, 50, -50);
    glVertex3f(50, 50, 50);
    glColor3d(0.0, 0.0, 1.0);
    glVertex3f(50, -50, 50);
    glEnd();

    glBegin(GL_QUADS); //left
    glVertex3f(-50, -50, 50);
    glColor3d(1.0, 0.5, 1.0);
    glVertex3f(-50, 50, 50);
    glVertex3f(-50, 50, -50);
    glColor3d(0.0, 1.5, 0.0);
    glVertex3f(-50, -50, -50);
    glEnd();

    glBegin(GL_QUADS); // top
    glVertex3f(50, 50, 50);
    glColor3d(1.0, 1.0, 0.0);
    glVertex3f(50, 50, -50);
    glVertex3f(-50, 50, -50);
    glColor3d(1.0, 0.0, 0.5);
    glVertex3f(-50, 50, 50);
    glEnd();

    glBegin(GL_QUADS); // bottom
    glVertex3f(50, -50, -50);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3f(50, -50, 50);
    glVertex3f(-50, -50, 50);
    glColor3d(0.5, 0.5, 1.0);
    glVertex3f(-50, -50, -50);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void timer() {
    glutPostRedisplay();
    glutTimerFunc(5, timer, 0);
}

void keyboardMove(unsigned char key, int x, int y) {
    switch (key) {
        case 'W':
            ymove += 2;
            break;
        case 'S':
            ymove -= 2;
            break;
        case 'A':
            xmove -= 2;
            break;
        case 'D':
            xmove += 2;
            break;
        case 'Q':
            exit(1);
    }
}

void keyboardRotate(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            yspin -= 2;
            yspin %= 360;
            break;
        case GLUT_KEY_RIGHT:
            yspin += 2;
            yspin %= 360;
            break;
        case GLUT_KEY_UP:
            xspin -= 2;
            xspin %= 360;
            break;
        case GLUT_KEY_DOWN:
            xspin += 2;
            xspin %= 360;
            break;
        case GLUT_KEY_F12:
            exit(1);
    }
}

void reshape(GLsizei Width, GLsizei Height) {

    GLfloat AspectRatio;
    if (Height == 0) Height = 1;
    AspectRatio = (GLfloat) Width / (GLfloat) Height;
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (Width <= Height) {
        glOrtho(-100, 100, -100 / AspectRatio, 100 / AspectRatio, -100, 100);
    } else {
        glOrtho(-100 * AspectRatio, 100 * AspectRatio, -100, 100, -100, 100);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(450, 60);
    glutCreateWindow("Moving Cube");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    glutKeyboardFunc(keyboardMove);
    glutSpecialFunc(keyboardRotate);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(5, timer, 0);
    glutMainLoop();
}