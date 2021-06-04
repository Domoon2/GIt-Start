#include <iostream>
#include <GL/glut.h>

void display()
{
	//Clear
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	//Draw
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2f, -0.2f);
	glVertex2f(0.4f, -0.4f);
	glVertex2f(0.4f, 0.4f);
	glVertex2f(-0.2f, 0.2f);
	glEnd();

	glFinish();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL");

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}