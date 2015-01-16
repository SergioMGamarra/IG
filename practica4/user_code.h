//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "file_ply_stl.h"
#include <iostream>
#include "vertex.h"
#include <cmath>
#include "jpg_imagen.hpp"


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
void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int n);
void draw_points (vector<float> &vertices);
void draw_alambre (vector<float> &vertices,vector<int> &faces);
void draw_solid (vector<float> &vertices,vector<int> &faces);
void draw_ajedrez(vector<float> &vertices,vector<int> &faces);

void Normales_Vertices(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &normales_caras, vector<_vertex3f> &normales_vertices);
void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3i> &caras,vector<_vertex3f> &normales_vertices);
_vertex3f Normalizar(_vertex3f vertice);

void draw (vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int opc);
void draw (vector<float> &vertices, vector<int> &caras, int opc);


//bool cargarImagen ();


class draw_practica_4_ 
{
   public:

// Atributos 

	vector<float> vertices;
	vector<int> caras;
		
	vector<_vertex3f> Vertices3f;
	vector<_vertex3f> Triangulos3f;

	vector<_vertex3f> Normal_triangulos;
	vector<_vertex3f> Normal_vertices; 
	vector<_vertex2f>  Vertices_tex_coords ; 
	vector<float> Vertices;

// variable filas
	unsigned int N;

// variable columnas	
	unsigned tamx; 
	unsigned tamy; 
	unsigned char * texels;
	float M;
	float angulo;
	float valor_vertices;
	float valor_triangulos;
	float valor_total_triangulos;
	float tamanio;
	GLuint idTex;
	bool es_automatico_;

// Métodos

	draw_practica_4_ ();
	void  crear_textura_lata();
	void  obtener_valores(vector<float> Vertices_);
	void  obtener_normales_vertices();
	void  obtener_normales_triangulos();
	void  draw_puntos();
	void  draw_alambre();
	void  draw_solido();
	void  draw_ajedrez();
	void  draw_solido_suave_(int es_automatico_); 
	void  draw_solido_plano_(int es_automatico_) ; 
	void  calcular_vertices();
	void  calcular_triangulos();
	void  fuentes_luz(float alfa_, float beta_);
	void  Luz (bool encendedor);
	void  material (bool encendedor);    
	void  metalico();
	void  cocacola();
	
};




// creamos como estructura de datos para los peones
class draw_practica_4_2_  {
    private:

// atributos

	unsigned tamx2; 
	unsigned tamy2;
	unsigned char * texels2;
	vector<float> Vertices;
	vector<_vertex3f> Vertices3f;
	vector<_vertex3f> Triangulos3f;
	vector<_vertex3f> Normal_vertices;
	vector<_vertex3f> Normal_triangulos;
	vector<_vertex2f>  Vertices_tex_coords ;
	float angulo;

// variable filas
	unsigned int N;

// variable columnas	
	float M;

	float valor_vertices;
	float valor_triangulos;
	float valor_total_triangulos;
	float tamanio;
	GLuint idTex2;
	unsigned tamx; 
	unsigned tamy; 
	unsigned char * texels;
    public:
	
// métodos
	draw_practica_4_2_(){

// Aquí modificamos el angulo 
	angulo=45;
		}

void obtener_valores(vector<float> Vertices_);
void obtener_vertices();
void obtener_triangulos();
void obtener_tapaderas();
void obtener_normales_triangulos();
void obtener_normales_vertices();
void opciones_display();
void draw_puntos();
void draw_solido_suave_(int es_automatico_); 
void draw_solido_plano_(int es_automatico_); 
void crear_textura_madera();
void madera();
void Luz(bool encendedor);
void material(bool encendedor);
void draw_alambre();
void draw_solido();	
void draw_ajedrez();
void negro();
void blanco();
};
