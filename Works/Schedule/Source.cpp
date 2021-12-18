#include <iostream>
#include <cmath>
#include "glut.h"

#define X_MAX 10
#define Y_MAX 10
#define X_MIN -10
#define Y_MIN -10

#define SHIFT_X 0
#define SHIFT_Y 0

#define COMPRESS_X 1;                // 1 - default
#define COMPRESS_Y 2;

using namespace std;

#pragma comment(lib, "opengl32.lib")    
#pragma comment(lib, "glut32.lib")      


void CanvasInit() {

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(X_MIN, X_MAX, Y_MIN, Y_MAX);
}

void setPixel(float x, float y) {

	x /= (float)COMPRESS_X;
	x += SHIFT_X;	
	y /= (float)COMPRESS_Y;
	y += SHIFT_Y;

	if (y > Y_MAX - 0.5 || y < Y_MIN + 0.5 || x > X_MAX - 0.5 || x < X_MIN + 0.5) { 	
		
		return; 
	}
	else {	

		glVertex2f(x, y);	
	}

	glFlush();
}


void AxisAndGrid() {

	int i;
	glLineWidth(1);
	glColor3f(0.75, 0.75, 0.75);

	glBegin(GL_LINES);                                        // grid

	for (i = Y_MIN + 2; i < Y_MAX - 1; i++) {

		glVertex2f(X_MIN + 1, i);
		glVertex2f(X_MAX - 1, i);
	}

	for (i = X_MIN + 2; i < X_MAX - 1; i++) {

		glVertex2f(i, Y_MIN + 1);
		glVertex2f(i, Y_MAX - 1);
	}

	glEnd();

	glColor3f(0, 0, 0);

	glBegin(GL_LINES);                                        // axis
	glVertex2f(X_MIN + 0.5, SHIFT_Y);
	glVertex2f(X_MAX - 0.5, SHIFT_Y);
	glVertex2f(SHIFT_X, Y_MIN + 0.5);
	glVertex2f(SHIFT_X, Y_MAX - 0.5);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(X_MAX - 1.25, 0.5 + SHIFT_Y);
	glVertex2f(X_MAX - 0.5, 0 + SHIFT_Y);
	glVertex2f(X_MAX - 1.25, -0.5 + SHIFT_Y);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0.5 + SHIFT_X, Y_MAX - 1.25);
	glVertex2f(0 + SHIFT_X, Y_MAX - 0.5);
	glVertex2f(-0.5 + SHIFT_X, Y_MAX - 1.25);
	glEnd();

	glBegin(GL_LINES);

	for (i = X_MIN + 2; i < X_MAX - 1; i++) {

		glVertex2f(i, 0.25 + SHIFT_Y);
		glVertex2f(i, -0.25 + SHIFT_Y);
	}

	for (i = Y_MIN + 2; i < Y_MAX - 1; i++) {

		glVertex2f(0.25 + SHIFT_X, i);
		glVertex2f(-0.25 + SHIFT_X, i);
	}

	glEnd();

	glRasterPos2i(1 + SHIFT_X, Y_MAX - 1);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');

	glRasterPos2i(X_MAX - 1, 1 + SHIFT_Y);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');

	glFlush();
}


float circle(float x_center, float y_center, float radius, float x_var) {

	return sqrt(pow(radius, 2) - pow(x_var - x_center, 2)) + y_center;
}

double strange_func(double x) {

	return 20 * pow(x, 3) * sin(x);
}


void Shedule() {

	float begin = X_MIN + 1;
	float end = X_MAX - 1;
	float step = 0.001;
	float x;

	AxisAndGrid();

	glPointSize(3);
	glBegin(GL_POINTS);	
	glColor3f(1.0f, 0.0f, 0.0f);

	for (x = begin; x <= end; x += step) {
	
		setPixel(x, circle(0, 0, 6, x));
		setPixel(x, -1 * circle(0, 0, 6, x));
	}

	glColor3f(1.0f, 0.5f, 0.0f);
	step = 0.00001;

	for (x = begin; x <= end; x += step) {

		setPixel(x, strange_func(x));
	}

	glEnd();
	glFlush();

}


int main(int argc, char** argv) {

	setlocale(LC_ALL, "ru");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	
	glutInitWindowSize(650, 650);
	glutCreateWindow("Shedule");

	CanvasInit();
	glutDisplayFunc(Shedule);

	glutMainLoop();

	return 0;
}