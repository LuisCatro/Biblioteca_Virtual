#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int dia;
    int mes;
    int anyo;
} fecha_anadelib;

typedef struct
{
    int mes;
    int anyo;
} fecha_terminolib;

typedef struct{
    FILE *archivo;
}archivos;

typedef struct
{
    char nombre_lib[50];
    char autor[50];
    int anyo_lib;
    char genero[50];
    fecha_terminolib fec_t;
    fecha_anadelib fec_anad;
    int lib_llenos;
    archivos files[15];
} libros;

typedef struct
{
    char nombre_bib[50];
    libros lib[15];
    int bib_lleno;
} bibliotecas;

bibliotecas biblio[10];


void anade_biblio();
void anade_lib();
void consulta();
void buscar_por_lib();
void buscar_por_autor();
void todo_vacio();
void cambiar();

int main()
{
    int opcion;
    char op;
    todo_vacio();
    do
    {
        do
        {
            printf("\nMENU\n");
            printf("=====\n");
            printf("Determine la acci%cn a realizar: \n\n",162);
            printf("(1) Crear una nueva biblioteca.\n");
            printf("(2) A%cadir un nuevo libro a una biblioteca.\n", 164);
            printf("(3) Consultar un libro guardado.\n");
            scanf("%i", &opcion);

            if(opcion<1 || opcion>3)
            {
                printf("Digite una opci%cn listada.\n",162);
                system("PAUSE");
                system("CLS");
            }
        }
        while(opcion<1 || opcion>3);

        switch(opcion)
        {
        case 1:
        {
            anade_biblio();
            break;
        }
        case 2:
        {
            anade_lib();
            break;
        }
        case 3:
        {
            consulta();
            break;
        }
        }
        system("CLS");
        printf("Quieres realizar alguna acci%cn m%cs?[s/n]",162,160);
        fflush(stdin);
        scanf("%c",&op);
    }
    while(op=='s' || op=='S');

    return 0;
}

//FUNCION: anade_biblio.
//OBJETIVO: Anade bibliotecas para insertar libros o imprime mensaje si no queda espacio disponible

void anade_biblio()
{
    int i,escape;
    escape=0;
    for(i=0; i<10 && escape==0; i++)
    {
        if(biblio[i].bib_lleno==0)
        {
            printf("Introduzca un nombre para la biblioteca %d: ", i+1);
            fflush(stdin);
            fgets(biblio[i].nombre_bib,50,stdin);
            cambiar(biblio[i].nombre_bib);
            biblio[i].bib_lleno=1;
            escape=1;
        }
    }

    if(escape==0)
    {
        printf("No puede a%cadirse una nueva biblioteca\n",164);
    }
}

//FUNCION: anade_lib
//OBJETIVO: anade libros a bibliotecas ya existentes y las guarda en un archivo .txt

void anade_lib()
{
    int i, j, escape=0, opcion;
    for(i=0; i<10; i++)
    {
        if(biblio[i].bib_lleno==1)
        {
            printf("[%d] %s\n", i, biblio[i].nombre_bib);
        }
    }
    scanf("%d", &opcion);
    for(i=0; i<15&&escape==0; i++)
    {
        for(j=0;j<15;j++){
            if(biblio[opcion].lib[i].lib_llenos==0)
            {
                biblio[opcion].lib[i].files[j].archivo=fopen("libros.txt","w");
                printf("Introduzca el nombre del libro %d: ",i+1);
                fflush(stdin);
                fgets(biblio[opcion].lib[i].nombre_lib,50,stdin);
                cambiar(biblio[opcion].lib[i].nombre_lib);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "Nombre: %s\n", biblio[opcion].lib[i].nombre_lib);

                printf("Introduzca el nombre del autor del libro %d: ",i+1);
                fflush(stdin);
                fgets(biblio[opcion].lib[i].autor,50,stdin);
                cambiar(biblio[opcion].lib[i].autor);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "Autor: %s\n", biblio[opcion].lib[i].autor);


                printf("Introduzca el a%co del libro %d: ",164, i+1);
                scanf("%d", &biblio[opcion].lib[i].anyo_lib);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "Agno del libro: %i\n", biblio[opcion].lib[i].anyo_lib);


                printf("Introduzca el g%cnero del libro %d: ",130, i+1);
                fflush(stdin);
                fgets(biblio[opcion].lib[i].genero,50,stdin);
                cambiar(biblio[opcion].lib[i].genero);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "Genero: %s\n", biblio[opcion].lib[i].genero);


                printf("Introduzca mes y a%co en que usted termin%c el libro %d: ",164, 162, i+1);
                scanf("%d %d",&biblio[opcion].lib[i].fec_t.mes, &biblio[opcion].lib[i].fec_t.anyo);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "Fecha de termino: %d", biblio[opcion].lib[i].fec_t.mes);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "/%d\n", biblio[opcion].lib[i].fec_t.anyo);

                printf("Introduzca la fecha actual: ");
                scanf("%d %d %d",&biblio[opcion].lib[i].fec_anad.dia, &biblio[opcion].lib[i].fec_anad.mes, &biblio[opcion].lib[i].fec_anad.anyo);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "Fecha de anadido: %d", biblio[opcion].lib[i].fec_anad.dia);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "/%d", biblio[opcion].lib[i].fec_anad.mes);
                fprintf(biblio[opcion].lib[i].files[j].archivo, "/%d", biblio[opcion].lib[i].fec_anad.anyo);

                biblio[opcion].lib[i].lib_llenos=1;
                escape=1;
                fclose(biblio[opcion].lib[i].files[j].archivo);
            }
        }
    }
}

