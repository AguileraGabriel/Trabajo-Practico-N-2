#include "../libs/libs.h"

int main(void){
	struct lista_t *ant=NULL, *r=NULL, *aux=NULL, *in=NULL, *b=NULL;
    struct lista_t persona;
    misDatos_t datosleidos;
	FILE *fp;

	//Leo los datos de mi archivo importado contactos.dat 
	fp = fopen (CONTACTOS,"rb+");
	if (!fp){
		printf("Error en la apertura del archivo %s \n",CONTACTOS);
		return 1;
	}
	while(fread(&persona,sizeof(struct pila_t),1,fp)){
		aux=(lista_t*) malloc(sizeof(lista_t));
		aux->dato=persona.dato;
		
  
		aux->prox=NULL;

		if(in == NULL){
			in = aux;
		}
		else{
			if(0 > strcmp(aux->dato.pApellido, in->dato.pApellido)){ //si cargo al inicio de la lista 
				aux->prox=in;
				in = aux;
			}
			else
			{
				r = in; //puntero de recorrido igual al de inicio
				ant = in; //puntero de anterior igual al de inicio
				
				while (0 <= strcmp(aux->dato.pApellido, r->dato.pApellido) && r->prox != NULL){ //mientras el dato ingresado sea mayor al objeto evaluedo y mientras sea distinto a fin de lista.
					ant = r; //ant ahora es r
					r = r->prox; //r adopta el valor del siguiente
				}
				if(0 <= strcmp(aux->dato.pApellido, r->dato.pApellido)){ //si el dato esta en el medio de la lista 
					r->prox = aux;
				}
				else{  //Si cargo al final de la lista
					aux->prox = r; // llegado a este punto r = NULL.
					ant->prox = aux; //el anterior a fin de lista es nuetro valor ingresado.
				}
			}  
		}		
	}
	fclose(fp);

    /*
	//IMPRESION DE LA LISTA ORDENADA
	r = in;
    printf("\n\n\t---> Lista completa ya ordenada por apellido <---\n\n");
    while(r != NULL){
        printf ("Nombre: %s\t\t Apellido: %s\t\t Edad: %d\t\t Telefono: %s\t\t Mail: %s \n",  r->dato.pNombre, r->dato.pApellido, r->dato.pEdad, r->dato.pTel, r->dato.pMail); 
		r = r->prox;
	}
	*/
	
	//Carga en el nuevo archivo
	fp = fopen(CONTACTOS_ORDENADOS, "wb+");
	if (!fp){
		printf("Error en la creacion del archivo %s",CONTACTOS_ORDENADOS);
		return 1;
	}
	r = in; //igualo el puntero de recorrido con el inicial
	while(r){
		fwrite(&(r->dato),sizeof(struct misDatos_t),1,fp);
		b = r;
		r = r->prox;
		free(b); //libero memoria
	}
	fclose(fp);

    //Lectura del archivo ordenado
	printf("\n\n---> Lectura del archivo ordenado <---\n\n");
	fp = fopen(CONTACTOS_ORDENADOS, "rb+");
	if (fp == NULL){
		printf ("Error en la apertura del archivo %s, puede que no exista\n",CONTACTOS_ORDENADOS);
		return 1;
	}
	fseek(fp, (0L), SEEK_SET);
	fread(&datosleidos,sizeof(struct misDatos_t),1,fp);
		while(!feof(fp)){
			printf ("--> Apellido: %s\t Nombre: %s\t Edad: %d\t Telefono: %s\t Mail: %s \n",  datosleidos.pApellido, datosleidos.pNombre, datosleidos.pEdad, datosleidos.pTel, datosleidos.pMail);
			fread(&datosleidos,sizeof(struct misDatos_t),1,fp);
		}

	fclose(fp);


	return 0;
}