#include "../libs/libs.h"

int main(void){
    
    int opc=1;
    lista_t *in = NULL;
    pila_t *ultimo = NULL;
    plista_t *pIn = NULL;
    extraccionRepuestos_t auxRepuesto;

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

    imprimirPila(ultimo);

    while(ultimo){
        printf("\nORDEN A CONSIDERAR");
        printf ("\nModelo: %s \t Numero de Orden: %ld \t Cliente: %s \t Falla: %s \t  Fecha y Hora: %s - %s", ultimo->dato.modelo, ultimo->dato.numeroDeOrden, ultimo->dato.cliente, ultimo->dato.descripciondeFalla, ultimo->dato.fecha, ultimo->dato.hora);
        printf("\nIngrese la Cantidad: ");
        scanf("%d", &auxRepuesto.cantidad);
        auxRepuesto.repuesto = ultimo->dato;
        listaExtraccion(auxRepuesto, &pIn);
        ultimo = ultimo->siguiente;
    }

    imprimirPLista(pIn);
    
    return 0;
}