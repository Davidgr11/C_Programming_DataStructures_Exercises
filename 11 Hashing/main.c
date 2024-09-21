#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "libreria.h"

// Nuestras constantes
#define MAX 30
#define MAXREG 50
#define CUBETA 4
#define COLISIONES (int)ceil(MAXREG * .25f)
#define REGISTER "registros" 

////////////////////////////////////////////////////////
/*
Integrantes:
  González Robles David Alejandro
  Rosales González Jesús Alejandro
  Lima Almaráz Javier Sayed

	Compilador CLANG y MINGW
*/
////////////////////////////////////////////////////////
//ESTRUCTURA
struct cuentas {
  char tipo;  // 'd' débito o 'c' cédito
	char num;   //clave de la cuenta
  float monto;//cuanto tiene en deuda o en ingreso
}; typedef struct cuentas T;

struct client {
	char nombre[MAX];
	int edad;
	_Bool estatus; // esta borrado o activo
	char key[4]; //clave del cliente
	T cuenta[3]; // Las 3 cuentas guardadas
}; typedef struct client  C;

struct registro {
  C cliente[CUBETA]; // los clientes que tiene la cubeta
	int cont; // cuantos clientes tiene el registro
	int sig; // registro de colisiones
}; typedef struct registro R;
////////////////////////////////////////////////////////
//FUNCIONES
void archivoCeros() {
    FILE *foutput = fopen(REGISTER, "wb");
    if(!foutput) {
			perror("Error Archivo");
			exit(EXIT_FAILURE);
		}
    for(int i = 0; i < sizeof(R) * ( MAXREG + COLISIONES ); i++)
        putc(0, foutput);

    fclose(foutput);
}

int hashing(char key[4])
// AAdd
// atoi -> argument to int
// dd % 50
{ return atoi(&key[2]) % 50; }//toma como entero los ultimos dos

int second_hashing(char key[4])
// (A (= 97) * 3 + B (= 98) * 2   ) * dd % 12 
{ return (key[0] * 3 + key[1] * 2) * atoi(key + 2) % COLISIONES; }

_Bool llaveValida(char key[4]) {
	return (isdigit(key[3]) && isdigit(key[2]) && isalpha(key[0]) && isalpha(key[1]));
}

void scanLlave(char key[4]) {
  _Bool error = 0;
	do {
		if(error) {
			puts("Hay un error con tu clave. Intente de nuevo AADD:");
			while(getchar() != '\n');
		}

		scanf(" %4[^\n]", key);
		error = 1;
	} while(!llaveValida(key));
	strupr(key);
}

C temporal(void) {
	C cliente = {.estatus = 0};
	_Bool error = 0;
	puts("Dame el nombre cliente: ");
	scanf(" %30[^\n]%*c", cliente.nombre);
 	strupr(cliente.nombre);
	do {
		if (error) puts("El cliente debe ser mayor de edad.");
			puts("Dame la edad del cliente: ");
			cliente.edad = validar_num();
	} while(error = 1, cliente.edad < 18);
	error = 0;
	puts("Dame la clave del usuario que quieres añadir: ");
	scanLlave(cliente.key);

	for(int i = 0; i < 3; i++) {
		error = 0;
		do {
			if (error) puts("La cuenta debe ser de crédito (c) o débito (d).");
			printf("Cuenta %d | ", i + 1);
			puts("Dame el tipo de la primera cuenta\n'D'->Debito   'C'->Credito ");
			scanf(" %c", &cliente.cuenta[i].tipo);
			cliente.cuenta[i].tipo = toupper(cliente.cuenta[i].tipo);
			error = 1;
		} while(cliente.cuenta[i].tipo != 'D' && cliente.cuenta[i].tipo != 'C');
		error = 1;
		
		do {
			if(!error) {
				puts("No es monto válido.");
				while(getchar() != '\n');
			}
			
			printf("Dame el monto de la cuenta %d: ", i + 1);
			error = scanf(" %f", &cliente.cuenta[i].monto);
		} while (!error);

		cliente.cuenta[i].num = rand()% 899 + 100;
    //printf("%d", cliente.cuenta[i].num);
	}
	return cliente;
}



