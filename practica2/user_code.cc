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


void generateRotatePoints(vector<_vertex3f> &vertices, vector<_vertex3f> &caras, int n)  {
	double ang;

	int num_elem_orig = vertices.size();
	vertices.resize(num_elem_orig*n);
	cout << "Tamaño original: " << num_elem_orig << endl;
	cout << "Nuevo Tamaño: "<< vertices.size() << endl;

	for (int i = 1; i <= n; ++i) {
		ang = i*((2*PI)/n);
		for(int j = 0; j < num_elem_orig; ++j)  {
			vertices[i*num_elem_orig+j].x = vertices[j].x * cos(ang) + vertices[j].z*sin(ang);
			vertices[i*num_elem_orig+j].y = vertices[j].y;
			vertices[i*num_elem_orig+j].z = -vertices[j].x * sin(ang) + vertices[j].z*cos(ang);
		}	
	}

	// Obtener las caras
	int modulo = (vertices.size()-contador_tapas);
	int cuerpo = (vertices .size()-contador_tapas)/n;
	int faces = 0;

	caras.clear();

	for(int i = 0; i < cuerpo-1;++i)  {
		for(int c1 = 0, c2 = 0; c1<(n*2);c1+=2,c2++) {
			faces = faces+2;
			caras.resize(faces);

			// cara par
			caras[i*(n*2)+c1]._0 = (i+cuerpo*c2)%modulo;
            caras[i*(n*2)+c1]._1 = ((i+cuerpo*c2)+cuerpo)%modulo;
            caras[i*(n*2)+c1]._2 = ((i+cuerpo*c2)+1)%modulo;

			// cara impar
            caras[(i*(n*2)+c1)+1]._0 = ((i+cuerpo*c2)+cuerpo)%modulo;
            caras[(i*(n*2)+c1)+1]._1 = (((i+cuerpo*c2)+cuerpo)+1)%modulo;
            caras[(i*(n*2)+c1)+1]._2 = ((i+cuerpo*c2)+1)%modulo;
		}
	}

	if (tapas == 2) {
		caras.resize(caras.size()+2*n);
		for(int i = 0; i<n; ++i) {
			caras[caras.size()-n+i]._0 = (i*cuerpo)%modulo;
			caras[caras.size()-n+i]._1 = (i*cuerpo+2)%modulo;
			caras[caras.size()-n+i]._2 = puntos.size()-1;

			caras[caras.size()-(2*n+i)]._0 = (i*cuerpol+1)%modulo;
			caras[caras.size()-(2*n)+i]._1 =  (i*cuerpo+3)%modulo;
            caras[caras.size()-(2*n)+i]._2 = puntos.size()-2;
		}
	}

/* CODIDO AUXILIAR TONI
int modulo=(Perfil_Puntos.size()-contador_tapas);
    //cout << "MODULOOOO" << modulo<<  endl;
    int cuerpo_central=(Perfil_Puntos.size()-contador_tapas)/n;    
    Perfil_Caras.clear();
    int faces=0;
    for(int i=0;i<cuerpo_central-1;i++){ // me recorre los dos vertices que definen el cuerpo central del prisma
        for(int c1=0,c2=0; c1<(n*2); c1+=2,c2++){ // -2 pra que quede hueco
            faces=faces+2;            
            Perfil_Caras.resize(faces);            
            // cara par
            Perfil_Caras[i*(n*2)+c1]._0 = (i+cuerpo_central*c2)%modulo; // 0 // 2 // 4 // 0 // 2 // 4
            Perfil_Caras[i*(n*2)+c1]._1 = ((i+cuerpo_central*c2)+cuerpo_central)%modulo; // 2 // 4 // 0
            Perfil_Caras[i*(n*2)+c1]._2 = ((i+cuerpo_central*c2)+1)%modulo;// 1 // 3 // 5 // 1 // 3 // 5
            //cout << Perfil_Caras[i*(n*2)+c1]._0 << "caras" <<endl;
            // cara impar
            Perfil_Caras[(i*(n*2)+c1)+1]._0 = ((i+cuerpo_central*c2)+cuerpo_central)%modulo;
            Perfil_Caras[(i*(n*2)+c1)+1]._1 = (((i+cuerpo_central*c2)+cuerpo_central)+1)%modulo;
            Perfil_Caras[(i*(n*2)+c1)+1]._2 = ((i+cuerpo_central*c2)+1)%modulo;



        }
    }
    cout << "Caras sin tapas despues" << Perfil_Caras.size()<<endl;


    if(contador_tapas==2){
            
        Perfil_Caras.resize(Perfil_Caras.size()+2*n);
        for(int i=0;i<n;i++){
            Perfil_Caras[Perfil_Caras.size()-n+i]._0 = (i*cuerpo_central)%modulo; // 0 // 2 // 4 //
            Perfil_Caras[Perfil_Caras.size()-n+i]._1 =  (i*cuerpo_central+2)%modulo; // 2 // 4 //0
            Perfil_Caras[Perfil_Caras.size()-n+i]._2 = Perfil_Puntos.size()-1;// 7 // 7 // 7 // 7
        
            Perfil_Caras[Perfil_Caras.size()-(2*n)+i]._0 = (i*cuerpo_central+1)%modulo; // 0 // 2 // 4 //
            Perfil_Caras[Perfil_Caras.size()-(2*n)+i]._1 =  (i*cuerpo_central+3)%modulo; // 2 // 4 //0
            Perfil_Caras[Perfil_Caras.size()-(2*n)+i]._2 = Perfil_Puntos.size()-2;// 8 // 8 // 8 //  

*/

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