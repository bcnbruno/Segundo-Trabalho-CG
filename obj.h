#ifndef OBJ_H
#define OBJ_H

#include <fstream>
#include <cstring>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

class OBJ
{
private:
    bool vt_2, vn_2, vf_2;
    GLint   v1, t1, n1, v2, t2, n2, v3, t3, n3;
    GLint   num_vertices, num_faces, num_v_textura, num_v_normal;
    GLfloat x, y, z,
            md_x, md_y, md_z; // Retirar

    GLfloat vertices[3][3];
    GLfloat normais[3][3];

    std::string line;
    std::vector<float> v;
    std::vector<float> vt;
    std::vector<float> vn;
    std::vector<unsigned int> f_v;
    std::vector<unsigned int> f_vt;
    std::vector<unsigned int> f_vn;

public:
    OBJ();
    ~OBJ(){};
    void abre_arquivo(char *nome);
    void get_face(int n_face);
    int get_num_faces();
    int get_num_vertices();
    void desenha_face(int n_face);
    void desenha_obj();
};

#endif // OBJ_H
