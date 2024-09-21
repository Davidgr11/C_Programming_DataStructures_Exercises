#include <stdio.h>
#include <stdlib.h>
#define maxBandera 8

/*David Alejandro González Robles, Jesús Alejandro Rosales González
6 / agosto / 2021 | Compilador MinGW
Programa para manejar un conjunto de ocho banderas en una variable "unsigned char" usando los operadores a nivel de bits de C*/

typedef unsigned char UC;
// 1. Encender bandera (si está apagada, la enciende; si está encendida, la deja así).
short int encender(UC *bandera, short int posicion, int maximo);
// 2. Apagar bandera (si está encendida, la apaga; si está apagada, la deja así).
short int apagar(UC *bandera, short int posicion, int maximo);
// Comprueba bandera(devuelve 0, si está apagada y 1, si está encendida).
short int comprobar(UC bandera, short int posicion, int maximo);
// Desplegar todas las banderas (0, si está apagada y 1 si está encendida).
void desplegar(UC bandera, short int maximo);

int main() {
  //system("color 6f");

  UC banderas = 0;
  short int numband, exito, opc;
  do
  {
    system("cls");
    printf("---------BIENVENIDO---------\n");
    printf("1)Encender bandera\n2)Apagar bandera\n3)Comprobar bandera\n4)Desplear banderas\n5)Salir\n");
    scanf("%d", &opc);
    switch(opc)
    {
      case 1: printf("Dame el numero de bandera (1-%d)\n", maxBandera);
              scanf("%hi", &numband);
              exito=encender(&banderas, numband, maxBandera);
              if(exito==0)
                printf("Error de rango\n");
              else
                printf("Proceso exitoso\n");
              break;
      case 2: printf("Dame el numero de bandera (1-%d)\n", maxBandera);
              scanf("%hi", &numband);
              exito=apagar(&banderas, numband, maxBandera);
              if(exito==0)
                printf("Error de rango\n");
              else
                printf("Proceso exitoso\n");
              break;
      case 3: printf("Dame el numero de bandera (1-%d)\n", maxBandera);
              scanf("%hi", &numband);
              exito=comprobar(banderas, numband, maxBandera);
              if(exito==0)
                printf("Error de rango\n");
              else{
                if(exito==1)
                    printf("Bandera encendida\n");
                else
                    printf("Bandera apagada\n");
              }
              break;
      case 4: desplegar(banderas, maxBandera);
              break;
      case 5: printf("Adios\n");
              break;
    }
    system("pause");
  }while(opc!=5);
  return 0;
}
//paso las banderas por referencia, la posicion y el máximo por valor
short int encender(UC *bandera, short int posicion, int maximo)
{
    if(posicion<1 || posicion>maximo)
        return 0;//Numero fuera de rango
    else
    {
        short int i, valorband;
        if(posicion<=2)
            valorband=posicion;//posicion 1 y 2 se llena con el mismo
        else{
            for(valorband=2, i=3;i<=posicion;i++)
                valorband*=2;
        }
        *bandera=*bandera | valorband;//OR para que si estaba apagada se encienda y sino que se quede encendida
        return 1;//exito
    }
}
//paso las banderas por referencia, la posicion y el máximo por valor
short int apagar(UC *bandera, short int posicion, int maximo)
{
    if(posicion<1 || posicion>maximo)
        return 0;//Numero fuera de rango
    else
    {
        short int i, valorband;
        if(posicion<=2)
            valorband=posicion;//posicion 1 y 2 se llena con el mismo
        else{
            for(valorband=2, i=3;i<=posicion;i++)
                valorband*=2;
        }
        if(*bandera & valorband)//si esta encendida entonces si la apago
            *bandera=*bandera ^ valorband;
        else
            printf("La bandera ya estaba apagada\n");
            //proceso alterno: *bandera &= ~valorband;
        return 1;//exito
    }
}
//paso las banderas,la posicion y el máximo por valor
short int comprobar(UC bandera, short int posicion, int maximo)
{
    if(posicion > maximo || posicion < 1)//verificamos rango
        return 0;
    else//recorremos un 1 en la posición indicada y aplicamos AND con la bandera
        bandera &= 1 << --posicion;
    if(bandera)//si existe significa que esta encendida
        return 1;
    else //si no existe significa que esta apagada
        return -1;
}
void desplegar(UC bandera, short int maximo)
{
    for(short i=0; i<maximo; i++, bandera<<=1) {//voy recorriendo
      printf("[%d]", (bandera & 0b10000000) ? 1 : 0);//imprimo 1 o 0
    }
    printf("\n");
}
