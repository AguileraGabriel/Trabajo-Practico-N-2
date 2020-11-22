#include "../libs/libs.h"


int lecturaDeArchivo (long PN){
    FILE *fp;
    repuestos41_t datosleidos;
    int cont = 0;
    //Lectura del archivo ordenado
	printf("\n\n---> Lectura del archivo ordenado <---\n\n");
	fp = fopen(REPUESTOS, "rb+");
	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",REPUESTOS);
	}
	fread(&datosleidos,sizeof(repuestos41_t),1,fp);
		while(!feof(fp)){
            printf("\nNumero de Parte: %ld\tNumero de Serie:%ld\tDescripcion:%s\t Ubicacion:%s",datosleidos.partNumber,datosleidos.serialNumber,datosleidos.descripcion,datosleidos.ubicacion);
            if(datosleidos.partNumber == PN){ 
                cont++;
            }
			fread(&datosleidos,sizeof(repuestos41_t),1,fp);
		}
	fclose(fp);
    
    return cont;
}



void bajaFisica (int cantidadSolicida, long PN){
    FILE *fp;   //archivo de datos originales (el de altas y bajas).
    FILE *fpActualizado;  //para altas.
    repuestos41_t leidos;
    int c=0, ch=0;

    fp = fopen(REPUESTOS, "rb");// "rb" arranca al inicio como lectura.
    fpActualizado = fopen(REPUESTOSACTUALIZADOS, "wb");

    if (!fp || !fpActualizado){
        printf("\nNo se pudo abrir o crear alguno de los archivos");
    }
    fread(&leidos, sizeof(repuestos41_t),1,fp);
    
    while(!feof(fp)){
        if((leidos.partNumber == PN) && (ch < cantidadSolicida)){
            ch++;
            printf ("\nValor de CH: %d", ch);
        }
        else{
            fwrite(&leidos, sizeof(repuestos41_t),1,fpActualizado); //escribo en el archivo de altas.
            c++;
        }
        fread(&leidos, sizeof(repuestos41_t),1,fp);
    }
    fclose(fp);
    //fclose(fph);
    fclose(fpActualizado);

    printf ("\nValor final de CH: %d", ch);
    
    if(remove(REPUESTOS)){ //elimino el archivo original(el de altas y bajas).
        printf("\nNo se pudo eliminar");
    }
    
    if(rename(REPUESTOSACTUALIZADOS,REPUESTOS)){ //el archivo con todas las altas es renombrado como el original.
        printf("\nNo se pudo renombrar");
    }
    
    printf("\n %ld registro(s) actualizados", c);
    printf("\n %ld registro(s) dados de baja", ch);
        
    return;
}



void encolar(extraccionRepuestos_t dato,cola_t **inicio, cola_t **fin){
    cola_t *aux;
    aux = (cola_t *)malloc(sizeof(cola_t));
    if(aux == NULL){
        printf("\n Error");
    }
    
    else{
        aux->dato = dato;
        aux->prox = NULL;
        
        
        if((*inicio) == NULL){ //cola vacia
            aux->prox = (*inicio);
            (*inicio) = (*fin) = aux;
            (*inicio)->ant = NULL; 
        }
    
        else{//agrego al final
            (*fin)->prox = aux;
            aux->ant = (*fin);
            aux->prox = NULL;
            (*fin) = aux;
        }
    }
}

void impresionDeCola( cola_t *inicio){
    printf("\n\t--->Imprimo la Cola<---");
    
    while(inicio != NULL){
        printf("\nNumero de Orden: %ld \t Cliente: %s \t Falla: %s \t Modelo(PN): %s \t Fecha y hora: %s - %s", inicio->dato.repuesto.numeroDeOrden, inicio->dato.repuesto.cliente, inicio->dato.repuesto.descripciondeFalla, inicio->dato.repuesto.modelo, inicio->dato.repuesto.fecha, inicio->dato.repuesto.hora);
        inicio = inicio->prox;
    }
}

//Funciones del 44:
void cargaArchivo (pila_t *pila){
    FILE *fp;
    repuestos_t carga;
    

    fp = fopen(REPUESTOS, "ab+");
    if (fp == NULL){
        printf("\nNo se pudo abrir el el archivo, se va a crear");
        
        fp = fopen(REPUESTOS, "wb+");
        if (fp == NULL){
            printf("\nError al crear archivo");
            return;
        }
        
    }
    else{
        while(pila){
            //carga = pila->dato;
            fwrite(&pila->dato,sizeof(repuestos_t),1,fp);
            pila = pila->siguiente;
        }
        fclose (fp);

    }
}

repuestos_t cargar(void){
    repuestos_t cargado;
    printf("\nNumero de Orden:");
    scanf("%ld",&cargado.numeroDeOrden);
    fflush(stdin);
    printf("Cliente:");
    scanf("%s",&cargado.cliente);
    fflush(stdin);
    printf("Falla:");
    scanf("%s",&cargado.descripciondeFalla);
    fflush(stdin);
    printf("Modelo:");
    scanf("%s",&cargado.modelo);
    fflush(stdin);
    printf("Fecha:");
    scanf("%s",&cargado.fecha);
    fflush(stdin);
    printf("Hora:");
    scanf("%s",&cargado.hora);
    fflush(stdin);
    return cargado;
}

