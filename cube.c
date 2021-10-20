#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>

HDC hDC = NULL; // device context handle
HGLRC hRC = NULL; // handle to GL Rendering Context
HWND hWnd = NULL; // window handle
HINSTANCE hInstance; // application instance handle

GLfloat xspin, yspin; // variables of rotation along the X, Y axes

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// clear screen and depth buffer
    glLoadIdentity();
    glPushMatrix(); // saving the current matrix to the stack
    glRotatef(xspin, 1, 0, 0); // rotation along the X axis on movxspin
    glRotatef(yspin, 0, 1, 0); // rotation along the Y axis on movyspin

    // draw a cube with squares and paint them
    glBegin(GL_QUADS); // front
    glVertex3f(50, -50, -50);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(50, 50, -50);
    glVertex3f(-50, 50, -50);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-50, -50, -50);
    glEnd();

    glBegin(GL_QUADS); //back
    glVertex3f(50, -50, 50);
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(50, 50, 50);
    glVertex3f(-50, 50, 50);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-50, -50, 50);
    glEnd();

    glBegin(GL_QUADS); //right
    glVertex3f(50, -50, -50);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(50, 50, -50);
    glVertex3f(50, 50, 50);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(50, -50, 50);
    glEnd();

    glBegin(GL_QUADS); //left
    glVertex3f(-50, -50, 50);
    glColor3f(1.0, 0.5, 1.0);
    glVertex3f(-50, 50, 50);
    glVertex3f(-50, 50, -50);
    glColor3f(0.0, 1.5, 0.0);
    glVertex3f(-50, -50, -50);
    glEnd();

    glBegin(GL_QUADS); // top
    glVertex3f(50, 50, 50);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(50, 50, -50);
    glVertex3f(-50, 50, -50);
    glColor3f(1.0, 0.0, 0.5);
    glVertex3f(-50, 50, 50);
    glEnd();

    glBegin(GL_QUADS); // bottom
    glVertex3f(50, -50, -50);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(50, -50, 50);
    glVertex3f(-50, -50, 50);
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-50, -50, -50);
    glEnd();

    glPopMatrix(); //restoring a previously saved matrix
    glutSwapBuffers(); // swap the buffers of the current window if double buffered
}

void timer() { // timer function for cube rotation
    display();  // cube drawing functions
    glutTimerFunc(5, timer, 0); // timer for 5 milliseconds
}

void Keyboard(int key, int x, int y) { // keyboard function

    switch (key) { // depending on which button the user presses, there is movement along a certain axis
        case GLUT_KEY_LEFT:
            yspin += 2.0;
            break;
        case GLUT_KEY_RIGHT:
            yspin -= 2.0;
            break;
        case GLUT_KEY_UP:
            xspin -= 2.0;
            break;
        case GLUT_KEY_DOWN:
            xspin += 2.0;
            break;
        case GLUT_KEY_F12:
            exit(1); // exit the program
    }
}

// the function of preserving the proportions of the figure when changing the window
void Reshape(GLsizei Width, GLsizei Height) {

    GLfloat AspectRatio; // window height to width ratio

    if (Height == 0) Height = 1;
    AspectRatio = (GLfloat) Width / (GLfloat) Height;
    glViewport(0, 0, Width, Height); // set viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // switch to the projection matrix
    glLoadIdentity(); // reset the projection matrix; cleaning up
    // set the orthographic projection matrix depending on the ratio of height and width
    if (Width <= Height) {
        glOrtho(-100, 100, -100 / AspectRatio, 100 / AspectRatio, -100, 100);
    } else {
        glOrtho(-100 * AspectRatio, 100 * AspectRatio, -100, 100, -100, 100);
    }
    glMatrixMode(GL_MODELVIEW); // switch back to the model view matrix
}

int main(int argc, char **argv) {

    printf("This program is \"Rotating Cube\". Use the arrow keys to move the cube. "
           "To exit the program, press the F12 key.");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600); // set the width and height of the window
    glutInitWindowPosition(450, 80); // set the position of the window
    glutCreateWindow("Rotating Cube"); // set the title for the window
    glEnable(GL_DEPTH_TEST); // enable Z-buffer depth test
    glClearColor(0, 0, 0, 1.0); // set the background color
    glutSpecialFunc(Keyboard); // tell GLUT to use the func "Keyboard" for cube movement
    glutDisplayFunc(display); // tell GLUT to use the func "display" for rendering
    glutReshapeFunc(Reshape); // tell GLUT to use the func "reshape" for rendering
    timer(); // registering timer function
    glutMainLoop(); // enter GLUT's main loop
}