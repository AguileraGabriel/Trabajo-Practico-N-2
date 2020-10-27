#include "../libs/libs.h"

int main (void){
    
    struct lista_t *in=NULL, *r=NULL;
    
    apilar (&in);
    r = in;
    impresionDeLista (r);
    cargaYLiberacionDeMemoria (&r);
    apreturaDeArchivo ();

    return 0;
}