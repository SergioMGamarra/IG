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

// Vertices del tetraedro

vector<_vertex3f> Vertices;
vector<_vertex3f> Caras;

vector<float> vertic;
vector<int> faces;

char *nombre_ply;
char *nombre_ply2;

int opc = 1;
int opcFigura = 5; 
int opcFiguraAux = 5;

void leer_datos_ply(vector<float> &vertic, vector<int> &faces, char *nombre) {
    _file_ply ply;

    ply.open(nombre);
    ply.read(vertic, faces);
    ply.close();
}


void leer_datos_tetraedro(vector<_vertex3f> &Vertices, vector<_vertex3f> &triangles)  {
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

    vector<_vertex3f> T(4);
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

void leer_datos_cubo(vector<_vertex3f> &Vertices, vector<_vertex3f> &triangles)  {

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


    vector<_vertex3f> T(12);
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

void leer_datos_rebo(vector<_vertex3f> &Vertices, vector<_vertex3f> &triangles)  {
    vector<_vertex3f> V(2);
    Vertices = V;


    Vertices[0].x =  0.5f;
    Vertices[0].y =  0.5f;
    Vertices[0].z =  0.0f;

    Vertices[1].x =  0.5f;
    Vertices[1].y = -0.5f;
    Vertices[1].z =  0.0f;

    generateRotatePoints(Vertices, triangles,4) ;

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

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
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
    if (OpcFig == 1 || opcFigura == 2 || opcFigura == 5) {
        draw(Vertices, Caras, opc);
    }else {
        draw(vertic, faces, opc);
    }
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
    draw_menu(opc, opcFigura);

}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
clear_window();
change_observer();
draw_axis();
draw_objects();
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
    if (toupper(Tecla1)=='Q') exit(0);
    if (toupper(Tecla1)=='P') opc = 1;
    if (toupper(Tecla1)=='A') opc = 2;
    if (toupper(Tecla1)=='S') opc = 3;
    if (toupper(Tecla1)=='C') opc = 4;
    if (toupper(Tecla1)=='1') opcFiguraAux = 1;
    if (toupper(Tecla1)=='2') opcFiguraAux = 2;
    if (toupper(Tecla1)=='3') opcFiguraAux = 3;
    if (toupper(Tecla1)=='4') opcFiguraAux = 4;
    if (toupper(Tecla1)=='5') opcFiguraAux = 5;



    if(opcFiguraAux != opcFigura)   {
        opcFigura = opcFiguraAux;
        switch (opcFigura)  {
            case 1:
                leer_datos_cubo(Vertices, Caras);
                break;
            case 2:
                leer_datos_tetraedro(Vertices, Caras);
                break;
            case 3:
                leer_datos_ply(vertic, faces,  nombre_ply);
                break;                
            case 4:
                leer_datos_ply(vertic, faces,  nombre_ply2);
                break;   
            case 5:
                leer_datos_rebo(Vertices, Caras);
                break;
        } 
    }
    
    if (opcFigura == 1 || opcFigura == 2 || opcFigura == 5)
        draw(Vertices, Caras, opc);
    else 
        draw(vertic, faces, opc);
    
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
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

    if (argc > 2) {
        nombre_ply = argv[1];
        nombre_ply2 = argv[2];
    }


    leer_datos_cubo(Vertices, Caras);
    //leer_datos_tetraedro(Vertices, Caras);



    // se llama a la inicialización de glut
    glutInit(&argc, argv);

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
    glutCreateWindow("Práctica 1");

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
