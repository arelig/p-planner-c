#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

#include "define.h"

typedef void *TClave;
typedef void *TValor;

typedef struct entrada{
    TClave clave;
    TValor valor;
} *TEntrada;

typedef struct nodo{
    TEntrada entrada;
    struct nodo *padre;
    struct nodo *hijo_izquierdo;
    struct nodo *hijo_derecho;
} *TNodo;

typedef struct cola_con_prioridad {
    unsigned int cantidad_elementos;
    TNodo raiz;
} *TColaCP;

void crear_cola_cp(TColaCP* cola, int (*f)(TEntrada p, TEntrada q));
int cp_insertar(TColaCP cola, TEntrada entr);
TEntrada cp_eliminar(TColaCP cola);
int cp_size(TColaCP cola);
int cp_destruir(TColaCP cola);


#endif // COLACP_H_INCLUDED
