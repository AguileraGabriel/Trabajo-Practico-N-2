#include "../libs/libs.h"

int main(void) { 
    //Variables a usar
    struct d dato;
    int posicion, opc;
    long clave;
    pila_t *pila = NULL;
    
    //Inicio de funciones y preograma
    crear_fichero();
    do{
    printf("\nClave a buscar:");
    scanf("%ld",&clave);
    leer_fichero(clave, &posicion, &dato);
    pila = ejercicio(clave, posicion, dato, pila);
    printf("\n 1) Continuar  0) Salir:  ");
    scanf("%d",&opc);
    }while(opc!=0);

    while(pila!=NULL){
        impresionOrdenado(pila->dato.posicion);
        pila = pila->prox;
    }
    
    return 0;
}