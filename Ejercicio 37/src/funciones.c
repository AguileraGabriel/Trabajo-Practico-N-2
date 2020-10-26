#include "../libs/libs.h"

/*
    Creacion del archivo datos.dat
*/
void crear_fichero (){ 
    FILE *fp;
    int i, opc=0, tipo=0;
    struct d r;
    if ((fp = fopen(DATOS, "wb")) == NULL){
        printf ("Error en apertura del fichero para escritura\n");
    }
    else {
        printf("---> Creacion del archivo <---");
        do{ 
            printf("\nTipo: ");
            scanf("%d",&tipo); 
            r.tipo = (unsigned char)tipo;
            printf("Clave: ");
            scanf("%ld",&r.clave);
            r.b = 'A';
            printf("De una descripcion: ");
            scanf("%s",&(r.d)); 
            fwrite(&r, sizeof(r), 1, fp);
        
            printf("1) Cotinuar 0) Salir: ");
            scanf("%d",&opc);  
        }while(opc!=0);

     fclose (fp);
    }
}


/*
    Esta funcion recive la clave a buscar y a su vez dos parametros que 
    son modificados para luego poder utilizarce para apilar y evitar el 
    uso de VARIABLES GLOBALES, modificando directamente el contenido de 
    las mismas.
*/
void leer_fichero (long clave, int *posicion, struct d *dato){ 
    FILE *fp;
    int control = 1; //variable de control para el while
    (*posicion) = 1;

    if ((fp = fopen(DATOS, "rb")) == NULL){ 
        printf ( "Error en apertura del fichero para lectura \n " );
    }
    else{ 
        fread (dato, sizeof(struct d), 1, fp);
        while (!feof(fp)&&(control==1)){ 
            if(clave == dato->clave && dato->b =='A'){ //busco si esta la clave y si se encuentra de alta
                control = 0;
                fclose (fp);
                break;
            }
            fread (dato, sizeof(struct d), 1, fp);
            (*posicion)++;
        }
        
        if(control){
            (*posicion)=-1;
        }
        fclose (fp);
    }
}

/*
    Esta funcion genera la pila si se cumple con la condicion solicitada
*/
pila_t* ejercicio (long clave, int posicion, struct d dato, pila_t *pila){ //si posicion = -1 no arma la cola
    pila_t *aux;
    pila_t *tope = pila;
    aux = NULL;

    if((dato.tipo & (1 << 4)) && (posicion > 0)){
        printf("---> Registro Encontrado <---");
        //Reserva de memoria
        aux=(pila_t *) malloc(sizeof(pila_t));
        
        ///Cargo los datos en la pila
        aux->dato.clave = dato.clave;
        aux->dato.posicion = posicion;
        
        //Condicion de movimiento de punteros
        if(!pila){
            aux->prox = NULL;
            tope = aux;
        }
        else{
            aux->prox = tope;
            tope = aux;
        }
    }
    else{
        printf("---> Registro no encontrado <---\n");
    } 
    return tope; 
}


/*
    Imprime los datos del Archivo, utilizando la pila como acceso
*/
void impresionOrdenado (long ubicacion){
    FILE *fp;
    struct d datos;

    if ((fp = fopen(DATOS, "rb")) == NULL){
        printf ("Error en apertura del fichero para escritura\n");
    }
    
    else{
        fseek(fp,(ubicacion-1)*sizeof(datos), SEEK_SET);         
        fread (&datos, sizeof(datos), 1, fp);
        printf ("\nTipo:%d \tDescripcion:%s \tEstado:%c \tClave:%ld\n" , datos.tipo, datos.d, datos.b, datos.clave);
    }
    fclose(fp);
}
