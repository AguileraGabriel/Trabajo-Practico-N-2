#include "../libs/libs.h"

/*
    Leo los datos que ingresa el usuario
*/
datos_t cargaDeDatos(){
    datos_t datos;
    
    printf("Ingrese Descripcion:");
    fflush(stdin);
    gets(datos.desc);
    fflush(stdin);
    printf("Ingrese valor de potencia:");
    scanf("%d", &datos.potencia);
    fflush(stdin);
    datos.estado = ((int)datos.desc[0])*datos.potencia;

    return datos;
}


/*
   Se apilan los datos cargados por el usuario
*/
void apilar (struct lista_t **in){
    struct lista_t *ant, *r, *nuevo = NULL;
    datos_t misDatos;
    int opc = 1;

    while(opc==1){
        misDatos = cargaDeDatos();

        nuevo=(lista_t*)malloc(sizeof(struct lista_t));
        nuevo->dato = misDatos;
        nuevo->prox=NULL;

        if((*in) == NULL){
            (*in) = nuevo;
        }
        else{
            if(misDatos.potencia > (*in)->dato.potencia){ //si cargo al inicio de la lista
                nuevo->prox=(*in);
                (*in) = nuevo;
            }
            else
            {
                r = (*in); //puntero de recorrido.
                ant = (*in); //puntero de anterior al de recorrido.
                
                while (misDatos.potencia <= r->dato.potencia && r->prox != NULL){ //mientras el dato ingresado sea mayor al objeto evaluedo y mientras sea distinto a fin de lista.
                    //en esta parte recorro...
                    ant = r; //ant conserva pos de r
                    r = r->prox; //r adopta el valor del siguiente
                }
                if(misDatos.potencia <= r->dato.potencia){ //si el dato esta en el medio de la lista
                    r->prox = nuevo;
                }
                else{  //Si cargo al final de la lista
                    nuevo->prox = r; // llegado a este punto r = NULL.
                    ant->prox = nuevo; //el anterior a fin de lista es nuetro valor ingresado.
                }
            }  
        }
    printf("\nDesea continuar?:1)SI \t 0)NO\t Respuesta:");
    scanf("%d",&opc);
    fflush(stdin);
    }
}


/*
    Imprimo mi lista ya ordenada
*/
void impresionDeLista (struct lista_t *r){
    printf("---> Lista completa <---\n");
    while(r != NULL){
        printf("Potencia:%i \tEstado:%d\t Descripcion:%s \n",r->dato.potencia, r->dato.estado, r->dato.desc);
        r = r->prox;
    }
}


/*
    Cargo la lista al archivo y libero la memoria 
*/
void cargaYLiberacionDeMemoria (struct lista_t **r){
    FILE *fp;
    carga_t input;
    struct lista_t *b;
    int i=0;

    fp = fopen ("potencia.dat", "wb+"); 
    if (fp == NULL) 
    { 
        fprintf(stderr, "\nError al abrir archivo\n"); 
        exit (1);
    }

	while((*r)){
		fseek(fp,(-1L)*(long)sizeof(struct lista_t),SEEK_END);
		fread(&input,sizeof(struct lista_t),1,fp);
		fseek(fp,0L,SEEK_END); //va a final de archivo
        input.leidos = (*r)->dato;
        input.id = i++;
        input.estado = 'A';
		fwrite(&input,sizeof(carga_t),1,fp);
		b = (*r);
		(*r) = (*r)->prox;
		free(b);
	}
	fclose(fp);
}


/*
    Abro y leo el archivo nuevo
*/
void apreturaDeArchivo (){
    FILE *fp;
    carga_t datosleidos;

    printf("\n\n---> Leo del nuevo archivo <---\n\n");
	fp = fopen("potencia.dat", "rb+");
	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n","potencia.dat");
	}
	fseek(fp, (0L)*(sizeof(carga_t)), SEEK_SET);
	fread(&datosleidos,sizeof(carga_t),1,fp);
		while(!feof(fp)){
			printf ("ID: %d\t Desc: %s\t Potencia: %d\t Estado: %d \t Baja/Alta: %c\n",  datosleidos.id, datosleidos.leidos.desc ,datosleidos.leidos.potencia, datosleidos.leidos.estado, datosleidos.estado);
			fread(&datosleidos,sizeof(carga_t),1,fp);
		}
	fclose(fp);
}
