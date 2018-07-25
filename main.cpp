#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "OBJ.h"
#include <iostream>

#include <stdlib.h>

#define LARGURA_JANELA 500
#define ALTURA_JANELA 500

GLint dist = 120.0;
GLint dist_z = 120.0;
GLfloat rot = 0.0;
GLfloat angulo = 0.0;
GLfloat d_x, d_y;
GLboolean primeira_pessoa = false;
GLboolean p_p_t = false;

GLdouble viewer[] = {-dist, 0.0, dist_z};
GLdouble foco[] = {-10.0, 0.0, 0.0};
GLdouble view_up[] = {1.0, 0.0, 1.0};
GLfloat rotaciona[] = {90.0, 1.0, 0.0, 0.0};
GLfloat mover[] = {0.0, 0.0, 0.0};
GLfloat posicao_aviao[] = {0.0, 0.0, 50.0};
int escolha_aviao = 1; // 0 - aviao A, 1 - aviao B, 2 - aviao C

OBJ aviaoA;
OBJ aviaoB;
OBJ aviaoC;
OBJ predio1;

void desenha_aviaoA(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-130, -60, 0);
        glRotatef(90, 1.0, 0.0, 0.0);
        aviaoA.desenha_obj();
    glPopMatrix();
}
void desenha_aviaoB(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(-40, -40, 0);
        glRotatef(90, 1.0, 0.0, 0.0);
        aviaoB.desenha_obj();
    glPopMatrix();
}
void desenha_aviaoC(){
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(40, -40, 0);
        glRotatef(90, 1.0, 0.0, 0.0);
        aviaoC.desenha_obj();
    glPopMatrix();
}


void desenha_cidade(){
    int distancia = 0;
    for(int i = 0; i < 10; i++){
        glPushMatrix();
            glColor3f(1.0, 0.0, 0.0);
            glTranslatef(140 + distancia, 70, 0);
            glRotatef(90, 1.0, 0.0, 0.0);
            predio1.desenha_obj();
        glPopMatrix();
        distancia += 80;
    }

    // desenhar aviao no chao
    if(escolha_aviao == 0){
        desenha_aviaoB();
        desenha_aviaoC();
    }
    else if(escolha_aviao == 1){
        desenha_aviaoA();
        desenha_aviaoC();
    }
    else{
        desenha_aviaoA();
        desenha_aviaoB();
    }

}

void desenha_eixos(){
    //eixos (x,y,z)
    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3f(1,0,0);// Vermelho x positivo
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(20000,0,0);
        glColor3f(1,1,0); // Amarelo x negativo
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(-20000,0,0);
        glColor3f(0,1,0); // Verde y positivo
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0,20000,0);
        glColor3f(0,0,0); // Preto y negativo
        glVertex3f(0,0,0);
        glVertex3f(0,-20000,0);
        glColor3f(0,0,1);
        glVertex3f(0,0,20000);
        glVertex3f(0,0,-20000);
    glEnd();
}

void desenha_chao(){
    desenha_eixos();
    glColor3f(0.7f,0.7f,0.7f);
    glBegin(GL_POLYGON);
        glVertex3f(20000.0f,0.0f,0.0f);
        glVertex3f(0.0f,20000.0f,0.0f);
        glVertex3f(-20000.0f,0.0f,0.0f);
        glVertex3f(0.0f,-20000.0f,0.0f);
    glEnd();

    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_POLYGON);
        glVertex3f(1000.0f,-10.0f,0.0f);
        glVertex3f(1000.0f,10.0f,0.0f);
        glVertex3f(0.0f,10.0f,0.0f);
        glVertex3f(0.0f,-10.0f,0.0f);
    glEnd();
}

void calcula_pos_aviao(){
    posicao_aviao[0] += (mover[0] - posicao_aviao[0]);
    posicao_aviao[1] += (mover[1] - posicao_aviao[1]);
    posicao_aviao[2] += (mover[2] - posicao_aviao[2]);
}

void calcula_pos_camera(){
    GLfloat x , y;

    angulo = rot*(3.14159/180);

    d_x = dist * cos(angulo);
    d_y = dist * sin(angulo);

    if(rot == 360 || rot == -360)
        rot = 0;

    if(rot > 0 && rot < 90){
        x = dist - d_x;
        y = d_y;
        viewer[0] = (x - dist) + mover[0] ;
        viewer[1] = (0 - y) + mover[1];
    }
    else if(rot >= 90 && rot < 180){
        x = ((dist + d_x) - dist) * -1;
        y = dist - d_y;
        viewer[0] = x + mover[0];
        viewer[1] = (y - dist) + mover[1] ;
    }
    else if(rot >= 180 && rot < 270){
        x = dist + d_x;
        y = ((dist + d_y) - dist) * -1;
        viewer[0] = (dist - x) + mover[0];
        viewer[1] = y + mover[1];
    }
    else if(rot >= 270 && rot < 360){
        x = dist - d_x;
        y = (dist + d_y) - dist;
        viewer[0] = (x - dist) + mover[0];
        viewer[1] = (0 - y) + mover[1];
    }
    else if(rot <= 0 && rot > -90){
        x = dist - d_x;
        y = ((dist + d_y) - dist) * -1;
        viewer[0] = (x - dist) + mover[0];
        viewer[1] = y  + mover[1];
    }
    else if(rot <= -90 && rot > -180){
        x = ((dist + d_x) - dist) * -1;
        y = (dist + d_y) - dist;
        viewer[0] = x + mover[0];
        viewer[1] = (0 - y) + mover[1];
    }
    else if(rot <= -180 && rot > -270){
        x = ((dist + d_x) - dist);
        y = (dist + d_y) - dist;
        viewer[0] = (0 - x) + mover[0];
        viewer[1] = (0 - y) + mover[1];
    }
    else if(rot <= -270 && rot > -360){
        x = ((dist - d_x) - dist) * -1;
        y = dist - d_y;
        viewer[0] = (0 - x) + mover[0];
        viewer[1] = (y - dist) + mover[1];
    }
}

