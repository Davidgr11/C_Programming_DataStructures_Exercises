#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#define MenuInicio 1
#define MenuFin 5
#define LineaDeInicio 2
//ESTRUCTURAS
/*
Gonzalez Robles David Alejandro
Vania Cadena Aguilar
Ángel López Vudoyra
Alethia Silvana Morán Franco
*/
struct operaciones
{
    float monto;
    int egoin, tipo;
};typedef struct operaciones O;
//////////////////////////////////
struct cuentas
{
    int numcta[5];
    float saldo, cred;
    char tipo[20];
};typedef struct cuentas T;
//////////////////////////////////
struct fecha
{
    char dia[3];
    char mes[3];
    char anio[5];
};typedef struct fecha F;
//////////////////////////////////
struct direcc
{
    char calle[20];
    int num;
    char col[20];
};typedef struct direcc D;
//////////////////////////////////
struct nombres
{
    char np[20];
    char app[20];
    char apm[20];
};typedef struct nombres N;
//////////////////////////////////
struct persona
{
  //Datos generales
    N nombre;
    int edad;
    int edo_civil;
    D direccion;
    F nacimiento;
    char rfcc[11];
    //Datos especificos
    T tarjeta;
    char pass[10];
    O operacion[20];
};typedef struct persona P;
////////////////////////////////////
//FUNCIONES
void llena (P personas[10],int *dir);//funcion que agrega personas de manera manual
void sacarfc(N name,F naci,char rfc[11]);//funcion que saca el RFC de una persona
void inicia(void);//funcion que hace el letrero inicial de BANCO VAAD
int validaUnaMayuscula(char contrasenha[20]);//funciones para validar contraseña
int validaUnaMinuscula(char contrasenha[20]);
int validaNumero(char pass[20]);
int validaConsecutivo(char pass[20]);
int validaPass(char contrasenha[20]);
int imprimeResultado(char pass[20]);
void imprimedatos(P personas[10], int usuario);//funcion que imprime los datos de una persona
int validaingreso(P personas[10], int dir);//funcion que valida que el usuario y contraseña del usuario a ingresar sean correctos
void fijas(P personas [10], int *dir);//funcion que agrega 5 personas con todos sus datos para fines de eficiencia en la exposicion
void llenaop(P personas[10], int usuario, int *dir, int *m);//funcion donde se registran las operaciones:ingresos o egresos
void autollenado(P personas[10], int usuario, int *m);//funcion que llena 11 operaciones diversas para fines de eficiencia en la exposicion
void edocuenta(P personas[10], int usuario, int *m, FILE *archivo);//funcion que imprime el estado de cuenta en pantalla y en un archivo csv para su lectura con el programa de graficos
////////////////////////////////////
int main(void) {
    srand(time(NULL));
    FILE *archivo;
  P personas[10];
  int menu1, menu2, dir=0, usuario, m, op;
  char w=223;
  printf("-------Bienvenido--------\n\n");
  inicia();
  system("color 1f");
  printf("\nELIGE:\t1)Crear cuenta \t2)Ingresar\n");
  scanf("%d",&menu1);
  fijas(personas, &dir);
  do
  {
    if(menu1==1){
    llena(personas, &dir);
    }
    else
    {
        //printf("%d", dir);
        usuario=validaingreso(personas, dir);
        m=0;
        //printf("Hola %s %s %s", personas[usuario].nombre.np, personas[usuario].nombre.app, personas[usuario].nombre.apm);
        do
        {
            system("cls");
            system("color 1f");
            printf("Hola %s %s %s", personas[usuario].nombre.np, personas[usuario].nombre.app, personas[usuario].nombre.apm);
            printf("\nSaldo actual: %.2f\t", personas[usuario].tarjeta.saldo);
            printf("\nCredito a pagar: %.2f", personas[usuario].tarjeta.cred);
            printf("\n---------Seleccione opcion:---------\n");
            printf("\t1. Mostrar mis datos\n");
            printf("\t2. Registrar ingreso o egreso\n");
            printf("\t3. Pagar credito\n");
            printf("\t4. Ver mi estado de cuenta\n");
            printf("\t5. Autollenado de operaciones\n");
            printf("\t6. Salir de mi cuenta\n");
            scanf("%d", &menu2);
            switch(menu2)
            {
                case 1: imprimedatos(personas, usuario);
                        break;
                case 2: llenaop(personas, usuario, &dir, &m);
                        break;
                case 3:
                        if(personas[usuario].tarjeta.cred<=personas[usuario].tarjeta.saldo){
                            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)-(personas[usuario].tarjeta.cred);
                            personas[usuario].tarjeta.cred=0;
                        }
                        else
                        {
                            printf("No tienes lo suficiente para pagar el credito en su total, ¿Deseas usar todo tu saldo para reducir el credito? 1)Si Otro)No\n");
                            scanf("%d", &op);
                            if(op==1){
                             personas[usuario].tarjeta.cred=(personas[usuario].tarjeta.cred)-(personas[usuario].tarjeta.saldo);
                             personas[usuario].tarjeta.saldo=0;}
                        }
                        break;
                case 4: edocuenta(personas, usuario, &m, archivo);
                        break;
                case 5: autollenado(personas, usuario, &m);
                        break;
            }
            system("pause");
        }while(menu2!=6);
    }
  printf("\nELIGE:\t1)Crear cuenta \t2)Ingresar\n3)Salir del banco\n");
  scanf("%d",&menu1);
  }while(dir<10 && menu1!=3);
  return 0;
}
////////////////////////////////////
void llena (P personas[10],int *dir){
    int i, w=223;
    srand(time(NULL));
    char pass[20];
    if (*dir <10)
    {
        system("cls");
        printf("---INGRESA LOS DATOS REQUERIDOS---\n");
        printf("\n\tNombre Propio\n");
        fflush(stdin);
        gets(personas[*dir].nombre.np);
        printf("\tApellido Paterno\n");
        fflush(stdin);
        gets(personas[*dir].nombre.app);
        printf("\tApellido Materno\n");
        fflush(stdin);
        gets(personas[*dir].nombre.apm);
        printf("\tEdad\n");
        scanf("%d",&personas[*dir].edad);
        printf("\tEdo civil\t 1)Solter@ 2)Casad@ 3)Divorciad@ 4)Viud@ 5)Concubinato\n");
        scanf("%d", &personas[*dir].edo_civil);
        system("cls");
        printf("\n\tDIRECCION\nCalle\n");
        fflush(stdin);
        gets(personas[*dir].direccion.calle);
        printf("\tNumero\n ");
        scanf("%d",&personas[*dir].direccion.num);
        printf("\tColonia\n ");
        fflush(stdin);
        gets(personas[*dir].direccion.col);
        printf("\nDia de Nacimiento con dos digitos\n");
        fflush(stdin);
        gets(personas[*dir].nacimiento.dia);
         printf(" Mes de Nacimiento con dos digitos\n");
        fflush(stdin);
        gets(personas[*dir].nacimiento.mes);
          printf("A%co de Nacimiento completo\n ",165);
        fflush(stdin);
        gets(personas[*dir].nacimiento.anio);
        sacarfc(personas[*dir].nombre, personas[*dir].nacimiento, personas[*dir].rfcc);
        system("cls");
        printf("REGISTRO DE CUENTA BANCARIA\n");
        for(i=0;i<5;i++)
        {
            personas[*dir].tarjeta.numcta[i]=rand()%9;
        }
        printf("¿Cual es tu saldo inicial?\n");
        scanf("%f", &personas[*dir].tarjeta.saldo);
        strcpy(personas[*dir].tarjeta.tipo, "VAAD PREMIUM");
        printf("DATOS PARA INGRESAR\n");
        printf("\nIngresa tu password. Recuerda que debe de contar con:\nExactamente 8 caracteres\nAl menos una mayuscula\nAl menos una minuscula\nAl menos un numero\nNo hay 2 caracteres consecutivos (ab, 12)\n");
        do{
        printf("\nEscribe un password: ");
        scanf("%s", &personas[*dir].pass);
        strcpy(pass, personas[*dir].pass);
        imprimeResultado(pass);
        }while(validaPass(pass)!=1);
        system("cls");
        system("color 1a");

        printf("\nIngresa con:\n\tUsuario(#cuenta): ");
        for(i=0;i<5;i++){
            printf("%d", personas[*dir].tarjeta.numcta[i]);
        }
        printf("\n\tContraseña:%s\n", personas[*dir].pass);
        printf("Cuenta creada con exito\n");
        printf ("\t %c\n\t%c%c%c\n\t%c%c%c\n\t%c%c%c\n\t%c%c%c\n\t %c\n\t%c%c%c\n       %c%c%c%c%c\n       %c%c%c%c%c\n       %c%c%c%c%c\n",w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w);
        (*dir)++;
    }
    else
        printf("\n Arreglo lleno");
}
void sacarfc(N nombre,F naci,char rfcc[11]){
    char nom, mat;
    srand(time(NULL));
    nom=nombre.np[0];
    mat=nombre.apm[0];
   strncpy(rfcc,nombre.app,2);
   //strncat(rfcc,nombre.apm,1);
   //strncat(rfcc,nombre.np,1);
   rfcc[2] =mat;
   rfcc[3] =nom;
   rfcc[4] =naci.anio[2];
   rfcc[5] =naci.anio[3];
   rfcc[6] ='\0';
   strcat(rfcc,naci.mes);
   strcat(rfcc,naci.dia);
   strupr(rfcc);
}
void inicia(void){
    char w=223;
    char b[8][21]={' '};
    int i,j;

b[0][0]=w,b[0][1]=w,b[0][5]=w,b[0][8]=w,b[0][11]=w,b[0][14]=w,b[0][15]=w,b[0][18]=w,b[0][19]=w;
b[1][0]=w,b[1][2]=w,b[1][4]=w,b[1][6]=w,b[1][8]=w,b[1][9]=w,b[1][11]=w,b[1][13]=w,b[1][17]=w,b[1][20]=w;
b[2][0]=w,b[2][2]=w,b[2][4]=w,b[2][6]=w,b[2][8]=w,b[2][9]=w,b[2][11]=w,b[2][13]=w,b[2][17]=w,b[2][20]=w;
b[3][0]=w,b[3][1]=w,b[3][4]=w,b[1][5]=w,b[3][6]=w,b[3][8]=w,b[3][9]=w,b[3][11]=w,b[3][13]=w,b[3][17]=w,b[3][20]=w;
b[4][0]=w,b[4][2]=w,b[4][4]=w,b[4][5]=w,b[4][6]=w,b[4][8]=w,b[4][10]=w,b[4][11]=w,b[4][13]=w,b[4][17]=w,b[4][20]=w;
b[5][0]=w,b[5][2]=w,b[5][4]=w,b[5][6]=w,b[5][8]=w,b[5][10]=w,b[5][11]=w,b[5][13]=w,b[5][17]=w,b[5][20]=w;
b[6][0]=w,b[6][2]=w,b[6][4]=w,b[6][6]=w,b[6][8]=w,b[6][11]=w,b[6][13]=w,b[6][17]=w,b[6][20]=w;
b[7][0]=w,b[7][1]=w,b[7][4]=w,b[7][6]=w,b[7][8]=w,b[7][11]=w,b[7][14]=w,b[7][15]=w,b[7][18]=w,b[7][19]=w;

for(i=0;i<8;i++)
{
    for(j=0;j<21;j++)
    {
        printf("%c ",b[i][j]);
    }
    printf("\n");
}
printf("\n\n");
    char m1[7][17]={ };
    int r,c;
m1[0][0]=w,m1[0][4]=w,m1[0][7]=w,m1[0][11]=w,m1[0][14]=w,m1[0][15]=w;
m1[1][0]=w,m1[1][4]=w,m1[1][6]=w,m1[1][8]=w,m1[1][10]=w,m1[1][12]=w,m1[1][14]=w,m1[1][16]=w;
m1[2][1]=w,m1[2][3]=w,m1[2][6]=w,m1[2][8]=w,m1[2][10]=w,m1[2][12]=w,m1[2][14]=w,m1[2][16]=w;
m1[3][1]=w,m1[3][3]=w,m1[3][6]=w,m1[1][7]=w,m1[3][8]=w,m1[3][10]=w,m1[1][11]=w,m1[3][12]=w,m1[3][14]=w,m1[3][16]=w;
m1[4][1]=w,m1[4][3]=w,m1[4][6]=w,m1[4][7]=w,m1[4][8]=w,m1[4][10]=w,m1[4][11]=w,m1[4][12]=w,m1[4][14]=w,m1[4][16]=w;
m1[5][1]=w,m1[5][3]=w,m1[5][6]=w,m1[4][7]=w,m1[5][8]=w,m1[5][10]=w,m1[5][12]=w,m1[5][14]=w,m1[5][16]=w;
m1[6][2]=w,m1[6][6]=w,m1[6][8]=w,m1[6][10]=w,m1[6][12]=w,m1[6][14]=w,m1[6][15]=w;
 //printf("\n                                             ");
for(r=0;r<7;r++)
{
    for(c=0;c<17;c++)
    {
        printf("%c ",m1[r][c]);
    }
   printf("\n");
}
}
void imprimedatos(P personas[10], int usuario){
    int i;
      printf("Hola %s %s %s\n",personas[usuario].nombre.np,personas[usuario].nombre.app,personas[usuario].nombre.apm);
        printf("Edad: %d\n", personas[usuario].edad);
        printf("Estado civil:  ",personas[usuario].edo_civil);
        switch(personas[usuario].edo_civil)
        {
            case 1: printf("Solter@\n");
                    break;
            case 2: printf("Casad@\n");
                    break;
            case 3: printf("Divorciad@\n");
                    break;
            case 4: printf("Viud@\n");
                    break;
            case 5: printf("Concubinat@\n");
                    break;
        }
        printf("Direccion: %s no.%d Col. %s\n", personas[usuario].direccion.calle, personas[usuario].direccion.num,personas[usuario].direccion.col);
        printf("Fecha de nacimiento: %s de %s del %s\n",personas[usuario].nacimiento.dia,personas[usuario].nacimiento.mes,personas[usuario].nacimiento.anio);
        printf("CURP: %s\n", personas[usuario].rfcc);
        printf("Datos bancarios\n#de cuenta: ");
        for(i=0;i<5;i++){
        printf("%d", personas[usuario].tarjeta.numcta[i]);
        }
        printf("\nSaldo actual: %.2f", personas[usuario].tarjeta.saldo);
        printf("\nTipo: %s\n", personas[usuario].tarjeta.tipo);
}
int validaUnaMayuscula(char contrasenha[20]){
    int i;
    for(i=0; i<8; i++){
        if(isupper(contrasenha[i]) > 0) {
            return 1;
        }
    }
    return 0;
}
int validaUnaMinuscula(char contrasenha[20]){
    int i;
    for(i=0; i<8; i++){//0 1 2 3 4 5 6 7
        if(islower(contrasenha[i]) > 0) {
            return 1;
        }
    }
    return 0;
}
int validaNumero(char pass[20]){
    int i;
    for(i=0; i<8; i++){//0 1 2 3 4 5 6 7
        if(pass[i] >= '0' && pass[i]<='9'){
            return 1;
        }
    }
    return 0;
}
int validaConsecutivo(char pass[20]){
    // mmP12345
    int i;
    for(i=0; i<8-1; i++){//0 1 2 3 4 5 6 7
        if(pass[i] - pass[i+1] == -1){// A B --> 65 66 ==-1
        //if(pass[i]+1 == pass[i+1]){
        //if(pass[i+1] - pass[i] == 1){
            return 0;
        }
    }
    return 1;
}
int validaPass(char contrasenha[20]){
    if(strlen(contrasenha) !=8){//Exactamente 8 caracteres
        return 0;
    }
    if(validaUnaMayuscula(contrasenha) == 0){//no hay mayusculas
        return 0;
    }
    if(validaUnaMinuscula(contrasenha) == 0){//no hay minusculas
        return 0;
    }
    if(validaNumero(contrasenha) == 0){//no hay numeros
        return 0;
    }
    if(validaConsecutivo(contrasenha) == 0){//hay 2 consecutivos
        return 0;
    }
    return 1;
}
int imprimeResultado(char pass[20]){

    if(validaPass(pass) == 1){
        printf("\nTu password es seguro y valido");
    }else{
        printf("\nTu password es inseguro y no es valido");
    }
    return validaPass(pass);
}
int validaingreso(P personas[10], int dir){
    int v1=0, v2=0, dir2, num1, band, usuari, aux;
    char pass[10];
    do
    {
        v1=0;
        v2=0;
        band=0;
        printf("Dame tu usuario\n");
        scanf("%d", &num1);
        for(dir2=0;dir2<dir && band==0;dir2++){
            aux=0;
            aux=((personas[dir2].tarjeta.numcta[0])*(10000))+((personas[dir2].tarjeta.numcta[1])*(1000))+((personas[dir2].tarjeta.numcta[2])*(100))+((personas[dir2].tarjeta.numcta[3])*(10))+((personas[dir2].tarjeta.numcta[4])*(1));
            if(num1!=aux)
            {
                v1++;
            }
            else{
                printf("Usuario correcto\tDame tu contrase%ca\n", 164);
                scanf("%s", &pass);
                if(strcmp(personas[dir2].pass, pass)==0){
                    v2++;
                    band=1;
                }
                else
                    printf("La contraseña es incorrecta\n");
                }
        }
    if(v1==dir)
    {
        printf("Usuario incorrecto\n");
    }
  }while(v2==0);
  usuari=dir2-1;
  return usuari;
}
void fijas(P personas[10], int *dir){
        strcpy(personas[*dir].nombre.np, "Andres");
        strcpy(personas[*dir].nombre.app, "Hernandez");
        strcpy(personas[*dir].nombre.apm, "Sada");
        personas[*dir].edad=24;
        personas[*dir].edo_civil=1;
        strcpy(personas[*dir].direccion.calle,"Bolivar");
        personas[*dir].direccion.num=172;
        strcpy(personas[*dir].direccion.col,"Pedregal");
        strcpy(personas[*dir].nacimiento.dia,"26");
        strcpy(personas[*dir].nacimiento.mes,"11");
        strcpy(personas[*dir].nacimiento.anio,"1997");
        sacarfc(personas[*dir].nombre, personas[*dir].nacimiento, personas[*dir].rfcc);
        personas[*dir].tarjeta.saldo=1000;
        strcpy(personas[*dir].tarjeta.tipo, "VAAD PREMIUM");
        strcpy(personas[*dir].pass,"L7jhht6m");
        personas[*dir].tarjeta.numcta[0]=9;
        personas[*dir].tarjeta.numcta[1]=6;
        personas[*dir].tarjeta.numcta[2]=0;
        personas[*dir].tarjeta.numcta[3]=2;
        personas[*dir].tarjeta.numcta[4]=4;
        (*dir)++;
        //2da persona
        strcpy(personas[*dir].nombre.np, "Ricardo");
        strcpy(personas[*dir].nombre.app, "Gutierrez");
        strcpy(personas[*dir].nombre.apm, "Espinal");
        personas[*dir].edad=29;
        personas[*dir].edo_civil=2;
        strcpy(personas[*dir].direccion.calle,"Ahuehuete");
        personas[*dir].direccion.num=45;
        strcpy(personas[*dir].direccion.col,"Bosque esmeralda");
        strcpy(personas[*dir].nacimiento.dia,"9");
        strcpy(personas[*dir].nacimiento.mes,"12");
        strcpy(personas[*dir].nacimiento.anio,"1991");
        sacarfc(personas[*dir].nombre, personas[*dir].nacimiento, personas[*dir].rfcc);
        personas[*dir].tarjeta.saldo=200;
        strcpy(personas[*dir].tarjeta.tipo, "VAAD PREMIUM");
        strcpy(personas[*dir].pass,"P8k02Pn4");
        personas[*dir].tarjeta.numcta[0]=0;
        personas[*dir].tarjeta.numcta[1]=5;
        personas[*dir].tarjeta.numcta[2]=7;
        personas[*dir].tarjeta.numcta[3]=9;
        personas[*dir].tarjeta.numcta[4]=3;
        (*dir)++;
        //3ra persona
        strcpy(personas[*dir].nombre.np, "Paulo");
        strcpy(personas[*dir].nombre.app, "Salcedo");
        strcpy(personas[*dir].nombre.apm, "Ramirez");
        personas[*dir].edad=19;
        personas[*dir].edo_civil=3;
        strcpy(personas[*dir].direccion.calle,"Gaviotas");
        personas[*dir].direccion.num=93;
        strcpy(personas[*dir].direccion.col,"GAM");
        strcpy(personas[*dir].nacimiento.dia,"02");
        strcpy(personas[*dir].nacimiento.mes,"01");
        strcpy(personas[*dir].nacimiento.anio,"2002");
        sacarfc(personas[*dir].nombre, personas[*dir].nacimiento, personas[*dir].rfcc);
        personas[*dir].tarjeta.saldo=5000;
        strcpy(personas[*dir].tarjeta.tipo, "VAAD PREMIUM");
        strcpy(personas[*dir].pass,"V8m2hlp1");
        personas[*dir].tarjeta.numcta[0]=9;
        personas[*dir].tarjeta.numcta[1]=3;
        personas[*dir].tarjeta.numcta[2]=1;
        personas[*dir].tarjeta.numcta[3]=6;
        personas[*dir].tarjeta.numcta[4]=2;
        (*dir)++;
        //4ta persona
        strcpy(personas[*dir].nombre.np, "Carlos");
        strcpy(personas[*dir].nombre.app, "Servin");
        strcpy(personas[*dir].nombre.apm, "Blanco");
        personas[*dir].edad=59;
        personas[*dir].edo_civil=4;
        strcpy(personas[*dir].direccion.calle,"Piedrin");
        personas[*dir].direccion.num=473;
        strcpy(personas[*dir].direccion.col,"La Herradura");
        strcpy(personas[*dir].nacimiento.dia,"17");
        strcpy(personas[*dir].nacimiento.mes,"06");
        strcpy(personas[*dir].nacimiento.anio,"1962");
        sacarfc(personas[*dir].nombre, personas[*dir].nacimiento, personas[*dir].rfcc);
        personas[*dir].tarjeta.saldo=1500;
        strcpy(personas[*dir].tarjeta.tipo, "VAAD PREMIUM");
        strcpy(personas[*dir].pass,"Ouy72mp0");
        personas[*dir].tarjeta.numcta[0]=7;
        personas[*dir].tarjeta.numcta[1]=3;
        personas[*dir].tarjeta.numcta[2]=5;
        personas[*dir].tarjeta.numcta[3]=4;
        personas[*dir].tarjeta.numcta[4]=1;
        (*dir)++;
        //5ta persona
        strcpy(personas[*dir].nombre.np, "Roberto");
        strcpy(personas[*dir].nombre.app, "Romero");
        strcpy(personas[*dir].nombre.apm, "Marin");
        personas[*dir].edad=18;
        personas[*dir].edo_civil=5;
        strcpy(personas[*dir].direccion.calle,"Portal");
        personas[*dir].direccion.num=91;
        strcpy(personas[*dir].direccion.col,"Del Valle");
        strcpy(personas[*dir].nacimiento.dia,"23");
        strcpy(personas[*dir].nacimiento.mes,"08");
        strcpy(personas[*dir].nacimiento.anio,"2003");
        sacarfc(personas[*dir].nombre, personas[*dir].nacimiento, personas[*dir].rfcc);
        personas[*dir].tarjeta.saldo=10000;
        strcpy(personas[*dir].tarjeta.tipo, "VAAD PREMIUM");
        strcpy(personas[*dir].pass,"7jY8mlo2");
        personas[*dir].tarjeta.numcta[0]=3;
        personas[*dir].tarjeta.numcta[1]=7;
        personas[*dir].tarjeta.numcta[2]=2;
        personas[*dir].tarjeta.numcta[3]=4;
        personas[*dir].tarjeta.numcta[4]=0;
        (*dir)++;
}
void llenaop(P personas[10], int usuario, int *dir, int *m){
  int aux, aux2, i,band, valida;
  printf("Selecciona\n 1)ingreso  2)Egreso\n");
  scanf("%d", &personas[usuario].operacion[*m].egoin);
  switch(personas[usuario].operacion[*m].egoin)

  {
    case 1: printf("Selecciona el tipo de ingreso\n1)Laboral(sueldo,honorario,bono)\n2)Ventas\n3)Servicios\n4)Otros\n");
            scanf("%d", &personas[usuario].operacion[*m].tipo);
            printf("Monto a ingresar\n");
            scanf("%f", &personas[usuario].operacion[*m].monto);
            //printf("%f", personas[usuario].operacion[*m].monto);
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            break;
    case 2: printf("Eliga alguna opcion:\n1)Retirar\n2)transferir a otra cuenta\n3)Gastos en general o por definir\n");
           scanf("%d",&personas[usuario].operacion[*m].tipo);
           switch(personas[usuario].operacion[*m].tipo)
           {
            case 1:
              printf("Cuanto desea retirar?\n");
              scanf("%f", &personas[usuario].operacion[*m].monto);
               //printf("%f", personas[usuario].operacion[*m].monto);
              if(personas[usuario].tarjeta.saldo<personas[usuario].operacion[*m].monto)
              {
                printf("Tu cuenta no cuenta con saldo suficiente\n¿Deseas agregar el monto faltante de tu cuenta de credito? 1)Si otro)No\n");
                scanf("%d", &aux);
                if(aux==1)
                {
                  personas[usuario].tarjeta.cred=(personas[usuario].operacion[*m].monto)-(personas[usuario].tarjeta.saldo);
                  personas[usuario].tarjeta.saldo=0;
                  (*m)++;
                }
              }
              else{
                personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)-(personas[usuario].operacion[*m].monto);
                (*m)++;
              }
            break;
            case 2:
              do{
               band=0;
               printf("Inserte el numero de cuenta\n");
               scanf("%d",&aux);
               for(i=0;i<*dir;i++)
               {
                valida=0;
                valida=((personas[i].tarjeta.numcta[0])*(10000))+((personas[i].tarjeta.numcta[1])*(1000))+((personas[i].tarjeta.numcta[2])*(100))+((personas[i].tarjeta.numcta[3])*(10))+((personas[i].tarjeta.numcta[4])*(1));
               if(valida==aux)
                {
                   band=1;
                   aux2=i;
                }
               }
              if(band!=1)
              {
                printf("La cuenta no existe\n");
              }
              }while(band!=1);
              do
              {
                band=0;
              printf("Monto de transferencia\n");
              scanf("%f",&personas[usuario].operacion[*m].monto);
               //printf("%f", personas[usuario].operacion[*m].monto);
              if(personas[usuario].tarjeta.saldo<personas[usuario].operacion[*m].monto)
              {
                band=1;
                printf("Ingresa un monto menor o igual a: %f\n", personas[usuario].tarjeta.saldo);
              }
            }while(band==1);
              personas[aux2].tarjeta.saldo=(personas[aux2].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
              personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)-(personas[usuario].operacion[*m].monto);
             (*m)++;
             break;
            case 3: printf("Dame el monto\n");
              scanf("%f", &personas[usuario].operacion[*m].monto);
               //printf("%f", personas[usuario].operacion[*m].monto);
              if(personas[usuario].tarjeta.saldo<personas[usuario].operacion[*m].monto)
              {
                printf("Tu cuenta no cuenta con saldo suficiente\n¿Deseas agregar el monto faltante de tu cuenta de credito? 1)Si otro)No\n");
                scanf("%d", &aux);
                if(aux==1)
                {
                  personas[usuario].tarjeta.cred=(personas[usuario].operacion[*m].monto)-(personas[usuario].tarjeta.saldo);
                  personas[usuario].tarjeta.saldo=0;
                  (*m)++;
                }
              }
              else{
                personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)-(personas[usuario].operacion[*m].monto);
                (*m)++;
              }
                break;
           }
  }
}
void edocuenta(P personas[10], int usuario, int *m, FILE *archivo){
    int i;
    float total;
    archivo=fopen("cuenta.csv", "w+");
    if(archivo==NULL){
        printf("Error al abrir el archivo\n");
    }
    else
    {
        printf("----------------------------------------------------------------------\n");
        printf("                           Estado de cuenta\n");
        printf("----------------------------------------------------------------------\n");
        printf("INGRESO\n");
        printf("----------------------------------------------------------------------\n");
        for(i=0;i<(*m);i++){
            if(personas[usuario].operacion[i].egoin==1){
                switch(personas[usuario].operacion[i].tipo)
                {
                    case 1: printf("Laboral\t");
                            break;
                    case 2: printf("Ventas\t");
                      break;
                    case 3: printf("Servicios\t");
                    break;
                    case 4: printf("Otros\t");
                    break;
                }
                printf("%f\n", personas[usuario].operacion[i].monto);
                fprintf(archivo, "%d %d %f\n", personas[usuario].operacion[i].egoin, personas[usuario].operacion[i].tipo, personas[usuario].operacion[i].monto);
            }
        }
        printf("----------------------------------------------------------------------\n");
        printf("EGRESO\n");
        printf("----------------------------------------------------------------------\n");
        for(i=0;i<*m;i++){
            if(personas[usuario].operacion[i].egoin==2){
                switch(personas[usuario].operacion[i].tipo)
                {
                    case 1: printf("Retiro\t");
                            break;
                    case 2: printf("Transferencia\t");
                      break;
                    case 3: printf("Gasto en general\t");
                    break;
                }
                printf("%f\n", personas[usuario].operacion[i].monto);
                fprintf(archivo, "%d %d %f\n", personas[usuario].operacion[i].egoin, personas[usuario].operacion[i].tipo, personas[usuario].operacion[i].monto);
            }
        }
        printf("\nSaldo actual: %.2f\t", personas[usuario].tarjeta.saldo);
            printf("\nCredito a pagar: %.2f", personas[usuario].tarjeta.cred);
            total=(personas[usuario].tarjeta.saldo)-(personas[usuario].tarjeta.cred);
            printf("\nTotal (saldo-credito): %.2f\t", total);
        if(total<0){
            printf("\nTienes saldo a pagar\n");
        }
        else{
            printf("\nTienes saldo a favor\n");
        }
    }
    fclose(archivo);
}
void autollenado(P personas[10], int usuario, int *m){
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=1;
            personas[usuario].operacion[*m].monto=5800;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=1;
            personas[usuario].operacion[*m].monto=600;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=1;
            personas[usuario].operacion[*m].monto=1250;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            ////2///
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=2;
            personas[usuario].operacion[*m].monto=2800;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=2;
            personas[usuario].operacion[*m].monto=1500;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            ////3////
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=3;
            personas[usuario].operacion[*m].monto=450;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            //4
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=4;
            personas[usuario].operacion[*m].monto=930;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            personas[usuario].operacion[*m].egoin=1;
            personas[usuario].operacion[*m].tipo=4;
            personas[usuario].operacion[*m].monto=1070;
            personas[usuario].tarjeta.saldo=(personas[usuario].tarjeta.saldo)+(personas[usuario].operacion[*m].monto);
            (*m)++;
            ////Egreso///
                personas[usuario].operacion[*m].egoin=2;
                personas[usuario].operacion[*m].tipo=3;
                personas[usuario].operacion[*m].monto=600;
                (personas[usuario].operacion[*m].monto)-(personas[usuario].tarjeta.saldo);
                (*m)++;
                personas[usuario].operacion[*m].egoin=2;
                personas[usuario].operacion[*m].tipo=3;
                personas[usuario].operacion[*m].monto=850;
                (personas[usuario].operacion[*m].monto)-(personas[usuario].tarjeta.saldo);
                (*m)++;
                personas[usuario].operacion[*m].egoin=2;
                personas[usuario].operacion[*m].tipo=3;
                personas[usuario].operacion[*m].monto=700;
                (personas[usuario].operacion[*m].monto)-(personas[usuario].tarjeta.saldo);
                (*m)++;
}
