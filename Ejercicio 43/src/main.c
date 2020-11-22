#include "../libs/libs.h"

int main(void){
    int opc=1;
    lista_t *in=NULL;
    pila_t *ultimo=NULL;
    
    while(opc==1){
        lista(cargar(),&in);
        printf("\nDesea continuar? 1)SI     0)NO");
        printf("\nRespuesta: ");
        scanf("%d",&opc);
    }  

    while(in){
        ultimo = apilar(in->dato,&ultimo);
        in = in->prox;
    }

    imprimirPila(ultimo); // Usado para verificar los datos a cargar en el archivo
    cargaEnArchivo(ultimo);    
    
    return 0;
}