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
#include "jpg_imagen.hpp"
#include <iostream>
#include "vertex.h"
#include <cmath>
#define PI 3.1415926


using namespace std;

typedef _vertex3<float> vectorRGB ;

typedef enum 
{  mgct_desactivada,  
   mgct_coords_objeto, 
   mgct_coords_ojo 
} 
   ModoGenCT ;

struct ColoresMat
{
   _vertex3f
      emision,    // color de la emisividad del material
      ambiente,   // reflectividad para la componente ambiental (M_A)
      difusa,     // reflectividad para la componente difusa (M_D)
      especular ; // reflectividad para la componente especular (M_S)
   GLfloat
      exp_brillo ; // exponente de brillo especular
} ;

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

void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3i> &caras,vector<_vertex3f> &normales_vertices);
_vertex3f Normalizar(_vertex3f vertice);

void draw (vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int opc);
void draw (vector<float> &vertices, vector<int> &caras, int opc);


class FuenteLuz
{
	public:

		FuenteLuz( GLenum p_ind_fuente, GLfloat p_longi_ini, GLfloat p_lati_ini, const vectorRGB & p_color ) ; 

		void activar() ;

		bool gestionarEventoTeclaEspecial( int key ) ; 

	protected:

		GLenum
		  ind_fuente ; 
		              
		GLfloat 
		  longi,     
		  lati,       
		  longi_ini,  
		  lati_ini ;

		_vertex3f
		  col_ambiente,  // color de la fuente para la componente ambiental
		  col_difuso,    // color de la fuente para la componente difusa
		  col_especular; // color de la fuente para la componente especular
};

class Textura
{
	public:
		Textura( const std::string & nombreArchivoJPG );
		~Textura() ; 
		void activar() ;

	protected: 

		GLuint ident_textura;
		unsigned tamx, tamy;
		unsigned char * texels;
		ModoGenCT modo_gen_ct ;
		GLfloat coefs_s[4], coefs_t[4];   
};


class Material
{
	public:
		Material() ;     
		Material( const std::string & nombreArchivoJPG );
		~Material();
		void activar() ; 
		void Madera();

		//--------------------------------------------------------

		void coloresCero();

		bool 
		  iluminacion;  
		Textura *
		  tex ;          
		GLuint 
		  ident_textura;
		_vertex3f
		  color;
		ColoresMat
		  del,           
		  tra;          
};


class Objeto {
private:
	vector <_vertex3f> Vertices;
	vector <_vertex3i> Caras;

	vector <_vertex3f> Vertices_normals;
	vector <_vertex3f> Faces_normals;

	vector<_vertex2f> Vertices_tex_coords;

	GLuint ident_textura;
	unsigned tamx, tamy;
	unsigned char * texels;

	_vertex4f Solid_color;

	Material * material;

	int num_vert_ply;


	float refl_amb, // reflectividad de la componente ambiental
      refl_dif,  // reflectividad de la componente difusa
      refl_esp,  // reflectividad de la componente especular
      exp_brillo ; // exponente de brillo

   
   _vertex3f 
      fesc , // factores de escala
      despl ; // desplazamiento


public:
	Objeto();
	void compute_vertices_normals();
	void compute_faces_normals();
	void compute_text_coord();
	void create(vector<_vertex3f> Vert, vector <_vertex3i> Faces);
	void draw_points();
	void Negro();
	void draw_solid_flat();
	void draw_solid_flat2();
	void draw_solid_material_gouroud();
	void Madera();
	void CocaCola();
};



