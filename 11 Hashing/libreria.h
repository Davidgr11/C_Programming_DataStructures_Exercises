#include <stdio.h>
#include <ctype.h>

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

void strupr(char* text) {
  for(; *text; text++)
      *text = toupper(*text);
}
