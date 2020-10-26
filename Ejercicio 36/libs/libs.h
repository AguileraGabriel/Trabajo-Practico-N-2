#ifndef LIBS_H
#define LIBS_H

#include "../../Ejercicio 35/libs/libs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct lista_t{
    misDatos_t dato;
    struct lista_t *prox;
}lista_t;

#define CONTACTOS_ORDENADOS "contactos_ordenados.dat"
#define CONTACTOS "contactos.dat"

#endif /* LIBS_H */