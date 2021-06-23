#include <iostream>
#include <GL/glut.h>


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);   //회색
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.5, 0.0);  //좌하단
	glVertex3f(0.5, -0.5, 0.0);  //우하단
	glVertex3f(0.5, 0.5, 0.0);   //우상단
	glVertex3f(-0.5, 0.5, 0.0);  //좌상단 
	glEnd();
	glFlush();

}
void Reshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)300;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}
int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB);
		glutInitWindowSize(300, 300);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("After Reshap");
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glutDisplayFunc(display);
		glutReshapeFunc(Reshape);
		glutMainLoop();
		return 0;
	}