void calcula_foco(){
    if(!primeira_pessoa){
        foco[0] = posicao_aviao[0]-10;
        foco[1] = posicao_aviao[1];
        foco[2] = posicao_aviao[2];
    }
    else if(!p_p_t){
        angulo = rot*(3.14159/180);
        foco[0] = posicao_aviao[0] + (cos(angulo)*500);
        foco[1] = posicao_aviao[1] + (sin(angulo)*500);
        foco[2] = posicao_aviao[2];
    }
    else{
        angulo = rot*(3.14159/180);
        foco[0] = posicao_aviao[0] + (cos(angulo)*-500);
        foco[1] = posicao_aviao[1] + (sin(angulo)*-500);
        foco[2] = posicao_aviao[2];
    }
}

void calcula_view_up(){
    view_up[0] = cos(rot*3.1415/180);
    view_up[1] = sin(rot*3.1415/180);
}

void voo(int n){
    angulo = rot*(3.14159/180);
    mover[0] += cos(angulo);
    mover[1] += sin(angulo);

    calcula_pos_camera();
    calcula_foco();
    calcula_view_up();

    glutPostRedisplay();
    glutTimerFunc(33,voo, 10);
}

void init(void) {
    aviaoA.abre_arquivo("aviaoA.obj");
    aviaoB.abre_arquivo("aviaoB.obj");
    aviaoC.abre_arquivo("aviaoC.obj");
    predio1.abre_arquivo("building.obj");

    glClearColor(1.0, 1.0, 1.0, 1.0); // cor para limpeza do buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(70.0,(LARGURA_JANELA/ALTURA_JANELA), 0.1, 20000); // projeção perspectiva
    glMatrixMode(GL_MODELVIEW);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa a janela
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2], // define posicao do observador
    foco[0],foco[1],foco[2],                 // ponto de interesse (foco)
    view_up[0], view_up[1], view_up[2]);     // vetor de "view up"

    desenha_chao();

    if(escolha_aviao == 0){
        glPushMatrix();
            glColor3f(1.0, 0.0, 0.0);
            calcula_pos_aviao();
            glTranslatef(mover[0],mover[1],50);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(90, 0.0, -1.0, 0.0);
            glRotatef(rot, 0.0, 1.0, 0.0);
            aviaoA.desenha_obj();
        glPopMatrix();
    }
    else if(escolha_aviao == 1){
        glPushMatrix();
            glColor3f(1.0, 0.0, 0.0);
            calcula_pos_aviao();
            glTranslatef(mover[0],mover[1],50);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            glRotatef(rot, 0.0, 1.0, 0.0);
            aviaoB.desenha_obj();
        glPopMatrix();
    }
    else{
        glPushMatrix();
            glColor3f(1.0, 0.0, 0.0);
            calcula_pos_aviao();
            glTranslatef(mover[0],mover[1],50);
            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            glRotatef(rot, 0.0, 1.0, 0.0);
            aviaoC.desenha_obj();
        glPopMatrix();
    }

    desenha_cidade();

    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); //ESC

	// Troca câmera
    if (key == '0'){ // Visão traseira
        dist *= -1;
        if(primeira_pessoa){
            if(p_p_t)
                p_p_t = false;
            else
                p_p_t = true;
            calcula_foco();
        }
    }
    if (key == '1'){
        p_p_t = false;
        primeira_pessoa = true;
        dist = -50;
        dist_z = 0;
    }
    if (key == '2'){
        p_p_t = false;
        primeira_pessoa = false;
        dist = 120;
        dist_z = 120;
    }
    if (key == '3'){
        p_p_t = false;
        primeira_pessoa = false;
        dist = 200;
        dist_z = 150;
    }
    if (key == '4'){
        p_p_t = false;
        primeira_pessoa = false;
        dist = 300;
        dist_z = 300;
    }
    if (key == '+'){ // Câmera se aproxima do avião
        dist -= 10;
        if(dist <= 120)
            dist = 120;
    }
    if (key == '-'){ // Câmera se afasta do avião
        dist += 10;
        if(dist >= 300)
            dist = 300;
    }
    if (key == 'w') {
        angulo = rot*(3.14159/180);
        mover[0] += cos(angulo) * 2;
        mover[1] += sin(angulo) * 2;

        calcula_pos_camera();
        calcula_foco();
        calcula_view_up();
    }

    if (key == 'a') {
        rot += 1.0;
        calcula_pos_camera();
        calcula_foco();
        calcula_view_up();
    }

    if (key == 'd') {
        rot -= 1.0;
        calcula_pos_camera();
        calcula_foco();
        calcula_view_up();
    }
    display();
}

int main(int argc, char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Trabalho 2");

    glutTimerFunc(33, voo, 10);

    std::cout<<"Ola, voce gostaria de jogar com qual aviao?"<<std::endl;
    std::cout<<"0 para aviao comercial\n1 para aviao da segunda guerra \n2 para aviao futuristico"<<std::endl;
    std::cin>>escolha_aviao;

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glutMainLoop();
    return 0;
}

