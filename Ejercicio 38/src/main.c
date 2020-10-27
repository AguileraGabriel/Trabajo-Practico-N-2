#include "../libs/libs.h"

int main(void){
    cola_t *inicio=NULL, *fin=NULL;
    int x = 0, opc=0, muestra = 0;
    char dato;

    //Carga de datos para la cola
    for(x=0; x<91; x+=5){
        dato=(char)((double)127.0*sin((double)x*3.14/180));
        encolar(dato, &inicio, &fin);
    }

    //Recorridos de la cola
    impresionDeCola(inicio);
    impresionDeColaInvertida(fin);
    impresionDeColaNegativa(inicio);
    impresionDeColaInvertidaNegativa(fin);

    return 0;
}