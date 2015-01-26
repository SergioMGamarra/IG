//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"

using namespace std;

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_tetaedro() {
	GLfloat Vertices[4][3] = {{-0.5,-0.5,-0.5},{-0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5}};

	glBegin(GL_POINTS);
    for (unsigned i=0;i<3;i++) {
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();
}

void draw_alambre_revo (vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {
	glColor3f(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < caras.size(); ++i) {
			glBegin(GL_LINES);
				glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
				glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
				glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
				glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
			glEnd();

		}
}
void draw_alambre (vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		for (int i = 0; i < caras.size(); ++i) {
			glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
			glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
			glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
		}
	glEnd();
}

void draw_solid (vector<_vertex3f> &vertices, vector<_vertex3i> &caras)  {
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < caras.size(); ++i) {
			glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
			glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
			glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
		}
	glEnd();
}

void draw_points (vector<_vertex3f> &vertices) {
	glPointSize(2.0f);
	glBegin(GL_POINTS);
		for (int i = 0; i < vertices.size(); ++i)
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	glEnd();
}

void draw_ajedrez(vector<_vertex3f> &vertices, vector<_vertex3i> &caras) {
	for (int i = 0; i < caras.size(); ++i) {
		if (i%2==0)
			glColor3f(1.0,0.0,0.0);
		else 
			glColor3f(0.0,0.0,1.0);

		glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
		glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
		glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < caras.size(); i+=2) {
			glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
			glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
			glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
		}
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		for (int i = 1; i < caras.size(); i+=2) {
			glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
			glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
			glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
		}
	glEnd();

}


void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &tapasV, int n)  {
	int tapas = tapasV.size();

	int num_elem_orig = vertices.size();
	vector<_vertex3f> tapa(2);

	vertices.resize(num_elem_orig*n);
	
	int m = n-1;

	for (int i = 0; i <= m; ++i) {
		double ang = i*(2*PI/m);
		for (int j = 0; j < num_elem_orig; ++j) {
			vertices[i*num_elem_orig+j].x = vertices[j].x * cos(ang) + vertices[j].z*sin(ang);
			vertices[i*num_elem_orig+j].y = vertices[j].y;
			vertices[i*num_elem_orig+j].z = -vertices[j].x * sin(ang) + vertices[j].z*cos(ang);
		}
	}
	// Obtenemos las caras
    caras.clear();
    caras.resize(0);
    int contador = 0;
    for (int i = 0; i < n-1; ++i)
    {
    	for (int j = 0; j < num_elem_orig-1; ++j)
    	{
    		caras.resize(caras.size()+2);
    		//cara par
    		caras[contador].x = i*num_elem_orig+j;
    		caras[contador].y = i*num_elem_orig+(j+1);
    		caras[contador].z = (i+1)*num_elem_orig+(j+1);

    		//Cara impar
    		caras[contador+1].x = i*num_elem_orig+j;
    		caras[contador+1].y = (i+1)*num_elem_orig+(j+1);
    		caras[contador+1].z = (i+1)*num_elem_orig+j;
    		contador+=2;
    	}
    }

	if (tapasV.size()>0)  {
		if (tapasV.size()==1) {
			vertices.resize(vertices.size()+1);
			vertices[vertices.size()-1]=tapasV[0];
		} else {
			vertices.resize(vertices.size()+2);
			vertices[vertices.size()-2]=tapasV[1];
			vertices[vertices.size()-1]=tapasV[0];
		}
	}

	if(tapas==2){
        caras.resize(caras.size()+2*n);

        for(int i=0;i<n-1;i++, contador++){
        	caras[contador].x = i*num_elem_orig;
        	caras[contador].y = vertices.size()-1;
        	caras[contador].z = (i+1)*num_elem_orig;
        }

        for(int i=0;i<n-1;i++, contador++){
        	caras[contador].x = num_elem_orig*i+(num_elem_orig-1);
        	caras[contador].y = vertices.size()-2;
        	caras[contador].z = (i+1)*num_elem_orig+(num_elem_orig-1);
        }

    }
    else if (tapas == 1)  {
    	caras.resize(caras.size()+n);
    	if(vertices[0].y == tapasV[0].y)  {
    		for(int i=0;i<n;i++){
	        	caras[contador+i].x = i*num_elem_orig;
	        	caras[contador+i].y = vertices.size()-1;
	        	caras[contador+i].z = (i+1)*num_elem_orig;
        	}

    	} else {
    		for(int i=0;i<n;i++){        	
    			caras[contador+i].x = num_elem_orig*i+(num_elem_orig-1);
	        	caras[contador+i].y = vertices.size()-1;
	        	caras[contador+i].z = (i+1)*num_elem_orig+(num_elem_orig-1);
	        
            }
    	}
    }

}

void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int n)  {

	int num_elem_orig = vertices.size();
	vertices.resize(num_elem_orig*n);
	
	int m = n-1;

	for (int i = 0; i <= m; ++i) {
		double ang = i*(2*PI/m);
		for (int j = 0; j < num_elem_orig; ++j) {
			vertices[i*num_elem_orig+j].x = vertices[j].x * cos(ang) + vertices[j].z*sin(ang);
			vertices[i*num_elem_orig+j].y = vertices[j].y;
			vertices[i*num_elem_orig+j].z = -vertices[j].x * sin(ang) + vertices[j].z*cos(ang);
		}
	}
	// Obtenemos las caras
    caras.clear();
    caras.resize(0);
    int contador = 0;
    for (int i = 0; i < n-1; ++i)
    {
    	for (int j = 0; j < num_elem_orig-1; ++j)
    	{
    		caras.resize(caras.size()+2);
    		//cara par
    		caras[contador].x = i*num_elem_orig+j;
    		caras[contador].y = i*num_elem_orig+(j+1);
    		caras[contador].z = (i+1)*num_elem_orig+(j+1);

    		//Cara impar
    		caras[contador+1].x = i*num_elem_orig+j;
    		caras[contador+1].y = (i+1)*num_elem_orig+(j+1);
    		caras[contador+1].z = (i+1)*num_elem_orig+j;
    		contador+=2;
    	}
    }
}

/*

+++++++++++++++++++++++++++++++++++ Funciones para PLY ++++++++++++++++++++++++++++++++++++++

*/

void draw_points (vector<float> &vertices) {
	glPointSize(1.0f);
	glBegin(GL_POINTS);
		for (unsigned int i = 0; i < vertices.size(); i+=3) {
			glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
		}
	glEnd();
}

void draw_alambre (vector<float> &vertices,vector<int> &faces) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		for (unsigned int i = 0; i < faces.size(); i+=2) {
			if (vertices[faces[i]*3+1] > 0 && vertices[faces[i+1]*3+1]> 0 &&  vertices[faces[i+2]*3+1] > 0) {
				glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
				glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
			}
		}
	glEnd();
}

