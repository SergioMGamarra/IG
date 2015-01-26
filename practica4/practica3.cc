//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include "file_ply_stl.h"
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"
#include <iostream>
using namespace std;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************


/*
 * Practica 4
*/

vector<float> verticesLat;
vector<int> carasLat;
vector<_vertex3f> verticesLata;
vector<_vertex3i> carasLata;
vector<_vertex3f> tapaSupVert;
vector<_vertex3i> tapaSupCar;
vector<_vertex3f> tapaInfVert;
vector<_vertex3i> tapaInfCar;

std::vector<float> vertices_1;
std::vector<int> caras_1;
std::vector<float> vertices_2;
std::vector<int> caras_2;
std::vector<float> vertices_3;
std::vector<int> caras_3;

float alfa = 0;
float beta = 0;

bool Ini=false;
FuenteLuz * fuente_luz_0 = NULL, * fuente_luz_1 = NULL;
//Material ColaTex("text-lata-1.jpg");

Objeto * CocaCola = NULL;

// Vertices del tetraedro

vector<_vertex3f> Vertices;
vector<_vertex3i> Caras;
vector<_vertex3f> Tapas;

vector<_vertex3f> Vertices_cubo;
vector<_vertex3i> Caras_cubo;

vector<_vertex3f> Vertices_beth;
vector<_vertex3i> Caras_beth;

vector<_vertex3f> Vertices_cilindro;
vector<_vertex3i> Caras_cilindro;
vector<_vertex3f> Tapas_cilindro;

vector<_vertex3f> Vertices2;
vector<_vertex3i> Caras2;
vector<_vertex3f> Tapas2;


// Vector para guardar los pares de coordenadas de la textura y del objeto
vector<GLfloat> texturas; 

vector<float> vertic;
vector<int> faces;

char *nombre_ply;

int revoluciones = 40;
int grado_rotatoria = 0;
int translacion_carga = 0;
int tamanio_hilos = 10;
int movimiento_lateral = 0;
int angulo = 0;


/*
    Control de teclado
*/
int opc = 3;
int opcFigura = 5; 
int opcFiguraAux = 5;
bool practica4 = false;



void FloatToVertexf(vector<float> &vect, vector<_vertex3f> &result) {
    result.resize(vect.size()/3);
    for (int i = 0; i < vect.size()/3; ++i) {
        result[i].x = vect[3*i];
        result[i].y = vect[3*i+1];
        result[i].z = vect[3*i+2];
    }
}


void FloatToVertexf(vector<float> &vect, vector<_vertex3f> &vertices, vector<_vertex3f> &tapas)  {
    vertices.resize(0);
    tapas.resize(0);
    int contador_tapa = 0;
    for (int i = 0; i < vect.size()/3; ++i) {
        if (vect[i*3] == 0 && vect[i*3+2] == 0 && contador_tapa < 2) {
            tapas.resize(tapas.size()+1);
            tapas[contador_tapa].x = vect[i*3];
            tapas[contador_tapa].y = vect[i*3+1];
            tapas[contador_tapa].z = vect[i*3+2];
        }else {
            vertices[i-contador_tapa].x = vect[i*3];
            vertices[i-contador_tapa].y = vect[i*3+1];
            vertices[i-contador_tapa].z = vect[i*3+2];
        }
    }
}


void IntToVertexi(vector<int> &vect, vector<_vertex3i> &result) {
    result.resize(vect.size()/3);
    for (int i = 0; i < vect.size(); ++i) {
        result[i].x = vect[3*i];
        result[i].y = vect[3*i+1];
        result[i].z = vect[3*i+2];
    }
}


void leer_datos_ply(vector<float> &vertic, vector<int> &faces, char *nombre) {
    _file_ply ply;

    ply.open(nombre);
    ply.read(vertic, faces);
    ply.close();
}

void leer_datos_ply(vector<_vertex3f> &vertices, vector<_vertex3f> &tapas, vector<_vertex3i> &caras, char *nombre) {
    _file_ply ply;

    ply.open(nombre);
    ply.read(vertic, faces);
    ply.close();

}


