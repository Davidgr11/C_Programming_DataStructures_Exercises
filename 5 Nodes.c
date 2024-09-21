#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Integrantes:
Rosales González Jesús Alejandro
González Robles David Alejandro
Lima Almaraz Javier

Práctica 3:
Listas simplemente ligadas
Compiladores: Mingw y Clang
*/
////////////////////////////////////////////////
//https://replit.com/join/qdinqowjbr-davidgr11//
////////////////////////////////////////////////
// estructura de datos que estan dentro de cada nodo

struct persona {
  int numero;
  char nombre [30];
  int edad;
};
// Estructura de la lista
typedef struct nodo {
  struct persona person;
  struct nodo *siguiente;
} Nodo, * NodoAp;
/////////////////////////////////////////////
// Funciones de insertar
// Reciben la lista con doble apuntador y el nuevo nodo a insertar
int insertarInicio(NodoAp* lista, const NodoAp nuevoNodo);
// Recibe el número donde se va a insertar
int insertarMedio(NodoAp* lista, const int numero, const NodoAp nuevoNodo);
int insertarFinal(NodoAp* lista, const NodoAp nuevoNodo);
int insertar(NodoAp* lista);
//Funciones de borrar
// Reciben la lista con doble apuntador y el nuevo nodo a borrar
void borrarInicio(NodoAp* lista);
// Recibe el número donde se va a borrar
void borrarMedio(NodoAp* lista, const int numero);
void borrarFinal(NodoAp* lista);
int borrar(NodoAp* lista, const char nombre[30]);
// Funciones auxiliares
//Función para desplegar nodos
int imprimeNodos(const NodoAp lista);
//Función para crear nodo nuevo
NodoAp crearNodo(struct persona person);
struct persona crearPersona(void);
// Función para regresar el tamaño de la lista
int tamLista(NodoAp lista);
// Funcion que busca algun nodo por nombre
int buscar(NodoAp lista, const char nombre[30]);
////////////////////////////////////////////
int main(void) {
  NodoAp inicio = NULL; //Inicializamos el apuntador
  int opcion, exito;
  char nombre[30];

  do {
    // Menu de opciones
      puts("\n1) Insertar nodo\n2) Borrar dato\n3) Recorrer\n4) Buscar\n5) Salir del programa\n");
      scanf("%d", &opcion);
    // Opciones
    switch(opcion) {
      case 1: // Insertar
      exito = insertar(&inicio);
      switch(exito) {
        case -1: puts("No se pudo insertar el nodo. :("); break;
        case  0: puts("Insertado correctamente."); break;
        case  1: puts("Insertado correctamente al inicio."); break;
        case  2: puts("Insertado correctamente en medio."); break;
        case  3: puts("Insertado correctamente al final."); break;
      }
        break;
      case 2:  // Borrar
      if(inicio != NULL) {
        printf("Dame el nombre del usuario que quieres borrar:\n");
        scanf(" %30[^\n]s", nombre);
        exito = borrar(&inicio, nombre);
      } else
        puts("Aun no se han insertado nodos.");
      switch(exito) {
        case 1: puts("Usuario eliminado del inicio.\n"); break;
        case 2: puts("Usuario eliminado del medio.\n"); break;
        case 3: puts("Usuario eliminado del final.\n"); break;
        case 0: puts("\n-No hay elementos en la lista.\n"); break;
        case -1: puts("Aun no se han insertado nodos.");
      }
        break;
      case 3: // Recorrer
      exito = imprimeNodos(inicio);
      switch(exito) {
        case -1: puts("Aun no se han insertado nodos."); break;
        case  1: puts("\n--Lista impresa--."); break;
      }
        break;
      case 4: // Buscar
        if(inicio != NULL) {
          printf("Dame el nombre del usuario que quieres buscar:\n");
          scanf(" %30[^\n]s", nombre);
          exito = buscar(inicio, nombre); // Buscar
        } else
      puts("Aun no se han insertado nodos.");
        switch(exito) {
        case 1: puts("Primera coincidencia.\n"); break;
        case 0: puts("\n--No se encontro el usuario.\n"); break;
        case -1: puts("Aun no se han insertado nodos.");
      }
        break;

      case 5: // Salir del programa
        printf("Adios :)\n");
        return 0;
    }
   } while(1);
}
//Función que regrea una estructura tipo struct persona
struct persona crearPersona(void) {
  struct persona person;

