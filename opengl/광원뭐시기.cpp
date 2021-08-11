#include <GL/glut.h>

#define _WINDOW_WIDTH 500
#define _WINDOW_HEGIHT 500

GLfloat camx = 0, camy = 5, camz = 7;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;


void drawWall(GLfloat z) {
    GLfloat x = -2.5, y = -2.5, w = 5;
    glColor3f(0.2, 0.6, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    glVertex3f(x, y + w, z);
    glVertex3f(x + w, y + w, z);
    glVertex3f(x + w, y, z);
    glEnd();
}
void drawFloor(GLfloat y) {
    GLfloat x = -2.5, z = -2.5, w = 5;
    glColor3f(0.2, 0.2, 0.8);
    glBegin(GL_POLYGON);
    glNormal3f(-0.5, 1, 0);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + w);
    glNormal3f(-0.5, 1, 0);
    glVertex3f(x + w, y, z + w);
    glVertex3f(x + w, y, z);
    glEnd();
}


void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);  // eye x ->at x ->up x

    drawFloor(-2.5);
    drawWall(-2.5);
    glColor3f(0.8, 0.2, 0);
    glutSolidSphere(0.3, 20, 20);

    glFlush();
}

void MyReshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (float)width / height;
    gluPerspective(40, ratio, 0.1, 1000);
}

void init_light()
{
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    int bNonDirectionalLight = 1;
    GLfloat light_global_ambient[] = { 1.0, 1.0, 1.1, 1.0 };
    GLfloat light_0_pos[] = { 5.0, 5.0, 0.0, bNonDirectionalLight };

    GLfloat light_0_amibient[] = { 1.0, 1.0, 1.0,1.0 };
    GLfloat light_0_diffuse[] = { 1.0, 1.0, 1.0,1.0 };
    GLfloat light_0_specular[] = { 1.0, 1.0, 1.0,1.0 };

    GLfloat matrial_0_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat matrial_0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat matrial_0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matrial_0_shininess[] = { 25.0 };

    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);

    glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matrial_0_shininess);

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEGIHT);
    glutInitWindowPosition(300, 200);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutCreateWindow("openGL Sample Drawing");
    init_light();

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutMainLoop();
    return 0;
}
