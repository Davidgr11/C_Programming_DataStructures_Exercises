#include <stdio.h>
//#include <graphics.h>
#include <time.h>
/*
Gonzalez Robles David Alejandro
Vania Cadena Aguilar
Ángel López Vudoyra
Alethia Silvana Morán Franco
*/
struct oper
{
    float monto;
    int egoin, tipo;
};typedef struct oper R;
int main() {
	srand(time(NULL));
	int i, validos=0;
	FILE *archivo;
	R oper[20];
    system("color 4A");
	printf("---Graficas:\n");
	archivo=fopen("cuenta.csv", "r");
	if(archivo==NULL){
        printf("Error al abrir\n");
	}
	else{
        rewind(archivo);
        printf("a");
        for(i=0;i<20;i++){
            fscanf(archivo, "%d %d %f\n", &oper[i].egoin, &oper[i].tipo, &oper[i].monto);
            if(oper[i].egoin==2 || oper[i].egoin==1){
                printf("%d %d %f\n", oper[i].egoin, oper[i].tipo, oper[i].monto);
                validos++;
            }
        }
        int gdriver=DETECT, gmode, contador=0;
        initgraph(&gdriver,&gmode,"C:\\BORLANDC\\BGI");
    setbkcolor(8);
    system("color 6B");
    setcolor(6);
    line(20, 5, 300, 170);
    delay(1000);
    setcolor(3);
    rectangle(10, 25, 600, 450);
    delay(1000);
    settextstyle(4,0,14);
    printf("Hola mundo\n\t\tProgramacion Estructurada");
    setcolor(10);
    outtextxy(50,60, "Todo el mundo debería saber");
    delay(1000);
    outtextxy(50,90, "programar porque te enseña a pensar");
    delay(1000);
    outtextxy(50,120, "-Steve Jobs\n");
    delay(1000);
    setcolor(14);
    settextstyle(6,0,14);
    outtextxy(50,170, ":)");
    delay(100000);
        break;
	}
 closegraph();

	system("pause");*/
	}

	fclose(archivo);
}
