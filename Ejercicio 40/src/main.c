#include "../libs/lib40.h"


int main(void){
    //Variables a usar
    int opc = 0;
    long id;
    char palabra[60]= " ";
    carga_t dato;
    pila_t *inicio = NULL, *fin = NULL;

    do{ 
    //Llamado de funciones
    printf ("Ingrese ID a buscar entre 0 y 5:");
    scanf("%ld",&id);
    dato = lecturaDelArchivo(id);
    strcpy(dato.leidos.desc, inversionDePalabra(dato)); //guardo la palabra invertida
    toggleBit(dato.leidos.estado,2); //Pongo el bit 3 en el estado contrario al que tenia
    apilar(dato, &inicio, &fin);
    actualizacionDelArchivo(id, dato);
    printf("\n1) Seguir\t 0) Salir   ");
    scanf("%d", &opc);
    }while(opc);

    return 0;
}