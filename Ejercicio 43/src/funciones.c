#include "../libs/libs.h"

repuestos_t cargar(void){
    repuestos_t cargado;
    
    printf("\nNumero de Orden:");
    scanf("%ld",&cargado.numeroDeOrden);
    fflush(stdin);
    printf("Cliente:");
    scanf("%s",&cargado.cliente);
    fflush(stdin);
    printf("Falla:");
    scanf("%s",&cargado.descripciondeFalla);
    fflush(stdin);
    printf("Modelo:");
    scanf("%s",&cargado.modelo);
    fflush(stdin);
    printf("Fecha:");
    scanf("%s",&cargado.fecha);
    fflush(stdin);
    printf("Hora:");
    scanf("%s",&cargado.hora);
    fflush(stdin);

    return cargado;
}


void cargaEnArchivo (pila_t *pila){
    FILE *fp;
    repuestos_t carga;
    

    fp = fopen(REPUESTOS, "ab+");
    if (fp == NULL){
        printf("\n***No se pudo abrir el el archivo, se va a crear***");
        
        fp = fopen(REPUESTOS, "wb+");
        if (fp == NULL){
            printf("\nError al crear archivo");
            return;
        } 
    }
    else{
        while(pila){
            fwrite(&pila->dato,sizeof(repuestos_t),1,fp);
            pila = pila->siguiente;
        }
        fclose (fp);
    }
    return;
}



void lista(repuestos_t dato,struct lista_t **in){
    struct lista_t *pre=NULL, *r=NULL, *aux=NULL; 

    aux=(lista_t*) malloc(sizeof(lista_t));
    if(aux == NULL){
        printf("\n Error");
    }
    else{
        aux->dato=dato;
        aux->prox=NULL;

        if(*in == NULL){
            *in = aux;
        }
        else{
            char auxFyH[20] = "";
            char inFyH[20] = "";
            strcat(auxFyH,aux->dato.fecha);
            strcat(auxFyH,aux->dato.hora);
            strcat(inFyH,(*in)->dato.fecha);
            strcat(inFyH,(*in)->dato.hora);
            
            if(atoi(auxFyH) < atoi(inFyH)){ //inicio lista
                aux->prox=(*in); //el proximo del reservado en memoria sera in. 
                (*in) = aux;
            }
            else
            {
                r = (*in); //puntero en el cual estoy
                pre = (*in); //apunta al anterior al que uso para recorrer.
                
                while ((atoi(auxFyH) >= atoi(inFyH) && r->prox != NULL)){ //hasta que prox sea null o el que agregue sea mayor
                    pre = r; 
                    r = r->prox; 
                }
                if(atoi(auxFyH) >= atoi(inFyH)){ //caso para nodo en la parte central.
                    r->prox = aux;
                }
                else{  //en caso de estar al final.
                    aux->prox = r; 
                    pre->prox = aux; 
                }
            }  
        }		    
        return;
    }
    return;
}



void imprimirPila(pila_t *ultimo){
    pila_t *p= NULL, *aux= NULL;
    printf("\n\n *** Imprimo la Pila ***\n");
    p = ultimo;
    
    while(p){
        aux=p;
        printf ("\nNumero de Orden: %ld \t Cliente: %s \t Falla: %s \t Modelo: %s \t Fecha y Hora: %s - %s",  p->dato.numeroDeOrden, p->dato.cliente, p->dato.descripciondeFalla, p->dato.modelo, p->dato.fecha, p->dato.hora);

        p=p->siguiente;
        free(aux); 
    }
    return;
}



pila_t* apilar(repuestos_t cargado,pila_t **ultimo){
    pila_t *aux = NULL; //inicializo en null.
    aux=(pila_t *) malloc(sizeof(pila_t)); //reservo memoria.
        if(aux == NULL){
        printf("\n Error");
    }
    else{
    aux->dato = cargado;
    

    aux->siguiente = *ultimo; //sig de aux apunta al ahora anteultimo.
    return aux;
    }
    return NULL;
}

