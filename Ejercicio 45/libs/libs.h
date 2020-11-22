#ifndef LIBS_H
#define LIBS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REPUESTOS "repuestos.dat"
#define REPUESTOSACTUALIZADOS "repuestosActualizados.dat"



typedef struct{
    long partNumber;
    long serialNumber;
    char descripcion[40];       
    char ubicacion[100];        
}repuestos41_t;

typedef struct{
    long numeroDeOrden;
    char cliente[40];       
    char descripciondeFalla[200];        
    char modelo[65]; //es equivalente a Part Number
    char fecha[10];
    char hora[10];
}repuestos_t;

typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;


typedef struct cola{
    extraccionRepuestos_t dato;        
    struct cola *prox;
    struct cola *ant;
}cola_t;

//Exclusivo del 44:

typedef struct lista_t{
    repuestos_t dato;
    struct lista_t *prox;
}lista_t;

typedef struct pila_t {
    repuestos_t dato;
    struct pila_t *siguiente;
}pila_t;


typedef struct plista_t{
    extraccionRepuestos_t dato;        
    struct plista_t *prox;
}plista_t;

//Prototipos del 45
int lecturaDeArchivo (long);

void bajaFisica (int, long);
void encolar(extraccionRepuestos_t dato,cola_t **inicio, cola_t **fin);
void impresionDeCola( cola_t *inicio);

//Prototipos del 44:
void cargaArchivo (pila_t *);
void lista(repuestos_t ,struct lista_t **);
void imprimirPila(pila_t *);
void listar (void);
void imprimirPLista(plista_t *);
void listaExtraccion(extraccionRepuestos_t, struct plista_t **);

pila_t* apilar(repuestos_t ,pila_t **);

repuestos_t cargar(void);
#endif /*LIBS_H*/






