#include "Listas_simples.h"
#include "Listas_dobles.h"
int tamGraf = 0;
/*
Equipo 11, integrantes:
  González Robles David Alejandro
  Rosales González Jesús Alejandro
  Lima Almaráz Javier
Compiladores:
  MinGW y Clang
*/
int buscar_repetida(CT matrix[tamGraf], int ciudades, char nombre[MAX]){
  int i;
  for(i = 0; i < ciudades; i++) {
    if(0 == strcasecmp(matrix[i].nombre, nombre))
			return ENCONTRADO;
  }
  return NO_ENCONTRADO;
}

void imprime_matriz(CT matrix[tamGraf], int ciudades) {
	for(int i = 0; i < ciudades; i++)
		printf("[%s]", matrix[i].nombre);
	putchar('\n');
}

int movimiento(ND ** inicio, ND *origen, char destino[MAX], int * rutas, int *ciudades, int acumcd[tamGraf*2], CT matriz[tamGraf*2][tamGraf]) {
	strcpy(matriz[*rutas][*ciudades].nombre, origen->datos.nombre);
	*ciudades += 1;
	
	if(0 == strcasecmp(destino, origen->datos.nombre)) {
		acumcd[*rutas] = *ciudades;
		memcpy(matriz[1 + *rutas], matriz[*rutas], (*ciudades)*sizeof(CT));
		// *ciudades -= 1;
    	*rutas += 1;
		// return EXITO;
	}
	for(N* aux = origen->inicio; aux != NULL; aux = aux->sig) {
    	matriz[*rutas][*ciudades].distancia = aux->datos.distancia;
		ND* origen2 = obtener_doble(inicio, NULL, aux->datos.nombre);
		if(buscar_repetida(matriz[*rutas], *ciudades, origen2->datos.nombre) != ENCONTRADO) {
			movimiento(inicio, origen2, destino, rutas, ciudades, acumcd, matriz);
		}
	}
	*ciudades -= 1;
	return NO_ENCONTRADO;
}

int rutas (ND **inicio, ND **fin, int tamGraf, int opc){
  char ciudad[MAX];
  //COMPROBAR CIUDADES CORRECTAS
  printf("Dame el nombre de la ciudad de origen\n");
	scanf(" %30[^\n]", ciudad);
  ND * origen = obtener_doble(inicio, fin, ciudad);
  if(!origen)
    return NO_ENCONTRADO;

  printf("Dame el nombre de la ciudad de destino\n");
	scanf(" %30[^\n]", ciudad);
  ND * destino = obtener_doble(inicio, fin, ciudad);
	if(!destino)
    return NO_ENCONTRADO;
    
	//PROCEDIMIENTO DE OBTENCIÓN DE RUTAS
  CT matriz[tamGraf*2][tamGraf];
	for(int i = 0; i < tamGraf; i++) // <- este era el for que fallaba
    for(int j = 0; j < tamGraf; j++) {
			matriz[i][j].distancia = 0;
			memset(matriz[i][j].nombre, 0, MAX);
		}
  int rutas = 0, ciudades=0, acumcd[tamGraf*2];
  movimiento(inicio, origen, destino->datos.nombre, &rutas, &ciudades, acumcd, matriz);

  switch(opc) {
    case 1:
        for(int i = 0; i < rutas; i++) {
          for(int j = 0; j < acumcd[i]; j++) {
            if((j + 1) == acumcd[i])
              printf("[%s]", matriz[i][j].nombre);
            else
              printf("[%s] --%d--", matriz[i][j].nombre, matriz[i][j+1].distancia);
          }
          puts("");
        }   break;
    case 2: 
{		
	// si porque es la cantidad menor "menos ciudades"
	int menor = INT16_MAX, dir;
	for(int i=0; i<rutas; i++) {
		// ¿Es < en lugar de >?
		if(acumcd[i] < menor) {
			menor = acumcd[i];
			dir = i;
		}
	}

	printf("La ruta mas corta es: \n");
	for(int j = 0; j < acumcd[dir]; j++) {
	if((j + 1) == acumcd[dir])
		printf("[%s]", matriz[dir][j].nombre);
	else
		printf("[%s] --%d--", matriz[dir][j].nombre, matriz[dir][j+1].distancia); 
	}
	// printf("%s", "");
	printf("\nCon %d ciudades\n", acumcd[dir]);
	break;
}
    case 3:
{
	int dist[rutas];
	for(int i = 0 ; i < rutas; i++)
   dist[i] = 0;

	for(int i = 0; i < rutas; i++) 
	for(int j = 0; j < acumcd[i]; j++) 
		dist[i] += matriz[i][j].distancia;

  printf("La ruta mas eficiente es: \n");
	// Menor empieza en cero, dir no está inicializada
	int menor = INT16_MAX, dir;
	for(int i = 0; i < rutas; i++) {
		if(dist[i] < menor) {
			menor = dist[i];
			dir = i;
		}
	}
	for(int i = 0; i < acumcd[dir]; i++) {
		if((i + 1) == acumcd[dir])
			printf("[%s]", matriz[dir][i].nombre);
		else
			printf("[%s] --%d--", matriz[dir][i].nombre, matriz[dir][i + 1].distancia); 
	}
	printf("\nCon una distancia de %d km\n", menor);

	printf("%s", "La ruta menos eficiente es: \n");
	int mayor = INT16_MIN;
	for(int i = 0; i < rutas; i++) {
		// debe de ser > en lugar de <
		if(dist[i] > mayor) {
			mayor = dist[i];
			dir = i;
		}
	}
	for(int j = 0; j < acumcd[dir]; j++) {
	if((j + 1) == acumcd[dir])
		printf("[%s]", matriz[dir][j].nombre);
	else
		printf("[%s] --%d--", matriz[dir][j].nombre, matriz[dir][j+1].distancia); 
	}
	printf("\nCon una distancia de %d km\n", mayor);
	break;
    }
  }
	return EXITO;
}

