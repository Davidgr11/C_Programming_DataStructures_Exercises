#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 30
//PROGRAMA DE LISTAS DOBLEMENTE LIGADAS
///////////////////////////////////////////////////////////////////////////////////
//ESTRUCTURAS
struct persona//estructura de datos que contiene cada nodo
{
    int numero;
    char nombre[MAX];
    int edad;
};typedef struct persona P;

 struct nodo_doble//estructura de cada nodo de la lista
{
   P datos;//variable con la que accedemos a struct persona
   struct nodo_doble *sig;//apuntador a otro nodo
   struct nodo_doble *ant;//apuntador a otro nodo
};typedef struct nodo_doble ND;

//////////////////////////////////////////////////////////////////////////////////
//FUNCIONES
P llenar(void);
int insertar_doble(ND **inicio, ND **fin);
int insertar_doble_inicio(ND **inicio, ND **fin, P temporal);
int insertar_doble_final(ND **inicio, ND **fin, P temporal);
int insertar_doble_medio(ND **inicio, ND **fin, P temporal);
int recorrer_doble(ND **inicio, ND **fin);
int validar_num(void);
int buscar_doble(ND **inicio, ND **fin, char temporal[MAX]);
int borrar_doble(ND **inicio, ND **fin, char temporal[MAX]);
int borrar_doble_inicio(ND **inicio, ND **fin, char temporal[MAX]);
int borrar_doble_final(ND **inicio, ND **fin, char temporal[MAX]);
int borrar_doble_medio(ND **inicio, ND **fin, char temporal[MAX]);

