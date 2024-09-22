#include <stdio.h>
#include <graphics.h>
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
	int i;;
	float valida=0, valida2=0, ti1=0, ti2=0, ti3=0, ti4=0, te1=0, te2=0, te3=0;
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
                switch(oper[i].egoin)
                {
                    case 1: valida++;
                            switch(oper[i].tipo)
                            {
                                case 1: ti1++;
                                        break;
                                case 2: ti2++;
                                        break;
                                case 3: ti3++;
                                        break;
                                case 4: ti4++;
                                        break;
                            }
                            break;
                    case 2: valida2++;
                            switch(oper[i].tipo)
                            {
                                case 1: te1++;
                                        break;
                                case 2: te2++;
                                        break;
                                case 3: te3++;
                                        break;
                            }
                            break;
                }
            }
        }
        ti1=(ti1*100)/valida;
        ti2=(ti2*100)/valida;
        ti3=(ti3*100)/valida;
        ti4=(ti4*100)/valida;

        te1=(te1*100)/valida2;
        te2=(te2*100)/valida2;
        te3=(te3*100)/valida2;
        ti1=(ti1*600)/100;
        ti2=(ti2*600)/100;
        ti3=(ti3*600)/100;
        ti4=(ti4*600)/100;
        te1=(te1*600)/100;
        te2=(te2*600)/100;
        te3=(te3*600)/100;
        printf("%f %f %f %f %f %f %f %f %f", ti1, ti2, ti3, ti4, te1, te2, te3, valida, valida2);
        int gdriver=DETECT, gmode, contador=0;
        initgraph(&gdriver,&gmode,"C:\\BORLANDC\\BGI");
        setcolor(12);
        settextstyle(4,0,1);
        outtextxy(10,10, "INGRESOS");
        delay(1000);
        bar(10,30, 610, 40);
        delay(1000);
        setcolor(9);
        outtextxy(10,50, "Laborales");
        delay(1000);
        bar(10,70, 10+ti1, 80);
        delay(1000);
        outtextxy(10,90, "Ventas");
        delay(1000);
        bar(10,110, 10+ti2, 120);
        delay(1000);
        outtextxy(10,130, "Servicios");
        delay(1000);
        bar(10,150, 10+ti3, 160);
        delay(1000);
        outtextxy(10,170, "Otros");
        delay(1000);
        bar(10,190, 10+ti4, 200);
        delay(1000);

        setcolor(12);
        settextstyle(4,0,1);
        outtextxy(10,210, "EGRESOS");
        delay(1000);
        bar(10,230, 610, 240);
        delay(1000);
        setcolor(9);
        outtextxy(10,250, "Retiros");
        delay(1000);
        bar(10,270, 10+te1, 280);
        delay(1000);
        outtextxy(10,290, "Transferencias");
        delay(1000);
        bar(10,310, 10+te2, 320);
        delay(1000);
        outtextxy(10,330, "Gastos en general");
        delay(1000);
        bar(10,350, 10+te3, 360);
        delay(1000);
    delay(100000);
	}
 closegraph();

	system("pause");

	fclose(archivo);
}
