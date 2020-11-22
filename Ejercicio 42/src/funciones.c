#include "../libs/libs.h"

void encolar(repuestos_t datos,cola_t **in, cola_t **fin){
    if((datos.partNumber == 1234) && (datos.serialNumber&(1 << 3)) && (datos.serialNumber&(1 << 5))){ 
        cola_t *aux;

        aux = (cola_t *)malloc(sizeof(cola_t));
        aux->datos = datos;
        aux->prox = NULL;
        
        if((*in) == NULL){ //cola vacia
            aux->prox = (*in);
            (*in) = (*fin) = aux;
            (*in)->ant = NULL; 
        }
    
        else{//agrego al final
            (*fin)->prox = aux;
            aux->ant = (*fin);
            aux->prox = NULL;
            (*fin) = aux;
        } 
    }
    return;
}


void lecturaDeArchivo (cola_t **in, cola_t **fin){
    FILE *fp;
    repuestos_t datosleidos;
    
    //Lectura del archivo ordenado
	printf("\n\n***Lectura del archivo ordenado***\n\n");
	fp = fopen(REPUESTOS, "rb+");
	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",REPUESTOS);
	}
	fseek(fp, (0L), SEEK_SET);
	fread(&datosleidos,sizeof(repuestos_t),1,fp);
		while(!feof(fp)){
			printf("\nNumero de Parte: %ld\tNumero de Serie:%ld\tDescripcion:%s\t Ubicacion:%s",datosleidos.partNumber,datosleidos.serialNumber,datosleidos.descripcion,datosleidos.ubicacion);
			encolar(datosleidos,&(*in), &(*fin));
            fread(&datosleidos,sizeof(repuestos_t),1,fp);
		}

	fclose(fp);
    return;
}



void cargaEnArchivo (cola_t** fin){
    FILE *fp;
    cola_t *b = NULL;
    fp = fopen("fallados.dat", "wb+");
    if(fp==NULL){
        printf("\n***No se pudo abrir el archivo %s***", "fallados.dat");
    }
    else{
        while(*fin != NULL){
            fwrite(&(*fin)->datos, sizeof(repuestos_t),1, fp);          
            //Recorro y libero memoria
            b = (&fin);
            *fin = (*fin)->ant;
            free(b);
        }
        fclose(fp);
    }
    return;
}

