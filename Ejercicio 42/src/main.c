#include "../libs/libs.h"

int main (void){
    cola_t *in=NULL, *fin=NULL;

    lecturaDeArchivo (&in, &fin);
    cargaEnArchivo (&fin);

    return 0; 
}