void draw_solid (vector<float> &vertices,vector<int> &faces)  {

	glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < faces.size(); i+=3) {	
			if (vertices[faces[i]*3+1] > 0 && vertices[faces[i+1]*3+1]> 0 &&  vertices[faces[i+2]*3+1] > 0) {
				if (vertices[faces[i]*3]>0 && vertices[faces[i+1]*3]>0 && vertices[faces[i+2]*3]>0) {
					if(vertices[faces[i]*3+2] > 0 && vertices[faces[i+1]*3+2]> 0 &&  vertices[faces[i+2]*3+2] > 0)  {
						glColor3f(0.0f, 1.0f, 0.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
					} else if (vertices[faces[i]*3+2] < 0 && vertices[faces[i+1]*3+2] < 0 &&  vertices[faces[i+2]*3+2] < 0) {
						glColor3f(0.0f, 0.0f, 1.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
					}				
					else {
						glColor3f(0.0f, 0.0f, 0.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
					}
				} else if (vertices[faces[i]*3]<0 && vertices[faces[i+1]*3]<0 && vertices[faces[i+2]*3]<0)  {
					if(vertices[faces[i]*3+2] > 0 && vertices[faces[i+1]*3+2]> 0 &&  vertices[faces[i+2]*3+2] > 0)  {
						glColor3f(1.0f, 1.0f, 0.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
					} else if (vertices[faces[i]*3+2] < 0 && vertices[faces[i+1]*3+2] < 0 &&  vertices[faces[i+2]*3+2] < 0) {
						glColor3f(1.0f, 0.0f, 0.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
					}
					else {
						glColor3f(0.0f, 0.0f, 0.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
					}
				}					
				else {
						glColor3f(0.0f, 0.0f, 0.0f);
						glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
						glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
						glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
				}
			}
		}
	glEnd();
}


void draw_ajedrez(vector<float> &vertices,vector<int> &faces) {
	glPolygonMode(GL_FRONT, GL_FILL);
	int j = 0;
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < faces.size()-1; i+=3) {
		if (j == 0) {
			glColor3f(1.0, 0.0, 0.0);
			j = 1;
		}
		else {
			glColor3f(0.0, 0.0, 1.0);
			j = 0;
		}
		if (vertices[faces[i]*3+1] > 0 &&  vertices[faces[i+1]*3+1] > 0 &&  vertices[faces[i+2]*3+1] > 0) {
			glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
			glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
			glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
		}
	}
	glEnd();
}
/*	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size()-2; ++i) {
		if (vertices[faces[i]*3+1] > 0 && vertices[faces[i+1]*3+1]> 0 &&  vertices[faces[i+2]*3+1] > 0) {
			if(i*3%2 == 0) {
				glColor3f(1.0, 0.0, 0.0);
					glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
					glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
					glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
			} else  {
				glColor3f(0.0, 0.0, 1.0);
					glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
					glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
					glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
			}
		}
	}
	glEnd();
*/
	/*
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		for (int i = 0; i < faces.size()/2; i+=2) {		
			if (vertices[faces[i]*3+1] > 0 && vertices[faces[i+1]*3+1]> 0 &&  vertices[faces[i+2]*3+1] > 0) {
				glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
				glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
				glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
			}
		}
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		for (int i = 1; i < faces.size()/2; i+=2) {			
			if (vertices[faces[i]*3+1] > 0 && vertices[faces[i+1]*3+1]> 0 &&  vertices[faces[i+2]*3+1] > 0) {
				glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
				glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
				glVertex3f(vertices[faces[i+2]*3], vertices[faces[i+2]*3+1], vertices[faces[i+2]*3+2]);
			}
		}
	glEnd();
*/

/************************Normales*************************************
void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3i> &caras,vector<_vertex3f> &normales_caras)  {
	normales_caras.clear();
	normales_caras.resize(0);

	for(unsigned int i = 0; i < caras.size(); ++i)  {
		normales_caras.resize(normales_caras.size()+1);
		_vertex3f AB, BC, res;

		AB.x = vertices[caras[i].y].x - vertices[caras[i].x].x;
		AB.y = vertices[caras[i].y].y - vertices[caras[i].x].y;
		AB.z = vertices[caras[i].y].z - vertices[caras[i].x].z;

		BC.x = vertices[caras[i].z].x - vertices[caras[i].y].x;
		BC.y = vertices[caras[i].z].y - vertices[caras[i].y].y;
		BC.z = vertices[caras[i].z].z - vertices[caras[i].y].z;

		res.x = AB.y*BC.z - AB.z*BC.y;
		res.y = AB.z*BC.x - AB.x*BC.z;
		res.z = AB.x*BC.y - AB.y*BC.x;

		normales_caras[i] = Normalizar(res);

	}
}

// ****************************** Normalizar ***********************************
_vertex3f Normalizar(_vertex3f vertice) {
	double mod = sqrt(vertice.x+vertice.y+vertice.z);

	vertice.x = vertice.x / mod;
	vertice.y = vertice.y / mod;
	vertice.z = vertice.z / mod;

	return vertice;
}


void Normales_Vertices(vector<_vertex3f> &vertices, vector<_vertex3i> &caras, vector<_vertex3f> &normales_caras, vector<_vertex3f> &normales_vertices) {
	_vertex3f N;
	double mod;
	int contador_puntos = 0;
	normales_vertices.clear();
	normales_vertices.resize(vertices.size());
	for (unsigned int i = 0; i < vertices.size(); ++i)  {
		for(unsigned int j = 0; j < caras.size(); ++j) {
			if (caras[j].x== i || caras[j].y == i || caras[j].z == i) {
				N = normales_caras[i]; 
				contador_puntos++;
			}
		}
		N.x = N.x/contador_puntos;
		N.y = N.y/contador_puntos;
		N.z = N.z/contador_puntos;
		normales_vertices [i] = Normalizar(N);
		contador_puntos = 0;
		N = 0;
	}
}


*/
//************************Funcion draw ++++++++++++++++++++++++++++++

void draw (vector<_vertex3f> &vertices, vector<_vertex3i> &caras, int opc) {
	if (opc == 1) {
		draw_points(vertices);
	}
	else if (opc == 2)  {
		draw_alambre_revo(vertices,caras);
	}
	else if (opc == 3) {
		draw_solid(vertices,caras);
	}
	else if (opc == 4)
		draw_ajedrez(vertices, caras);
}

void draw (vector<float> &vertics, vector<int> &cars, int opc) {
	if (opc == 1)
		draw_points(vertics);
	else if (opc == 2)
		draw_alambre(vertics,cars);
	else if (opc == 3) {
		draw_solid(vertics,cars);
	}
	else if (opc == 4){
		draw_ajedrez(vertics, cars);
	}
}

/*
draw_practica_4_::draw_practica_4_()
{
	
	glPointSize(6);
	glLineWidth(4);
	angulo=10;

}

void draw_practica_4_::obtener_valores(vector<float> Vertices_){

	
		Vertices=Vertices_;
		
// Iniciamos los valores	
		valor_triangulos=0;
		valor_vertices=0; 
		N=360/angulo;
		M=(Vertices.size()/3); 
		tamanio=(M*N);

// Asignamos tamaño a los vectores 		
		Normal_vertices.resize(tamanio+2);
		Normal_triangulos.resize((tamanio*8)+(6*N));
		Vertices3f.resize(tamanio+2);
		Triangulos3f.resize((tamanio*8)+(6*N));		
		Vertices_tex_coords.resize(tamanio) ;

		calcular_vertices();
}
	

void draw_practica_4_::calcular_vertices(){

// Conseguimos el vector de puntos, vertices3f
				
	float Pi = 3.141, cons=N, cons2=M, coseno=cos(angulo/180*Pi),seno=sin(angulo/180*Pi), a, b, c, d, e, j=0;

	  for (unsigned i=0;i<M;i++){   
			
		for (unsigned h=0; h<N; h++){
			
		if( h == 0 ){
// Primer punto			
	
		Vertices_tex_coords[valor_vertices].x=0;
		
		
		a=Vertices3f[valor_vertices].x=Vertices[j];
		e=Vertices3f[valor_vertices].y=Vertices[j+1];
		b=Vertices3f[valor_vertices].z=Vertices[j+2];
		valor_vertices++;

		j=j+3;	
	}

// Generamos los siguientes puntos ( yo lo he hecho por filas, horizontalmente )
		else {
		c=(coseno*a)+(seno*b);
		d=-1*(seno*a)+(coseno*b);
		a=c;
		b=d;
	
		Vertices_tex_coords[valor_vertices].x=h/(cons-1.0);

		if ( i == 0 ) Vertices_tex_coords[valor_vertices].y=0;
		else Vertices_tex_coords[valor_vertices].y=1-(i/(cons2-1.0));

		Vertices3f[valor_vertices].x=c;
		Vertices3f[valor_vertices].y=e;
		Vertices3f[valor_vertices].z=d;
		valor_vertices++; 
		}
					
	}
}


		calcular_triangulos();
}


//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void draw_practica_4_::calcular_triangulos(){		   

	
	for (unsigned i=0;i<M-1;i++){   
		for (unsigned h=0; h<N; h++){	
	
//b, a, c  -----------------------
					
//b					
		Triangulos3f[valor_triangulos]=Vertices3f[(h+i*N)];
		valor_triangulos++;
	
//a último punto
		if( h == N-1 ){					
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)-N];
		valor_triangulos++;}

//a
		else{
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)];
		valor_triangulos++;}				

//c					
		Triangulos3f[valor_triangulos]=Vertices3f[h+(i+1)*N];
		valor_triangulos++;

//c, a, d  -----------------------

//c					
		Triangulos3f[valor_triangulos]=Vertices3f[h+(i+1)*N];
		valor_triangulos++;

//a último punto
		if( h == N-1 ){
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)-N];
		valor_triangulos++;}

//a					
		else{
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)];
		valor_triangulos++;}

//d último punto
		if( h == N-1 ){					
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+(i+1)*N)-N];
		valor_triangulos++;}
					
//d	
		else{				
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+(i+1)*N)];
		valor_triangulos++;}			
				
			} 
		}

		obtener_normales_triangulos();
	}

//-------------------------------------------------------------------------------------------------------
void draw_practica_4_::obtener_normales_triangulos(){


		float x1=0, y1=0, z1=0, x2=0, y2=0, z2=0, x3=0, y3=0, z3=0;
 
		for (unsigned valor=0; valor<valor_triangulos/3; valor++){


// BA (X) AC 

//BA = A - B
//AC = C - A

//Distinguir entre los dos triangulos de cada cuadrado
			if( valor%2==0 ){
							
//BA = A - B
		x1= Triangulos3f[valor*3+1].x - Triangulos3f[valor*3].x;
		y1= Triangulos3f[valor*3+1].y - Triangulos3f[valor*3].y;
		z1= Triangulos3f[valor*3+1].z - Triangulos3f[valor*3].z;

//AC = C - A
		x2= Triangulos3f[valor*3+2].x - Triangulos3f[valor*3+1].x;
		y2= Triangulos3f[valor*3+2].y - Triangulos3f[valor*3+1].y;
		z2= Triangulos3f[valor*3+2].z - Triangulos3f[valor*3+1].z;
		
		x3 = y1*z2-z1*y2;
		y3 = x1*z2-z1*x2;
		z3 = x1*y2-y1*x2;

//Normalizar vector

// X
		if (x3>0){
		  x3=1;}
		else if (x3<0){
		  x3=-1;}
		else x3=0;
// Y
		if (y3>0){
		  y3=-1;}
		else if (y3<0){
		  y3=1;}
		else y3=0;
// Z
		if (z3>0){
		  z3=1;}
		else if (z3<0){
		  z3=-1;}
		else z3=0;

//Meter en vector de normales de caras
		Normal_triangulos[valor].x=x3;
		Normal_triangulos[valor].y=y3;
		Normal_triangulos[valor].z=z3;	
}
		
		else {
//CA (X) AD

//CA= A - C
		x1= Triangulos3f[valor*3+1].x - Triangulos3f[valor*3].x;
		y1= Triangulos3f[valor*3+1].y - Triangulos3f[valor*3].y;
		z1= Triangulos3f[valor*3+1].z - Triangulos3f[valor*3].z;

//AD= D - A
		x2= Triangulos3f[valor*3+2].x - Triangulos3f[valor*3+1].x;
		y2= Triangulos3f[valor*3+2].y - Triangulos3f[valor*3+1].y;
		z2= Triangulos3f[valor*3+2].z - Triangulos3f[valor*3+1].z;
		
		x3 = y1*z2-z1*y2;
		y3 = x1*z2-z1*x2;
		z3 = x1*y2-y1*x2;
		
//Normalizar vector

// X
		if (x3>0){
		  x3=1;}
		else if (x3<0){
		  x3=-1;}
		else x3=0;
// Y
		if (y3>0){
		  y3=-1;}
		else if (y3<0){
		  y3=1;}
		else y3=0;
// Z
		if (z3>0){
		  z3=1;}
		else if (z3<0){
		  z3=-1;}
		else z3=0;

//Meter en vector normales de caras
		Normal_triangulos[valor].x=x3;
		Normal_triangulos[valor].y=y3;
		Normal_triangulos[valor].z=z3;		
				
					}
				}

	obtener_normales_vertices();
			}
		

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void draw_practica_4_::obtener_normales_vertices(){

// Inicializamos a 0
  	for( unsigned i=0; i< valor_vertices; i++){
		Normal_vertices[i].x=0;
		Normal_vertices[i].y=0;
		Normal_vertices[i].z=0;
		}  

// Variables de control
	unsigned int h=1;

// Metemos las normales
	for (unsigned j=0; j<valor_triangulos/3; j++){
	

// Hacemos dos casos, para los dos triangulos de los cuadrados
		if( j%2==0 ){
		
		if ( h%N == 0 && h != 0){

// b a c, último caso cada fila
		Normal_vertices[h-1] += Normal_triangulos[j];
		Normal_vertices[h-N] += Normal_triangulos[j];
		Normal_vertices[h+N-1] += Normal_triangulos[j];	
		}	

		else {
// b a c
		Normal_vertices[h-1] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+N-1] += Normal_triangulos[j]; 
		}	
	
	}		
		else {
	
		if ( h%N == 0 && h != 0 ){

// c a d, último caso cada fila
		Normal_vertices[h+N-1] += Normal_triangulos[j];
		Normal_vertices[h-N] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];	
		h++; 
	}
		
		else {
// c a d
		Normal_vertices[h+N-1] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+N] += Normal_triangulos[j];	
		h++;
		}
	
	
	}

}

// Normalizar vector normal vertices
		for( unsigned i=0; i< valor_vertices; i++){

//eje X		
		if(Normal_vertices[i].x>0){
			Normal_vertices[i].x=1;
		}
		if(Normal_vertices[i].x<0){
			Normal_vertices[i].x=-1;
		}
//eje Y		
		
		if(Normal_vertices[i].y>0){
			Normal_vertices[i].y=1;
		}
		if (i == valor_vertices-1){
			Normal_vertices[i].y=1;
		}
		else if(Normal_vertices[i].y<0){
			Normal_vertices[i].y=-1;
		}
//eje Z
		
		if(Normal_vertices[i].z>0){
			Normal_vertices[i].z=1;
		}
		if(Normal_vertices[i].z<0){
			Normal_vertices[i].z=-1;
		}
		
	     }  
       }
		
		

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

//*************************************************************************
// Dibuja puntos
//*************************************************************************

void draw_practica_4_::draw_puntos()
{
	
	material(false);
	Luz(false);
	
	glBegin(GL_POINTS);
	  		  for (unsigned i=0;i<Vertices3f.size();i++){
	    		    glVertex3fv((GLfloat *) &Vertices3f[i]);
					
		}
	   	 glEnd();

 }


//*************************************************************************
// Dibuja alambre
//*************************************************************************

void draw_practica_4_::draw_alambre()
{   
	material(false);
	Luz(false);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLES);
  		  for (unsigned i=0;i<Triangulos3f.size();i+=3){
					   		    		
				glVertex3fv((GLfloat *) &Triangulos3f[i]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+1]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
			
   		 glEnd();
}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------


//*************************************************************************
// Dibuja solido
//*************************************************************************

void draw_practica_4_::draw_solido()
{
	material(false);
	Luz(false);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);

  		  for (unsigned i=0;i<Triangulos3f.size();i+=3){	   		    
				glVertex3fv((GLfloat *) &Triangulos3f[i]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+1]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
			
   		 glEnd();

}

//*************************************************************************
// Dibuja ajedrez
//*************************************************************************

void draw_practica_4_::draw_ajedrez()
{
	

	material(false);
	Luz(false);
	  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);
  		  for (unsigned i=0;i<Triangulos3f.size();i+=3){
			if( i%2==0 )	glColor3f(0,1,0);
			else glColor3f(0,2,1); 	   		    		
				glVertex3fv((GLfloat *) &Triangulos3f[i]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+1]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
		
   		 glEnd();
	
}
//**********************************************************************


void draw_practica_4_::draw_solido_suave_( int es_automatico_)
{

if (es_automatico_== 0) cocacola();

if (es_automatico_== 1) metalico();

	unsigned int i;
   	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for(i=0; i<valor_triangulos-3; i++){
		glBegin(GL_TRIANGLES);
		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._0].x,Vertices_tex_coords[Triangulos3f[i]._0].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._0]);
		glVertex3fv((GLfloat *) &Triangulos3f[i]);

		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._1].x,Vertices_tex_coords[Triangulos3f[i]._1].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._1]);
		glVertex3fv((GLfloat *) &Triangulos3f[i+1]);

		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._2].x,Vertices_tex_coords[Triangulos3f[i]._2].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._2]);
		glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		glEnd(); 
	}  
glPopMatrix();
}


void draw_practica_4_::draw_solido_plano_( int es_automatico_)
{

if (es_automatico_== 0) cocacola();

if (es_automatico_== 1) metalico();
		 
   	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBegin(GL_TRIANGLES);

  		  for (unsigned i=0;i<valor_triangulos-3;i+=3){	 

glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._0].x,Vertices_tex_coords[Triangulos3f[i]._0].y);
glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._0]);  		    
glVertex3fv((GLfloat *) &Triangulos3f[i]);

glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._1].x,Vertices_tex_coords[Triangulos3f[i]._1].y);
glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._1]);
glVertex3fv((GLfloat *) &Triangulos3f[i+1]);

glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._2].x,Vertices_tex_coords[Triangulos3f[i]._2].y);
glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._2]);
glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
			
   		 glEnd();
}

void draw_practica_4_::fuentes_luz(float alfa_, float beta_){

float alfa, beta;
	
	GLfloat lightColor0[] = {0.4f, 0.4f, 0.4f, 1.0f};

	GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f};  
	GLfloat lightColor3[] = {0.0f, 0.0f, 0.0f, 1.0f}; 
	GLfloat lightPos0[] = { 0.0f, 0.0f, 1.0f}; 
	GLfloat spotDirection[] = {-1.0f, -1.0f, 0.f};
   
glPushMatrix() ;

glLightModelf( GL_LIGHT_MODEL_AMBIENT, 1 ) ;

glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);

glPopMatrix() ;

glPushMatrix() ;    

alfa= 1/2 + alfa_/2*3.14;
beta= 1/2 + beta_/3.14;

glRotatef( alfa*2, 0.0, 1.0, 0.0 ) ;
glRotatef( beta*2, 1.0, 0.0, 0.0 ) ;
 
glLightfv( GL_LIGHT1, GL_DIFFUSE, lightColor1 ); 
glLightfv( GL_LIGHT1, GL_AMBIENT, lightColor3 );
glLightfv( GL_LIGHT1, GL_POSITION, lightPos0);
glLightfv( GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection );

glPopMatrix() ;

}
//**********************************************************************

void draw_practica_4_::metalico(){

glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable(GL_NORMALIZE);
glDisable(GL_TEXTURE_2D);
glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, false);

GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat specular[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat shininess = 100;

glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );

}

void draw_practica_4_::cocacola(){

glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable (GL_TEXTURE_2D);
glEnable( GL_TEXTURE_GEN_S ); 
glEnable( GL_TEXTURE_GEN_T );

static bool creada = false;
 if ( !creada ){

crear_textura_lata();
creada=true;	
glDisable(GL_TEXTURE_2D);
}
glBindTexture(GL_TEXTURE_2D,idTex);

glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;

glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_DECAL);

	
}     
   		    
void draw_practica_4_::crear_textura_lata(){


glGenTextures( 1, &idTex);
glBindTexture (GL_TEXTURE_2D, idTex);

jpg::Imagen * pimg = NULL ;
pimg = new jpg::Imagen("text-lata-1.jpg");
tamx = pimg->tamX(); 
tamy = pimg->tamY(); 
texels = pimg->leerPixels();

gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tamx, tamy, GL_RGB, GL_UNSIGNED_BYTE, texels);

delete pimg;
}

void draw_practica_4_::Luz(bool encendedor){

if (encendedor) glEnable(GL_LIGHTING);
else glDisable(GL_LIGHTING);

}

void draw_practica_4_::material(bool encendedor){

if (encendedor) glEnable( GL_TEXTURE_2D);
else glDisable( GL_TEXTURE_2D);

}


void draw_practica_4_2_::obtener_valores(vector<float> Vertices_){

		Vertices=Vertices_;
		
// Iniciamos los valores	
		valor_triangulos=0;
		valor_vertices=0; 
		N=360/angulo;
		M=(Vertices.size()/3); 
		tamanio=(M*N);

// Asignamos tamaño a los vectores 		
		Normal_vertices.resize(tamanio+2);
		Normal_triangulos.resize((tamanio*8)+(6*N));
		Vertices3f.resize(tamanio+2);
		Triangulos3f.resize((tamanio*8)+(6*N));		
		Vertices_tex_coords.resize(tamanio) ;

		obtener_vertices();
}
		

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void draw_practica_4_2_::obtener_vertices(){

// Conseguimos el vector de puntos, vertices3f
				
	float Pi = 3.141, cons=N, coseno=cos(angulo/180*Pi),seno=sin(angulo/180*Pi), a, b, c, d, e, j=0;

	  for (unsigned i=0;i<M;i++){   
			
		for (unsigned h=0; h<N; h++){
			
		if( h == 0 ){
// Primer punto			
	//Vertices_tex_coords[Faces_vertices[i]._0].x,Vertices_tex_coords[Faces_vertices[i]._0].y
		Vertices_tex_coords[valor_vertices].x=0;
		Vertices_tex_coords[valor_vertices].y=0;
		
		a=Vertices3f[valor_vertices].x=Vertices[j];
		e=Vertices3f[valor_vertices].y=Vertices[j+1];
		b=Vertices3f[valor_vertices].z=Vertices[j+2];
		valor_vertices++;

		j=j+3;	
	}

// Generamos los siguientes puntos ( yo lo he hecho por filas, horizontalmente )
		else {
		c=(coseno*a)+(seno*b);
		d=-1*(seno*a)+(coseno*b);
		a=c;
		b=d;
	
		Vertices_tex_coords[valor_vertices].x=h/(cons-1.0);
		Vertices_tex_coords[valor_vertices].y=0;

		Vertices3f[valor_vertices].x=c;
		Vertices3f[valor_vertices].y=e;
		Vertices3f[valor_vertices].z=d;
		valor_vertices++; 
		}
					
	}
}

//Metemos los dos puntos de los extremos alfinal del vector Vertices3f, polo sur y luego polo norte 

//Polo sur
		Vertices3f[valor_vertices].x=0.0;
		Vertices3f[valor_vertices].y=-1.4;
		Vertices3f[valor_vertices].z=0.0;
		valor_vertices++;

//Polo norte				
		Vertices3f[valor_vertices].x=0.0;
		Vertices3f[valor_vertices].y=1.4;
		Vertices3f[valor_vertices].z=0.0;
		valor_vertices++;

			obtener_triangulos();
}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void draw_practica_4_2_::obtener_triangulos(){		   

		
	for (unsigned i=0;i<M-1;i++){   
		for (unsigned h=0; h<N; h++){	
	
//b, a, c  -----------------------
					
//b					
		Triangulos3f[valor_triangulos]=Vertices3f[(h+i*N)];
		valor_triangulos++;
	
//a último punto
		if( h == N-1 ){					
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)-N];
		valor_triangulos++;}

//a
		else{
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)];
		valor_triangulos++;}				

//c					
		Triangulos3f[valor_triangulos]=Vertices3f[h+(i+1)*N];
		valor_triangulos++;

//c, a, d  -----------------------

//c					
		Triangulos3f[valor_triangulos]=Vertices3f[h+(i+1)*N];
		valor_triangulos++;

//a último punto
		if( h == N-1 ){
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)-N];
		valor_triangulos++;}

//a					
		else{
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+i*N)];
		valor_triangulos++;}

//d último punto
		if( h == N-1 ){					
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+(i+1)*N)-N];
		valor_triangulos++;}
					
//d	
		else{				
		Triangulos3f[valor_triangulos]=Vertices3f[((h+1)+(i+1)*N)];
		valor_triangulos++;}			
				
			} 
		}
	
			obtener_tapaderas();

}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------			
void draw_practica_4_2_::obtener_tapaderas(){


		valor_total_triangulos= valor_triangulos;

//Meter tapadera polo sur:
		for (unsigned i =0 ; i <N  ; i++ ){

									
		Triangulos3f[valor_total_triangulos].x=0.0;
		Triangulos3f[valor_total_triangulos].y=-1.4;
		Triangulos3f[valor_total_triangulos].z=0.0;
		valor_total_triangulos++;
					
		Triangulos3f[valor_total_triangulos]=Vertices3f[i];
		valor_total_triangulos++;

// Para el último punto hay un caso especial						
		if (i == N-1) Triangulos3f[valor_total_triangulos]=Vertices3f[i+1-N];				
					
		else Triangulos3f[valor_total_triangulos]=Vertices3f[i+1];

		valor_total_triangulos++; 
	}

//Meter tapadera polo norte:

		for (unsigned i =0 ; i <N  ; i++ ){

									
		Triangulos3f[valor_total_triangulos].x=0.0;
		Triangulos3f[valor_total_triangulos].y=1.4;
		Triangulos3f[valor_total_triangulos].z=0.0;
		valor_total_triangulos++;
					
		Triangulos3f[valor_total_triangulos]=Vertices3f[i+((M-1)*N)];
		valor_total_triangulos++;
						
// Para el último punto hay un caso especial
		if (i == N-1) Triangulos3f[valor_total_triangulos]=Vertices3f[(i+1+((M-1)*N))-N];			
					
		else Triangulos3f[valor_total_triangulos]=Vertices3f[i+1+((M-1)*N)];

		valor_total_triangulos++; 
	}
			obtener_normales_triangulos();	  				
}


//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void draw_practica_4_2_::obtener_normales_triangulos(){


		float x1, y1, z1, x2, y2, z2, x3, y3, z3;
 
		for (unsigned valor=0; valor<valor_total_triangulos/3; valor++){

// Normales de los caras de los trianguos, sin las tapaderas		
		if (valor<valor_triangulos/3){

// BA (X) AC 

//BA = A - B
//AC = C - A

//Distinguir entre los dos triangulos de cada cuadrado
			if( valor%2==0 ){
							
//BA = A - B
		x1= Triangulos3f[valor*3+1].x - Triangulos3f[valor*3].x;
		y1= Triangulos3f[valor*3+1].y - Triangulos3f[valor*3].y;
		z1= Triangulos3f[valor*3+1].z - Triangulos3f[valor*3].z;

//AC = C - A
		x2= Triangulos3f[valor*3+2].x - Triangulos3f[valor*3+1].x;
		y2= Triangulos3f[valor*3+2].y - Triangulos3f[valor*3+1].y;
		z2= Triangulos3f[valor*3+2].z - Triangulos3f[valor*3+1].z;
		
		x3 = y1*z2-z1*y2;
		y3 = x1*z2-z1*x2;
		z3 = x1*y2-y1*x2;

//Normalizar vector

// X
		if (x3>0){
		  x3=1;}
		else if (x3<0){
		  x3=-1;}
		else x3=0;
// Y
		if (y3>0){
		  y3=-1;}
		else if (y3<0){
		  y3=1;}
		else y3=0;
// Z
		if (z3>0){
		  z3=1;}
		else if (z3<0){
		  z3=-1;}
		else z3=0;

//Meter en vector de normales de caras
		Normal_triangulos[valor].x=x3;
		Normal_triangulos[valor].y=y3;
		Normal_triangulos[valor].z=z3;	
}
		
		else {
//CA (X) AD

//CA= A - C
		x1= Triangulos3f[valor*3+1].x - Triangulos3f[valor*3].x;
		y1= Triangulos3f[valor*3+1].y - Triangulos3f[valor*3].y;
		z1= Triangulos3f[valor*3+1].z - Triangulos3f[valor*3].z;

//AD= D - A
		x2= Triangulos3f[valor*3+2].x - Triangulos3f[valor*3+1].x;
		y2= Triangulos3f[valor*3+2].y - Triangulos3f[valor*3+1].y;
		z2= Triangulos3f[valor*3+2].z - Triangulos3f[valor*3+1].z;
		
		x3 = y1*z2-z1*y2;
		y3 = x1*z2-z1*x2;
		z3 = x1*y2-y1*x2;
		
//Normalizar vector

// X
		if (x3>0){
		  x3=1;}
		else if (x3<0){
		  x3=-1;}
		else x3=0;
// Y
		if (y3>0){
		  y3=-1;}
		else if (y3<0){
		  y3=1;}
		else y3=0;
// Z
		if (z3>0){
		  z3=1;}
		else if (z3<0){
		  z3=-1;}
		else z3=0;

//Meter en vector normales de caras
		Normal_triangulos[valor].x=x3;
		Normal_triangulos[valor].y=y3;
		Normal_triangulos[valor].z=z3;		
		}
}

// Normales de las tapaderas
			else {
// Xo es un vertice del triangulo, X1 el vertice siguiente y Z es el vertice radio. 

//XoX1 = X1 - Xo
		x1= Triangulos3f[valor*3+2].x - Triangulos3f[valor*3+1].x;
		y1= Triangulos3f[valor*3+2].y - Triangulos3f[valor*3+1].y;
		z1= Triangulos3f[valor*3+2].z - Triangulos3f[valor*3+1].z;

//X1Z = Z - X1
		x2= Triangulos3f[valor*3].x - Triangulos3f[valor*3+2].x;
		y2= Triangulos3f[valor*3].y - Triangulos3f[valor*3+2].y;
		z2= Triangulos3f[valor*3].z - Triangulos3f[valor*3+2].z;
		
		x3 = y1*z2-z1*y2;
		y3 = x1*z2-z1*x2;
		z3 = x1*y2-y1*x2;

//Normalizar vector

// X
		if (x3>0){
		  x3=1;}
		else if (x3<0){
		  x3=-1;}
		else x3=0;
// Y
		if (valor > (valor_triangulos/3)+(((valor_total_triangulos/3)-(valor_triangulos/3)+1)/2)-1){
		  y3=1;}
		else if (y3!=0){
		  y3=-1;}
		else y3=0;
// Z
		if (z3>0){
		  z3=7;}
		else if (z3<0){
		  z3=-1;}
		else z3=0;	

//Meter en vector normales de caras
		Normal_triangulos[valor].x=x3;
		Normal_triangulos[valor].y=y3;
		Normal_triangulos[valor].z=z3; 

	
			}
		}
			obtener_normales_vertices();
	}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void draw_practica_4_2_::obtener_normales_vertices(){

// Inicializamos a 0
  	for( unsigned i=0; i< valor_vertices; i++){
		Normal_vertices[i].x=0;
		Normal_vertices[i].y=0;
		Normal_vertices[i].z=0;
		}  

// Variables de control
	unsigned int h=1;

// Metemos las normales
	for (unsigned j=0; j<valor_total_triangulos/3; j++){


	
// Normales de los caras de los trianguos, sin las tapaderas		
		if (j<valor_triangulos/3){	

// Hacemos dos casos, para los dos triangulos de los cuadrados
		if( j%2==0 ){
		
		if ( h%N == 0 && h != 0){

// b a c, último caso cada fila
		Normal_vertices[h-1] += Normal_triangulos[j];
		Normal_vertices[h-N] += Normal_triangulos[j];
		Normal_vertices[h+N-1] += Normal_triangulos[j];	
		}	

		else {
// b a c
		Normal_vertices[h-1] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+N-1] += Normal_triangulos[j]; 
		}	
	
	}		
		else {
	
		if ( h%N == 0 && h != 0 ){

// c a d, último caso cada fila
		Normal_vertices[h+N-1] += Normal_triangulos[j];
		Normal_vertices[h-N] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];	
		h++; 
	}
		
		else {
// c a d
		Normal_vertices[h+N-1] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+N] += Normal_triangulos[j];	
		h++;
		}
	
	
	}

}

// Normales de las tapaderas
		else {
// Polo sur	
			 
		if ( j*3 < (valor_triangulos+((valor_total_triangulos-valor_triangulos)/2))  ) 	{
			if ( j == valor_triangulos/3)	{		
			h = 0; 
		}
		
		
		if ( (valor_triangulos/3)+N-1 != j ){

		Normal_vertices[valor_vertices-2] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+1] += Normal_triangulos[j];	
		h++; 
		} 
		
		else {

		Normal_vertices[valor_vertices-2] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+1-N] += Normal_triangulos[j];	
		h++;
		}
}
//Polo norte
		else{ 
	
		if( j*3 == valor_triangulos+((valor_total_triangulos-valor_triangulos)/2 )) {

		h = N*(M-1); 		
		}
		
		if ((valor_total_triangulos/3)-1 != j ){

		Normal_vertices[valor_vertices-1] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+1] += Normal_triangulos[j];	
		h++;
		}

		else {

		Normal_vertices[valor_vertices-1] += Normal_triangulos[j];
		Normal_vertices[h] += Normal_triangulos[j];
		Normal_vertices[h+1-N] += Normal_triangulos[j];	
		h++;

		}
	}
}

// Normalizar vector normal vertices
		for( unsigned i=0; i< valor_vertices; i++){

//eje X		
		if(Normal_vertices[i].x>0){
			Normal_vertices[i].x=1;
		}
		if(Normal_vertices[i].x<0){
			Normal_vertices[i].x=-1;
		}
//eje Y		
		
		if(Normal_vertices[i].y>0){
			Normal_vertices[i].y=1;
		}
		if (i == valor_vertices-1){
			Normal_vertices[i].y=1;
		}
		else if(Normal_vertices[i].y<0){
			Normal_vertices[i].y=-1;
		}
//eje Z
		
		if(Normal_vertices[i].z>0){
			Normal_vertices[i].z=1;
		}
		if(Normal_vertices[i].z<0){
			Normal_vertices[i].z=-1;
		}
		
	     }  
       }
			opciones_display();
}		

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Opciones de Dibujado
void draw_practica_4_2_::opciones_display(){

// opción de dibujado y tamaño puntos
			
		   float color[4] = {0.0,0.0,1.0,1.0};
		    glColor4fv((GLfloat *) &color);
		    glPointSize(2);	

		   		
}

void draw_practica_4_2_::draw_puntos()
{	
//______________________________DIBUJADO:_________________________________

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//Puntos		
		  glBegin(GL_POINTS);
	  		  for (unsigned i=0;i<Vertices3f.size();i++){
	    		    glVertex3fv((GLfloat *) &Vertices3f[i]);		
		}
	   	 glEnd();
}

	
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Lineas


	
void draw_practica_4_2_::draw_alambre(){
				
		
			
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLES);
  		  for (unsigned i=0;i<valor_total_triangulos;i+=3){
					   		    		
				glVertex3fv((GLfloat *) &Triangulos3f[i]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+1]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
			
   		 glEnd();			
			
	}	
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Caras rellenas

void draw_practica_4_2_::draw_solido(){

			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);

  		  for (unsigned i=0;i<valor_total_triangulos;i+=3){	   		    
				glVertex3fv((GLfloat *) &Triangulos3f[i]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+1]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
			
   		 glEnd();
			 
		
	}
	
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

// Ajedrez

void draw_practica_4_2_::draw_ajedrez(){
		
		
			
		  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);
  		  for (unsigned i=0;i<valor_total_triangulos;i+=3){
			if( i%2==0 )	glColor3f(0,1,0);
			else glColor3f(0,2,1); 	   		    		
				glVertex3fv((GLfloat *) &Triangulos3f[i]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+1]);
				glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		}
		
   		 glEnd();
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void draw_practica_4_2_::draw_solido_suave_( int es_automatico_)
{

if (es_automatico_== 0) madera();

if (es_automatico_== 1) negro();

if (es_automatico_== 2) blanco();

	unsigned int i;
   	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for(i=0; i<valor_triangulos-3; i++){
		glBegin(GL_TRIANGLES);
		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._0].x,Vertices_tex_coords[Triangulos3f[i]._0].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._0]);
		glVertex3fv((GLfloat *) &Triangulos3f[i]);

		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._1].x,Vertices_tex_coords[Triangulos3f[i]._1].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._1]);
		glVertex3fv((GLfloat *) &Triangulos3f[i+1]);

		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._2].x,Vertices_tex_coords[Triangulos3f[i]._2].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._2]);
		glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		glEnd(); 
	}  
glPopMatrix();
}


void draw_practica_4_2_::draw_solido_plano_( int es_automatico_)
{

if (es_automatico_== 0) madera();

if (es_automatico_== 1) negro();

if (es_automatico_== 2) blanco();
		 
	unsigned int i;
   	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for(i=0; i<valor_triangulos-3; i++){
		glBegin(GL_TRIANGLES);
		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._0].x,Vertices_tex_coords[Triangulos3f[i]._0].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._0]);
		glVertex3fv((GLfloat *) &Triangulos3f[i]);

		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._1].x,Vertices_tex_coords[Triangulos3f[i]._1].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._1]);
		glVertex3fv((GLfloat *) &Triangulos3f[i+1]);

		glTexCoord2f(Vertices_tex_coords[Triangulos3f[i]._2].x,Vertices_tex_coords[Triangulos3f[i]._2].y);
		glNormal3fv((GLfloat *) &Normal_vertices[Triangulos3f[i]._2]);
		glVertex3fv((GLfloat *) &Triangulos3f[i+2]);
		glEnd(); 
	}  
}

void draw_practica_4_2_::Luz(bool encendedor){

if (encendedor) glEnable(GL_LIGHTING);
else glDisable(GL_LIGHTING);

}

void draw_practica_4_2_::material(bool encendedor){

if (encendedor) glEnable( GL_TEXTURE_2D);
else glDisable( GL_TEXTURE_2D);

}

void draw_practica_4_2_::negro(){

glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable(GL_NORMALIZE);
glDisable(GL_TEXTURE_2D);
glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);


GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat specular[] = { 2.8, 2.8, 2.8, 1.0 };
GLfloat shininess = 100;

glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );

}

void draw_practica_4_2_::blanco(){

glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable(GL_NORMALIZE);
glDisable(GL_TEXTURE_2D);

glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);


GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specular[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat shininess = 100;

glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular );
glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );

}
void draw_practica_4_2_::madera(){

glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable (GL_TEXTURE_2D);
glEnable( GL_TEXTURE_GEN_S ); 
glEnable( GL_TEXTURE_GEN_T );

static bool creada = false;
 if ( !creada ){

crear_textura_madera();
creada=true;

}

glBindTexture(GL_TEXTURE_2D,idTex2);

glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;

glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_DECAL);

}     
   		    
void draw_practica_4_2_::crear_textura_madera(){


glGenTextures( 1, &idTex2);
glBindTexture (GL_TEXTURE_2D, idTex2);

jpg::Imagen * pimg2 = NULL ;
pimg2 = new jpg::Imagen("text-madera.jpg");
tamx2 = pimg2->tamX(); 
tamy2 = pimg2->tamY(); 
texels2 = pimg2->leerPixels();

gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tamx2, tamy2, GL_RGB, GL_UNSIGNED_BYTE, texels2);

delete pimg2;
}
*/

FuenteLuz::FuenteLuz( GLenum p_ind_fuente, GLfloat p_longi_ini, GLfloat p_lati_ini, const vectorRGB & p_color )
{
   assert( glGetError() == GL_NO_ERROR );
   
   // guardar el indice opengl de la fuente, y comprobar que es 
   // alguno de GL_LIGHT0, GL_LIGHT1, etc.....
   
   ind_fuente = p_ind_fuente ;
   GLenum max_num_fuentes ;
   
   glGetIntegerv( GL_MAX_LIGHTS, (GLint *) &max_num_fuentes );
   assert( GL_LIGHT0 <= ind_fuente );
   assert( ind_fuente <= GL_LIGHT0 + max_num_fuentes );
   
   // inicializar parámetros de la fuente de luz
   longi_ini = p_longi_ini ;
   lati_ini  = p_lati_ini  ;
   longi = longi_ini ;
   lati  = lati_ini ;
   
   col_ambiente  = p_color ;
   col_difuso    = p_color ;
   col_especular = p_color ;
   
   assert( glGetError() == GL_NO_ERROR );
}

//----------------------------------------------------------------------

void FuenteLuz::activar()
{
   glEnable(ind_fuente) ;  
   GLfloat light_ambient[] = { col_ambiente.r,col_ambiente.g,col_ambiente.b, 1.0 };
   GLfloat light_diffuse[] = {  col_difuso.r,col_difuso.g,col_difuso.b, 1.0 };
   GLfloat light_specular[] = { col_especular.r,col_especular.g,col_especular.b, 1.0 };
   glLightfv (ind_fuente, GL_AMBIENT, light_ambient);
   glLightfv (ind_fuente, GL_DIFFUSE, light_diffuse);
   glLightfv (ind_fuente, GL_SPECULAR, light_specular);
   
   glMatrixMode( GL_MODELVIEW ) ;
   glLoadIdentity() ;
   glPushMatrix() ;
	glRotatef( longi, 0.0, 1.0, 0.0 ) ;
	glRotatef( lati, 1.0, 0.0, 0.0 ) ;
	 GLfloat pos[] = {0.0,0.0,1.0,0.0};
	glLightfv(ind_fuente,GL_POSITION, pos);
   glPopMatrix() ;
   glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
   glEnable(GL_RESCALE_NORMAL);
   glEnable(GL_NORMALIZE);
}

//----------------------------------------------------------------------

bool FuenteLuz::gestionarEventoTeclaEspecial( int key ) 
{
	/*
   bool actualizar = true ;
   const float incr = 3.0f ;
   
   switch( key )
   {
      case GLUT_KEY_RIGHT:
         longi = longi+incr ;
         break ;
      case GLUT_KEY_LEFT:
         longi = longi-incr ;
         break ;
      case GLUT_KEY_UP:
         lati = minim( lati+incr, 90.0) ;
         break ;
      case GLUT_KEY_DOWN:
         lati = maxim( lati-incr, -90.0 ) ;
         break ;
      case GLUT_KEY_HOME:
         lati  = lati_ini ;
         longi = longi_ini ;
         break ;
      default :
         actualizar = false ;
         cout << "tecla no usable para la fuente de luz." << endl << flush ;
   }
   
   //if ( actualizar )
   //   cout << "fuente de luz cambiada: longi == " << longi << ", lati == " << lati << endl << flush ;
   return actualizar ;
   */
}

void Objeto::compute_faces_normals()
{
   	Faces_normals.resize(Faces_vertices.size());
	
	for(int i=0;i<Faces_vertices.size();i++)
	{
		_vertex3f v0 = Vertices[Faces_vertices[i]._0];
		_vertex3f v1 = Vertices[Faces_vertices[i]._1];
		_vertex3f v2 = Vertices[Faces_vertices[i]._2];
		_vertex3f a1 = v1-v0;
		_vertex3f a2 = v2-v0;
		_vertex3f N=a1.cross_product(a2);
		N.normalize();
		Faces_normals[i]=N;
	}
}


//*************************************************************************
// Calcular normales de vértices,
//
//*************************************************************************

void Objeto::compute_vertices_normals()
{
 	Vertices_normals.resize(Vertices.size());
	for(int i=0;i<Vertices_normals.size();i++)
	{
		Vertices_normals[i]=_vertex3f(0,0,0);
	}
	for(int i=0; i<Faces_vertices.size();i++)
	{
		_vertex3f NC = Faces_normals[i];
		int j0 = Faces_vertices[i]._0;
		int j1 = Faces_vertices[i]._1;
		int j2 = Faces_vertices[i]._2;
		
		Vertices_normals[j0]+=NC;
		Vertices_normals[j1]+=NC;
		Vertices_normals[j2]+=NC;
	}

	for(int i=0;i<Vertices_normals.size();i++)
	{
		Vertices_normals[i].normalize();
	}
}

Objeto::Objeto(vector<float> Vertices1,vector<int> Faces1)  {
	material = NULL ;
	Line_color=_vertex4f(0.5,0.5,0.5,1); //Inicia colores
	Solid_color= _vertex4f(0,0,0.6,1);
	Solid_chess_color1= _vertex4f(0,.9,.0,1);
	Solid_chess_color2= _vertex4f(.9,0,.4,1);

}

int Objeto::create(vector<_vertex3f> Vertices1,vector<_vertex3i> Faces1) {
	_vertex3f v;
	_vertex3i f;

	Vertices.resize(Vertices1.size());
	Faces_vertices.resize(Faces1.size());

	for(int i=0;i<Vertices.size();i+=1)
	{
		cout << "i: " << i << endl;
		Vertices[i] = Vertices1[i];
	}

	for(int i=0;i<Faces1.size();i+=3)
	{
		Faces_vertices[i] = Faces1[i];
	}
	
	compute_faces_normals();
	compute_vertices_normals();

  	Vertices_tex_coords.resize(Vertices.size());
   	for(int i = 0; i < Vertices.size(); i++){ Vertices_tex_coords[i] = _vertex2f(0.0,0.0); }
	
	cout << "Salgo del create"<<endl;

}


/*int Objeto::create()
{
	
/*
	cout << "Entramos en create" << endl;



}
*/

void Objeto::draw_solid_material_gouroud(/*vector<_vertex3f> & Vertices_normals, vector<_vertex3i> & Faces_vertices,  vector<_vertex3f> & Vertices*/)
{
   glShadeModel(GL_SMOOTH);
   //material->activar();
   for(int i=0;i<Faces_vertices.size();i++)
	{
		_vertex3f v1 = Vertices[Faces_vertices[i]._0];
		_vertex3f v2 = Vertices[Faces_vertices[i]._1];
		_vertex3f v3 = Vertices[Faces_vertices[i]._2];
		_vertex3f f1 = Vertices_normals[Faces_vertices[i]._0];
		_vertex3f f2 = Vertices_normals[Faces_vertices[i]._1];
		_vertex3f f3 = Vertices_normals[Faces_vertices[i]._2];
		glBegin( GL_TRIANGLES );
			glNormal3f(f1.x,f1.y,f1.z); glTexCoord2f(Vertices_tex_coords[Faces_vertices[i]._0].s,Vertices_tex_coords[Faces_vertices[i]._0].t ); glVertex3f(v1.x,v1.y,v1.z);
			glNormal3f(f2.x,f2.y,f2.z); glTexCoord2f(Vertices_tex_coords[Faces_vertices[i]._1].s,Vertices_tex_coords[Faces_vertices[i]._1].t );glVertex3f(v2.x,v2.y,v2.z);
			glNormal3f(f3.x,f3.y,f3.z); glTexCoord2f(Vertices_tex_coords[Faces_vertices[i]._2].s,Vertices_tex_coords[Faces_vertices[i]._2].t );glVertex3f(v3.x,v3.y,v3.z);
		glEnd();
	}
}

void Objeto::draw_solid_material_flat()
{
   glShadeModel(GL_FLAT);
   //material->activar();
   for(int i=0;i<Faces_vertices.size();i++)
	{
		_vertex3f v1 = Vertices[Faces_vertices[i]._0];
		_vertex3f v2 = Vertices[Faces_vertices[i]._1];
		_vertex3f v3 = Vertices[Faces_vertices[i]._2];
		_vertex3f f1 = Faces_normals[i];
		glBegin( GL_TRIANGLES );
			glNormal3f(f1.x,f1.y,f1.z); glTexCoord2f(Vertices_tex_coords[Faces_vertices[i]._0].s,Vertices_tex_coords[Faces_vertices[i]._0].t );glVertex3f(v1.x,v1.y,v1.z);
			glTexCoord2f(Vertices_tex_coords[Faces_vertices[i]._1].s,Vertices_tex_coords[Faces_vertices[i]._2].t );glVertex3f(v2.x,v2.y,v2.z);
			glTexCoord2f(Vertices_tex_coords[Faces_vertices[i]._2].s,Vertices_tex_coords[Faces_vertices[i]._2].t );glVertex3f(v3.x,v3.y,v3.z);
		glEnd();
	}
}
