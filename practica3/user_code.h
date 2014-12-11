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

void draw_cube(vector<_vertex3f> &vertices, vector<_vertex3i> &caras);
void draw_tetrahedron();
void draw_vertices(vector<float> &Vertices);
void draw_alambre (vector<_vertex3f> &vertices, vector<_vertex3i> &caras);
void draw_alambre_revo (vector<_vertex3f> &vertices, vector<_vertex3i> &caras);
void draw_solid (vector<_vertex3f> &vertices, vector<_vertex3i> &caras);
void draw_points (vector<_vertex3f> &vertices);
void draw_ajedrez (vector<_vertex3f> &vertices, vector<_vertex3i> &caras);
void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &tapas, int n);
void draw_points (vector<float> &vertices);
void draw_alambre (vector<float> &vertices,vector<int> &faces);
void draw_solid (vector<float> &vertices,vector<int> &faces);
void draw_ajedrez(vector<float> &vertices,vector<int> &faces);

void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3i> &caras,vector<_vertex3f> &normales_vertices);
_vertex3f Normalizar(_vertex3f vertice);

void draw (vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int opc);
void draw (vector<float> &vertices, vector<int> &caras, int opc);
