#include <stdio.h>
#include <stdlib.h>
//EJEMPLO SOBRE COMO CREAR MATRIZ EN MAIN
void main ()
{
	int r, c, *ap;
	printf(“Ingrese numero de renglones\n”);
	scanf(“%d”,&r);
	printf(“Ingrese numero de columnas\n”);
	scanf(“%d”,&c);
	ap=(*int)malloc((r*c)*sizeof(int));
	if (ap)
		printf(“Matriz creada con éxito\n”);
	else
		printf(“ Error. No se pudo reservar memoria\n”);
}
/////////////////////////////////////////////////////////////////////
//EJEMPLO SOBRE COMO CREAR MATRIZ EN FUNCION
Int *creaMatriz (int, int);
void main ()
{
	int ren=3, col=5;
	int *matriz=NULL;
	matriz = creaMatriz( ren, col );
	if (matriz)
		printf(“Matriz Creada\n”);
	else
		printf(“Error. No se pudo reservar memoria\n”);
}//OBSERVAR COMO NO PASA EL APUNTADOR, SINO DEVUELVE UN DATO INT CON LA DIR INI
int *crearMatriz (int ren, int col)//VER *CREAMATRIZ
{
	return ( int * )malloc( col * ren * sizeof( int * ) );
}
///////////////////////////////////////////////////////////////////////
#define MaxCol 10
#define MaxRen 10
//EJEMPLO DE LLENAR MATRIZ CON FUNCIONES
short int llenaMatriz (int *matriz, int ren, int col)
void main ()
{
	int ren = 3, col = 5;
	short int exito, opc;
	int *matriz;
	switch (opc)
	{
	 case 2:
	exito=llenaMatriz( matriz, ren, col);//APUNTADOR SIMPLE
		switch (exito)

 {
		 case -2: printf("Cree antes la matriz\n");//VALIDACIONES
                    		break;
            case -1: printf("Error en parametros\n");
                    		break;
            case 0: printf("Error en parametro\n");
                   		 break;
            case 1: printf("Exito. Matriz llenada por columnas\n");
                   		 break;
	           }

                   break;
	}
}
short int llenaMatriz(int *Matriz, int ren, int col)
{
     if(!Matriz)//VALIDO QUE NO SE HA CREADO
    {
        return -2;
    }
    else
    {
       if((col<2) || (ren<2))//VALIDO RANGO
       {
         return -1;
       }
       else
       {
           if(col>MaxCol || ren>MaxRen)
           {
               return 0;
           }
           else
           {
               if (Matriz)
               {
                   int i,j;
                   int con=1,*apactual;
                   apactual=Matriz;//AP ACTUAL LO APUNTO A DONDE APUNTA MATRIZ
                   for (i=0;i<ren;i++)
                   {
                       for (j=0;j<col;j++)
                       {
                         *(apactual+i*col+j)=con;//LLENADO POR RENGLONES
                        con++;
                       }
                       printf("\n");
                   }
               }
           }
       }
    }
return 1;
}
///////////////////////////////////////////////////////////////////
//EJEMPLO DE EL DESPLIEGUE DE LA MATRIZ
short int imprimeMatriz (int *, int ren, int col);
void main ( )
{
	int ren = 3, col = 5;
	short int éxito, opc;
	int *matriz;
	switch (opc)
	{
	 case 3:
	éxito=imprimeMatriz( matriz, ren, col);
		switch (éxito)//SWITHC DE VALIDACIONES ARROJADAS
	          {
		 case -2: printf("Cree antes la matriz\n");

                    		break;
                    		case -1: printf("Error en parametros\n");
                    		break;
                    		case 0: printf("Error en parametro\n");
                   		 break;
                   		 case 1: printf("Exito. Matriz desplegada\n");
                   		 break;
	           }
                   break;
	}
}
  short int imprimeMatriz(int *Matriz, int ren, int col)//FUNCION QUE DESPLIEGA
{
    if(!Matriz)//VALIDO QUE ESTE CREADA
    {
        return -2;
    }
    else
    {
       if((col<2) || (ren<2))//VALIDO RANGO
       {
         return -1;
       }
       else
       {
           if(col>MaxCol || ren>MaxRen)//VALIDO
           {
               return 0;
           }
           else
           {
               if (Matriz)
               {
                   register int i,j;//DATO REGISTER
                   int n;
                   n=ren*col;
                   for (i=0;i<ren;i++)
                   {
                       for (j=0;j<col;j++)
                       {
                           printf("|%8d|",*(Matriz+i*col)+j);//FORMULA IMPRESIÓN

                       }
                       printf("\n");
                   }
               }
           }
       }
    }
  return 1;
}
////////////////////////////////////////////////////////////////////
//EJEMPLO DE LIBERACIÓN DE MATRIZ
short int liberarMat    ( int * );
void main ( )
{
	int *matriz;
	short int opc, exito;
	switch ( opc )
	{
		case 4:
		éxito = liberaMat ( matriz );
		switch ( éxito)
		{
		   case -1: printf("Antes cree la matriz\n");
               		   break;
                		  case 0: printf("Matriz liberada\n");
		  break;
		}
		  break;
	}

}
   short int liberarMat(int *Matriz)
{
    if (!Matriz)//VALIDO SI EXISTE
    {
        return -1;
    }
    else
    {
        free(Matriz);//LIBERO
        Matrix=NULL;//INICIALIZO
        return 0;
    }
}
