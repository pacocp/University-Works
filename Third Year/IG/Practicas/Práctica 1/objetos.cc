//**************************************************************************
// Práctica 1
//
// Francisco Carrillo Pérez ;Informática Gráfica; Grupo:B1
//
// GPL
// All wrongs Reserved
// https://github.com/pacocp
//**************************************************************************
#include <vector>
#include <GL/gl.h>
#include "objetos.h"
#include "vertex.h"
#include <stdlib.h>

using namespace std;


//*********************************************************
// CONSTRUCTORES
//**********************************************************
_puntos3D::_puntos3D()
{

}
_triangulos3D::_triangulos3D()
{

}

_cubo::_cubo(float tam)
{
  _vertex3f v1c = _vertex3f(0,tam,0); //0
	_vertex3f v2c = _vertex3f(tam,0,0); //1
	_vertex3f v3c = _vertex3f(0,0,tam);//2
	_vertex3f v4c = _vertex3f(tam,tam,tam);//3
	_vertex3f v5 = _vertex3f(0,0,0);//4
	_vertex3f v6 = _vertex3f(tam,0,tam);//5
	_vertex3f v7 = _vertex3f(tam,tam,0);//6
	_vertex3f v8 = _vertex3f(0,tam,tam);//7
	//caras
	_vertex3i c1c = _vertex3i(4,1,6);
	_vertex3i c2c = _vertex3i(4,0,6);
	_vertex3i c3c = _vertex3i(1,5,3);
	_vertex3i c4c = _vertex3i(1,6,3);
	_vertex3i c5 = _vertex3i(5,3,7);
	_vertex3i c6 = _vertex3i(5,2,7);
	_vertex3i c7 = _vertex3i(4,2,7);
	_vertex3i c8 = _vertex3i(4,0,7);
	_vertex3i c9 = _vertex3i(0,6,3);
	_vertex3i c10 = _vertex3i(0,3,7);
	_vertex3i c11 = _vertex3i(4,1,5);
	_vertex3i c12 = _vertex3i(4,2,5);

	vertices.push_back(v1c);
	vertices.push_back(v2c);
	vertices.push_back(v3c);
	vertices.push_back(v4c);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);
	caras.push_back(c1c);
	caras.push_back(c2c);
	caras.push_back(c3c);
	caras.push_back(c4c);
	caras.push_back(c5);
	caras.push_back(c6);
	caras.push_back(c7);
	caras.push_back(c8);
	caras.push_back(c9);
	caras.push_back(c10);
	caras.push_back(c11);
	caras.push_back(c12);
}

_piramide::_piramide(float tam, float al)
{
  /*
  _vertex3f v1 = _vertex3f(0,tam,0); //0
	_vertex3f v2 = _vertex3f(tam,0,0); //1
	_vertex3f v3 = _vertex3f(0,0,tam);//2
	_vertex3f v4 = _vertex3f(tam,tam,tam);//3
	//CARAS
	_vertex3i c1 = _vertex3i(0,1,2);
	_vertex3i c2 = _vertex3i(1,2,3);
	_vertex3i c3 = _vertex3i(0,2,3);
	_vertex3i c4 = _vertex3i(0,1,3);
  */
   //****************************************************
   // EXAMEN
   //****************************************************
   _vertex3f v1 = _vertex3f(tam,tam,0);//0
   _vertex3f v3 = _vertex3f(tam,tam,tam);//1
   _vertex3f v2 = _vertex3f(0,tam,tam);//2
   _vertex3f v4 = _vertex3f(0,tam,0); //3
   _vertex3f v5p = _vertex3f(tam/2,al,tam/2); //4
   //CARAS
 	_vertex3i c1 = _vertex3i(0,1,2);
 	_vertex3i c2 = _vertex3i(2,3,4);
 	_vertex3i c3 = _vertex3i(0,1,4);
 	_vertex3i c4 = _vertex3i(0,4,3);
  _vertex3i c5p = _vertex3i(3,4,2);
  _vertex3i c6p = _vertex3i(2,4,1);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
  vertices.push_back(v5p);
	caras.push_back(c1);
	caras.push_back(c2);
	caras.push_back(c3);
	caras.push_back(c4);
  caras.push_back(c5p);
  caras.push_back(c6p);
}

//************************************************
// Implementación de la función draw puntos
//************************************************
void 	_puntos3D::draw_puntos(float r, float g, float b, int grosor)
{

    glColor3f(r,g,b); //Color de los puntos
    glPointSize(grosor); //Grosor de los puntos
    glBegin(GL_POINTS); //Queremos dibujar los puntos
      for(int i = 0; i< vertices.size(); i++) //Iteramos sobre los vértices
      {
        glVertex3f(vertices[i]._0,vertices[i]._1,vertices[i]._2);
      }
  	glEnd();
}

//************************************************
// Implementación de la función draw aristas
//************************************************
void 	_triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
    glColor3f(r,g,b); //Color de la línea
    glLineWidth(grosor); //Grosor de la línea
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //para que dibuje líneas
    glBegin(GL_TRIANGLES); //Queremos dibujar los triángulos
      for(int i = 0; i< caras.size(); i++) //Iteramos sobre los vértices
      {
        int v1 = caras[i]._0;
        int v2 = caras[i]._1;
        int v3 = caras[i]._2;
        glVertex3f(vertices[v1]._0,vertices[v1]._1,vertices[v1]._2);
        glVertex3f(vertices[v2]._0,vertices[v2]._1,vertices[v2]._2);
        glVertex3f(vertices[v3]._0,vertices[v3]._1,vertices[v3]._2);
      }
    glEnd();
}

//************************************************
// Implementación de la función draw sólido
//************************************************
void 	_triangulos3D::draw_solido(float r, float g, float b)
{
    glColor3f(r,g,b); //Color del sólido
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES); //Queremos dibujar los triángulos
      for(int i = 0; i< caras.size(); i++) //Iteramos sobre los vértices
      {
        int v1 = caras[i]._0;
        int v2 = caras[i]._1;
        int v3 = caras[i]._2;
        glVertex3f(vertices[v1]._0,vertices[v1]._1,vertices[v1]._2);
        glVertex3f(vertices[v2]._0,vertices[v2]._1,vertices[v2]._2);
        glVertex3f(vertices[v3]._0,vertices[v3]._1,vertices[v3]._2);
      }
    glEnd();
}

//************************************************
// Implementación de la función draw sólido ajedrez
//************************************************
void 	_triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES); //Queremos dibujar los triángulos
      for(int i = 0; i< caras.size(); i++) //Iteramos sobre los vértices
      {
        if(i&1)
        {
          glColor3f(r1,g1,b1); //Color del sólido 1
        }
        else{
          glColor3f(r2,g2,b2); //Color del sólido 2
        }
        int v1 = caras[i]._0;
        int v2 = caras[i]._1;
        int v3 = caras[i]._2;
        glVertex3f(vertices[v1]._0,vertices[v1]._1,vertices[v1]._2);
        glVertex3f(vertices[v2]._0,vertices[v2]._1,vertices[v2]._2);
        glVertex3f(vertices[v3]._0,vertices[v3]._1,vertices[v3]._2);
      }
    glEnd();
}