//////////////////////////////////////////////////////////////////////////////////
int main()
{
    system("color 4b");
    ND *inicio=NULL, *fin=NULL;
    char temporal[MAX];
    int opc, exito;
    printf("-----BIENVENIDO A LISTAS SIMPLEMENTE LIGADAS-----\n");
    do{//Menu de opciones
        printf("\n1) Insertar nodo\n2) Borrar dato\n3) Recorrer\n4) Buscar\n5) Salir del programa\n");
        opc=validar_num();
        switch(opc)
        {
            case 1: exito=insertar_doble(&inicio, &fin);
                    switch(exito) {
                        case  0: puts("Error, no hay espacio"); break;
                        case  1: puts("Insertado correctamente al inicio"); break;
                        case  2: puts("Insertado correctamente al final"); break;
                        case  3: puts("Insertado correctamente en medio"); break;
                        case  4: puts("Primer elemento insertado de manera correcta"); break;
                    }
                    break;
            case 2: exito=borrar_doble(&inicio, &fin, temporal);
                    switch(exito) {
                        case  0: puts("Aun no hay nada en la lista"); break;
                        case  1: puts("Borrado correctamente del inicio"); break;
                        case  2: puts("No se encontro ese nombre"); break;
                        case  3: puts("Borrado correctamente del final"); break;
                        case  4: puts("Borrado correctamente del medio"); break;
                        case  5: puts("Unico elemento borrado de manera correcta"); break;
                    }
                    break;
            case 3: exito=recorrer_doble(&inicio, &fin);
                    switch(exito){
                        case 1: puts("Lista correctamente recorrida de inicio a fin"); break;
                        case 2: puts("Lista correctamente recorrida de fin a inicio"); break;
                        case 0: puts("Aun no hay nada en la lista"); break;
                        default: puts("La lista no se pudo recorrer"); break;
                    }
                    break;
            case 4: exito=buscar_doble(&inicio, &fin, temporal);
                    if(exito==1)
                        puts("La busqueda se realizo de manera correcta");
                    else{
                        if(exito==0){
                            puts("Aun no hay nada en la lista");
                        }
                        else
                            puts("No se encontro ese nombre");
                    }
                    break;
            case 5: puts("Hasta pronto");
                    break;
            default: puts("Error, numero fuera de rango, intenta de nuevo.");
                    break;
        }
    printf("\n");
    //system("pause");
    //system("cls");
    }while(opc!=5);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////
int insertar_doble(ND **inicio, ND **fin)
{
    int exito;
    P temporal;//para guardar datos
    temporal=llenar();
    if(*inicio && (strcasecmp((*inicio)->datos.nombre, temporal.nombre)>0)){
        exito=insertar_doble_inicio(inicio, fin, temporal);
    }
    else{
        if(!(*inicio) || strcasecmp((*fin)->datos.nombre, temporal.nombre)<0){
            exito=insertar_doble_final(inicio, fin, temporal);
        }
        else{
            if((strcasecmp((*inicio)->datos.nombre, temporal.nombre)<0)&&(strcasecmp((*fin)->datos.nombre, temporal.nombre)>0))
                exito=insertar_doble_medio(inicio, fin, temporal);
        }
    }
    return exito;
}

int insertar_doble_inicio(ND **inicio, ND **fin, P temporal)
{
    ND *nuevo;
    nuevo=(ND*)malloc(sizeof(ND));
    if(!nuevo)
        return 0;   //error no hay espacio
    else{
        nuevo->datos=temporal;
        nuevo->ant=NULL;//como sera el primero, su ant va a nulo
        nuevo->sig=*inicio;//nuevo apunta a donde apunta inicio
        (*inicio)->ant=nuevo;//el anterior de inicio ahora apunta al nuevo
        *inicio=nuevo;//inicio apunta a nuevo
        return 1;
    }
}

int insertar_doble_final(ND **inicio, ND **fin, P temporal)
{
    ND *aux, *nuevo;
    nuevo=(ND*)malloc(sizeof(ND));
    if(!nuevo)
        return 0;   //error no hay espacio
    else{
        nuevo->datos=temporal;
        nuevo->sig=NULL;//apunto el nuevo a nulo
        if(!(*inicio)){  //si no hay lista, apuntar inicio a nuevo
            *inicio=nuevo;
            *fin=nuevo;
            nuevo->ant=NULL;//por ser el primero, el ant va a nulo
            return 4;
        }
        else{
            aux=*inicio;//apunto aux a donde apunta inicio
            while(aux->sig!=NULL)//si ese nodo no apunta a nulo seguimos recorriendo
            {
                aux=aux->sig;//apunto aux al nodo siguiente
            }
            nuevo->ant=aux;//el ant va al que antes era el fin
            aux->sig=nuevo;//el que apuntaba a nulo ahora apunta a nuevo
            *fin=nuevo;
            return 2;
        }
    }
}

int insertar_doble_medio(ND **inicio, ND **fin, P temporal)
{
    ND *aux, *nuevo;
    nuevo=(ND*)malloc(sizeof(ND));
    if(!nuevo)
        return 0;   //error no hay espacio
    else{
        nuevo->datos=temporal;
        aux=*inicio;//apunto aux a donde apunta inicio
        while(strcasecmp((aux->sig)->datos.nombre, nuevo->datos.nombre)<0)
        {//mientras el nuevo sea mayor al lo que tiene el siguiente
            aux=aux->sig;//apunto aux al nodo siguiente
        }
        nuevo->sig=aux->sig;//apunto el nuevo al que es mayor al nuevo
        (aux->sig)->ant=nuevo;//al anterior del siguiente será el nuevo
        aux->sig=nuevo;//el que apuntaba a nulo ahora apunta a nuevo
        nuevo->ant=aux;//el ant del nuevo sera el aux
    }
    return 3;
}

int recorrer_doble(ND **inicio, ND **fin)
{
    if(!(*inicio))
        return 0;
    else {
        ND *aux;
        printf("Imprimir:  1)Inicio a fin  Otro)Fin a inicio\n");
        int forma;
        forma=validar_num();
        if(forma==1){
            aux=*inicio;//apunto aux a donde apunta inicio
            while(aux!=NULL)//si ese nodo no es nulo seguimos recorriendo
            {
                printf("Nombre: %s\tNumero: %d\tEdad:%d\n", aux->datos.nombre, aux->datos.numero, aux->datos.edad);
                aux=aux->sig;//apunto aux al nodo siguiente
            }
            //printf("INICIO Nombre: %s\tNumero: %d\tEdad:%d\n", (*inicio)->datos.nombre, (*inicio)->datos.numero, (*inicio)->datos.edad);
            //printf("FIN    Nombre: %s\tNumero: %d\tEdad:%d\n", (*fin)->datos.nombre, (*fin)->datos.numero, (*fin)->datos.edad);
            return 1;
        }
        else{
            aux=*fin;
            while(aux!=NULL)//si ese nodo no es nulo seguimos recorriendo
            {
                printf("Nombre: %s\tNumero: %d\tEdad:%d\n", aux->datos.nombre, aux->datos.numero, aux->datos.edad);
                aux=aux->ant;//apunto aux al nodo siguiente
            }
            //printf("INICIO Nombre: %s\tNumero: %d\tEdad:%d\n", (*inicio)->datos.nombre, (*inicio)->datos.numero, (*inicio)->datos.edad);
            //printf("FIN    Nombre: %s\tNumero: %d\tEdad:%d\n", (*fin)->datos.nombre, (*fin)->datos.numero, (*fin)->datos.edad);
            return 2;
        }
    }
}

P llenar(void)  //Función para llenar los datos del nodo
{
    P per;
    printf("Dame el nombre\n");
    scanf(" %30[^\n]s", per.nombre);
    printf("Dame el numero\n");
    per.numero=validar_num();
    printf("Dame la edad\n");
    per.edad=validar_num();
    return per;//regresamos una estructura de los datos que tiene una persona
}

int validar_num(void) //función para validar que no me de un char en un int
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

int borrar_doble(ND **inicio, ND **fin, char temporal[MAX])
{
    int exito;
    exito=buscar_doble(inicio, fin, temporal);
    if(exito==0 || exito==2)
        return exito;
    else
        puts("Encontrado");
    if((strcasecmp((*inicio)->datos.nombre, temporal)==0) && (*inicio)->sig!=NULL){//si es igual al inicio
        exito=borrar_doble_inicio(inicio, fin, temporal);
    }
    else{
        if(strcasecmp((*fin)->datos.nombre, temporal)==0){//si es igual al final
            exito=borrar_doble_final(inicio, fin, temporal);
        }
        else{
            if((strcasecmp((*inicio)->datos.nombre, temporal)<0)&&(strcasecmp((*fin)->datos.nombre, temporal)>0))
                exito=borrar_doble_medio(inicio, fin, temporal);
        }
    }
    return exito;
}

int borrar_doble_inicio(ND **inicio, ND **fin, char temporal[MAX])
{
    ND *aux;
    aux=*inicio; //lo copio para liberarlo
    *inicio=(*inicio)->sig;//inicio apunta al siguiente
    (*inicio)->ant=NULL;
    free(aux);
    return 1;
}

int borrar_doble_final(ND **inicio, ND **fin, char temporal[MAX])
{
    if((*inicio)->sig!=NULL)//hay mas de uno
    {
        ND *aux, *aux2;
        aux=*inicio;
        while((aux->sig)->sig!=NULL){//se detiene si lo que tiene dos mas adenlante es nulo
            aux=aux->sig;
        }
        aux2=*fin;
        aux->sig=NULL;//ahora ese apunta a nulo
        free(aux2);
        *fin=aux;//fin ahora es el de atras
        return 3;
    }
    else{//solo hay uno
        ND *aux;
        aux=*inicio;
        free(aux);
        *inicio=NULL;
        *fin=NULL;
        return 5;
    }
}

int borrar_doble_medio(ND **inicio, ND **fin, char temporal[MAX])
{
    ND *aux, *aux2, *aux3;
    aux=*inicio;
    while(strcasecmp(aux->sig->datos.nombre, temporal)!=0)
    {//mientras temporal no sea igual al que va adelante
        aux=aux->sig;
    }
    aux2=aux->sig;//copio el siguiente para liberarlo despues
    aux3=(aux->sig)->sig;//copio el sig sig para no perderlo
    aux->sig=aux3;//ahora el siguiente va a ser dos adelante
    aux3->ant=aux;//pongo el anterior
    free(aux2);
    return 4;
}

int buscar_doble(ND **inicio, ND **fin, char temporal[MAX])
{
    if(!(*inicio))
        return 0;
    else{
        ND *aux;
        printf("Dame el nombre\n");
        scanf(" %30[^\n]s", temporal);
        aux=*inicio;
        while(aux!=NULL && strcasecmp(aux->datos.nombre, temporal)!=0)
        {
            aux=aux->sig;
        }
        if(!aux)
            return 2;
        else{
            printf("Nombre: %s\tNumero: %d\tEdad:%d\n", aux->datos.nombre, aux->datos.numero, aux->datos.edad);
            return 1;
        }
    }
}

/*
short int comp_datos(struct datos origen1, struct datos origen2)

Comparar los datos del Origen 1 con el Origen 2
RECIBE: La dos estructuras a comparar
ENVIA: -1 origen1<origen2
        0 origen1=origen2
        1 origen1>origen2

{
    if(origen1.num_jug<origen2.num_jug)
        return -1;
    else
        if(origen1.num_jug>origen2.num_jug)
            return 1;
        else //SON IGUALES
            return(strcmp(origen1.nombre_jug,origen2.nombre_jug));
}
*/