//FUNCION: consulta
//OBJETIVO: Permie consultar los libros ya registrados a traves de su nombre o su autor

void consulta()
{
    int opcion;
    char op;
    do
    {
        do
        {
            printf("Elige cual va a ser tu accion.\n");
            printf("(1) Buscar por libro.\n");
            printf("(2) Bucar por autor.\n");
            scanf("%i",&opcion);
        }
        while( opcion<1 || opcion>2);

        switch(opcion)
        {
        case 1:
        {
            buscar_por_lib();
            break;
        }
        case 2:
        {
            buscar_por_autor();
        }
        }
        printf("Quiere realizar alguno otra consulta [S/N]: ");
        fflush(stdin);
        scanf("%c",&op);
    }
    while (op == 'S' || op == 's');
}

//FUNCION: buscar_por_lib
//OBJETIVO: Permite buscar el libro que se le indique mediante comparacion de strings e imprime e pantalla sus datos

void buscar_por_lib()
{
    char librobuscado[50];
    int i,j,escape,busqueda=1;
    system("CLS");
    printf("Introduce el nombre del libro que desea buscar: ");
    fflush(stdin);
    fgets(librobuscado,50,stdin);
    cambiar(librobuscado);
    for(i=0; i<10; i++)
    {
        if(biblio[i].bib_lleno==1)
        {
            for(j=0; j<15 ; j++)
            {
                if(biblio[i].lib[j].lib_llenos==1)
                {
                    busqueda=strcmp(librobuscado,biblio[i].lib[j].nombre_lib);
                    if(busqueda==0)
                    {
                        printf("Busqueda exitosa. La infomacion referente a este libro es la siguiente: .\n");
                        printf("Biblioteca:  %s.\n",biblio[i].nombre_bib);
                        printf("Nombre:  %s.\n",biblio[i].lib[j].nombre_lib);
                        printf("Autor:  %s.\n",biblio[i].lib[j].autor);
                        printf("A%co: %i.\n",164,biblio[i].lib[j].anyo_lib);
                        printf("G%cnero: %s.\n",130, biblio[i].lib[j].genero);
                        printf("Fecha de termino: %i/%i.\n",biblio[i].lib[j].fec_t.mes, biblio[i].lib[j].fec_t.anyo);
                        printf("Fecha de a%cadido: %i/%i/%i.\n",164,biblio[i].lib[j].fec_anad.dia,biblio[i].lib[j].fec_anad.mes,biblio[i].lib[j].fec_anad.anyo);
                        printf("\n\n");
                        escape=1;
                    }
                }
            }
        }
    }
    if(escape!=1)
    {
        printf("El libro que busca no ha sido registrado.\n");
        system("PAUSE");
    }
}

//FUNCION: buscar_por_autor
//OBJETIVO: Permite buscar los libros mediante el nombre del autor mediante comparacion de strings e imprime sus datos por pantalla

void buscar_por_autor()
{
    char autorbuscado[50];
    int i,j,escape,busqueda=1;
    system("CLS");
    printf("Introduce el nombre del autor que desea buscar: ");
    fflush(stdin);
    fgets(autorbuscado,50,stdin);
    cambiar(autorbuscado);
    for(i=0; i<10; i++)
    {
        if(biblio[i].bib_lleno==1)
        {
            for(j=0; j<15 ; j++)
            {
                if(biblio[i].lib[j].lib_llenos==1)
                {
                    busqueda=strcmp(autorbuscado,biblio[i].lib[j].autor);
                    if(busqueda==0)
                    {
                        printf("Busqueda exitosa. La infomacion referente a este libro es la siguiente: .\n");
                        printf("Biblioteca: %s.\n",biblio[i].nombre_bib);
                        printf("Nombre: %s.\n",biblio[i].lib[j].nombre_lib);
                        printf("Autor: %s.\n",biblio[i].lib[j].autor);
                        printf("A%co: %i.\n",164,biblio[i].lib[j].anyo_lib);
                        printf("G%cnero: %s.\n",130, biblio[i].lib[j].genero);
                        printf("Fecha de termino: %i/%i.\n",biblio[i].lib[j].fec_t.mes, biblio[i].lib[j].fec_t.anyo);
                        printf("Fecha de a%cadido: %i/%i/%i.\n",164,biblio[i].lib[j].fec_anad.dia,biblio[i].lib[j].fec_anad.mes,biblio[i].lib[j].fec_anad.anyo);
                        printf("\n\n");
                        escape=1;
                    }
                }
            }
        }
    }
    if(escape!=1)
    {
        printf("El libro que busca no ha sido registrado.\n");
        system("PAUSE");
    }
}

//FUNCION: cambiar
//PARAMETROS: nombre, strings o 50 caracteres
//OBJETIVO: Recibe los nombres de los libros y bibliotecas y sustituye el caracter \n por \0

void cambiar(char nombre[50])
{
    int L;
    L=strlen(nombre);
    nombre[L-1]='\0';
}

//FUNCION: todo_vacio
//OBJETIVO: Inicializa todas las variables lleno de las bibliotecas y libros a 0(falso)

void todo_vacio()
{
    int i,j;
    for(j=0; j<10; j++)
    {
        biblio[j].bib_lleno=0;
        for(i=0; i<15; i++)
        {
            biblio[j].lib[i].lib_llenos=0;
        }
    }
}

