#include "../libs/lib40.h"


/*
    Busca por ID en el archivo potencia.dat y obtiene el dato
*/
carga_t lecturaDelArchivo (long ID){
    FILE *fp;
    carga_t datosleidos;

    fp = fopen("potencia.dat", "rb+");
	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n","potencia.dat");
	}

    fseek(fp,(ID)*sizeof(carga_t), SEEK_SET); 
    fread (&datosleidos, sizeof(carga_t), 1, fp);
    printf("\n--->El Original<---\n");
    printf ("ID: %d\t Desc: %s\t Potencia: %d\t Estado: %d \t Baja/Alta: %c\n",  datosleidos.id, datosleidos.leidos.desc ,datosleidos.leidos.potencia, datosleidos.leidos.estado, datosleidos.estado);

    fclose(fp);
	return datosleidos;
}


/*
    Actualiza el archivo potencia.dat
*/
void actualizacionDelArchivo (long ID, carga_t dato){
    FILE *fp;
    carga_t datosleidos = dato;

    fp = fopen("potencia.dat", "rb+");
	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n","potencia.dat");
	}

    fseek(fp,(ID)*sizeof(carga_t), SEEK_SET); 
    fwrite (&datosleidos, sizeof(carga_t), 1, fp);

    fclose(fp);

}


/*
    Invierte la Palabra
*/
char* inversionDePalabra (carga_t dato){
    char palabra[60] = " ";
    int i = 0;
    while((dato.leidos.desc[i] != ' ') && (dato.leidos.desc[i] != '\0')){
        palabra[i] = dato.leidos.desc[i];
        i++;
    }
    return strrev(palabra);
}


/*
   Genera el nuevo archivo y carga los datos
*/
void nuevoArchivoSalida (carga_t datos){
    FILE *fp;

    fp = fopen("salida.dat", "rb+");
    
    if (fp == NULL){
		printf ("Error en la apertura del archivo %s, se va a crear\n","salida.dat");
        fp = fopen("salida.dat", "wb+");
	}

	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, no se creo\n","salida.dat");
	}
    else{
        printf("\n ---> Dato Modificado <---");
        printf ("\nID: %d\t Desc: %s\t Potencia: %d\t Estado: %d \t Baja/Alta: %c\n",  datos.id, datos.leidos.desc ,datos.leidos.potencia, datos.leidos.estado, datos.estado);
        fwrite(&datos,sizeof(carga_t),1,fp);
    }
    fclose(fp);
}

/*
    Genera la pila si se cumple la condicion pedida
*/
void apilar (carga_t dato, pila_t **inicio, pila_t **fin){ 
    if ((dato.leidos.estado & (1 << 0)) && (dato.leidos.estado  & (1 << 2))){
        pila_t *aux;
        aux = (pila_t *)malloc(sizeof(pila_t));
        aux->pPotencia = dato.leidos.potencia; //cargo valor de potencia 
        aux->prox = NULL;
    
        if((*inicio) == NULL){ //pila vacia
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
    }else{
        //printf("\n entre al else....\n");
        nuevoArchivoSalida(dato);
    }
}