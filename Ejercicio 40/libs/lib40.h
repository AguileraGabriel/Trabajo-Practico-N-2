#ifndef LIB40_H
#define LIB40_H

#include "../Ejercicio 39/libs.h"
#include <string.h>

#define toggleBit(var,bit) var=var^(1<<bit)

typedef struct pila{
    unsigned char pPotencia;
    struct pila *prox;
    struct pila *ant;
}pila_t;

#endif /*LIB40_H*/