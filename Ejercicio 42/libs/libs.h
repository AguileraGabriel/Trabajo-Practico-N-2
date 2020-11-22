#ifndef LIBS_H
#define LIBS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define REPUESTOS "repuestos.dat"

typedef struct{
            long partNumber;
            long serialNumber;
            char descripcion[40];       
            char ubicacion[100];        
}repuestos_t;


typedef struct cola{
    repuestos_t datos;
    struct cola *prox;
    struct cola *ant;
}cola_t;

//Prototipos
void encolar(repuestos_t ,cola_t **, cola_t **);
void lecturaDeArchivo (cola_t **, cola_t **);
void cargaEnArchivo (cola_t**);


#endif /*LIBS_H*/