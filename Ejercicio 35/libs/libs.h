#ifndef _LIBS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define TAM1 20
#define TAM2 40

typedef struct misDatos_t {
    char pNombre[20];
    char pApellido[20];
    char pEdad;
    char pTel[20];
    char pMail[40];
} misDatos_t;
 

typedef struct pila_t { //pongo ahi el pila_t para poder usarlo adentro de la estructura
    misDatos_t dato;
    struct pila_t * prox;
} pila_t;

#endif