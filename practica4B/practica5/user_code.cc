//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

/*TODAS LAS FUNCIONES DE LA PRÁCTICA 5 SE ENCUENTRAN EN PRACTICA5.CC */

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
	for(int i = 0; i < vertices.size(); ++i)
		cout << i << ": " << vertices[i].x << endl;
	float x, y, z;
	int tapas = tapasV.size();
	//a = 45 * 3.141592653589793 / 180.0;
	//b = tan(a);
	double ang = 0;
	double ang2 = 360;
	double ang1rad = ang * PI/180.0;
	double ang2rad = ang2 * PI/180.0;
	cout << ang1rad << endl;
	tapas = tapasV.size();

	int num_elem_orig = vertices.size();
	vector<_vertex3f> tapa(2);

	for (int i = 0; i < num_elem_orig; ++i){
		x = vertices[i].x;
		y = vertices[i].y;
		z = vertices[i].z;

		vertices[i].x = x * cos(ang1rad) + z*sin(ang1rad);
		vertices[i].y = y;
		vertices[i].z = -x * sin(ang1rad) + z*cos(ang1rad);
	}

	vertices.resize(num_elem_orig*n);
	
	int m = n-1;

	for (int i = num_elem_orig-1; i <= m; ++i) {
		double ang = i*((ang2rad - ang1rad)/m);
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
		for (int i = 0; i < vertices.size(); i+=3) {
			glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
		}
	glEnd();
}

void draw_alambre (vector<float> &vertices,vector<int> &faces) {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		for (int i = 0; i < faces.size(); i+=2) {
			if (vertices[faces[i]*3+1] > 0 && vertices[faces[i+1]*3+1]> 0 &&  vertices[faces[i+2]*3+1] > 0) {
				glVertex3f(vertices[faces[i]*3], vertices[faces[i]*3+1], vertices[faces[i]*3+2]);
				glVertex3f(vertices[faces[i+1]*3], vertices[faces[i+1]*3+1], vertices[faces[i+1]*3+2]);
			}
		}
	glEnd();
}

