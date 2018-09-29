#include <stdio.h>
#include <stdlib.h>
#include "TLista.h"

int main()
{
    int i;
    TLista listaPrueba;
    crear_lista(&listaPrueba);
    for(i=0;i<6;i++)
        l_insertar(&listaPrueba,NULL,i);
    return 0;
}
