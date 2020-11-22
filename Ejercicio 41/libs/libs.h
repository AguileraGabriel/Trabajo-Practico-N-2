#ifndef LIBS_H
#define LIBS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPUESTOS "repuestos.dat"

typedef struct{
            long partNumber;
            long serialNumber;
            char descripcion[40];       
            char ubicacion[100];        
        }repuestos_t;

typedef struct lista_t{
    repuestos_t repuesto;
    struct lista_t *prox;
}lista_t;

//Prototipos

void imprimirLista (lista_t*);
repuestos_t cargaDeDatos (void);
lista_t* lista(void);
void cargaEnArchivo (lista_t**);

#endif /*LIBS_H*/