void alta(C cliente) {
	FILE *fp = fopen(REGISTER, "rb+");
	R registro;
	// Error de archivo
	if(!fp) { perror("Error Archivo"); exit(EXIT_FAILURE); }
	// 0 - 49
	fseek(fp, hashing(cliente.key) * sizeof(R), SEEK_SET);
	fread(&registro, sizeof registro, 1, fp);
	// registro [A][B][*][*]
	if(registro.cont < CUBETA) {
		registro.cliente[registro.cont++] = cliente;
  }
	else if(registro.sig == 0) {
		// registro insertados normal [0][1][2][3][4][5][6] ...[49] COLISIONES [50 + 0] [50 + 1] ... [50 + 12]
    // Guardar el segundo hashing
		registro.sig = second_hashing(cliente.key); // 0 - 12
    fseek(fp, -1 * sizeof registro, SEEK_CUR);
    fwrite(&registro, sizeof registro, 1, fp);

		fseek(fp, (MAXREG + registro.sig) * sizeof(R), SEEK_SET);
		fread(&registro, sizeof registro, 1, fp);
		registro.cliente[registro.cont++] = cliente;
	} 
  else {
		if(registro.cont < 4) {
			fseek(fp, (MAXREG + registro.sig) * sizeof(R), SEEK_SET);
			fread(&registro, sizeof registro, 1, fp);
			registro.cliente[registro.cont++] = cliente;
		}
    else {
			puts("No se pudo insertar el usuario porque la tabla ya está llena.");
			fclose(fp);
			return;
		}
	}
	fseek(fp, -1 * sizeof registro, SEEK_CUR);
	fwrite(&registro, sizeof registro, 1, fp);
  printf("Insertado en el registro %lu, posición %d.", ftell(fp) / sizeof registro, registro.cont);
	fclose(fp);
}

void imprimirCliente(C cliente) {
	printf("\nClave: %s.\nNombre: %s \nLa edad del cliente: %d. \nTiene ", cliente.key, cliente.nombre, cliente.edad);
	register char d = 0;
	for(int i = 0; i < 3; i++) 
    if(cliente.cuenta[i].tipo == 'D') d++;
	printf("%d cuenta%c de débito y %d de crédito.\n\n", d, d == 1 ? '\0' : 's', 3 - d);
}

void imprimirCuentas(C cliente) {
	printf("Las cuentas del usuario %s\n", cliente.nombre);
/*
	Cliente: af34
		****************************
		cuenta tipo     monto
		****************************
		000***  Debito  +$3000.00
		000***  Credito -$3000.00
		000***  Debito  +$3000.00
		_____________________
		Utilidad        $3000
*/
	double balance = 0;
  const size_t lines = 50UL;
  for(size_t i = 0; i < lines; i++) putchar('-'); putchar(10);
	printf("%10s\t%10s\t%10s\n", "CUENTA", "TIPO", "MONTO");
  for(size_t i = 0; i < lines; i++) putchar('-'); putchar(10);
	for( int i = 0; i < 3; i++ ) {
		switch(cliente.cuenta[i].tipo) {
			case 'D': balance += cliente.cuenta[i].monto; break;
			case 'C': balance -= cliente.cuenta[i].monto;
		}
  	printf("\t%03d\t\t%s\t\t%c$%.2f\n", abs(cliente.cuenta[i].num), ('D' == cliente.cuenta[i].tipo) ? "Débito" : "Crédito", ('C' == cliente.cuenta[i].tipo) ? '-' : '+', fabsf(cliente.cuenta[i].monto));
	}
  for(size_t i = 0; i < lines; i++) putchar('-'); putchar(10);
	printf("\tBalance/Utilidad:\t\t%c$%.2lf\n", (balance < 0) ? '-': '+', fabs(balance));
  for(size_t i = 0; i < lines; i++) putchar('-'); putchar(10);
}

_Bool buscar_registro(C *cliente, int *indices) {
  FILE *fp = fopen(REGISTER, "rb");
  R registro;
	if(!fp) {perror("Error de archivo"); exit(EXIT_FAILURE);}

	fseek(fp, hashing(cliente->key) * sizeof registro, SEEK_SET);	
	fread(&registro, sizeof registro, 1, fp);
	// NORMAL
	for(int i = 0; i < registro.cont; i++) {
		if( 0 == strncmp(registro.cliente[i].key, cliente->key, 4) ) {
			*cliente = registro.cliente[i];
			if(indices) { indices[0] = ftell(fp)/sizeof registro - 1; indices[1] = i; }
			return 1;
		}
  }
	// COLISIONES
	if (registro.sig != 0) {
    printf("\nSig %d\n", registro.sig);
		fseek(fp, (MAXREG + registro.sig) * sizeof registro, SEEK_SET);
		fread(&registro, sizeof registro, 1, fp);
		// NORMAL
		for(int i = 0; i < registro.cont; i++)
			if( 0 == strncmp(registro.cliente[i].key, cliente->key, 4) ) {
				*cliente = registro.cliente[i];
				if(indices) { indices[0] = ftell(fp)/sizeof registro - 1; indices[1] = i; }
				return 1;
			}
	}
	if(indices) { indices[0] = - 1; indices[1] = -1; }
	return 0;
}