void leer_datos_tetraedro(vector<_vertex3f> &Vertices, vector<_vertex3i> &triangles)  {
    vector<_vertex3f> V(4);
    Vertices = V;

    Vertices[0].x =  0.0f;
    Vertices[0].y =  0.448f;
    Vertices[0].z =  0.0f;

    Vertices[1].x = -0.44f;
    Vertices[1].y = -0.448f;
    Vertices[1].z = -0.5f;

    Vertices[2].x = -0.44f;
    Vertices[2].y = -0.448f;
    Vertices[2].z =  0.5f;

    Vertices[3].x =  0.44f;
    Vertices[3].y = -0.448f;
    Vertices[3].z =  0.0f;

    vector<_vertex3i> T(4);
    triangles = T;

    triangles[0].x = 0;
    triangles[0].y = 1;
    triangles[0].z = 2;

    triangles[1].x = 3;
    triangles[1].y = 1;
    triangles[1].z = 2;

    triangles[2].x = 2;
    triangles[2].y = 0;
    triangles[2].z = 3;

    triangles[3].x = 0;
    triangles[3].y = 1;
    triangles[3].z = 3;
}

void leer_datos_cubo(vector<_vertex3f> &Vertices, vector<_vertex3i> &triangles)  {

    vector<_vertex3f> V(8);
    Vertices = V;

    Vertices[0].x = -0.5f;
    Vertices[0].y =  0.5f;
    Vertices[0].z =  0.5f;

    Vertices[1].x = -0.5f;
    Vertices[1].y = -0.5f;
    Vertices[1].z =  0.5f;

    Vertices[2].x =  0.5f;
    Vertices[2].y = -0.5f;
    Vertices[2].z =  0.5f;

    Vertices[3].x =  0.5f;
    Vertices[3].y =  0.5f;
    Vertices[3].z =  0.5f;
    
    Vertices[4].x = -0.5f;
    Vertices[4].y =  0.5f;
    Vertices[4].z = -0.5f;

    Vertices[5].x = -0.5f;
    Vertices[5].y = -0.5f;
    Vertices[5].z = -0.5f;

    Vertices[6].x =  0.5f;
    Vertices[6].y = -0.5f;
    Vertices[6].z = -0.5f;

    Vertices[7].x =  0.5f;
    Vertices[7].y =  0.5f;
    Vertices[7].z = -0.5f;


    vector<_vertex3i> T(12);
    triangles = T;

//------------------------

    triangles[0].x = 0;
    triangles[0].y = 1;
    triangles[0].z = 3;

    triangles[1].x = 1;
    triangles[1].y = 2;
    triangles[1].z = 3;

//------------------------

    triangles[2].x = 2;
    triangles[2].y = 5;
    triangles[2].z = 1;

    triangles[3].x = 2;
    triangles[3].y = 6;
    triangles[3].z = 5;

//------------------------

    triangles[4].x = 7;
    triangles[4].y = 4;
    triangles[4].z = 0;

    triangles[5].x = 7;
    triangles[5].y = 3;
    triangles[5].z = 0;

//-----------------------

    triangles[6].x = 7;
    triangles[6].y = 3;
    triangles[6].z = 2;

    triangles[7].x = 6;
    triangles[7].y = 2;
    triangles[7].z = 7;


//----------------------

    triangles[8].x = 4;
    triangles[8].y = 6;
    triangles[8].z = 7;

    triangles[9].x = 6;
    triangles[9].y = 5;
    triangles[9].z = 4;

//----------------------

    triangles[10].x = 0;
    triangles[10].y = 4;
    triangles[10].z = 5;

    triangles[11].x = 0;
    triangles[11].y = 5;
    triangles[11].z = 1;

}

