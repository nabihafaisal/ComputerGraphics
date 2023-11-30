
/*
This is a program which displays several primitives as well as animates objects.
Your task is to make the plane that makes a crash landing, but unlike the movies,
it doesn't burst into flames.The background contains a triangle for windmill.
You need to complete it using transformation then make it animate*/

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define PI 3.141592

void display(void); // draw everything
void drawWind(void);  // draw single blade 
void drawwindmill(void); //complete this to complete windmill i.e. call drawWind() in it
void drawplane();  // work in this function
//  for crash landing of plane i.e. animate and collision with land 
void drawCloud(float x, float y, float size);
void drawlandscape();// do nothing with it 
void Timer(int value); // update varible for animation here
void drawSun();
void DrawCircle(float cx, float cy, float r, int num_segments);
void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);


// // Variables for cloud positions and sizes
float cloud1X = 90.0f;
float cloud1Y = 200.0f;
float cloud2X = 200.0f;
float cloud2Y = 220.0f;
float cloudSize = 10.0f;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawlandscape();
    drawplane();
    drawwindmill();
//    Draw clouds
    drawCloud(cloud1X, cloud1Y, cloudSize);
    drawCloud(cloud2X, cloud2Y, cloudSize);
    drawSun();
    glutSwapBuffers();


}
void DrawCircle(float cx, float cy, float r, int num_segments) {

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 

        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 

        glVertex2f(x + cx, y + cy);//output vertex 

    }
    glEnd();
}

void drawSun()
{
    // Define the center coordinates of the sun (top-left corner)
    float cx = 30.0f; // X-coordinate
    float cy = 220.0f; // Y-coordinate

    glColor3f(3.0, 1.0, 0.5);
    DrawCircle(cx, cy, 25, 100);
}


void drawWind()
{
   static float current_angle = 0.0f;
   const float step_angle = 0.50f;
   const float center_x = 125.0f; // Adjust these values as needed
   const float center_y = 90.0f;

   glPushMatrix();

   // Translate to the center point
   glTranslatef(center_x, center_y, 0.0f);

   // Rotate around the center point
   glRotatef(current_angle, 0, 0, 1);
   current_angle += step_angle;

   // Translate back to the original position
   glTranslatef(-center_x, -center_y, 0.0f);

   // Define the blade coordinates as an array of endpoints
   float bladeCoordinates[4][6] = {
       {125.0, 90.0, 115.0, 125.0, 135.0, 125.0}
   };

   for (int i = 0; i < 4; ++i)
   {
      glPushMatrix();
      glTranslatef(center_x, center_y, 0.0f);
      glRotatef(i * 90.0, 0.0, 0.0, 1.0); // Rotate by 90 degrees clockwise around the Z-axis
      glTranslatef(-center_x, -center_y, 0.0f);
      glBegin(GL_TRIANGLES);
      glColor3f(0.9, 0.9, 0.9);
      // Loop through the blade coordinates and draw each blade
      glVertex2f(bladeCoordinates[0][0], bladeCoordinates[0][1]);
      glVertex2f(bladeCoordinates[0][2], bladeCoordinates[0][3]);
      glVertex2f(bladeCoordinates[0][4], bladeCoordinates[0][5]);
      glEnd();
      glPopMatrix();
   }

   glPopMatrix();
}
void drawwindmill()   // complete windmill in this body
{
    /* Draw a windmill */

    drawWind();

}

void drawCloud(float x, float y, float size) {
    int numCircles = 6; // Number of circles to create a cloud

    glColor3f(1.0, 1.0, 1.0); // White color for clouds

    for (int i = 0; i < numCircles; i++) {
        float xOffset = i * size * 0.6; // Adjust the spacing between circles
        float circleX = x + xOffset;
        float circleY = y;

        int numSegments = 50; // Number of segments to approximate a circle

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(circleX, circleY); // Center of the circle

        for (int j = 0; j <= numSegments; j++) {
            float theta = 2.0f * PI * float(j) / float(numSegments); // Angle for each segment
            float xPos = circleX + size * cosf(theta); // Calculate X position
            float yPos = circleY + size * sinf(theta); // Calculate Y position
            glVertex2f(xPos, yPos);
        }

        glEnd();
    }
}




float planeX = 245.0f; // Initial X position of the plane
float planeY = 230.0f; // Initial Y position of the plane
bool planeCrashed = false; // Flag to indicate if the plane has crashed

void drawplane() {
    /* Draw a plane */
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(planeX, planeY);
    glVertex2f(planeX, planeY + 10.0); // Increase Y to simulate the plane descending
    glVertex2f(planeX - 30.0, planeY); // Move the plane to the left

    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(planeX - 1.0, planeY - 2.0);
    glVertex2f(planeX - 1.0, planeY + 5.0); // Increase Y to simulate the plane descending
    glVertex2f(planeX - 17.0, planeY + 5.0); // Move the plane to the left

    glEnd();
}

void Timer(int value) {
    if (!planeCrashed) {
        // Update plane position (move it downward and to the left)
        planeY -= 1.0;
        planeX -= 0.98; // Move the plane slightly to the left (horizontal motion)

        // Check for collision with the ground (grass)
        if (planeY <= 50.0) {
            // Calculate the slope of the ground (rise over run)
            float slope = (50.0 - 150.0) / (0.0 - 250.0); // (Y1 - Y2) / (X1 - X2)

            // Calculate the corresponding X position on the slope
            float slopeX = (planeY - 150.0) / slope;

            // Check if the plane's X position is less than or equal to the slopeX
            if (planeX >= slopeX) {
                planeCrashed = true;
                printf("Plane crashed!\n");
            }
        }
    }
    // Update cloud positions
    cloud1X += 0.5f; // Move cloud1 to the right
    cloud2X += 0.5f; // Move cloud2 to the right

    // Check if clouds have moved out of the screen, and reset their positions if needed
    if (cloud1X > 250.0f + cloudSize) {
        cloud1X = -cloudSize; // Reset cloud1 to the left of the screen
    }
    if (cloud2X > 250.0f + cloudSize) {
        cloud2X = -cloudSize; // Reset cloud2 to the left of the screen
    }



    // Redraw the scene
    glutPostRedisplay();
    glutTimerFunc(15, Timer, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("BSCS 514 Lab #8");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, Timer, 1);
    glutMainLoop();
}



void drawlandscape()
{
    /* Draw a box of grass */
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(250.0, 0.0);
    glColor3f(0.0, 0.9, 0.0);
    glVertex2f(250.0, 50.0);
    glColor3f(0.0, 0.8, 0.0);
    glVertex2f(0.0, 50.0);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(0.0, 0.0);
    glEnd();

    /* An attempt at a few snow covered mountains */

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.6);
    glVertex2f(250.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(200.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(150.0, 50.0);

    //glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(200.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(150.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);

    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(150.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(100.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(50.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(50.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(0.0, 50.0);

    glEnd();

    /* Draw the body of a windmill */
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex2f(145.0, 50.0);
    glVertex2f(135.0, 100.0);
    glVertex2f(115.0, 100.0);
    glVertex2f(105.0, 50.0);
    glEnd();

}

void init()
{
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}





void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}