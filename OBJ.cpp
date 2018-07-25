#include <GL/glut.h>
#include "OBJ.h"

OBJ::OBJ()
{
    num_vertices = 0;
    num_faces = 0;
    num_v_textura = 0;
    num_v_normal = 0;
    x = 0;
    y = 0;
    z = 0;
    md_x = 0;
    md_y = 0;
    md_z = 0;

    v.push_back(0);
    vt.push_back(0);
    vn.push_back(0);
    f_v.push_back(0);
    f_vt.push_back(0);
    f_vn.push_back(0);

    vt_2 = false;
    vn_2 = false;
    vf_2 = false;
}

void  OBJ::abre_arquivo(char *nome){
    FILE *arq;
    arq = fopen(nome, "r");
    if(arq == NULL){std::cout << "ERRO ao abrir o arquivo!\n";}

    while(true){

        char first[100];
        int res = fscanf(arq, "%s", first);

        if(strcmp(first, "#vt_2")==0){vt_2 = true;}
        if(strcmp(first, "#vn_2")==0){vn_2 = true;}
        if(strcmp(first, "#vf_2")==0){vf_2 = true;}

        if(res == EOF){break;}

        if(strcmp(first, "v")==0){
            fscanf(arq, "%f %f %f\n", &x, &y, &z);
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            // Retirar
            md_x += x;
            md_y += y;
            md_z += z;

            num_vertices++;
        }else if(strcmp(first, "vt")==0){
            if(vt_2){
                fscanf(arq, "%f %f\n", &x, &y);
                vt.push_back(x);
                vt.push_back(y);
            }else{
                fscanf(arq, "%f %f %f\n", &x, &y, &z);
                vt.push_back(x);
                vt.push_back(y);
                vt.push_back(z);
            }
            num_v_textura++;
        }else if(strcmp(first, "vn")==0){
            if(vn_2){
                fscanf(arq, "%f %f\n", &x, &y);
                vn.push_back(x);
                vn.push_back(y);
            }else{
                fscanf(arq, "%f %f %f\n", &x, &y, &z);
                vn.push_back(x);
                vn.push_back(y);
                vn.push_back(z);
            }
            num_v_normal++;
        }else if(strcmp(first, "f")==0){
            if(vf_2){
                fscanf(arq, "%d/%d %d/%d %d/%d\n", &v1, &n1, &v2, &n2, &v3, &n3);
                f_v.push_back(v1);
                f_v.push_back(v2);
                f_v.push_back(v3);
                f_vn.push_back(n1);
                f_vn.push_back(n2);
                f_vn.push_back(n3);
            }else{
                fscanf(arq, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
                f_v.push_back(v1);
                f_v.push_back(v2);
                f_v.push_back(v3);
                f_vt.push_back(t1);
                f_vt.push_back(t2);
                f_vt.push_back(t3);
                f_vn.push_back(n1);
                f_vn.push_back(n2);
                f_vn.push_back(n3);
            }
            num_faces++;
        }
    }
    // Retirar
    md_x = md_x/(float)num_vertices;
    md_y = md_y/(float)num_vertices;
    md_z = md_z/(float)num_vertices;
}

void OBJ::get_face(int n_face){
    vertices[0][0] = v[ (f_v[(n_face*3) -2]*3) - 2 ];
    vertices[0][1] = v[ (f_v[(n_face*3) -2]*3) - 1 ];
    vertices[0][2] = v[ (f_v[(n_face*3) -2]*3)     ];

    vertices[1][0] = v[ (f_v[(n_face*3) -1]*3) - 2 ];
    vertices[1][1] = v[ (f_v[(n_face*3) -1]*3) - 1 ];
    vertices[1][2] = v[ (f_v[(n_face*3) -1]*3)     ];

    vertices[2][0] = v[ (f_v[(n_face*3)   ]*3) - 2 ];
    vertices[2][1] = v[ (f_v[(n_face*3)   ]*3) - 1 ];
    vertices[2][2] = v[ (f_v[(n_face*3)   ]*3)     ];

    normais[0][0] = vn[ (f_vn[(n_face*3) -2]*3) - 2 ];
    normais[0][1] = vn[ (f_vn[(n_face*3) -2]*3) - 1 ];
    normais[0][2] = vn[ (f_vn[(n_face*3) -2]*3)     ];

    normais[1][0] = vn[ (f_vn[(n_face*3) -1]*3) - 2 ];
    normais[1][1] = vn[ (f_vn[(n_face*3) -1]*3) - 1 ];
    normais[1][2] = vn[ (f_vn[(n_face*3) -1]*3)     ];

    normais[2][0] = vn[ (f_vn[(n_face*3)   ]*3) - 2 ];
    normais[2][1] = vn[ (f_vn[(n_face*3)   ]*3) - 1 ];
    normais[2][2] = vn[ (f_vn[(n_face*3)   ]*3)     ];
}

int OBJ::get_num_faces(){
    return this->num_faces;
}

int OBJ::get_num_vertices(){
    return this->num_vertices * 3;
}

void OBJ::desenha_face(int n_face){
    this->get_face(n_face);

    glEnable(GL_NORMALIZE); //
    glBegin(GL_POLYGON);
        glNormal3fv(normais[0]);
        glVertex3fv(vertices[0]);
        glNormal3fv(normais[1]);
        glVertex3fv(vertices[1]);
        glNormal3fv(normais[2]);
        glVertex3fv(vertices[2]);
    glEnd();
}

void OBJ::desenha_obj(){
    int n_faces = this->get_num_faces();
    for(int cont = 1; cont <= n_faces; cont++)
        this->desenha_face(cont);
}
