#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define _WINDOW_WIDTH 500
#define _WINDOW_HEIGHT 500
int angle_upper = 0;
int angle_lower = 0;

int dir_upper = 1;
int dir_lower = 1;

GLfloat camx = 0.5, camy = 0.5, camz = 4;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

void reshape(int width, int height) {

    GLfloat left = 0, bottom = 0;
    glViewport(left, bottom, width - left , height-bottom); // 파라미터 GLint left, GLint bottom, width, hegiht
    GLfloat f_w = (GLfloat)width / (GLfloat)_WINDOW_WIDTH;
    GLfloat f_h = (GLfloat)width / (GLfloat)_WINDOW_HEIGHT;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 //   glOrtho(-1.0 * f_w, 1.0 * f_w, -1.0 * f_h, 1.0 * f_h, -2, 2);
    GLfloat ratio = (float)(width-left) / (height-bottom);
   gluPerspective(40, ratio, 0.1, 10);

}


void drawArrow()  //화살표 그리기
{
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0.2, 0, 0);
        glVertex3f(0.2, 0, 0);
        glVertex3f(0.14, 0.06, 0);
        glVertex3f(0.2, 0, 0);
        glVertex3f(0.14, -0.06, 0);
        glEnd();
}

void drawAxis()   //화살표 축 돌리기
{
    glColor3f(1, 1, 1);
  /*  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/

    drawArrow();
    glPushMatrix();
        glRotatef(90, 0, 0, 1);
        drawArrow();
    glPopMatrix(); 

    glPushMatrix();
        glRotatef(-90, 0, 1, 0);
        drawArrow();
    glPopMatrix();
}
void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz)//직육면체 그리는 함수
{
    glPushMatrix();
    glScalef(sx, sy, sz);
    glutWireCube(1);
    glPopMatrix();
}
void drawBody()
{
    glPushMatrix();
        glScalef(2, 4, 1);
        glutWireCube(0.25);
    glPopMatrix();
}
void drawUpperArm(GLfloat angle)
{  
    glTranslatef(0.25, 0.3, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(0.25, 0, 0);
    drawCuboid(0.5, 0.2, 0.2);
  
}
void drawUpperArm2(GLfloat angle)
{
    glTranslatef(-0.25, 0.3, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-0.25, 0, 0);
    drawCuboid(0.5, 0.2, 0.2);

}
void drawLowerArm2(GLfloat angle)
{
    glTranslatef(-0.25, 0, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-0.25, 0, 0);
    drawCuboid(0.5, 0.2, 0.2);
}
void drawLowerArm(GLfloat angle)
{
    glTranslatef(0.25, 0, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(0.25, 0, 0);
    drawCuboid(0.5, 0.2, 0.2);
}
void drawHand2()
{
    glTranslatef(-0.35, 0, 0);
    glutWireSphere(0.1, 15, 15);
    drawAxis();
}
void drawFinger3()
{

    glTranslatef(-0.15, 0, 0);
    drawCuboid(0.1, 0.05, 0.05);
}
void drawFinger4()
{
    glRotatef(30, 0, 0, 1);
    glTranslatef(-0.15, 0, 0);
    drawCuboid(0.1, 0.05, 0.05);
}
void drawHand()
{
    glTranslatef(0.35, 0, 0);
    glutWireSphere(0.1, 15, 15);
    drawAxis();
}
void drawFinger1()
{

    glTranslatef(0.15, 0, 0);
    drawCuboid(0.1, 0.05, 0.05);
}
void drawFinger2()
{
    glRotatef(30, 0, 0, 1);
    glTranslatef(0.15, 0, 0);
    drawCuboid(0.1, 0.05, 0.05);
}
void display() {

   
    glClear(GL_COLOR_BUFFER_BIT);
    //drawAxis();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //항등행렬로 초기화 대각선만 1

    gluLookAt(camx, camy, camz,
        cam2x, cam2y, cam2z,
        cam_upx, cam_upy, cam_upz);  // eye x ->at x ->up x

    drawBody();
    glPushMatrix();
        drawUpperArm(angle_upper);
        drawLowerArm(angle_lower);
        drawHand();
        glPushMatrix();
            drawFinger1();
        glPopMatrix();
        glPushMatrix();
            drawFinger2();
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        drawUpperArm2(angle_upper);
        drawLowerArm2(angle_lower);
        drawHand2();
        glPushMatrix();
        drawFinger3();
        glPopMatrix();
        glPushMatrix();
        drawFinger4();
        glPopMatrix();
    glPopMatrix();


    glutSwapBuffers();
}

void MyTimer(int value)
{
    angle_upper += dir_upper;
    angle_lower += 5*dir_lower;
    if (angle_upper >= 80)
        dir_upper =  -1;
    else if (angle_upper <= -90)
        dir_upper = 1;
    if (angle_lower >= 160)
        dir_lower = -1;
    else if (angle_lower <= 0)
        dir_lower = 1;
    GLfloat theta = 0.01;
    camx = camx * cos(theta) + camz * sin(theta);
    camz = -camx * sin(theta) + camz * cos(theta);
    glutTimerFunc(20, MyTimer, 1);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
    glutCreateWindow("OpenGL Drawing Example");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(20, MyTimer, 1);
    glutMainLoop();
    return 0;
}
