#include "../libs/libs.h"

int main (void){
    //inicio main 44
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
    
    //inicio del 45:
    
    long PN;
    int cantidad, cantidadSolicida;
    cola_t *inicioCola = NULL, *finCola = NULL;
    extraccionRepuestos_t dato;
  

    while(pIn){
        
        printf("\nNumero de Parte del Producto: %d ", pIn->dato.repuesto.modelo);
        printf("\nCantidad del Producto: %d ", pIn->dato.cantidad);
        printf("\nCliente: %d ", pIn->dato.repuesto.cliente);
        
        PN = (long)(pIn->dato.repuesto.modelo);
        cantidadSolicida = pIn->dato.cantidad;

        cantidad = lecturaDeArchivo(PN); //modelo es equivalente a PN
 

        if(cantidadSolicida <= cantidad){
            printf("\nHay stock suficiente");
            bajaFisica(cantidadSolicida, PN);
        }
        else{
            printf("\nNo hay stock suficiente");
            dato = pIn->dato;
            encolar(dato, &inicioCola, &finCola);
            impresionDeCola(inicioCola);
        }
        pIn = pIn->prox; //muevo el puntero que recorre la lista
    }

    cantidad = lecturaDeArchivo(1);


    return 0;
}