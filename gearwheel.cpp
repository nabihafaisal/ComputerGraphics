#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <ctime>

// Declare a global angle variable to keep track of the rotation angle
float rotationAngle = 0.0;

void tooth()
{
    glBegin(GL_LINE_LOOP); // Start drawing a line loop

    // Define the vertices for your flake motif
    glColor3f(0.0, 0.0, 1);
    glVertex2f(0, 0);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.8);
    glVertex2f(0.2, 0.8);
    glVertex2f(0, 1);

    glEnd(); // End drawing the line loop
}
// this function is used for inclination
void tooth1(double r)
{
    double rad = (6.0 * 3.1416 / 180.0) + 0.1,
           sin6 = r * sin(rad), cos6 = r * cos(rad);
    glPushMatrix();
    glTranslatef(cos6, -sin6, 0.0);
    glScalef(2.0 * sin6, 2.0 * sin6, 1.0);
    // Draw your geometry here if needed
    tooth(); // Draw a tooth at the transformed position
    glPopMatrix();
}

void gear(double r, int numTeeth)
{
    for (int i = 0; i < numTeeth; i++)
    {
        glPushMatrix();
        glRotatef(static_cast<float>(i * (360.0 / numTeeth) + rotationAngle), 0.0, 0.0, 1.0);
        glTranslatef(0.0, r, 0.0);          // Translate along the y-axis by the radius
        glRotatef(6.0 + 90, 0.0, 0.0, 1.0); // Rotate each tooth by 6 degrees

        tooth1(r);
        glPopMatrix();
    }

    // Draw a smaller circle in the middle
    glColor3f(0.0, 0.0, 1.0); // Set color to white
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0); // Center of the circle
    for (int j = 0; j <= 360; j += 10)
    { // Draw the circle's vertices
        double angle = static_cast<double>(j) * 3.1416 / 180.0;
        double x = 0.1 * cos(angle);
        double y = 0.1 * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void move()
{
    // 'Standard Setup for animation
    float speed = 0.01;
    rotationAngle += 2.0 * speed; // Increment the rotation angle by 6 degrees

    // Ensure that the angle wraps around 360 degrees
    if (rotationAngle >= 360.0)
        rotationAngle -= 360.0;

    glutPostRedisplay();
}

void display(void)
{
    // Clear the screen and set up the coordinate system
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0); // Adjust the coordinate system

    // Call the gear function to draw the gear with teeth, circle between teeth, and smaller circle in the middle
    gear(0.5, 30);                   // You can adjust the gear radius and number of teeth as needed
    glColor3f(0.0, 255.0, 0.0);      // Set color to red
    

    glFlush();
}

int main(int argc, char **argv)
{
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // Adjust window size
    glutCreateWindow("Moving Gear");

    // Set the display function
    glutDisplayFunc(display);

    // Set the clear color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Register the move function for animation
    glutIdleFunc(move);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}