  printf("Dame el numero\n");
  scanf("%d", &person.numero);
  printf("Dame la edad\n");
  scanf("%d", &person.edad);
  printf("Dame la nombre\n");
  scanf(" %30[^\n]s", person.nombre);

  return person;
}

NodoAp crearNodo(struct persona person) {
  NodoAp nodo = (NodoAp) malloc(sizeof(Nodo));
  nodo->person = person;
  nodo->siguiente = NULL;
  return nodo;
}

// Función que imprime la lista
int imprimeNodos(NodoAp lista)
{
  if(lista == NULL) return  -1;
  while (lista != NULL) {
    printf("Nombre: %s Numero: %d Edad: %d\n", lista->person.nombre, lista->person.numero , lista->person.edad);
    lista = lista->siguiente;
  }
  return 1;
}

int insertarInicio(NodoAp* lista, const NodoAp nuevoNodo) {
  nuevoNodo->siguiente = *lista;
  *lista = nuevoNodo;
  return 1;
}

int insertarFinal(NodoAp* lista, const NodoAp nuevoNodo) {
  NodoAp auxiliar = *lista;
  while(auxiliar->siguiente)
    auxiliar = auxiliar->siguiente;

  auxiliar->siguiente = nuevoNodo;
  return 1;
}

int insertarMedio(NodoAp* lista, const int numero, const NodoAp nuevoNodo)
{
  NodoAp auxiliar = *lista;
  for(int i = 0; i < numero; i++)
    auxiliar = auxiliar->siguiente;

  nuevoNodo->siguiente = auxiliar->siguiente;
  auxiliar->siguiente = nuevoNodo;
  return 1;
}

int tamLista(NodoAp lista) {
  int tam = 0;
  while (lista != NULL) {
    tam++;
    lista = lista->siguiente;
  }
  return tam;
}

int insertar(NodoAp* lista) {
  const int tam = tamLista(*lista);
  int numero = 0;
  NodoAp auxiliar = *lista, nuevoNodo = crearNodo(crearPersona());
  if(nuevoNodo == NULL) return -1;

  if(tam == 0) {
    *lista = nuevoNodo;
    return 0;
  }
  //stricmp en CODEBLOCKS
  while(strcasecmp(auxiliar->person.nombre, nuevoNodo->person.nombre) < 0) {
    if(auxiliar->siguiente == NULL) {
      insertarFinal(lista, nuevoNodo);
      return 3;
    }
    numero++;
    auxiliar = auxiliar->siguiente;
  }

  if(numero == 0) {
    insertarInicio(lista, nuevoNodo);
    return 1;
  }
  else {
    insertarMedio (lista, --numero, nuevoNodo);
    return 2;
  }
}

int buscar(NodoAp lista, const char nombre[30]) {
  if(lista == NULL) return -1;

  while(strcasecmp(lista->person.nombre, nombre) != 0) {
    lista = lista->siguiente;
    if(lista == NULL) return 0;
  }
  printf("Nombre: %s Numero: %d Edad: %d\n", lista->person.nombre, lista->person.numero , lista->person.edad);

  return 1;
}

