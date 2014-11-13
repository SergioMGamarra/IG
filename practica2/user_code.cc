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
    for (unsigned i=0;i<3;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
        }
    glEnd();
}

void draw_alambre (vector<_vertex3f> &vertices, vector<_vertex3f> &caras) {
	glBegin(GL_LINES);
		for (int i = 0; i < caras.size(); ++i) {
			glVertex3f(vertices[caras[i]._0].x, vertices[caras[i]._0].y, vertices[caras[i]._0].z);
			glVertex3f(vertices[caras[i]._1].x, vertices[caras[i]._1].y, vertices[caras[i]._1].z);
			glVertex3f(vertices[caras[i]._2].x, vertices[caras[i]._2].y, vertices[caras[i]._2].z);
		}
	glEnd();
}

void draw_solid (vector<_vertex3f> &vertices, vector<_vertex3f> &caras)  {
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

void draw_ajedrez(vector<_vertex3f> &vertices, vector<_vertex3f> &caras) {
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


void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3f> &caras, vector<_vertex3f> &tapasV, int n)  {
	double ang;
	int tapas = 0;

	if (tapasV.size()!=0) tapas = 2;


	int num_elem_orig = vertices.size();
	vector<_vertex3f> tapa(2);

	vertices.resize(num_elem_orig*n);

	for (int i = num_elem_orig-1; i <= n-1; ++i) {
		ang = i*((2*PI)/n);
		for (int j = 0; j < num_elem_orig; ++j) {
			vertices[i*num_elem_orig+j].x = vertices[j].x * cos(ang) + vertices[j].z*sin(ang);
			vertices[i*num_elem_orig+j].y = vertices[j].y;
			vertices[i*num_elem_orig+j].z = -vertices[j].x * sin(ang) + vertices[j].z*cos(ang);

		}
	}

	vertices.resize(vertices.size()+2);
	vertices[vertices.size()-2]=tapasV[1];
	vertices[vertices.size()-1]=tapasV[0];

	// Obtenemos las caras
	int mod = (vertices.size()-tapas);
	cout << "Modulo: " << mod << endl;
	int cuerpo = vertices.size();
	caras.clear();
	int faces = 0;
	for(int i = 0; i < cuerpo/n;++i) {
		for(int c1=0, c2=0; c1<(n*2); c1+=2,c2++) {
			faces+=2;
			caras.resize(faces);
			// cara par
			caras[i*(n*2)+c1]._0 = (i+cuerpo*c2)%mod;
			caras[i*(n*2)+c1]._1 = ((i+cuerpo*c2)+cuerpo)%mod; // 2 // 4 // 0
            caras[i*(n*2)+c1]._2 = ((i+cuerpo*c2)+1)%mod;// 1 // 3 // 5 // 1 // 3 // 5
            //cout << Perfil_Caras[i*(n*2)+c1]._0 << "caras" <<endl;
            // cara impar
            caras[(i*(n*2)+c1)+1]._0 = ((i+cuerpo*c2)+cuerpo)%mod;
            caras[(i*(n*2)+c1)+1]._1 = (((i+cuerpo*c2)+cuerpo)+1)%mod;
            caras[(i*(n*2)+c1)+1]._2 = ((i+cuerpo*c2)+1)%mod;

		}
	}

	if(tapas==2){
            
        caras.resize(caras.size()+2*n);
        for(int i=0;i<n;i++){
            caras[caras.size()-n+i]._0 = (i*cuerpo)%mod; // 0 // 2 // 4 //
            caras[caras.size()-n+i]._1 =  (i*cuerpo+2)%mod; // 2 // 4 //0
            caras[caras.size()-n+i]._2 = vertices.size()-1; // 7 // 7 // 7 // 7
        
            caras[caras.size()-(2*n)+i]._0 = (i*cuerpo+1)%mod; // 0 // 2 // 4 //
            caras[caras.size()-(2*n)+i]._1 =  (i*cuerpo+3)%mod; // 2 // 4 //0
            caras[caras.size()-(2*n)+i]._2 = vertices.size()-2; // 8 // 8 // 8 //  
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
void Normales_Caras(vector<_vertex3f> &vertices, vector<_vertex3f> &caras,vector<_vertex3f> &normales_caras)  {
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


void Normales_Vertices(vector<_vertex3f> &vertices, vector<_vertex3f> &caras, vector<_vertex3f> &normales_caras, vector<_vertex3f> &normales_vertices) {
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
		Normalizar(N);
		normales_vertices [i] = N;
		contador_puntos = 0;
		N = 0;
	}
}



//************************Funcion draw ++++++++++++++++++++++++++++++

void draw (vector<_vertex3f> &vertices, vector<_vertex3f> &caras, int opc) {
	if (opc == 1)
		draw_points(vertices);
	else if (opc == 2)
		draw_alambre(vertices,caras);
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