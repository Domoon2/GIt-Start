#include <iostream>
#include <GL/glut.h>

int mode = 0;
int color_mode = 0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (color_mode == 0)
	{
		glColor3f(0.5, 0.5, 0.5);   //색설정(RGB)
	}
	else if (color_mode == 1)
	{
		glColor3f(1, 0, 0);   //색설정(RGB)
	}
	else if (color_mode == 2)
	{
		glColor3f(0, 1, 0);   //색설정(RGB)
	}
	else if (color_mode == 3)
	{ 
		glColor3f(0, 0, 1);   //색설정(RGB)
	}
	if (mode == 0)
	{

	}
	else if (mode == 1)
	{
		glutWireSphere(0.3, 15, 15);
	}
	
	else if (mode == 2)
	{
		glutWireTorus(0.2, 0.5, 15, 15);
	}
	else
	{
		glutWireTeapot(0.6);
	}
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
void Keyboard(unsigned char Keypressed, int X, int Y)
{
	switch (Keypressed)
	{
	case 'a':
		mode =  (mode+1)%5;
		break;
	case 'c':
		color_mode = (color_mode + 1) % 4;
		break;
	case 'Q':
		exit(0); break;
	case 'q':
		exit(0); break;
	case 27:
		exit(0); break;
	}
}
//void Mouse(int btn, int states, int x, int y)
//{
//	if (btn == GLUT_LEFT_BUTTON && states == GLUT_UP)
//	{
//		glColor(1,0,0)
//	}
//}

void selectMenu(int value)
{
	if (value == 2)
	{
		exit(0);
	}
}
void SelectSubMenu(int value)
{
	mode = value;
	glutPostRedisplay();
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
		glutKeyboardFunc(Keyboard);

		int subMenID = glutCreateMenu(SelectSubMenu);
		glutAddMenuEntry("Sphere", 1);
		glutAddMenuEntry("Torus", 2);
		glutAddMenuEntry("Teapot", 3);

		int mainMenuID = glutCreateMenu(selectMenu);
		glutSetMenu(mainMenuID);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		glutAddSubMenu("3D Model", subMenID);
		glutAddMenuEntry("Exit", 2);

	
		glutMainLoop();
		return 0;
	}