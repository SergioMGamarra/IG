//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <vector>
#include "file_ply_stl.h"
#include <iostream>
#include "vertex.h"
#include <cmath>
#define PI 3.1415926


using namespace std;


// Hay que declarar el vector como global para no tener que estar inicializandolo cada vez que se dibuja la figura

void draw_cube(vector<_vertex3f> &vertices, vector<_vertex3f> &caras);
void draw_tetrahedron();
void draw_vertices(vector<float> &Vertices);
void draw_alambre (vector<_vertex3f> &vertices, vector<_vertex3f> &caras);
void draw_solid (vector<_vertex3f> &vertices, vector<_vertex3f> &caras);
void draw_points (vector<_vertex3f> &vertices);
void draw_ajedrez (vector<_vertex3f> &vertices, vector<_vertex3f> &caras);
void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3f> &caras, int n);
void draw_points (vector<float> &vertices);
void draw_alambre (vector<float> &vertices,vector<int> &faces);
void draw_solid (vector<float> &vertices,vector<int> &faces);
void draw_ajedrez(vector<float> &vertices,vector<int> &faces);
void draw (vector<_vertex3f> &vertices, vector<_vertex3f> &caras, int opc);
void draw (vector<float> &vertices, vector<int> &caras, int opc);