int main(void) {
  ND *inicio = NULL, *fin = NULL;
  int val=1;
  puts("------GRAFOS CON LISTAS DE LISTAS------\n\nNota: Si no recupera la estructura, la tendrá que ingresar de manera manual y la anterior se borrará del archivo. Si desea recuperarla, la comentamos en el main");
  do{ //menu de opciones
    puts (
	  "\n0) Recuperar estructura\n"
    "1) Crear estructura\n"
    "2) Insertar ciudad\n"
    "3) Insertar conexion\n"
    "4) Desplegar ciudades\n"
    "5) Rutas de lugar origen a destino\n"
    "6) Ruta mas corta\n"
    "7) Ruta mas eficiente y menos eficiente\n" 
    "8) Salir"
    );
    
	switch(validar_num()) {
		case 0: 
	{
		FILE* fp;
		if((fp = fopen("grafo", "r")) == NULL) {
			perror("Error de archivo");
			exit(EXIT_FAILURE);
		}
		fscanf(fp, "%d", &tamGraf);
		for(size_t i = 0; i < tamGraf; i++) {
			char str[MAX];
			fscanf(fp, " %30[^\n]", str);
			insertar_ciudadNom(&inicio, &fin, str);
		}
		
		while(!feof(fp)) {
			char str[2][30];
			int dist;
			fscanf(fp, " %30[^\n]", str[0]);
			fscanf(fp, " %30[^\n]", str[1]);
			fscanf(fp, "%d", &dist);
			insertar_conexionNOM(&inicio, &fin, str[0], str[1], dist);
		}
		fclose(fp);
		val = tamGraf + 1;
		break;
	}
		case 1: 
				if(tamGraf == 0) {
							puts("Dame el numero de nodos");
							tamGraf = validar_num();
				} else
					puts("ERROR. Ya existe la estructura");
				break;
              
		case 2: 
  { 
		if(tamGraf == 0) {
			puts("Aun no esta creada la estructura.");
			continue;
		}
		int band = 1;
		while(val <= tamGraf && band == 1) {
			insertar_ciudad(&inicio, &fin);
			val++;
			puts("Deseas insertar otra ciudad 1) si otro) No");
			band = validar_num();
		}
    if(val > tamGraf) puts("Ya insertaste todas las ciudades posibles");
		break;
		}
		case 3: 
        if(tamGraf == 0) {
          puts("Aun no esta creada la estructura.");
          continue;
        }
				do {
					if(insertar_conexion(&inicio, &fin) != EXITO)
						puts("No se pudo realizar la conexion.");
					else 
						puts("Conexion exitosa.");

					puts("Quieres otra conexion? 1 Si");
				} while(validar_num() == 1);
				printf("El tamaño del grafo: %d\n\n", tamGraf);
				break;

		case 4:
		if(tamGraf == 0) {
			puts("Aun no esta creada la estructura.");
			continue;
		}
				puts("1. Ver grafo, 2. Ver ciudades");
				switch(validar_num()) {
					case 1: recorrer(&inicio, &fin, true); break;
					case 2: recorrer(&inicio, &fin, false); break;
					default: puts("No es una opción válida");
				} break;
			
		case 5: 
		if(tamGraf == 0) {
			puts("Aun no esta creada la estructura.");
			continue;
		}
		rutas(&inicio, &fin, tamGraf, 1); 
		break;
		case 6: 
		if(tamGraf == 0) {
			puts("Aun no esta creada la estructura.");
			continue;
		}
		rutas(&inicio, &fin, tamGraf, 2); 
		break;
		case 7:
		if(tamGraf == 0) {
			puts("Aun no esta creada la estructura.");
			continue;
		}
		rutas(&inicio, &fin, tamGraf, 3); break;
		case 8:
		{
			puts("Adiós :)");
			FILE* fp;
			if((fp = fopen("grafo", "w")) == NULL) {
				perror("Error de archivo");
				exit(EXIT_FAILURE);
			}
			fprintf(fp, "%d", tamGraf);
			for (ND* aux = inicio; aux; aux = aux->sig) {
				fprintf(fp, "\n%s", aux->datos.nombre);
			}
		
			for (ND* aux = inicio; aux; aux = aux->sig)
			for(N* conec = aux->inicio; conec; conec = conec->sig)
				fprintf(fp, "\n%s\n%s\n%d", aux->datos.nombre, conec->datos.nombre, conec->datos.distancia);

			fclose(fp);
			return 0;
		}
		default: puts("Error de rango");
	}
  } while(1);
}
/*
6
CDMX
MONTERREY
GUADALAJARA
TOLUCA
TEPIC
MERIDA
CDMX
MONTERREY
909
CDMX
TEPIC
737
MONTERREY
TOLUCA
890
GUADALAJARA
TOLUCA
730
GUADALAJARA
TEPIC
204
TOLUCA
GUADALAJARA
63
TOLUCA
CDMX
63
TEPIC
MONTERREY
992
MERIDA
MONTERREY
1991
MERIDA
CDMX
1316
MERIDA
GUADALAJARA
1850
*/