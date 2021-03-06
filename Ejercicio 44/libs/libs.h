#ifndef LIBS_H
#define LIBS_H 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define REPUESTOS "repuestos.dat"

typedef struct{
    long numeroDeOrden;
    char cliente[40];       
    char descripciondeFalla[200];        
    char modelo[65];
    char fecha[10];
    char hora[10];
}repuestos_t;


typedef struct lista_t{
    repuestos_t dato;
    struct lista_t *prox;
}lista_t;

typedef struct pila_t {
    repuestos_t dato;
    struct pila_t *siguiente;
}pila_t;


typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;


typedef struct plista_t{
    extraccionRepuestos_t dato;        
    struct plista_t *prox;
}plista_t;

//Prototipos

void cargaArchivo (pila_t *);
void lista(repuestos_t ,struct lista_t **);
void imprimirPila(pila_t *);
void listar (void);
void imprimirPLista(plista_t *);
void listaExtraccion(extraccionRepuestos_t, struct plista_t **);

pila_t* apilar(repuestos_t ,pila_t **);

repuestos_t cargar(void);

#endif /* LIBS_H */