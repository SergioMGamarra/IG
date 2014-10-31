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