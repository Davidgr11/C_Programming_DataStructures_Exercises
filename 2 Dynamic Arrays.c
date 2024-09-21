#include <stdio.h>
#include <stdlib.h>
/*
Realizado por: Gonz�lez Robles David Alejandro y Rosales Gonz�lez Jesus Alejandro
Programa para probar funciones para manejar un vector ordenado con apuntadores
Compilador MinGW*/

int creaVector(int**,                              const int);
int insertarDato(     int[], const int, const int, const int);
void desplegar(            const int[], const int);
int primeraOcurrencia (    const int[], const int, const int);
int eliminarPosicion(int[],  const int, const int, const int);
int eliminarDato(    int[],  const int, const int, const int);


int main()
{
   int *vector = NULL, dim = 0, opc = 0, dato = 0, exito = 0, tam = 0;
   //regresa la direccion inicial del vector de n posiciones que almacena el int
	do {
      printf("1) Crear vector\n2) Insertar dato\n3) Eliminar un dato\n4) Buscar primera ocurrencia\n5) Recorrer y desplegar vector\n6) Liberar el vector\n7) Salir\n");
      scanf("%d", &opc);
      switch(opc) {
        case 1: // Crear vector
                if(vector) {
                  printf("\nYa hay un vector creado\n");
                  continue;
                }

                  printf("\nDame la dimension del vector que deseas\n");
                  scanf("%d", &dim);
                  exito = creaVector(&vector, dim);
                  if(exito)
                    printf("Creado correctamente\n");
                  else
                    printf("No se pudo crear el vector\n");
                  break;
        case 2: // Insertar dato
                if (!vector) {
                  printf("\nAun no se ha creado un vector.\n");
                  continue;
                }
                printf("\nDame el dato\n");
                scanf("%d", &dato);
                tam += exito = insertarDato(vector, dato, tam, dim);

                if(exito)
                  printf("Se inserto correctamente\n");
                else
                  printf("Ya no hay espacio en el vector\n");
                break;
        case 3: // Eliminar dato o posici�n
              if (!vector) {
                printf("\nAun no se ha creado un vector.\n");
                continue;
              }
              printf("\nDame el dato a eliminar\n");
              scanf("%d", &dato);
              tam -= exito = eliminarDato(vector, dim, tam, dato);

              if(exito)
                printf("Se elimino correctamente\n");
              else
                printf("Ya esta vacio el vector o no se encontro el dato\n");

              break;

        case 4: // Buscar primera cocurrencia
              if (!vector) {
                printf("\nAun no se ha creado un vector.\n");
                continue;
              }
              printf("\nDame el dato a buscar\n");
              scanf("%d", &dato);
              exito = 1 + primeraOcurrencia(vector, dato, tam);
              if(exito > 0)
                printf("El dato se encontro en la posicion: %d\n", exito);
              else
                printf("El dato no se encontro\n");
              break;

        case 5: //
              if (!vector) {
                printf("\nAun no se ha creado un vector.\n");
                continue;
              }
              desplegar(vector, tam);
              printf("Hay %d ocupadas de %d\n", tam, dim);
              break;

        case 6: //
              if (!vector) {
                printf("\nAun no se ha creado un vector.\n");
                continue;
              }
              free(vector); tam = dim = 0; vector = NULL;
              if(!vector)
                printf("Vector liberado correctamente\n");
              break;
        case 7: // Salir del programa
              printf("Adios :)\n");
              return 0;
      }
   } while(1);
}

/* Sirve para crear el vector din�micamente con la funci�n malloc
 * Recibe: la referencia del vector | la dimensi�n del vector
 * Regresa 1 si se cre�, regresa 0 en caso de que malloc no haya creado la direcci�n
*/
int creaVector(int **vector, const int dim) {
  *vector = ( int* ) malloc( dim * sizeof( int ) );
  if(!vector) {  //ap_vector==NULL
    return 0;
  }
  return 1;
}

/* Sirve para encontrar la primera ocurrencia de un dato en el vector
 * Recibe: el vector | el dato a buscar | el tama�o del vector
 * Regresa 1 si se elimin� correctamente, regresa 0 en caso de que la posici�n sea inv�lida
*/
int primeraOcurrencia(const int vector[], const int dato, const int tam) {
  for(int i = 0; 1; i++) {
    if(vector[i] == dato) return i;
    else if(!(i < tam)) return -1;
  }
}

/* Sirve para eliminar una posici�n en el vector
 * Recibe: el vector | el tama�o del vector | la dimensi�n del vector | el dato a eliminar
 * Regresa 1 si se elimin� correctamente, regresa 0 en caso de que la posici�n sea inv�lida
*/
int eliminarPosicion(int vector[], const int posicion, const int dimension, const int tam) {
  if(posicion <= 0 || posicion > tam || posicion >  dimension) return 0;

  for (int i = posicion - 1 ; i < tam - 1 ; i++ )
    vector[i] = vector[i + 1];

  if(posicion == (tam - 1))
    printf("\nSe elimino al final\n");
  else if(posicion == 1)
   printf("\nSe elimino al inicio\n");
   else
   printf("\nSe elimino en medio\n");

  return 1;
}

/* Sirve para buscar y eliminar un dato en el vector con ayuda de eliminar posici�n y primera ocurrencia
 * Recibe: el vector | el tama�o del vector | la dimensi�n del vector | el dato a eliminar
 * Regresa 1 si se elimin� correctamente, regresa 0 en caso de que no haya encontrado el vector
*/
int eliminarDato(int vector[], const int tam, const int dimension, const int dato) {
  int posicion = 1 + primeraOcurrencia(vector, dato, tam),
      exito = eliminarPosicion(vector, posicion, dimension, tam);

  if(!exito) return 0;
  return 1;
}

/* Sirve para insertar (ordenadamente) datos en el vector
 * Recibe: el vector | el dato a insertar | el tama�o del vector | la dimensi�n del vector
 * Regresa 1 si se insert� correctamente, regresa 0 en caso de que el vector est� lleno
*/
int insertarDato(int vector[], const int dato, const int tam, const int dim) {
  int i, cont;
  if(tam == dim) return 0;

  if(!tam || dato < vector[0]) { // insertar al inicio
    if(tam > 0)
    for(i = tam; i > 0; i--)
      vector[i] = vector[i - 1];

    vector[0] = dato;
    printf("\nDato insertado al inicio\n");
  }

  else if(dato > vector[tam - 1]) {
    vector[tam] = dato;
    printf("\nDato insertado al final\n");
  }
  else {
    for(i = 0; dato > vector[i]; i++);
    for(cont = tam - 1; cont >= i; cont--)
      vector[cont + 1] = vector[cont];

     vector[i] = dato;
    printf("\nDato insertado en medio\n");
  }
  return 1;
}

/* Sirve para imprimir el contenido del vector en 2 formas enumerado (0) y no enumerado (1)
 * Recibe: el vector | el tama�o del vector | el modo de impresi�n
 * No regresa ning�n dato
*/
void desplegar(const int vector[], const int tam) {
  // printf("%p", vector);
  for(int i = 0; i < tam; i++)
      printf("[%d]", vector[i]);
  putchar('\n');
}
