


#include "../libs/libs.h"


int main(void) {
    int i=0;
    char edad;
    char nombre[TAM1], apellido[TAM1], mail[TAM2], tel[TAM1], preg[2];
    pila_t *p, *aux;
    pila_t * tope;
    int count = 0;
    p=aux= NULL; //Iniciamos los punteros apuntando a Null
    size_t size = 0;
    int ingresar = 1;
    int fwrite_res = 0;
    FILE *fp;
    FILE * infile; //usado para verificar que se cargen bien los datos
    struct pila_t input;
    
    for(i; ingresar == 1; i++){

        do {
            count = 0;
            printf("\n Quiere ingresar un nuevo usuario? (s|n):");
            count = scanf("%s",&preg);
            fflush(stdin);
            if (count > 0 && strcmp(preg, "s") != 0 && strcmp(preg, "n") != 0) {
                count = -1;
            }
        } while (count < 0);

        if (strcmp(preg, "n") == 0) {
            ingresar = 0;
            continue;
        }
          
        printf("\n Ingrese Nombre:");
        scanf("%s",&nombre);
        fflush(stdin);
        printf(" Ingrese Apellido:");
        scanf("%s",&apellido);
        fflush(stdin);
        printf(" Ingrese Edad:");
        scanf("%d",&edad);
        fflush(stdin);
        printf(" Ingrese Telefono:");
        scanf("%s",&tel);
        fflush(stdin);
        printf(" Ingrese Mail:");
        scanf("%s",&mail);
        fflush(stdin);
        
        aux=(pila_t *) malloc(sizeof(pila_t));
        //Carga de datos en la pila
        strcpy(aux->dato.pNombre, nombre);
        strcpy(aux->dato.pApellido, apellido);
        strcpy(aux->dato.pMail, mail);
        aux->dato.pEdad = edad;
        strcpy(aux->dato.pTel, tel);

        //Desplazamiento del puntero hacia el siguiente
        aux->prox = p;
        p = aux;
        tope = aux;
        size++;
    }
    
    fp = fopen ("contactos.dat", "wb+"); 
    if (fp == NULL) 
    { 
        fprintf(stderr, "\nError en apertura de archivo\n"); 
        exit (1);
    } 
    printf("\n\n -->Comienza la Impresion y el guardado de Datos <--\n");
    p = tope;
    for(i=0; i<size; i++){
        aux=p;
        printf("\nNombre: %s",p->dato.pNombre);
        printf("\nApellido: %s",p->dato.pApellido);
        printf("\nEdad: %d",p->dato.pEdad);
        printf("\nTelefono: %s",p->dato.pTel);
        printf("\nMail: %s",p->dato.pMail);

        // Escribir en archivo
        // https://www.geeksforgeeks.org/readwrite-structure-file-c/
        if (p->dato.pEdad > 21) {
            printf("\n-->Lo cargo es mayor a 21");
            fwrite_res = fwrite(p, sizeof(struct pila_t), 1, fp); 
            if(fwrite_res != 0)  
                printf("\t Contenido cargado en el archivo !\n"); 
            else {
                printf("\t Error escribiendo en archivo !\n");
                perror("error");
            } 
        }
        else {
            printf("\n-->No lo cargo es menor a 21");
        }
        p=p->prox;
    }

    // close file 
    fclose (fp); 

    printf("\n\n -->Liberamos la memoria <--\n");
    p = tope;
    for(i=0; i<size; i++){
        aux=p;
        p=p->prox;
        free(aux);   
    }
   
    //Lectura del Archivo
    printf("\n--> Comienza la lectura del archivo <--\n");
    
    // Abro el archivo para la lectura
    infile = fopen("contactos.dat", "rb+"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 

    while(fread(&input, sizeof(struct pila_t), 1, infile)) {
        printf ("\nNombre: %s\t Apellido: %s\t Edad: %d\t Telefono: %s\t Mail: %s",  input.dato.pNombre,input.dato.pApellido, input.dato.pEdad, input.dato.pTel, input.dato.pMail); 
    }
           
    // Cierro el archivo 
    fclose (infile); 

    return 0;
}