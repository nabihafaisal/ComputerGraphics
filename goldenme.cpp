
#include <GL/glut.h>
#include <stdio.h>
#include <algorithm> 
void drawGoldenRectangle(float width, float height) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(-width / 2.0f, -height / 2.0f);
    glVertex2f(width / 2.0f, -height / 2.0f);
    glVertex2f(width / 2.0f, height / 2.0f);
    glVertex2f(-width / 2.0f, height / 2.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Define the initial size of the largest golden rectangle
    float baseSize = screenWidth < screenHeight ? screenWidth : screenHeight;
    float aspectRatio = 1.618f;

    // Calculate the threshold as a fraction of the smaller screen dimension
    float threshold = 1.0f / std::min(screenWidth, screenHeight);

    while (baseSize > threshold) {
        drawGoldenRectangle(baseSize, baseSize / aspectRatio);

        // Reduce the size for the next rectangle
        baseSize /= aspectRatio;
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Golden Rectangles");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
