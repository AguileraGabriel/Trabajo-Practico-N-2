#ifndef LIBS_H
#define LIBS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef struct cola{
    char datos;
    struct cola *prox;
    struct cola *ant;
}cola_t;

//Prototipos de Funciones

void encolar( char, cola_t **, cola_t **);
void impresionDeCola( cola_t *);
void impresionDeColaInvertida( cola_t *);
void impresionDeColaNegativa( cola_t *);
void impresionDeColaInvertidaNegativa( cola_t *);

#endif /* LIBS_H*/