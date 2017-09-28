//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

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
void 	draw_aristas(float r, float g, float b, int grosor);
void  draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

vector<_vertex3i> caras;
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

vector<double> Vertices;
vector<unsigned long> Caras;
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
