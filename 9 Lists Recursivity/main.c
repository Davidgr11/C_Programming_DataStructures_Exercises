#include <stdio.h>
#include "Listas_simples.h"

void desplegar(N * inicio) {
	if(inicio!=NULL)  {
		printf("Nombre: %15s\tEdad:%d\n", inicio->datos.nombre, inicio->datos.edad);
		desplegar(inicio->sig);
	}
}

void desplegar_reverso(N * inicio) {
	if(inicio!=NULL) {
		desplegar_reverso(inicio->sig);
		printf("Nombre: %15s\tEdad:%d\n", inicio->datos.nombre, inicio->datos.edad);
	}
}
int insertar_recursivo(N** inicio) {
    if (!(*inicio)) {
			N* nuevo = malloc(sizeof(N));
			if(!nuevo) return 0;
			else  {
				nuevo->datos= llenar();
				nuevo->sig= NULL;
				*inicio=nuevo;
				return 1;
			}
		}
		else
			return insertar_recursivo(&(*inicio)->sig);
}

int main(void) {
	N* inicio = NULL, *fin = NULL; char a = 0;
	while(a++ < 3)
    insertar_recursivo(&inicio);

	puts("Lista desplegada normal:");
  desplegar(inicio);
	puts("Lista desplegada reverso:");
  desplegar_reverso(inicio);
}
/*
a
1
1
e
2
2
c
3
3
b
4
4
d
5
5
*/