int borrar(NodoAp* lista, const char nombre[30]) {
  if(*lista == NULL) return -1;
  int numero = 0; const int tam = tamLista(*lista);
  NodoAp auxiliar = *lista;

  while(strcasecmp(auxiliar->person.nombre, nombre) != 0) {
    numero++;
    auxiliar = auxiliar->siguiente;
    if(auxiliar == NULL) return 0;
  }

  if(numero == 0) {
    borrarInicio(lista);
    return 1;
  } else if(numero == tam - 1) {
    borrarFinal(lista);
    return 3;
  }
  else {
    borrarMedio (lista, --numero);
    return 2;
  }
}

void borrarInicio(NodoAp* lista) {
  NodoAp auxiliar = *lista;
  *lista = (*lista)->siguiente;
  free(auxiliar);
}

void borrarFinal(NodoAp* lista) {
  NodoAp auxiliar = *lista;
  while(auxiliar->siguiente->siguiente)
    auxiliar = auxiliar->siguiente;

  // auxiliar == ultimo nodo == auxiliar2
  free(auxiliar->siguiente);
  auxiliar->siguiente = NULL;
}

void borrarMedio(NodoAp* lista, int numero) {
  NodoAp auxiliar = *lista, auxiliar2;
  for(int i = 0; i < numero; i++)
    auxiliar = auxiliar->siguiente;

  auxiliar2 = auxiliar->siguiente;
  auxiliar->siguiente = auxiliar2->siguiente;
  free(auxiliar2);
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Integrantes:
  Rosales González Jesús Alejandro
  González Robles David Alejandro
  Lima Almaraz Javier

Práctica 3:
  Listas simplemente ligadas

Compiladores:
  Mingw y Clang
*/

////////////////////////////////////////////////
//https://replit.com/join/qdinqowjbr-davidgr11//
////////////////////////////////////////////////

// Estructura de datos que estan dentro de cada nodo

// Estructura de la lista

#ifndef LISTASDOBLES_H
#define LISTASDOBLES_H 1
typedef struct nodoDoble {
  struct persona person;
  struct nodoDoble *siguiente;
  struct nodoDoble * anterior;
} NodoDoble, * NodoApDoble;

/////////////////////////////////////////////
// Funciones de insertar

// Reciben la lista con doble apuntador y el nuevo nodo a insertar
void insertarInicioDoble(NodoApDoble *lista,  const NodoApDoble nuevoNodo);
void insertarMedioDoble(NodoApDoble lista,    const NodoApDoble nuevoNodo);
void insertarFinalDoble(NodoApDoble lista,    const NodoApDoble nuevoNodo);
int insertarDoble(NodoApDoble *lista);

//Funciones de borrar

// Reciben la lista con doble apuntador y el nuevo nodo a borrar
void borrarInicioDoble(NodoApDoble *lista);
// Recibe el número donde se va a borrar
void borrarMedioDoble(NodoApDoble lista);
void borrarFinalDoble(NodoApDoble *lista);
int borrarDoble(NodoApDoble* lista, const char nombre[30]);

// Funciones auxiliares

//Función para desplegar nodos
int imprimeNodosDoble(NodoApDoble lista);
int imprimeReversoNodosDoble(NodoApDoble lista);
void imprimeNodoDoble(const NodoApDoble lista);
//Función para crear nodo nuevo
NodoApDoble crearNodoDoble(struct persona person);
struct persona crearPersonaDoble(void);
// Función para regresar el tamaño de la lista
int tamListaDoble(NodoApDoble lista);
// Funcion que busca algun nodo por nombre
int buscarDoble(NodoApDoble lista, const char nombre[30]);

void limpiarDoble(NodoApDoble * lista);
////////////////////////////////////////////
int menuListasDobles(NodoApDoble * inicio) {
  int opcion, exito;
  char nombre[30];

  do {
    // Menu de opciones
      puts("\n1) Insertar nodo\n2) Borrar dato\n3) Recorrer\n4) Recorrer reverso\n5) Buscar\n6)Limpiar lista\n7) Regresar al menu principal\n");
      scanf("%d", &opcion);
    // Opciones
    switch(opcion) {
      case 1: // Insertar
      exito = insertarDoble(inicio);
      switch(exito) {
        case -1: puts("No se pudo insertar el nodo. :("); break;
        case  0: puts("Insertado correctamente."); break;
        case  1: puts("Insertado correctamente al inicio."); break;
        case  2: puts("Insertado correctamente en medio."); break;
        case  3: puts("Insertado correctamente al final."); break;
      }
      break;


      case 2:  // Borrar

      if((*inicio) != NULL) {
        printf("Dame el nombre del usuario que quieres borrar:\n");
        scanf(" %30[^\n]s", nombre);
        exito = borrarDoble(inicio, nombre);
      } else {
        puts("Aun no se han insertado nodos.");
        continue;
      }
      switch(exito) {
        case 1: puts("Usuario eliminado del inicio.\n"); break;
        case 2: puts("Usuario eliminado del medio.\n"); break;
        case 3: puts("Usuario eliminado del final.\n"); break;
        case 0: puts("\n-No hay elementos que coincidan en la lista.\n"); break;
        case -1: puts("Aun no se han insertado nodos.");
      }
      break;


      case 3: // Recorrer
      exito = imprimeNodosDoble(*inicio);
      switch(exito) {
        case -1: puts("Aun no se han insertado nodos."); break;
        case  1: puts("\n--Lista impresa--."); break;
      }
      break;

      case 4: // Recorrer reverso
      exito = imprimeReversoNodosDoble(*inicio);
      switch(exito) {
        case -1: puts("Aun no se han insertado nodos."); break;
        case  1: puts("\n--Lista reversa impresa--."); break;
      }
      break;

      case 5: // Buscar
      if((*inicio) != NULL) {
        printf("Dame el nombre del usuario que quieres buscar:\n");
        scanf(" %30[^\n]s", nombre);
        exito = buscarDoble(*inicio, nombre); // Buscar
      } else {
        puts("Aun no se han insertado nodos.");
        continue;
      }
      switch(exito) {
        case 1: puts("Primera coincidencia.\n"); break;
        case 0: puts("\n--No se encontro el usuario.\n"); break;
        case -1: puts("Aun no se han insertado nodos.");
      }
      break;
      case 6:
      if((*inicio) != NULL) {
        limpiarDoble(inicio);
        printf("Limpiado correctamente\n");
      }
      else
        puts("Aun no se han insertado nodos.");
      break;

      case 7: printf("Regresando...\n");// Regresar al menú principal
        return 0;
    }
   } while(1);
}
////////////////////////////////////////////
//Función que regrea una estructura tipo struct persona
struct persona crearPersonaDoble(void) {
  struct persona person;

  printf("Dame el numero\n");
  scanf("%d", &person.numero);
  printf("Dame la edad\n");
  scanf("%d", &person.edad);
  printf("Dame la nombre\n");
  scanf(" %30[^\n]s", person.nombre);

  return person;
}

NodoApDoble crearNodoDoble(struct persona person) {
  NodoApDoble nodo = (NodoApDoble) malloc(sizeof(Nodo));
  if(!nodo) return NULL;
  nodo->person = person;
  nodo->siguiente = NULL;
  nodo->anterior = NULL;
  return nodo;
}

void imprimeNodoDoble(const NodoApDoble lista) {
  printf("Nombre: %s Numero: %3d Edad: %3d\n", lista->person.nombre, lista->person.numero, lista->person.edad);
  // printf("Dirección: %p Anterior: %p Siguiente: %p\n", lista, lista->anterior, lista->siguiente);
}

// Función que imprime la lista
int imprimeNodosDoble(NodoApDoble lista)
{
  if(lista == NULL) return  -1;

  do {
    imprimeNodoDoble(lista);
    lista = lista->siguiente;
  } while (lista != NULL);

  return 1;
}

int imprimeReversoNodosDoble(NodoApDoble lista) {
  if(lista == NULL) return  -1;
  while (lista->siguiente) {
    lista = lista->siguiente;
  }

  do {
    imprimeNodoDoble(lista);
  } while ((lista = lista->anterior));

  return 1;
}

void insertarInicioDoble(NodoApDoble *lista,  const NodoApDoble nuevoNodo) {
  nuevoNodo->siguiente = *lista;
  (*lista)->anterior = nuevoNodo;
  *lista = (*lista)->anterior;
}

void insertarFinalDoble(NodoApDoble lista,    const NodoApDoble nuevoNodo) {
  lista->siguiente = nuevoNodo;
  nuevoNodo->anterior = lista;
}

void insertarMedioDoble(NodoApDoble lista,    const NodoApDoble nuevoNodo) {
  nuevoNodo->siguiente = lista;
  nuevoNodo->anterior = lista->anterior;
  lista->anterior->siguiente = nuevoNodo;
  lista->anterior = nuevoNodo;
}

int tamListaDoble(NodoApDoble lista) {
  int tam = 0;
  while (lista != NULL) {
    tam++;
    lista = lista->siguiente;
  }
  return tam;
}

int insertarDoble(NodoApDoble *lista) {
  NodoApDoble auxiliar = *lista, nuevoNodo = crearNodoDoble(crearPersonaDoble());

  if(nuevoNodo == NULL) return -1;

  if(!auxiliar) {
    *lista = nuevoNodo;
    return 0;
  }

  //stricmp en CODEBLOCKS
  if(strcasecmp(auxiliar->person.nombre, nuevoNodo->person.nombre) > 0) {
    insertarInicioDoble(lista, nuevoNodo);
    return 1;
  }

  do {
    if(auxiliar->siguiente == NULL) {
      insertarFinalDoble(auxiliar, nuevoNodo);
      return 3;
    }

    auxiliar = auxiliar->siguiente;
  } while(strcasecmp(auxiliar->person.nombre, nuevoNodo->person.nombre) < 0);

  insertarMedioDoble(auxiliar, nuevoNodo);
  return 2;
}

int buscarDoble(NodoApDoble lista, const char nombre[30]) {
  if(lista == NULL) return -1;

  while(strcasecmp(lista->person.nombre, nombre) != 0) {
    lista = lista->siguiente;
    if(lista == NULL) return 0;
  }

  imprimeNodoDoble(lista);

  return 1;
}

int borrarDoble(NodoApDoble* lista, const char nombre[30]) {
  if(*lista == NULL) return -1;

  NodoApDoble auxiliar = *lista;

  if(strcasecmp(auxiliar->person.nombre, nombre) == 0) {
    borrarInicioDoble(lista);
    return 1;
  }

  do {
    if(strcasecmp(auxiliar->person.nombre, nombre) == 0 && auxiliar->siguiente == NULL) {
      borrarFinalDoble(&auxiliar);
      return 3;
    } else if(strcasecmp(auxiliar->person.nombre, nombre) == 0) {
      borrarMedioDoble (auxiliar);
      return 2;
    }
    auxiliar = auxiliar->siguiente;
    if(auxiliar == NULL) return 0;
  } while(1);

}

void borrarInicioDoble(NodoApDoble* lista) {
  NodoApDoble auxiliar = *lista;
  *lista = (*lista)->siguiente;
  if(*lista) (*lista)->anterior = NULL;
  free(auxiliar);
}

void borrarFinalDoble(NodoApDoble* lista) {
  (*lista)->anterior->siguiente = NULL;
  free(*lista);
}

void borrarMedioDoble(NodoApDoble lista) {
  lista->anterior->siguiente = lista->siguiente;
  lista->siguiente->anterior = lista->anterior;
  free(lista);
}

void limpiarDoble(NodoApDoble  * lista) {
  while(*lista)
    borrarInicioDoble(lista);
}

#endif
