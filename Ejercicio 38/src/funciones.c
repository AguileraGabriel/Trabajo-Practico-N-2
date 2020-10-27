#include "../libs/libs.h"

/*
    Carga en una cola los datos que se reciven desde el main
*/
void encolar(char dato,cola_t **inicio, cola_t **fin){
    cola_t *aux;
    aux = (cola_t *)malloc(sizeof(cola_t));
    aux->datos = dato;
    aux->prox = NULL;
    
    
    if((*inicio) == NULL){ //cola vacia
        aux->prox = (*inicio);
        (*inicio) = (*fin) = aux;
        (*inicio)->ant = NULL; 
    }
   
    else{//agrego al final
        (*fin)->prox = aux;
        aux->ant = (*fin);
        aux->prox = NULL;
        (*fin) = aux;
    }
}


/*
    Imprimo la cola al derecho
*/
void impresionDeCola( cola_t *inicio){
    printf("\n\t--->Imprimo la Cola<---");
    
    while(inicio != NULL){
        printf("\n%d", inicio->datos);
        inicio = inicio->prox;
    }
}


/*
    Imprimo la cola al revez
*/
void impresionDeColaInvertida( cola_t *fin){
    printf("\n\t--->Imprimo la Cola en sentido inverso<---");

    while(fin != NULL){
        printf("\n%d", fin->datos);
        fin = fin->ant;
    }
}


/*
    Imprimo la cola al derecho con el bit mas significativo cambiado a 1
*/
void impresionDeColaNegativa( cola_t *inicio){
    printf("\n\t--->Imprimo la Cola con bit cambiado<---");
    
    while(inicio != NULL){
        printf("\n%d", (inicio->datos) | (1<<7));
        inicio = inicio->prox;
    }
}


/*
    Imprimo la cola al revez con el bit mas significativo cambiado a 1
*/
void impresionDeColaInvertidaNegativa( cola_t *fin){
    printf("\n\t--->Imprimo la Cola con bit cambiado en sentido inverso<---");

    while(fin != NULL){
        printf("\n%d", (fin->datos) | (1<<7));
        fin = fin->ant;
    }
}