//**************************************************************************
// Práctica 4
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
#include "jpg_imagen.hpp"

using namespace std;


//*********************************************************
// CONSTRUCTORES
//**********************************************************
_puntos3D::_puntos3D()
{

}
_triangulos3D::_triangulos3D()
{
  ambiente_difusa._0 = 0;
  ambiente_difusa._1 = 0;
  ambiente_difusa._2 = 1.0;
  ambiente_difusa._3 = 1;

  brillo = 12;

  especular._0 = 1.0;
  especular._1 = 0.5;
  especular._2 = 0.7;
  especular._3 = 1.0;

  mode_text = true;
  b_textura_coord = false;
  for(int i = 0; i< 4;i++)
  {
    coefs_s[i]=0.0;
    coefs_t[i]=0.0;

  }

  coefs_t[1] = 1.0;
  coefs_s[0] = 1.0;

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
  //Abrimos el archivo
  archivo.open(nombre_archivo);
  //Leemos los vértices y las caras
  archivo.read(Vertices,Caras);
  //Cerramos el archivo para que no ocurran errores
  archivo.close();
  _vertex3f aux;
  _vertex3f v;
  _vertex3i c;
  //Guardamos en vértices
  for(int i = 0; i< Vertices.size(); i+=3)
  {
      v.x = Vertices[i];
      v.y = Vertices[i+1];
      v.z = Vertices[i+2];
      vertices.push_back(v);
  }
  //Guardamos en caras
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

//*******************************************************************************
//
// textura
//*******************************************************************************

textura::textura(const char *archivoJPG)
{
  this->imagen = new jpg::Imagen(archivoJPG);

}

textura::textura()
{}

//*******************************************************************************
//
// Revolución con textura
//*******************************************************************************

revolucion_tex::revolucion_tex()
{

}

revolucion_tex::revolucion_tex(vector<_vertex3f> ver, int num_caras)
{
  int i,j;
  _vertex3f vertices_aux;
  _vertex3i caras_aux;
  _vertex2f tex_aux;
  float alfa = 2*3.1416/num_caras;
  float alfa_aux = 2*3.1416/num_caras;
  vector <float> distancias;
  float distancia_total=0.0;
  b_textura_coord=true;
  int num_aux;

  //calculo las distancias para las coordenadas de la textura

  num_aux = ver.size();

  for(i=0; i<num_aux-1;++i)
  {
    distancias.push_back(distancia_total);
    distancia_total += sqrt((ver[i].x-ver[i+1].x)*(ver[i].x-ver[i+1].x)+
                            (ver[i].y-ver[i+1].y)*(ver[i].y-ver[i+1].y)+
                            (ver[i].z-ver[i+1].z)*(ver[i].z-ver[i+1].z));
  }

  //Normalizamos las distancias
  for(i=0;i<num_aux-1;++i)
  {
    distancias[i] = 1.0-distancias[i]/distancia_total;

  }
  distancias[0] = 1.0; //primera instancia
  distancias.push_back(0.0); //última instancia

  //tratamiento de los vértices

  for(j=0;j<num_caras+1;++j)
  {
    tex_aux.s=j/(1.0*num_caras);
    for(i=0;i<num_aux;i++)
    {
        vertices_aux.x =  ver[i].x * cos(alfa);
        vertices_aux.z =  ver[i].x * sin(alfa);
        vertices_aux.y  = ver[i].y;
        vertices.push_back(vertices_aux);

      tex_aux.t=distancias[i];
      textura_coord.push_back(tex_aux);
    }
    alfa += alfa_aux;
  }

  //asignación manual de coordenadas de textura

  mode_text = false;
  b_textura_coord=true;

  // tratamiento de las caras

  for(j=0;j<num_caras;j++)
  {
    for(i=0;i<num_aux-1;i++)
    {
      caras_aux._0=i+(j+1)*num_aux;
      caras_aux._1=i+1+(j+1)*num_aux;
      caras_aux._2=i+1+j*num_aux;

      caras.push_back(caras_aux);

      caras_aux._0=i+1+j*num_aux;
      caras_aux._1=i+j*num_aux;
      caras_aux._2=i+(j+1)*num_aux;

      caras.push_back(caras_aux);

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

//***************************************************************************
//
//           Métodos _triangulos3D
//
//***************************************************************************
void _triangulos3D::calcular_normales_caras()
{
  normales_caras.resize(caras.size());

  for(unsigned long i=0;i<caras.size();i++)
  {
    //obtener dos vectores en el triángulo y calcular el producto vectorial
    _vertex3f
              a1=vertices[caras[i]._1]-vertices[caras[i]._0],
              a2=vertices[caras[i]._2]-vertices[caras[i]._0],
              n=a1.cross_product(a2);
    //modulo
    float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
    //normalización
    normales_caras[i]= _vertex3f(n.x/m,n.y/m,n.z/m);
  }
  b_normales_caras = true; //ponemos a true que hemos calculado las normales de las caras
}

void _triangulos3D::calcular_normales_vertices()
{
   int i,j;
   if(b_normales_vertices == false)
   {
     if(b_normales_caras==false) calcular_normales_caras(); //Si no hemos calculado las normales de las caras hay que hacerlo

     normales_vertices.resize(vertices.size());
     for(i=0;i<vertices.size();i++)
     {
       normales_vertices[i].x = 0.0;
       normales_vertices[i].y = 0.0;
       normales_vertices[i].z = 0.0;
     }
     for(i=0;i<caras.size();++i)
     {
       //se suma la normal de la cara a las normales de los tres vértices de la cara.
       normales_vertices[caras[i]._0]+=normales_caras[i];
       normales_vertices[caras[i]._1]+=normales_caras[i];
       normales_vertices[caras[i]._2]+=normales_caras[i];
     }
     //Normalización
     for(i=0;i<vertices.size();i++)
     {
       normales_vertices[i].normalize(); //normalizamos
     }
     b_normales_vertices=true; //ponemos a true que hemos calculado las normales de los vértices
   }
}

void _triangulos3D::draw_iluminacion_plana()
{
  int i;
  GLfloat ambient_component[4]={1,1,1,1};

  if(b_normales_caras==false) calcular_normales_caras();

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  //Hay que añadir más luces
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  //Atributos de la luz
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  //Vamos dibujando
  for(i=0;i<caras.size();++i)
  {
    glNormal3fv((GLfloat *) &normales_caras[i]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING); //deshabilitamos las luces

}

void _triangulos3D::draw_iluminacion_suave()
{
  int i;
  GLfloat ambient_component[4]={1,1,1,1};

  if(b_normales_vertices==false) calcular_normales_vertices();

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  //Vamos dibujando
  for(i=0;i<caras.size();++i)
  {
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();

  glDisable(GL_LIGHTING); //deshabilitamos las luces
}

void _triangulos3D::draw_textura(GLuint ident_textura,jpg::Imagen*& imagen)
{
  //Carga la imagen
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
  //activación de la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  //vamos a realizar la generación automática de texturas

  if(mode_text)
  {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
  }

  glColor3f(1.0,1.0,1.0); //máscara blanca
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  //Vamos dibujando
  for(int i =0; i<caras.size();++i)
  {
    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
}

void _triangulos3D::draw_textura_ilum_suave(GLuint ident_textura,jpg::Imagen*& imagen)
{

  //Carga la imagen
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
  GLfloat material_blanco[4]={1,1,1,1}; //para que no se quede negra del todo

  if(b_normales_vertices==false) calcular_normales_vertices();

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco); //para que no quede del todo negra, si no que queda con sombra
  //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  //activamos la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  if(mode_text)
  {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
  }
  glColor3f(1.0,1.0,1.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  for(int i =0; i<caras.size();++i)
  {
    if (b_textura_coord) //solo se utiliza para la revolución, que es cuando asignamos manualmente las coordenadas
    {
      glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_LIGHTING);

}

void _triangulos3D::draw_textura_ilum_plana(GLuint ident_textura,jpg::Imagen*& imagen)
{

  //Carga la imagen
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imagen->tamX(), imagen->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagen->leerPixels());
  GLfloat material_blanco[4]={1,1,1,1}; //Para que no se quede negra del todo

  if(b_normales_caras == false) calcular_normales_caras();

  //activamos la iluminación
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  //Hay que añadir más luces
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_blanco); //para que no quede del todo negra
  //glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *)&ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);

  //activamos la textura
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,ident_textura); //vínculo con la tectura
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  if(mode_text)
  {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_S,GL_EYE_PLANE,coefs_s);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGenfv(GL_T,GL_EYE_PLANE,coefs_t);
  }
  glColor3f(1.0,1.0,1.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);

  for(int i =0; i<caras.size();++i)
  {
    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._0].s,textura_coord[caras[i]._0].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._1].s,textura_coord[caras[i]._1].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

    if (b_textura_coord)
    {
      glTexCoord2f(textura_coord[caras[i]._2].s,textura_coord[caras[i]._2].t);

    }

    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }

  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_LIGHTING);

}


//***********************************************************************************
//
//           Método grúa
//
//***********************************************************************************
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
