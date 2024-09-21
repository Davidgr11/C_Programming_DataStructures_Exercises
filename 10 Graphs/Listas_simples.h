#ifndef Listas_simples
#define Listas_simples
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX 30

enum exito {
  VACIO, NO_ENCONTRADO, ENCONTRADO, EXITO, ERROR
};

struct ciudad {
  char nombre[MAX];
	int distancia;
}; typedef struct ciudad CT;

struct secundaria {
  CT datos;
  struct secundaria *sig;
}; typedef struct secundaria N;

//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
int insertar(N **inicio, CT temporal) {
    if (!(*inicio)) {
			N* nuevo = malloc(sizeof(N));
			if(!nuevo) return 0;
			else  { 
				nuevo->datos= temporal;
				nuevo->sig= NULL;
				*inicio=nuevo;
				return 1; 
			}
		}
		else
			return insertar(&(*inicio)->sig, temporal);
}

int recorrer_conexiones(N **inicio)
{
    if(!(*inicio)) return 0;

		N *aux = *inicio;
		//apunto aux a donde apunta inicio
		while(aux != NULL) //si ese nodo no es nulo seguimos recorriendo
		{
				printf(" --%d km-- (%s) ", aux->datos.distancia, aux->datos.nombre);
				aux=aux->sig;//apunto aux al nodo siguiente
		}
		return EXITO;
}

int validar_num(void) //funci�n para validar que no me de un char en un int
{
  int num, band=0;
  while (band == 0) {
    //puts("\nDame el numero");
    if( scanf("%d", &num) == 0 ){
      band = 0;
      // Eliminamos todos los caracteres hasta el primer espacio o salto de linea
      while(getchar() != '\n');
      puts("ERROR, se requiere un numero"); continue;
    }
    else
      band = 1;
  }
  return num;
}

int buscar_simple(N **inicio, char temporal[MAX]) {
    if(!(*inicio))
			return VACIO;

		N *aux = *inicio;
		while(aux!=NULL && strcasecmp(aux->datos.nombre, temporal)!=0) {
			aux=aux->sig;
		}
		if(!aux)
			return NO_ENCONTRADO;

		printf("(%s)", aux->datos.nombre);
		return EXITO;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // Listas_simples