void leer_datos_revo(vector<_vertex3f> &Vertices, vector<_vertex3i> &triangles, vector<_vertex3f> &tap)  {

    //leer_datos_ply(Vertices, tap, triangles, nombre_ply_rev);


    vector<_vertex3f> V(2);
    tap.resize(2);
    Vertices = V;

    Vertices[0].x =  0.5f;
    Vertices[0].y =  -0.5f;
    Vertices[0].z =  0.0f;

    Vertices[1].x =  0.5f;
    Vertices[1].y = 0.5f;
    Vertices[1].z =  0.0f;

    tap[1].x = 0.0f;
    tap[1].y = 0.5f;
    tap[1].z = 0.0f;
 
    tap[0].x = 0.0f;
    tap[0].y = -0.5f;
    tap[0].z = 0.0f;

    generateRotatePoints(Vertices, triangles, tap, revoluciones) ;
    cout << "Termino la funcion leer_datos_revo" << endl;
}

void leer_datos_revo2(vector<_vertex3f> &Vertices, vector<_vertex3i> &triangles, vector<_vertex3f> &tap)  {

    cout << "Leido revo 2" << endl;
    vector<_vertex3f> V(2);
    tap.resize(0);
    tap.clear();
    Vertices = V;

    Vertices[0].x =  0.5f;
    Vertices[0].y =  -0.5f;
    Vertices[0].z =  0.0f;

    Vertices[1].x =  0.5f;
    Vertices[1].y =  0.5f;
    Vertices[1].z =  0.0f;


    tap[0].x = 0.0f;
    tap[0].y = -0.5f;
    tap[0].z = 0.0f;

    generateRotatePoints(Vertices, triangles, tap, revoluciones) ;
    cout << "Termino la funcion leer_datos_revo2" << endl;
}

void leer_datos_revo3(vector<_vertex3f> &Vertices, vector<_vertex3i> &triangles, vector<_vertex3f> &tap)  {

    cout << "Leido revo 3" << endl;

    vector<_vertex3f> V(2);
    tap.resize(1);
    Vertices = V;

    Vertices[0].x =  0.4f;
    Vertices[0].y =  0.5f;
    Vertices[0].z =  0.0f;

    Vertices[1].x =  0.6f;
    Vertices[1].y = -0.5f;
    Vertices[1].z =  0.0f;

    tap[0].x = 0.0f;
    tap[0].y = 0.5f;
    tap[0].z = 0.0f;

    generateRotatePoints(Vertices, triangles, tap, revoluciones) ;
    cout << "Termino la funcion leer_datos_revo2" << endl;
}

void leer_datos_revo4(vector<_vertex3f> &Vertices, vector<_vertex3i> &triangles, vector<_vertex3f> &tap)  {

    cout << "Leido revo 4" << endl;

    vector<_vertex3f> V(2);
    tap.resize(1);
    Vertices = V;

    Vertices[0].x =  0.4f;
    Vertices[0].y =  0.5f;
    Vertices[0].z =  0.0f;

    Vertices[1].x =  0.6f;
    Vertices[1].y = -0.5f;
    Vertices[1].z =  0.0f;

    generateRotatePoints(Vertices, triangles, tap, revoluciones) ;
    cout << "Termino la funcion leer_datos_revo2" << endl;
}

void dibujar( vector<_vertex3f> &vertices, vector<_vertex3i> &caras){
    if (opc == 1) draw_points(vertices);
    else if (opc == 2) draw_alambre_revo(vertices, caras);
    else if (opc == 3) draw_solid(vertices, caras);
    else if(opc == 4) draw_ajedrez(vertices,caras);
}

void cubo (vector<_vertex3f> vertices, vector<_vertex3i> caras) {
    dibujar(vertices, caras);
}

void cubo_carga(const vector<_vertex3f> &vertices, const vector<_vertex3i> &caras)  {
    glPushMatrix();
        glColor3f(0.2,0.2,0.2);
        glScalef(10.0, 4.0, 10.0);
        cubo(vertices, caras);
    glPopMatrix();

}


void palo(const vector<_vertex3f> &vertices, const vector<_vertex3i> &caras)  {
    glPushMatrix();
        glColor3f(0.0,0.0,1.0);
        glScalef(0.5, 0.5, 5.5);
        cubo(vertices, caras);
    glPopMatrix();
}

