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

typedef _vertex3<float> vectorRGB ;


#define PI 3.1415926
using namespace std;

typedef _vertex3<float> vectorRGB ;

class Material ;
class Textura  ;
   
// posibles modos de generacion de coords. de textura
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

void Normales_Vertices(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &normales_caras, vector<_vertex3f> &normales_vertices);
void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3i> &caras,vector<_vertex3f> &normales_vertices);
_vertex3f Normalizar(_vertex3f vertice);

void draw (vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int opc);
void draw (vector<float> &vertices, vector<int> &caras, int opc);

// devuelve el mínimo de sus dos argumentos
inline float minim( float a, float b )
{
   return a < b ? a : b ;
}

// devuelve el maximo de sus dos argumentos
inline float maxim( float a, float b )
{
   return a < b ? b : a ;
}





class FuenteLuz
{
   public:
   
   FuenteLuz( GLenum p_ind_fuente, GLfloat p_longi_ini, GLfloat p_lati_ini, const vectorRGB & p_color ) ; 
   
   void activar() ;
   
   bool gestionarEventoTeclaEspecial( int key ) ; 

   protected:
   
   GLenum
      ind_fuente ;// indice de la fuente de luz 
                  // (entre GL_LIGHT0 y GL_LIGHT0+máx.núm.fuentes)
   GLfloat 
      longi,      // longitud actual de la fuente direccional (entre 0 y 360)
      lati,       // latitud actual de la fuente direccional (entre -90 y 90)
      longi_ini,  // valor inicial de 'longi'
      lati_ini ;  // valor inicial de 'lati'
   _vertex3f
      col_ambiente,  // color de la fuente para la componente ambiental
      col_difuso,    // color de la fuente para la componente difusa
      col_especular; // color de la fuente para la componente especular
   
} ;

class Material
{
   public:
   
   // crea un material con un color plano blanco sin textura 
   // ni iluminación
   Material() ;     
   
   // crea un material con una textura asociada, y con la iluminación activada.
   // 'nombreArchivoJPG' nombre del archivo que contiene la imagen de text.
   Material( const string & nombreArchivoJPG ) ;
   
   // libera la memoria dinámica ocupada por el material
   ~Material() ;    
   
   // cambia el estado de OpenGL de forma que a partir de la llamada
   // se usaran los atributos de este material como valores de los parámetros
   // en la evaluación del MIL durante la visualización de primitivas
   void activar() ; 
  
    //--------------------------------------------------------
   
   void coloresCero();// pone todos los colores y reflectividades a cero
   
   bool iluminacion;
                     
   Textura *
      tex ;          // si !=NULL, el material tiene esta textura
   GLuint 
      ident_textura ;// identificador de textura, si tiene_textura=true
   _vertex3f
      color ;        // color del material cuando iluminacion=false 
   ColoresMat
      del,           // reflectividades de caras delanteras, si iluminacion= true
      tra ;          // reflectividades de caras traseras, si iluminacion=true
};

class Objeto {
  	_vertex4f Point_color;

   vector<_vertex3f> Vertices;
   vector<_vertex3i> Faces_vertices;
   vector<_vertex3f> Faces_normals;

   vector<_vertex3f> Vertices_normals;
   vector<_vertex2f> Vertices_tex_coords; 
   
   Material * material;

   bool Faces_normals_computed;
   bool Vertices_normals_computed;
   bool Vertices_tex_coords_computed;
   
  	_vertex4f Line_color;
  	_vertex4f Solid_color;
  	_vertex4f Solid_chess_color1;
	_vertex4f Solid_chess_color2;
 	
   public:
      Objeto();
      Objeto(vector<float> Vertices1,vector<int> Faces1);
      //int create(vector<float> Vertices1, vector<int> Faces1);
      int create(vector<_vertex3f> Vertices1,vector<_vertex3i> Faces1);
      void draw_solid_material_flat();
      void draw_solid_material_gouroud();
      
     	//void draw( _draw_type Draw_type );
   	void compute_faces_normals();
     	void compute_vertices_normals();

   void draw_points()
   {
   cout << "Entro en el draw_points" << endl;
   //glColor4f(Point_color[0],Point_color[1],Point_color[2],Point_color[3]);

   glBegin(GL_POINTS);
      for (int i = 0; i < Vertices.size(); ++i)
         glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
   glEnd();
   }

};