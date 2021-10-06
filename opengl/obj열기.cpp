#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define _WINDOW_WIDTH 500
#define _WINDOW_HEIGHT 500

GLfloat camx = 0, camy = 2, camz = -10;
GLfloat cam2x = 0, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;
using namespace std;

class CPoint2f {
public:
    vector <float> d{ 0,0 };

};
class CPoint3f {
public:
    vector <float> d{ 0, 0 ,0};

};
class CPoint3i {
public:
    vector <int> d{ 0,0 };

};
class CFace {
public:
    vector <CPoint3i> v_pairs;
};
class CObj {
public:
    string name;
    vector <CPoint3f> v;
    vector <CPoint2f> vt;
    vector <CPoint3f> vn;
    vector <CFace> f;
};
class CModel {
public:
    vector <CObj> objs;

    vector<float> my_strtok_f(char* str, char* delimeter)
    {
        vector <float> v;
        char* context;
        char* tok = strtok_s(str, delimeter, &context);

        while (tok != NULL)
        {
            v.push_back(atof(tok));
            tok = strtok_s(NULL, delimeter, &context);
        }
        return v;
    }

    vector<string> my_strtok_s(char* str, char* delimeter)
    {
        vector <string> v;
        char* context;
        char* tok = strtok_s(str, delimeter, &context);

        while (tok != NULL)
        {
            v.push_back(tok);
            tok = strtok_s(context, delimeter, &context);
        }
        return v;
    }
    vector<int> my_strtok_i(char* str, char* delimeter)
    {
        vector <int> v;
        char* context;
        char* tok = strtok_s(str, delimeter, &context);

        while (tok != NULL)
        {
            v.push_back(atoi(tok));
            tok = strtok_s(context, delimeter, &context);
        }
        return v;
    }

    void loadObj(ifstream& fin)
    {
        string line;
        CObj obj_tmp;
        int cnt = 0;
        while (getline(fin, line)) {
            int len = line.length();
            vector<float> vf;
            vector<string> s;
            vector<int> vi;
            CPoint3f p3;
            CPoint2f p2;
            CPoint3i p3i;
            if (line[0] == 'o' && line[1] == ' ') {
                obj_tmp.name = line.substr(2, len - 2);
                objs.push_back(obj_tmp);
                cnt += 1;
            }
            else if (line[0] == 'v' && line[1] == ' ') {
                vf = my_strtok_f((char*)line.substr(2, len - 2).c_str(), (char*)" ");
                p3.d = { vf[0],vf[1],vf[2] };
                objs[cnt - 1].v.push_back(p3);
            }
            else if (line[0] == 'v' && line[1] == 't')
            {
                vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
                p2.d = { vf[0],vf[1] };
                objs[cnt - 1].vt.push_back(p2);
            }
            else if (line[0] == 'v' && line[1] == 'n') {
                vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
                p3.d = { vf[0],vf[1],vf[2] };
                objs[cnt - 1].vn.push_back(p3);
            }
            else if (line[0] == 'f' && line[1] == ' ') {
                s = my_strtok_s((char*)line.substr(2, len - 2).c_str(), (char*)" ");
                int nVertexes = s.size();
                CFace face_tmp;
                for (int i = 0; i < nVertexes; i++)
                {
                    vi = my_strtok_i((char*)s[i].c_str(), (char*)"/");
                    p3i.d = { vi[0],vi[1],vi[2] };
                    face_tmp.v_pairs.push_back(p3i);
                }
                objs[cnt - 1].f.push_back(face_tmp);
            }
        }
    }
 };


    CModel m;

    void reshape(int width, int height) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = (float)width / height;
        gluPerspective(100, ratio, 0.1, 1000);
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camx, camy, camz, cam2x, cam2y, cam2z, cam_upx, cam_upy, cam_upz);

        GLfloat x, y, z, nx, ny, nz;
        int v_id, vt_id, vn_id;
        int nFaces = m.objs[0].f.size();

        for (int k = 0; k < nFaces; k++)
        {
            int nPoints = m.objs[0].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for (int i = 0; i < nPoints; i++)
            {
                v_id = m.objs[0].f[k].v_pairs[i].d[0];
                vt_id = m.objs[0].f[k].v_pairs[i].d[1];
                vn_id = m.objs[0].f[k].v_pairs[i].d[2];
                x = m.objs[0].v[v_id - 1].d[0];
                y = m.objs[0].v[v_id - 1].d[1];
                z = m.objs[0].v[v_id - 1].d[2];

                nx = m.objs[0].vn[vn_id - 1].d[0];
                ny = m.objs[0].vn[vn_id - 1].d[1];
                nz = m.objs[0].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x, y, z);
                }
            glEnd();
        }
        glFlush();
    }

    int main(int argc, char** argv)
    {
        string filepath = "C:/graphics/Lens.obj";
        ifstream fin(filepath);

        m.loadObj(fin);
        fin.close();

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
        glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);
        glutInitWindowPosition(300, 200);
        glClearColor(0.0, 0.0, 0.0, 0.0);

        glutCreateWindow("OBJ Load");

        glutDisplayFunc(display);
        glutReshapeFunc(reshape);

        glutMainLoop();
        return 0;
    }