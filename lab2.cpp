#include <GL\glut.h>
#include <iostream>
#include <windows.h>
using namespace std;

// Function to initialize the drivers
void myInit(void)
{
    // Clear all the screen color
    glClearColor(0.1, 0.39, 0.88, 1.0); // Colour change through coordinates

    // Sets background color to orange
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    // Specify the display area
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

// Function to draw the tree
void drawTree()
{
    // Tree trunk
    glColor3f(0.36f, 0.25f, 0.20f);
    glBegin(GL_POLYGON);
    glVertex2i(400, 40);
    glVertex2i(420, 40);
    glVertex2i(420, 150);
    glVertex2i(400, 150);
    glEnd();

    // Tree leaves
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2i(350, 150);
    glVertex2i(470, 150);
    glVertex2i(410, 220);
    glEnd();
}

// Function to display the Hut-like structure with a tree
void myDisplay(void)
{
    // Clear the screen buffer
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(4.0);

    // Draw the Hut

    // Rectangular part of hut
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(40, 40);
    glVertex2i(320, 40);
    glVertex2i(320, 200);
    glVertex2i(40, 200);
    glEnd();

    // Right Window Update
    glColor3f(0.6, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(220, 60);
    glVertex2i(300, 60);
    glVertex2i(300, 150);
    glVertex2i(220, 150);
    glEnd();

    // Door
    glColor3f(0.60f, 0.42f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2i(130, 40);
    glVertex2i(130, 160);
    glVertex2i(180, 160);
    glVertex2i(180, 40);
    glEnd();

    // Hut's top triangle part
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2i(10, 200);
    glVertex2i(340, 200);
    glVertex2i(200, 390);
    glEnd();

    // Draw the Tree
    drawTree();

    // Sends all output to display
    glFlush();
}

// Driver Code
int main(int argc, char** argv)
{
    // Initialize the init function
    glutInit(&argc, argv);

    // Initialize the toolkit;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Sets the display mode and specify the colour scheme
    glutInitWindowSize(800, 600); // Adjusted window size to fit both hut and tree
    glutInitWindowPosition(100, 100); // Adjusted window position
    glutCreateWindow("Basic hut-like structure with a tree");

    // Creates the window and sets the title
    glutDisplayFunc(myDisplay);
    myInit();

    // Additional initializations
    glutMainLoop();

    // Go into a loop until an event occurs
    return 0;
}