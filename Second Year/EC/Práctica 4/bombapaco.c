/************************************************************
  Francisco Carrillo Pérez                                  *
  Estructura de Computadores                                *
  Práctica 4                                                *
************************************************************/

#include <stdio.h>    // para printf()
#include <stdlib.h>   // para exit()
#include <string.h>   // para strncmp()/strlen()
#include <sys/time.h> // para gettimeofday(), struct timeval
// gcc -m32 –O2 bombapaco -o bombapaco.c

char password[]="fibonacci\n";
int  passcode  = 4554;

void boom(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void defused(){
	printf("·························\n");
	printf("··· bomba desactivada ···\n");
	printf("·························\n");
	exit(0);
}

void encriptar(char * cad)
{
	cad[1] = '0';
	cad[3] = '1';
	if(cad[3] == '1')
	{
		cad[5] = '1';
	}
	else
	{
		cad[7] = 'C';
	}
	
	cad[8] = 'I';
	
}
int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
#define TLIM 10
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);

	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);
	encriptar(password);
	if (strncmp(pass,password,strlen(password)))
		boom();

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
		boom();

	printf("Introduce el código: ");
	scanf("%i",&pasv);
	if (pasv!=passcode)
		boom();

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
		boom();

	defused();

	return 0;
}