void draw_solid (vector<float> &vertices,vector<int> &faces)  {

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < faces.size(); i+=3) {	
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
	for (int i = 0; i < faces.size()-1; i+=3) {
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

//************************Normales*************************************
void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3i> &caras,vector<_vertex3f> &normales_caras)  {
	normales_caras.clear();
	normales_caras.resize(0);

	for(int i = 0; i < caras.size(); ++i)  {
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
	for (int i = 0; i < vertices.size(); ++i)  {
		for(int j = 0; j < caras.size(); ++j) {
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



/*************PRACTICA4********************/


Objeto::Objeto() {
	Solid_color= _vertex4f(0,0,0.0,0.0);
}


void Objeto::compute_faces_normals()
{
   	Faces_normals.resize(Caras.size());
	
	for(int i=0;i<Caras.size();i++)
	{
		_vertex3f v0 = Vertices[Caras[i]._0];
		_vertex3f v1 = Vertices[Caras[i]._1];
		_vertex3f v2 = Vertices[Caras[i]._2];
		_vertex3f a1 = v1-v0;
		_vertex3f a2 = v2-v0;
		_vertex3f N=a1.cross_product(a2);
		N.normalize();
		Faces_normals[i]=N;
	}
}


void Objeto::compute_vertices_normals()
{
 	Vertices_normals.resize(Vertices.size());
	for(int i=0;i<Vertices_normals.size();i++)
	{
		Vertices_normals[i]=_vertex3f(0,0,0);
	}
	for(int i=0; i<Caras.size();i++)
	{
		_vertex3f NC = Faces_normals[i];
		int j0 = Caras[i]._0;
		int j1 = Caras[i]._1;
		int j2 = Caras[i]._2;
		
		Vertices_normals[j0]+=NC;
		Vertices_normals[j1]+=NC;
		Vertices_normals[j2]+=NC;
	}

	for(int i=0;i<Vertices_normals.size();i++)
	{
		Vertices_normals[i].normalize();
	}
}


void Objeto::create(vector<_vertex3f> Vert, vector <_vertex3i> Faces) {
	num_vert_ply = Vert.size();
	generateRotatePoints(Vert, Faces, 50);

	Vertices.resize(Vert.size());
	Caras.resize(Faces.size());


	for (int i = 0; i < Vert.size(); ++i) 
		Vertices[i] = Vert[i];

	for (int i = 0; i < Caras.size(); ++i)
		Caras[i] = Faces[i];

	compute_faces_normals();
	compute_vertices_normals();


   Vertices_tex_coords.resize(Vertices.size());
   for(int i = 0; i < Vertices.size(); i++){ 
   		Vertices_tex_coords[i] = _vertex2f(0.0,0.0); 
   }

}

void Objeto::compute_text_coord()  {
	int rev = Vertices.size()/num_vert_ply;
	Vertices_tex_coords.resize(Vertices.size());
	for (int i = 0; i < rev; ++i)  {
		for (int j = 0; j < num_vert_ply; ++j)  {
			if (i =! 0) {
				if (j != 0)  {
					Vertices_tex_coords[rev*i+j].x = j/(rev-1.0);  
					Vertices_tex_coords[rev*i+j].y = 1.0 - (i/(rev-1.0));
				}else  {
					Vertices_tex_coords[rev*i+j].y = 0;
				}
			} else {
				Vertices_tex_coords[rev*i+j].x = 0;
			}
		}
	}
}


void Objeto::draw_points () {
	glPointSize(1.0f);
	glBegin(GL_POINTS);
		for (int i = 0; i < Vertices.size(); i++) {
			glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
		}
	glEnd();
}

void Objeto::draw_solid_flat() {
   glShadeModel(GL_FLAT);
   for(int i=0;i<Caras.size();i++)
	{
		_vertex3f v1 = Vertices[Caras[i]._0];
		_vertex3f v2 = Vertices[Caras[i]._1];
		_vertex3f v3 = Vertices[Caras[i]._2];
		_vertex3f f1 = Faces_normals[i];
		glBegin( GL_TRIANGLES );
			glNormal3f(f1.x,f1.y,f1.z); glTexCoord2f(Vertices_tex_coords[Caras[i]._0].s,Vertices_tex_coords[Caras[i]._0].t );glVertex3f(v1.x,v1.y,v1.z);
			glTexCoord2f(Vertices_tex_coords[Caras[i]._1].s,Vertices_tex_coords[Caras[i]._2].t );glVertex3f(v2.x,v2.y,v2.z);
			glTexCoord2f(Vertices_tex_coords[Caras[i]._2].s,Vertices_tex_coords[Caras[i]._2].t );glVertex3f(v3.x,v3.y,v3.z);
		glEnd();
	}
}

void Objeto::draw_solid_flat2() {
   glShadeModel(GL_FLAT);
   for(int i=0;i<Caras.size();i++)
	{
		_vertex3f v1 = Vertices[Caras[i]._0];
		_vertex3f v2 = Vertices[Caras[i]._1];
		_vertex3f v3 = Vertices[Caras[i]._2];
		_vertex3f f1 = Faces_normals[i];
		glEnable(GL_TEXTURE_2D);
		glBegin( GL_TRIANGLES );
			glNormal3f(f1.x,f1.y,f1.z); glTexCoord2f(Vertices_tex_coords[Caras[i]._0].s,Vertices_tex_coords[Caras[i]._0].t );glVertex3f(v1.x,v1.y,v1.z);
			glTexCoord2f(Vertices_tex_coords[Caras[i]._1].s,Vertices_tex_coords[Caras[i]._2].t );glVertex3f(v2.x,v2.y,v2.z);
			glTexCoord2f(Vertices_tex_coords[Caras[i]._2].s,Vertices_tex_coords[Caras[i]._2].t );glVertex3f(v3.x,v3.y,v3.z);
		glEnd();
		glDisable(GL_TEXTURE_2D);

	}
}

void Objeto::draw_solid_material_gouroud()
{
   glShadeModel(GL_SMOOTH);
   for(int i=0;i<Caras.size();i++)
	{
		_vertex3f v1 = Vertices[Caras[i]._0];
		_vertex3f v2 = Vertices[Caras[i]._1];
		_vertex3f v3 = Vertices[Caras[i]._2];
		_vertex3f f1 = Vertices_normals[Caras[i]._0];
		_vertex3f f2 = Vertices_normals[Caras[i]._1];
		_vertex3f f3 = Vertices_normals[Caras[i]._2];
		glBegin( GL_TRIANGLES );
			glNormal3f(f1.x,f1.y,f1.z); glTexCoord2f(Vertices_tex_coords[Caras[i]._0].s,Vertices_tex_coords[Caras[i]._0].t ); glVertex3f(v1.x,v1.y,v1.z);
			glNormal3f(f2.x,f2.y,f2.z); glTexCoord2f(Vertices_tex_coords[Caras[i]._1].s,Vertices_tex_coords[Caras[i]._1].t );glVertex3f(v2.x,v2.y,v2.z);
			glNormal3f(f3.x,f3.y,f3.z); glTexCoord2f(Vertices_tex_coords[Caras[i]._2].s,Vertices_tex_coords[Caras[i]._2].t );glVertex3f(v3.x,v3.y,v3.z);
		glEnd();
	}
}


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


Textura::Textura( const std::string & nombreArchivoJPG ) 
{
   	glGenTextures( 1, &ident_textura );
   	glBindTexture( GL_TEXTURE_2D, ident_textura);
   	jpg::Imagen * pimg = NULL;
   	pimg = new jpg::Imagen(nombreArchivoJPG);
   	tamx = pimg->tamX();
   	tamy = pimg->tamY();
   	texels = pimg->leerPixels();
   	gluBuild2DMipmaps( GL_TEXTURE_2D,GL_RGB,tamx,tamy,GL_RGB,GL_UNSIGNED_BYTE,texels);
    modo_gen_ct = mgct_desactivada;

}

//----------------------------------------------------------------------

Textura::~Textura( ) 
{
   
}

//----------------------------------------------------------------------


void Textura::activar( ) 
{
   glEnable( GL_TEXTURE_2D ) ; //Activa texturas
   glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //Activa interpolación
   glBindTexture( GL_TEXTURE_2D, ident_textura );
   if(modo_gen_ct != mgct_desactivada){
   	glEnable( GL_TEXTURE_GEN_S );
   	glEnable( GL_TEXTURE_GEN_T );
	if(modo_gen_ct == mgct_coords_objeto){
		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
		glTexGenfv( GL_S, GL_OBJECT_PLANE, coefs_s ) ;
		glTexGenfv( GL_T, GL_OBJECT_PLANE, coefs_t ) ;
	} else{
		glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR ) ;
		glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR ) ;
		glTexGenfv( GL_S, GL_EYE_PLANE, coefs_s ) ;
		glTexGenfv( GL_T, GL_EYE_PLANE, coefs_t ) ;
	}
   } else {
   	glDisable( GL_TEXTURE_GEN_S );
   	glDisable( GL_TEXTURE_GEN_T );
   }
}


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


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


//**********************************************************************

Material::Material() 
{
   iluminacion = false ;
   tex = NULL ;
   
   coloresCero() ;
}

//----------------------------------------------------------------------

Material::Material( const std::string & nombreArchivoJPG ) 
{
   iluminacion    = false ;
   tex            = new Textura( nombreArchivoJPG ) ;
   
   coloresCero();
   
   del.difusa = vectorRGB( 0.5, 0.5, 0.5 );
   tra.difusa = vectorRGB( 0.2, 0.2, 0.2 );
   
   del.especular = vectorRGB( 0.0, 0.0, 0.0 );
   tra.especular = vectorRGB( 0.2, 0.2, 0.2 );
}



//----------------------------------------------------------------------

void Material::coloresCero()
{
   const vectorRGB ceroRGB(0.0,0.0,0.0);
   
   color         = 
   
   del.emision   = 
   del.ambiente  = 
   del.difusa    = 
   del.especular = 

   tra.emision   = 
   tra.ambiente  = 
   tra.difusa    = 
   tra.especular = ceroRGB ;
   
   del.exp_brillo = 
   tra.exp_brillo = 1.0 ;
}

//----------------------------------------------------------------------

Material::~Material() 
{      
   if ( tex != NULL )
   {  
   		delete tex ;
    	tex = NULL ;
   }
}


//----------------------------------------------------------------------

void Material::activar()
{

   if(tex != NULL){
	tex->activar();
   }

   if(iluminacion){
		glEnable(GL_LIGHTING) ;
		GLfloat emision[4] = {del.emision.r,del.emision.g,del.emision.b,1.0};
	   	GLfloat ambiente[4] =  {del.ambiente.r,del.ambiente.g,del.ambiente.b,1.0};
	   	GLfloat difusa[4] =  {del.difusa.r,del.difusa.g,del.difusa.b,1.0};
	   	GLfloat especular[4] =  {del.especular.r,del.especular.g,del.especular.b,1.0};

	   	glMaterialfv( GL_FRONT, GL_EMISSION, emision ) ;
	   	glMaterialfv( GL_FRONT, GL_AMBIENT, ambiente ) ;
	   	glMaterialfv( GL_FRONT, GL_DIFFUSE, difusa ) ;
	   	glMaterialfv( GL_FRONT, GL_SPECULAR, especular ) ;
	   	glMaterialf( GL_FRONT, GL_SHININESS, del.exp_brillo ) ;

		GLfloat emisionb[4] = {tra.emision.r,tra.emision.g,tra.emision.b,1.0};
		GLfloat ambienteb[4] =  {tra.ambiente.r,tra.ambiente.g,tra.ambiente.b,1.0};
		GLfloat difusab[4] =  {tra.difusa.r,tra.difusa.g,tra.difusa.b,1.0};
		GLfloat especularb[4] =  {tra.especular.r,tra.especular.g,tra.especular.b,1.0};

		glMaterialfv( GL_BACK, GL_EMISSION, emisionb ) ;
		glMaterialfv( GL_BACK, GL_AMBIENT, ambienteb ) ;
		glMaterialfv( GL_BACK, GL_DIFFUSE, difusab ) ;
		glMaterialfv( GL_BACK, GL_SPECULAR, especularb ) ;
		glMaterialf( GL_BACK, GL_SHININESS, tra.exp_brillo ) ;
		glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR ) ;
   } else {
	glDisable(GL_LIGHTING) ;
   }
   
}

void Objeto::Madera()  {

glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable (GL_TEXTURE_2D);
glEnable( GL_TEXTURE_GEN_S ); 
glEnable( GL_TEXTURE_GEN_T );

static bool creada = false;
 if ( !creada ){
creada = true;
glGenTextures( 1, &ident_textura);
glBindTexture (GL_TEXTURE_2D, ident_textura);

jpg::Imagen * pimg = NULL ;
pimg = new jpg::Imagen("text-madera.jpg");
tamx = pimg->tamX(); 
tamy = pimg->tamY(); 
texels = pimg->leerPixels();

gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tamx, tamy, GL_RGB, GL_UNSIGNED_BYTE, texels);

delete pimg;
}
glBindTexture(GL_TEXTURE_2D,ident_textura);

glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;

glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_DECAL);

}

void Objeto::CocaCola()  {
glEnable(GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glEnable (GL_TEXTURE_2D);
glEnable( GL_TEXTURE_GEN_S ); 
glEnable( GL_TEXTURE_GEN_T );

static bool creada = false;
 if ( !creada ){
creada = true;
glGenTextures( 1, &ident_textura);
glBindTexture (GL_TEXTURE_2D, ident_textura);

jpg::Imagen * pimg = NULL ;
pimg = new jpg::Imagen("text-lata-1.jpg");
tamx = pimg->tamX(); 
tamy = pimg->tamY(); 
texels = pimg->leerPixels();

gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tamx, tamy, GL_RGB, GL_UNSIGNED_BYTE, texels);

delete pimg;
}
glBindTexture(GL_TEXTURE_2D,ident_textura);

glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;

glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_DECAL);

}
