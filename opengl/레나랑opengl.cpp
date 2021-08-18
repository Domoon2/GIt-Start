#include <GL/glut.h>
#include <opencv2/opencv.hpp>	


using namespace cv;

#define _WINDOW_WIDTH 500
#define _WINDOW_HEGIHT 500

GLfloat camx = 2, camy = 2, camz = 5;
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
    glNormal3f(0.5, 1, 0);
    glVertex3f(x + w, y, z + w);
    glVertex3f(x + w, y, z);
    glEnd();
}



void MyReshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = (float)width / height;
    gluPerspective(40, ratio, 0.1, 1000);
}

void set_light()
{

    GLfloat light_global_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat light_0_pos[] = { 2.0, 2.0, 5.0, 1.0 };
    GLfloat light_0_ambient[] = { 1.0, 1.0, 1.0,1.0 };
    GLfloat light_0_diffuse[] = { 1.0, 1.0, 1.0,1.0 };
    GLfloat light_0_specular[] = { 1.0, 1.0, 1.0,1.0 };



    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_pos);


}
void set_material_color()
{
    glDisable(GL_COLOR_MATERIAL);
    GLfloat matrial_0_ambient[] = { 0.3,0.3,0.3,1.0 };
    GLfloat matrial_0_diffuse[] = {1.0,1.0,1.0,1.0 };
    GLfloat matrial_0_specular[] = { 1.0,1.0,1.0,1.0 };
    GLfloat matrial_0_shininess[] = { 25.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, matrial_0_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matrial_0_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matrial_0_specular);
    glMaterialfv(GL_FRONT, GL_POSITION, matrial_0_shininess);
}
void display_objs()
{
    GLfloat v1[3] = { -1, -1, 1 };
    GLfloat v2[3] = { -1, 1, 1 };
    GLfloat v3[3] = { 1, 1, 1 };
    GLfloat v4[3] = {1, -1, 1 };

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0, 1.0);
        glVertex3f(v1[0], v1[1], v1[2]);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(v2[0], v2[1], v2[2]);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(v3[0], v3[1], v3[2]);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(v4[0], v4[1], v4[2]);
    glEnd();
}
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);  // eye x ->at x ->up x

    set_light();
    set_material_color();
    display_objs();
    glFlush();
}
void init_light()
{
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void init_texture(uchar* pImgArray, int width, int height)
{
    GLuint tex_id = 1;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pImgArray);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
}
int main(int argc, char** argv) {
    Mat img = imread("Lenna.png", IMREAD_COLOR);
    cvtColor(img, img, COLOR_BGR2RGB);
    imshow("33", img);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEGIHT);
    glutInitWindowPosition(300, 200);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutCreateWindow("openGL Sample Drawing");
    init_light();
    init_texture(img.data, img.cols, img.rows);
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutMainLoop();
    return 0;
}
