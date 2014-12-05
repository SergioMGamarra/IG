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
	double ang = -30;
	double ang2 = -270;
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