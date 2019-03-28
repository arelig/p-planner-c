#ifndef TLISTA_H_INCLUDED
#define TLISTA_H_INCLUDED

typedef struct celda* TPosicion;

typedef void* TElemento;

typedef struct celda
{
    TElemento* elemento;
    struct celda* celda_anterior;
    struct celda* celda_siguiente;
}*TLista;

void crear_lista(TLista* lista);
int l_insertar(TLista* lista, TPosicion pos,TElemento elem);
int l_eliminar(TLista* lista, TPosicion pos);
TPosicion l_primera(TLista lista);
TPosicion l_ultima(TLista lista);
TPosicion l_anterior(TLista lista, TPosicion pos);
TPosicion l_siguiente(TLista lista, TPosicion pos);
TElemento l_recuperar(TLista lista,TPosicion pos);
int l_size(TLista lista);
int l_destruir(TLista* lista);


#endif // TLISTA_H_INCLUDED
