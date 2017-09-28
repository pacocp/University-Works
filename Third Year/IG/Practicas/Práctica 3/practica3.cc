//**************************************************************************
// Práctica 3
//
// Domingo Martin Perandres 2013-2016
// Francisco Carrillo Pérez ;Informática Gráfica; Grupo:B1
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include "objetos.h"
#include <GL/glut.h>
#include <ctype.h>
#include <cmath>

// tamaño de los ejes
/*const int AXIS_SIZE=5000;*/

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1000,UI_window_height=1000;



//***************************************************************************
// Variable para cambiar
//***************************************************************************
int pulso = 1;

//**********************************************************************
// OBJETOS
//**********************************************************************
_piramide tetraedro(5,9);
_cubo cubo(5);
objeto_PLY ply("beethoven");
objeto_PLY ply2("ant");
objeto_PLY ply3("big_dodge");
objeto_PLY ply4("perfil");
revolucion peon(ply4.vertices,40,true);
revolucion peon2(ply4.vertices,40,false);
grua grua;
//**************************************************************************
//
//***************************************************************************
void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************



void draw_objects()
{

	if(pulso%4 == 1)
	{
		grua.draw_grua(1,0,0,0,0.12,1,1,2);
	}
	else if(pulso%4 == 2)
	{
			grua.draw_grua(2,0,0,0,0.12,1,1,2);
	}
	else if(pulso%4 ==3)
	{
		grua.draw_grua(3,0,0,0,0.12,1,1,2);
	}
	else if(pulso%4==0)
	{
		grua.draw_grua(4,0,0,0,0.12,1,1,2);
	}

	/*if(pulso%28 == 1)
	{
		tetraedro.draw_puntos(0,0,0,8);

	}
	else if(pulso%28 ==2)
	{
		tetraedro.draw_aristas(0,0,0,3);
	}
	else if(pulso%28 == 3)
	{
		tetraedro.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 4)
	{
		tetraedro.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	else if(pulso%28 == 5)
	{
		cubo.draw_puntos(0,0,0,8);
	}
	else if (pulso%28 == 6)
	{
		cubo.draw_aristas(0,0,0,3);
	}
	else if(pulso%28 == 7)
	{
		cubo.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 8)
	{
		cubo.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	else if(pulso%28 == 9)
	{
		ply.draw_puntos(0,0,0,8);
	}
	else if(pulso%28 == 10)
	{
		ply.draw_aristas(0,0,0,3);
	}
	else if(pulso%28 == 11)
	{
		ply.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 12)
	{
		ply.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	else if(pulso%28 == 13)
	{
		ply2.draw_puntos(0,0,0,8);
	}
	else if(pulso%28 == 14)
	{
		ply2.draw_aristas(0,0,0,3);
	}
	else if(pulso%28 == 15)
	{
		ply2.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 16)
	{
		ply2.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	else if(pulso%28 == 17)
	{
		ply3.draw_puntos(0,0,0,8);
	}
	else if(pulso%28 == 18)
	{
		ply3.draw_aristas(0,0,0,3);
	}
	else if(pulso%28 == 19)
	{
		ply3.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 20)
	{
		ply3.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	else if(pulso%28 == 21)
	{
		peon.draw_puntos(0,0,0,8);
	}
	else if(pulso%28 == 22)
	{
		peon.draw_aristas(0,0,0,2);
	}
	else if(pulso%28 == 23)
	{
		peon.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 24)
	{
		peon.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	else if(pulso%28 == 25)
	{
		peon2.draw_puntos(0,0,0,8);
	}
	else if(pulso%28 == 26)
	{
		peon2.draw_aristas(0,0,0,2);
	}
	else if(pulso%28 == 27)
	{
		peon2.draw_solido(0,0.8,0.8);
	}
	else if(pulso%28 == 0)
	{
		peon2.draw_solido_ajedrez(0,0,0,0,0.8,0.8);
	}
	*/








}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
	if(toupper(Tecla1) == 'M') {pulso++;draw_scene();} //para moverme de figura
	else if (toupper(Tecla1)=='Q') exit(0);
	//pulso++;
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1: grua.giro_cilindro+=1;
	if(grua.giro_cilindro > 180)
	{
		grua.giro_cilindro = 180;
	}
	break;
	case GLUT_KEY_F2: grua.giro_cilindro-=1;
	if(grua.giro_cilindro < -180)
	{
		grua.giro_cilindro = -180;
	}
	break;
	case GLUT_KEY_F3: grua.movimiento_basecable +=1;
	if(grua.movimiento_basecable > 17)
	{
		grua.movimiento_basecable = 17;
	}
	break;
	case GLUT_KEY_F4: grua.movimiento_basecable -=1;
	if(grua.movimiento_basecable < 10)
	{
		grua.movimiento_basecable = 10;
	}
	break;
	case GLUT_KEY_F5: grua.scalate_cable +=0.2;
	if(grua.scalate_cable > 2)
	{
		grua.scalate_cable = 2;
	}
	break;

	case GLUT_KEY_F6: grua.scalate_cable-=0.2;
	if(grua.scalate_cable < 1)
	{
		grua.scalate_cable = 1;
	}
	break;

}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