void palo_transversal(const vector<_vertex3f> &vertices, const vector<_vertex3i> &caras)  {
    glPushMatrix();
        glColor3f(0.0,0.0,1.0);
        glScalef(0.5, 0.5, 6.5);
        cubo(vertices, caras);
    glPopMatrix();
}


void seccion_cubo_altura(const vector<_vertex3f> &vertices, const vector<_vertex3i> &caras) {
    glPushMatrix();
        glTranslatef(0.0, 2.5, 0.0);
        glRotatef(90.0, 0, 1, 0);
        palo(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(2.5, 0.0, 0.0);
        glRotatef(90.0, 0, 1, 0);
        glRotatef(90.0, 1, 0, 0);
        palo(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, -2.5, 0.0);
        glRotatef(90.0, 0, 1, 0);
        palo(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-2.5, 0.0, 0.0);
        glRotatef(90.0, 0, 1, 0);
        glRotatef(90.0, 1, 0, 0);
        palo(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glRotatef(90.0, 0, 1, 0);
        glRotatef(45.0, 1, 0, 0);
        palo_transversal(vertices, caras);
    glPopMatrix();

}

void seccion_altura(const vector<_vertex3f> &vertices, const vector<_vertex3i> &caras) {
    glPushMatrix();
        glTranslatef(0,0,2.5);
        seccion_cubo_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0,-2.5);
        seccion_cubo_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-2.5,0,0);
        glRotatef(90.0,0, 1,0);
        seccion_cubo_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(3.0,0,0);
        glRotatef(90.0,0, 1,0);
        seccion_cubo_altura(vertices, caras);
    glPopMatrix();
}

