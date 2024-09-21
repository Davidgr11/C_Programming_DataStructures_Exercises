#include <stdio.h>
#include "Listas_simples.h"
#include "Listas_dobles.h"

int main() {
	char temporal[30]; ND *inicio = NULL, *fin = NULL, *aux;
	puts("|-----BIENVENIDO A LISTAS DE LISTAS-----|");
	do {
		puts (
			"1. Insertar aerolinea.\n"
			"2. Borrar aerolinea.\n"
			"3. Buscar aerolinea.\n"
			"4. Desplegar una aerolinea con pasajeros.\n"
			"5. Desplegar aerolineas.\n"
			"6. Insertar pasajero.\n"
			"7. Buscar pasajero.\n"
			"8. Borrar pasajero.\n"
			"9. Salir.\n" );

    switch(validar_num()) {
			case 1:
						//recorrer_doble(&inicio, &fin);
						switch(insertar_doble(&inicio, &fin)) {
							case  0: puts("Error, no hay espacio"); break;
							case  1: puts("Insertado correctamente al inicio"); break;
							case  2: puts("Insertado correctamente al final"); break;
							case  3: puts("Insertado correctamente en medio"); break;
							case  4: puts("Primer avion insertado de manera correcta"); break;
						}
						break;
			case 2:
            switch(borrar_doble(&inicio, &fin, temporal)) {
							case  0: puts("Aun no hay nada en la lista");								break;
							case  1: puts("Borrado correctamente del inicio");					break;
							case  2: puts("No se encontro ese nombre");									break;
							case  3: puts("Borrado correctamente del final");						break;
							case  4: puts("Borrado correctamente del medio");						break;
							case  5: puts("Unico elemento borrado de manera correcta"); break;
						}
						break;
			case 3:
				switch (buscar_doble(&inicio, &fin, temporal)) {
					case 0: puts("Aun no hay nada en la lista"); break;
					case 1: puts("La busqueda se realizo de manera correcta"); break;
					default: puts("No se encontro ese nombre");
				}
				break;
      case 4:
				aux = obtener_doble( &inicio, &fin, temporal);
				if(aux)
					switch( recorrer_simple(&aux->datos.inicio, &aux->datos.fin) ) {
              case 1: puts("Lista correctamente recorrida de inicio a fin"); break;
              case 2: puts("Lista correctamente recorrida de fin a inicio"); break;
              case 0: puts("Aun no hay nada en la lista"); break;
              default: puts("La lista no se pudo recorrer"); break;
          	}
				else puts("No existe el avion"); break;
      case 5:
            switch( recorrer_doble(&inicio, &fin) ) {
              case 1: puts("Lista correctamente recorrida de inicio a fin"); break;
              case 2: puts("Lista correctamente recorrida de fin a inicio"); break;
              case 0: puts("Aun no hay nada en la lista"); break;
              default: puts("La lista no se pudo recorrer"); break;
          	}
            break;
      case 6:
				aux = obtener_doble( &inicio, &fin, temporal);
				if(aux)
					switch(insertar_simple(&aux->datos.inicio, &aux->datos.fin)) {
						case  0: puts("Error, no hay espacio"); break;
						case  1: puts("Insertado correctamente al inicio"); break;
						case  2: puts("Insertado correctamente al final"); break;
						case  3: puts("Insertado correctamente en medio"); break;
						case  4: puts("Primer elemento insertado de manera correcta"); break;
					}
				else puts("No existe el avion"); break;
      case 7:
				aux = obtener_doble( &inicio, &fin, temporal );
				if(aux)
					switch(buscar_simple(&aux->datos.inicio, &aux->datos.fin, temporal)) {
						case 0: puts("Aun no hay nada en la lista"); break;
						case 1:  puts("No se encontro ese nombre");break;
						default: puts("La busqueda se realizo de manera correcta");
					}
				else puts("No existe el avion"); break;
      case 8:
				aux = obtener_doble( &inicio, &fin, temporal );
				if(aux)
          switch(borrar_simple(&aux->datos.inicio, &aux->datos.fin, temporal)) {
              case  0: puts("Aun no hay nada en la lista"); break;
              case  1: puts("Borrado correctamente del inicio"); break;
              case  2: puts("No se encontro ese nombre"); break;
              case  3: puts("Borrado correctamente del final"); break;
              case  4: puts("Borrado correctamente del medio"); break;
              case  5: puts("Unico elemento borrado de manera correcta"); break;
					}
				else  puts("No existe el avion"); break;

      case 9:
				puts("Adios :)"); return 0;
		 	default:
				puts("No es una opcion valida");
		}
	} while(1);
}