void lista(repuestos_t dato,struct lista_t **in){
    struct lista_t *pre=NULL, *r=NULL, *aux=NULL; 

    aux=(lista_t*) malloc(sizeof(lista_t));
    if(aux == NULL){
        printf("\n Error");
    }
    else{
        aux->dato=dato;
        aux->prox=NULL;

        if(*in == NULL){
            *in = aux;
        }
        else{
            char auxFyH[20] = "";
            char inFyH[20] = "";
            strcat(auxFyH,aux->dato.fecha);
            strcat(auxFyH,aux->dato.hora);
            strcat(inFyH,(*in)->dato.fecha);
            strcat(inFyH,(*in)->dato.hora);
            printf("\n aux: %s",auxFyH);
            printf("\n  in: %s",inFyH);
            
            if(atoi(auxFyH) < atoi(inFyH)){ //inicio lista
                aux->prox=(*in); //el proximo del reservado en memoria sera in. 
                (*in) = aux;
            }
            else
            {
                r = (*in); //puntero en el cual estoy
                pre = (*in); //apunta al anterior al que uso para recorrer.
                
                while ((atoi(auxFyH) >= atoi(inFyH) && r->prox != NULL)){ //hasta que prox sea null o el que agregue sea mayor
                    pre = r; 
                    r = r->prox; 
                }
                if(atoi(auxFyH) >= atoi(inFyH)){ //caso para nodo en la parte central.
                    r->prox = aux;
                }
                else{  //en caso de estar al final.
                    aux->prox = r; 
                    pre->prox = aux; 
                }
            }  
        }		    
        return;
    }
}



void imprimirPila(pila_t *ultimo){
    pila_t *p= NULL, *aux= NULL;
    printf("\n\n *** Imprimo la Pila ***\n");
    p = ultimo;
    
    while(p){
        aux=p;
        printf ("\nNumero de Orden: %ld \t Cliente: %s \t Falla: %s \t Modelo: %s \t Fecha y Hora: %s - %s",  p->dato.numeroDeOrden, p->dato.cliente, p->dato.descripciondeFalla, p->dato.modelo, p->dato.fecha, p->dato.hora);

        p=p->siguiente;
        free(aux); 
    }
    return;
}



pila_t* apilar(repuestos_t cargado,pila_t **ultimo){
    pila_t *aux = NULL; //inicializo en null.
    aux=(pila_t *) malloc(sizeof(pila_t)); //reservo memoria.
        if(aux == NULL){
        printf("\n Error");
    }
    else{
    //cargo datos
    aux->dato = cargado;
    //termino carga de datos.

    aux->siguiente = *ultimo; //sig de aux apunta al ahora anteultimo.
    return aux;
    }
    return NULL;
}

void listar (void){
    FILE *fp;
    repuestos_t leido;

    fp = fopen(REPUESTOS, "rb+");
    if (fp == NULL){
        printf("\nNo se pudo abrir el el archivo");
        return;
    }
    else{
        printf("\n\n *** Impresion del Archivo *** ");
        //Lectura anticipada
        fread(&leido, sizeof(repuestos_t),1,fp);
        while (!feof(fp)){ //pregunta al principio
            printf ("\nNumero de Orden: %ld \t Cliente: %s \t Falla: %s \t Modelo: %s \t Fecha y Hora: %s - %s",  leido.numeroDeOrden, leido.cliente, leido.descripciondeFalla, leido.modelo, leido.fecha, leido.hora);
            fread(&leido, sizeof(repuestos_t),1,fp);
        }
        fclose (fp);
    }
}



void imprimirPLista(plista_t *r){ 
    printf("\n**Entre a imprimirPLista**");  
	while(r){
		printf ("\nModelo: %s \t Cantidad: %d \t Numero de Orden: %ld \t Cliente: %s \t Falla: %s \t  Fecha y Hora: %s - %s",  r->dato.repuesto.modelo, r->dato.cantidad,r->dato.repuesto.numeroDeOrden, r->dato.repuesto.cliente, r->dato.repuesto.descripciondeFalla, r->dato.repuesto.fecha, r->dato.repuesto.hora);
		r = r->prox;
	}
}


void listaExtraccion(extraccionRepuestos_t dato,struct plista_t **in){
    struct plista_t *pre=NULL, *r=NULL, *aux=NULL; 

    aux=(plista_t*) malloc(sizeof(plista_t));
    if(aux == NULL){
        printf("\n Error");
    }
    else{
        aux->dato=dato;
        aux->prox=NULL;

        if(*in == NULL){
            *in = aux;
        }
        else{
            if(strcmp(aux->dato.repuesto.modelo,(*in)->dato.repuesto.modelo) < 0 ){ //inicio lista
                aux->prox=(*in); //el proximo del reservado en memoria sera in. 
                (*in) = aux;
            }
            else
            {
                r = (*in); //puntero en el cual estoy
                pre = (*in); //apunta al anterior al que uso para recorrer.
                
                while ((strcmp(aux->dato.repuesto.modelo,r->dato.repuesto.modelo) > 0) && (r->prox != NULL)){ //hasta que prox sea null o el que agregue sea mayor
                    pre = r; 
                    r = r->prox;             
                }

                if(strcmp(aux->dato.repuesto.modelo,r->dato.repuesto.modelo) > 0){ //caso para nodo en la parte central.
                    r->prox = aux; 
                }
                else if(strcmp(aux->dato.repuesto.modelo,r->dato.repuesto.modelo) == 0){
                    printf("\nIguales IF (parte central)\n");
                    r->dato.cantidad = r->dato.cantidad + aux->dato.cantidad;
                    free(aux);
                }
                else{  //en caso de estar al final.
                    aux->prox = r; 
                    pre->prox = aux; 
                }
            }  
        }		    
        return;
    }
}

