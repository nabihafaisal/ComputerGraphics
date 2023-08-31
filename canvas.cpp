
#include<gl/glut.h>
#include<math.h>
#include<iostream>
#include <stdlib.h>
using namespace std;


class Point2 {
public:
	Point2() { x = y = 0.0f; }
	Point2(float xx, float yy) { x = xx; y = yy; }
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw(void) {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float x, y;
};

class IntRect {
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; }
	IntRect(int left, int right, int bottom, int top) {
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top) {
		l = left; r = right; b = bottom; t = top;
	}
	void draw(void);
private:
	int l, r, b, t;
};

class RealRect {
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; }
	RealRect(float left, float right, float bottom, float top) {
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top) {
		l = left; r = right; b = bottom; t = top;
	}
	void draw(void);
private:
	float l, r, b, t;
};

class Canvas {
public:
	Canvas(int width, int height, char* windowTitle);
	void setWindow(float l, float r, float b, float t);
	void setViewport(int l, int r, int b, int t);
	void clearScreen();
	void setBackgroundColor(float r, float g, float b);
	void setColor(float r, float g, float b);
	void lineTo(float x, float y);
	void moveTo(float x, float y);
	void moveRel(float dx, float dy);
	void lineRel(float dx, float dy);
	void arrow(float x, float y, float length, float angle);
private:
	Point2 CP;
	IntRect viewport;
	RealRect window;
};
// void RealRect::draw(void) {
// 	glBegin(GL_LINE_LOOP);
// 	glVertex2f((GLfloat)l, (GLfloat)b);
// 	glVertex2f((GLfloat)r, (GLfloat)b);
// 	glVertex2f((GLfloat)r, (GLfloat)t);
// 	glVertex2f((GLfloat)l, (GLfloat)t);
// 	glEnd();
// }
Canvas cvs(640, 480, "try out Canvas");


Canvas::Canvas(int width, int height, char* windowTitle) {
	char* argv[1];
	char dummyString[8];
	argv[0] = dummyString;
	int argc = 1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(20, 20);
	glutCreateWindow(windowTitle);
	setWindow(0, (float)width, 0, (float)height);
	setViewport(0, width, 0, height);
	CP.set(0.0f, 0.0f);
}

void Canvas::moveTo(float x, float y) {
	CP.set(x, y);
}

void Canvas::lineTo(float x, float y) {
	glBegin(GL_LINES);
	glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
	glVertex2f((GLfloat)x, (GLfloat)y);
	glEnd();
	CP.set(x, y);
	glFlush();
}
void Canvas::moveRel(float dx, float dy)
{
	float x = CP.getX() + dx;
	float y = CP.getY() + dy;
	CP.set(x, y);
}

void Canvas::lineRel(float dx, float dy)
{
	float x = CP.getX() + dx;
	float y = CP.getY() + dy;
	lineTo(x, y);
	CP.set(x, y);
}


void Canvas::setWindow(float l, float r, float b, float t) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
	window.set(l, r, b, t);
}

void Canvas::setViewport(int l, int r, int b, int t) {
	glViewport(l, b, r - l, t - b);
	viewport.set(l, r, b, t);
}

void Canvas::clearScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas::setBackgroundColor(float r, float g, float b) {
	glClearColor(r, g, b, 0.0);
}

void Canvas::setColor(float r, float g, float b) {
	glColor3f(r, g, b);
}
void Canvas::arrow(float f, float h, float t, float w)
{
    // assumes global Canvas object: cvs

    // Move to the starting point at (-w - t / 2, -f)
    cvs.lineRel(-w - t / 2, -f); // down the left side

    // Draw the top horizontal line of the arrow with width 'w'
    cvs.lineRel(w, 0);

    // Draw the vertical line of the arrow with height 'h'
    cvs.lineRel(0, -h);

    // Draw the bottom horizontal line of the arrow with width 't'
    cvs.lineRel(t, 0); // across

    // Draw the vertical line back up to complete the arrow
    cvs.lineRel(0, h); // back up

    // Draw the right side of the arrow
    cvs.lineRel(w, 0);

    // Return to the starting point to complete the arrow shape
    cvs.lineRel(-w - t / 2, f); 
}


void display(void) {
	cvs.clearScreen();
	cvs.setWindow(-10.0, 10.0, -10.0, 10.0);
	cvs.setViewport(10, 630, 10, 470);
	// cvs.moveTo(0, -10.0);
	// cvs.lineTo(0, 10.0);
	// cvs.lineRel(0, 10.0);
	// cvs.moveRel(0, -10.0);
	cvs.arrow(4.0, 5.0, 1.0, 1.0); // Draws an arrow with specific dimensions

	// RealRect box(-2.0, 2.0, -1.0, 1.0);
	// box.draw();
	glFlush();
}

int main(int argc, char** argv) {
	cvs.setBackgroundColor(1.0, 1.0, 1.0);
	cvs.setColor(0.0, 0.0, 0.0);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