void generar_reporte() {
  FILE *fp = fopen(REGISTER, "rb");
  R registro;
  for(size_t i = 1; i <= MAXREG + COLISIONES; i++) {
    if(i == 1) puts("\nTabla de 50 registros lógicos.\n");
    else if (i == MAXREG + 1) puts("\nTabla de COLISIONES\n");
    fread(&registro, sizeof registro, 1, fp);
    printf("Registro número: %2zu.\tClientes: %d\tSiguiente: %d.\n", i, registro.cont, registro.sig);
    for(size_t j = 1; j <= registro.cont; j++)
      printf("\t·Cliente %zu: %s, Nombre: %s Borrado: %s\n", j, registro.cliente[j - 1].key, registro.cliente[j - 1].nombre, registro.cliente[j - 1].estatus ? "Sí" : "No");
  }
}

C borrar_registro(C *cliente) {
  cliente->estatus = 1;
  return *cliente;
}

C modificar_cliente(C *cliente) {
  char letter = 0;
  do {
    puts("¿Qué quieres modificar del cliente?\na) Nombre.\nb) Edad\nc) Clave");
    scanf(" %c", &letter); while(getchar() != 10);
    switch(tolower(letter)) {
      case 'a':
        puts("Dame el nuevo nombre del cliente.");
        scanf(" %30[^\n]", cliente->nombre);
        strupr(cliente->nombre);
      break;

      case 'b':
      {
        _Bool error = 0;
        do {
          if(error) puts("Error. Debe ser mayor de edad.");
          puts("Dame la nueva edad del usuario.");
          cliente->edad = validar_num();
          error = 1;
        } while(cliente->edad < 18);
      }
      break;

      case 'c':
      {
        puts("Dame la nueva llave del usuario: ");
        scanLlave(cliente->key);
        alta(*cliente);
        memset(cliente, 0, sizeof (C));
        return *cliente;
      }
      break;

      default :
        puts("La opción no es correcta."); 
    }
    puts("¿Quieres otra modificación? (1. si 0. no)");
  } while(validar_num());
  return *cliente;
}

void modificar_registro(int iRegistro, int indice, C modify(C*)) {
  FILE *fp = fopen(REGISTER, "rb+");
  R registro;
  fseek(fp, iRegistro * sizeof registro, SEEK_SET);
  fread(&registro, sizeof registro, 1, fp);
  registro.cliente[indice] = modify(registro.cliente + indice);
  if(!llaveValida(registro.cliente[indice].key)) {
    memmove(registro.cliente + indice, registro.cliente + indice + 1, sizeof(C) * (CUBETA - indice - 1));
    registro.cont--;
  }

  fseek(fp, sizeof registro * iRegistro, SEEK_SET);
  fwrite(&registro, sizeof registro, 1, fp);
  fclose(fp);
}

void comprimir() {
  FILE *fp = fopen(REGISTER, "rb+");
  R registro;
  for(size_t i = 0; i < MAXREG + COLISIONES; i++) {
    fread(&registro, sizeof registro, 1, fp);
    for(size_t j = 0; j < CUBETA; j++)
      if(registro.cliente[j].estatus) {
        fseek(fp, -1 * sizeof registro, SEEK_CUR);
        memmove(registro.cliente + j, registro.cliente + j + 1, sizeof(C) * (CUBETA - j - 1));
        registro.cont--;
        fwrite(&registro, sizeof registro, 1, fp);
        fread(&registro, sizeof registro, 1, fp);
      }
  }
  fclose(fp);
}

C depositos_a_cuenta(C *cliente) {
  _Bool error = 0; size_t i; float monto;
  do {
    _Bool igual = 0;
    if(error) puts("Esa cuenta no existe. Inténtelo de nuevo.");
    fputs("¿Cuál es la cuenta a la que le quiere depositar? ", stdout);
    register int numero = validar_num(); 
    for(i = 0; i < 3; i++) 
      if (numero == abs(cliente->cuenta[i].num)) goto next;
    error = 1;
  } while(1);
  next:
  error = 1;
  do {
    if(!error) {
      puts("No es monto válido.");
      while(getchar() != '\n');
    }
    
    fputs("Dame el monto de despósito: ", stdout);
    error = scanf(" %f", &monto);
  } while (!error);
  cliente->cuenta[i].monto += monto;

  return *cliente;
}

C retiros_a_cuenta(C *cliente) {
  _Bool error = 0; size_t i; float monto;
  do {
    _Bool igual = 0;
    if(error) puts("Esa cuenta no existe. Inténtelo de nuevo.");
    fputs("¿Cuál es la cuenta a la que le quiere retirar? ", stdout);
    register int numero = validar_num();
    for(i = 0; i < 3; i++)
      if (numero == abs(cliente->cuenta[i].num)) goto next;
  error = 1;
  } while(1);
next:
    error = 1;
		do {
			if(!error) {
				puts("No es monto válido.");
				while(getchar() != '\n');
			}
			
			fputs("Dame el monto de retiro: ", stdout);
			error = scanf(" %f", &monto);
		} while (!error);
    if((cliente->cuenta[i].monto - monto) > 0)
      cliente->cuenta[i].monto -= monto;
    else
      perror("Error. No tiene el monto para hacer el retiro");

  return *cliente;
}