void altura(const vector<_vertex3f> &vertices, const vector<_vertex3i> &caras)  {
    glPushMatrix();
        glTranslatef(0.0,2.5,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,8.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,13.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();    
    glPushMatrix();
        glTranslatef(0.0,18.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();    
    glPushMatrix();
        glTranslatef(0.0,23.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,28.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,33.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,38.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,43.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,48.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,53.0,0);
        seccion_altura(vertices, caras);
    glPopMatrix();
}


void torre_altura( vector<_vertex3f> &vertices,  vector<_vertex3i> &caras)  {
    glPushMatrix();
        glTranslatef(0.0,0,0);
        cubo_carga(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        altura(vertices, caras);
    glPopMatrix();
}

void torre_horizontal( vector<_vertex3f> &vertices,  vector<_vertex3i> &caras)  {
    glPushMatrix();
        glTranslatef((53.0/2),53.0,0.0);
        glRotatef(90.0,0,0,1);
        altura(vertices, caras);
    glPopMatrix();

}

void union_secciones( vector<_vertex3f> &vertices,  vector<_vertex3i> &caras) {
    glPushMatrix();
        glRotatef(90.0,0,1,0);
        torre_horizontal(vertices, caras);
    glPopMatrix();


}

void seccion_grua(vector<_vertex3f> &vertices, vector<_vertex3i> &caras)  {
    glPushMatrix();
        glTranslatef((53.0/2-2.25),0.0,0.0);
        torre_altura(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        torre_horizontal(vertices, caras);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-(53.0/2),0.0,0.0);
        torre_altura(vertices, caras);
    glPopMatrix();

}

void plataforma_carga(vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {
    glPushMatrix();
        glTranslatef(0.0,58,0.0);
        glColor3f(0.0,0.0,0.0);
        glScalef(8.0,3.0,58.0);
        cubo(vertices, caras);
    glPopMatrix();

}

void plataforma_rotatoria(vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {
    glPushMatrix();
        glTranslatef(0.0,55,0.0);
        glColor3f(0.2,0.2,0.2);
        glScalef(8.0,3.0,8.0);
        cubo(vertices, caras);
    glPopMatrix();

}

void hilo(int tamanio, vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {

    glPushMatrix();
        glTranslatef(0.0,55.0,0.0);
        glTranslatef(0.0, -tamanio/2, 0.0);
        glColor3f(0.7,0.0,0.0);
        glScalef(1.0,3.0+tamanio,1.0);
        cubo(vertices, caras);
    glPopMatrix();

}

void caja( vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {

    glPushMatrix();
        glColor3f(0.3,0.3,1.0);
        glTranslatef(0.0,53,0.0);
        glScalef(8.0,8.0,8.0);
        cubo(Vertices, caras);
    glPopMatrix();
}

void cilindro(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &tapas) {
    glPushMatrix();
        glTranslatef(0.0,0.0,0.0);
        dibujar(vertices, caras);
    glPopMatrix();
}

void control_animacion() {
    // 1. Control movimiento lateral
    // cout << "movimiento_lateral: " << movimiento_lateral << endl;
    if (movimiento_lateral < -18) movimiento_lateral = -18;
    else if (movimiento_lateral > 18) movimiento_lateral = 18;

    // 2.Control tamaño hilos
    // cout << "tamanio_hilos: " << tamanio_hilos << endl;
    if (tamanio_hilos < 8) tamanio_hilos = 8;
    else if(tamanio_hilos > 50) tamanio_hilos = 50;

    // 3. Control movimiento de plataforma rotatoria
    // cout << "translacion_carga: " << translacion_carga << endl;
    if (translacion_carga < -19) translacion_carga = -19;
    else if(translacion_carga > 16) translacion_carga = 16;

}


void grua(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &VC, vector<_vertex3i> &CC) {
    control_animacion();    
    leer_datos_cubo(VC, CC);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glRotatef(angulo, 0, 1, 0);
        glPushMatrix();
            glTranslatef(0.0,0.0,-(53.0/2));
            seccion_grua(VC, CC);
        glPopMatrix();

        // Seccion delantera
        glPushMatrix();
            glTranslatef(0.0,0.0,(53.0/2));
            seccion_grua(VC, CC);
        glPopMatrix();

        // Seccion trasera
        glPushMatrix();
            glTranslatef(0.0,0.0,-(53.0/2));
            seccion_grua(VC, CC);
        glPopMatrix();

        // Uniones
        glPushMatrix();
            glTranslatef((53.0/2)-2.25,0.0,0.0);
            union_secciones(VC, CC);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-((53.0/2)),0.0,0.0);
            union_secciones(VC, CC);
        glPopMatrix();


        glPushMatrix();
            glTranslatef(translacion_carga, 0.0,0.0);
            glPushMatrix();
                plataforma_carga(VC, CC);
            glPopMatrix();
            glPushMatrix();
                glColor3f(1.0,0.5,0.0);
                glTranslatef(0,64.5,0);
                glScalef(10,10,10);
                cilindro(Vertices_cilindro, Caras_cilindro, Tapas_cilindro);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0,0.0, movimiento_lateral);
                glRotatef(grado_rotatoria, 0, 1, 0);
                glPushMatrix();
                    plataforma_rotatoria(VC, CC);
                glPopMatrix();
                glPushMatrix();
                    glPushMatrix();
                        glTranslatef(0.0,0.0,3.0);
                        hilo(tamanio_hilos, VC, CC);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(0.0,0.0,-3.0);
                        hilo(tamanio_hilos, VC, CC);
                    glPopMatrix();
                    glPushMatrix();
                        glTranslatef(0,-tamanio_hilos,0);
                        glTranslatef(0.0,56.0,0.0);
                        //Beethoven
                        glRotatef(90, 0,1,0);
                        dibujar(Vertices_beth, Caras_beth);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}


void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimqo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


void draw_menu(int Opc, int OpcFig) {
        draw(Vertices, Caras, opc);
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects_4()
{
    // Activamos las fuentes de luz
    //fuente_luz_0->activar();
    //fuente_luz_1->activar();

    //Objeto PeonNegro;
    //PeonNegro.create(vertices_1, caras_1);
    //PeonNegro.draw_solid_material_flat();
    //PeonNegro->draw_solid_material_flat();
    //CocaCola->draw_solid_material_flat();
    CocaCola->draw_points();
}


void draw_objects(vector<_vertex3f> vertices, vector<_vertex3i> caras)
{
    if (practica4 == false) { 
        leer_datos_cubo(Vertices_cubo, Caras_cubo);
        grua(Vertices, Caras, Vertices_cubo, Caras_cubo);
        draw_menu(opc, opcFigura);
    } else  {
        draw_objects_4();
    }
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
clear_window();
change_observer();
draw_axis();
draw_objects(Vertices, Caras);
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

    if (toupper(Tecla1)=='4') {
        if (practica4 == false) practica4 = true;
        else practica4 = false;
    }

    if (practica4 == false)  {
        if (toupper(Tecla1)=='P') opc = 1;
        if (toupper(Tecla1)=='L') opc = 2;
        if (toupper(Tecla1)=='S') opc = 3;
        if (toupper(Tecla1)=='A') opc = 4;
        if (Tecla1=='C') grado_rotatoria++;
        if (Tecla1=='c') grado_rotatoria--;
        if (Tecla1 =='X') translacion_carga++;
        if (Tecla1 =='x') translacion_carga--;
        if (Tecla1 =='Z') angulo++;
        if (Tecla1 =='z') angulo--;
        if ((Tecla1)=='V') tamanio_hilos++;
        if ((Tecla1)=='v') tamanio_hilos--;
        if (toupper(Tecla1)=='G') movimiento_lateral++;
        if (toupper(Tecla1)=='H') movimiento_lateral--;


        if (toupper(Tecla1)=='1') {
            leer_datos_ply(vertic, faces, nombre_ply);
            IntToVertexi(faces, Caras_beth);
            FloatToVertexf(vertic, Vertices_beth);
        }
        if (toupper(Tecla1)=='2') leer_datos_revo(Vertices_cilindro, Caras_cilindro, Tapas_cilindro);
        if (toupper(Tecla1)=='3') opcFiguraAux = 3;
    } 
        
    draw(Vertices, Caras, opc);
    if (toupper(Tecla1)=='Y') alfa++;
    if (toupper(Tecla1)=='U') alfa--;
    if (toupper(Tecla1)=='I') beta++;
    if (toupper(Tecla1)=='O') beta--;


    glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del ratons
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
    // se inicalizan la ventana y los planos de corte
    Window_width=.5;
    Window_height=.5;
    Front_plane=1;
    Back_plane=1000;


    // se inicia la posicion del observador, en el eje z
    Observer_distance=32*Front_plane;

    Observer_angle_x=0;
    Observer_angle_y=0;

    // se indica cual sera el color para limpiar la ventana (r,v,a,al)
    // blanco=(1,1,1,1) rojo=(1,0,0,1), ...
    glClearColor(1,1,1,1);

    change_projection();
    glViewport(0,0,UI_window_width,UI_window_height);


    // Inicializamos las fuentes de luz
    fuente_luz_0 = new FuenteLuz(GL_LIGHT0, 80.0f, 50.0f, vectorRGB(1.0f,1.0f,1.0f));
    fuente_luz_1 = new FuenteLuz(GL_LIGHT1,-100.0f,-30.0f, vectorRGB(0.8f,0.3f,0.2f));

    Objeto * CocaCola = new Objeto(vertices_1, caras_1);
    CocaCola->create(verticesLata, carasLata);

}



//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    nombre_ply = "beethoven.ply";

    leer_datos_ply(vertices_1, caras_1, "lata-pcue.ply");

    IntToVertexi(caras_1, carasLata);
    FloatToVertexf(vertices_1, verticesLata);

    leer_datos_ply(vertices_2, caras_2, "lata-psup.ply");
    leer_datos_ply(vertices_3, caras_3, "lata-pinf.ply");


    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 4");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();




    // inicio del bucle de eventos
    glutMainLoop();

    return 0;
}
