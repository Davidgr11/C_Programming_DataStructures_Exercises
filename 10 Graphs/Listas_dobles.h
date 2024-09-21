#ifndef Listas_dobles
#define Listas_dobles
#ifdef WIN32
	#define CLEAR system("cls");
#else
	#define CLEAR system("clear");
#endif

//PROGRAMA DE LISTAS DOBLEMENTE LIGADAS
//ESTRUCTURAS

struct principal {
    CT datos;
    N * inicio; 
		struct principal *sig, *ant;
}; typedef struct principal ND;

//////////////////////////////////////////////////////////
//FUNCIONES aux
CT llenar(void);
int insertar_ciudadNom(ND ** inicio, ND ** fin, char nomb[MAX]) {
    ND *nuevo;
    CT temporal = {.distancia = 0};
    strcpy(temporal.nombre, nomb);
    nuevo=malloc(sizeof(ND));
    if(!nuevo)
        return ERROR;   //error no hay espacio
    else{
        nuevo->datos=temporal;
        nuevo->sig=NULL;//apunto el nuevo a nulo
        if(!(*inicio)){  //si no hay lista, apuntar inicio a nuevo
            *inicio=nuevo;
            *fin=nuevo;
            nuevo->ant=NULL;//por ser el primero, el ant va a nulo
            return EXITO;
        }
        else{
            ND *aux = *inicio;//apunto aux a donde apunta inicio
            while(aux->sig!=NULL)//si ese nodo no apunta a nulo seguimos recorriendo
            {
                aux=aux->sig;//apunto aux al nodo siguiente
            }
            nuevo->ant=aux;//el ant va al que antes era el fin
            aux->sig=nuevo;//el que apuntaba a nulo ahora apunta a nuevo
            *fin=nuevo;
            return EXITO;
        }
    }
}
int insertar_ciudad(ND **inicio, ND **fin)
{
    ND *nuevo;
    CT temporal = llenar();
    nuevo=malloc(sizeof(ND));
    if(!nuevo)
        return ERROR;   //error no hay espacio
    else{
        nuevo->datos=temporal;
        nuevo->sig=NULL;//apunto el nuevo a nulo
        if(!(*inicio)){  //si no hay lista, apuntar inicio a nuevo
            *inicio=nuevo;
            *fin=nuevo;
            nuevo->ant=NULL;//por ser el primero, el ant va a nulo
            return EXITO;
        }
        else{
            ND *aux = *inicio;//apunto aux a donde apunta inicio
            while(aux->sig!=NULL)//si ese nodo no apunta a nulo seguimos recorriendo
            {
							aux=aux->sig;//apunto aux al nodo siguiente
            }
            nuevo->ant=aux;//el ant va al que antes era el fin
            aux->sig=nuevo;//el que apuntaba a nulo ahora apunta a nuevo
            *fin=nuevo;
            return EXITO;
        }
    }
}

int recorrer(ND **inicio, ND **fin, bool quieres_imprimir_las_conexiones) // MODIFICACIÓN
{
	if(!(*inicio))
		return VACIO;
	else {
		ND *aux = *inicio; // /apunto aux a donde apunta inicio
		while(aux!=NULL)//si ese nodo no es nulo seguimos recorriendo
		{
				printf("(%s)", aux->datos.nombre);
				if(quieres_imprimir_las_conexiones) {
					recorrer_conexiones(&aux->inicio);
					puts(" ");
				}
				else {
					printf("%s", ", ");
				}
				aux=aux->sig;//apunto aux al nodo siguiente
		}
		return EXITO;
	}
}

int buscar_doble(ND **inicio, ND **fin, char temporal[MAX])
{
    if(!(*inicio))
        return VACIO;
    else{
        ND *aux = *inicio;
        printf("Dame el nombre de la ciudad\n");
        scanf(" %30[^\n]s", temporal);
        while(aux!=NULL && !strcasecmp(aux->datos.nombre, temporal))
        {
            aux=aux->sig;
        }
        if(!aux)
            return NO_ENCONTRADO;
        else{
          printf("Nombre: %s", aux->datos.nombre);
            return ENCONTRADO;
        }
    }
}

ND * obtener_doble(ND **inicio, ND **fin, char temporal[MAX])
{
	if(!(*inicio)) return NULL;
	else{
			ND *aux = *inicio;
			while(aux && strcasecmp(aux->datos.nombre, temporal) != 0)
					aux = aux->sig;
          
			if(!aux) {
      	printf("No se encontro la ciudad: %s\n", temporal);
				return NULL;
			}
			
      // printf("Encontrado: %s\n", aux->datos.nombre);
			return aux;
	}
}
void insertar_conexionNOM(ND** inicio, ND** fin, char origen[MAX], char destino[MAX], int dist) {
    ND * aux = obtener_doble(inicio, fin, origen);
    CT temporal = {.distancia = dist};
	strcpy(temporal.nombre, destino);
    insertar(&aux->inicio, temporal);
}

int insertar_conexion(ND** inicio, ND** fin) {
  char ciudad[MAX];
  printf("Dame el nombre de la ciudad de origen\n");
	scanf(" %30[^\n]", ciudad);

  ND * aux = obtener_doble(inicio, fin, ciudad);

  if(!aux)
    return NO_ENCONTRADO;

  printf("Dame el nombre de la ciudad de destino\n");
	scanf(" %30[^\n]", ciudad);
	
	if(!obtener_doble(inicio, fin, ciudad))
    return NO_ENCONTRADO;
	
  if(buscar_simple(&aux->inicio, ciudad) == EXITO) {
		puts("\nERROR. Ya existe esa conexión");
		return ENCONTRADO;
	}
	printf("Dame la distancia (en km) entre las ciudades\n");
	CT temporal = {.distancia = validar_num()};
	
	strcpy(temporal.nombre, ciudad);
	insertar(&aux->inicio, temporal);
	return EXITO;
}

CT llenar(void)
{
    CT city;
    printf("Dame el nombre de la ciudad\n");
    scanf(" %30[^\n]s", city.nombre);
    return city;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // Listas_dobles