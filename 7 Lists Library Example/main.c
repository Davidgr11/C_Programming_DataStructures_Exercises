#include <stdio.h>
#include <stdlib.h>
#include "Listas_simples.h"
#include "Listas_dobles.h"

int main()
{
    system("color 4b");
    int menu, tipo, exito;
    N *inicio=NULL, *fin=NULL;
    ND *iniciod=NULL, *find=NULL;
    do{
        printf("1)Listas simplemente ligadas\n2)Listas doblemente ligadas\n3)Salir\n");
        scanf("%d", &menu);
        switch (menu) {
        case 1: menu_listas_simples(&inicio, &fin);
                break;//funcion que era el main de listas simples
        case 2: menu_listas_dobles(&iniciod, &find);
                break;//funcion que era el main de listas dobles
        case 3: printf("Te esperamos pronto :)\n");
                break;
      }
    } while(menu!=3);
    return 0;
}

/*
datos predeterminados
1
Elon Musk
3
50
1
Mark Zuckemberg
6
37
1
Jeff Bezos
8
57
1
Satya Nadella
4
54
1
Sundar Pichai
9
49
1
Tim Cook
3
60
*/
