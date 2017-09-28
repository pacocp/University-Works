//**************************************************************************
// Práctica 2
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
#include <cmath>
#include "file_ply_stl.hpp"
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

_cubo::_cubo()
{}
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

_piramide::_piramide()
{}
_piramide::_piramide(float tam, float al)
{

   //Vértices
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

objeto_PLY::objeto_PLY(char* nombre_archivo)
{
  _file_ply::read(nombre_archivo,Vertices,Caras);

  _vertex3f aux;



  _vertex3f v;
  _vertex3i c;
  for(int i = 0; i< Vertices.size(); i+=3)
  {
      v.x = Vertices[i];
      v.y = Vertices[i+1];
      v.z = Vertices[i+2];
      vertices.push_back(v);
  }

  for(int i = 0; i< Caras.size(); i+=3)
  {
      c._0 = Caras[i];
      c._1 = Caras[i+1];
      c._2 = Caras[i+2];
      caras.push_back(c);
  }

}

revolucion::revolucion()
{}
revolucion::revolucion(vector<_vertex3f> ver,int num_caras,bool tapas)
{

  caras.clear();
  _vertex3f aux,abajo,arriba;
  //double maxy=0,maxy=ver[ver.size()-1].y;
  int inicio = 0, fin = ver.size();
  float alfa = 2*3.1416/num_caras;
  float alfa_aux = 2*3.1416/num_caras;

  if(tapas)
  {
    abajo = ver[0];
    abajo.x = 0;
    arriba = ver[ver.size()-1];
    arriba.x = 0;

  }


  vertices = ver;
  for(int i = 0; i < num_caras; i++)
  {
    for(int j = 0; j < fin;j++)
    {

      aux.x =  ver[j].x * cos(alfa);
      aux.z =  ver[j].x * sin(alfa);
      aux.y  = ver[j].y;

      vertices.push_back(aux);
    }
    alfa += alfa_aux;
  }

  if(tapas)
  {
    vertices.push_back(abajo);
    vertices.push_back(arriba);
  }


  int indice=0;
  for(int i = 0; i < num_caras; i++)
  {
      for(int j=0; j< ver.size()-1;j++)
      {

         indice = i*ver.size()+j; //INDICE para las caras
         _vertex3i aux(indice,indice+ver.size(),indice+1); //Caras superiores
         _vertex3i aux2(indice+1,indice+ver.size(),indice+1+ver.size()); //Caras inferires
         caras.push_back(aux);
         caras.push_back(aux2);
      }
  }

  if(tapas)
  {
    for(int i = 0; i < num_caras; i++)
    {

           _vertex3i aux(vertices.size()-2,ver.size()*i,ver.size()*(i+1)); //Caras inferiores tapa
           caras.push_back(aux);


    }
    for(int i = 0; i < num_caras; i++)
    {


           _vertex3i aux2(vertices.size()-1,ver.size()*i + ver.size()-1,(ver.size()*(i+1))+ ver.size()-1); //Caras superiores tapa
           caras.push_back(aux2);

    }
  }





}

/*Función que dibuja un círculo*/
void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
	int i;
	if (modo==GL_LINE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (modo==GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glBegin( GL_POLYGON );
	for (i=0;i<n;i++)
	glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
	glEnd();
}

grua::grua()
{
  //**********************************************************************************
  // CREACIÓN DE LOS OBJETOS
  //**********************************************************************************
  //VAMOS A CREAR LA BASE
  vector<_vertex3f> vertices_base,vertices_palo,vertices_cilindro_cabina, vertices_cable;
  _vertex3f v1;
  v1.x = 4;
  v1.y = 2;
  v1.z=0;
  vertices_base.push_back(v1);
  v1.x = 4;
  v1.y = 0;
  v1.z = 0;
  vertices_base.push_back(v1);
  base = revolucion(vertices_base,20,true);
  //VAMOS A CREAR EL PALO
  v1.x = 1.25;
  v1.y = 12;
  v1.z = 0;
  vertices_palo.push_back(v1);
  v1.x = 1.25;
  v1.y = 0;
  v1.z = 0;
  vertices_palo.push_back(v1);
  palo = revolucion(vertices_palo,10,false);
  //VAMOS A CREAR LA CABINA Y EL CABLE
  cabina = _cubo(3);
  encima_cabina = _piramide(3,5);

  //VÉRTICES PARA EL CILINDRO QUE NO CORRESPONDE A LA BASE
  v1.x = 1;
  v1.y = 25;
  v1.z = 0;
  vertices_cilindro_cabina.push_back(v1);
  v1.x = 1;
  v1.y = 0;
  v1.z = 0;
  vertices_cilindro_cabina.push_back(v1);
  cilindro_cabina = revolucion(vertices_cilindro_cabina,10,false);
  // VÉRTICES PARA EL CABLE
  v1.x = 0.2;
  v1.y = 7;
  v1.z = 0;
  vertices_cable.push_back(v1);
  v1.x = 0.2;
  v1.y = 0;
  v1.z = 0;
  vertices_cable.push_back(v1);
  cable = revolucion(vertices_cable,10,false);
  //BASE DEL CABLE
  basecable = _cubo(1.5);
}
void grua::draw_grua(int modo,int r1,int g1, int b1, int r2, int g2, int b2, int grosor)
{


  //*******************************************************************************
  // Vamos a dibujar los objetos
  //******************************************************************************
  switch (modo) {
    case 1:
                    glRotatef(giro_base,0,1,0);
                    //Base
                    glPushMatrix();
                    base.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();
                    //palo
                    glRotatef(giro_palo,1,0,0);
                    glPushMatrix();

                    glTranslatef(0,2,0);
                    palo.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();
                    glRotatef(giro_cilindro,0,1,0);
                    //cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    cabina.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Piramide encima cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    encima_cabina.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Cilindro cabina
                    glPushMatrix();

                    glTranslatef(-5,10,0);
                    glRotatef(90,0,0,-1);

                    cilindro_cabina.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();

                    //Base cable
                    glTranslatef(movimiento_basecable,8,-0.65);
                    glPushMatrix();
                    basecable.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Cable
                    glPushMatrix();

                    glTranslatef(0.75,0,0.75);
                    glScalef(1,-scalate_cable,1);

                    cable.draw_puntos(r1,g1,b1,grosor);
                    glPopMatrix();
                    break;
    case 2:
                    glRotatef(giro_base,0,1,0);
                    //Base
                    glPushMatrix();
                    base.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    //palo
                    glRotatef(giro_palo,1,0,0);
                    glPushMatrix();

                    glTranslatef(0,2,0);
                    palo.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    glRotatef(giro_cilindro,0,1,0);
                    //cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    cabina.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Piramide encima cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    encima_cabina.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Cilindro cabina
                    glPushMatrix();

                    glTranslatef(-5,10,0);
                    glRotatef(90,0,0,-1);

                    cilindro_cabina.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Base Cable
                    glTranslatef(movimiento_basecable,8,-0.65);
                    glPushMatrix();
                    basecable.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    //Cable
                    glPushMatrix();

                    glTranslatef(0.75,0,0.75);
                    glScalef(1,-scalate_cable,1);

                    cable.draw_aristas(r1,g1,b1,grosor);
                    glPopMatrix();
                    break;
    case 3:
                    glRotatef(giro_base,0,1,0);
                    //Base
                    glPushMatrix();
                    base.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    //palo
                    glRotatef(giro_palo,1,0,0);
                    glPushMatrix();

                    glTranslatef(0,2,0);
                    palo.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    glRotatef(giro_cilindro,0,1,0);
                    //cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    cabina.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    //Piramide encima cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    encima_cabina.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    //Cilindro cabina
                    glPushMatrix();

                    glTranslatef(-5,10,0);
                    glRotatef(90,0,0,-1);

                    cilindro_cabina.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    //Base cable
                    glTranslatef(movimiento_basecable,8,-0.65);
                    glPushMatrix();
                    basecable.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    //Cable
                    glPushMatrix();

                    glTranslatef(0.75,0,0.75);
                    glScalef(1,-scalate_cable,1);

                    cable.draw_solido(r1,g1,b1);
                    glPopMatrix();
                    break;
      case 4:
                    glRotatef(giro_base,0,1,0);
                    //Base
                    glPushMatrix();
                    base.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();
                    //palo
                    glRotatef(giro_palo,1,0,0);
                    glPushMatrix();

                    glTranslatef(0,2,0);
                    palo.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();
                    glRotatef(giro_cilindro,0,1,0);
                    //cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    cabina.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();
                    //Piramide encima cabina
                    glPushMatrix();
                    glTranslatef(1.25,9,-1.5);
                    encima_cabina.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();
                    //Cilindro cabina
                    glPushMatrix();

                    glTranslatef(-5,10,0);
                    glRotatef(90,0,0,-1);

                    cilindro_cabina.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();
                    //Base cable
                    glTranslatef(movimiento_basecable,8,-0.65);
                    glPushMatrix();
                    basecable.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();
                    //Cable
                    glPushMatrix();

                    glTranslatef(0.75,0,0.75);
                    glScalef(1,-scalate_cable,1);

                    cable.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
                    glPopMatrix();

                    break;
  }
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
