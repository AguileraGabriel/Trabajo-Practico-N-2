#include "../libs/libs.h"


repuestos_t cargaDeDatos (void){
    repuestos_t repuesto;
    long partNumber;
    long serialNumber;
    char descripcion[40];       
    char ubicacion[100];

    printf("\nIngrese Numero de parte:");
    fflush(stdin);
    scanf("%ld", &repuesto.partNumber);
    printf("\nIngrese Numero de serie:");
    fflush(stdin);
    scanf("%ld", &repuesto.serialNumber);
    printf("\nIngrese Descripcion:");
    fflush(stdin);
    gets(repuesto.descripcion);
    printf("\nIngrese Ubicacion:");
    fflush(stdin);
    gets(repuesto.ubicacion);

    return repuesto;
}


lista_t* lista(void){
    struct lista_t *pre=NULL, *r=NULL, *aux=NULL, *in=NULL; 
    struct lista_t registro; 
    repuestos_t repuestos;
    int opc = 1;
 
        while(opc){ 
            repuestos = cargaDeDatos();
            aux=(lista_t*) malloc(sizeof(lista_t));
            aux->repuesto = repuestos;
            aux->prox = NULL;

            if(in == NULL){
                in = aux;
            }
            else{
                if(0 > strcmp(aux->repuesto.descripcion, in->repuesto.descripcion)){ //inicio lista
                    aux->prox=in; //el proximo del reserbado en memoria sera in. 
                    in = aux;
                }
                else
                {
                    r = in; //puntero en el cual estoy
                    pre = in; //apunta al anterior al que uso para recorrer.
                    
                    while (0 <= strcmp(aux->repuesto.descripcion, r->repuesto.descripcion) && r->prox != NULL){ //hasta que prox sea null o el que agregue sea mayor
                        pre = r; 
                        r = r->prox; 
                    }
                    if(0 <= strcmp(aux->repuesto.descripcion, r->repuesto.descripcion)){ //caso para nodo en la parte central.
                        r->prox = aux;
                    }
                    else{  //en caso de estar al final.
                        aux->prox = r; 
                        pre->prox = aux; 
                    }
                }  
            }
        imprimirLista(in);
        printf("\n Desea continuar? 1)SI 0)NO");
        printf("\n Respuesta: ");       
        scanf("%d",&opc);    		
        }

    return in;
}



void imprimirLista (lista_t* in){
    printf("\n***Impresion de la lista***");
    while(in != NULL){
        printf("\nNumero de Parte: %ld\tNumero de Serie:%ld\tDescripcion:%s\t Ubicacion:%s",in->repuesto.partNumber,in->repuesto.serialNumber,in->repuesto.descripcion,in->repuesto.ubicacion);
        in = in->prox;
    }
}


void cargaEnArchivo (lista_t** in){
    FILE *fp;
    lista_t *b = NULL;
    fp = fopen(REPUESTOS, "wb+");
    if(fp==NULL){
        printf("\n***No se pudo abrir el archivo %s***", REPUESTOS);
    }
    else{
        while (*in != NULL){
            fwrite(&(*in)->repuesto, sizeof(repuestos_t),1, fp);

            //Recorro y libero memoria
            b = (&in);
            *in = (*in)->prox;
            free(b);
        }
        fclose(fp);
    }
}