int main(void) {
  puts("------BIENVENIDO A HASHING------\n");

  // archivoCeros();
	do { puts("\nMENU\n 1) Alta de registro\n 2) Buscar registro\n 3) Buscar cuentas\n 4) Borrar registro\n 5) Modificar registro\n 6) Depositos a cuenta\n 7) Retiros a cuenta\n 8) Generar reporte\n 9) Salir\n10) Comprimir archivo\n");
		switch(validar_num()) {
      case 0:
        puts("¿Seguro que quieres llenar el archivo de ceros? (0. para abortar)");
        if(validar_num()) archivoCeros(); break;
      case 1:
      	alta(temporal()); break;

      case 2:
      {
				C *cliente = malloc(sizeof(C)); int indices[2];
				puts("Dame la llave del usuario que quieres buscar: ");
				scanLlave(cliente->key);
      	if( buscar_registro(cliente, indices) && !cliente->estatus ) {
					printf("Se encontró el cliente en el registro %d y la posición %d\n", indices[0] + 1, indices[1] + 1);
					imprimirCliente(*cliente);
				}
				else
					puts("No se encontró el cliente.");
				free(cliente);
      } break;

      case 3:
      {
				C *cliente = malloc(sizeof(C)); int indices[2];
        puts("Dame la llave del usuario para consultar las cuentas: ");
        scanLlave(cliente->key);

        if(buscar_registro(cliente, indices) && !cliente->estatus) {
					printf("Se encontró el cliente en el registro %d y la posición %d\n", indices[0] + 1, indices[1] + 1);
          imprimirCuentas(*cliente);
        }
        else
          puts("No se encontró el cliente.");
        free(cliente);
			}
			break;

      case 4: {
        C *cliente = malloc(sizeof(C)); int indices[2];
        puts("Dame la llave del usuario que quieres borrar: ");
        scanLlave(cliente->key);

        if(buscar_registro(cliente, indices)) {
          if(!cliente->estatus) {
            modificar_registro(indices[0], indices[1], borrar_registro);
            printf("Se encontró y se eliminó el usuario: %s\n", cliente->nombre);
          }
          else
            puts("ERROR. El usuario ya está eliminado.");
        }
        else
          puts("No se encontró el cliente.");
        free(cliente);
        break;
      }
      case 5: {
        C *cliente = malloc(sizeof(C)); int indices[2];
        puts("Dame la llave del usuario que quieres modificar: ");
        scanLlave(cliente->key);

        if(buscar_registro(cliente, indices) && !cliente->estatus) {
          puts("Se encontró el cliente.");
          imprimirCliente(*cliente);
          modificar_registro(indices[0], indices[1], modificar_cliente);
        }
        else
          puts("No se encontró el cliente.");
        free(cliente);
      }
      break;
       
      case 6: {
        C *cliente = malloc(sizeof(C)); int indices[2];
        puts("Dame la llave del usuario que quieres depositarle: ");
        scanLlave(cliente->key);

        if(buscar_registro(cliente, indices) && !cliente->estatus) {
          imprimirCuentas(*cliente);
          modificar_registro(indices[0], indices[1], depositos_a_cuenta);
          puts("\nEl monto se actualizó correctamente.");
        }
        else
          puts("No se encontró el cliente.");
        free(cliente);
      }
      break;
      case 7: {
        C *cliente = malloc(sizeof(C)); int indices[2];
        puts("Dame la llave del usuario que quieres retirarle: ");
        scanLlave(cliente->key);

        if(buscar_registro(cliente, indices) && !cliente->estatus) {
          imprimirCuentas(*cliente);
          modificar_registro(indices[0], indices[1], retiros_a_cuenta);
          puts("\nEl monto se actualizó correctamente.");
        }
        else
          puts("No se encontró el cliente.");
        free(cliente);
      }
      case 8:
      	generar_reporte(); break;
        
      case 9:
         puts("Hasta luego :)");
       return 0; 

      case 10:
          comprimir();
          puts("Archivo Comprimido");
          break;
			default:
				puts("No es una opción válida.");
    }
  } while(1);
}
/*
	algoritmo aplicado a las llaves que nos da la dirección
	Tener en cuenta el número máximo de direcciones
	Agregar el 25% más
	No tener más de 3 colisiones
	Factor de carga=#registros archivo/#max registros
	máximo 0.7 o 0.8
	Si exede asignar más espacio
	método de hashing
	utilizar los ultimos 2 digitos y les aplicamos MOD 50
	fseek(hashing(key))
	fread
*/