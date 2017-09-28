//**************************************************************************
// Práctica 4 usando objetos
//**************************************************************************

#include <vector>
#include <string>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "jpg_imagen.hpp"
#include "file_ply_stl.h"
using namespace std;

const float AXIS_SIZE=5000;


//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
//Funciones para métodos de dibujo
void 	draw_aristas(float r, float g, float b, int grosor);
void  draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
//Funciones para iluminación
void draw_iluminacion_plana();
void draw_iluminacion_suave();
void calcular_normales_caras();
void calcular_normales_vertices();
//Funciones para textura
void draw_textura(GLuint ident_textura,jpg::Imagen*& imagen);
void draw_textura_ilum_plana(GLuint ident_textura,jpg::Imagen*& imagen);
void draw_textura_ilum_suave(GLuint ident_textura,jpg::Imagen*& imagen);


vector<_vertex3i> caras;
//Atributos para iluminación
vector <_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;
bool b_textura_coord;
bool b_normales_caras;
bool b_normales_vertices;

//Atributos para texturas
GLfloat coefs_s[4] , coefs_t[4] ;  // si mode_text == false, coeficientes para la coord. S idem para coordenada T
vector<_vertex2f> textura_coord; //texels
bool mode_text=true;
//Atributos para ambos
_vertex4f ambiente_difusa; //coeficientes ambiente y difuso
_vertex4f especular; //coeficiente especular
float brillo; //exponente del brillo


};


//*************************************************************************
// clase textura
//*************************************************************************

class textura: public _triangulos3D
{
public:
	textura();
  //Método para leer una imágen y poder usarla con OpenGL. Es el constructor. Le pasamos el nombre del archivo de la imagen
  textura(const char * archivoJPG);

GLuint ident_textura; //Entero que asigna OpenGL a la textura.
jpg::Imagen * imagen; //imagen a leer

};
//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
	_cubo();
	_cubo(float tam);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:
	_piramide();
	_piramide(float tam, float al);
};

//***************************************************************************
// clase PLY
//***************************************************************************

class objeto_PLY: public _triangulos3D
{
public:
	objeto_PLY(char* nombre_archivo);

vector<float> Vertices;
vector<int> Caras;
_file_ply archivo;
};

//***************************************************************************
// clase Revolución
//***************************************************************************

class revolucion: public _triangulos3D
{
public:
	revolucion();
	revolucion(vector<_vertex3f> ver, int num_caras, bool tapas);
};

//***************************************************************************
// clase Revolución Textura
//***************************************************************************

class revolucion_tex: public _triangulos3D
{
public:
  revolucion_tex();
  revolucion_tex(vector<_vertex3f> ver, int num_caras);
};
//****************************************************************************
// Grua
//****************************************************************************
class grua: public _triangulos3D
{
public:
	grua();
	void draw_grua(int modo,int r1,int g1, int b1, int r2, int g2, int b2, int grosor);
	float giro_base =0;
	float giro_palo = 0;
	float giro_cilindro = 0;
	float scalate_cable = 1;
	float movimiento_basecable = 10;
protected:
	revolucion base;
	revolucion palo;
	_cubo cabina;
	_piramide encima_cabina;
	revolucion cilindro_cabina;
	revolucion cable;
	_cubo basecable;
};
