#include "../libs/libs.h"

int main (void){
    lista_t *in;

    in = lista();
    cargaEnArchivo(&in);

    return 0; 
}